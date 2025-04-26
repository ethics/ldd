#include<stdio.h>

int main() {
	unsigned int major = 8;
	unsigned int minor = 1;
	unsigned int dev_t;

	dev_t = (major << 20) | minor;

	printf("Original Major: %u\n", major);
	printf("Original Minor: %u\n", minor);
	printf("Packed dev_t: %u (0x%X)\n\n", dev_t, dev_t);

	unsigned int extracted_major = dev_t >> 20;
	unsigned int extracted_minor = dev_t & 0xFFFFF;

	printf("Extracted Major: %u\n", extracted_major);
	printf("Extracted Minor: %u\n", extracted_minor);

	return 0;
}
