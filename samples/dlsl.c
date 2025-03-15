#include <stdio.h>
#include <DLSL.h>

void render_stack (struct DLSLVM* vm, DLUInt split);

int main ()
{
	struct DLSLVM vm = dlslCreateVM();
	dlslVMInit(&vm, 32);

	DLUChar code[255] =
	{
		// DLSL_OPCODE_PUSH, 10,
		// DLSL_OPCODE_PUSH, 5,

		// DLSL_OPCODE_IADD,

		// DLSL_OPCODE_PUSH, 3,
		// DLSL_OPCODE_IDIV,

		// DLSL_OPCODE_PUSH, 2,
		// DLSL_OPCODE_IMUL,

		DLSL_OPCODE_PUSH, 0,

		DLSL_OPCODE_PUSH, 1,
		DLSL_OPCODE_IADD,

		DLSL_OPCODE_SCL,
		DLSL_OPCODE_PUSH, 10,

		DLSL_OPCODE_ILT,
		DLSL_OPCODE_JMPI, 2,

		DLSL_OPCODE_QUIT,
	};

	dlslVMBindCode(&vm, code, sizeof(code));

	dlslVMRun(&vm);

	printf("STACK\n");
	render_stack(&vm, 2);

	return 0;
}

void render_stack (struct DLSLVM* vm, DLUInt split)
{
	for (int i = 0; i < vm->stack_size; i++)
	{
		if (i > 0 && i % split == 0)
		{
			printf("\n");
		}

		printf("%.2d. %d;\t", i, vm->stack[i]);
	}
}