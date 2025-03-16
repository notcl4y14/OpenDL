#include <stdio.h>
#include <DL.h>
#include <DLSL.h>

int main ()
{
	printf("Initializing DL...\n");
	dlInit();

	printf("Creating a Shader...\n");
	DLUInt shader = dlCreateShader();

	// There's a "bug" that makes realloc return NULL.
	// So this is why I put 4 here instead of 2.
	// Nevermind.
	dlShaderInit(shader, 4, 4);

	printf("Initializing Buffers...\n");
	int attrib_buffer[4 * 4] =
	{
		10, 0,   0,   0,
		20, 0,   0,   0,
		30, 0,   0,   0,
		40, 100, 200, 300,
	};

	int texture_buffer[4 * 4] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	};

	int shader_code[255] =
	{
		DLSL_OPCODE_PUSH, 512,
		DLSL_OPCODE_BUFFERVALUE_SET, 0,
		DLSL_OPCODE_PUSH, 256,
		DLSL_OPCODE_BUFFERVALUE_SET, 1,
		DLSL_OPCODE_PUSH, 128,
		DLSL_OPCODE_BUFFERVALUE_SET, 2,
		DLSL_OPCODE_PUSH, 64,
		DLSL_OPCODE_BUFFERVALUE_SET, 3,
		DLSL_OPCODE_QUIT,
	};

	printf("Loading the Shader code...\n");
	dlShaderLoadCode(shader, (int*)&shader_code, sizeof(shader_code) / sizeof(int));

	printf("Binding Attributes...\n");
	dlShaderBindAttribID(shader, "attrib1", 0);
	dlShaderBindAttribID(shader, "attrib2", 1);
	dlShaderBindAttribID(shader, "attrib3", 2);
	dlShaderBindAttribID(shader, "attrib4", 3);

	printf("Binding Attribute Buffers...\n");
	dlShaderBindBufferAttrib(
		shader,
		&attrib_buffer,
		0,
		4,
		sizeof(int),
		0
	);

	dlShaderBindBufferAttrib(
		shader,
		&attrib_buffer,
		1,
		4,
		sizeof(int),
		1
	);

	dlShaderBindBufferAttrib(
		shader,
		&attrib_buffer,
		2,
		4,
		sizeof(int),
		2
	);

	dlShaderBindBufferAttrib(
		shader,
		&attrib_buffer,
		3,
		4,
		sizeof(int),
		3
	);

	printf("Applying Shader...\n");
	dlApplyShader(shader, &texture_buffer, sizeof(texture_buffer) / sizeof(int), sizeof(int), 4);

	printf("Done!\n\n");

	printf("attrib1: %d\n", *(int*)_DL_shaders_values[shader].attrs.values[0]);
	printf("attrib2: %d\n", *(int*)_DL_shaders_values[shader].attrs.values[1]);
	printf("attrib3: %d\n", *(int*)_DL_shaders_values[shader].attrs.values[2]);
	printf("attrib4: %d\n", *(int*)_DL_shaders_values[shader].attrs.values[3]);

	printf("\n");

	printf("Texture Buffer:\n");

	for (int i = 0; i < sizeof(texture_buffer) / sizeof(int); i++)
	{
		printf("%d. %d\n", i, texture_buffer[i]);
	}

	return 0;
}