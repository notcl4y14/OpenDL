#include <DL.h>

#ifndef DLSL_h
#define DLSL_h

enum DLSLOpCode
{
	DLSL_OPCODE_NONE,

	DLSL_OPCODE_JUMP,
	DLSL_OPCODE_CALL,
	DLSL_OPCODE_RET,
	DLSL_OPCODE_QUIT,

	DLSL_OPCODE_USIZ,

	DLSL_OPCODE_PUSH,
	DLSL_OPCODE_POP,

	DLSL_OPCODE_GLD,
	DLSL_OPCODE_GST,

	DLSL_OPCODE_IADD,
	DLSL_OPCODE_ISUB,
	DLSL_OPCODE_IMUL,
	DLSL_OPCODE_IDIV,
};

struct DLSLRunner
{
	double* code;
	DLuint  code_size;

	double* stack;
	DLuint  stack_size;

	double* globals;
	DLuint  globals_size;
};

void DLSLRunner_loadCode (struct DLSLRunner* runner, double* code, DLuint code_size);
void DLSLRunner_run (struct DLSLRunner* runner);

#endif