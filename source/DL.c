#include <DL/DL.h>

#include <stdlib.h>
#include <string.h>

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

void DL_TextureUseShader (DLTexture* texture, DLShader* shader) {
	uint32_t loop_loc = -1;

	while (++loop_loc < texture->data_capacity)
	{
		uint32_t coordX = loop_loc % texture->width;
		uint32_t coordY = loop_loc / texture->width;
		uint32_t coord[2] = {coordX, coordY};
		void*    color = DL_TextureGetPixelPI(texture, loop_loc);
		shader->func(coord, color);
	}
}

void DL_TextureUsePath (DLTexture* texture, DLPath* path)
{
	path->func(texture);
}

DLShader* DL_CreateShader () {
	DLShader* shader = malloc(sizeof(DLShader));

	shader->func = NULL;

	return shader;
}

void DL_DeleteShader (DLShader* shader) {
	return;
}

DLPath* DL_CreatePath () {
	DLPath* path = malloc(sizeof(DLPath));

	path->func = NULL;

	return path;
}

void DL_DeletePath (DLPath* path) {
	return;
}