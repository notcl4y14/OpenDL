#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <DLSL.h>

struct DLSLVM dlslCreateVM ()
{
	struct DLSLVM vm;

	vm.code = NULL;
	vm.code_size = 0;

	vm.stack = NULL;
	vm.stack_unit_size = 0;
	vm.stack_size = 0;

	vm.global = NULL;
	vm.global_unit_size = 0;
	vm.global_size = 0;

	vm.attrs = NULL;
	vm.attrs_unit_size = 0;
	vm.attrs_size = 0;

	return vm;
}

void dlslFreeVM (struct DLSLVM* vm)
{
	free(vm->code);
	free(vm->stack);
	free(vm->global);
	free(vm->attrs);
	free(vm->dl_BufferValue);
}

void dlslVMLoad (struct DLSLVM* vm)
{
	vm->stack = calloc(vm->stack_size, vm->stack_unit_size);
	vm->global = calloc(vm->global_size, vm->global_unit_size);
	vm->attrs = calloc(vm->attrs_size, vm->attrs_unit_size);
	vm->dl_BufferValue = calloc(vm->dl_BufferValue_size, vm->dl_BufferValue_unit_size);
}

void dlslVMLoadCode (struct DLSLVM* vm, int* code, DLUInt code_size)
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

void dlslVMLoadAttrs (struct DLSLVM* vm, struct DLAttrs* attrs)
{
	int index = -1;

	while (++index < attrs->capacity)
	{
		void* attrib_location = vm->attrs + (index * vm->attrs_unit_size);
		memcpy(attrib_location, attrs->values[index], vm->attrs_unit_size);
	}
}

void dlslVMStackGet (struct DLSLVM* vm, void* dest, int delta)
{
	memcpy(
		dest,
		vm->stack + (vm->stack_pointer + delta) * vm->stack_unit_size,
		vm->stack_unit_size
	);
}

void dlslVMStackPush (struct DLSLVM* vm, void* value)
{
	memcpy(
		vm->stack + vm->stack_pointer * vm->stack_unit_size,
		value,
		vm->stack_unit_size
	);
	vm->stack_pointer++;
}

void dlslVMStackPop (struct DLSLVM* vm, void* dest)
{
	vm->stack_pointer--;
	dlslVMStackGet(vm, dest, 0);
}

void dlslVMGlobalGet (struct DLSLVM* vm, void* dest, int location)
{
	memcpy(
		dest,
		vm->global + location * vm->global_unit_size,
		vm->global_unit_size
	);
}

void dlslVMGlobalSet (struct DLSLVM* vm, void* value, int location)
{
	memcpy(
		vm->global + location * vm->global_unit_size,
		value,
		vm->global_unit_size
	);
}

void dlslVMAttrsGet (struct DLSLVM* vm, void* dest, int location)
{
	memcpy(
		dest,
		vm->attrs + location * vm->attrs_unit_size,
		vm->attrs_unit_size
	);
}

void dlslVMAttrsSet (struct DLSLVM* vm, void* value, int location)
{
	memcpy(
		vm->attrs + location * vm->attrs_unit_size,
		value,
		vm->attrs_unit_size
	);
}

void dlslVMBufferValueGet (struct DLSLVM* vm, void* dest, int index)
{
	memcpy(
		dest,
		vm->dl_BufferValue + index * vm->dl_BufferValue_unit_size,
		vm->dl_BufferValue_unit_size
	);
}

void dlslVMBufferValueSet (struct DLSLVM* vm, void* value, int index)
{
	memcpy(
		vm->dl_BufferValue + index * vm->dl_BufferValue_unit_size,
		value,
		vm->dl_BufferValue_unit_size
	);
}

void dlslVMRun (struct DLSLVM* vm)
{
	// https://github.com/parrt/simple-virtual-machine-C/blob/master/src/vm.c
	vm->stack_pointer = -1;
	int ip, sp, callsp;

	double a, b;
	int addr, offset;

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
				dlslVMStackPop(vm, &ip);
				ip--;
				break;

			case DLSL_OPCODE_QUIT:
				running = 0;
				break;

			case DLSL_OPCODE_IADD:
				dlslVMStackPop(vm, &b);
				dlslVMStackPop(vm, &a);

				a = a + b;
				dlslVMStackPush(vm, &a);
				break;

			case DLSL_OPCODE_ISUB:
				dlslVMStackPop(vm, &b);
				dlslVMStackPop(vm, &a);
				
				a = a - b;
				dlslVMStackPush(vm, &a);
				break;

			case DLSL_OPCODE_IMUL:
				dlslVMStackPop(vm, &b);
				dlslVMStackPop(vm, &a);
				
				a = a * b;
				dlslVMStackPush(vm, &a);
				break;

			case DLSL_OPCODE_IDIV:
				dlslVMStackPop(vm, &b);
				dlslVMStackPop(vm, &a);
				
				a = a / b;
				dlslVMStackPush(vm, &a);
				break;

			case DLSL_OPCODE_PUSH:
				dlslVMStackPush(vm, &vm->code[++ip]);
				break;

			case DLSL_OPCODE_SCL:
				dlslVMStackGet(vm, &a, 0);
				dlslVMStackPush(vm, &a);
				break;

			case DLSL_OPCODE_SPN:
				vm->stack_pointer++;
				break;

			case DLSL_OPCODE_POP:
				vm->stack_pointer--;
				break;

			case DLSL_OPCODE_ILT:
				dlslVMStackPop(vm, &b);
				dlslVMStackPop(vm, &a);

				a = a < b;
				dlslVMStackPush(vm, &a);
				break;

			case DLSL_OPCODE_IGT:
				dlslVMStackPop(vm, &b);
				dlslVMStackPop(vm, &a);

				a = a > b;
				dlslVMStackPush(vm, &a);
				break;

			case DLSL_OPCODE_IEQ:
				dlslVMStackPop(vm, &b);
				dlslVMStackPop(vm, &a);

				a = a == b;
				dlslVMStackPush(vm, &a);
				break;

			case DLSL_OPCODE_JMPI:
				addr = vm->code[++ip];
				dlslVMStackPop(vm, &a);

				if (a == 1)
				{
					ip = addr - 1;
				}

				break;

			case DLSL_OPCODE_JMPN:
				addr = vm->code[ip++];
				dlslVMStackPop(vm, &a);

				if (a == 0)
				{
					ip = addr - 1;
				}

				break;

			case DLSL_OPCODE_GST:
				addr = vm->code[++ip];
				dlslVMStackPop(vm, &a);
				dlslVMGlobalSet(vm, &a, addr);
				break;

			case DLSL_OPCODE_GLD:
				addr = vm->code[++ip];
				dlslVMGlobalGet(vm, &a, addr);
				dlslVMStackPush(vm, &a);
				break;

			case DLSL_OPCODE_ALD:
				addr = vm->code[++ip];
				dlslVMAttrsGet(vm, &a, addr);
				dlslVMStackPush(vm, &a);
				break;

			case DLSL_OPCODE_AST:
				addr = vm->code[++ip];
				dlslVMStackPop(vm, &a);
				dlslVMAttrsSet(vm, &a, addr);
				break;

			case DLSL_OPCODE_BUFFERVALUE_SET:
				addr = vm->code[++ip];
				dlslVMStackPop(vm, &a);
				dlslVMBufferValueSet(vm, &a, addr);
				break;

			case DLSL_OPCODE_BUFFERVALUE_GET:
				addr = vm->code[++ip];
				dlslVMBufferValueSet(vm, &a, addr);
				dlslVMStackPush(vm, &a);
				break;
		}
	}
}