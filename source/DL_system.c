#include <stdlib.h>
#include <string.h>

#include <DL_system.h>

DLBuffer* DL_buffers;
DLbool*   DL_buffers_available;
DLuint    DL_buffers_count;
DLuint    DL_buffers_capacity;

DLShader* DL_shaders;
DLbool*   DL_shaders_available;
DLuint    DL_shaders_count;
DLuint    DL_shaders_capacity;

DLPath*   DL_paths;
DLbool*   DL_paths_available;
DLuint    DL_paths_count;
DLuint    DL_paths_capacity;

DLuint*   DL_type_sizes;

DLSLRunner DL_DLSLRunner;

// 

void DL_init ()
{
	DLuint loop_loc;

	// DL object arrays

	DL_buffers_capacity = 16;
	DL_shaders_capacity = 16;
	DL_paths_capacity = 16;

	DL_buffers_count = 0;
	DL_shaders_count = 0;
	DL_paths_count = 0;

	DL_buffers = malloc(DL_buffers_capacity * sizeof(DLBuffer));
	DL_shaders = malloc(DL_shaders_capacity * sizeof(DLShader));
	DL_paths = malloc(DL_paths_capacity * sizeof(DLPath));

	DL_buffers_available = malloc(DL_buffers_capacity * sizeof(DLbool));
	DL_shaders_available = malloc(DL_shaders_capacity * sizeof(DLbool));
	DL_paths_available = malloc(DL_paths_capacity * sizeof(DLbool));

	// Filling DL_object_available with DL_TRUE-s
	loop_loc = -1;

	while (++loop_loc < DL_buffers_capacity)
	{
		DL_buffers_available[loop_loc] = DL_TRUE;
	}

	loop_loc = -1;

	while (++loop_loc < DL_shaders_capacity)
	{
		DL_shaders_available[loop_loc] = DL_TRUE;
	}

	loop_loc = -1;

	while (++loop_loc < DL_paths_capacity)
	{
		DL_paths_available[loop_loc] = DL_TRUE;
	}

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

void DL_free ()
{
	free(DL_buffers);
	free(DL_shaders);
	free(DL_paths);
	free(DL_buffers_available);
	free(DL_shaders_available);
	free(DL_paths_available);

	free(DL_type_sizes);

	DLSLRunner_free(&DL_DLSLRunner);
}

// 

DLuint DL_add_buffer (DLBuffer buffer)
{
	DLuint loop_loc = -1;

	while (++loop_loc < DL_buffers_capacity)
	{
		if (DL_buffers_available[loop_loc] == DL_TRUE)
		{
			break;
		}
	}

	if (loop_loc == DL_buffers_capacity)
	{
		DL_realloc_buffers();
	}

	DL_buffers[loop_loc] = buffer;
	DL_buffers_available[loop_loc] = DL_FALSE;
	DL_buffers_count++;

	return loop_loc;
}

DLuint DL_add_shader (DLShader shader)
{
	DLuint loop_loc = -1;

	while (++loop_loc < DL_shaders_capacity)
	{
		if (DL_shaders_available[loop_loc] == DL_TRUE)
		{
			break;
		}
	}

	if (loop_loc == DL_shaders_capacity)
	{
		DL_realloc_shaders();
	}

	DL_shaders[loop_loc] = shader;
	DL_shaders_available[loop_loc] = DL_FALSE;
	DL_shaders_count++;

	return loop_loc;
}

DLuint DL_add_path (DLPath path)
{
	DLuint loop_loc = -1;

	while (++loop_loc < DL_paths_capacity)
	{
		if (DL_paths_available[loop_loc] == DL_TRUE)
		{
			break;
		}
	}

	if (loop_loc == DL_paths_capacity)
	{
		DL_realloc_paths();
	}

	DL_paths[loop_loc] = path;
	DL_paths_available[loop_loc] = DL_FALSE;
	DL_paths_count++;

	return loop_loc;
}

// 

void DL_realloc_buffers ()
{
	DLuint loop_loc, last_loc;

	last_loc = DL_buffers_capacity;
	DL_buffers_capacity *= 2;

	DL_buffers = realloc(DL_buffers, DL_buffers_capacity * sizeof(DLBuffer));
	DL_buffers_available = realloc(DL_buffers_available, DL_buffers_capacity * sizeof(DLbool));

	// Filling DL_buffers_available with DL_TRUE-s
	loop_loc = last_loc - 1;

	while (++loop_loc < DL_buffers_capacity)
	{
		DL_buffers_available[loop_loc] = DL_TRUE;
	}
}

void DL_realloc_shaders ()
{
	DLuint loop_loc, last_loc;

	last_loc = DL_shaders_capacity;
	DL_shaders_capacity *= 2;

	DL_shaders = realloc(DL_shaders, DL_shaders_capacity * sizeof(DLBuffer));
	DL_shaders_available = realloc(DL_shaders_available, DL_shaders_capacity * sizeof(DLbool));

	// Filling DL_shaders_available with DL_TRUE-s
	loop_loc = last_loc - 1;

	while (++loop_loc < DL_shaders_capacity)
	{
		DL_shaders_available[loop_loc] = DL_TRUE;
	}
}

void DL_realloc_paths ()
{
	DLuint loop_loc, last_loc;

	last_loc = DL_paths_capacity;
	DL_paths_capacity *= 2;

	DL_paths = realloc(DL_paths, DL_paths_capacity * sizeof(DLBuffer));
	DL_paths_available = realloc(DL_paths_available, DL_paths_capacity * sizeof(DLbool));

	// Filling DL_paths_available with DL_TRUE-s
	loop_loc = last_loc - 1;

	while (++loop_loc < DL_paths_capacity)
	{
		DL_paths_available[loop_loc] = DL_TRUE;
	}
}