#include <stdio.h>
#include <DL.h>

void print_shader (DLUInt shader);

int main ()
{
	printf("Initializing DL...\n\n");
	dlInit();

	printf("Creating a DLShader...\n\n");
	DLUInt shader = dlCreateShader();

	printf("Initializing a DLShader...\n\n");
	dlShaderInit(shader, 4, 1);

	dlShaderBindAttribID(shader, "multiplier", 0);
	dlShaderBindAttribID(shader, "color", 1);
	dlShaderBindAttribID(shader, "corners", 2);
	dlShaderBindAttribID(shader, "sides", 3);

	printf("Binding DLShader's attributes...\n\n");
	int shader_attribs[4] =
	{
		4, 0xFFFF00, 1, 1,
	};

	dlShaderBindUniformAttrib(shader, dlShaderGetAttribIndex(shader, "multiplier"), &shader_attribs[0]);
	dlShaderBindUniformAttrib(shader, dlShaderGetAttribIndex(shader, "color"), &shader_attribs[1]);
	dlShaderBindUniformAttrib(shader, dlShaderGetAttribIndex(shader, "corners"), &shader_attribs[2]);
	dlShaderBindUniformAttrib(shader, dlShaderGetAttribIndex(shader, "sides"), &shader_attribs[3]);

	dlShaderBindBufferAttrib(shader, &shader_attribs, 0, 1, sizeof(int), 0);

	print_shader(shader);
	printf("\n");

	printf("Freeing Shader...\n\n");
	dlFreeShader(shader);

	print_shader(shader);
	printf("\n");

	printf("Terminating DL...\n\n");
	dlTerminate();

	printf("Done!\n");
	return 0;
}

void print_shader (DLUInt shader)
{
	DLShader* _shader = &_DL_shaders_values[shader];

	printf("DLShader (0x%x)\n", (DLUChar*)_shader);
	printf("- Attribs Capacity: %d\n", _shader->attrs.capacity);
	printf("- Attribs:");

	if (_shader->attrs.capacity == 0)
	{
		printf(" None\n");
	}
	else
	{
		printf("\n");
	}

	for (int i = 0; i < _shader->attrs.capacity; i++)
	{
		// printf("	- %d. %s: %d (0x%x)\n", i, _shader->attrs_keys[i], *(int*)_shader->attrs_values[i], &_shader->attrs_values[i]);
		printf("	- %d. ", i);

		if (_shader->attrs.keys[i] == NULL)
		{
			printf("*unbound*");
		}
		else
		{
			printf("%s", _shader->attrs.keys[i]);
		}

		printf(": ");

		if (_shader->attrs.values[i] == NULL)
		{
			printf("null");
		}
		else
		{
			printf("%d", *(long*)_shader->attrs.values[i]);
		}

		printf("\n");
	}

	printf("- Buffer Attribs Capacity: %d\n", _shader->buf_attrs.capacity);
	printf("- Buffer Attribs Count: %d\n", _shader->buf_attrs.count);
	printf("- Buffer Attribs:");

	if (_shader->buf_attrs.count == 0)
	{
		printf(" None\n");
	}
	else
	{
		printf("\n");
		printf("	     Buffer\tvOffset\tvSize\tAttrib\n");
	}

	for (int i = 0; i < _shader->buf_attrs.count; i++)
	{
		printf(
			"	- %d. 0x%x\t%d\t%d\t%d",
			i,
			&_shader->buf_attrs.buffers[i],
			_shader->buf_attrs.voffset[i],
			_shader->buf_attrs.vsize[i],
			_shader->buf_attrs.attribs[i]
		);

		printf("\n");
	}
}