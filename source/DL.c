#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <DL.h>

struct DLBuffer* _DL_buffers;
struct DLShader* _DL_shaders;
struct DLPath*   _DL_paths;

DLuint _DL_buffers_count;
DLuint _DL_shaders_count;
DLuint _DL_paths_count;

DLuint _DL_buffers_capacity;
DLuint _DL_shaders_capacity;
DLuint _DL_paths_capacity;

// 
// 

DLuint DL_buffers_add (struct DLBuffer buffer)
{
	DLuint location = -1;

	while (++location < _DL_buffers_capacity)
	{
		if (_DL_buffers[location].buffer == NULL)
		{
			break;
		}
	}

	if (location >= _DL_buffers_capacity)
	{
		_DL_buffers_capacity = _DL_buffers_capacity * 2;
		_DL_buffers = realloc(_DL_buffers, _DL_buffers_capacity * sizeof(struct DLBuffer));
	}

	_DL_buffers_count++;
	_DL_buffers[location] = buffer;

	return location;
}

DLuint DL_shaders_add (struct DLShader shader)
{
	DLuint location = -1;

	while (++location < _DL_shaders_capacity)
	{
		if (_DL_shaders[location].attrs.capacity == 0)
		{
			break;
		}
	}

	if (location >= _DL_shaders_capacity)
	{
		_DL_shaders_capacity = _DL_shaders_capacity * 2;
		_DL_shaders = realloc(_DL_shaders, _DL_shaders_capacity * sizeof(struct DLShader));
	}

	_DL_shaders_count++;
	_DL_shaders[location] = shader;

	return location;
}

DLuint DL_paths_add (struct DLPath path)
{
	DLuint location = -1;

	while (++location < _DL_paths_capacity)
	{
		if (_DL_paths[location].attrs.capacity == 0)
		{
			break;
		}
	}

	if (location >= _DL_paths_capacity)
	{
		_DL_paths_capacity = _DL_paths_capacity * 2;
		_DL_paths = realloc(_DL_paths, _DL_paths_capacity * sizeof(struct DLPath));
	}

	_DL_paths_count++;
	_DL_paths[location] = path;

	return location;
}

// 
// 

void dlInit ()
{
	_DL_buffers_capacity = 16;
	_DL_shaders_capacity = 16;
	_DL_paths_capacity = 16;

	_DL_buffers_count = 0;
	_DL_shaders_count = 0;
	_DL_paths_count = 0;

	_DL_buffers = calloc(_DL_buffers_capacity, sizeof(struct DLBuffer));
	_DL_shaders = calloc(_DL_shaders_capacity, sizeof(struct DLShader));
	_DL_paths = calloc(_DL_paths_capacity, sizeof(struct DLPath));
}

void dlTerminate ()
{
	DLuint arr_index;

	arr_index = -1;
	while (++arr_index < _DL_buffers_capacity)
	{
		dlFreeBuffer(arr_index);
	}

	arr_index = -1;
	while (++arr_index < _DL_shaders_capacity)
	{
		dlFreeShader(arr_index);
	}

	arr_index = -1;
	while (++arr_index < _DL_paths_capacity)
	{
		dlFreePath(arr_index);
	}
}

// 
// 

DLuint dlCreateBuffer (DLuint buf_size, DLuint buf_usize)
{
	struct DLBuffer _buffer;

	_buffer.buffer = calloc(_buffer.size, _buffer.usize);
	_buffer.size = buf_size;
	_buffer.usize = buf_usize;

	return DL_buffers_add(_buffer);
}

void dlFreeBuffer (DLuint buffer)
{
	struct DLBuffer* _buffer = &DL_buffers[buffer];

	free(_buffer->buffer);

	_DL_buffers_count--;
}

void dlBufferLoad (DLuint buffer, void* source)
{
	struct DLBuffer* _buffer = &DL_buffers[buffer];

	DLuint size = _buffer->size * _buffer->usize;

	// Clear the data in case the source is shorter than
	// buffer's capacity.
	memset(_buffer.buffer, 0, size);
	memcpy(_buffer.buffer, source, size);
}

// 
// 

DLuint dlCreateShader ()
{
	struct DLShader shader;

	shader.attrs.capacity = 0;
	shader.attrs.keys = NULL;
	shader.attrs.values = NULL;

	return DL_shaders_add(shader);
}

void dlFreeShader (DLuint shader)
{
	struct DLShader* _shader = &_DL_shaders[shader];

	DLuint loop_index = -1;

	while (++loop_index < _shader->attrs.capacity)
	{
		free(_shader->attrs.keys[loop_index]);
	}

	free(_shader->attrs.keys);
	free(_shader->attrs.values);

	_DL_shaders_count--;
}

// 

void dlInitShader (DLuint shader)
{
	struct DLShader* _shader = &_DL_shaders[shader];

	_shader->attrs.keys = calloc(_shader->attrs.capacity, sizeof(char*));
	_shader->attrs.values = calloc(_shader->attrs.capacity, sizeof(void*));
}

void dlShaderBindAttribID (DLuint shader, char* attrib_id, DLuint attrib_loc)
{
	DLuint attrib_id_len = strlen(attrib_id);

	struct DLShader* _shader = &_DL_shaders[shader];

	_shader->attrs.keys[attrib_loc] = malloc(attrib_id_len * sizeof(char));
	strcpy(_shader->attrs.keys[attrib_loc], attrib_id);
}

// 

DLuint dlShaderGetAttribLocation (DLuint shader, char* attrib_id)
{
	struct DLShader* _shader = &_DL_shaders[shader];

	DLuint loop_index = -1;

	while (++loop_index < _shader->attrs.capacity)
	{
		if (strcmp(_shader->attrs.keys[loop_index], attrib_id) == 0)
		{
			return loop_index;
		}
	}

	return -1;
}

void dlShaderBindAttrib (DLuint shader, DLuint attrib_loc, void* attrib_ptr)
{
	struct DLShader* _shader = &_DL_shaders[shader];

	_shader->attrs.values[attrib_loc] = attrib_ptr;
}

void dlApplyShader (DLuint shader, DLuint buffer)
{
	return;
}

// 
// 

DLuint dlCreatePath ()
{
	struct DLPath path;

	path.attrs.capacity = 0;
	path.attrs.keys = NULL;
	path.attrs.values = NULL;

	return DL_paths_add(path);
}

void dlFreePath (DLuint path)
{
	struct DLPath* _path = &_DL_paths[path];

	DLuint loop_index = -1;

	while (++loop_index < _path->attrs.capacity)
	{
		free(_path->attrs.keys[loop_index]);
	}

	free(_path->attrs.keys);
	free(_path->attrs.values);
	
	_DL_paths_count--;
}

// 

void dlInitPath (DLuint path)
{
	struct DLPath* _path = &_DL_paths[path];

	_path->attrs.keys = calloc(_path->attrs.capacity, sizeof(char*));
	_path->attrs.values = calloc(_path->attrs.capacity, sizeof(void*));
}

void dlPathBindAttribID (DLuint path, char* attrib_id, DLuint attrib_loc)
{
	DLuint attrib_id_len = strlen(attrib_id);

	struct DLPath* _path = &_DL_paths[path];

	_path->attrs.keys[attrib_loc] = malloc(attrib_id_len * sizeof(char));
	strcpy(_path->attrs.keys[attrib_loc], attrib_id);
}

// 

DLuint dlPathGetAttribLocation (DLuint path, char* attrib_id)
{
	struct DLPath* _path = &_DL_paths[path];

	DLuint loop_index = -1;

	while (++loop_index < _path->attrs.capacity)
	{
		if (strcmp(_path->attrs.keys[loop_index], attrib_id) == 0)
		{
			return loop_index;
		}
	}

	return -1;
}

void dlPathBindAttrib (DLuint path, DLuint attrib_loc, void* attrib_ptr)
{
	struct DLPath* _path = &_DL_paths[path];

	_path->attrs.values[attrib_loc] = attrib_ptr;
}

void dlApplyPath (DLuint path, DLuint buffer, void (*test_func)(struct DLAttrs* attrs, struct DLBuffer* buffer))
{
	struct DLPath* _path = &_DL_paths[path];
	struct DLBuffer* _buffer = &_DL_buffers[buffer];

	test_func(&_path->attrs, _buffer);
}
