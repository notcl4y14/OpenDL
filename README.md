# OpenDL

OpenDL is a graphics library.

Java Prototype: https://github.com/notcl4y14/JavaOpenDL

## Features

### Surface

Surface is a 2D array that contains RGBA values (Basically, a Texture). It can be modified and applied to other Surfaces.

### Planned Features

- Shader
- Path

## "OpenDL"?

**OpenDL** stands for **Open Drawing Library**. Because, it's basically managing and drawing Surfaces.

# Example Code "Sketches"

```c++
#include <DL.h>
#include "shaders.h"

int main ()
{
	DLInit();

	DLShader gradientShader = DLCreateShader();
	DLShaderSource(gradientShader, SHADERS_GRADIENT);
	DLShaderCompile();

	if (DLShaderGetErrorCode() != 0)
	{
		throw DLShaderGetError();
	}
	
	DLSurface canvas = DLCreateSurface(800, 600);
	DLBindSurface(canvas);
	DLSurfaceFill( DLVec4(255, 255, 255, 255) );
	
	DLBindShader(gradientShader);
	DLShaderSetAttrib("color1", DLVec4(255, 0, 0, 255));
	DLShaderSetAttrib("color2", DLVec4(0, 0, 255, 255));
	DLShaderSetAttrib("point1", DLVec2(0, 0));
	DLShaderSetAttrib("point2", DLVec2(800, 0));

	DLSurfaceApplyShader(gradientShader);

	// Present the Canvas
	// ...

	DLTerminate();
}
```
```c++
#include <DL.h>
#include "shaders.h"

int main ()
{
	DLShader gradientShader = DLShader();
	gradientShader.setSource(SHADERS_GRADIENT);
	
	if (gradientShader.compile() != 0)
	{
		throw gradientShader.getError();
	}

	DLSurface canvas = DLSurface(800, 600);
	canvas.fill( DLVec4(255, 255, 255, 255) );

	gradientShader.setAttrib("color1", DLVec4(255, 0, 0, 255));
	gradientShader.setAttrib("color2", DLVec4(0, 0, 255, 255));
	gradientShader.setAttrib("point1", DLVec2(0, 0));
	gradientShader.setAttrib("point2", DLVec2(800, 0));

	canvas = canvas.applyShader(gradientShader);

	// Present the Canvas
	// ...
}
```