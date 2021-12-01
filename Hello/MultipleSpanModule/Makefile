obj-m += enter.o
obj-m += exit.o
obj-m += combinedmodule.o

combinedmodule-objs := enter.o exit.o

all:
	make -C  /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
