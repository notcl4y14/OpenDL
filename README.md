# OpenDL

OpenDL is a graphics library that uses its own concept of graphics programming.

Java Prototype: https://github.com/notcl4y14/JavaOpenDL

## Concept

OpenDL is pretty similar to OpenGL. To be precise, what they have in common is that they both have textures and shaders. Except in OpenGL you create vertex data, and in OpenDL you create pixel data. To add a shape in OpenGL you use vertices, and since there's no vertices in OpenDL, you could just render a shape manually by setting every pixel, use a shader OR use a path. Path is an object, that's similar to shader as an object but different in action. When using a path on a texture, it's called once (and the shader is called many times), and it edits the entire texture data (which sounds kind of useless since you could just create and use a renderer function). For example, you can create a path object that draws a white circle on a texture, and use a shader that replaces all the white pixels by a different color, shade or even another texture. Also you can create a path that does vertex processing.

## "OpenDL"?

OpenDL stands for **Open Drawing Library**.

## Plans for the library

- Add customizable (and default) compiler support for shader and path codes
- Make the library cross-compiler and bindable to other languages

## What would the code look like

```c
#include <DL/DL.h>

DLTexture* canvas_texture;
DLPath*    circle_path;
DLShader*  cool_shader;

const char* circle_path_code = /* code */;
const char* cool_shader_code = /* code */;

int main () {
	// Initialize DL hints
	DL_Hint(DL_STORE_OBJECTS, DL_TRUE);
	DL_Hint(DL_DEF_TEXTURE_UNIT_TYPE, DL_BYTE);
	DL_Hint(DL_DEF_TEXTURE_UNIT_SIZE, sizeof(char) * 4);
	DL_Hint(DL_DEF_TEXTURE_UNIT_STRIDE, sizeof(char));

	// Initialize DL system
	DL_Init();

	// Create Texture (there might be a function for creating a texture with default parameters)
	canvas_texture = DL_CreateTexture(256, 256, DL_BYTE, sizeof(char) * 4, sizeof(char));

	// Create and initialize Path
	circle_path = DL_CreatePath();
	DL_PathCompile(circle_path, circle_path_code);

	// Create and initialize Shader
	cool_shader = DL_CreateShader();
	DL_ShaderCompile(cool_shader, cool_shader_code);

	// Use Path and Shader on Texture
	DL_TextureUsePath(canvas_texture, circle_path);
	DL_TextureUseShader(canvas_texture, cool_shader);

	/**
	 * After you're done with rendering,
	 * you can apply the texture data onto the window,
	 * PNG, some array or just free it.
	 */

	// Free DL system
	DL_Terminate();

	return 0;
}