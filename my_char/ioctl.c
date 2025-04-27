#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define MY_IOCTL_MAGIC 'x'
#define IOCTL_RESET _IO(MY_IOCTL_MAGIC, 0)
#define IOCTL_GET_STATUS _IOR(MY_IOCTL_MAGIC, 1, int)
#define IOCTL_SET_STATUS _IOW(MY_IOCTL_MAGIC, 2, int)

int main()
{
    int fd = open("/dev/mychar", O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    int status;
    
    ioctl(fd, IOCTL_RESET);
    
    status = 5;
    ioctl(fd, IOCTL_SET_STATUS, &status);
    
    status = 0;
    ioctl(fd, IOCTL_GET_STATUS, &status);
    printf("Device Status: %d\n", status);

    close(fd);
    return 0;
}

