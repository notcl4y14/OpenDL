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

struct DLAttrs;
struct DLBufAttrs;

typedef struct DLShader DLShader;
typedef struct DLPath DLPath;

struct DLAttrs
{
	int capacity;
	char** keys;
	void** values;
};

struct DLBufAttrs
{
	int capacity;
	int count;
	void**    buffers;
	DLUInt*   voffset;
	DLUInt*   vstride;
	DLUInt*   vsize;
	DLUInt*   attribs;
};

struct DLShader
{
	struct DLAttrs attrs;
	struct DLBufAttrs buf_attrs;
};

struct DLPath
{
	struct DLAttrs attrs;
};

extern struct DLShader* _DL_shaders_values;
extern struct DLPath*   _DL_paths_values;

extern DLUInt _DL_shaders_count;
extern DLUInt _DL_paths_count;

extern DLUInt _DL_shaders_capacity;
extern DLUInt _DL_paths_capacity;

// extern DLUChar _DL_shaders_auto_init;
// extern DLUChar _DL_paths_auto_init;

// DL
void dlInit ();
void dlTerminate ();

void dlInitialArrayCapacity (DLUInt object, DLUInt capacity);
// void dlInitObjectsAutomatically (DLUInt object, DLUChar boolean);

// DLShader
DLUInt dlCreateShader ();
void dlFreeShader (DLUInt shader);

void dlShaderInit (DLUInt shader, int attrs_capacity, int buf_attrs_capacity);
void dlShaderBindAttribID (DLUInt shader, char* id, int index);

DLUInt dlShaderGetAttribIndex (DLUInt shader, char* id);
void dlShaderBindUniformAttrib (DLUInt shader, int index, void* attrib);
void dlShaderBindBufferAttrib (DLUInt shader, void* buffer, DLUInt voffset, DLUInt vstride, DLUInt vsize, DLUInt attrib);

void dlApplyShader (DLUInt shader, void* buffer, DLUInt buffer_size, DLUInt byte_size);

// DLPath
DLUInt dlCreatePath ();
void dlFreePath ();

void dlPathInit (DLUInt path, int attrs_capacity);
void dlPathBindAttribID (DLUInt path, char* id, int index);

DLUInt dlPathGetAttribIndex (DLUInt path, char* id);
void dlPathBindUniformAttrib (DLUInt path, int index, void* attrib);

void dlApplyPath (DLUInt path, void* buffer, DLUInt buffer_size, DLUInt byte_size);

#endif