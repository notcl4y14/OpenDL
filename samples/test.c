#include <stdio.h>
#include <DL.h>

int main ()
{
	printf("Initializing DL...\n\n");
	dlInit();
	printf("__DL_buffers_count: %d\n", __DL_buffers_count);
	printf("__DL_buffers_firstAvailable_count: %d\n", __DL_buffers_firstAvailable_count);
	printf("__DL_buffers_firstAvailable_values[0]: %d\n", __DL_buffers_firstAvailable_values[0]);
	printf("__DL_buffers_count: %d\n\n", __DL_buffers_count);

	printf("Creating 32x32 buffer...\n\n");
	DL_uint buffer = dlCreateBuffer(32, 32);

	DLBuffer* _buffer = dlGetBuffer(buffer);
	printf("__DL_buffers_count: %d\n", __DL_buffers_count);
	printf("__DL_buffers_firstAvailable_count: %d\n", __DL_buffers_firstAvailable_count);
	printf("__DL_buffers_firstAvailable_values[0]: %d\n", __DL_buffers_firstAvailable_values[0]);

	printf("__DL_buffers_count: %d\n", __DL_buffers_count);
	printf("buffer.width: %d\n", _buffer->width);
	printf("buffer.height: %d\n\n", _buffer->height);

	printf("Freeing buffer...\n\n");
	dlFreeBuffer(buffer);

	printf("__DL_buffers_count: %d\n", __DL_buffers_count);
	printf("__DL_buffers_firstAvailable_count: %d\n", __DL_buffers_firstAvailable_count);
	printf("__DL_buffers_firstAvailable_values[0]: %d\n", __DL_buffers_firstAvailable_values[0]);

	printf("__DL_buffers_count: %d\n", __DL_buffers_count);
	printf("buffer.width: %d\n", _buffer->width);
	printf("buffer.height: %d\n\n", _buffer->height);

	printf("Terminating DL...\n\n");
	dlTerminate();

	printf("__DL_buffers_count: %d\n", __DL_buffers_count);
	printf("__DL_buffers_firstAvailable_count: %d\n", __DL_buffers_firstAvailable_count);
	printf("__DL_buffers_firstAvailable_values[0]: %d\n", __DL_buffers_firstAvailable_values[0]);

	printf("__DL_buffers_count: %d\n", __DL_buffers_count);
	printf("buffer.width: %d\n", _buffer->width);
	printf("buffer.height: %d\n\n", _buffer->height);

	printf("Done!\n");
	return 0;
}