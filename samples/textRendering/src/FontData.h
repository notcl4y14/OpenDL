#include <DL.h>
#include "public.h"

#ifndef FONT_DATA_H
#define FONT_DATA_H

uchar* FontData_getChar (uchar* fontData, char character);
void FontData_render (uchar* character, DlBuffer* buffer);

#endif