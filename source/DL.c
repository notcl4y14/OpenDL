#include <stdlib.h>
#include <string.h>

#include <DL.h>
#include <DLSL.h>

struct DLShader* _DL_shaders_values;
struct DLPath*   _DL_paths_values;

DLUInt _DL_shaders_count;
DLUInt _DL_paths_count;

DLUInt _DL_shaders_capacity = 16;
DLUInt _DL_paths_capacity = 16;

struct DLSLVM _DL_dlsl_vm;

// ====================== //
// ======== Util ======== //
// ====================== //

struct DLShader* shader_get (DLUInt shader)
{
	return &_DL_shaders_values[shader];
}

struct DLPath* path_get (DLUInt path)
{
	return &_DL_paths_values[path];
}

int shader_getFirstAvailable ()
{
	int index = -1;

	while (++index < _DL_shaders_capacity)
	{
		if (_DL_shaders_values[index].attrs.capacity == 0)
		{
			break;
		}
	}

	if (index == _DL_shaders_capacity)
	{
		_DL_shaders_capacity = _DL_shaders_capacity * 2;
		_DL_shaders_values = realloc(_DL_shaders_values, _DL_shaders_capacity * sizeof(struct DLShader));
		return shader_getFirstAvailable();
	}

	return index;
}

int path_getFirstAvailable ()
{
	int index = -1;

	while (++index < _DL_paths_capacity)
	{
		if (_DL_paths_values[index].attrs.capacity == 0)
		{
			break;
		}
	}

	if (index == _DL_paths_capacity)
	{
		_DL_paths_capacity = _DL_paths_capacity * 2;
		_DL_paths_values = realloc(_DL_paths_values, _DL_paths_capacity * sizeof(struct DLPath));
		return path_getFirstAvailable();
	}

	return index;
}

void shader_applyBufferAttrib (DLUInt shader, DLUInt val_index)
{
	struct DLShader* _shader = &_DL_shaders_values[shader];

	// buf_index is a loop index for Buffer Attributes
	// val_index is a loop index for Buffer Arrays
	int buf_index = -1;

	while (++buf_index < _shader->buf_attrs.count)
	{
		void* _buffer = _shader->buf_attrs.buffers[buf_index];

		DLUInt voffset = _shader->buf_attrs.voffset[buf_index];
		DLUInt vstride = _shader->buf_attrs.vstride[buf_index];
		DLUInt vsize = _shader->buf_attrs.vsize[buf_index];
		DLUInt attrib = _shader->buf_attrs.attribs[buf_index];

		if (val_index % vstride > 0)
		{
			continue;
		}

		void* value = _buffer + (val_index + voffset) * vsize;
		dlShaderBindUniformAttrib(shader, attrib, value);
	}
}

// ==================== //
// ======== DL ======== //
// ==================== //

void dlInit ()
{
	_DL_shaders_values = calloc(_DL_shaders_capacity, sizeof(struct DLShader));
	_DL_paths_values = calloc(_DL_paths_capacity, sizeof(struct DLPath));

	_DL_shaders_count = 0;
	_DL_paths_count = 0;

	_DL_dlsl_vm = dlslCreateVM();
	dlslVMLoad(&_DL_dlsl_vm, 64, 64, 64);
}

void dlTerminate ()
{
	_DL_shaders_count = 0;
	_DL_paths_count = 0;

	for (int i = 0; i < _DL_shaders_capacity; i++)
	{
		if (_DL_shaders_values[i].attrs.capacity == 0)
		{
			continue;
		}

		dlFreeShader(i);
	}

	for (int i = 0; i < _DL_paths_capacity; i++)
	{
		if (_DL_paths_values[i].attrs.capacity == 0)
		{
			continue;
		}

		dlFreePath(i);
	}

	free(_DL_shaders_values);
	free(_DL_paths_values);
	dlslFreeVM(&_DL_dlsl_vm);
}

void dlInitialArrayCapacity (DLUInt object, DLUInt capacity)
{
	switch (object)
	{
		case DL_OBJECT_SHADER:
			_DL_shaders_capacity = capacity;
			break;

		case DL_OBJECT_PATH:
			_DL_paths_capacity = capacity;
			break;

		case DL_OBJECT_ALL:
			_DL_shaders_capacity = capacity;
			_DL_paths_capacity = capacity;
			break;
	}
}

// ========================== //
// ======== DLShader ======== //
// ========================== //

DLUInt dlCreateShader ()
{
	struct DLShader shader;

	shader.attrs.capacity = 0;
	shader.attrs.keys = NULL;
	shader.attrs.values = NULL;

	shader.buf_attrs.capacity = 0;
	shader.buf_attrs.count = 0;
	shader.buf_attrs.buffers = NULL;
	shader.buf_attrs.voffset = NULL;
	shader.buf_attrs.vstride = NULL;
	shader.buf_attrs.vsize = NULL;
	shader.buf_attrs.attribs = NULL;

	int index = shader_getFirstAvailable();
	_DL_shaders_values[index] = shader;
	_DL_shaders_count++;

	return index;
}

void dlFreeShader (DLUInt shader)
{
	struct DLShader* _shader = &_DL_shaders_values[shader];

	// Freeing code parameters
	_shader->code.code_size = 0;

	free(_shader->code.code);

	_shader->code.code = NULL;

	// Freeing attr parameters
	for (int i = 0; i < _shader->attrs.capacity; i++)
	{
		free(_shader->attrs.keys[i]);
	}

	_shader->attrs.capacity = 0;

	free(_shader->attrs.keys);
	free(_shader->attrs.values);
	_shader->attrs.keys = NULL;
	_shader->attrs.values = NULL;

	// Freeing buf_attr parameters
	_shader->buf_attrs.capacity = 0;
	_shader->buf_attrs.count = 0;

	free(_shader->buf_attrs.buffers);
	free(_shader->buf_attrs.voffset);
	free(_shader->buf_attrs.vstride);
	free(_shader->buf_attrs.vsize);
	free(_shader->buf_attrs.attribs);

	_shader->buf_attrs.buffers = NULL;
	_shader->buf_attrs.voffset = NULL;
	_shader->buf_attrs.vstride = NULL;
	_shader->buf_attrs.vsize = NULL;
	_shader->buf_attrs.attribs = NULL;

	_DL_shaders_count--;
}

void dlShaderInit (DLUInt shader, int attrs_capacity, int buf_attrs_capacity)
{
	struct DLShader* _shader = &_DL_shaders_values[shader];

	_shader->attrs.capacity = attrs_capacity;
	_shader->attrs.keys = calloc(attrs_capacity, sizeof(char*));
	_shader->attrs.values = calloc(attrs_capacity, sizeof(void*));

	_shader->buf_attrs.capacity = buf_attrs_capacity;
	_shader->buf_attrs.count = 0;
	_shader->buf_attrs.buffers = calloc(_shader->buf_attrs.capacity, sizeof(void*));
	_shader->buf_attrs.voffset = calloc(_shader->buf_attrs.capacity, sizeof(int));
	_shader->buf_attrs.vstride = calloc(_shader->buf_attrs.capacity, sizeof(int));
	_shader->buf_attrs.vsize = calloc(_shader->buf_attrs.capacity, sizeof(int));
	_shader->buf_attrs.attribs = calloc(_shader->buf_attrs.capacity, sizeof(int));
}

void dlShaderBindAttribID (DLUInt shader, char* id, int index)
{
	struct DLShader* _shader = &_DL_shaders_values[shader];

	_shader->attrs.keys[index] = calloc(strlen(id), sizeof(char));
	strcpy(_shader->attrs.keys[index], id);
}

void dlShaderLoadCode (DLUInt shader, int* code, int code_size)
{
	struct DLShader* _shader = &_DL_shaders_values[shader];

	_shader->code.code_size = code_size;
	_shader->code.code = calloc(_shader->code.code_size, sizeof(int));

	int index = -1;

	while (++index < _shader->code.code_size)
	{
		_shader->code.code[index] = code[index];
	}
}

DLUInt dlShaderGetAttribIndex (DLUInt shader, char* id)
{
	struct DLShader* _shader = &_DL_shaders_values[shader];

	int index = -1;

	while (++index < _shader->attrs.capacity)
	{
		char* attr_id = _shader->attrs.keys[index];

		if (strcmp(attr_id, id) == 0)
		{
			return index;
		}
	}

	return -1;
}

void dlShaderBindUniformAttrib (DLUInt shader, int index, void* attrib)
{
	struct DLShader* _shader = &_DL_shaders_values[shader];
	_shader->attrs.values[index] = attrib;
}

void dlShaderBindBufferAttrib (DLUInt shader, void* buffer, DLUInt voffset, DLUInt vstride, DLUInt vsize, DLUInt attrib)
{
	struct DLShader* _shader = &_DL_shaders_values[shader];

	int index = _shader->buf_attrs.count++;

	if (index >= _shader->buf_attrs.capacity)
	{
		_shader->buf_attrs.capacity = _shader->buf_attrs.capacity * 2;

		_shader->buf_attrs.buffers = realloc(_shader->buf_attrs.buffers, _shader->buf_attrs.capacity * sizeof(void*));
		_shader->buf_attrs.voffset = realloc(_shader->buf_attrs.voffset, _shader->buf_attrs.capacity * sizeof(DLUInt));
		_shader->buf_attrs.vstride = realloc(_shader->buf_attrs.vstride, _shader->buf_attrs.capacity * sizeof(DLUInt));
		_shader->buf_attrs.vsize = realloc(_shader->buf_attrs.vsize, _shader->buf_attrs.capacity * sizeof(DLUInt));
		_shader->buf_attrs.attribs = realloc(_shader->buf_attrs.attribs, _shader->buf_attrs.capacity * sizeof(DLUInt));
	}

	_shader->buf_attrs.buffers[index] = buffer;
	_shader->buf_attrs.voffset[index] = voffset;
	_shader->buf_attrs.vstride[index] = vstride;
	_shader->buf_attrs.vsize[index] = vsize;
	_shader->buf_attrs.attribs[index] = attrib;
}

void dlApplyShader (DLUInt shader, void* dest_buffer, DLUInt buffer_size, DLUInt byte_size)
{
	struct DLShader* _shader = &_DL_shaders_values[shader];

	dlslVMLoadCode(&_DL_dlsl_vm, _shader->code.code, _shader->code.code_size);

	int index = -1;

	while (++index < buffer_size)
	{
		shader_applyBufferAttrib (shader, index);
		dlslVMRun(&_DL_dlsl_vm);
		memcpy(dest_buffer + (index * byte_size), &_DL_dlsl_vm.dl_BufferValue, byte_size);
	}
}

// ======================== //
// ======== DLPath ======== //
// ======================== //

DLUInt dlCreatePath ()
{
	struct DLPath path;

	path.attrs.capacity = 0;
	path.attrs.keys = NULL;
	path.attrs.values = NULL;

	int index = path_getFirstAvailable();
	_DL_paths_values[index] = path;
	_DL_paths_count++;

	return index;
}

void dlFreePath (DLUInt path)
{
	struct DLPath* _path = &_DL_paths_values[path];

	for (int i = 0; i < _path->attrs.capacity; i++)
	{
		free(_path->attrs.keys[i]);
	}

	_path->attrs.capacity = 0;

	free(_path->attrs.keys);
	free(_path->attrs.values);
	_path->attrs.keys = NULL;
	_path->attrs.values = NULL;

	_DL_paths_count--;
}

void dlPathInit (DLUInt path, int attrs_capacity)
{
	struct DLPath* _path = &_DL_paths_values[path];

	_path->attrs.capacity = attrs_capacity;
	_path->attrs.keys = calloc(attrs_capacity, sizeof(char*));
	_path->attrs.values = calloc(attrs_capacity, sizeof(void*));
}

void dlPathBindAttribID (DLUInt path, char* id, int index)
{
	struct DLPath* _path = &_DL_paths_values[path];

	_path->attrs.keys[index] = calloc(strlen(id), sizeof(char));
	strcpy(_path->attrs.keys[index], id);
}

DLUInt dlPathGetAttribIndex (DLUInt path, char* id)
{
	struct DLPath* _path = &_DL_paths_values[path];

	int index = -1;

	while (++index < _path->attrs.capacity)
	{
		char* attr_id = _path->attrs.keys[index];

		if (strcmp(attr_id, id) == 0)
		{
			return index;
		}
	}

	return -1;
}

void dlPathBindUniformAttrib (DLUInt path, int index, void* attrib)
{
	struct DLPath* _path = &_DL_paths_values[path];
	_path->attrs.values[index] = attrib;
}
