#include <DL_system.h>

void debug_arr ()
{
	printf("[");

	for (int i = 0; i < DL_buffers_capacity; i++)
	{
		printf("%d,", DL_buffers_available[i]);
	}

	printf("]");
}

void debug ()
{
	printf("DLBuffers:\n");
	printf("\tCount: %d (%dB)\n", DL_buffers_count, DL_buffers_count * sizeof(DLBuffer));
	printf("\tCapacity: %d (%dB)\n", DL_buffers_capacity, DL_buffers_capacity * sizeof(DLBuffer));
	printf("\tAvailable: ");
	debug_arr();
	printf("\n");
}

int main ()
{
	debug();

	DL_init();

	debug();

	DL_realloc_buffers();

	debug();

	DL_free();

	// debug();
	
	return 0;
}