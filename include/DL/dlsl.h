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
struct dlslRunner;
struct dlslCompiler;
struct dlslToken;

/* Typedef Struct Declarations
 */
typedef struct dlslRunner dlslRunner;
typedef struct dlslCompiler dlslCompiler;
typedef struct dlslToken dlslToken;

/* Struct Definitions
 */
struct dlslRunner
{
	dlCode* code;
	dlAttrMap* attrmap;

	DLdouble* stack;
	DLuint stack_size;

	DLuint ip;
	DLuint sp;
};

struct dlslCompiler
{
	DLchar_p code;
	DLuint code_size;

	DLuint* tokens;
	DLuint tokens_size;

	DLuint location;

	dlCode result;
	DLuint error;
};

struct dlslToken
{
	DLuint type;
	DLchar value[24];
};

/* dlslRunner
 */

void dlslRunner_init (dlslRunner* runner);
void dlslRunner_free (dlslRunner* runner);

void dlslRunner_initStack (dlslRunner* runner, DLuint stack_size);
void dlslRunner_bindCode (dlslRunner* runner, dlCode* code);
void dlslRunner_bindAttrMap (dlslRunner* runner, dlAttrMap* attrmap);

void dlslRunner_run (dlslRunner* runner);

/* dlslCompiler
 */

void dlslCompiler_init (dlslCompiler* compiler);
void dlslCompiler_free (dlslCompiler* compiler);

void dlslCompiler_loadCode (dlslCompiler* compiler, DLchar_p code, DLuint size);
void dlslCompiler_compile (dlslCompiler* compiler);

void dlslCompiler_lexer (dlslCompiler* compiler);
void dlslCompiler_lexer_number (dlslCompiler* compiler);
void dlslCompiler_lexer_ident (dlslCompiler* compiler);
void dlslCompiler_lexer_symbol (dlslCompiler* compiler);

#endif