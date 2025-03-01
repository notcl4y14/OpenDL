#include <DL.h>
#include <stdio.h>
#include <stdlib.h>

void shaderFunc (DlShaderAttrs* shader)
{
	shader->Dl_color[0] = shader->Dl_positionX * shader->values[0];
	shader->Dl_color[1] = shader->Dl_positionY * shader->values[0];
	shader->Dl_color[2] = 0;
}

void renderAttribs (DlShaderAttrs* shader)
{
	printf("DlShader Attribs (%d):\n", shader->count);
	for (int i = 0; i < shader->count; i++)
	{
		printf("- \"%s\" (%d): %d\n", shader->ids[i], i, shader->values[i]);
	}
}

int main ()
{
	Dl_Init();
	Dl_SetDefaultPixelSize(4);

	DlBuffer buffer = Dl_CreateBuffer(4, 4);
	Dl_FillBuffer(&buffer, 255, 255, 255, 255);

	DlShader shader = Dl_CreateShader();
	Dl_ShaderInit(&shader, 1); // Initializing shader attrib map for 1 value
	Dl_ShaderBindAttrib(&shader, "multiplier", 0);
	Dl_ShaderBindCode(&shader, &shaderFunc);

	// Dl_SetShaderAttrib(&shader, 0, 4);
	Dl_SetShaderAttribID(&shader, "multiplier", 4);

	renderAttribs(&shader.attrs);

	DlBuffer newBuffer = Dl_BufferApplyShader(&buffer, &shader);

	printf("DlBuffer data:\n");
	for (int i = 0; i < newBuffer.area; i++)
	{
		printf("%d,%d,%d,%d\n", newBuffer.data[i * 4], newBuffer.data[i * 4 + 1], newBuffer.data[i * 4 + 2], newBuffer.data[i * 4 + 3]);
	}

	// Dl_FreeShader(&shader);
	Dl_FreeBuffer(&buffer);
	Dl_FreeBuffer(&newBuffer);
	
	return 0;
}