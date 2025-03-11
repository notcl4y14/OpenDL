#include <stdio.h>
#include <DL.h>

void print_buffer (DL_uint buffer);

int main ()
{
	printf("Initializing DL...\n\n");
	dlInit();

	printf("Creating 32x32 buffer...\n\n");
	DL_uint buffer1 = dlCreateBuffer(32, 32);

	print_buffer(buffer1);
	printf("\n");

	printf("Creating 512x512 buffer...\n\n");
	DL_uint buffer2 = dlCreateBuffer(512, 512);

	print_buffer(buffer2);
	printf("\n");

	printf("Freeing buffers...\n\n");
	dlFreeBuffer(buffer1);
	dlFreeBuffer(buffer2);

	print_buffer(buffer1);
	printf("\n");

	print_buffer(buffer2);
	printf("\n");

	printf("Terminating DL...\n\n");
	dlTerminate();

	printf("Done!\n");
	return 0;
}

void print_buffer (DL_uint buffer)
{
	DLBuffer* _buffer = dlGetBuffer(buffer);
	printf("Buffer (0x%x)\n", (unsigned int)_buffer);
	printf("- Dimensions: %dx%d\n", _buffer->width, _buffer->height);
	printf("- Area: %dB\n", _buffer->area);
	printf("- Data Size: %dB\n", _buffer->data_size);
	printf("- Pixel Size: %dB\n", _buffer->pixel_size);
}