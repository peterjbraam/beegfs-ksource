## BeeGFS kernel source repo

```
 wget https://cdn.kernel.org/pub/linux/kernel/vx.x/
 tar -xvf <linux-x.x.x>
 diff linux-x.x.x/ linux-source-code/ | grep Only
 rsync -Pva --delete linux-x.x.x/ linux-source-code/
 diff linux-x.x.x/ linux-source-code/ | grep Only
```

### For RHEL
(e.g., rhel8.3)

```
 wget https://vault.centos.org/8.3.2011/centosplus/Source/SPackages/kernel-plus-4.18.0-240.1.1.el8_3.centos.plus.src.rpm
 rpm2cpio kernel-plus-4.18.0-240.1.1.el8_3.centos.plus.src.rpm | cpio -i --make-directories
 tar -xvf linux-4.18.0-240.1.1.el8_3.tar.xz
 rsync -Pva --delete linux-4.18.0-240.1.1.el8_3/ linux-source-code/

```
