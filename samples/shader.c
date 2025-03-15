#include <stdio.h>
#include <DL.h>
#include <DLSL.h>

int main ()
{
	dlInit();

	DLUInt shader = dlCreateShader();
	dlShaderInit(shader, 2, 2);

	int attrib_buffer[4 * 4] =
	{
		10, 0,   0,   0,
		20, 0,   0,   0,
		30, 0,   0,   0,
		40, 100, 200, 300,
	};

	int texture_buffer[4] =
	{
		0, 0, 0, 0,
	};

	int shader_code[255] =
	{
		DLSL_OPCODE_PUSH, 512,
		DLSL_OPCODE_BUFFERVALUE,
		DLSL_OPCODE_QUIT,
	};

	dlShaderLoadCode(shader, (int*)&shader_code, sizeof(shader_code) / sizeof(int));

	dlShaderBindAttribID(shader, "attrib1", 0);
	dlShaderBindAttribID(shader, "attrib2", 1);
	dlShaderBindAttribID(shader, "attrib3", 2);
	dlShaderBindAttribID(shader, "attrib4", 3);

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

	dlApplyShader(shader, &texture_buffer, sizeof(texture_buffer), sizeof(int));

	printf("attrib1: %d\n", *(int*)_DL_shaders_values[shader].attrs.values[0]);
	printf("attrib2: %d\n", *(int*)_DL_shaders_values[shader].attrs.values[1]);
	printf("attrib3: %d\n", *(int*)_DL_shaders_values[shader].attrs.values[2]);
	printf("attrib4: %d\n", *(int*)_DL_shaders_values[shader].attrs.values[3]);

	printf("\n");

	printf("Texture Buffer:\n");

	for (int i = 0; i < 4; i++)
	{
		printf("%d. %d\n", i, texture_buffer[i]);
	}

	return 0;
}