#include <stdlib.h>
#include <string.h>

#include <DL/dlsl.h>
#include <DL/dlutil.h>

/* ////////////////
 * DLSLRunner
 * ////////////////
 */

void DLSLRunner_init (DLSLRunner* runner)
{
	runner->code = NULL;
	runner->attrmap = NULL;
	runner->stack = NULL;
	runner->stack_size = 0;
	runner->ip = 0;
	runner->sp = 0;
}

void DLSLRunner_free (DLSLRunner* runner)
{
	free(runner->stack);

	runner->code = NULL;
	runner->attrmap = NULL;
	runner->stack = NULL;
}

// 

void DLSLRunner_initStack (DLSLRunner* runner, DLuint stack_size)
{
	// TODO: Change `calloc` to `malloc` when needed
	runner->stack = calloc(stack_size, sizeof(double));
	runner->stack_size = stack_size;
}

void DLSLRunner_bindCode (DLSLRunner* runner, DLCode* code)
{
	runner->code = code;
}

void DLSLRunner_bindAttrMap (DLSLRunner* runner, DLAttrMap* attrmap)
{
	runner->attrmap = attrmap;
}

// 

void DLSLRunner_run (DLSLRunner* runner)
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
				DLutil_copydts(
					&runner->stack[++runner->sp],
					DL_DOUBLE,
					runner->attrmap->attrs[addr].vbstride * sizeof(DLdouble),
					sizeof(DLdouble),

					runner->attrmap->attrs[addr].value,
					runner->attrmap->attrs[addr].vtype,
					runner->attrmap->attrs[addr].vsize,
					runner->attrmap->attrs[addr].vsstride
				);
				break;

			case DLSL_AST:
				addr = runner->code->data[++runner->ip];
				// printf("stack value: %d\n", runner->stack[runner->sp]);
				DLutil_copydts(
					runner->attrmap->attrs[addr].value,
					runner->attrmap->attrs[addr].vtype,
					runner->attrmap->attrs[addr].vsize,
					runner->attrmap->attrs[addr].vsstride,

					&runner->stack[runner->sp],
					DL_DOUBLE,
					runner->attrmap->attrs[addr].vbstride * sizeof(DLdouble),
					sizeof(DLdouble)
				);
				runner->sp--;
				break;
		}
	}
}

/* ////////////////
 * DLSLCompiler
 * ////////////////
 */

// void DLSLCompiler_init (DLSLCompiler* compiler)
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

// void DLSLCompiler_free (DLSLCompiler* compiler)
// {
// 	free(compiler->code);
// 	free(compiler->tokens);
// 	DLCode_free(&compiler->result);
// }

// // 

// void DLSLCompiler_loadCode (DLSLCompiler* compiler, DLchar_p code, DLuint size)
// {
// 	compiler->code = malloc(size);
// 	compiler->code_size = 0;

// 	memcpy(compiler->code, code, size);
// }

// void DLSLCompiler_compile (DLSLCompiler* compiler)
// {
// 	DLSLCompiler_lexer(compiler);
// }

// // 

// void DLSLCompiler_lexer (DLSLCompiler* compiler)
// {
// 	compiler->location = -1;

// 	while (++compiler->location < compiler->code_size)
// 	{
// 		DLchar _char = compiler->code[compiler->location];

// 		if (_char >= '0' && _char <= '9')
// 		{
// 			DLSLCompiler_token_number(compiler);
// 		}
// 		else if (_char >= 'a' && _char <= 'z')
// 		{
// 			DLSLCompiler_token_ident(compiler);
// 		}
// 		else if (_char >= 'A' && _char <= 'Z')
// 		{
// 			DLSLCompiler_token_ident(compiler);
// 		}
// 		else if (_char >= '!' && _char <= '/')
// 		{
// 			DLSLCompiler_token_symbol(compiler);
// 		}
// 	}
// }

// void DLSLCompiler_token_number (DLSLCompiler* compiler)
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