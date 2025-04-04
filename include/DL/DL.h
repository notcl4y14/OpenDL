#include <stddef.h>
#include <stdint.h>

#ifndef DL_H
#define DL_H

#define DL_FALSE 0x0
#define DL_TRUE  0x1

#define DL_TYPE_BYTE  0x01
#define DL_TYPE_SHORT 0x02
#define DL_TYPE_INT   0x03
#define DL_TYPE_LONG  0x04
#define DL_TYPE_FLOAT 0x05
#define DL_TYPE_DOUBLE 0x06

#define DL_OBJECT_ARRAYS_ENABLED   0x00
#define DL_OBJECT_ARRAYS_CAPACITY  0x01
#define DL_TEXTURE_DEF_UNIT_SIZE   0x02
#define DL_TEXTURE_DEF_UNIT_STRIDE 0x03
#define DL_TEXTURE_DEF_UNIT_TYPE   0x04

// TODO: Make structs like DLAttr and DLAttrList private if needed
struct DLAttr;
struct DLAttrList;

struct DLTexture;
struct DLShader;
struct DLPath;

typedef struct DLAttr DLAttr;
typedef struct DLAttrList DLAttrList;

typedef struct DLTexture DLTexture;
typedef struct DLShader DLShader;
typedef struct DLPath DLPath;

extern uint32_t   DL_System_Hints[4];
extern DLTexture* DL_System_Textures;
extern DLShader*  DL_System_Shaders;
extern DLPath*    DL_System_Paths;
extern uint32_t   DL_System_Textures_Count;
extern uint32_t   DL_System_Shaders_Count;
extern uint32_t   DL_System_Paths_Count;
extern uint32_t   DL_System_Textures_Capacity;
extern uint32_t   DL_System_Shaders_Capacity;
extern uint32_t   DL_System_Paths_Capacity;
extern uint8_t*   DL_System_Textures_Available;
extern uint8_t*   DL_System_Shaders_Available;
extern uint8_t*   DL_System_Paths_Available;

void DL_Init ();
void DL_Terminate ();
void DL_Hint (uint32_t hint, uint32_t value);

struct DLAttr {
	void*   value;
	uint8_t value_type;
	size_t  value_size;
	size_t  value_stride; // Used for splitting values
};

void DL_InitAttr (DLAttr* attr, uint8_t type, size_t size, size_t stride);
void DL_DeleteAttr (DLAttr* attr);

void DL_ReinitAttr (DLAttr* attr, uint8_t type, size_t size, size_t stride);

void DL_AttrGetValue (DLAttr* attr, void* to);
void DL_AttrSetValue (DLAttr* attr, void* from);

struct DLAttrList {
	DLAttr*  data_v;
	char**   data_k;
	uint32_t data_capacity;
};

void DL_InitAttrList (DLAttrList* attrlist, uint32_t data_capacity);
void DL_DeleteAttrList (DLAttrList* attrlist);

DLAttr* DL_AttrListGetAttr (DLAttrList* attrlist, uint32_t location);
char*   DL_AttrListGetAttrID (DLAttrList* attrlist, uint32_t location);

uint32_t DL_AttrListGetAttrLocation (DLAttrList* attrlist, char* id);
void     DL_AttrListBindAttrLocation (DLAttrList* attrlist, uint32_t location, char* id);

struct DLTexture {
	void*   data;
	size_t  data_capacity;
	size_t  data_unit_size;
	size_t  data_unit_stride;
	uint8_t data_unit_type;

	uint32_t width;
	uint32_t height;
};

DLTexture* DL_CreateTexture (uint32_t width, uint32_t height, uint8_t unit_type, size_t unit_size, size_t unit_stride);
DLTexture  DL_CreateTextureP (uint32_t width, uint32_t height, uint8_t unit_type, size_t unit_size, size_t unit_stride);
DLTexture* DL_CreateTextureD (uint32_t width, uint32_t height);
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
	DLAttrList attrlist;
};

DLShader* DL_CreateShader ();
DLShader  DL_CreateShaderP ();
void DL_DeleteShader (DLShader* shader);

void DL_InitShaderAttrList (DLShader* shader, uint32_t capacity);
uint32_t DL_GetShaderAttrLocation (DLShader* shader, char* id);
void DL_BindShaderAttrLocation (DLShader* shader, uint32_t location, char* id);

void DL_InitShaderAttr (DLShader* shader, uint32_t location, uint8_t type, size_t size, size_t stride);
void DL_GetShaderAttrValue (DLShader* shader, void* to, uint32_t location);
void DL_SetShaderAttrValue (DLShader* shader, void* from, uint32_t location);

struct DLPath {
	void (*func) (DLTexture* texture);
	DLAttrList attrlist;
};

DLPath* DL_CreatePath ();
DLPath  DL_CreatePathP ();
void DL_DeletePath (DLPath* path);

void DL_InitPathAttrList (DLPath* path, uint32_t capacity);
uint32_t DL_GetPathAttrLocation (DLPath* path, char* id);
void DL_BindPathAttrLocation (DLPath* path, uint32_t location, char* id);

void DL_InitPathAttr (DLPath* path, uint32_t location, uint8_t type, size_t size, size_t stride);
void DL_GetPathAttrValue (DLPath* path, void* to, uint32_t location);
void DL_SetPathAttrValue (DLPath* path, void* from, uint32_t location);

#endif