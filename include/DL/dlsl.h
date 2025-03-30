#include <DL/dldefines.h>
#include <DL/dlcore.h>

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
#define DLSL_ALD  0x09
#define DLSL_AST  0x0A

#define DLSL_TOKEN_NONE   0x0
#define DLSL_TOKEN_NUMBER 0x1
#define DLSL_TOKEN_IDENT  0x2
#define DLSL_TOKEN_SYMBOL 0x3

#define DLSL_COMP_ERR_NONE 0x00

/* Struct Declarations
 */
struct DLSLRunner;
struct DLSLCompiler;
struct DLSLToken;

/* Typedef Struct Declarations
 */
typedef struct DLSLRunner DLSLRunner;
typedef struct DLSLCompiler DLSLCompiler;
typedef struct DLSLToken DLSLToken;

/* Struct Definitions
 */
struct DLSLRunner
{
	DLCode* code;
	DLAttrMap* attrmap;

	DLdouble* stack;
	DLuint stack_size;

	DLuint ip;
	DLuint sp;
};

struct DLSLCompiler
{
	DLchar_p code;
	DLuint code_size;

	DLuint* tokens;
	DLuint tokens_size;

	DLuint location;

	DLCode result;
	DLuint error;
};

struct DLSLToken
{
	DLuint type;
	DLchar value[24];
};

/* DLSLRunner
 */

void DLSLRunner_init (DLSLRunner* runner);
void DLSLRunner_free (DLSLRunner* runner);

void DLSLRunner_initStack (DLSLRunner* runner, DLuint stack_size);
void DLSLRunner_bindCode (DLSLRunner* runner, DLCode* code);
void DLSLRunner_bindAttrMap (DLSLRunner* runner, DLAttrMap* attrmap);

void DLSLRunner_run (DLSLRunner* runner);

/* DLSLCompiler
 */

void DLSLCompiler_init (DLSLCompiler* compiler);
void DLSLCompiler_free (DLSLCompiler* compiler);

void DLSLCompiler_loadCode (DLSLCompiler* compiler, DLchar_p code, DLuint size);
void DLSLCompiler_compile (DLSLCompiler* compiler);

void DLSLCompiler_lexer (DLSLCompiler* compiler);
void DLSLCompiler_lexer_number (DLSLCompiler* compiler);
void DLSLCompiler_lexer_ident (DLSLCompiler* compiler);
void DLSLCompiler_lexer_symbol (DLSLCompiler* compiler);

#endif