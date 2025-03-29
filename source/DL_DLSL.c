#include <stdlib.h>

#include <DL_DLSL.h>

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
	runner->stack = malloc(stack_size * sizeof(double));
	runner->stack_size = stack_size;
}

void DLSLRunner_bindCode (DLSLRunner* runner, DLCode* code)
{
	runner->code = code;
}

void DLSLRunner_bindAttrMap (DLSLRunner* runner, DLAttribMap* attrmap)
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
		}
	}
}