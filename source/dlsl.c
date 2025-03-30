#include <stdlib.h>
#include <string.h>

#include <DL/dlsl.h>
#include <DL/dlutil.h>

/* ////////////////
 * dlslRunner
 * ////////////////
 */

void dlslRunner_init (dlslRunner* runner)
{
	runner->code = NULL;
	runner->attrmap = NULL;
	runner->stack = NULL;
	runner->stack_size = 0;
	runner->ip = 0;
	runner->sp = 0;
}

void dlslRunner_free (dlslRunner* runner)
{
	free(runner->stack);

	runner->code = NULL;
	runner->attrmap = NULL;
	runner->stack = NULL;
}

// 

void dlslRunner_initStack (dlslRunner* runner, DLuint stack_size)
{
	// TODO: Change `calloc` to `malloc` when needed
	runner->stack = calloc(stack_size, sizeof(double));
	runner->stack_size = stack_size;
}

void dlslRunner_bindCode (dlslRunner* runner, dlCode* code)
{
	runner->code = code;
}

void dlslRunner_bindAttrMap (dlslRunner* runner, dlAttrMap* attrmap)
{
	runner->attrmap = attrmap;
}

// 

void dlslRunner_run (dlslRunner* runner)
{
	DLdouble a, b;
	DLuint addr;
	DLubyte opcode;
	DLbool running;

	runner->ip = -1;
	runner->sp = -1;

	a = 0;
	b = 0;
	addr = 0;
	opcode = 0;
	running = DL_TRUE;

	while (running)
	{
		opcode = runner->code->data[++runner->ip];

		switch (opcode)
		{
			case DLSL_JUMP:
				addr = runner->code->data[++runner->ip];
				runner->ip = addr - 1;
				break;

			case DLSL_QUIT:
				running = DL_FALSE;
				break;

			case DLSL_PUSH:
				runner->stack[++runner->sp] = runner->code->data[++runner->ip];
				break;

			case DLSL_POP:
				runner->sp--;
				break;

			case DLSL_IADD:
				b = runner->stack[runner->sp--];
				a = runner->stack[runner->sp--];
				runner->stack[++runner->sp] = a + b;
				break;

			case DLSL_ISUB:
				b = runner->stack[runner->sp--];
				a = runner->stack[runner->sp--];
				runner->stack[++runner->sp] = a - b;
				break;

			case DLSL_IMUL:
				b = runner->stack[runner->sp--];
				a = runner->stack[runner->sp--];
				runner->stack[++runner->sp] = a * b;
				break;

			case DLSL_IDIV:
				b = runner->stack[runner->sp--];
				a = runner->stack[runner->sp--];
				runner->stack[++runner->sp] = a / b;
				break;

			case DLSL_ALD:
				addr = runner->code->data[++runner->ip];
				dlUtil_copydt(
					&runner->stack[++runner->sp],
					DL_DOUBLE,
					runner->attrmap->attrs[addr].ptr,
					runner->attrmap->attrs[addr].type
				);
				break;

			case DLSL_AST:
				addr = runner->code->data[++runner->ip];
				dlUtil_copydt(
					runner->attrmap->attrs[addr].ptr,
					runner->attrmap->attrs[addr].type,
					&runner->stack[runner->sp],
					DL_DOUBLE
				);
				runner->sp--;
				break;
		}
	}
}

/* ////////////////
 * dlslCompiler
 * ////////////////
 */

// void dlslCompiler_init (dlslCompiler* compiler)
// {
// 	compiler->code = NULL;
// 	compiler->code_size = 0;

// 	compiler->tokens = NULL;
// 	compiler->tokens_size = 0;

// 	compiler->location = 0;

// 	compiler->error = DLSL_COMP_ERR_NONE;
// 	compiler->result.data = NULL;
// 	compiler->result.size = 0;
// }

// void dlslCompiler_free (dlslCompiler* compiler)
// {
// 	free(compiler->code);
// 	free(compiler->tokens);
// 	DLCode_free(&compiler->result);
// }

// // 

// void dlslCompiler_loadCode (dlslCompiler* compiler, DLchar_p code, DLuint size)
// {
// 	compiler->code = malloc(size);
// 	compiler->code_size = 0;

// 	memcpy(compiler->code, code, size);
// }

// void dlslCompiler_compile (dlslCompiler* compiler)
// {
// 	dlslCompiler_lexer(compiler);
// }

// // 

// void dlslCompiler_lexer (dlslCompiler* compiler)
// {
// 	compiler->location = -1;

// 	while (++compiler->location < compiler->code_size)
// 	{
// 		DLchar _char = compiler->code[compiler->location];

// 		if (_char >= '0' && _char <= '9')
// 		{
// 			dlslCompiler_token_number(compiler);
// 		}
// 		else if (_char >= 'a' && _char <= 'z')
// 		{
// 			dlslCompiler_token_ident(compiler);
// 		}
// 		else if (_char >= 'A' && _char <= 'Z')
// 		{
// 			dlslCompiler_token_ident(compiler);
// 		}
// 		else if (_char >= '!' && _char <= '/')
// 		{
// 			dlslCompiler_token_symbol(compiler);
// 		}
// 	}
// }

// void dlslCompiler_token_number (dlslCompiler* compiler)
// {
// 	DLchar_p num_str = calloc(8, sizeof(DLchar));
// 	DLuint num_str_count = 0;
// 	DLbool is_float = DL_FALSE;

// 	while (compiler->location < compiler->code_size)
// 	{
// 		DLchar _char = compiler->code[compiler->location];
// 		DLbool stop = !( (_char >= '0' && _char <= '9') || (_char == '.') );

// 		if (stop)
// 		{
// 			break;
// 		}

// 		if (_char == '.')
// 		{
// 			if (is_float)
// 			{
// 				break;
// 			}
			
// 			is_float = DL_TRUE;
// 		}

// 		num_str[num_str_count] = _char;

// 		compiler->location++;
// 	}
// }