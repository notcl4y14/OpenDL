#include <stdlib.h>
#include <string.h>

#include <DLSL.h>

// 
// 

void memcpy_diff (void* to, void* from, DLuint to_size, DLuint from_size)
{
	DLuint copy_size = to_size;

	if (from_size < copy_size)
	{
		copy_size = from_size;
	}

	memset(to, 0, to_size);
	memcpy(to, from, copy_size);
}

// 
// 

struct DLSLVM DLSL_createVM (DLuint stack_size)
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

void DLSL_vmLoadCode (struct DLSLVM* vm, double* code, DLuint code_size)
{
	vm->code = malloc(code_size * sizeof(double));
	memcpy(vm->code, code, code_size * sizeof(double));

	vm->code_size = code_size;
}

void DLSL_vmRun (struct DLSLVM* vm)
{
	DLint ip, sp, addr;
	DLdouble a, b;

	// This is for copying almost "undefined" data types
	DLint v_int;
	DLdouble v_double;

	ip = -1;
	sp = -1;
	addr = 0;
	a = 0;
	b = 0;

	DLbool running;
	DLSLopcode opcode;

	running = 1;
	opcode = 0;

	while (running)
	{
		opcode = vm->code[++ip];
		printf("opcode: %d\n", opcode);

		switch (opcode)
		{
			case DLSL_JUMP:
				ip = vm->code[ip + 1];
				ip--;
				break;

			case DLSL_QUIT:
				running = 0;
				break;

			case DLSL_PUSH:
				vm->stack[++sp] = vm->code[++ip];
				break;

			case DLSL_POP:
				sp--;
				break;

			case DLSL_IADD:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = a + b;
				break;

			case DLSL_ISUB:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = a - b;
				break;

			case DLSL_IMUL:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = a * b;
				break;

			case DLSL_IDIV:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = a / b;
				break;

			case DLSL_ALD:
				addr = vm->code[++ip];

				switch (vm->attrs->v_types[addr])
				{
					case DL_BYTE:
					case DL_UBYTE:
					case DL_SHORT:
					case DL_USHORT:
					case DL_INT:
					case DL_UINT:
						v_int = 0;
						DL_getAttribValue(vm->attrs, addr, &v_int);
						vm->stack[++sp] = (double)v_int;
						break;

					case DL_FLOAT:
					case DL_DOUBLE:
						v_double = 0;
						DL_getAttribValue(vm->attrs, addr, &v_double);
						vm->stack[++sp] = v_double;
						break;
				}
				break;

			case DLSL_AST:
				addr = vm->code[++ip];

				switch (vm->attrs->v_types[addr])
				{
					case DL_BYTE:
					case DL_UBYTE:
					case DL_SHORT:
					case DL_USHORT:
					case DL_INT:
					case DL_UINT:
						v_int = (int)vm->stack[sp--];
						printf("v_int: %d\n", v_int);
						memcpy(vm->attrs->v_values[addr], &v_int, vm->attrs->v_sizes[addr]);
						break;

					case DL_FLOAT:
					case DL_DOUBLE:
						v_double = vm->stack[sp--];
						memcpy(vm->attrs->v_values[addr], &v_double, vm->attrs->v_sizes[addr]);
						break;
				}
				break;

			// I hope these next two OpCodes will work since
			// I didn't test whether they work correctly
			case DLSL_BLD:
				addr = vm->code[++ip];

				switch (vm->buffer->type)
				{
					case DL_BYTE:
					case DL_UBYTE:
					case DL_SHORT:
					case DL_USHORT:
					case DL_INT:
					case DL_UINT:
						v_int = 0;
						DL_bufferGetValue(vm->buffer, addr, &v_int);
						vm->stack[++sp] = v_int;
						break;

					case DL_FLOAT:
					case DL_DOUBLE:
						v_double = 0;
						DL_bufferGetValue(vm->buffer, addr, &v_double);
						vm->stack[++sp] = v_double;
						break;
				}
				break;

			case DLSL_BST:
				addr = vm->code[++ip];

				switch (vm->buffer->type)
				{
					case DL_BYTE:
					case DL_UBYTE:
					case DL_SHORT:
					case DL_USHORT:
					case DL_INT:
					case DL_UINT:
						v_int = vm->stack[sp--];
						memcpy((char*)(vm->buffer->data) + (addr * DLarray_types[vm->buffer->type]), &v_int, DLarray_types[vm->buffer->type]);
						break;

					case DL_FLOAT:
					case DL_DOUBLE:
						v_double = vm->stack[sp--];
						memcpy((char*)(vm->buffer->data) + (addr * DLarray_types[vm->buffer->type]), &v_double, DLarray_types[vm->buffer->type]);
						break;
				}
				break;
		}
	}
}