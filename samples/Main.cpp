#include <DL.h>
#include <iostream>
#include <string>
#include "Util.h"

int main ()
{
	DL_Init();

	// DLVec4 color = DLVec4 {128, 24, 10, 255};
	DLVec4 color = DLVec4 {24, 24, 10, 255};
	DLSurface surface = DL_CreateSurface(8, 8, color);
	DLSurface partSurface = DL_ClipSurface(&surface, DLVec4 {0, 0, 4, 4});

	DL_FillSurface(&partSurface, DLVec4 {100, 255, 200, 255});
	DL_DrawSurface(&surface, &partSurface, DLVec4 {0, 0, 4, 4});

	for (int i = 0; i < surface.area; i++)
	{
		int r = surface.data[i * 4];
		int g = surface.data[i * 4 + 1];
		int b = surface.data[i * 4 + 2];
		int a = surface.data[i * 4 + 3];
		std::cout << r << "," << g << "," << b << "," << a << "\n";
	}

	DL_DestroySurface(&surface);
	DL_DestroySurface(&partSurface);
	// delete[] surface.data;
}