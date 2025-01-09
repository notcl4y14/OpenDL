#pragma once

#define DL_UChar unsigned char

struct DLSurface
{
	DL_UChar* data;
	int width;
	int height;
	int area;
	int count;
};

struct DLVec2
{
	float a;
	float b;
};

struct DLVec4
{
	float a;
	float b;
	float c;
	float d;
};

void DL_Init();

DLSurface DL_CreateSurface (int width, int height);
DLSurface DL_CreateSurface (int width, int height, DL_UChar* color);
DLSurface DL_CreateSurface (int width, int height, DLVec4 color);
void DL_DestroySurface (DLSurface* surface);

DLVec4 DL_SurfaceGetColor (DLSurface* surface, int x, int y);
DLVec4 DL_SurfaceGetColor (DLSurface* surface, int index);
void DL_SurfaceSetColor (DLSurface* surface, int x, int y, DLVec4 color);
void DL_SurfaceSetColor (DLSurface* surface, int index, DLVec4 color);

void DL_SurfaceSetSize (DLSurface* surface, DLVec2 dimensions);
void DL_SurfaceSetSize (DLSurface* surface, int width, int height);

DLSurface DL_ClipSurface (DLSurface* surface, DLVec4 rect);
DLSurface DL_ClipSurface (DLSurface* surface, int x, int y, int width, int height);

void DL_FillSurface (DLSurface* surface, DLVec4 color);
void DL_DrawSurface (DLSurface* dest, DLSurface* src, DLVec4 rect);

float DL_GetVectorValue (DLVec4 vector, int index);