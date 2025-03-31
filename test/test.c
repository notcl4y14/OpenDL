#include <stdio.h>
#include <DL/DL.h>
#include <DL/dlsl.h>

DLSurface* surface;
DLShader*  shader;

DLdouble shader_code[32] =
{
	DLSL_PUSH, 40,
	// DLSL_PUSH, 30,
	// DLSL_PUSH, 20,
	// DLSL_PUSH, 10,
	DLSL_AST,  1,
	DLSL_QUIT,
};

int main ()
{
	DL_init();

	surface = DLSurface_create();
	shader  = DLShader_create();

	DLSurface_init(
		surface,
		DL_BYTE,             // Unit Type Specifier
		sizeof(DLubyte),     // Unit Size
		sizeof(DLubyte),     // Unit Stride Size
		8, 8                 // Width, Height
	);
	DLShader_init(
		shader,
		2 // AttrMap Capacity
	);

	DLShader_loadCode(shader, (DLdouble*)&shader_code, sizeof(shader_code));

	DLShader_bindAttrParams(
		shader,
		0,      // Attribute Location
		DL_INT, // Attribute Value Type Specifier
		sizeof(DLuint) * 2, // Attribute Value Size
		sizeof(DLuint)      // Attribute Value Stride Size
	);
	DLShader_bindAttrParams(
		shader,
		1,
		DL_BYTE,
		sizeof(DLubyte),
		sizeof(DLubyte)
	);
	shader->attr_loc_coord = 0;
	shader->attr_loc_color = 1;

	{
		DLubyte value = 10;
		DLSurface_fill(surface, &value);
	}

	DLShader_apply(shader, surface);

	for (int i = 0; i < surface->csize * surface->ubstride; i++)
	{
		printf("%d,", ((DLubyte*)(surface->data))[i]);
	}

	DLSurface_delete(surface);
	DLShader_delete(shader);
	DL_terminate();

	return 0;
}