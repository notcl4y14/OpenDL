#ifndef DL_H
#define DL_H

// Including objects from DLSL.h
// to prevent header recursion
// =============================
struct DLSLVM;
// =============================

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

struct DLCode;

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

struct DLCode
{
	int*   code;
	DLUInt code_size;
};

struct DLShader
{
	struct DLCode code;
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

extern struct DLSLVM _DL_dlsl_vm;

// DL
void dlInit ();
void dlTerminate ();

void dlInitialArrayCapacity (DLUInt object, DLUInt capacity);

// DLShader
DLUInt dlCreateShader ();
void dlFreeShader (DLUInt shader);

void dlShaderInit (DLUInt shader, int attrs_capacity, int buf_attrs_capacity);
void dlShaderBindAttribID (DLUInt shader, char* id, int index);

void dlShaderLoadCode (DLUInt shader, int* code, int code_size);

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