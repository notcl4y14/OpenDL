#include <stdio.h>
#include <DL.h>

void main ()
{
	printf("Declaring Shader and Path...\n");
	struct DLShader shader;
	struct DLPath path;

	printf("Defining Shader and Path...\n");
	shader = DL_createShader();
	path = DL_createPath();

	printf("Creating Attrs for Shader and Path... (2 elements for each)\n");
	shader.attrs = DL_createAttrs(2);
	path.attrs = DL_createAttrs(2);

	printf("Freeing Shader and Path...\n");
	DL_freeShader(&shader);
	DL_freePath(&path);

	printf("Done!\n");
}