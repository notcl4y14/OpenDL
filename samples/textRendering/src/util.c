#include <stdio.h>
#include "util.h"

void Util_saveToFile (DlBuffer* buffer, char* filename)
{
	int index = -1;

	FILE* file;
	file = fopen(filename, "w");

	fprintf(file, "%d\n%d\n", buffer->width, buffer->height);

	while (++index < buffer->count)
	{
		fprintf(file, "%d\n", buffer->data[index]);
	}

	fclose(file);
}