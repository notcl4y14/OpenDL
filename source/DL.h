#ifndef DL_H
#define DL_H

#define DL_uchar unsigned char
#define DL_uint unsigned int

#define DL_TRUE 1
#define DL_FALSE 0

typedef struct
{
	DL_uchar* data;
	int width;
	int height;
	int area;

	int data_size;
	int pixel_size;
} DLBuffer;

typedef struct
{
	DL_uchar* pixel_color;
	int pixel_coord[2];

	int    attrs_count;
	char** attrs_keys;
	void** attrs_values;
} DLShaderAttrs;

typedef struct
{
	void (*code)(DLShaderAttrs*);
	DLShaderAttrs attrs;
} DLShader;

typedef struct
{
	DLBuffer* buffer;

	int    attrs_count;
	char** attrs_keys;
	void** attrs_values;
} DLPathAttrs;

typedef struct
{
	void (*code)(DLPathAttrs*);
	DLPathAttrs attrs;
} DLPath;

extern DL_uint __DL_bufferDefaultPixelSize;

extern DLBuffer* __DL_buffers_values;
extern DLShader* __DL_shaders_values;
extern DLPath* __DL_paths_values;

extern DL_uint __DL_buffers_count;
extern DL_uint __DL_shaders_count;
extern DL_uint __DL_paths_count;

extern DL_uint __DL_buffers_capacity;
extern DL_uint __DL_shaders_capacity;
extern DL_uint __DL_paths_capacity;

void dlInit();
void dlTerminate();

void dlBufferDefaultPixelSize (DL_uint size);
void dlInitialArraysCapacity (DL_uint size);

// DlBuffer
DL_uint dlCreateBuffer (int width, int height);
DL_uint dlCreateBufferSize (int width, int height, int size);
void dlFreeBuffer (DL_uint buffer);

DLBuffer* dlGetBuffer (DL_uint buffer);

DL_uchar* dlBufferGetData (DL_uint buffer);
// int[2]    dlBufferGetDimensions (DL_uint buffer);
int       dlBufferGetWidth (DL_uint buffer);
int       dlBufferGetHeight (DL_uint buffer);
int       dlBufferGetArea (DL_uint buffer);
int       dlBufferGetGetDataSize (DL_uint buffer);
int       dlBufferGetGetPixelSize (DL_uint buffer);

void dlBufferSetDimensions (DL_uint buffer, int width, int height);
void dlBufferSetPixelSize (DL_uint buffer, int size);

DL_uchar* dlBufferGetPixel (DL_uint buffer, int index, int step);
DL_uchar* dlBufferGetPixelAt (DL_uint buffer, int x, int y, int step);
void dlBufferSetPixel (DL_uint buffer, int index, DL_uchar* value);
void dlBufferSetPixelAt (DL_uint buffer, int x, int y, DL_uchar* value);

DL_uint dlClipBuffer (DL_uint buffer, int x1, int y1, int x2, int y2);
void dlFillBuffer (DL_uint buffer, DL_uchar* value);
void dlDrawBuffer (DL_uint destBuffer, DL_uint srcBuffer, int x1, int y1, int x2, int y2);

void dlBufferApplyShader (DL_uint buffer, DL_uint shader);
void dlBufferApplyPath (DL_uint buffer, DL_uint path);

// DlShader
DL_uint dlCreateShader ();
void dlFreeShader (DL_uint shader);

DLShader* dlGetShader (DL_uint shader);

DLShaderAttrs* dlShaderGetAttrs (DL_uint shader);

void dlShaderInit (DL_uint shader, int count);
void dlShaderBindAttrib  (DL_uint shader, char* id, int index);

void dlShaderBindCode    (DL_uint shader, void (*code) (DLShaderAttrs*));

void dlShaderSetAttrib   (DL_uint shader, int index, void* value);
void dlShaderSetAttribID (DL_uint shader, char* id, void* value);
void* dlShaderGetAttrib   (DL_uint shader, int index);
void* dlShaderGetAttribID (DL_uint shader, char* id);

// DlPath
DL_uint dlCreatePath ();
void dlFreePath (DL_uint path);

DLPath* dlGetPath (DL_uint path);

DLPathAttrs* dlPathGetAttrs (DL_uint path);

void dlPathInit (DL_uint path, int count);
void dlPathBindAttrib  (DL_uint path, char* id, int index);

void dlPathBindCode    (DL_uint path, void (*code) (DLPathAttrs*));

void dlPathSetAttrib   (DL_uint path, int index, void* value);
void dlPathSetAttribID (DL_uint path, char* id, void* value);
void* dlPathGetAttrib   (DL_uint path, int index);
void* dlPathGetAttribID (DL_uint path, char* id);

#endif