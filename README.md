# What is this for?

Each version of BeeGFS works with a limited set of sometimes patched Linux kernels from multiple vendors.  For developers of BeeGFS it is convenient to have these versions available in one repository.  This is that repository.  

To use it note the following:
- git checkout the tag that you wish to work with
- in that tagged version, the correct kernel .config file is already present, you can make it to build the kernel
- in your IDE changes between the different tags can easily be seen and assist in keeping the BeeGFS kernel module compatible with the supported kernels.

**TODO**
- make it clear how to indicate in the tag which BeeGFS branch a certain tag should support
- make sure not too many old tags stick around

# To Maintain this Repository

When new kernels are supported, the sources need to be added and tagged.  Below are the instructions how to do this for various sources of Linux kernels.

## Kernel.org

```
 wget https://cdn.kernel.org/pub/linux/kernel/vx.x/
 tar -xvf <linux-x.x.x>
 diff linux-x.x.x/ linux-source-code/ | grep Only
 rsync -Pva --delete linux-x.x.x/ linux-source-code/
 diff linux-x.x.x/ linux-source-code/ | grep Only
```

## RHEL
(e.g., rhel8.3)

```
 wget https://vault.centos.org/8.3.2011/centosplus/Source/SPackages/kernel-plus-4.18.0-240.1.1.el8_3.centos.plus.src.rpm
 rpm2cpio kernel-plus-4.18.0-240.1.1.el8_3.centos.plus.src.rpm | cpio -i --make-directories
 tar -xvf linux-4.18.0-240.1.1.el8_3.tar.xz
 rsync -Pva --delete linux-4.18.0-240.1.1.el8_3/ linux-source-code/

```

## SUSE

## Ubuntu



## Debian

See Ubuntu
