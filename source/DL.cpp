#include <DL.h>

void DL_Init ()
{
	return;
}

// =========================== //
// ======== DLSurface ======== //
// =========================== //

DLSurface DL_CreateSurface (int width, int height)
{
	DLSurface surface;

	surface.width = width;
	surface.height = height;
	surface.area = surface.width * surface.height;
	surface.count = surface.area * 4;
	surface.data = new DL_UChar[surface.count];

	return surface;
}

DLSurface DL_CreateSurface (int width, int height, DL_UChar* color)
{
	DLSurface surface = DL_CreateSurface(width, height);

	int index = -1;

	while (++index < surface.count)
	{
		surface.data[index] = color[index % 4];
	}

	return surface;
}

DLSurface DL_CreateSurface (int width, int height, DLVec4 color)
{
	DLSurface surface = DL_CreateSurface(width, height);

	int index = -1;

	while (++index < surface.count)
	{
		surface.data[index] = DL_GetVectorValue(color, index);
	}

	return surface;
}

void DL_DestroySurface (DLSurface* surface)
{
	delete[] surface->data;
}

// ================================ //

DLVec4 DL_SurfaceGetColor (DLSurface* surface, int x, int y)
{
	return DL_SurfaceGetColor(surface, y * surface->width + x);
}

DLVec4 DL_SurfaceGetColor (DLSurface* surface, int index)
{
	int pixelIndex = index * 4;

	DLVec4 color;
	color.a = surface->data[pixelIndex];
	color.b = surface->data[pixelIndex + 1];
	color.c = surface->data[pixelIndex + 2];
	color.d = surface->data[pixelIndex + 3];

	return color;
}

void DL_SurfaceSetColor (DLSurface* surface, int x, int y, DLVec4 color)
{
	DL_SurfaceSetColor(surface, y * surface->width + x, color);
}

void DL_SurfaceSetColor (DLSurface* surface, int index, DLVec4 color)
{
	int pixelIndex = index * 4;
	surface->data[pixelIndex] = color.a;
	surface->data[pixelIndex + 1] = color.b;
	surface->data[pixelIndex + 2] = color.c;
	surface->data[pixelIndex + 3] = color.d;
}

// ================================ //

DLSurface DL_ClipSurface (DLSurface* surface, DLVec4 rect)
{
	return DL_ClipSurface(surface, rect.a, rect.b, rect.c, rect.d);
}

DLSurface DL_ClipSurface (DLSurface* surface, int x1, int y1, int x2, int y2)
{
	int width = x2 - x1;
	int height = y2 - y1;
	
	DLSurface newSurface = DL_CreateSurface(width, height);

	int x = x1;
	int y = y1;

	while (x < x2)
	{
		while (y < y2)
		{
			DLVec4 color = DL_SurfaceGetColor(surface, x, y);

			int pixelX = x - x1;
			int pixelY = y - y1;
			int index = (pixelY * newSurface.width + pixelX) * 4;

			newSurface.data[index] = color.a;
			newSurface.data[index + 1] = color.b;
			newSurface.data[index + 2] = color.c;
			newSurface.data[index + 3] = color.d;
			
			y++;
		}

		x++;
		y = y1;
	}

	return newSurface;
}

// ================================ //

void DL_FillSurface (DLSurface* surface, DLVec4 color)
{
	int index = -1;

	while (++index < surface->count)
	{
		surface->data[index] = DL_GetVectorValue(color, index);
	}
}

void DL_DrawSurface (DLSurface* dest, DLSurface* src, DLVec4 rect)
{
	int x1 = rect.a;
	int y1 = rect.b;
	int x2 = rect.c;
	int y2 = rect.d;

	int width = x2 - x1;
	int height = y2 - y1;
	int area = width * height;

	// For some reason putting "dest" instead of "src" here randomized the output
	float widthFraction = src->width / width;
	float heightFraction = src->height / height;

	for (int i = 0; i < area; i++)
	{
		int x = i % width;
		int y = i / width;
		int pixelX = x * widthFraction;
		int pixelY = y * heightFraction;

		DLVec4 color = DL_SurfaceGetColor(src, pixelX, pixelY);
		DL_SurfaceSetColor(dest, x + x1, y + y1, color);
	}
}

// ======================== //
// ======== DLVec4 ======== //
// ======================== //

float DL_GetVectorValue (DLVec4 vector, int index)
{
	switch (index % 4)
	{
		case 0:
			return vector.a;
		
		case 1:
			return vector.b;
		
		case 2:
			return vector.c;
		
		case 3:
			return vector.d;
		
		default:
			return 0;
	}
}