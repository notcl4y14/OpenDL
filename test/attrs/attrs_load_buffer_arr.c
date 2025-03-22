#include <stdio.h>
#include <stdlib.h>
#include <DL.h>

int main ()
{
	printf("Creating Attrs... (4 attributes)\n");
	struct DLAttrs* attrs = malloc(sizeof(struct DLAttrs));
	*attrs = DL_createAttrs(4);

	printf("Creating Buffer... (4 char elements)\n");
	struct DLBuffer* attrs_data_buf = malloc(sizeof(struct DLBuffer));
	*attrs_data_buf = DL_createBuffer(4, sizeof(char));

	printf("Setting Buffer Data... [10, 24, 72, 40]\n");
	// attrs_data_buf->data = { 10, 24, 72, 40 };
	{
		char attrs_data_buf_data[4] = { 10, 24, 72, 40 };
		DL_bufferLoadData(attrs_data_buf, attrs_data_buf_data);
	}

	printf("Loading Buffer Data to Attrs...\n");
	DL_attrsLoadBuffer(attrs, attrs_data_buf);

	printf("Attrs: [%d, %d, %d, %d]\n",
	       *(char*)(attrs->data[0]),
	       *(char*)(attrs->data[1]),
	       *(char*)(attrs->data[2]),
	       *(char*)(attrs->data[3]));

	printf("Creating Array Data... [40, 50, 20, 25]\n");
	char attrs_data_arr[4] = { 40, 50, 20, 25 };

	printf("Loading Array Data to Attrs...\n");
	DL_attrsLoadArray(attrs, attrs_data_arr, sizeof(char));

	printf("Attrs: [%d, %d, %d, %d]\n",
	       *(char*)(attrs->data[0]),
	       *(char*)(attrs->data[1]),
	       *(char*)(attrs->data[2]),
	       *(char*)(attrs->data[3]));

	printf("Done!\n");
	return 0;
}