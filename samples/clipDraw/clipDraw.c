#include <DL.h>
#include <stdio.h>

void render (DlBuffer* buffer)
{
	int index = -1;

	while (++index < buffer->area)
	{
		if (index > 0 && index % buffer->width == 0)
		{
			printf("\n");
		}
		
		DL_uchar* color = &buffer->data[index * buffer->size];

		int r = color[0];
		int g = color[1];
		int b = color[2];

		int sum = r + g + b;

		if (sum == 0)
		{
			printf(".");
		}
		else if ((float)sum / (255 * 3) < 1.0f / 8.0f)
		{
			printf(",");
		}
		else if ((float)sum / (255 * 3) < 2.0f / 8.0f)
		{
			printf(":");
		}
		else if ((float)sum / (255 * 3) < 3.0f / 8.0f)
		{
			printf(";");
		}
		else if ((float)sum / (255 * 3) < 4.0f / 8.0f)
		{
			printf("#");
		}
		else if ((float)sum / (255 * 3) < 5.0f / 8.0f)
		{
			printf("&");
		}
		else if ((float)sum / (255 * 3) < 6.0f / 8.0f)
		{
			printf("%%");
		}
		else if ((float)sum / (255 * 3) < 7.0f / 8.0f)
		{
			printf("$");
		}
		else if ((float)sum / (255 * 3) <= 1)
		{
			printf("@");
		}
	}

	printf("\n");
}

void shaderCode (DlShaderAttrs* attrs)
{
	int r = attrs->Dl_color[0] + attrs->Dl_positionX * 4;
	int g = attrs->Dl_color[1] + attrs->Dl_positionY * 4;
	int b = attrs->Dl_color[2] + attrs->Dl_positionY * 4;
	attrs->Dl_color[0] = r;
	attrs->Dl_color[1] = g;
	attrs->Dl_color[2] = b;
}

int main ()
{
	Dl_Init();
	Dl_SetDefaultPixelSize(4);

	DlShader shader = Dl_CreateShader();
	Dl_ShaderBindCode(&shader, &shaderCode);

	DlBuffer buffer = Dl_CreateBuffer(64, 32);
	Dl_FillBuffer(&buffer, 0, 0, 0, 255);
	Dl_BufferApplyShader(&buffer, &shader);

	DlBuffer clippedBuffer = Dl_ClipBuffer(&buffer, 0, 0, 32, 16);
	Dl_FillBuffer(&clippedBuffer, 255, 255, 255, 255);

	Dl_DrawBuffer(&buffer, &clippedBuffer, 0, 0, 32, 16);

	render(&buffer);
	return 0;
}