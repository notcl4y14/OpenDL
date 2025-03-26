#include <DL.h>

#ifndef DLSL_h
#define DLSL_h

// DLSLopcode
#define DLSL_NONE 0x00
#define DLSL_JUMP 0x01
#define DLSL_QUIT 0x02
#define DLSL_PUSH 0x03
#define DLSL_POP  0x04
#define DLSL_IADD 0x05
#define DLSL_ISUB 0x06
#define DLSL_IMUL 0x07
#define DLSL_IDIV 0x08
#define DLSL_ALD  0x09
#define DLSL_AST  0x0A
#define DLSL_BLD  0x0B
#define DLSL_BST  0x0C

typedef unsigned char DLSLopcode;

struct DLSLVM
{
	double* code;
	DLuint code_size;

	DLuint* stack;
	DLuint stack_size;

	struct DLAttrs* attrs;
	struct DLBuffer* buffer;
};

struct DLSLVM DLSL_createVM (DLuint stack_size);
void DLSL_freeVM (struct DLSLVM* vm);

void DLSL_vmLoadCode (struct DLSLVM* vm, double* code, DLuint code_size);
void DLSL_vmRun (struct DLSLVM* vm);

#endif