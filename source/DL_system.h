#include <DL_defines.h>
#include <DL_core.h>

#ifndef DL_SYSTEM_H
#define DL_SYSTEM_H

extern DLBuffer* DL_buffers;
extern DLbool*   DL_buffers_available;
extern DLuint    DL_buffers_count;
extern DLuint    DL_buffers_capacity;

extern DLShader* DL_shaders;
extern DLbool*   DL_shaders_available;
extern DLuint    DL_shaders_count;
extern DLuint    DL_shaders_capacity;

extern DLPath*   DL_paths;
extern DLbool*   DL_paths_available;
extern DLuint    DL_paths_count;
extern DLuint    DL_paths_capacity;

extern DLuint*   DL_type_sizes;

void DL_init ();
void DL_free ();

DLuint DL_add_buffer (DLBuffer buffer);
DLuint DL_add_shader (DLShader shader);
DLuint DL_add_path (DLPath path);

void DL_realloc_buffers ();
void DL_realloc_shaders ();
void DL_realloc_paths ();

#endif