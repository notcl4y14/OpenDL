#include <stdio.h>
#include <DL_core.h>
#include <DL_DLSL.h>

void debug_stack (DLSLRunner* runner)
{
	double* stack = runner->stack;
	printf("Stack: [%f, %f, %f, %f]\n", stack[0], stack[1], stack[2], stack[3]);
}

int main ()
{
	DLdouble code_data[32] =
	{
		DLSL_PUSH, 10,
		DLSL_PUSH, 20,
		DLSL_IADD,
		DLSL_QUIT,
	};

	DLSLRunner runner;
	DLSLRunner_init(&runner);

	DLCode code;
	DLCode_init(&code);

	DLCode_load(&code, (double*)&code_data, sizeof(code_data) / sizeof(double));

	DLSLRunner_initStack(&runner, 4);
	DLSLRunner_bindCode(&runner, &code);

	DLSLRunner_run(&runner);

	debug_stack(&runner);
	return 0;
}