#include <DL/dldefines.h>
#include <DL/dlcore.h>
#include <DL/dlsl.h>

#ifndef DL_SYSTEM_H
#define DL_SYSTEM_H

extern dlBuffer* DL_buffers;
extern DLbool*   DL_buffers_available;
extern DLuint    DL_buffers_count;
extern DLuint    DL_buffers_capacity;

extern dlShader* DL_shaders;
extern DLbool*   DL_shaders_available;
extern DLuint    DL_shaders_count;
extern DLuint    DL_shaders_capacity;

extern dlPath*   DL_paths;
extern DLbool*   DL_paths_available;
extern DLuint    DL_paths_count;
extern DLuint    DL_paths_capacity;

extern DLuint*   DL_type_sizes;

extern dlslRunner DL_dlslRunner;

void DL_init ();
void DL_free ();

DLuint DL_add_buffer (dlBuffer buffer);
DLuint DL_add_shader (dlShader shader);
DLuint DL_add_path (dlPath path);

void DL_realloc_buffers ();
void DL_realloc_shaders ();
void DL_realloc_paths ();

#endif