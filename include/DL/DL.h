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

#define DL_TEXTURE_DEF_UNIT_SIZE   0x01
#define DL_TEXTURE_DEF_UNIT_STRIDE 0x02
#define DL_TEXTURE_DEF_UNIT_TYPE   0x03

#define DL_SHADER_ATTR_COORD 0x01
#define DL_SHADER_ATTR_COLOR 0x02
#define DL_PATH_ATTR_TEXTURE 0x03 

// TODO: Make structs like DLAttr and DLAttrList private if needed
struct DLAttr;
struct DLAttrList;
struct DLCode;

struct DLTexture;
struct DLShader;
struct DLPath;

typedef struct DLAttr DLAttr;
typedef struct DLAttrList DLAttrList;
typedef struct DLCode DLCode;

typedef struct DLTexture DLTexture;
typedef struct DLShader DLShader;
typedef struct DLPath DLPath;

extern uint32_t DL_System_Hints[3];

void DL_Hint (uint32_t hint, uint32_t value);

struct DLAttr
{
	void*   value;
	uint8_t value_ptr;
	uint8_t value_type;
	size_t  value_size;
	size_t  value_stride; // Used for splitting values
};

void DL_InitAttr (DLAttr* attr, uint8_t type, size_t size, size_t stride);
void DL_DeleteAttr (DLAttr* attr);

void DL_ReinitAttr (DLAttr* attr, uint8_t type, size_t size, size_t stride);

void DL_AttrGetValue (DLAttr* attr, void* to);
void DL_AttrSetValue (DLAttr* attr, void* from);

struct DLAttrList
{
	DLAttr*  data_v;
	char**   data_k;
	uint32_t data_capacity;

	uint32_t shader_attr_coord;
	uint32_t shader_attr_color;
	uint32_t path_attr_texture;
};

void DL_InitAttrList (DLAttrList* attrlist, uint32_t data_capacity);
void DL_DeleteAttrList (DLAttrList* attrlist);

DLAttr* DL_AttrListGetAttr (DLAttrList* attrlist, uint32_t location);
char*   DL_AttrListGetAttrID (DLAttrList* attrlist, uint32_t location);

uint32_t DL_AttrListGetAttrLocation (DLAttrList* attrlist, char* id);
void     DL_AttrListBindAttrLocation (DLAttrList* attrlist, uint32_t location, char* id);

void DL_AttrListBindAttr (DLAttrList* attrlist, uint32_t location, uint8_t ptr, uint8_t type, size_t size, size_t stride);
void DL_AttrListBindAttrType (DLAttrList* attrlist, uint32_t location, uint8_t type);

struct DLCode
{
	void (*bind) (DLAttrList* attrlist);
};

void DL_InitCode (DLCode* code, void (*bind) (DLAttrList* attrlist));
void DL_DeleteCode (DLCode* code);

struct DLTexture
{
	void*   data;
	size_t  data_capacity;
	size_t  data_unit_size;
	size_t  data_unit_stride;
	uint8_t data_unit_type;

	uint32_t width;
	uint32_t height;
};

DLTexture* DL_CreateTexture (uint32_t width, uint32_t height, uint8_t unit_type, size_t unit_size, size_t unit_stride);
DLTexture* DL_CreateTextureD (uint32_t width, uint32_t height);
void DL_InitTexture (DLTexture* texture, uint32_t width, uint32_t height, uint8_t unit_type, size_t unit_size, size_t unit_stride);
void DL_InitTextureD (DLTexture* texture, uint32_t width, uint32_t height);
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

struct DLShader
{
	DLCode code;
	DLAttrList attrlist;
};

DLShader* DL_CreateShader (DLAttrList* attrlist, DLCode* code);
void DL_InitShader (DLShader* shader, DLAttrList* attrlist, DLCode* code);
void DL_DeleteShader (DLShader* shader);

DLAttrList* DL_ShaderGetAttrList (DLShader* shader);
DLCode*     DL_ShaderGetCode (DLShader* shader);

void DL_ShaderBindAttrList (DLShader* shader, DLAttrList* attrlist);
void DL_ShaderBindCode (DLShader* shader, DLCode* code);

struct DLPath
{
	DLCode code;
	DLAttrList attrlist;
};

DLPath* DL_CreatePath (DLAttrList* attrlist, DLCode* code);
void DL_InitPath (DLPath* path, DLAttrList* attrlist, DLCode* code);
void DL_DeletePath (DLPath* path);

DLAttrList* DL_PathGetAttrList (DLPath* path);
DLCode*     DL_PathGetCode (DLPath* path);

void DL_PathBindAttrList (DLPath* path, DLAttrList* attrlist);
void DL_PathBindCode (DLPath* path, DLCode* code);

#endif