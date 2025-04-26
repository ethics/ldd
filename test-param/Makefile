obj-m +=test-param.o

KRN_SOURCE := /lib/modules/`uname -r`/build

all:
	make -C $(KRN_SOURCE) M=$(PWD) modules

clean:
	make -C $(KRN_SOURCE) M=$(PWD) clean
