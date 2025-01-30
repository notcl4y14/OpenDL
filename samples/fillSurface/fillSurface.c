#include <DL.h>
#include <stdio.h>

int main ()
{
	DL_Init();

	int surfaceWidth = 8;
	int surfaceHeight = 8;
	int surfaceColorSize = 4;
	
	DlBuffer surface = Dl_CreateBuffer(surfaceWidth * surfaceHeight, surfaceColorSize);
	Dl_FillBuffer(&surface, 0, 255, 0, 255, 255);

	for (int i = 0; i < surface.area; i++)
	{
		int x = i % surfaceWidth;
		int y = i / surfaceWidth;

		int r = surface.data[i * surfaceColorSize];
		int g = surface.data[i * surfaceColorSize + 1];
		int b = surface.data[i * surfaceColorSize + 2];
		int a = surface.data[i * surfaceColorSize + 3];
		printf("%d,%d: %d,%d,%d,%d\n", x, y, r, g, b, a);
	}

	Dl_FreeBuffer(&surface);

	return 0;
}