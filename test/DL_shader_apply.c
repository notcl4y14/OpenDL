#include <stdio.h>
#include <DL_core.h>
#include <DL_DLSL.h>

void debug_buffer (DLBuffer* buffer)
{
	DLint* data = (int*)buffer->data;
	printf("Buffer: [%d, %d]\n", data[0], data[1]);
}

int main ()
{
	DLSLRunner runner;
	DLBuffer buffer;
	DLShader shader;

	DLint buffer_data[2] = { 10, 20 };

	DLdouble shader_code[32] =
	{
		// DLSL_ALD, 1,
		// DLSL_ALD, 0,
		// DLSL_IADD,
		// DLSL_AST, 1,

		DLSL_ALD,  0, // Push buffer index
		DLSL_PUSH, 1, // Push 1
		DLSL_IADD,    // Add buffer index and 1

		DLSL_ALD,  1, // Push buffer value
		DLSL_IADD,    // Add (buffer index + 1) and buffer value

		DLSL_AST,  1, // Store the result in buffer value

		DLSL_QUIT,    // Quit
	};

	DLBuffer_init(&buffer, DL_INT, 2, sizeof(DLint));
	DLBuffer_setData(&buffer, &buffer_data, sizeof(buffer_data));

	DLShader_init(&shader);
	DLAttribMap_init(&shader.attrmap, 1);
	DLCode_load(&shader.code, shader_code, sizeof(shader_code) / sizeof(DLdouble));

	shader.attrmap.attrs[0].type = DL_INT;
	shader.attrmap.attrs[0].size = sizeof(DLint);

	shader.attrmap.attrs[1].type = DL_INT;
	shader.attrmap.attrs[1].size = sizeof(DLint);

	shader.attr_loc_index = 0;
	shader.attr_loc_value = 1;

	DLShader_apply(&shader, &buffer, &runner);

	debug_buffer(&buffer);
	return 0;
}