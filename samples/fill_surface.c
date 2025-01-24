#include <DL.h>
#include <stdio.h>

int main ()
{
	DL_Init();
	
	DLVec4 color = {24, 24, 10, 255};
	DLSurface surface = DL_CreateSurface(8, 8);
	DL_FillSurface(&surface, color);

	for (int i = 0; i < surface.area; i++)
	{
		int x = i % surface.width;
		int y = i / surface.width;

		int r = surface.data[i * 4];
		int g = surface.data[i * 4 + 1];
		int b = surface.data[i * 4 + 2];
		int a = surface.data[i * 4 + 3];
		printf("%d,%d: %d,%d,%d,%d\n", x, y, r, g, b, a);
	}

	DL_DestroySurface(&surface);

	return 0;
}