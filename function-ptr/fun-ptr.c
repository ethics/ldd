#include<stdio.h>

void hello() {
	printf("Hello from function!\n");
}

int main() {
	void (*func_ptr)(); // Declare a function pointer  return_type(pointer name)(parameters passed)
	func_ptr = hello; // Assign function to pointer
	func_ptr();
	return 0;
}
