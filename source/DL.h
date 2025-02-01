#ifndef DL_H
#define DL_H

#define DL_UChar unsigned char

typedef struct
{
	DL_UChar* data;
	int width;
	int height;
	int area;
	int count;
	int size;
} DlBuffer;

typedef struct
{
	DL_UChar* Dl_color;
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

static unsigned int __Dl_DefaultPixelSize = 1;

void Dl_Init();

void Dl_SetDefaultPixelSize (unsigned int size);

// DlBuffer
DlBuffer Dl_CreateBuffer (int width, int height);
void Dl_FreeBuffer (DlBuffer* buffer);

DL_UChar Dl_BufferGetPixel (DlBuffer* buffer, int index, int step);
DL_UChar Dl_BufferGetPixelAt (DlBuffer* buffer, int x, int y, int step);
void Dl_BufferSetPixel (DlBuffer* buffer, int index, ...);
void Dl_BufferSetPixelAt (DlBuffer* buffer, int x, int y, ...);

void Dl_SetBufferSize (DlBuffer* buffer, int width, int height);
void Dl_FillBuffer (DlBuffer* buffer, ...);

DlBuffer Dl_BufferApplyShader (DlBuffer* buffer, DlShader* shader);
DlBuffer Dl_BufferApplyPath (DlBuffer* buffer, DlPath* path);

// DlShader
DlShader Dl_CreateShader ();
void Dl_FreeShader (DlShader* shader);

void Dl_ShaderBindCode (DlShader* shader, void (*code) (DlShaderAttrs*));

// DlPath
DlPath Dl_CreatePath ();
void Dl_FreePath (DlPath* path);

void Dl_PathBindCode (DlPath* path, void (*code) (DlPathAttrs*));

#endif