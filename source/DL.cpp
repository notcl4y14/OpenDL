#include "DL.h"

DLSurface* __DLSurface;

void DLInit()
{
	__DLSurface = nullptr;
}

void DLBindSurface(DLSurface &surface)
{
	__DLSurface = &surface;
}

DLSurface DLSurfaceCreate (int width, int height)
{
	DLSurface surface;
	surface.width = width;
	surface.height = height;
	surface.area = surface.width * surface.height;
	surface.count = surface.area * 4;
	surface.data.resize(surface.count);
	return surface;
}

void DLSurfaceFill (DLVec4 color)
{
	if (__DLSurface == nullptr)
	{
		return;
	}
	
	int index = -1;
	int area = __DLSurface->area;

	while (++index < area)
	{
		int pixelIndex = index * 4;
		__DLSurface->data.at(pixelIndex) = color.a;
		__DLSurface->data.at(pixelIndex + 1) = color.b;
		__DLSurface->data.at(pixelIndex + 2) = color.c;
		__DLSurface->data.at(pixelIndex + 3) = color.d;
	}
}

DLSurface DLSurfaceClip (DLVec4 clip)
{
	if (__DLSurface == nullptr)
	{
		return DLSurface{};
	}

	DLSurface surface;

	int x1 = clip.a;
	int y1 = clip.b;
	int x2 = clip.c;
	int y2 = clip.d;

	surface.width = x2 - x1;
	surface.height = y2 - y1;
	surface.area = surface.width * surface.height;
	surface.count = surface.area * 4;
	surface.data.resize(surface.count);

	int x = x1;
	int y = y1;

	while (x < x2)
	{
		while (y < y2)
		{
			DLVec4 color = DLSurfaceGetColor(x, y);

			int pixelX = x - x1;
			int pixelY = y - y1;
			int index = (pixelY * surface.width + pixelX) * 4;

			surface.data.at(index) = color.a;
			surface.data.at(index) = color.b;
			surface.data.at(index) = color.c;
			surface.data.at(index) = color.d;
			
			y++;
		}

		x++;
		y = y1;
	}

	return surface;
}

void DLSurfaceDraw (DLSurface surface)
{
	DLSurfaceDraw(surface, DLVec2{0, 0});
}

void DLSurfaceDraw(DLSurface surface, DLVec2 position)
{
	DLSurfaceDraw(surface, DLVec4{
		position.a, position.b,
		position.a + surface.width, position.b + surface.height});
}

void DLSurfaceDraw(DLSurface surface, DLVec4 rect)
{
	if (__DLSurface == nullptr)
	{
		return;
	}
	
	int x1 = rect.a;
	int y1 = rect.b;
	int x2 = rect.c;
	int y2 = rect.d;

	int width = x2 - x1;
	int height = y2 - y1;
	int area = width * height;

	float widthFraction = surface.width / width;
	float heightFraction = surface.height / height;

	int index = 0;

	while (index < area)
	{
		int x = index % width;
		int y = index / width;
		int pixelX = x * widthFraction;
		int pixelY = y * heightFraction;

		DLVec4 color = DLSurfaceGetColor(pixelX, pixelY);
		DLSurfaceSetColor(x + x1, y + y1, color);
		
		index++;
	}
}

DLVec4 DLSurfaceGetColor (DLVec2 position)
{
	return DLSurfaceGetColor(position.a, position.b);
}

DLVec4 DLSurfaceGetColor (int x, int y)
{
	if (__DLSurface == nullptr)
	{
		return DLVec4{};
	}

	int index = (y * __DLSurface->width + x) * 4;
	
	DLVec4 color;
	color.a = __DLSurface->data.at(index);
	color.b = __DLSurface->data.at(index + 1);
	color.c = __DLSurface->data.at(index + 2);
	color.d = __DLSurface->data.at(index + 3);

	return color;
}

DLVec4 DLSurfaceGetColor (int index)
{
	if (__DLSurface == nullptr)
	{
		return DLVec4{};
	}

	int pixelIndex = index * 4;
	
	DLVec4 color;
	color.a = __DLSurface->data.at(pixelIndex);
	color.b = __DLSurface->data.at(pixelIndex + 1);
	color.c = __DLSurface->data.at(pixelIndex + 2);
	color.d = __DLSurface->data.at(pixelIndex + 3);

	return color;
}

void DLSurfaceSetColor (DLVec2 position, DLVec4 color)
{
	DLSurfaceSetColor(position.a, position.b, color);
}

void DLSurfaceSetColor (int x, int y, DLVec4 color)
{
	if (__DLSurface == nullptr)
	{
		return;
	}

	int index = (y * __DLSurface->width + x) * 4;
	
	__DLSurface->data.at(index) = color.a;
	__DLSurface->data.at(index + 1) = color.b;
	__DLSurface->data.at(index + 2) = color.c;
	__DLSurface->data.at(index + 3) = color.d;
}

void DLSurfaceSetColor (int index, DLVec4 color)
{
	if (__DLSurface == nullptr)
	{
		return;
	}

	int pixelIndex = pixelIndex * 4;
	
	__DLSurface->data.at(pixelIndex) = color.a;
	__DLSurface->data.at(pixelIndex + 1) = color.b;
	__DLSurface->data.at(pixelIndex + 2) = color.c;
	__DLSurface->data.at(pixelIndex + 3) = color.d;
}