#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <DL.h>

struct DLBuffer* _DL_Buffers;
struct DLShader* _DL_Shaders;
struct DLPath*   _DL_Paths;

DLuint _DL_Buffers_count;
DLuint _DL_Shaders_count;
DLuint _DL_Paths_count;

DLuint _DL_Buffers_capacity;
DLuint _DL_Shaders_capacity;
DLuint _DL_Paths_capacity;

// 
// 

DLuint DL_buffers_add (struct DLBuffer buffer)
{
	DLuint location = -1;

	while (++location < _DL_Buffers_capacity)
	{
		if (_DL_Buffers[location].buffer == NULL)
		{
			break;
		}
	}

	if (location >= _DL_Buffers_capacity)
	{
		_DL_Buffers_capacity = _DL_Buffers_capacity * 2;
		_DL_Buffers = realloc(_DL_Buffers, _DL_Buffers_capacity * sizeof(struct DLBuffer));
	}

	_DL_Buffers_count++;
	_DL_Buffers[location] = buffer;

	return location;
}

DLuint DL_shaders_add (struct DLShader shader)
{
	DLuint location = -1;

	while (++location < _DL_Shaders_capacity)
	{
		if (_DL_Shaders[location].attrs.capacity == 0)
		{
			break;
		}
	}

	if (location >= _DL_Shaders_capacity)
	{
		_DL_Shaders_capacity = _DL_Shaders_capacity * 2;
		_DL_Shaders = realloc(_DL_Shaders, _DL_Shaders_capacity * sizeof(struct DLShader));
	}

	_DL_Shaders_count++;
	_DL_Shaders[location] = shader;

	return location;
}

DLuint DL_paths_add (struct DLPath path)
{
	DLuint location = -1;

	while (++location < _DL_Paths_capacity)
	{
		if (_DL_Paths[location].attrs.capacity == 0)
		{
			break;
		}
	}

	if (location >= _DL_Paths_capacity)
	{
		_DL_Paths_capacity = _DL_Paths_capacity * 2;
		_DL_Paths = realloc(_DL_Paths, _DL_Paths_capacity * sizeof(struct DLPath));
	}

	_DL_Paths_count++;
	_DL_Paths[location] = path;

	return location;
}

// 
// 

void DL_init ()
{
	_DL_Buffers_capacity = 16;
	_DL_Shaders_capacity = 16;
	_DL_Paths_capacity = 16;

	_DL_Buffers_count = 0;
	_DL_Shaders_count = 0;
	_DL_Paths_count = 0;

	_DL_Buffers = calloc(_DL_Buffers_capacity, sizeof(struct DLBuffer));
	_DL_Shaders = calloc(_DL_Shaders_capacity, sizeof(struct DLShader));
	_DL_Paths = calloc(_DL_Paths_capacity, sizeof(struct DLPath));
}

void DL_terminate ()
{
	DLuint arr_index;

	arr_index = -1;
	while (++arr_index < _DL_Buffers_capacity)
	{
		DL_buffer_free(arr_index);
	}

	arr_index = -1;
	while (++arr_index < _DL_Shaders_capacity)
	{
		DL_shader_free(arr_index);
	}

	arr_index = -1;
	while (++arr_index < _DL_Paths_capacity)
	{
		DL_path_free(arr_index);
	}
}

// 
// 

DLuint DL_buffer_generate (void* buffer, DLuint buf_size, DLuint buf_usize)
{
	struct DLBuffer _buffer;

	_buffer.buffer = buffer;
	_buffer.size = buf_size;
	_buffer.usize = buf_usize;

	buffer = calloc(_buffer.size, _buffer.usize);

	return DL_buffers_add(_buffer);
}

DLuint DL_buffer_bind (void* buffer, DLuint buf_size, DLuint buf_usize)
{
	struct DLBuffer _buffer;

	_buffer.buffer = buffer;
	_buffer.size = buf_size;
	_buffer.usize = buf_usize;

	return DL_buffers_add(_buffer);
}

void DL_buffer_free (DLuint buffer)
{
	return;
}

// 
// 

DLuint DL_shader_create ()
{
	struct DLShader shader;

	shader.attrs.capacity = 0;
	shader.attrs.keys = NULL;
	shader.attrs.values = NULL;

	return DL_shaders_add(shader);
}

void DL_shader_free (DLuint shader)
{
	struct DLShader* _shader = &_DL_Shaders[shader];

	DLuint loop_index = -1;

	while (++loop_index < _shader->attrs.capacity)
	{
		free(_shader->attrs.keys[loop_index]);
	}

	free(_shader->attrs.keys);
	free(_shader->attrs.values);
}

// 

void DL_shader_load (DLuint shader)
{
	struct DLShader* _shader = &_DL_Shaders[shader];

	_shader->attrs.keys = calloc(_shader->attrs.capacity, sizeof(char*));
	_shader->attrs.values = calloc(_shader->attrs.capacity, sizeof(void*));
}

void DL_shader_bindAttribId (DLuint shader, char* attrib_id, DLuint attrib_loc)
{
	DLuint attrib_id_len = strlen(attrib_id);

	struct DLShader* _shader = &_DL_Shaders[shader];

	_shader->attrs.keys[attrib_loc] = malloc(attrib_id_len * sizeof(char));
	strcpy(_shader->attrs.keys[attrib_loc], attrib_id);
}

// 

DLuint DL_shader_getAttribLocation (DLuint shader, char* attrib_id)
{
	struct DLShader* _shader = &_DL_Shaders[shader];

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

void DL_shader_bindAttrib (DLuint shader, DLuint attrib_loc, void* attrib_ptr)
{
	struct DLShader* _shader = &_DL_Shaders[shader];

	_shader->attrs.values[attrib_loc] = attrib_ptr;
}

void DL_shader_apply (DLuint shader, DLuint buffer)
{
	return;
}

// 
// 

DLuint DL_path_create ()
{
	struct DLPath path;

	path.attrs.capacity = 0;
	path.attrs.keys = NULL;
	path.attrs.values = NULL;

	return DL_paths_add(path);
}

void DL_path_free (DLuint path)
{
	struct DLPath* _path = &_DL_Paths[path];

	DLuint loop_index = -1;

	while (++loop_index < _path->attrs.capacity)
	{
		free(_path->attrs.keys[loop_index]);
	}

	free(_path->attrs.keys);
	free(_path->attrs.values);
}

// 

void DL_path_load (DLuint path)
{
	struct DLPath* _path = &_DL_Paths[path];

	_path->attrs.keys = calloc(_path->attrs.capacity, sizeof(char*));
	_path->attrs.values = calloc(_path->attrs.capacity, sizeof(void*));
}

void DL_path_bindAttribId (DLuint path, char* attrib_id, DLuint attrib_loc)
{
	DLuint attrib_id_len = strlen(attrib_id);

	struct DLPath* _path = &_DL_Paths[path];

	_path->attrs.keys[attrib_loc] = malloc(attrib_id_len * sizeof(char));
	strcpy(_path->attrs.keys[attrib_loc], attrib_id);
}

// 

DLuint DL_path_getAttribLocation (DLuint path, char* attrib_id)
{
	struct DLPath* _path = &_DL_Paths[path];

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

void DL_path_bindAttrib (DLuint path, DLuint attrib_loc, void* attrib_ptr)
{
	struct DLPath* _path = &_DL_Paths[path];

	_path->attrs.values[attrib_loc] = attrib_ptr;
}

void DL_path_apply (DLuint path, DLuint buffer)
{
	return;
}
