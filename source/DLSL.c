#include <stdlib.h>
#include <string.h>

#include <DLSL.h>

void DLSLRunner_loadCode (struct DLSLRunner* runner, double* code, DLuint code_size)
{
	runner->code = malloc(code_size * sizeof(double));
	runner->code_size = code_size;
	memcpy(runner->code, code, code_size);
}

void DLSLRunner_run (struct DLSLRunner* runner)
{
	DLuint ip, sp, addr, usize;
	double a, b, c;

	ip = -1;
	sp = -1;
	addr = 0;
	usize = 1;
	a = 0;
	b = 0;
	c = 0;

	DLuchar running = 1;
	DLuchar opcode = -1;

	while (running)
	{
		opcode = runner->code[++ip];

		switch (opcode)
		{
			case DLSL_OPCODE_JUMP:
				ip = runner->code[ip + 1];
				ip--;
				break;

			case DLSL_OPCODE_QUIT:
				running = 0;
				break;

			case DLSL_OPCODE_USIZ:
				usize = runner->code[++ip];
				break;

			case DLSL_OPCODE_PUSH:
				runner->stack[++sp] = runner->code[++ip];
				break;

			case DLSL_OPCODE_POP:
				sp--;
				break;

			case DLSL_OPCODE_GLD:
				addr = runner->code[++ip];
				runner->stack[++sp] = runner->globals[addr];
				break;

			case DLSL_OPCODE_GST:
				addr = runner->code[++ip];
				runner->globals[addr] = runner->stack[sp--];
				break;

			case DLSL_OPCODE_IADD:
				b = runner->stack[sp--];
				a = runner->stack[sp--];
				runner->stack[++sp] = a + b;
				break;

			case DLSL_OPCODE_ISUB:
				b = runner->stack[sp--];
				a = runner->stack[sp--];
				runner->stack[++sp] = a - b;
				break;

			case DLSL_OPCODE_IMUL:
				b = runner->stack[sp--];
				a = runner->stack[sp--];
				runner->stack[++sp] = a * b;
				break;

			case DLSL_OPCODE_IDIV:
				b = runner->stack[sp--];
				a = runner->stack[sp--];
				runner->stack[++sp] = a / b;
				break;
		}
	}
}