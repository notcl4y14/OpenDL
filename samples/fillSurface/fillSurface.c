#include <DL.h>
#include <stdio.h>

int main ()
{
	Dl_Init();

	Dl_SetDefaultPixelSize(4);

	DlBuffer surface = Dl_CreateBuffer(8, 8);
	Dl_FillBuffer(&surface, 255, 0, 255, 255);

	for (int i = 0; i < surface.area; i++)
	{
		int x = i % surface.width;
		int y = i / surface.width;

		int r = surface.data[i * surface.size];
		int g = surface.data[i * surface.size + 1];
		int b = surface.data[i * surface.size + 2];
		int a = surface.data[i * surface.size + 3];
		printf("%d,%d: %d,%d,%d,%d\n", x, y, r, g, b, a);
	}

	Dl_FreeBuffer(&surface);

	return 0;
}