#include <stdlib.h>
#include <string.h>

#include <DL/dlsystem.h>

DLuint*   DL_type_sizes;

DLSLRunner DL_DLSLRunner;

// 

void DL_init ()
{
	// DL type sizes

	DL_type_sizes = malloc(DL_TYPE_COUNT * sizeof(DLuint));
	DL_type_sizes[DL_BYTE] = 1;
	DL_type_sizes[DL_SHORT] = 2;
	DL_type_sizes[DL_INT] = 4;
	DL_type_sizes[DL_FLOAT] = 4;
	DL_type_sizes[DL_DOUBLE] = 8;

	// DLSL Runner

	DLSLRunner_init(&DL_DLSLRunner);
}

void DL_terminate ()
{
	free(DL_type_sizes);

	DLSLRunner_free(&DL_DLSLRunner);
}