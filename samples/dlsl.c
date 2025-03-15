#include <stdio.h>
#include <DL.h>
#include <DLSL.h>

void render_stack (struct DLSLVM* vm, DLUInt split);
void render_global (struct DLSLVM* vm, DLUInt split);

int main ()
{
	DLUInt shader_attr_size = 4;
	DLUInt vm_stack_size = 32;
	DLUInt vm_global_size = 32;

	// Initializing DL
	dlInit();

	// Creating and initializing Shader
	DLUInt shader = dlCreateShader();
	dlShaderInit(shader, shader_attr_size, shader_attr_size);

	// Creating a Uniform Attribute Buffer for Shader
	int shader_attrs[4] =
	{
		10, 20, 30, 40
	};

	// Binding Shader's Uniform Attributes
	dlShaderBindUniformAttrib(shader, 0, &shader_attrs[0]);
	dlShaderBindUniformAttrib(shader, 1, &shader_attrs[1]);
	dlShaderBindUniformAttrib(shader, 2, &shader_attrs[2]);
	dlShaderBindUniformAttrib(shader, 3, &shader_attrs[3]);

	// Creating and initializing DLSL VM
	struct DLSLVM vm = dlslCreateVM();
	dlslVMInit(&vm, vm_stack_size, vm_global_size, shader_attr_size);

	// Creating VM's code
	int code[255] =
	{
		// DLSL_OPCODE_PUSH, 10,
		// DLSL_OPCODE_GST, 0,

		// DLSL_OPCODE_PUSH, 64,
		// DLSL_OPCODE_GLD, 0,

		// DLSL_OPCODE_IADD,

		DLSL_OPCODE_ALD, 0,
		DLSL_OPCODE_GST, 0,

		DLSL_OPCODE_ALD, 1,
		DLSL_OPCODE_GST, 1,

		DLSL_OPCODE_ALD, 2,
		DLSL_OPCODE_GST, 2,

		DLSL_OPCODE_ALD, 3,
		DLSL_OPCODE_GST, 3,

		DLSL_OPCODE_QUIT,
	};

	// Binding VM code
	dlslVMBindCode(&vm, code, sizeof(code) / sizeof(int));

	// Loading Shader's attributes to VM
	dlslVMLoadAttribs(&vm, &_DL_shaders_values[shader].attrs);

	// Running VM
	dlslVMRun(&vm);

	// Rendering VM's stack and globals
	printf("STACK\n");
	render_stack(&vm, 2);

	printf("\n\n");

	printf("GLOBAL\n");
	render_global(&vm, 2);

	return 0;
}

void render_stack (struct DLSLVM* vm, DLUInt split)
{
	for (int i = 0; i < vm->stack_size; i++)
	{
		if (i > 0 && i % split == 0)
		{
			printf("\n");
		}

		printf("%.2d. %d;\t", i, vm->stack[i]);
	}
}

void render_global (struct DLSLVM* vm, DLUInt split)
{
	for (int i = 0; i < vm->global_size; i++)
	{
		if (i > 0 && i % split == 0)
		{
			printf("\n");
		}

		printf("%.2d. %d;\t", i, vm->global[i]);
	}
}