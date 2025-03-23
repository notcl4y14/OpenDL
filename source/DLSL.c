#include <stdlib.h>
#include <string.h>

#include <DLSL.h>

// 
// 

struct DLSLVM DLSL_createVM (size_dl stack_size)
{
	struct DLSLVM vm;

	vm.code = NULL;
	vm.code_size = 0;

	vm.stack = calloc(stack_size, sizeof(double));
	vm.stack_size = stack_size;

	return vm;
}

void DLSL_freeVM (struct DLSLVM* vm)
{
	if (vm->code)
	{
		free(vm->code);
	}

	free(vm->stack);
}

// 

void DLSL_vmLoadCode (struct DLSLVM* vm, double* code, size_dl code_size)
{
	vm->code = malloc(code_size * sizeof(double));
	memcpy(vm->code, code, code_size * sizeof(double));

	vm->code_size = code_size;
}

void DLSL_vmRun (struct DLSLVM* vm)
{
	int ip, sp, addr;
	double a, b;

	ip = -1;
	sp = -1;
	addr = 0;
	a = 0;
	b = 0;

	char running, opcode;

	running = 1;
	opcode = 0;

	while (running)
	{
		opcode = vm->code[++ip];

		switch (opcode)
		{
			case DLSL_OPCODE_JUMP:
				ip = vm->code[ip + 1];
				ip--;
				break;

			case DLSL_OPCODE_QUIT:
				running = 0;
				break;

			case DLSL_OPCODE_PUSH:
				vm->stack[++sp] = vm->code[++ip];
				break;

			case DLSL_OPCODE_POP:
				sp--;
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

			case DLSL_OPCODE_ALD:
				addr = vm->code[++ip];
				sp++;
				// TODO: Change `8` to the size of attribute pointer value.
				memcpy(&vm->stack[sp], vm->attrs->data[addr], 8);
				break;

			case DLSL_OPCODE_AST:
				addr = vm->code[++ip];
				memcpy(vm->attrs->data[addr], &vm->stack[sp], 8);
				sp--;
				break;

			case DLSL_OPCODE_BLD:
				addr = vm->code[++ip];
				sp++;
				memset(&vm->stack[sp], 0, 8);
				// TODO: Change `vm->buffer->usize` to the lowest size: vm->buffer->usize or sizeof(double).
				memcpy(
					&vm->stack[sp],
					(char*)(vm->buffer->data) + (addr * vm->buffer->usize),
					vm->buffer->usize);
				break;

			case DLSL_OPCODE_BST:
				addr = vm->code[++ip];
				memcpy(
					(char*)(vm->buffer->data) + (addr * vm->buffer->usize),
					&vm->stack[sp],
					vm->buffer->usize);
				sp--;
				break;
		}
	}
}