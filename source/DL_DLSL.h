#include <DL_defines.h>
#include <DL_core.h>

#ifndef DL_DLSL_H
#define DL_DLSL_H

#define DLSL_NONE 0x00
#define DLSL_JUMP 0x01
#define DLSL_QUIT 0x02
#define DLSL_PUSH 0x03
#define DLSL_POP  0x04
#define DLSL_IADD 0x05
#define DLSL_ISUB 0x06
#define DLSL_IMUL 0x07
#define DLSL_IDIV 0x08

struct DLSLRunner;

typedef struct DLSLRunner DLSLRunner;

struct DLSLRunner
{
	DLCode* code;
	DLAttribMap* attrmap;

	DLdouble* stack;
	DLuint stack_size;

	DLuint ip;
	DLuint sp;
};

void DLSLRunner_init (DLSLRunner* runner);
void DLSLRunner_free (DLSLRunner* runner);

void DLSLRunner_initStack (DLSLRunner* runner, DLuint stack_size);
void DLSLRunner_bindCode (DLSLRunner* runner, DLCode* code);
void DLSLRunner_bindAttrMap (DLSLRunner* runner, DLAttribMap* attrmap);

void DLSLRunner_run (DLSLRunner* runner);

#endif