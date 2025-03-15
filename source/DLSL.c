#include <stdlib.h>
#include <stddef.h>
#include <DLSL.h>

struct DLSLVM dlslCreateVM ()
{
	struct DLSLVM vm;

	vm.code = NULL;
	vm.code_size = 0;

	vm.stack = NULL;
	vm.stack_size = 0;

	return vm;
}

void dlslFreeVM (struct DLSLVM* vm)
{
	free(vm->code);
	free(vm->stack);
}

void dlslVMInit (struct DLSLVM* vm, DLUInt stack_size)
{
	vm->stack_size = stack_size;
	vm->stack = calloc(stack_size, sizeof(int));
}

void dlslVMBindCode (struct DLSLVM* vm, DLUChar* code, DLUInt code_size)
{
	vm->code_size = code_size;
	vm->code = calloc(code_size, sizeof(DLUInt));

	// Copy the source code to VM code
	int index = -1;

	while (++index < code_size)
	{
		vm->code[index] = code[index];
	}
}

void dlslVMRun (struct DLSLVM* vm)
{
	// https://github.com/parrt/simple-virtual-machine-C/blob/master/src/vm.c
	int ip, sp, callsp;

	int a, b, addr, offset;

	a = 0;
	b = 0;
	addr = 0;
	offset = 0;

	ip = -1;
	sp = -1;
	callsp = -1;

	DLUChar running = 1;
	DLUChar opcode;

	while (running)
	{
		opcode = vm->code[++ip];

		switch (opcode)
		{
			case DLSL_OPCODE_JUMP:
				ip = vm->stack[ip + 1];
				ip--;
				break;

			case DLSL_OPCODE_QUIT:
				running = 0;
				break;

			case DLSL_OPCODE_IADD:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				// printf("[%d]\tIADD: Adding %d, %d\n", ip, a, b);
				vm->stack[++sp] = a + b;
				// printf("[%d]\tIADD: Pushing %d\t(%d)\n", ip, a + b, sp);
				break;

			case DLSL_OPCODE_ISUB:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = a - b;
				break;

			case DLSL_OPCODE_IMUL:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = a * b;
				break;

			case DLSL_OPCODE_IDIV:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = a / b;
				break;

			case DLSL_OPCODE_PUSH:
				vm->stack[++sp] = vm->code[++ip];
				// printf("[%d]\tPUSH: Pushing %d\t(%d)\n", ip, vm->code[ip], sp);
				break;

			case DLSL_OPCODE_SCL:
				a = vm->stack[sp];
				vm->stack[++sp] = a;
				// printf("[%d]\tSCL: Pushing %d\t(%d)\n", ip, a, sp);
				break;

			case DLSL_OPCODE_SPN:
				sp++;
				break;

			case DLSL_OPCODE_POP:
				sp--;
				break;

			case DLSL_OPCODE_ILT:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				// printf("[%d]\tILT: Comparing %d, %d\n", ip, a, b);
				vm->stack[++sp] = (a < b);
				// printf("[%d]\tILT: Pushing %d\t(%d)\n", ip, a < b, sp);
				break;

			case DLSL_OPCODE_IGT:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = (a > b);
				break;

			case DLSL_OPCODE_IEQ:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = (a == b);
				break;

			case DLSL_OPCODE_JMPI:
				addr = vm->code[++ip];

				// printf("[%d]\tJMPI: Checking...\n", ip);

				if (vm->stack[sp--] == 1)
				{
					// printf("[%d]\tJMPI: True, moving to %d\t(%d)\n", ip, addr, sp);
					ip = addr - 1;
				}

				break;

			case DLSL_OPCODE_JMPN:
				addr = vm->code[ip++];

				// printf("[%d]\tJMPN: Checking...\n", ip);

				if (vm->stack[sp--] == 0)
				{
					// printf("[%d]\tJMPN: True, moving to %d\t(%d)\n", ip, addr, sp);
					ip = addr - 1;
				}

				break;
		}
	}
}