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
#define DLSL_OPCODE_BUFFERVALUE 22

struct DLSLVM
{
	int*    code;
	DLUInt  code_size;

	int*    global;
	DLUInt  global_size;

	int*    stack;
	DLUInt  stack_size;

	int*    attrs;
	DLUInt  attrs_size;

	int dl_BufferValue;
};

struct DLSLVM dlslCreateVM ();
void dlslFreeVM (struct DLSLVM* vm);

void dlslVMLoad (struct DLSLVM* vm, DLUInt stack_size, DLUInt global_size, DLUInt attrs_size);
void dlslVMLoadCode (struct DLSLVM* vm, int* code, DLUInt code_size);
void dlslVMLoadAttrs (struct DLSLVM* vm, struct DLAttrs* attrs);

void dlslVMRun (struct DLSLVM* vm);

#endif