#include <stdio.h>
#include <DL.h>

void main ()
{
	printf("Declaring a buffer...\n");
	struct DLBuffer buffer;

	printf("Defining a buffer... (10 char elements)\n");
	buffer = DL_createBuffer(10, sizeof(char));

	printf("Freeing a buffer...\n");
	DL_freeBuffer(&buffer);

	printf("Done!\n");
}