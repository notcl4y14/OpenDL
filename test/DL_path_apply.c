#include <stdio.h>
#include <DL_core.h>
#include <DL_DLSL.h>

void debug_buffer (DLBuffer* buffer)
{
	DLint* data = (int*)buffer->data;
	printf("Buffer: [%d]\n", data[0]);
}

int main ()
{
	DLSLRunner runner;
	DLBuffer buffer;
	DLPath path;

	DLint buffer_data[1] = { 0 };

	DLdouble path_code[32] =
	{
		DLSL_PUSH, 10,
		DLSL_AST, 0,
		DLSL_QUIT,
	};

	DLBuffer_init(&buffer, DL_INT, 1, sizeof(DLint));
	DLBuffer_setData(&buffer, &buffer_data, sizeof(buffer_data));

	DLPath_init(&path);
	DLAttribMap_init(&path.attrmap, 1);
	DLCode_load(&path.code, path_code, sizeof(path_code) / sizeof(DLdouble));

	path.attrmap.attrs[0].type = DL_INT;
	path.attrmap.attrs[0].size = sizeof(buffer.data);

	path.attr_loc_buffer = 0;

	DLPath_apply(&path, &buffer, &runner);

	debug_buffer(&buffer);
	return 0;
}