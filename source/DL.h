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

extern struct DLBuffer* _DL_buffers;
extern struct DLShader* _DL_shaders;
extern struct DLPath*   _DL_paths;

extern DLuint _DL_buffers_count;
extern DLuint _DL_shaders_count;
extern DLuint _DL_paths_count;

extern DLuint _DL_buffers_capacity;
extern DLuint _DL_shaders_capacity;
extern DLuint _DL_paths_capacity;

// DL
void dlInit ();
void dlTerminate ();

// DLBuffer
DLuint dlCreateBuffer (DLuint buf_size, DLuint buf_item_size);
void dlFreeBuffer (DLuint buffer);

void dlBufferLoad (DLuint buffer, void* source);

// DLShader
DLuint dlCreateShader ();
void dlFreeShader (DLuint shader);

void dlInitShader (DLuint shader);
void dlShaderBindAttribID (DLuint shader, char* attrib_id, DLuint attrib_loc);

DLuint dlShaderGetAttribLocation (DLuint shader, char* attrib_id);
void dlShaderBindAttrib (DLuint shader, DLuint attrib_loc, void* attrib_ptr);

void dlApplyShader (DLuint shader, DLuint buffer);

// DLPath
DLuint dlCreatePath ();
void dlFreePath (DLuint path);

void dlInitPath (DLuint path);
void dlPathBindAttribID (DLuint path, char* attrib_id, DLuint attrib_loc);

DLuint dlPathGetAttribLocation (DLuint path, char* attrib_id);
void dlPathBindAttrib (DLuint path, DLuint attrib_loc, void* attrib_ptr);

void dlApplyPath (DLuint path, DLuint buffer, void (*test_func)(struct DLAttrs* attrs, struct DLBuffer* buffer));

#endif