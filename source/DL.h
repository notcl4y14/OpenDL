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
} DLSurface;

typedef struct
{
	DL_UChar* data;
	int size;
} DLShader;

typedef struct
{
	float a;
	float b;
} DLVec2;

typedef struct
{
	float a;
	float b;
	float c;
	float d;
} DLVec4;

void DL_Init();

DLSurface DL_CreateSurface (int width, int height);
void DL_DestroySurface (DLSurface* surface);

DLVec4 DL_SurfaceGetColor_Pos (DLSurface* surface, int x, int y);
DLVec4 DL_SurfaceGetColor (DLSurface* surface, int index);
void DL_SurfaceSetColor_Pos (DLSurface* surface, int x, int y, DLVec4 color);
void DL_SurfaceSetColor (DLSurface* surface, int index, DLVec4 color);

void DL_SurfaceSetSize_Dim (DLSurface* surface, DLVec2 dimensions);
void DL_SurfaceSetSize (DLSurface* surface, int width, int height);

DLSurface DL_ClipSurface_Rect (DLSurface* surface, DLVec4 rect);
DLSurface DL_ClipSurface (DLSurface* surface, int x, int y, int width, int height);

void DL_FillSurface (DLSurface* surface, DLVec4 color);
void DL_DrawSurface (DLSurface* dest, DLSurface* src, DLVec4 rect);
DLSurface DL_SurfaceApplyShader (DLSurface* surface, DLShader* shader);

DLShader DL_CreateShader ();
void DL_DestroyShader (DLShader* shader);

float DL_GetVectorValue (DLVec4 vector, int index);

#endif