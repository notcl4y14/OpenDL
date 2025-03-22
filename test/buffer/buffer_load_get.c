#include <stdio.h>
#include <stdlib.h>
#include <DL.h>

void main ()
{
	char* buffer_data = malloc(4 * sizeof(char));

	printf("Creating Buffer... (4 char elements)\n\n");
	struct DLBuffer* buffer = malloc(sizeof(struct DLBuffer));
	*buffer = DL_createBuffer(4, sizeof(char));

	printf("Getting Buffer Data...\n\n");
	DL_bufferGetData(buffer, buffer_data);

	printf("Buffer Data:\n");
	printf("[%d, %d, %d, %d]\n\n",
	       buffer_data[0],
	       buffer_data[1],
	       buffer_data[2],
	       buffer_data[3]);

	printf("Creating an Array... [10, 120, 41, 50]\n\n");
	char buf_arr[4] = { 10, 120, 41, 50 };

	printf("Loading an Array into Buffer Data...\n\n");
	DL_bufferLoadData(buffer, &buf_arr);

	printf("Getting Buffer Data...\n\n");
	DL_bufferGetData(buffer, buffer_data);

	printf("Buffer Data:\n");
	printf("[%d, %d, %d, %d]\n\n",
	       buffer_data[0],
	       buffer_data[1],
	       buffer_data[2],
	       buffer_data[3]);

	printf("Done!\n");
}