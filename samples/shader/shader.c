#include <DL.h>
#include <stdio.h>
#include <stdlib.h>

void shaderFunc (DlShaderAttrs* shader)
{
	shader->Dl_color[0] = shader->Dl_positionX;
	shader->Dl_color[1] = shader->Dl_positionY;
	shader->Dl_color[2] = 0;
}

int main ()
{
	Dl_Init();
	Dl_SetDefaultPixelSize(4);

	DlBuffer buffer = Dl_CreateBuffer(4, 4);
	Dl_FillBuffer(&buffer, 255, 255, 255, 255);

	DlShader shader = Dl_CreateShader();
	Dl_ShaderBindCode(&shader, &shaderFunc);

	DlBuffer newBuffer = Dl_BufferApplyShader(&buffer, &shader);

	for (int i = 0; i < newBuffer.area; i++)
	{
		printf("%d,%d,%d,%d\n", newBuffer.data[i * 4], newBuffer.data[i * 4 + 1], newBuffer.data[i * 4 + 2], newBuffer.data[i * 4 + 3]);
	}

	// Dl_FreeShader(&shader);
	Dl_FreeBuffer(&buffer);
	Dl_FreeBuffer(&newBuffer);
	
	return 0;
}