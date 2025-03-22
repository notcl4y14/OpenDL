#include <DL.h>

void main ()
{
	printf("Declaring Attrs...\n");
	struct DLAttrs attrs;

	printf("Defining Attrs... (4 attributes)\n");
	attrs = DL_createAttrs(4);

	printf("Freeing Attrs...\n");
	DL_freeAttrs(&attrs);

	printf("Done!\n");
}