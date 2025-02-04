#include "FontData.h"

uchar* FontData_getChar(uchar* fontData, char character)
{
	return &fontData[character * FONT_DATA_CHAR_SIZE];
}

void FontData_render (uchar* character, DlBuffer* buffer)
{
	int index = 2;
	int length = character[0] + 2;

	while (index < length * 2)
	{
		int x = character[index];
		int y = character[index + 1];

		y = y * -1 + (FONT_DATA_CHAR_HEIGHT - 1);

		Dl_BufferSetPixel(buffer, y * FONT_DATA_CHAR_WIDTH + x, 1);
		index += 2;
	}
}
