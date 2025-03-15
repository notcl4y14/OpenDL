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
	free(vm->global);
	free(vm->attrib);
}

void dlslVMInit (struct DLSLVM* vm, DLUInt stack_size, DLUInt global_size, DLUInt attrib_size)
{
	vm->stack_size = stack_size;
	vm->stack = calloc(stack_size, sizeof(int));

	vm->global_size = global_size;
	vm->global = calloc(global_size, sizeof(int));

	vm->attrib_size = attrib_size;
	vm->attrib = calloc(attrib_size, sizeof(int));
}

void dlslVMBindCode (struct DLSLVM* vm, int* code, DLUInt code_size)
{
	vm->code_size = code_size;
	vm->code = calloc(code_size, sizeof(int));

	// Copy the source code to VM code
	int index = -1;

	while (++index < code_size)
	{
		vm->code[index] = code[index];
	}
}

void dlslVMLoadAttribs (struct DLSLVM* vm, struct DLAttrs* attrs)
{
	int index = -1;

	while (++index < attrs->capacity)
	{
		vm->attrib[index] = *(int*)attrs->values[index];
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
	int opcode;

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
				vm->stack[++sp] = a + b;
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
				break;

			case DLSL_OPCODE_SCL:
				a = vm->stack[sp];
				vm->stack[++sp] = a;
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
				vm->stack[++sp] = (a < b);
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

				if (vm->stack[sp--] == 1)
				{
					ip = addr - 1;
				}

				break;

			case DLSL_OPCODE_JMPN:
				addr = vm->code[ip++];

				if (vm->stack[sp--] == 0)
				{
					ip = addr - 1;
				}

				break;

			case DLSL_OPCODE_GST:
				addr = vm->code[++ip];
				vm->global[addr] = vm->stack[sp--];
				break;

			case DLSL_OPCODE_GLD:
				addr = vm->code[++ip];
				vm->stack[++sp] = vm->global[addr];
				break;

			case DLSL_OPCODE_ALD:
				addr = vm->code[++ip];
				vm->stack[++sp] = vm->attrib[addr];
				break;
		}
	}
}