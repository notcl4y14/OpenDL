#include <stddef.h>
#include <stdint.h>

#ifndef DL_H
#define DL_H

#define DL_TYPE_BYTE  0x01
#define DL_TYPE_SHORT 0x02
#define DL_TYPE_INT   0x03
#define DL_TYPE_LONG  0x04
#define DL_TYPE_FLOAT 0x05
#define DL_TYPE_DOUBLE 0x06

struct DLTexture;
struct DLShader;
struct DLPath;

typedef struct DLTexture DLTexture;
typedef struct DLShader DLShader;
typedef struct DLPath DLPath;

struct DLTexture {
	void*   data;
	size_t  data_capacity;
	size_t  data_unit_size;
	uint8_t data_unit_type;

	uint32_t width;
	uint32_t height;
};

DLTexture* DL_CreateTexture (uint32_t width, uint32_t height, uint8_t unit_type, size_t unit_size);
DLTexture  DL_CreateTextureP (uint32_t width, uint32_t height, uint8_t unit_type, size_t unit_size);
void DL_DeleteTexture (DLTexture* texture);

DLTexture* DL_CloneTexture (DLTexture* texture);
void DL_CopyTexture (DLTexture* texture, DLTexture* texture_source);

void* DL_TextureGetPixelPI (DLTexture* texture, uint32_t index);
void* DL_TextureGetPixelP (DLTexture* texture, uint32_t x, uint32_t y);
void DL_TextureGetPixelI (DLTexture* texture, void* to, uint32_t index);
void DL_TextureGetPixel (DLTexture* texture, void* to, uint32_t x, uint32_t y);
void DL_TextureSetPixelI (DLTexture* texture, void* from, uint32_t index);
void DL_TextureSetPixel (DLTexture* texture, void* from, uint32_t x, uint32_t y);

void DL_ResizeTexture (DLTexture* texture, uint32_t width, uint32_t height);

void DL_TextureUseShader (DLTexture* texture, DLShader* shader);
void DL_TextureUsePath (DLTexture* texture, DLPath* path);

struct DLShader {
	void (*func) (uint32_t coord[2], void* color);
};

DLShader* DL_CreateShader ();
DLShader  DL_CreateShaderP ();
void DL_DeleteShader (DLShader* shader);

struct DLPath {
	void (*func) (DLTexture* texture);
};

DLPath* DL_CreatePath ();
DLPath  DL_CreatePathP ();
void DL_DeletePath (DLPath* path);

#endif