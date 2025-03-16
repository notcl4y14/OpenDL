#include <DL.h>

#ifndef DLSL_H
#define DLSL_H

#define DLSL_OPCODE_NONE 0

#define DLSL_OPCODE_JUMP 1
#define DLSL_OPCODE_CALL 2
#define DLSL_OPCODE_RET  3
#define DLSL_OPCODE_QUIT 4

#define DLSL_OPCODE_IADD 5
#define DLSL_OPCODE_ISUB 6
#define DLSL_OPCODE_IMUL 7
#define DLSL_OPCODE_IDIV 8

#define DLSL_OPCODE_PUSH 9
#define DLSL_OPCODE_SCL  10
#define DLSL_OPCODE_SPN  11
#define DLSL_OPCODE_POP  12

#define DLSL_OPCODE_ILT  13
#define DLSL_OPCODE_IGT  14
#define DLSL_OPCODE_IEQ  15
#define DLSL_OPCODE_JMPI 16
#define DLSL_OPCODE_JMPN 17

#define DLSL_OPCODE_GST  18
#define DLSL_OPCODE_GLD  19

#define DLSL_OPCODE_ALD  20
#define DLSL_OPCODE_AST  21
#define DLSL_OPCODE_BUFFERVALUE_SET 22
#define DLSL_OPCODE_BUFFERVALUE_GET 23

struct DLSLVM
{
	int*    code;
	DLUInt  code_size;

	void*   global;
	DLUInt  global_unit_size;
	DLUInt  global_size;

	void*   stack;
	DLUInt  stack_unit_size;
	DLUInt  stack_size;
	DLUInt  stack_pointer;

	void*   attrs;
	DLUInt  attrs_unit_size;
	DLUInt  attrs_size;

	void* dl_BufferValue;
	DLUInt dl_BufferValue_unit_size;
	DLUInt dl_BufferValue_size;
};

struct DLSLVM dlslCreateVM ();
void dlslFreeVM (struct DLSLVM* vm);

void dlslVMLoad (struct DLSLVM* vm);
void dlslVMLoadCode (struct DLSLVM* vm, int* code, DLUInt code_size);
void dlslVMLoadAttrs (struct DLSLVM* vm, struct DLAttrs* attrs);

void dlslVMStackGet (struct DLSLVM* vm, void* dest, int delta);
void dlslVMStackPush (struct DLSLVM* vm, void* value);
void dlslVMStackPop (struct DLSLVM* vm, void* dest);

void dlslVMGlobalGet (struct DLSLVM* vm, void* dest, int location);
void dlslVMGlobalSet (struct DLSLVM* vm, void* value, int location);

void dlslVMAttrsGet (struct DLSLVM* vm, void* dest, int location);
void dlslVMAttrsSet (struct DLSLVM* vm, void* value, int location);

void dlslVMBufferValueGet (struct DLSLVM* vm, void* dest, int index);
void dlslVMBufferValueSet (struct DLSLVM* vm, void* value, int index);

void dlslVMRun (struct DLSLVM* vm);

#endif