# OpenDL

OpenDL is a graphics library that involves the use of its own concept of graphics programming.

Java Prototype: https://github.com/notcl4y14/JavaOpenDL

## Features

### Buffer

In OpenDL, a Buffer is an array. That's it, just a basic array. There are two types of it: Texture Buffer and Attribute Buffer. The Texture Buffer stores RGBA values, meanwhile Attribute Buffer stores attributes for Shaders.

Uniform Attribute Buffer can also be created and used for Shaders/Paths.

### Shader

Shader is an object that modifies values of the Buffer with given attributes. Useful for basic Texture coloring, effects, gradients, etc.

### Path

Similar to Shaders. Path is an object that directly modifies the Buffer object, instead of modifying it pixel-by-pixel like Shaders. It's useful for generating complex Textures like Text rendering, Shadow rendering, Shape rendering, etc.

### Planned Features

- Blending for Texture Buffers
- Function Overloading

## "OpenDL"?

**OpenDL** stands for **Open Drawing Library**. ~~Because, it's basically managing and drawing Textures.~~ The name MIGHT be changed in the future.

# Example Code "Sketches"

```c
#include <DL.h>

int main ()
{
	// Initializing DL
	dlInit();

	// Loading Shaders and Paths
	char* shader_gradient_source = /* code */;
	char* path_triangle_source = /* code */;

	DLUInt shader_gradient = dlCreateShader();
	dlShaderBindSource(shader_gradient, *shader_gradient_source);
	dlShaderCompile(shader_gradient);

	if (dlShaderGetErrorCode() != 0)
	{
		printf("Shader Compilation Error: %d\n", dlShaderGetErrorCode());
		return 1;
	}
	
	DLUInt path_triangle = dlCreatePath();
	dlPathBindSource(path_triangle, *path_triangle_source);
	dlPathCompile(path_triangle);

	if (dlPathGetErrorCode() != 0)
	{
		printf("Path Compilation Error: %d\n", dlPathGetErrorCode());
		return 1;
	}

	// Initializing Canvas
	int canvas_width = 800;
	int canvas_height = 600;
	int canvas_size = canvas_width * canvas_height * 4;
	char canvas[canvas_size];

	// Filling Canvas with Color (255, 255, 255, 255)
	for (int i = 0; i < canvas_size; i++)
	{
		canvas[i] = 255;
	}

	// Setting Path Attributes
	int vertices[6] = {400,0, 0,600, 800,600};
	char triangle_color[4] = {255, 255, 255, 255};

	dlPathBindUniformAttrib(path_triangle, "vertices", vertices);
	dlPathBindUniformAttrib(path_triangle, "color", triangle_color);

	// Setting Shader Attributes
	char color1[4] = {255, 0, 0, 255};
	char color2[4] = {0, 0, 255, 255};
	char point1[2] = {0, 0};
	char point2[2] = {800, 0};

	dlShaderSetAttrib(shader_gradient, "color1", color1);
	dlShaderSetAttrib(shader_gradient, "color2", color2);
	dlShaderSetAttrib(shader_gradient, "point1", point1);
	dlShaderSetAttrib(shader_gradient, "point2", point2);

	dlApplyPath(canvas, path_triangle);
	dlApplyShader(canvas, shader_gradient);

	// Present the Canvas Buffer in PNG file,
	// window, ASCII art or something
	// ...

	dlTerminate();
	return 0;
}
```