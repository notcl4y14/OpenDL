#include <stdio.h>
#include <stdlib.h>

#include <DL.h>

void main ()
{
	printf("Creating Attrs...\n\n");
	struct DLAttrs* attrs = malloc(sizeof(struct DLAttrs));
	*attrs = DL_createAttrs(4);

	printf("Binding Attribute Keys to Attrs...\n\n");
	DL_bindAttribLocation(attrs, 0, "attrib1");
	DL_bindAttribLocation(attrs, 1, "attrib2");
	DL_bindAttribLocation(attrs, 2, "attrib3");
	DL_bindAttribLocation(attrs, 3, "attrib4");

	printf("Creating an Attribute Buffer...\n\n");
	int attr_buffer[4] = { 10, 20, 40, 80 };

	printf("Getting Attribute Locations...\n\n");
	size_t attrib1_loc = DL_getAttribLocation(attrs, "attrib1");
	size_t attrib2_loc = DL_getAttribLocation(attrs, "attrib2");
	size_t attrib3_loc = DL_getAttribLocation(attrs, "attrib3");
	size_t attrib4_loc = DL_getAttribLocation(attrs, "attrib4");

	printf("Attrs (all null):\n");
	printf("[%d, %d, %d, %d]\n\n",
	       (int*)(attrs->data)[0],
	       (int*)(attrs->data)[1],
	       (int*)(attrs->data)[2],
	       (int*)(attrs->data)[3]);

	printf("Binding Attribute Values...\n\n");
	DL_bindAttribValue(attrs, attrib1_loc, &attr_buffer[0]);
	DL_bindAttribValue(attrs, attrib2_loc, &attr_buffer[1]);
	DL_bindAttribValue(attrs, attrib3_loc, &attr_buffer[2]);
	DL_bindAttribValue(attrs, attrib4_loc, &attr_buffer[3]);

	printf("Attrs:\n");
	printf("[%d, %d, %d, %d]\n\n",
	       *(int*)(attrs->data)[0],
	       *(int*)(attrs->data)[1],
	       *(int*)(attrs->data)[2],
	       *(int*)(attrs->data)[3]);
}