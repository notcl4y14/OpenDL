#include <DL.h>
#include <stdio.h>

void render (DlBuffer* buffer)
{
	int blackCount = 0;
	int whiteCount = 0;

	int index = -1;

	while (++index < buffer->area)
	{
		if (index > 0 && index % buffer->width == 0)
		{
			printf("\n");
		}

		DL_uchar r = *Dl_BufferGetPixel(buffer, index, 0);
		DL_uchar g = *Dl_BufferGetPixel(buffer, index, 1);
		DL_uchar b = *Dl_BufferGetPixel(buffer, index, 2);

		int sum = r + g + b;

		if (sum == 0)
		{
			printf(".");
			blackCount++;
		}
		else if (sum == 255 * 3)
		{
			printf("#");
			whiteCount++;
		}
	}

	printf("\n");

	printf("Black pixels: %f%%\n", (float)blackCount / (float)buffer->area * 100);
	printf("White pixels: %f%%\n", (float)whiteCount / (float)buffer->area * 100);
}

void pathCode (DlPathAttrs* path)
{
	int offsetX = path->buffer->width / 2;
	int offsetY = path->buffer->height / 2;
	
	for (int x = 0; x < path->buffer->width; x++)
	{
		for (int y = 0; y < path->buffer->height; y++)
		{
			int rx = x - offsetX;
			int ry = y - offsetY;
			int isTrue = rx * rx + ry * ry
				<= path->buffer->width;
			
			if (isTrue)
			{
				Dl_BufferSetPixelAt(path->buffer, x, y, 255, 255, 255, 255);
			}
		}
	}
}

int main ()
{
	Dl_Init();

	Dl_SetDefaultPixelSize(4);

	DlBuffer buffer = Dl_CreateBuffer(32, 16);
	Dl_FillBuffer(&buffer, 0, 0, 0, 255);

	printf("Before applying Path\n");
	render(&buffer);

	DlPath path = Dl_CreatePath();
	Dl_PathBindCode(&path, &pathCode);

	buffer = Dl_BufferApplyPath(&buffer, &path);

	printf("After applying Path\n");
	render(&buffer);
	return 0;
}