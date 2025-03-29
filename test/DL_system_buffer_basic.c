#include <stdio.h>
#include <DL_public.h>

void debug_buffer (DLuint buffer)
{
	#include <DL_core.h>
	#include <DL_system.h>

	DLBuffer* _buffer = &DL_buffers[buffer];

	printf("DLBuffer:\n");
	printf("\tCount Size: %d\n", _buffer->csize);
	printf("\tUnit Size: %d\n", _buffer->usize);
	printf("\tTotal Size: %d\n", _buffer->size);
	printf("\tSize in bytes: %d\n", sizeof(*_buffer));
}

int main ()
{
	DLuint buffer;
	DLuint buffer_data[4] = { 10, 20, 30, 40 };

	dlInit();

	buffer = dlCreateBuffer(DL_INT, 4);
	dlBufferData(buffer, &buffer_data, sizeof(buffer_data));

	debug_buffer(buffer);

	dlTerminate();
}