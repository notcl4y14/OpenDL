#include <stdlib.h>
#include <string.h>

#include <DL.h>

// 
// 

struct DLBuffer* DLarray_buffers;
struct DLShader* DLarray_shaders;
struct DLPath* DLarray_paths;

size_dl DLarray_buffers_capacity;
size_dl DLarray_shaders_capacity;
size_dl DLarray_paths_capacity;

size_dl DLarray_buffers_count;
size_dl DLarray_shaders_count;
size_dl DLarray_paths_count;

// 
// 

loc_dl DL_arrayBufferAdd (struct DLBuffer buffer)
{
	loc_dl location = -1;

	while (++location < DLarray_buffers_capacity)
	{
		if (DLarray_buffers[location].data == NULL)
		{
			DLarray_buffers[location] = buffer;
			DLarray_buffers_count++;
			return location;
		}
	}

	// Reallocate
	DLarray_buffers_capacity *= 2;
	DLarray_buffers = realloc(DLarray_buffers, DLarray_buffers_capacity);
	DLarray_buffers[location] = buffer;
	DLarray_buffers_count++;

	return location;
}

loc_dl DL_arrayShaderAdd (struct DLShader shader)
{
	loc_dl location = -1;

	while (++location < DLarray_shaders_capacity)
	{
		if (DLarray_shaders[location].attrs.data == NULL)
		{
			DLarray_shaders[location] = shader;
			DLarray_shaders_count++;
			return location;
		}
	}

	// Reallocate
	DLarray_shaders_capacity *= 2;
	DLarray_shaders = realloc(DLarray_shaders, DLarray_shaders_capacity);

	DLarray_shaders[location] = shader;
	DLarray_shaders_count++;

	return location;
}

loc_dl DL_arrayPathAdd (struct DLPath path)
{
	loc_dl location = -1;

	while (++location < DLarray_paths_capacity)
	{
		if (DLarray_paths[location].attrs.data == NULL)
		{
			DLarray_paths_count++;
			DLarray_paths[location] = path;
			return location;
		}
	}

	// Reallocate
	DLarray_paths_capacity *= 2;
	DLarray_paths = realloc(DLarray_paths, DLarray_paths_capacity);

	DLarray_paths[location] = path;
	DLarray_paths_count++;

	return location;
}

// 

struct DLBuffer* DL_arrayBufferGet (loc_dl location)
{
	return &DLarray_buffers[location];
}

struct DLShader* DL_arrayShaderGet (loc_dl location)
{
	return &DLarray_shaders[location];
}

struct DLPath* DL_arrayPathGet (loc_dl location)
{
	return &DLarray_paths[location];
}

// 
// 

struct DLBuffer DL_createBuffer (size_dl size, size_dl usize)
{
	struct DLBuffer buffer;

	buffer.data = calloc(size, usize);
	buffer.size = size;
	buffer.usize = usize;

	return buffer;
}

void DL_freeBuffer (struct DLBuffer* buffer)
{
	free(buffer->data);
}

// 

void DL_bufferGetData (struct DLBuffer* buffer, void* to)
{
	memcpy(to, buffer->data, buffer->size * buffer->usize);
}

void DL_bufferLoadData (struct DLBuffer* buffer, void* data)
{
	memset(buffer->data, 0, buffer->size * buffer->usize);
	memcpy(buffer->data, data, buffer->size * buffer->usize);
}

// 
// 

struct DLAttrs DL_createAttrs (size_dl capacity)
{
	struct DLAttrs attrs;

	attrs.data = calloc(capacity, sizeof(void*));
	attrs.keys = calloc(capacity, sizeof(char*));
	attrs.capacity = capacity;

	return attrs;
}

void DL_freeAttrs (struct DLAttrs* attrs)
{
	loc_dl loop_index = -1;

	while (++loop_index < attrs->capacity)
	{
		char* key = attrs->keys[loop_index];

		if (key == NULL)
		{
			continue;
		}

		free(attrs->keys[loop_index]);
	}

	free(attrs->data);
	free(attrs->keys);
}

// 

loc_dl DL_getAttribLocation (struct DLAttrs* attrs, char* key)
{
	loc_dl loop_index = -1;

	while (++loop_index < attrs->capacity)
	{
		if (strcmp(attrs->keys[loop_index], key) == 0)
		{
			return loop_index;
		}
	}

	return -1;
}

void DL_bindAttribLocation (struct DLAttrs* attrs, loc_dl location, char* key)
{
	size_dl key_len = strlen(key);
	attrs->keys[location] = malloc(key_len);
	strcpy(attrs->keys[location], key);
}

void DL_bindAttribPointer (struct DLAttrs* attrs, loc_dl location, void* pointer)
{
	attrs->data[location] = pointer;
}

// 
// 

struct DLShader DL_createShader ()
{
	struct DLShader shader;

	shader.attrs.data = NULL;
	shader.attrs.keys = NULL;
	shader.attrs.capacity = 0;

	return shader;
}

void DL_freeShader (struct DLShader* shader)
{
	DL_freeAttrs(&shader->attrs);
}

// 
// 

struct DLPath DL_createPath ()
{
	struct DLPath path;

	path.attrs.data = NULL;
	path.attrs.keys = NULL;
	path.attrs.capacity = 0;

	return path;
}

void DL_freePath (struct DLPath* path)
{
	DL_freeAttrs(&path->attrs);
}

// 
// 

// 
// 

void dlInit ()
{
	DLarray_buffers_capacity = 16;
	DLarray_shaders_capacity = 16;
	DLarray_paths_capacity = 16;

	DLarray_buffers_count = 0;
	DLarray_shaders_count = 0;
	DLarray_paths_count = 0;

	DLarray_buffers = calloc(DLarray_buffers_capacity, sizeof(struct DLBuffer));
	DLarray_shaders = calloc(DLarray_shaders_capacity, sizeof(struct DLShader));
	DLarray_paths = calloc(DLarray_paths_capacity, sizeof(struct DLPath));
}

void dlTerminate ()
{
	loc_dl location;

	location = -1;

	while (++location < DLarray_buffers_capacity)
	{
		if (DLarray_buffers[location].data != NULL)
		{
			DL_freeBuffer(DL_arrayBufferGet(location));
		}
	}

	location = -1;

	while (++location < DLarray_shaders_capacity)
	{
		if (DLarray_shaders[location].attrs.data != NULL)
		{
			DL_freeShader(DL_arrayShaderGet(location));
		}
	}

	location = -1;

	while (++location < DLarray_paths_capacity)
	{
		if (DLarray_paths[location].attrs.data != NULL)
		{
			DL_freePath(DL_arrayPathGet(location));
		}
	}

	free(DLarray_buffers);
	free(DLarray_shaders);
	free(DLarray_paths);
}

// 
// 

loc_dl dlCreateBuffer (size_dl size, size_dl usize)
{
	struct DLBuffer buffer = DL_createBuffer(size, usize);
	return DL_arrayBufferAdd(buffer);
}

void dlFreeBuffer (loc_dl buffer)
{
	DL_freeBuffer(DL_arrayBufferGet(buffer));
}

// 

void dlBufferGetData (loc_dl buffer, void* to)
{
	DL_bufferGetData(DL_arrayBufferGet(buffer), to);
}

void dlBufferLoadData (loc_dl buffer, void* data)
{
	DL_bufferLoadData(DL_arrayBufferGet(buffer), data);
}

// 
// 

loc_dl dlCreateShader ()
{
	struct DLShader shader = DL_createShader();
	return DL_arrayShaderAdd(shader);
}

void dlFreeShader (loc_dl shader)
{
	DL_freeShader(DL_arrayShaderGet(shader));
}

// 

loc_dl dlShaderGetAttribLocation (loc_dl shader, char* key)
{
	return DL_getAttribLocation(&DL_arrayShaderGet(shader)->attrs, key);
}

void dlShaderBindAttribLocation (loc_dl shader, loc_dl location, char* key)
{
	DL_bindAttribLocation(&DL_arrayShaderGet(shader)->attrs, location, key);
}

void dlShaderBindAttribPointer (loc_dl shader, loc_dl location, void* pointer)
{
	DL_bindAttribPointer(&DL_arrayShaderGet(shader)->attrs, location, pointer);
}

// 
// 

loc_dl dlCreatePath ()
{
	struct DLPath path = DL_createPath();
	return DL_arrayPathAdd(path);
}

void dlFreePath (loc_dl path)
{
	DL_freePath(DL_arrayPathGet(path));
}

// 

loc_dl dlPathGetAttribLocation (loc_dl path, char* key)
{
	return DL_getAttribLocation(&DL_arrayPathGet(path)->attrs, key);
}

void dlPathBindAttribLocation (loc_dl path, loc_dl location, char* key)
{
	DL_bindAttribLocation(&DL_arrayPathGet(path)->attrs, location, key);
}

void dlPathBindAttribPointer (loc_dl path, loc_dl location, void* pointer)
{
	DL_bindAttribPointer(&DL_arrayPathGet(path)->attrs, location, pointer);
}