#ifndef DL_H
#define DL_H

#define DLUChar unsigned char
#define DLUInt unsigned int

#define DL_TRUE 1
#define DL_FALSE 0

#define DL_OBJECT_NONE 0
#define DL_OBJECT_SHADER 1
#define DL_OBJECT_PATH 2
#define DL_OBJECT_ALL 3

struct DLShader;
struct DLPath;

typedef struct DLShader DLShader;
typedef struct DLPath DLPath;

struct DLShader
{
	// int    attrs_count;
	int    attrs_capacity;
	char** attrs_keys;
	void** attrs_values;

	int    buf_attrs_capacity;
	int    buf_attrs_count;
	void** buf_attrs_buffers;
	int*   buf_attrs_voffset;
	int*   buf_attrs_vsize;
	int*   buf_attrs_attribs;
};

struct DLPath
{
	// int    attrs_count;
	int    attrs_capacity;
	char** attrs_keys;
	void** attrs_values;
};

extern struct DLShader* _DL_shaders_values;
extern struct DLPath*   _DL_paths_values;

extern DLUInt _DL_shaders_count;
extern DLUInt _DL_paths_count;

extern DLUInt _DL_shaders_capacity;
extern DLUInt _DL_paths_capacity;

// DL
void dlInit ();
void dlTerminate ();

void dlInitialArrayCapacity (DLUInt object, DLUInt capacity);

// DLShader
DLUInt dlCreateShader ();
void dlFreeShader (DLUInt shader);

void dlShaderInit (DLUInt shader, int attrs_size, int buf_attrs_capacity);
void dlShaderBindAttribID (DLUInt shader, char* id, int index);

int dlShaderGetAttribIndex (DLUInt shader, char* id);
void dlShaderBindUniformAttrib (DLUInt shader, int index, void* attrib);
void dlShaderBindBufferAttrib (DLUInt shader, void* buffer, DLUInt voffset, DLUInt vsize, DLUInt attrib);

// DLPath
DLUInt dlCreatePath ();
void dlFreePath ();

#endif