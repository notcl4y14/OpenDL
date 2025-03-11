#include "DL.h"
#include <stdlib.h>
#include <stdarg.h>

#define _DL_DEFAULT_ARRAYS_CAPACITY 16

DL_uint __DL_bufferDefaultPixelSize;

DLBuffer* __DL_buffers_values;
DLShader* __DL_shaders_values;
DLPath* __DL_paths_values;

DL_uint __DL_buffers_count;
DL_uint __DL_shaders_count;
DL_uint __DL_paths_count;

DL_uint __DL_buffers_capacity = _DL_DEFAULT_ARRAYS_CAPACITY;
DL_uint __DL_shaders_capacity = _DL_DEFAULT_ARRAYS_CAPACITY;
DL_uint __DL_paths_capacity = _DL_DEFAULT_ARRAYS_CAPACITY;

// ====================== //
// ======== Util ======== //
// ====================== //

int buffer_getFirstAvailable ()
{
	int index = -1;

	while (++index < __DL_buffers_count)
	{
		if (__DL_buffers_values[index].data_size == 0)
		{
			return index;
		}
	}

	__DL_buffers_capacity = __DL_buffers_capacity * 2;
	__DL_buffers_values = realloc(__DL_buffers_values, __DL_buffers_capacity * sizeof(DLBuffer));

	return index;
}

int shader_getFirstAvailable ()
{
	int index = -1;

	while (++index < __DL_shaders_count)
	{
		if (__DL_shaders_values[index].code == NULL)
		{
			break;
		}
	}

	__DL_shaders_capacity = __DL_shaders_capacity * 2;
	__DL_shaders_values = realloc(__DL_shaders_values, __DL_shaders_capacity * sizeof(DLShader));

	return index;
}


int path_getFirstAvailable ()
{
	int index = -1;

	while (++index < __DL_paths_count)
	{
		if (__DL_paths_values[index].code == NULL)
		{
			break;
		}
	}

	__DL_paths_capacity = __DL_paths_capacity * 2;
	__DL_paths_values = realloc(__DL_paths_values, __DL_paths_capacity * sizeof(DLPath));

	return index;
}


// ==================== //
// ======== DL ======== //
// ==================== //

void dlInit ()
{
	__DL_bufferDefaultPixelSize = 1;

	__DL_buffers_values = calloc(__DL_buffers_capacity, sizeof(DLBuffer));
	__DL_shaders_values = calloc(__DL_shaders_capacity, sizeof(DLShader));
	__DL_paths_values = calloc(__DL_paths_capacity, sizeof(DLPath));

	__DL_buffers_count = 0;
	__DL_shaders_count = 0;
	__DL_paths_count = 0;
}

void dlTerminate ()
{
	__DL_buffers_count = 0;
	__DL_shaders_count = 0;
	__DL_paths_count = 0;

	free(__DL_buffers_values);
	free(__DL_shaders_values);
	free(__DL_paths_values);
}

void dlBufferDefaultPixelSize (DL_uint size)
{
	__DL_bufferDefaultPixelSize = size;
}

void dlInitialArraysCapacity (DL_uint size)
{
	__DL_buffers_capacity = size;
	__DL_shaders_capacity = size;
	__DL_paths_capacity = size;
}

void dlInitialBufferArrayCapacity (DL_uint size)
{
	__DL_buffers_capacity = size;
}

void dlInitialShaderArrayCapacity (DL_uint size)
{
	__DL_shaders_capacity = size;
}

void dlInitialPathArrayCapacity (DL_uint size)
{
	__DL_paths_capacity = size;
}

// ========================== //
// ======== DLBuffer ======== //
// ========================== //

DL_uint dlCreateBuffer (int width, int height)
{
	DLBuffer buffer;

	buffer.width = width;
	buffer.height = height;
	buffer.area = width * height;
	buffer.pixel_size = __DL_bufferDefaultPixelSize;
	buffer.data_size = buffer.area * buffer.pixel_size;
	buffer.data = calloc(buffer.data_size, sizeof(DL_uchar));

	int id = buffer_getFirstAvailable();
	__DL_buffers_values[id] = buffer;
	__DL_buffers_count++;

	return id;
}

DL_uint dlCreateBufferSize (int width, int height, int size)
{
	DLBuffer buffer;

	buffer.width = width;
	buffer.height = height;
	buffer.area = width * height;
	buffer.pixel_size = size;
	buffer.data_size = buffer.area * buffer.pixel_size;
	buffer.data = calloc(buffer.data_size, sizeof(DL_uchar));

	int id = buffer_getFirstAvailable();
	__DL_buffers_values[id] = buffer;
	__DL_buffers_count++;
	
	return id;
}

void dlFreeBuffer (DL_uint buffer)
{
	DLBuffer* _buffer = &__DL_buffers_values[buffer];
	free(_buffer->data);
	_buffer->width = 0;
	_buffer->height = 0;
	_buffer->area = 0;
	_buffer->data_size = 0;
	_buffer->pixel_size = 0;
	__DL_buffers_count--;
}

// ================================ //

DLBuffer* dlGetBuffer (DL_uint buffer)
{
	return &__DL_buffers_values[buffer];
}

// ================================ //

DL_uchar* dlBufferGetData (DL_uint buffer)
{
	return __DL_buffers_values[buffer].data;
}

int dlBufferGetWidth (DL_uint buffer)
{
	return __DL_buffers_values[buffer].width;
}

int dlBufferGetHeight (DL_uint buffer)
{
	return __DL_buffers_values[buffer].height;
}

int dlBufferGetArea (DL_uint buffer)
{
	return __DL_buffers_values[buffer].area;
}

int dlBufferGetDataSize (DL_uint buffer)
{
	return __DL_buffers_values[buffer].data_size;
}

int dlBufferGetPixelSize (DL_uint buffer)
{
	return __DL_buffers_values[buffer].pixel_size;
}

// ================================ //

void dlBufferSetDimensions (DL_uint buffer, int width, int height)
{
	DLBuffer* _buffer = &__DL_buffers_values[buffer];

	_buffer->width = width;
	_buffer->height = height;
	_buffer->area = width * height;
	_buffer->data_size = _buffer->area * _buffer->pixel_size;
	free(_buffer->data);
	_buffer->data = calloc(_buffer->data_size, sizeof(DL_uchar));
}

void dlBufferSetPixelSize (DL_uint buffer, int size)
{
	DLBuffer* _buffer = &__DL_buffers_values[buffer];

	_buffer->pixel_size = size;
	_buffer->data_size = _buffer->area * _buffer->pixel_size;
	_buffer->data = realloc(_buffer->data, _buffer->data_size * sizeof(DL_uchar));
}

// ================================ //

DL_uchar* dlBufferGetPixel (DL_uint buffer, int index, int step)
{
	DLBuffer* _buffer = &__DL_buffers_values[buffer];
	return &_buffer->data[index * _buffer->pixel_size + step];
}

DL_uchar* dlBufferGetPixelAt (DL_uint buffer, int x, int y, int step)
{
	DLBuffer* _buffer = &__DL_buffers_values[buffer];
	return &_buffer->data[(y * _buffer->width + x) * _buffer->pixel_size + step];
}

void dlBufferSetPixel (DL_uint buffer, int index, DL_uchar* value)
{
	DLBuffer* _buffer = &__DL_buffers_values[buffer];

	int i = -1;
	int pixelIndex = index * _buffer->pixel_size;

	while (++i < _buffer->pixel_size)
	{
		_buffer->data[pixelIndex + i] = value[i];
	}
}

void dlBufferSetPixelAt (DL_uint buffer, int x, int y, DL_uchar* value)
{
	DLBuffer* _buffer = &__DL_buffers_values[buffer];

	int i = -1;
	int pixelIndex = (y * _buffer->width + x) * _buffer->pixel_size;

	while (++i < _buffer->pixel_size)
	{
		_buffer->data[pixelIndex + i] = value[i];
	}
}

// ================================ //

DL_uint dlClipBuffer (DL_uint buffer, int x1, int y1, int x2, int y2)
{
	DLBuffer* _buffer = &__DL_buffers_values[buffer];
	// DLBuffer newBuffer = dlCreateBuffer(x2 - x1, y2 - y1);
	DLBuffer newBuffer;

	newBuffer.width = x2 - x1;
	newBuffer.height = y2 - y1;
	newBuffer.area = newBuffer.width * newBuffer.height;
	newBuffer.pixel_size = _buffer->pixel_size;
	newBuffer.data_size = newBuffer.area * newBuffer.pixel_size;
	newBuffer.data = calloc(newBuffer.data_size, sizeof(DL_uchar));

	int x = x1;
	int y = y1;

	while (x < x2)
	{
		while (y < y2)
		{
			DL_uchar* color = &_buffer->data[(y * _buffer->width + x) * _buffer->pixel_size];

			int pixelX = x - x1;
			int pixelY = y - y1;
			int index = (pixelY * newBuffer.width + pixelX) * _buffer->pixel_size;
		
			int j = -1;
			while (++j < newBuffer.pixel_size)
			{
				newBuffer.data[index + j] = color[j];
			}
			
			y++;
		}

		x++;
		y = y1;
	}

	int id = buffer_getFirstAvailable();
	__DL_buffers_values[id] = newBuffer;
	__DL_buffers_count++;
	
	return id;
}

void dlFillBuffer (DL_uint buffer, DL_uchar* color)
{
	DLBuffer* _buffer = &__DL_buffers_values[buffer];

	int index = -1;

	while (++index < _buffer->data_size)
	{
		_buffer->data[index] = color[index % _buffer->pixel_size];
	}
}

void dlDrawBuffer (DL_uint destBuffer, DL_uint srcBuffer, int x1, int y1, int x2, int y2)
{
	DLBuffer* _destBuffer = &__DL_buffers_values[destBuffer];
	DLBuffer* _srcBuffer = &__DL_buffers_values[srcBuffer];

	int width = x2 - x1;
	int height = y2 - y1;
	int area = width * height;

	float widthFraction = _srcBuffer->width / width;
	float heightFraction = _srcBuffer->height / height;

	int index = 0;

	while (index < area)
	{
		int x = index % width;
		int y = index / width;
		int pixelX = x * widthFraction;
		int pixelY = y * heightFraction;

		DL_uchar* color = &_srcBuffer->data[(pixelY * _srcBuffer->width + pixelX) * _srcBuffer->pixel_size];
		
		int rx = x + x1;
		int ry = y + y1;
		int ri = (ry * _destBuffer->width + rx) * _destBuffer->pixel_size;

		int color_index = -1;
		while (++color_index < _destBuffer->pixel_size)
		{
			_destBuffer->data[ri + color_index] = color[color_index];
		}
		
		index++;
	}
}

// ================================ //

void dlBufferApplyShader (DL_uint buffer, DL_uint shader)
{
	DLBuffer* _buffer = &__DL_buffers_values[buffer];
	DLShader* _shader = &__DL_shaders_values[shader];

	DLBuffer newBuffer = *_buffer;

	int index = -1;

	while (++index < _buffer->area)
	{
		int pixelIndex = index * _buffer->pixel_size;
		_shader->attrs.pixel_coord[0] = index % _buffer->width;
		_shader->attrs.pixel_coord[1] = index / _buffer->width;
		_shader->attrs.pixel_color = &newBuffer.data[pixelIndex];

		_shader->code(&_shader->attrs);
		
		int j = -1;

		while (++j < newBuffer.pixel_size)
		{
			_buffer->data[pixelIndex + j] = _shader->attrs.pixel_color[j];
		}
	}

	*_buffer = newBuffer;
}

void dlBufferApplyPath (DL_uint buffer, DL_uint path)
{
	DLBuffer* _buffer = &__DL_buffers_values[buffer];
	DLPath* _path = &__DL_paths_values[path];

	DLBuffer newBuffer = *_buffer;

	_path->attrs.buffer = &newBuffer;
	_path->code(&_path->attrs);

	*_buffer = newBuffer;
}

// ========================== //
// ======== DLShader ======== //
// ========================== //

DL_uint dlCreateShader ()
{
	DLShader shader;
	
	shader.code = NULL;
	shader.attrs.pixel_color = NULL;
	shader.attrs.pixel_coord[0] = 0;
	shader.attrs.pixel_coord[1] = 0;

	shader.attrs.attrs_count = 0;
	shader.attrs.attrs_keys = NULL;
	shader.attrs.attrs_values = NULL;

	int id = shader_getFirstAvailable();
	__DL_shaders_values[id] = shader;
	__DL_shaders_count++;
	
	return id;
}

void dlFreeShader (DL_uint shader)
{
	DLShader* _shader = &__DL_shaders_values[shader];
	_shader->code = NULL;
	free(_shader->attrs.pixel_color);
	_shader->attrs.pixel_color = NULL;
	_shader->attrs.pixel_coord[0] = 0;
	_shader->attrs.pixel_coord[1] = 0;
	_shader->attrs.attrs_count = 0;
	free(_shader->attrs.attrs_keys);
	free(_shader->attrs.attrs_values);
	_shader->attrs.attrs_keys = NULL;
	_shader->attrs.attrs_values = NULL;
	__DL_shaders_count--;
}

// ================================ //

DLShader* dlGetShader (DL_uint shader)
{
	return &__DL_shaders_values[shader];
}

// ================================ //

DLShaderAttrs* dlShaderGetAttrs (DL_uint shader)
{
	return &__DL_shaders_values[shader].attrs;
}

// ================================ //

void dlShaderInit (DL_uint shader, int count)
{
	DLShader* _shader = &__DL_shaders_values[shader];
	_shader->attrs.attrs_count = count;
	_shader->attrs.attrs_keys = calloc(count, sizeof(char*));
	_shader->attrs.attrs_values = calloc(count, sizeof(void*));
}

void dlShaderBindAttrib (DL_uint shader, char* id, int index)
{
	DLShader* _shader = &__DL_shaders_values[shader];
	_shader->attrs.attrs_keys[index] = id;
}

// ================================ //

void dlShaderBindCode (DL_uint shader, void (*code) (DLShaderAttrs*))
{
	DLShader* _shader = &__DL_shaders_values[shader];
	_shader->code = code;
}

// ================================ //

void dlSetShaderAttrib (DL_uint shader, int index, void* value)
{
	DLShader* _shader = &__DL_shaders_values[shader];
	_shader->attrs.attrs_values[index] = value;
}

// ================================ //

void dlSetShaderAttribID (DL_uint shader, char* id, void* value)
{
	DLShader* _shader = &__DL_shaders_values[shader];

	int index = 0;

	while (index < _shader->attrs.attrs_count)
	{
		if (_shader->attrs.attrs_keys[index] == id)
		{
			break;
		}

		index++;
	}

	_shader->attrs.attrs_values[index] = value;
}

void* dlGetShaderAttrib (DL_uint shader, int index)
{
	DLShader* _shader = &__DL_shaders_values[shader];
	return &_shader->attrs.attrs_values[index];
}

void* dlGetShaderAttribID (DL_uint shader, char* id)
{
	DLShader* _shader = &__DL_shaders_values[shader];

	int index = 0;

	while (index < _shader->attrs.attrs_count)
	{
		if (_shader->attrs.attrs_keys[index] == id)
		{
			break;
		}

		index++;
	}

	return &_shader->attrs.attrs_values[index];
}

// ======================== //
// ======== DLPath ======== //
// ======================== //

DL_uint dlCreatePath ()
{
	DLPath path;

	path.code = NULL;
	path.attrs.buffer = NULL;

	int id = path_getFirstAvailable();
	__DL_paths_values[id] = path;
	__DL_paths_count++;
	
	return id;
}

void dlFreePath (DL_uint path)
{
	DLPath* _path = &__DL_paths_values[path];
	_path->attrs.buffer = NULL;
	_path->attrs.attrs_count = 0;
	free(_path->attrs.attrs_keys);
	free(_path->attrs.attrs_values);
	_path->attrs.attrs_keys = NULL;
	_path->attrs.attrs_values = NULL;
	__DL_paths_count--;
}

// ================================ //

DLPath* dlGetPath (DL_uint path)
{
	return &__DL_paths_values[path];
}

// ================================ //

DLPathAttrs* dlPathGetAttrs (DL_uint path)
{
	return &__DL_paths_values[path].attrs;
}

// ================================ //

void dlPathInit (DL_uint path, int count)
{
	DLPath* _path = &__DL_paths_values[path];
	_path->attrs.attrs_count = count;
	_path->attrs.attrs_keys = calloc(count, sizeof(char*));
	_path->attrs.attrs_values = calloc(count, sizeof(void*));
}

void dlPathBindAttrib (DL_uint path, char* id, int index)
{
	DLPath* _path = &__DL_paths_values[path];
	_path->attrs.attrs_keys[index] = id;
}

// ================================ //

void dlPathBindCode (DL_uint path, void (*code) (DLPathAttrs*))
{
	DLPath* _path = &__DL_paths_values[path];
	_path->code = code;
}

// ================================ //

void dlSetPathAttrib (DL_uint path, int index, void* value)
{
	DLPath* _path = &__DL_paths_values[path];
	_path->attrs.attrs_values[index] = value;
}

void dlSetPathAttribID (DL_uint path, char* id, void* value)
{
	DLPath* _path = &__DL_paths_values[path];

	int index = 0;

	while (index < _path->attrs.attrs_count)
	{
		if (_path->attrs.attrs_keys[index] == id)
		{
			break;
		}

		index++;
	}

	_path->attrs.attrs_values[index] = value;
}

void* dlGetPathAttrib (DL_uint path, int index)
{
	DLPath* _path = &__DL_paths_values[path];
	return &_path->attrs.attrs_values[index];
}

void* dlGetPathAttribID (DL_uint path, char* id)
{
	DLPath* _path = &__DL_paths_values[path];

	int index = 0;

	while (index < _path->attrs.attrs_count)
	{
		if (_path->attrs.attrs_keys[index] == id)
		{
			break;
		}

		index++;
	}

	return &_path->attrs.attrs_values[index];
}