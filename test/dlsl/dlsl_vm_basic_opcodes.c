#include <stdio.h>
#include <stdlib.h>
#include <DLSL.h>

void print_code (double* code, size_dl code_size)
{
	loc_dl location = -1;

	double a = 0;
	char opcode = 0;

	while (++location < code_size)
	{
		opcode = code[location];

		switch (opcode)
		{
			case DLSL_OPCODE_JUMP:
				a = code[++location];
				printf("jump\t%f\n", a);
				break;

			case DLSL_OPCODE_QUIT:
				printf("quit\n");
				break;

			case DLSL_OPCODE_PUSH:
				a = code[++location];
				printf("push\t%f\n", a);
				break;
				
			case DLSL_OPCODE_POP:
				printf("pop\n");
				break;
				
			case DLSL_OPCODE_IADD:
				printf("iadd\n");
				break;
				
			case DLSL_OPCODE_ISUB:
				printf("isub\n");
				break;
				
			case DLSL_OPCODE_IMUL:
				printf("imul\n");
				break;
				
			case DLSL_OPCODE_IDIV:
				printf("idiv\n");
				break;
		}
	}
}

int main ()
{
	printf("Creating DLSL VM...\n\n");
	struct DLSLVM* vm = malloc(sizeof(struct DLSLVM));
	*vm = DLSL_createVM(4);

	printf("Creating Code for VM...\n\n");
	double code[32] =
	{
		DLSL_OPCODE_PUSH, 10,
		DLSL_OPCODE_PUSH, 20,
		DLSL_OPCODE_IADD,     // 10 + 20 = 30

		DLSL_OPCODE_PUSH, 2,
		DLSL_OPCODE_IDIV,     // 30 / 2 = 15

		DLSL_OPCODE_PUSH, 10,
		DLSL_OPCODE_ISUB,     // 15 - 10 = 5

		DLSL_OPCODE_PUSH, 5,
		DLSL_OPCODE_IMUL,     // 5 * 5 = 25

		DLSL_OPCODE_JUMP, 18,

		// This should be skipped by the previous JUMP
		DLSL_OPCODE_PUSH, 1024,

		DLSL_OPCODE_QUIT,
	};
	size_dl code_size = sizeof(code) / sizeof(double);

	printf("CODE:\n");
	print_code(&code, code_size);
	printf("\n");

	printf("Loading the code into VM...\n");
	DLSL_vmLoadCode(vm, &code, code_size);

	printf("Starting VM...\n\n");
	DLSL_vmRun(vm);

	printf("STACK: [%f, %f, %f, %f]\n\n",
	       vm->stack[0],
	       vm->stack[1],
	       vm->stack[2],
	       vm->stack[3]);

	printf("Done!\n");
	return 0;
}