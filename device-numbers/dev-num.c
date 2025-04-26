#include<stdio.h>

int main(){
	unsigned int major = 8;
	unsigned int minor = 2;
	unsigned int dev_t;

	dev_t = (major << 20) | minor;

	printf("Major number: %u\n", major);
	printf("Minor number: %u\n", minor);
	printf("Device number (dev_t): %u\n", dev_t);

	printf("Device number in hex: 0x%X\n", dev_t);

	return 0;
}
