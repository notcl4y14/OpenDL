#include "DL.h"
#include <stdlib.h>
#include <stdarg.h>

void DL_Init ()
{
	return;
}

// ========================== //
// ======== DlBuffer ======== //
// ========================== //

DlBuffer Dl_CreateBuffer (int area, int size)
{
	DlBuffer buffer;

	buffer.area = area;
	buffer.size = size;
	buffer.count = area * size;
	buffer.data = (DL_UChar*)calloc(buffer.count, sizeof(DL_UChar));

	return buffer;
}

void Dl_FreeBuffer (DlBuffer* buffer)
{
	free(buffer->data);
}

// ================================ //

DL_UChar Dl_BufferGet (DlBuffer* buffer, int index, int step)
{
	return buffer->data[index * buffer->size + step];
}

void Dl_BufferSet (DlBuffer* buffer, int index, int values, ...)
{
	va_list args;
	va_start(args, values);

	int i = -1;

	while (++i < buffer->size)
	{
		buffer->data[index + i] = va_arg(args, int);
	}

	va_end(args);
}

// ================================ //

void Dl_SetBufferArea (DlBuffer* buffer, int area)
{
	buffer->area = area;
	buffer->count = buffer->area * buffer->size;
	free(buffer->data);
	buffer->data = (DL_UChar*)calloc(buffer->count, sizeof(DL_UChar));
}

// ================================ //

void Dl_FillBuffer (DlBuffer* buffer, int values, ...)
{
	va_list args;
	va_start(args, values);

	int index = -1;

	while (++index < buffer->count)
	{
		if (index % buffer->size == 0)
		{
			va_end(args);
			va_start(args, values);
		}

		buffer->data[index] = va_arg(args, int);
	}

	va_end(args);
}