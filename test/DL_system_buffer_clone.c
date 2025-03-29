#include <stdio.h>
#include <DL_public.h>

void debug_buffer (DLuint buffer)
{
	#include <DL_core.h>
	#include <DL_system.h>

	DLBuffer* _buffer = &DL_buffers[buffer];
	DLint* _buffer_data = (DLint*)(_buffer->data);

	printf("[%d, %d]\n", _buffer_data[0], _buffer_data[1]);
}

int main ()
{
	DLuint buffer1, buffer2, buffer3;
	DLuint buffer1_data[2] = { 10, 20 };

	dlInit();

	// Create Buffer
	buffer1 = dlCreateBuffer(DL_INT, 2);
	dlBufferData(buffer1, &buffer1_data, sizeof(buffer1_data));

	// Clone Buffer
	buffer2 = dlBufferClone(buffer1);

	// Copy Buffer
	buffer3 = dlCreateBuffer(DL_INT, 2);
	dlBufferCopy(buffer3, buffer1);

	printf("Buffer1: "); debug_buffer(buffer1);
	printf("Buffer2: "); debug_buffer(buffer2);
	printf("Buffer3: "); debug_buffer(buffer3);

	dlTerminate();
	return 0;
}