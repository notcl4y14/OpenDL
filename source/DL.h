#ifndef DL_H
#define DL_H

#define DL_UChar unsigned char

typedef struct
{
	DL_UChar* data;
	int area;
	int count;
	int size;
} DlBuffer;

void DL_Init();

DlBuffer Dl_CreateBuffer (int count, int size);
void Dl_FreeBuffer (DlBuffer* buffer);

DL_UChar Dl_BufferGet (DlBuffer* buffer, int index, int step);
void Dl_BufferSet (DlBuffer* buffer, int index, int values, ...);

void Dl_SetBufferArea (DlBuffer* buffer, int area);
void Dl_FillBuffer (DlBuffer* buffer, int values, ...);

#endif