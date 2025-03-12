#include <stdlib.h>
#include <string.h>

#include <DL.h>

struct DLShader* _DL_shaders_values;
struct DLPath*   _DL_paths_values;

DLUInt _DL_shaders_count;
DLUInt _DL_paths_count;

DLUInt _DL_shaders_capacity = 16;
DLUInt _DL_paths_capacity = 16;

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
		if (_DL_shaders_values[index].attrs_capacity == 0)
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
		if (_DL_paths_values[index].attrs_capacity == 0)
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

// ==================== //
// ======== DL ======== //
// ==================== //

void dlInit ()
{
	_DL_shaders_values = calloc(_DL_shaders_capacity, sizeof(struct DLShader));
	_DL_paths_values = calloc(_DL_paths_capacity, sizeof(struct DLPath));

	_DL_shaders_count = 0;
	_DL_paths_count = 0;
}

void dlTerminate ()
{
	_DL_shaders_count = 0;
	_DL_paths_count = 0;

	for (int i = 0; i < _DL_shaders_capacity; i++)
	{
		if (_DL_shaders_values[i].attrs_capacity == 0)
		{
			continue;
		}

		dlFreeShader(i);
	}

	for (int i = 0; i < _DL_paths_capacity; i++)
	{
		if (_DL_paths_values[i].attrs_capacity == 0)
		{
			continue;
		}

		dlFreePath(i);
	}

	free(_DL_shaders_values);
	free(_DL_paths_values);
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

	// shader.attrs_count = 0;
	shader.attrs_capacity = 0;
	shader.attrs_keys = NULL;
	shader.attrs_values = NULL;

	int index = shader_getFirstAvailable();
	_DL_shaders_values[index] = shader;
	_DL_shaders_count++;

	return index;
}

void dlFreeShader (DLUInt shader)
{
	struct DLShader* _shader = &_DL_shaders_values[shader];

	// Freeing attr parameters
	for (int i = 0; i < _shader->attrs_capacity; i++)
	{
		free(_shader->attrs_keys[i]);
	}

	// _shader->attrs_count = 0;
	_shader->attrs_capacity = 0;

	free(_shader->attrs_keys);
	free(_shader->attrs_values);
	_shader->attrs_keys = NULL;
	_shader->attrs_values = NULL;

	// Freeing buf_attr parameters
	_shader->buf_attrs_capacity = 0;
	_shader->buf_attrs_count = 0;

	free(_shader->buf_attrs_buffers);
	free(_shader->buf_attrs_voffset);
	free(_shader->buf_attrs_vsize);
	free(_shader->buf_attrs_attribs);

	_shader->buf_attrs_buffers = NULL;
	_shader->buf_attrs_voffset = NULL;
	_shader->buf_attrs_vsize = NULL;
	_shader->buf_attrs_attribs = NULL;

	_DL_shaders_count--;
}

void dlShaderInit (DLUInt shader, int attrs_capacity, int buf_attrs_capacity)
{
	struct DLShader* _shader = &_DL_shaders_values[shader];

	// _shader->attrs_count = 0;
	_shader->attrs_capacity = attrs_capacity;
	_shader->attrs_keys = calloc(attrs_capacity, sizeof(char*));
	_shader->attrs_values = calloc(attrs_capacity, sizeof(void*));

	_shader->buf_attrs_capacity = buf_attrs_capacity;
	_shader->buf_attrs_count = 0;
	_shader->buf_attrs_buffers = calloc(_shader->buf_attrs_capacity, sizeof(void*));
	_shader->buf_attrs_voffset = calloc(_shader->buf_attrs_capacity, sizeof(int));
	_shader->buf_attrs_vsize = calloc(_shader->buf_attrs_capacity, sizeof(int));
	_shader->buf_attrs_attribs = calloc(_shader->buf_attrs_capacity, sizeof(int));
}

void dlShaderBindAttribID (DLUInt shader, char* id, int index)
{
	struct DLShader* _shader = &_DL_shaders_values[shader];

	_shader->attrs_keys[index] = calloc(strlen(id), sizeof(char));
	strcpy(_shader->attrs_keys[index], id);
}

int dlShaderGetAttribIndex (DLUInt shader, char* id)
{
	struct DLShader* _shader = &_DL_shaders_values[shader];

	int index = -1;

	while (++index < _shader->attrs_capacity)
	{
		char* attr_id = _shader->attrs_keys[index];

		if (strcmp(attr_id, id) == 0)
		{
			return index;
		}
	}

	return -1;
}

void dlShaderBindUniformAttrib (DLUInt shader, int index, void* value)
{
	struct DLShader* _shader = &_DL_shaders_values[shader];
	_shader->attrs_values[index] = value;
}

void dlShaderBindBufferAttrib (DLUInt shader, void* buffer, DLUInt voffset, DLUInt vsize, DLUInt attrib)
{
	struct DLShader* _shader = &_DL_shaders_values[shader];

	int index = _shader->buf_attrs_count++;

	if (index >= _shader->buf_attrs_capacity)
	{
		_shader->buf_attrs_capacity = _shader->buf_attrs_capacity * 2;

		_shader->buf_attrs_buffers = realloc(_shader->buf_attrs_buffers, _shader->buf_attrs_capacity * sizeof(void*));
		_shader->buf_attrs_voffset = realloc(_shader->buf_attrs_voffset, _shader->buf_attrs_capacity * sizeof(int));
		_shader->buf_attrs_vsize = realloc(_shader->buf_attrs_vsize, _shader->buf_attrs_capacity * sizeof(int));
		_shader->buf_attrs_attribs = realloc(_shader->buf_attrs_attribs, _shader->buf_attrs_capacity * sizeof(int));
	}

	_shader->buf_attrs_buffers[index] = buffer;
	_shader->buf_attrs_voffset[index] = voffset;
	_shader->buf_attrs_vsize[index] = vsize;
	_shader->buf_attrs_attribs[index] = attrib;
}

// ======================== //
// ======== DLPath ======== //
// ======================== //

DLUInt dlCreatePath ()
{
	struct DLPath path;

	path.attrs_capacity = 0;
	path.attrs_keys = NULL;
	path.attrs_values = NULL;

	int index = path_getFirstAvailable();
	_DL_paths_values[index] = path;
	_DL_paths_count++;

	return index;
}

void dlFreePath (DLUInt path)
{
	struct DLPath* _path = &_DL_paths_values[path];

	for (int i = 0; i < _path->attrs_capacity; i++)
	{
		free(_path->attrs_keys[i]);
	}

	_path->attrs_capacity = 0;

	free(_path->attrs_keys);
	free(_path->attrs_values);
	_path->attrs_keys = NULL;
	_path->attrs_values = NULL;

	_DL_paths_count--;
}