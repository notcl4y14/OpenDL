#pragma once

#include <vector>

struct DLSurface {
	// TODO: Change vector to array or char*, if needed
	std::vector<int> data;
	int width;
	int height;
	int area;
	int count;
};

struct DLVec2 {
	int a;
	int b;
};

struct DLVec3 {
	int a;
	int b;
	int c;
};

struct DLVec4 {
	int a;
	int b;
	int c;
	int d;
};

void DLInit();

void DLBindSurface(DLSurface &surface);

DLSurface DLSurfaceCreate(int width, int height);
void DLSurfaceFill(DLVec4 color);
void DLSurfaceDraw(DLSurface surface);
void DLSurfaceDraw(DLSurface surface, DLVec2 position);
void DLSurfaceDraw(DLSurface surface, DLVec4 rect);
DLSurface DLSurfaceClip(DLVec4 clip);
DLVec4 DLSurfaceGetColor(DLVec2 position);
DLVec4 DLSurfaceGetColor(int x, int y);
DLVec4 DLSurfaceGetColor(int index);
void DLSurfaceSetColor(DLVec2 position, DLVec4 color);
void DLSurfaceSetColor(int x, int y, DLVec4 color);
void DLSurfaceSetColor(int index, DLVec4 color);