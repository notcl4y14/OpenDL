#include <stdio.h>
#include <DL.h>

void main ()
{
	printf("Initializing DL...\n");
	dlInit();

	printf("Creating a Buffer... (4 char elements)...\n");
	loc_dl buffer = dlCreateBuffer(4, sizeof(char));

	printf("Creating a Shader...\n");
	loc_dl shader = dlCreateShader();

	printf("Creating a Path...\n");
	loc_dl path = dlCreatePath();

	printf("Buffers: %d/%d; Shaders: %d/%d; Paths: %d/%d.\n",
		   DLarray_buffers_count, DLarray_buffers_capacity,
		   DLarray_shaders_count, DLarray_shaders_capacity,
		   DLarray_paths_count, DLarray_paths_capacity);

	printf("Buffers: %d/%d B; Shaders: %d/%d B; Paths: %d/%d B.\n",
		   DLarray_buffers_count * sizeof(struct DLBuffer), DLarray_buffers_capacity * sizeof(struct DLBuffer),
		   DLarray_shaders_count * sizeof(struct DLShader), DLarray_shaders_capacity * sizeof(struct DLShader),
		   DLarray_paths_count * sizeof(struct DLPath), DLarray_paths_capacity * sizeof(struct DLPath));

	printf("Terminating DL...\n");
	dlTerminate();

	printf("Done!\n");
}