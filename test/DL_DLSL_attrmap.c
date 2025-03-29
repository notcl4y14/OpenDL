#include <stdio.h>
#include <DL_core.h>
#include <DL_DLSL.h>

void debug_stack (DLSLRunner* runner)
{
	double* stack = runner->stack;
	printf("Stack: [%f, %f, %f, %f]\n", stack[0], stack[1], stack[2], stack[3]);
}

void debug_attr (DLAttribute* attr)
{
	printf("Attribute: %f\n", *(float*)(attr->ptr));
}

int main ()
{
	DLdouble code_data[32] =
	{
		DLSL_PUSH, 10,
		DLSL_PUSH, 20,
		DLSL_IADD,
		DLSL_ALD, 0,
		DLSL_IADD,
		DLSL_AST, 0,
		DLSL_QUIT,
	};

	DLfloat attrmap_attr = 40;


	DLAttribMap attrmap;
	DLAttribMap_init(&attrmap, 1);

	DLSLRunner runner;
	DLSLRunner_init(&runner);

	DLCode code;
	DLCode_init(&code);


	attrmap.attrs[0].ptr = &attrmap_attr;
	attrmap.attrs[0].type = DL_FLOAT;
	attrmap.attrs[0].size = sizeof(DLfloat);

	DLCode_load(&code, (double*)&code_data, sizeof(code_data) / sizeof(double));

	DLSLRunner_initStack(&runner, 4);
	DLSLRunner_bindCode(&runner, &code);
	DLSLRunner_bindAttrMap(&runner, &attrmap);


	DLSLRunner_run(&runner);


	debug_stack(&runner);
	debug_attr(&attrmap.attrs[0]);
	return 0;
}