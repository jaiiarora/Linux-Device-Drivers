#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/ioctl.h>

#define MAJOR_NUM 100

//TO SEND INFO FROM PROCESS TO KERNEL
#define IOCTL_SET_MSG _IOW(MAJOR_NUM, 0, char*)


//TO SEND INFO FROM KERNEL TO PROCESS
#define IOCTL_GET_MSG _IOR(MAJOR_NUM, 1, char*)


//Used for both input/output. Receives a mu,ber from user and returns message[n]
#define IOCTL_GET_NTH_BYTE _IORW(MAJOR_NUM, 2, int)

#define DEVICE_FILE_NAME "char_dev"
#define DEVICE_PATH "/dev/char_dev"

#endif
