#include <stdio.h>
#include <DL.h>
#include <DLSL.h>

int main ()
{
	dlInit();

	DLuint buffer, shader;
	struct DLShader* _shader;
	struct DLBuffer* _buffer;

	DLubyte buffer_data[4] = { 10, 20, 40, 80 };
	double shader_code[32] =
	{
		DLSL_ALD, 0,  // Buffer Value
		DLSL_ALD, 1,  // Buffer Index
		DLSL_IADD,
		DLSL_AST, 0,

		DLSL_QUIT,
	};

	shader = dlCreateShader();
	_shader = &DLarray_shaders[shader];

		// Initializing Shader Attributes
		_shader->attrs = DL_createAttrs(2);

		// Binding Shader Attributes
		DL_shaderBindAttrib_value(_shader, 0);
		DL_shaderBindAttrib_index(_shader, 1);

	dlShaderLoadCode(shader, &shader_code, sizeof(shader_code) / sizeof(double));

	// Be careful, I tried (4, DL_UBYTE) for (type, size) here
	buffer = dlCreateBuffer(DL_UBYTE, 4);
	_buffer = &DLarray_buffers[buffer];

	dlBufferLoadData(buffer, &buffer_data);

	dlApplyShader(shader, buffer);

	printf("Buffer: [%d, %d, %d, %d]\n",
		((DLubyte*)(_buffer->data))[0],
		((DLubyte*)(_buffer->data))[1],
		((DLubyte*)(_buffer->data))[2],
		((DLubyte*)(_buffer->data))[3]);

	// dlTerminate();
	return 0;
}