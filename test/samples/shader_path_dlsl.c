#include <stdio.h>
#include <DL.h>
#include <DLSL.h>

int main ()
{
	dlInit();

	double shader_path_code[8] =
	{
		DLSL_OPCODE_PUSH, 10,
		DLSL_OPCODE_BST, 0,
		DLSL_OPCODE_QUIT,
	};
	size_dl shader_path_code_size = sizeof(shader_path_code) / sizeof(double);

	loc_dl shader, path, buf_shader, buf_path;
	// double shader_code[8], path_code[8];

	shader = dlCreateShader();
	path = dlCreatePath();
	buf_shader = dlCreateBuffer(1, sizeof(double));
	buf_path = dlCreateBuffer(1, sizeof(double));

	dlShaderLoadCode(shader, &shader_path_code, shader_path_code_size);
	dlPathLoadCode(path, &shader_path_code, shader_path_code_size);

	dlApplyShader(shader, buf_shader);
	dlApplyPath(path, buf_path);

	printf("buf_shader: %f\n", ((double*)(DLarray_buffers[buf_shader].data))[0]);
	printf("buf_path: %f\n", ((double*)(DLarray_buffers[buf_path].data))[0]);

	dlTerminate();
	return 0;
}