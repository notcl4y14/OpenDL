#ifndef DL_H
#define DL_H

#define DL_UChar unsigned char

typedef struct
{
	DL_UChar* data;
	int width;
	int height;
	int area;
	int count;
	int size;
} DlBuffer;

static unsigned int __Dl_DefaultPixelSize = 1;

void Dl_Init();

void Dl_SetDefaultPixelSize (unsigned int size);

DlBuffer Dl_CreateBuffer (int width, int height);
void Dl_FreeBuffer (DlBuffer* buffer);

DL_UChar Dl_BufferGetPixel (DlBuffer* buffer, int index, int step);
DL_UChar Dl_BufferGetPixelAt (DlBuffer* buffer, int x, int y, int step);
void Dl_BufferSetPixel (DlBuffer* buffer, int index, ...);
void Dl_BufferSetPixelAt (DlBuffer* buffer, int x, int y, ...);

void Dl_SetBufferSize (DlBuffer* buffer, int width, int height);
void Dl_FillBuffer (DlBuffer* buffer, ...);

#endif