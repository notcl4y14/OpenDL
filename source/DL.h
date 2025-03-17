#ifndef DL_h
#define DL_h

#define DLuchar unsigned char
#define DLuint unsigned int

#define DL_FALSE 0
#define DL_TRUE 1

struct DLBuffer;
struct DLShader;
struct DLPath;
struct DLAttrs;

struct DLAttrs
{
	DLuint capacity;
	char** keys;
	void** values;
};

struct DLBuffer
{
	void* buffer;
	DLuint size;
	DLuint usize;
};

struct DLShader
{
	struct DLAttrs attrs;
};

struct DLPath
{
	struct DLAttrs attrs;
};

extern struct DLBuffer* _DL_Buffers;
extern struct DLShader* _DL_Shaders;
extern struct DLPath*   _DL_Paths;

extern DLuint _DL_Buffers_count;
extern DLuint _DL_Shaders_count;
extern DLuint _DL_Paths_count;

extern DLuint _DL_Buffers_capacity;
extern DLuint _DL_Shaders_capacity;
extern DLuint _DL_Paths_capacity;

// DL
void DL_init ();
void DL_terminate ();

// DLBuffer
DLuint DL_buffer_generate (void* buffer, DLuint buf_size, DLuint buf_item_size);
DLuint DL_buffer_bind (void* buffer, DLuint buf_size, DLuint buf_item_size);
void DL_buffer_free (DLuint buffer);

// DLShader
DLuint DL_shader_create ();
void DL_shader_free (DLuint shader);

void DL_shader_load (DLuint shader);
void DL_shader_bindAttribId (DLuint shader, char* attrib_id, DLuint attrib_loc);

DLuint DL_shader_getAttribLocation (DLuint shader, char* attrib_id);
void DL_shader_bindAttrib (DLuint shader, DLuint attrib_loc, void* attrib_ptr);

void DL_shader_apply (DLuint shader, DLuint buffer);

// DLPath
DLuint DL_path_create ();
void DL_path_free (DLuint path);

void DL_path_load (DLuint path);
void DL_path_bindAttribId (DLuint shader, char* attrib_id, DLuint attrib_loc);

DLuint DL_path_getAttribLocation (DLuint path, char* attrib_id);
void DL_path_bindAttrib (DLuint shader, DLuint attrib_loc, void* attrib_ptr);

void DL_path_apply (DLuint path, DLuint buffer);

#endif