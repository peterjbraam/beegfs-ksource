## BeeGFS kernel source repo

```
 wget https://cdn.kernel.org/pub/linux/kernel/vx.x/
 tar -xvf <linux-x.x.x>
 diff linux-x.x.x/ linux-source-code/ | grep Only
 rsync -Pva --delete linux-x.x.x/ linux-source-code/
 diff linux-x.x.x/ linux-source-code/ | grep Only
```
