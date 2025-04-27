make       # (use simple Makefile)
insmod mychar.ko
dmesg      # (check major number printed)
mknod /dev/mychar c <major> 0

echo "Hello Kernel" > /dev/mychar
cat /dev/mychar

rmmod mychar
