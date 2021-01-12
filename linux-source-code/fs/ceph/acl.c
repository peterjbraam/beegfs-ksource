/*
 * linux/fs/ceph/acl.c
 *
 * Copyright (C) 2013 Guangliang Zhao, <lucienchao@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License v2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 021110-1307, USA.
 */

#include <linux/ceph/ceph_debug.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/xattr.h>
#include <linux/posix_acl_xattr.h>
#include <linux/posix_acl.h>
#include <linux/sched.h>
#include <linux/slab.h>

#include "super.h"

static inline void ceph_set_cached_acl(struct inode *inode,
					int type, struct posix_acl *acl)
{
	struct ceph_inode_info *ci = ceph_inode(inode);

	spin_lock(&ci->i_ceph_lock);
	if (__ceph_caps_issued_mask(ci, CEPH_CAP_XATTR_SHARED, 0))
		set_cached_acl(inode, type, acl);
	spin_unlock(&ci->i_ceph_lock);
}

static inline struct posix_acl *ceph_get_cached_acl(struct inode *inode,
							int type)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	struct posix_acl *acl = ACL_NOT_CACHED;

	spin_lock(&ci->i_ceph_lock);
	if (__ceph_caps_issued_mask(ci, CEPH_CAP_XATTR_SHARED, 0))
		acl = get_cached_acl(inode, type);
	spin_unlock(&ci->i_ceph_lock);

	return acl;
}

struct posix_acl *ceph_get_acl(struct inode *inode, int type)
{
	int size;
	const char *name;
	char *value = NULL;
	struct posix_acl *acl;

	if (!IS_POSIXACL(inode))
		return NULL;

	acl = ceph_get_cached_acl(inode, type);
	if (acl != ACL_NOT_CACHED)
		return acl;

	switch (type) {
	case ACL_TYPE_ACCESS:
		name = POSIX_ACL_XATTR_ACCESS;
		break;
	case ACL_TYPE_DEFAULT:
		name = POSIX_ACL_XATTR_DEFAULT;
		break;
	default:
		BUG();
	}

	size = __ceph_getxattr(inode, name, "", 0);
	if (size > 0) {
		value = kzalloc(size, GFP_NOFS);
		if (!value)
			return ERR_PTR(-ENOMEM);
		size = __ceph_getxattr(inode, name, value, size);
	}

	if (size > 0)
		acl = posix_acl_from_xattr(&init_user_ns, value, size);
	else if (size == -ERANGE || size == -ENODATA || size == 0)
		acl = NULL;
	else
		acl = ERR_PTR(-EIO);

	kfree(value);

	if (!IS_ERR(acl))
		ceph_set_cached_acl(inode, type, acl);

	return acl;
}

static int ceph_set_acl(struct dentry *dentry, struct inode *inode,
				struct posix_acl *acl, int type)
{
	int ret = 0, size = 0;
	const char *name = NULL;
	char *value = NULL;
	struct iattr newattrs;
	umode_t new_mode = inode->i_mode, old_mode = inode->i_mode;

	switch (type) {
	case ACL_TYPE_ACCESS:
		name = POSIX_ACL_XATTR_ACCESS;
		if (acl) {
			ret = posix_acl_update_mode(inode, &new_mode, &acl);
			if (ret)
				goto out;
		}
		break;
	case ACL_TYPE_DEFAULT:
		if (!S_ISDIR(inode->i_mode)) {
			ret = acl ? -EINVAL : 0;
			goto out;
		}
		name = POSIX_ACL_XATTR_DEFAULT;
		break;
	default:
		ret = -EINVAL;
		goto out;
	}

	if (acl) {
		size = posix_acl_xattr_size(acl->a_count);
		value = kmalloc(size, GFP_NOFS);
		if (!value) {
			ret = -ENOMEM;
			goto out;
		}

		ret = posix_acl_to_xattr(&init_user_ns, acl, value, size);
		if (ret < 0)
			goto out_free;
	}

	if (new_mode != old_mode) {
		newattrs.ia_ctime = current_fs_time(inode->i_sb);
		newattrs.ia_mode = new_mode;
		newattrs.ia_valid = ATTR_MODE;
		ret = __ceph_setattr(dentry, &newattrs);
		if (ret)
			goto out_free;
	}

	ret = __ceph_setxattr(dentry, name, value, size, 0);
	if (ret) {
		if (new_mode != old_mode) {
			newattrs.ia_mode = old_mode;
			newattrs.ia_valid = ATTR_MODE;
			__ceph_setattr(dentry, &newattrs);
		}
		goto out_free;
	}

	ceph_set_cached_acl(inode, type, acl);

out_free:
	kfree(value);
out:
	return ret;
}

int ceph_pre_init_acls(struct inode *dir, umode_t *mode,
		       struct ceph_acls_info *info)
{
	struct posix_acl *acl = NULL, *default_acl = NULL;
	size_t val_size1 = 0, val_size2 = 0;
	struct ceph_pagelist *pagelist = NULL;
	void *tmp_buf = NULL;
	int err;

	if (S_ISLNK(*mode) || !IS_POSIXACL(dir))
		return 0;

	default_acl = ceph_get_acl(dir, ACL_TYPE_DEFAULT);
	if (IS_ERR(default_acl))
		return PTR_ERR(default_acl);

	if (!default_acl) {
		*mode &= ~current_umask();
		return 0;
	}

	if (S_ISDIR(*mode)) {
		acl = posix_acl_dup(default_acl);
	} else {
		acl = default_acl;
		default_acl = NULL;
	}

	err = posix_acl_create(&acl, GFP_NOFS, mode);
	if (err < 0)
		goto out_err;
	if (err == 0) {
		posix_acl_release(acl);
		acl = NULL;
	}

	if (!default_acl && !acl)
		return 0;

	if (acl)
		val_size1 = posix_acl_xattr_size(acl->a_count);
	if (default_acl)
		val_size2 = posix_acl_xattr_size(default_acl->a_count);

	err = -ENOMEM;
	tmp_buf = kmalloc(max(val_size1, val_size2), GFP_NOFS);
	if (!tmp_buf)
		goto out_err;
	pagelist = kmalloc(sizeof(struct ceph_pagelist), GFP_NOFS);
	if (!pagelist)
		goto out_err;
	ceph_pagelist_init(pagelist);

	err = ceph_pagelist_reserve(pagelist, PAGE_SIZE);
	if (err)
		goto out_err;

	ceph_pagelist_encode_32(pagelist, acl && default_acl ? 2 : 1);

	if (acl) {
		size_t len = strlen(POSIX_ACL_XATTR_ACCESS);
		err = ceph_pagelist_reserve(pagelist, len + val_size1 + 8);
		if (err)
			goto out_err;
		ceph_pagelist_encode_string(pagelist, POSIX_ACL_XATTR_ACCESS,
					    len);
		err = posix_acl_to_xattr(&init_user_ns, acl,
					 tmp_buf, val_size1);
		if (err < 0)
			goto out_err;
		ceph_pagelist_encode_32(pagelist, val_size1);
		ceph_pagelist_append(pagelist, tmp_buf, val_size1);
	}
	if (default_acl) {
		size_t len = strlen(POSIX_ACL_XATTR_DEFAULT);
		err = ceph_pagelist_reserve(pagelist, len + val_size2 + 8);
		if (err)
			goto out_err;
		err = ceph_pagelist_encode_string(pagelist,
						  POSIX_ACL_XATTR_DEFAULT, len);
		err = posix_acl_to_xattr(&init_user_ns, default_acl,
					 tmp_buf, val_size2);
		if (err < 0)
			goto out_err;
		ceph_pagelist_encode_32(pagelist, val_size2);
		ceph_pagelist_append(pagelist, tmp_buf, val_size2);
	}

	kfree(tmp_buf);

	info->acl = acl;
	info->default_acl = default_acl;
	info->pagelist = pagelist;
	return 0;
out_err:
	posix_acl_release(acl);
	posix_acl_release(default_acl);
	kfree(tmp_buf);
	if (pagelist)
		ceph_pagelist_release(pagelist);
	return err;
}

void ceph_init_inode_acls(struct inode* inode, struct ceph_acls_info *info)
{
	if (!inode)
		return;
	ceph_set_cached_acl(inode, ACL_TYPE_ACCESS, info->acl);
	ceph_set_cached_acl(inode, ACL_TYPE_DEFAULT, info->default_acl);
}

void ceph_release_acls_info(struct ceph_acls_info *info)
{
	posix_acl_release(info->acl);
	posix_acl_release(info->default_acl);
	if (info->pagelist)
		ceph_pagelist_release(info->pagelist);
}

int ceph_acl_chmod(struct dentry *dentry, struct inode *inode)
{
	struct posix_acl *acl;
	int ret = 0;

	if (S_ISLNK(inode->i_mode)) {
		ret = -EOPNOTSUPP;
		goto out;
	}

	if (!IS_POSIXACL(inode))
		goto out;

	acl = ceph_get_acl(inode, ACL_TYPE_ACCESS);
	if (IS_ERR_OR_NULL(acl)) {
		ret = PTR_ERR(acl);
		goto out;
	}

	ret = posix_acl_chmod(&acl, GFP_KERNEL, inode->i_mode);
	if (ret)
		goto out;
	ret = ceph_set_acl(dentry, inode, acl, ACL_TYPE_ACCESS);
	posix_acl_release(acl);
out:
	return ret;
}

static int ceph_xattr_acl_get(struct dentry *dentry, const char *name,
				void *value, size_t size, int type)
{
	struct posix_acl *acl;
	int ret = 0;

	if (!IS_POSIXACL(dentry->d_inode))
		return -EOPNOTSUPP;

	acl = ceph_get_acl(dentry->d_inode, type);
	if (IS_ERR(acl))
		return PTR_ERR(acl);
	if (acl == NULL)
		return -ENODATA;

	ret = posix_acl_to_xattr(&init_user_ns, acl, value, size);
	posix_acl_release(acl);

	return ret;
}

static int ceph_xattr_acl_set(struct dentry *dentry, const char *name,
			const void *value, size_t size, int flags, int type)
{
	int ret = 0;
	struct posix_acl *acl = NULL;

	if (!inode_owner_or_capable(dentry->d_inode)) {
		ret = -EPERM;
		goto out;
	}

	if (!IS_POSIXACL(dentry->d_inode)) {
		ret = -EOPNOTSUPP;
		goto out;
	}

	if (value) {
		acl = posix_acl_from_xattr(&init_user_ns, value, size);
		if (IS_ERR(acl)) {
			ret = PTR_ERR(acl);
			goto out;
		}

		if (acl) {
			ret = posix_acl_valid(dentry->d_inode->i_sb->s_user_ns, acl);
			if (ret)
				goto out_release;
		}
	}

	ret = ceph_set_acl(dentry, dentry->d_inode, acl, type);

out_release:
	posix_acl_release(acl);
out:
	return ret;
}

const struct xattr_handler ceph_xattr_acl_default_handler = {
	.prefix = POSIX_ACL_XATTR_DEFAULT,
	.flags  = ACL_TYPE_DEFAULT,
	.get    = ceph_xattr_acl_get,
	.set    = ceph_xattr_acl_set,
};

const struct xattr_handler ceph_xattr_acl_access_handler = {
	.prefix = POSIX_ACL_XATTR_ACCESS,
	.flags  = ACL_TYPE_ACCESS,
	.get    = ceph_xattr_acl_get,
	.set    = ceph_xattr_acl_set,
};
