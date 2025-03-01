# OpenDL

OpenDL is a graphics library.

Java Prototype: https://github.com/notcl4y14/JavaOpenDL

## Features

### Buffer

Buffer is a 2D array that contains pixel values (Basically, a Texture). It can be modified and applied to other Buffers.

### Shader

Shader is an object that modifies each pixel of the Buffer with given position and color. Useful for basic Texture coloring, effects, gradients, etc.

### Path

Somewhat similar to Shaders. Path is an object that directly modifies the Buffer. Meanwhile Shaders do it pixel-by-pixel. It's useful for generating complex Textures like Text rendering, Shadow rendering, Shape rendering, etc.

Path Shaders, which are managed manually in the Path code, might become a feature.

### Planned Features

- Path Shader
- More functions for managing Buffers (probably)
- Function Overloading (probably)

## "OpenDL"?

**OpenDL** stands for **Open Drawing Library**. Because, it's basically managing and drawing Buffers.

# Example Code "Sketches"

```c
#include <DL.h>
#include "shaders.h"

int main ()
{
	DL_Init();

	DL_SetDefaultPixelSize(4);

	// Creating Shader
	DLShader gradientShader = DL_CreateShader();
	DL_ShaderSource(gradientShader, SHADERS_GRADIENT);
	DL_ShaderCompile();

	if (DL_ShaderGetErrorCode() != 0)
	{
		return 1;
	}
	
	// Creating Canvas
	DLBuffer canvas = DL_CreateBuffer(800, 600);
	DL_FillBuffer(&canvas, 255, 255, 255, 255);
	
	// Setting Shader Attributes
	DL_ShaderSetAttrib("color1", 255, 0, 0, 255);
	DL_ShaderSetAttrib("color2", 0, 0, 255, 255);
	DL_ShaderSetAttrib("point1", 0, 0);
	DL_ShaderSetAttrib("point2", 800, 0);

	// Applying Shader to Canvas
	DL_BufferApplyShader(&gradientShader);

	// Present the Canvas
	// ...

	DL_Terminate();
}
```