/*
Code for makng SYstem Calls
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define WR_VALUE  _IOW('a', 'a', int32_t*)
#define RD_VALUE  _IOR('a', 'b', int32_t*)

int main()
{
  int fd;
  int32_t value,  number;

  printf("Opening Driver \n");
  fd=open("/dev/etx_device", O_RDWR);
  printf("Opening  Driver via File   Descriptor %d \n", fd );
  if (fd<0)
  {
    printf("Cannot Open\n");
  }
  printf("Enter Value for Sending \n");
  scanf("%d", &number);
  printf("Writing to Driver\n");
  ioctl(fd, WR_VALUE,  (int32_t*)&number);
  printf("Reading from Driver\n");
  ioctl(fd, RD_VALUE,  (int32_t*)&value);
  printf("Value is %d\n", value);
  printf("Closing Driver\n");
  close(fd);
}
