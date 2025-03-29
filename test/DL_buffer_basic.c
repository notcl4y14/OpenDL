#include <stdio.h>
#include <DL_system.h>
#include <DL_core.h>

void debug_arr (DLBuffer* buffer)
{
	printf("[");

	for (DLint i = 0; i < buffer->csize; i++)
	{
		DLint unit;
		DLBuffer_getDataUnit(buffer, &unit, i);
		printf("%d,", unit);
	}

	printf("]");
}

void debug_buffer (DLBuffer* buffer)
{
	printf("DLBuffer:\n");
	printf("\tSize: %d\n", buffer->size);
	printf("\tCount Size: %d\n", buffer->csize);
	printf("\tUnit Size: %d\n", buffer->usize);
	printf("\tData: ");
	debug_arr(buffer);
	printf("\n");
	printf("\tSize in bytes: %d\n", sizeof(*buffer));
}

int main ()
{
	DL_init();

	DLBuffer buffer;
	// DLBuffer_init(&buffer, DL_INT, 4);
	DLBuffer_init(&buffer, DL_INT, 4, 4);

	DLint buffer_data[4] = {2, 10, 20, 40};
	DLBuffer_setData(&buffer, &buffer_data, sizeof(buffer_data));

	DLint unit_a;
	DLBuffer_getDataUnit(&buffer, &unit_a, 0);

	unit_a = unit_a * 40;
	DLBuffer_setDataUnit(&buffer, &unit_a, 0);

	debug_buffer(&buffer);

	DL_free();
}