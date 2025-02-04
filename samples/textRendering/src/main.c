#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <DL.h>
#include "public.h"
#include "FontData.h"
#include "util.h"

uchar* fontData;
DlBuffer* fontBitmapData;

void loadFontData (uchar* fontData)
{
	int position = 0;
	int count = 0;

	// A
	position = 'A' * FONT_DATA_CHAR_SIZE;
	count = position;

	fontData[count++]     = 10;
	fontData[count++]     = 0;

	fontData[count++]     = 0;
	fontData[count++]     = 0;
	fontData[count++]     = 0;
	fontData[count++]     = 1;
	fontData[count++]     = 0;
	fontData[count++]     = 2;

	fontData[count++]     = 1;
	fontData[count++]     = 1;
	fontData[count++]     = 1;
	fontData[count++]     = 3;

	fontData[count++]     = 2;
	fontData[count++]     = 1;
	fontData[count++]     = 2;
	fontData[count++]     = 3;

	fontData[count++]     = 3;
	fontData[count++]     = 0;
	fontData[count++]     = 3;
	fontData[count++]     = 1;
	fontData[count++]     = 3;
	fontData[count++]     = 2;
}

void Text_render (DlBuffer* buffer, DlBuffer* fontBitmapData, char* text, int x, int y)
{
	int index = 0;
	int length = strlen(text);

	while (index < length)
	{
		char character = text[index];

		if (character == ' ')
		{
			index++;
			continue;
		}

		int rx1 = x + index * (FONT_DATA_CHAR_WIDTH + 1);
		int ry1 = y;
		int rx2 = rx1 + FONT_DATA_CHAR_WIDTH;
		int ry2 = ry1 + FONT_DATA_CHAR_HEIGHT;

		DlBuffer* charBuffer = &fontBitmapData[character];
		Dl_DrawBuffer(buffer, charBuffer, rx1, ry1, rx2, ry2);

		index++;
	}
}

int main ()
{
	Dl_Init();
	Dl_SetDefaultPixelSize(1);

	// Load Font Data
	printf("Loading Font Data...\n");
	fontData = (uchar*)malloc(FONT_DATA_LENGTH * FONT_DATA_CHAR_SIZE * sizeof(uchar));
	loadFontData(fontData);
	
	// Load Font Bitmap Data
	printf("Saving them into a bitmap...\n");
	fontBitmapData = (DlBuffer*)malloc(FONT_DATA_LENGTH * FONT_DATA_CHAR_WIDTH * FONT_DATA_CHAR_HEIGHT * sizeof(DlBuffer));

	fontBitmapData['A'] = Dl_CreateBuffer(4, 4);
	Dl_FillBuffer(&fontBitmapData['A'], 0);
	FontData_render(FontData_getChar(fontData, 'A'), &fontBitmapData['A']);

	printf("Done!\n");

	printf("Creating Canvas...\n");
	// Drawing onto the Canvas
	DlBuffer canvas = Dl_CreateBuffer(64, 64);
	Dl_FillBuffer(&canvas, 0);

	printf("Rendering text...\n");
	Text_render(&canvas, fontBitmapData, "AAAAAA AAA A", 0, 0);
	Text_render(&canvas, fontBitmapData, "AAA AA AAA A", 1, (4 + 1));
	Text_render(&canvas, fontBitmapData, "AAA AA AAA A", 2, (4 + 1) * 2);
	Text_render(&canvas, fontBitmapData, "AAA AA AAA A", 3, (4 + 1) * 3);
	Text_render(&canvas, fontBitmapData, "AAA AA AAA A", 4, (4 + 1) * 4);
	Text_render(&canvas, fontBitmapData, "AAA AA AAA A", 5, (4 + 1) * 5);
	Text_render(&canvas, fontBitmapData, "AAA AA AAA A", 4, (4 + 1) * 6);
	Text_render(&canvas, fontBitmapData, "AAA AA AAA A", 3, (4 + 1) * 7);
	Text_render(&canvas, fontBitmapData, "AAA AA AAA A", 2, (4 + 1) * 8);
	Text_render(&canvas, fontBitmapData, "AAA AA AAA A", 1, (4 + 1) * 9);
	Text_render(&canvas, fontBitmapData, "AAA AA AAA A", 0, (4 + 1) * 10);
	Text_render(&canvas, fontBitmapData, "AAA AA AAA A", 1, (4 + 1) * 11);
	Text_render(&canvas, fontBitmapData, "AAA AA AAA A", 2, (4 + 1) * 12);
	
	printf("Saving...\n");
	// Saving into a file
	Util_saveToFile(&canvas, "output.txt");
	printf("Done!\n");
	return 0;
}