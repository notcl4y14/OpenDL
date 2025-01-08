#include <DL.h>
#include <iostream>

int main ()
{
	DLInit();

	DLSurface surface = DLSurfaceCreate(1920, 1080);
	DLBindSurface(surface);

	DLSurfaceFill( DLVec4{255, 255, 255, 255} );

	DLSurface partSurface = DLSurfaceClip(DLVec4{0, 0, 2, 2});
	DLBindSurface(partSurface);

	for (int i = 0; i < partSurface.area; i++)
	{
		DLVec4 color = DLSurfaceGetColor(i);
		std::cout << color.a << "," << color.b << "," << color.c << "," << color.d << "\n";
	}
}