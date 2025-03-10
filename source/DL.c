#include "DL.h"
#include <stdlib.h>
#include <stdarg.h>

DL_uint __DL_bufferDefaultPixelSize;

DLBuffer* __DL_buffers_values;
DLShader* __DL_shaders_values;
DLPath* __DL_paths_values;

DL_uint __DL_buffers_count;
DL_uint __DL_shaders_count;
DL_uint __DL_paths_count;

// TODO: Rework this feature
DL_uint* __DL_buffers_firstAvailable_values;
DL_uint* __DL_shaders_firstAvailable_values;
DL_uint* __DL_paths_firstAvailable_values;

DL_uint __DL_buffers_firstAvailable_count;
DL_uint __DL_shaders_firstAvailable_count;
DL_uint __DL_paths_firstAvailable_count;

DL_uint __DL_buffers_capacity;
DL_uint __DL_shaders_capacity;
DL_uint __DL_paths_capacity;

// ====================== //
// ======== Util ======== //
// ====================== //

void array_shift (char* array, int length)
{
	for (int i = 0; i < length - 1; i++)
	{
		array[i] = array[i + 1];
	}
}

// void array_push (void* array, void* value, int* count, int* capacity, int size)
// {
// 	if (count <= capacity)
// 	{
// 		*capacity = *capacity * 2;
// 		array = realloc(array, capacity * size);
// 	}

// 	array[*count++] = value;
// }

void buffers_firstAvailable_push (DL_uint buffer)
{
	if (__DL_buffers_firstAvailable_count <= __DL_buffers_capacity)
	{
		__DL_buffers_capacity = __DL_buffers_capacity * 2;

		__DL_buffers_values = realloc(
			__DL_buffers_values,
			__DL_buffers_capacity * sizeof(DLBuffer)
		);

		__DL_buffers_firstAvailable_values = realloc(
			__DL_buffers_firstAvailable_values,
			__DL_buffers_capacity * sizeof(DL_uint)
		);
	}

	__DL_buffers_firstAvailable_values[__DL_buffers_firstAvailable_count++] = buffer;
}

void shaders_firstAvailable_push (DL_uint shader)
{
	if (__DL_shaders_firstAvailable_count <= __DL_shaders_capacity)
	{
		__DL_shaders_capacity = __DL_shaders_capacity * 2;

		__DL_shaders_values = realloc(
			__DL_shaders_values,
			__DL_shaders_capacity * sizeof(DLShader)
		);

		__DL_buffers_firstAvailable_values = realloc(
			__DL_buffers_firstAvailable_values,
			__DL_shaders_capacity * sizeof(DL_uint)
		);
	}

	__DL_buffers_firstAvailable_values[__DL_shaders_firstAvailable_count++] = shader;
}

void paths_firstAvailable_push (DL_uint path)
{
	if (__DL_paths_firstAvailable_count <= __DL_paths_capacity)
	{
		__DL_paths_capacity = __DL_paths_capacity * 2;

		__DL_paths_values = realloc(
			__DL_paths_values,
			__DL_paths_capacity * sizeof(DLPath)
		);

		__DL_buffers_firstAvailable_values = realloc(
			__DL_buffers_firstAvailable_values,
			__DL_paths_capacity * sizeof(DL_uint)
		);
	}

	__DL_buffers_firstAvailable_values[__DL_paths_firstAvailable_count++] = path;
}

// ==================== //
// ======== DL ======== //
// ==================== //

void dlInit ()
{
	__DL_bufferDefaultPixelSize = 1;

	__DL_buffers_values = calloc(16, sizeof(DLBuffer));
	__DL_shaders_values = calloc(16, sizeof(DLBuffer));
	__DL_paths_values = calloc(16, sizeof(DLBuffer));

	__DL_buffers_count = 0;
	__DL_shaders_count = 0;
	__DL_paths_count = 0;

	__DL_buffers_firstAvailable_values = calloc(16, sizeof(DL_uint));
	__DL_shaders_firstAvailable_values = calloc(16, sizeof(DL_uint));
	__DL_paths_firstAvailable_values = calloc(16, sizeof(DL_uint));

	__DL_buffers_firstAvailable_count = 0;
	__DL_shaders_firstAvailable_count = 0;
	__DL_paths_firstAvailable_count = 0;

	__DL_buffers_capacity = 16;
	__DL_shaders_capacity = 16;
	__DL_paths_capacity = 16;
}

void dlTerminate ()
{
	__DL_buffers_count = 0;
	__DL_shaders_count = 0;
	__DL_paths_count = 0;

	free(__DL_buffers_firstAvailable_values);
	free(__DL_shaders_firstAvailable_values);
	free(__DL_paths_firstAvailable_values);

	__DL_buffers_firstAvailable_count = 0;
	__DL_shaders_firstAvailable_count = 0;
	__DL_paths_firstAvailable_count = 0;

	free(__DL_buffers_values);
	free(__DL_shaders_values);
	free(__DL_paths_values);
}

void dlBufferDefaultPixelSize (DL_uint size)
{
	__DL_bufferDefaultPixelSize = size;
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

	int id = __DL_buffers_firstAvailable_values[0];
	__DL_buffers_count++;

	array_shift((char*)__DL_buffers_firstAvailable_values, __DL_buffers_capacity);
	buffers_firstAvailable_push(__DL_buffers_count);

	__DL_buffers_values[id] = buffer;

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

	int id = __DL_buffers_firstAvailable_values[0];
	__DL_buffers_count++;

	array_shift((char*)__DL_buffers_firstAvailable_values, __DL_buffers_capacity);
	buffers_firstAvailable_push(__DL_buffers_count);

	__DL_buffers_values[id] = buffer;
	
	return id;
}

void dlFreeBuffer (DL_uint buffer)
{
	DLBuffer* _buffer = &__DL_buffers_values[buffer];
	__DL_buffers_count--;
	buffers_firstAvailable_push(buffer);
	free(_buffer->data);
}

// ================================ //

DLBuffer* dlGetBuffer (DL_uint buffer)
{
	return &__DL_buffers_values[buffer];
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

void dlSetBufferDimensions (DL_uint buffer, int width, int height)
{
	DLBuffer* _buffer = &__DL_buffers_values[buffer];

	_buffer->width = width;
	_buffer->height = height;
	_buffer->area = width * height;
	_buffer->data_size = _buffer->area * _buffer->pixel_size;
	free(_buffer->data);
	_buffer->data = calloc(_buffer->data_size, sizeof(DL_uchar));
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

	int id = __DL_buffers_firstAvailable_values[0];
	__DL_buffers_count++;

	array_shift((char*)__DL_buffers_firstAvailable_values, __DL_buffers_capacity);
	buffers_firstAvailable_push(__DL_buffers_count);

	__DL_buffers_values[id] = newBuffer;
	
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
		_shader->attrs.Dl_positionX = index % _buffer->width;
		_shader->attrs.Dl_positionY = index / _buffer->width;
		_shader->attrs.Dl_color = &newBuffer.data[pixelIndex];

		_shader->code(&_shader->attrs);
		
		int j = -1;

		while (++j < newBuffer.pixel_size)
		{
			_buffer->data[pixelIndex + j] = _shader->attrs.Dl_color[j];
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
	shader.attrs.Dl_color = NULL;
	shader.attrs.Dl_positionX = 0;
	shader.attrs.Dl_positionY = 0;

	shader.attrs.count = 0;
	shader.attrs.attrs_keys = NULL;
	shader.attrs.attrs_values = NULL;

	int id = __DL_shaders_firstAvailable_values[0];
	__DL_shaders_count++;

	array_shift((char*)__DL_shaders_firstAvailable_values, __DL_shaders_capacity);
	shaders_firstAvailable_push(__DL_shaders_count);

	__DL_shaders_values[id] = shader;
	
	return id;
}

void dlFreeShader (DL_uint shader)
{
	DLShader* _shader = &__DL_shaders_values[shader];
	__DL_shaders_count--;
	shaders_firstAvailable_push(shader);
	free(_shader->attrs.Dl_color);
	free(_shader->attrs.attrs_keys);
	free(_shader->attrs.attrs_values);
}

DLShader* dlGetShader (DL_uint shader)
{
	return &__DL_shaders_values[shader];
}

void dlShaderInit (DL_uint shader, int count)
{
	DLShader* _shader = &__DL_shaders_values[shader];
	_shader->attrs.count = count;
	_shader->attrs.attrs_keys = calloc(count, sizeof(char*));
	_shader->attrs.attrs_values = calloc(count, sizeof(void*));
}

void dlShaderBindCode (DL_uint shader, void (*code) (DLShaderAttrs*))
{
	DLShader* _shader = &__DL_shaders_values[shader];
	_shader->code = code;
}

void dlShaderBindAttrib (DL_uint shader, char* id, int index)
{
	DLShader* _shader = &__DL_shaders_values[shader];
	_shader->attrs.attrs_keys[index] = id;
}

void dlSetShaderAttrib (DL_uint shader, int index, void* value)
{
	DLShader* _shader = &__DL_shaders_values[shader];
	_shader->attrs.attrs_values[index] = value;
}

void dlSetShaderAttribID (DL_uint shader, char* id, void* value)
{
	DLShader* _shader = &__DL_shaders_values[shader];

	int index = 0;

	while (index < _shader->attrs.count)
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

	while (index < _shader->attrs.count)
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

	int id = __DL_paths_firstAvailable_values[0];
	__DL_paths_count++;

	array_shift((char*)__DL_paths_firstAvailable_values, __DL_paths_capacity);
	paths_firstAvailable_push(__DL_paths_count);

	__DL_paths_values[id] = path;
	
	return id;
}

void dlFreePath (DL_uint path)
{
	DLPath* _path = &__DL_paths_values[path];
	__DL_paths_count--;
	paths_firstAvailable_push(path);
	free(_path->attrs.attrs_keys);
	free(_path->attrs.attrs_values);
}

DLPath* dlGetPath (DL_uint path)
{
	return &__DL_paths_values[path];
}

void dlPathInit (DL_uint path, int count)
{
	DLPath* _path = &__DL_paths_values[path];
	_path->attrs.count = count;
	_path->attrs.attrs_keys = calloc(count, sizeof(char*));
	_path->attrs.attrs_values = calloc(count, sizeof(void*));
}

void dlPathBindCode (DL_uint path, void (*code) (DLPathAttrs*))
{
	DLPath* _path = &__DL_paths_values[path];
	_path->code = code;
}

void dlPathBindAttrib (DL_uint path, char* id, int index)
{
	DLPath* _path = &__DL_paths_values[path];
	_path->attrs.attrs_keys[index] = id;
}

void dlSetPathAttrib (DL_uint path, int index, void* value)
{
	DLPath* _path = &__DL_paths_values[path];
	_path->attrs.attrs_values[index] = value;
}

void dlSetPathAttribID (DL_uint path, char* id, void* value)
{
	DLPath* _path = &__DL_paths_values[path];

	int index = 0;

	while (index < _path->attrs.count)
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

	while (index < _path->attrs.count)
	{
		if (_path->attrs.attrs_keys[index] == id)
		{
			break;
		}

		index++;
	}

	return &_path->attrs.attrs_values[index];
}