#include <DL/DL.h>

#include <stdlib.h>
#include <string.h>

void DL_InitAttr (DLAttr* attr, uint8_t type, size_t size, size_t stride) {
	attr->value = calloc(size, 1);
	attr->value_type = type;
	attr->value_size = size;
	attr->value_stride = stride;
}

void DL_DeleteAttr (DLAttr* attr) {
	free(attr->value);
}

void DL_ReinitAttr (DLAttr* attr, uint8_t type, size_t size, size_t stride) {
	DL_DeleteAttr(attr);
	DL_InitAttr(attr, type, size, stride);
}

void DL_AttrGetValue (DLAttr* attr, void* to) {
	memcpy(to, attr->value, attr->value_size);
}

void DL_AttrSetValue (DLAttr* attr, void* from) {
	memcpy(attr->value, from, attr->value_size);
}

void DL_InitAttrList (DLAttrList* attrlist, uint32_t data_capacity) {
	attrlist->data_v = calloc(data_capacity, sizeof(DLAttr));
	attrlist->data_k = calloc(data_capacity, sizeof(char*));
	attrlist->data_capacity = data_capacity;
}

void DL_DeleteAttrList (DLAttrList* attrlist) {
	uint32_t loop_loc = -1;

	while (++loop_loc < attrlist->data_capacity) {
		DLAttr* attr = DL_AttrListGetAttr(attrlist, loop_loc);

		if (attr->value == NULL) {
			continue;
		}

		DL_DeleteAttr(attr);
	}

	loop_loc = -1;

	while (++loop_loc < attrlist->data_capacity) {
		char* id = DL_AttrListGetAttrID(attrlist, loop_loc);

		if (id == NULL) {
			continue;
		}

		free(id);
	}

	free(attrlist->data_v);
	free(attrlist->data_k);
}

DLAttr* DL_AttrListGetAttr (DLAttrList* attrlist, uint32_t location) {
	return &attrlist->data_v[location];
}

char* DL_AttrListGetAttrID (DLAttrList* attrlist, uint32_t location) {
	return attrlist->data_k[location];
}

uint32_t DL_AttrListGetAttrLocation (DLAttrList* attrlist, char* id) {
	uint32_t location = -1;

	while (++location < attrlist->data_capacity) {
		char* comp_id = DL_AttrListGetAttrID(attrlist, location);

		if (strcmp(id, comp_id) == 0) {
			return location;
		}
	}

	return -1;
}

void DL_AttrListBindAttrLocation (DLAttrList* attrlist, uint32_t location, char* id) {
	size_t id_size = strlen(id);
	attrlist->data_k[location] = malloc(id_size);
	memcpy(attrlist->data_k[location], id, id_size);
}

DLTexture* DL_CreateTexture (uint32_t width, uint32_t height, uint8_t unit_type, size_t unit_size) {
	DLTexture* texture = malloc(sizeof(DLTexture));

	size_t data_capacity = width * height;

	texture->data = calloc(data_capacity, unit_size);
	texture->data_capacity = data_capacity;
	texture->data_unit_type = unit_type;
	texture->data_unit_size = unit_size;
	texture->width = width;
	texture->height = height;

	return texture;
}

void DL_DeleteTexture (DLTexture* texture) {
	free(texture->data);
	texture->data = NULL;
}

DLTexture* DL_CloneTexture (DLTexture* texture) {
	DLTexture* texture_n;
	memcpy(texture_n, texture, sizeof(DLTexture));

	size_t data_size =
		texture_n->data_capacity * texture_n->data_unit_size;

	texture_n->data = malloc(data_size);
	memcpy(texture_n->data, texture->data, data_size);
}

void DL_CopyTexture (DLTexture* texture, DLTexture* texture_source) {
	memcpy(texture, texture_source, sizeof(DLTexture));

	size_t data_size =
		texture->data_capacity * texture->data_unit_size;

	texture->data = malloc(data_size);
	memcpy(texture->data, texture_source->data, data_size);
}

void* DL_TextureGetPixelPI (DLTexture* texture, uint32_t index) {
	return (char*)(texture->data) + (index * texture->data_unit_size);
}

void* DL_TextureGetPixelP (DLTexture* texture, uint32_t x, uint32_t y) {
	uint32_t index = x + y * texture->width;
	return (char*)(texture->data) + (index * texture->data_unit_size);
}

void DL_TextureGetPixelI (DLTexture* texture, void* to, uint32_t index) {
	void* from = DL_TextureGetPixelPI(texture, index);
	memcpy(to, from, texture->data_unit_size);
}

void DL_TextureGetPixel (DLTexture* texture, void* to, uint32_t x, uint32_t y)
{
	void* from = DL_TextureGetPixelP(texture, x, y);
	memcpy(to, from, texture->data_unit_size);
}

void DL_TextureSetPixelI (DLTexture* texture, void* from, uint32_t index) {
	void* to = DL_TextureGetPixelPI(texture, index);
	memcpy(to, from, texture->data_unit_size);
}

void DL_TextureSetPixel (DLTexture* texture, void* from, uint32_t x, uint32_t y) {
	void* to = DL_TextureGetPixelP(texture, x, y);
	memcpy(to, from, texture->data_unit_size);
}

void DL_ResizeTexture (DLTexture* texture, uint32_t width, uint32_t height) {
	// TODO: Finish this function
}

void DL_TextureUseShader (DLTexture* texture, DLShader* path) {
	uint32_t loop_loc = -1;

	while (++loop_loc < texture->data_capacity)
	{
		uint32_t coordX = loop_loc % texture->width;
		uint32_t coordY = loop_loc / texture->width;
		uint32_t coord[2] = {coordX, coordY};
		void*    color = DL_TextureGetPixelPI(texture, loop_loc);
		path->func(coord, color);
	}
}

void DL_TextureUsePath (DLTexture* texture, DLPath* path)
{
	path->func(texture);
}

DLShader* DL_CreateShader () {
	DLShader* path = malloc(sizeof(DLShader));

	path->func = NULL;

	return path;
}

void DL_DeleteShader (DLShader* path) {
	return;
}

void DL_InitShaderAttrList (DLShader* path, uint32_t capacity) {
	DL_InitAttrList(&path->attrlist, capacity);
}

uint32_t DL_GetShaderAttrLocation (DLShader* path, char* id) {
	return DL_AttrListGetAttrLocation(&path->attrlist, id);
}

void DL_BindShaderAttrLocation (DLShader* path, uint32_t location, char* id) {
	DL_AttrListBindAttrLocation(&path->attrlist, location, id);
}

void DL_InitShaderAttr (DLShader* path, uint32_t location, uint8_t type, size_t size, size_t stride) {
	DLAttr* attr = DL_AttrListGetAttr(&path->attrlist, location);
	DL_InitAttr(attr, type, size, stride);
}

void DL_GetShaderAttrValue (DLShader* path, void* to, uint32_t location) {
	DLAttr* attr = DL_AttrListGetAttr(&path->attrlist, location);
	DL_AttrGetValue(attr, to);
}

void DL_SetShaderAttrValue (DLShader* path, void* from, uint32_t location) {
	DLAttr* attr = DL_AttrListGetAttr(&path->attrlist, location);
	DL_AttrSetValue(attr, from);
}

DLPath* DL_CreatePath () {
	DLPath* path = malloc(sizeof(DLPath));

	path->func = NULL;

	return path;
}

void DL_DeletePath (DLPath* path) {
	return;
}

void DL_InitPathAttrList (DLPath* path, uint32_t capacity) {
	DL_InitAttrList(&path->attrlist, capacity);
}

uint32_t DL_GetPathAttrLocation (DLPath* path, char* id) {
	return DL_AttrListGetAttrLocation(&path->attrlist, id);
}

void DL_BindPathAttrLocation (DLPath* path, uint32_t location, char* id) {
	DL_AttrListBindAttrLocation(&path->attrlist, location, id);
}

void DL_InitPathAttr (DLPath* path, uint32_t location, uint8_t type, size_t size, size_t stride) {
	DLAttr* attr = DL_AttrListGetAttr(&path->attrlist, location);
	DL_InitAttr(attr, type, size, stride);
}

void DL_GetPathAttrValue (DLPath* path, void* to, uint32_t location) {
	DLAttr* attr = DL_AttrListGetAttr(&path->attrlist, location);
	DL_AttrGetValue(attr, to);
}

void DL_SetPathAttrValue (DLPath* path, void* from, uint32_t location) {
	DLAttr* attr = DL_AttrListGetAttr(&path->attrlist, location);
	DL_AttrSetValue(attr, from);
}