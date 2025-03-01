#ifndef DL_H
#define DL_H

#define DL_uchar unsigned char

typedef struct
{
	DL_uchar* data;
	int width;
	int height;
	int area;
	int count;
	int size;
} DlBuffer;

typedef struct
{
	DL_uchar* Dl_color;
	int Dl_positionX;
	int Dl_positionY;
} DlShaderAttrs;

typedef struct
{
	void (*code)(DlShaderAttrs*); // void* is supposed to be DlShader*
	DlShaderAttrs attrs;
} DlShader;

typedef struct
{
	DlBuffer* buffer;
} DlPathAttrs;

typedef struct
{
	void (*code)(DlPathAttrs*); // void* is supposed to be DlShader*
	DlPathAttrs attrs;
} DlPath;

extern unsigned int __Dl_DefaultPixelSize;

void Dl_Init();

void Dl_SetDefaultPixelSize (unsigned int size);

// DlBuffer
DlBuffer Dl_CreateBuffer (int width, int height);
DlBuffer Dl_CreateBufferSize (int width, int height, int size);
void Dl_FreeBuffer (DlBuffer* buffer);

DL_uchar* Dl_BufferGetPixel (DlBuffer* buffer, int index, int step);
DL_uchar* Dl_BufferGetPixelAt (DlBuffer* buffer, int x, int y, int step);
void Dl_BufferSetPixel (DlBuffer* buffer, int index, ...);
void Dl_BufferSetPixelAt (DlBuffer* buffer, int x, int y, ...);

void Dl_SetBufferSize (DlBuffer* buffer, int width, int height);
DlBuffer Dl_ClipBuffer (DlBuffer* buffer, int x1, int y1, int x2, int y2);
void Dl_FillBuffer (DlBuffer* buffer, ...);
void Dl_DrawBuffer (DlBuffer* buffer, DlBuffer* srcBuffer, int x1, int y1, int x2, int y2);

DlBuffer Dl_BufferApplyShader (DlBuffer* buffer, DlShader* shader);
DlBuffer Dl_BufferApplyPath (DlBuffer* buffer, DlPath* path);

// DlShader
DlShader Dl_CreateShader ();
void Dl_FreeShader (DlShader* shader);

void Dl_ShaderBindCode (DlShader* shader, void (*code) (DlShaderAttrs*));
void Dl_SetShaderAttrib (DlShader* shader, char* attribute, void* value);
void* Dl_GetShaderAttrib (DlShader* shader, char* attribute);

// DlPath
DlPath Dl_CreatePath ();
void Dl_FreePath (DlPath* path);

void Dl_PathBindCode (DlPath* path, void (*code) (DlPathAttrs*));
void Dl_SetPathAttrib (DlPath* path, char* attribute, void* value);
void* Dl_GetPathAttrib (DlPath* path, char* attribute);

#endif