#include <stdio.h>
#include <DLSL.h>

int main ()
{
	printf("Creating a VM... (64 stack size)\n");
	struct DLSLVM vm = DLSL_createVM(64);

	printf("Creating Code for VM...\n");
	double code[32] =
	{
		DLSL_OPCODE_PUSH, 10,
		DLSL_OPCODE_PUSH, 20,
		DLSL_OPCODE_IADD,
		DLSL_OPCODE_QUIT,
	};

	printf("Loading Code into VM...\n");
	DLSL_vmLoadCode(&vm, &code, sizeof(code) / sizeof(double));

	printf("Freeing VM...\n");
	DLSL_freeVM(&vm);

	printf("Done!\n");
	return 0;
}