/* FS-Cache netfs (client) registration
 *
 * Copyright (C) 2008 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version
 * 2 of the Licence, or (at your option) any later version.
 */

#define FSCACHE_DEBUG_LEVEL COOKIE
#include <linux/module.h>
#include <linux/slab.h>
#include "internal.h"

static LIST_HEAD(fscache_netfs_list);

/*
 * register a network filesystem for caching
 */
int __fscache_register_netfs(struct fscache_netfs *netfs)
{
	struct fscache_netfs *ptr;
	struct fscache_cookie *cookie;
	int ret;

	_enter("{%s}", netfs->name);

	INIT_LIST_HEAD(&netfs->link);

	/* allocate a cookie for the primary index */
	cookie = fscache_alloc_cookie(&fscache_fsdef_index,
				      &fscache_fsdef_netfs_def,
				      netfs);
	if (!cookie) {
		_leave(" = -ENOMEM");
		return -ENOMEM;
	}

	cookie->flags = 1 << FSCACHE_COOKIE_ENABLED;

	/* check the netfs type is not already present */
	down_write(&fscache_addremove_sem);

	ret = -EEXIST;
	list_for_each_entry(ptr, &fscache_netfs_list, link) {
		if (strcmp(ptr->name, netfs->name) == 0)
			goto already_registered;
	}

	atomic_inc(&cookie->parent->usage);
	atomic_inc(&cookie->parent->n_children);

	netfs->primary_index = cookie;
	list_add(&netfs->link, &fscache_netfs_list);
	ret = 0;

	pr_notice("Netfs '%s' registered for caching\n", netfs->name);

already_registered:
	up_write(&fscache_addremove_sem);

	if (ret < 0)
		kmem_cache_free(fscache_cookie_jar, cookie);

	_leave(" = %d", ret);
	return ret;
}
EXPORT_SYMBOL(__fscache_register_netfs);

/*
 * unregister a network filesystem from the cache
 * - all cookies must have been released first
 */
void __fscache_unregister_netfs(struct fscache_netfs *netfs)
{
	_enter("{%s.%u}", netfs->name, netfs->version);

	down_write(&fscache_addremove_sem);

	list_del(&netfs->link);
	fscache_relinquish_cookie(netfs->primary_index, 0);

	up_write(&fscache_addremove_sem);

	pr_notice("Netfs '%s' unregistered from caching\n",
		  netfs->name);

	_leave("");
}
EXPORT_SYMBOL(__fscache_unregister_netfs);
