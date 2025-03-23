#include <DL.h>

#ifndef DLSL_h
#define DLSL_h

enum DLSLOpCode
{
	DLSL_OPCODE_NONE,

	DLSL_OPCODE_JUMP,
	DLSL_OPCODE_QUIT,

	DLSL_OPCODE_PUSH,
	DLSL_OPCODE_POP,

	DLSL_OPCODE_IADD,
	DLSL_OPCODE_ISUB,
	DLSL_OPCODE_IMUL,
	DLSL_OPCODE_IDIV,

	DLSL_OPCODE_ALD,
	DLSL_OPCODE_AST,

	DLSL_OPCODE_BLD,
	DLSL_OPCODE_BST,
};

struct DLSLVM
{
	double* code;
	size_dl code_size;

	double* stack;
	size_dl stack_size;

	struct DLAttrs* attrs;
	struct DLBuffer* buffer;
};

struct DLSLVM DLSL_createVM (size_dl stack_size);
void DLSL_freeVM (struct DLSLVM* vm);

void DLSL_vmLoadCode (struct DLSLVM* vm, double* code, size_dl code_size);
void DLSL_vmRun (struct DLSLVM* vm);

#endif