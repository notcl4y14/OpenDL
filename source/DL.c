#include "DL.h"
#include <stdlib.h>
#include <stdarg.h>

void Dl_Init ()
{
	__Dl_DefaultPixelSize = 1;
}

void Dl_SetDefaultPixelSize (unsigned int size)
{
	__Dl_DefaultPixelSize = size;
}

// ========================== //
// ======== DlBuffer ======== //
// ========================== //

DlBuffer Dl_CreateBuffer (int width, int height)
{
	DlBuffer buffer;

	buffer.width = width;
	buffer.height = height;
	buffer.area = width * height;
	buffer.size = __Dl_DefaultPixelSize;
	buffer.count = buffer.area * buffer.size;
	buffer.data = (DL_UChar*)calloc(buffer.count, sizeof(DL_UChar));

	return buffer;
}

void Dl_FreeBuffer (DlBuffer* buffer)
{
	free(buffer->data);
}

// ================================ //

DL_UChar Dl_BufferGetPixel (DlBuffer* buffer, int index, int step)
{
	return buffer->data[index * buffer->size + step];
}

DL_UChar Dl_BufferGetPixelAt (DlBuffer* buffer, int x, int y, int step)
{
	return Dl_BufferGetPixel(buffer, y * buffer->width + x, step);
}

void Dl_BufferSetPixel (DlBuffer* buffer, int index, ...)
{
	va_list args;
	va_start(args, index);

	int i = -1;

	while (++i < buffer->size)
	{
		buffer->data[index + i] = va_arg(args, int);
	}

	va_end(args);
}

void Dl_BufferSetPixelAt (DlBuffer* buffer, int x, int y, ...)
{
	va_list args;
	va_start(args, y);

	int index = y * buffer->width + x;

	int i = -1;

	while (++i < buffer->size)
	{
		buffer->data[index + i] = va_arg(args, int);
	}

	va_end(args);
}

// ================================ //

void Dl_SetBufferSize (DlBuffer* buffer, int width, int height)
{
	buffer->width = width;
	buffer->height = height;
	buffer->area = width * height;
	buffer->count = buffer->area * buffer->size;
	free(buffer->data);
	buffer->data = (DL_UChar*)calloc(buffer->count, sizeof(DL_UChar));
}

// ================================ //

void Dl_FillBuffer (DlBuffer* buffer, ...)
{
	va_list args;
	va_start(args, buffer);

	int index = -1;

	while (++index < buffer->count)
	{
		if (index % buffer->size == 0)
		{
			va_end(args);
			va_start(args, buffer);
		}

		buffer->data[index] = va_arg(args, int);
	}

	va_end(args);
}