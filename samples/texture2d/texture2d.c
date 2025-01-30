#include <DL.h>
#include <stdio.h>

typedef struct
{
	DlBuffer buffer;
	int width;
	int height;
} Texture2D;

Texture2D Texture2D_Create (int width, int height)
{
	Texture2D texture;

	texture.width = width;
	texture.height = height;
	texture.buffer = Dl_CreateBuffer(texture.width * texture.height, 4);

	return texture;
}

void Texture2D_fill (Texture2D* texture, int r, int g, int b, int a)
{
	for (int i = 0; i < texture->buffer.count; i++)
	{
		int value = 0;

		switch (i % 4)
		{
			case 0: value = r; break;
			case 1: value = g; break;
			case 2: value = b; break;
			case 3: value = a; break;
		}

		texture->buffer.data[i] = value;
	}
}

int main ()
{
	Texture2D texture = Texture2D_Create(16, 16);
	Texture2D_fill(&texture, 0, 255, 255, 255);

	printf("Texture2D\n");
	printf("Size: %d,%d\n", texture.width, texture.height);
	printf("Area: %d\n", texture.buffer.area);
	printf("Count: %d\n", texture.buffer.count);
	printf("First Color: (%d,%d,%d,%d)\n", texture.buffer.data[0], texture.buffer.data[1], texture.buffer.data[2], texture.buffer.data[3]);
	
	Dl_FreeBuffer(&texture.buffer);

	return 0;
}