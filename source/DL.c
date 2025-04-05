#include <DL/DL.h>

#include <stdlib.h>
#include <string.h>

/* ================
 * DL System
 * ================
 */

uint32_t DL_System_Hints[3];

void DL_Hint (uint32_t hint, uint32_t value)
{
	DL_System_Hints[hint] = value;
}

/* ================
 * DLAttr
 * ================
 */

void DL_InitAttr (DLAttr* attr, uint8_t type, size_t size, size_t stride)
{
	attr->value = calloc(size, 1);
	attr->value_type = type;
	attr->value_size = size;
	attr->value_stride = stride;
}

void DL_DeleteAttr (DLAttr* attr)
{
	free(attr->value);
}

void DL_ReinitAttr (DLAttr* attr, uint8_t type, size_t size, size_t stride)
{
	DL_DeleteAttr(attr);
	DL_InitAttr(attr, type, size, stride);
}

void DL_AttrGetValue (DLAttr* attr, void* to)
{
	memcpy(to, attr->value, attr->value_size);
}

void DL_AttrSetValue (DLAttr* attr, void* from)
{
	memcpy(attr->value, from, attr->value_size);
}

/* ================
 * DLAttrList
 * ================
 */

void DL_InitAttrList (DLAttrList* attrlist, uint32_t data_capacity)
{
	attrlist->data_v = calloc(data_capacity, sizeof(DLAttr));
	attrlist->data_k = calloc(data_capacity, sizeof(char*));
	attrlist->data_capacity = data_capacity;

	attrlist->shader_attr_coord = 0;
	attrlist->shader_attr_color = 0;
	attrlist->path_attr_texture = 0;
}

void DL_DeleteAttrList (DLAttrList* attrlist)
{
	uint32_t loop_loc;
	uint32_t loop_end;

	loop_loc = -1;
	loop_end = attrlist->data_capacity;

	while (++loop_loc < loop_end)
	{
		DLAttr* attr = DL_AttrListGetAttr(attrlist, loop_loc);

		if (attr->value_ptr == 1)
		{
			continue;
		}

		if (attr->value == NULL)
		{
			continue;
		}

		DL_DeleteAttr(attr);
	}

	loop_loc = -1;
	// loop_end = attrlist->data_capacity;

	while (++loop_loc < loop_end)
	{
		char* id = DL_AttrListGetAttrID(attrlist, loop_loc);

		if (id == NULL)
		{
			continue;
		}

		free(id);
	}

	free(attrlist->data_v);
	free(attrlist->data_k);
}

DLAttr* DL_AttrListGetAttr (DLAttrList* attrlist, uint32_t location)
{
	return &attrlist->data_v[location];
}

char* DL_AttrListGetAttrID (DLAttrList* attrlist, uint32_t location)
{
	return attrlist->data_k[location];
}

uint32_t DL_AttrListGetAttrLocation (DLAttrList* attrlist, char* id)
{
	uint32_t location = -1;

	while (++location < attrlist->data_capacity)
	{
		char* comp_id = DL_AttrListGetAttrID(attrlist, location);

		if (strcmp(id, comp_id) == 0)
		{
			return location;
		}
	}

	return -1;
}

void DL_AttrListBindAttrLocation (DLAttrList* attrlist, uint32_t location, char* id)
{
	size_t id_size = strlen(id);
	attrlist->data_k[location] = malloc(id_size);
	memcpy(attrlist->data_k[location], id, id_size);
}

void DL_AttrListBindAttr (DLAttrList* attrlist, uint32_t location, uint8_t ptr, uint8_t type, size_t size, size_t stride)
{
	DLAttr* attr = DL_AttrListGetAttr(attrlist, location);

	attr->value = ptr ? NULL : calloc(size, 1);
	attr->value_ptr = ptr;
	attr->value_type = type;
	attr->value_size = size;
	attr->value_stride = stride;
}

void DL_AttrListBindAttrType (DLAttrList* attrlist, uint32_t location, uint8_t type)
{
	switch (type)
	{
		case DL_SHADER_ATTR_COORD:
			attrlist->shader_attr_coord = location;
			break;

		case DL_SHADER_ATTR_COLOR:
			attrlist->shader_attr_color = location;
			break;

		case DL_PATH_ATTR_TEXTURE:
			attrlist->path_attr_texture = location;
			break;
	}
}

/* ================
 * DLCode
 * ================
 */

void DL_InitCode (DLCode* code, void (*bind) (DLAttrList* attrlist))
{
	code->bind = bind;
}

void DL_DeleteCode (DLCode* code)
{
	return;
}

/* ================
 * DLTexture
 * ================
 */

DLTexture* DL_CreateTexture (uint32_t width, uint32_t height, uint8_t unit_type, size_t unit_size, size_t unit_stride)
{
	DLTexture* texture = malloc(sizeof(DLTexture));
	DL_InitTexture(texture, width, height, unit_type, unit_size, unit_stride);

	return texture;
}

DLTexture* DL_CreateTextureD (uint32_t width, uint32_t height)
{
	DLTexture* texture = malloc(sizeof(DLTexture));
	DL_InitTexture(texture,
	               width,
	               height,
	               DL_TEXTURE_DEF_UNIT_TYPE,
	               DL_TEXTURE_DEF_UNIT_SIZE,
	               DL_TEXTURE_DEF_UNIT_STRIDE);

	return texture;
}

void DL_InitTexture (DLTexture* texture, uint32_t width, uint32_t height, uint8_t unit_type, size_t unit_size, size_t unit_stride)
{
	size_t data_capacity = width * height;

	texture->data = calloc(data_capacity, unit_size);
	texture->data_capacity = data_capacity;
	texture->data_unit_type = unit_type;
	texture->data_unit_size = unit_size;
	texture->data_unit_stride = unit_stride;
	texture->width = width;
	texture->height = height;
}

void DL_DeleteTexture (DLTexture* texture)
{
	free(texture->data);
	texture->data = NULL;

	free(texture);
}

DLTexture* DL_CloneTexture (DLTexture* texture)
{
	DLTexture* texture_n = malloc(sizeof(DLTexture));
	memcpy(texture_n, texture, sizeof(DLTexture));

	size_t data_size = texture_n->data_capacity * texture_n->data_unit_size;

	texture_n->data = malloc(data_size);
	memcpy(texture_n->data, texture->data, data_size);

	return texture_n;
}

void DL_CopyTexture (DLTexture* texture, DLTexture* texture_source)
{
	memcpy(texture, texture_source, sizeof(DLTexture));

	size_t data_size = texture->data_capacity * texture->data_unit_size;

	texture->data = malloc(data_size);
	memcpy(texture->data, texture_source->data, data_size);
}

void* DL_TextureGetPixelPI (DLTexture* texture, uint32_t index)
{
	return (char*)(texture->data) + (index * texture->data_unit_size);
}

void* DL_TextureGetPixelP (DLTexture* texture, uint32_t x, uint32_t y)
{
	uint32_t index = x + y * texture->width;
	return (char*)(texture->data) + (index * texture->data_unit_size);
}

void DL_TextureGetPixelI (DLTexture* texture, void* to, uint32_t index)
{
	void* from = DL_TextureGetPixelPI(texture, index);
	memcpy(to, from, texture->data_unit_size);
}

void DL_TextureGetPixel (DLTexture* texture, void* to, uint32_t x, uint32_t y)
{
	void* from = DL_TextureGetPixelP(texture, x, y);
	memcpy(to, from, texture->data_unit_size);
}

void DL_TextureSetPixelI (DLTexture* texture, void* from, uint32_t index)
{
	void* to = DL_TextureGetPixelPI(texture, index);
	memcpy(to, from, texture->data_unit_size);
}

void DL_TextureSetPixel (DLTexture* texture, void* from, uint32_t x, uint32_t y)
{
	void* to = DL_TextureGetPixelP(texture, x, y);
	memcpy(to, from, texture->data_unit_size);
}

void DL_ResizeTexture (DLTexture* texture, uint32_t width, uint32_t height)
{
	// TODO: Finish this function
}

void DL_TextureUseShader (DLTexture* texture, DLShader* shader)
{
	DLAttrList* attrlist = DL_ShaderGetAttrList(shader);
	DLAttr* attr_coord = DL_AttrListGetAttr(attrlist, attrlist->shader_attr_coord);
	DLAttr* attr_color = DL_AttrListGetAttr(attrlist, attrlist->shader_attr_color);

	uint32_t value_coord[2];
	void*    value_color;

	uint32_t loop_loc = -1;

	while (++loop_loc != texture->data_capacity)
	{
		value_coord[0] = loop_loc % texture->width;
		value_coord[1] = loop_loc / texture->width;
		value_color    = DL_TextureGetPixelPI(texture, loop_loc);

		attr_coord->value = (uint32_t*)&value_coord;
		attr_color->value = value_color;

		shader->code.bind(attrlist);
	}
}

void DL_TextureUsePath (DLTexture* texture, DLPath* path)
{
	DLAttrList* attrlist = DL_PathGetAttrList(path);
	DLAttr* attr_texture = DL_AttrListGetAttr(attrlist, attrlist->path_attr_texture);
	attr_texture->value = texture;
	path->code.bind(attrlist);
}

/* ================
 * DLShader
 * ================
 */

DLShader* DL_CreateShader (DLAttrList* attrlist, DLCode* code)
{
	DLShader* shader = malloc(sizeof(DLShader));
	DL_InitShader(shader, attrlist, code);
	return shader;
}

void DL_InitShader (DLShader* shader, DLAttrList* attrlist, DLCode* code)
{
	if (attrlist != NULL)
	{
		shader->attrlist = *attrlist;
	}

	if (code != NULL)
	{
		shader->code = *code;
	}
}

void DL_DeleteShader (DLShader* shader)
{
	DL_DeleteAttrList(&shader->attrlist);
	DL_DeleteCode(&shader->code);

	free(shader);
}

DLAttrList* DL_ShaderGetAttrList (DLShader* shader)
{
	return &shader->attrlist;
}

DLCode* DL_ShaderGetCode (DLShader* shader)
{
	return &shader->code;
}

void DL_ShaderBindAttrList (DLShader* shader, DLAttrList* attrlist)
{
	shader->attrlist = *attrlist;
}

void DL_ShaderBindCode (DLShader* shader, DLCode* code)
{
	shader->code = *code;
}

/* ================
 * DLPath
 * ================
 */

DLPath* DL_CreatePath (DLAttrList* attrlist, DLCode* code)
{
	DLPath* path = malloc(sizeof(DLPath));

	if (attrlist != NULL)
	{
		path->attrlist = *attrlist;
	}

	if (code != NULL)
	{
		path->code = *code;
	}

	return path;
}

void DL_InitPath (DLPath* path, DLAttrList* attrlist, DLCode* code)
{
	if (attrlist != NULL)
	{
		path->attrlist = *attrlist;
	}

	if (code != NULL)
	{
		path->code = *code;
	}
}

void DL_DeletePath (DLPath* path)
{
	DL_DeleteAttrList(&path->attrlist);
	DL_DeleteCode(&path->code);

	free(path);
}

DLAttrList* DL_PathGetAttrList (DLPath* path)
{
	return &path->attrlist;
}

DLCode* DL_PathGetCode (DLPath* path)
{
	return &path->code;
}

void DL_PathBindAttrList (DLPath* path, DLAttrList* attrlist)
{
	path->attrlist = *attrlist;
}

void DL_PathBindCode (DLPath* path, DLCode* code)
{
	path->code = *code;
}