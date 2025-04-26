#include<stdio.h>

struct badminton {
	void(*fund)();
	void(*mem)();
};

void exfund() {
	printf("Hello from exfund\n");
}

void prfund() {
	printf("Hello from prefund\n");
}


int main()
{
	/*struct badminton s1;
	s1.fund = exfund;
	s1.fund();
        return 0;*/

	struct badminton s1 = {    //Object is created and assigned function pointer with = equal and no semicoln
		.fund = exfund,    // no semicolon
		.mem = prfund      // no semicolon
	};

	s1.fund();
	s1.mem();

	struct badminton s2 = {
		.fund = prfund       //same function can be assinged to different function pointers
	};

	s2.fund();
	return 0;

}
