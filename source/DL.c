#include <DL/DL.h>

#include <stdlib.h>
#include <string.h>

/* ================ 
 * DL System
 * ================
 */

uint32_t DL_System_Hints[4];
DLTexture* DL_System_Textures;
DLShader*  DL_System_Shaders;
DLPath*    DL_System_Paths;
uint32_t   DL_System_Textures_Count;
uint32_t   DL_System_Shaders_Count;
uint32_t   DL_System_Paths_Count;
uint32_t   DL_System_Textures_Capacity;
uint32_t   DL_System_Shaders_Capacity;
uint32_t   DL_System_Paths_Capacity;
uint8_t*   DL_System_Textures_Available;
uint8_t*   DL_System_Shaders_Available;
uint8_t*   DL_System_Paths_Available;

void DL_Init ()
{
	uint8_t init_objarr = DL_System_Hints[DL_OBJECT_ARRAYS_ENABLED];

	if (init_objarr)
	{
		uint32_t objarr_cap = DL_OBJECT_ARRAYS_ENABLED;

		DL_System_Textures_Count = 0;
		DL_System_Shaders_Count = 0;
		DL_System_Textures_Count = 0;

		DL_System_Textures_Capacity = objarr_cap;
		DL_System_Shaders_Capacity = objarr_cap;
		DL_System_Paths_Capacity = objarr_cap;

		DL_System_Textures_Available = malloc(objarr_cap);
		DL_System_Shaders_Available = malloc(objarr_cap);
		DL_System_Paths_Available = malloc(objarr_cap);

		memset(DL_System_Textures_Available, 1, objarr_cap);
		memset(DL_System_Shaders_Available, 1, objarr_cap);
		memset(DL_System_Paths_Available, 1, objarr_cap);

		DL_System_Textures = malloc(objarr_cap * sizeof(DLTexture));
		DL_System_Shaders = malloc(objarr_cap * sizeof(DLShader));
		DL_System_Paths = malloc(objarr_cap * sizeof(DLPath));
	}
}

void DL_Terminate ()
{
	if (DL_System_Hints[DL_OBJECT_ARRAYS_ENABLED])
	{
		uint32_t loop_loc;
		uint32_t loop_end;

		// Textures
		loop_loc = -1;
		loop_end = DL_System_Textures_Capacity;

		while (++loop_loc < loop_end)
		{
			if (DL_System_Textures_Available[loop_loc])
			{
				continue;
			}

			DLTexture* texture = &DL_System_Textures[loop_loc];
			DL_DeleteTexture(texture);
		}

		// Shaders
		loop_loc = -1;
		loop_end = DL_System_Shaders_Capacity;

		while (++loop_loc < loop_end)
		{
			if (DL_System_Shaders_Available[loop_loc])
			{
				continue;
			}

			DLShader* shader = &DL_System_Shaders[loop_loc];
			DL_DeleteShader(shader);
		}

		// Paths
		loop_loc = -1;
		loop_end = DL_System_Paths_Capacity;

		while (++loop_loc < loop_end)
		{
			if (DL_System_Paths_Available[loop_loc])
			{
				continue;
			}

			DLPath* path = &DL_System_Paths[loop_loc];
			DL_DeletePath(path);
		}
	}
}

void DL_Hint (uint32_t hint, uint32_t value)
{
	DL_System_Hints[hint] = value;
}

/* Private definitions
 */

// Texture

uint32_t DL_System_TextureAvailable ()
{
	uint32_t loop_loc = -1;
	uint32_t loop_end = DL_System_Textures_Capacity;

	while (++loop_loc < loop_end)
	{
		if (DL_System_Textures_Available[loop_loc])
		{
			break;
		}
	}

	return loop_loc;
}

void* DL_System_PushTexture ()
{
	void* ptr;

	switch (DL_System_Hints[DL_OBJECT_ARRAYS_ENABLED])
	{
		case 0:
			ptr = malloc(sizeof(DLTexture));
			break;

		case 1:
		{
			uint32_t location = DL_System_TextureAvailable();
			DL_System_Textures_Available[location] = 0;
			DL_System_Textures_Count++;
			ptr = DL_System_Textures + (location * sizeof(DLTexture));
		}
		break;
	}

	return ptr;
}

void DL_System_PopTexture (DLTexture* texture)
{
	switch (DL_System_Hints[DL_OBJECT_ARRAYS_ENABLED])
	{
		case 0:
			free(texture);
			break;

		case 1:
		{
			uint32_t location = (texture - DL_System_Textures) / sizeof(DLTexture);
			DL_System_Textures_Count--;
			DL_System_Textures_Available[location] = 0;
		}
		break;
	}
}

// Shader

uint32_t DL_System_ShaderAvailable ()
{
	uint32_t loop_loc = -1;
	uint32_t loop_end = DL_System_Shaders_Capacity;

	while (++loop_loc < loop_end)
	{
		if (DL_System_Shaders_Available[loop_loc])
		{
			break;
		}
	}

	return loop_loc;
}

void* DL_System_PushShader ()
{
	void* ptr;

	switch (DL_System_Hints[DL_OBJECT_ARRAYS_ENABLED])
	{
		case 0:
			ptr = malloc(sizeof(DLShader));
			break;

		case 1:
		{
			uint32_t location = DL_System_ShaderAvailable();
			DL_System_Shaders_Available[location] = 0;
			DL_System_Shaders_Count++;
			ptr = DL_System_Shaders + (location * sizeof(DLShader));
		}
		break;
	}

	return ptr;
}

void DL_System_PopShader (DLShader* shader)
{
	switch (DL_System_Hints[DL_OBJECT_ARRAYS_ENABLED])
	{
		case 0:
			free(shader);
			break;

		case 1:
		{
			uint32_t location = (shader - DL_System_Shaders) / sizeof(DLShader);
			DL_System_Shaders_Count--;
			DL_System_Shaders_Available[location] = 0;
		}
		break;
	}
}

// Path

uint32_t DL_System_PathAvailable ()
{
	uint32_t loop_loc = -1;
	uint32_t loop_end = DL_System_Paths_Capacity;

	while (++loop_loc < loop_end)
	{
		if (DL_System_Paths_Available[loop_loc])
		{
			break;
		}
	}

	return loop_loc;
}

void* DL_System_PushPath ()
{
	void* ptr;

	switch (DL_System_Hints[DL_OBJECT_ARRAYS_ENABLED])
	{
		case 0:
			ptr = malloc(sizeof(DLPath));
			break;

		case 1:
		{
			uint32_t location = DL_System_PathAvailable();
			DL_System_Paths_Available[location] = 0;
			DL_System_Paths_Count++;
			ptr = DL_System_Paths + (location * sizeof(DLPath));
		}
		break;
	}

	return ptr;
}

void DL_System_PopPath (DLPath* path)
{
	switch (DL_System_Hints[DL_OBJECT_ARRAYS_ENABLED])
	{
		case 0:
			free(path);
			break;

		case 1:
		{
			uint32_t location = (path - DL_System_Paths) / sizeof(DLPath);
			DL_System_Paths_Count--;
			DL_System_Paths_Available[location] = 0;
		}
		break;
	}
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
}

void DL_DeleteAttrList (DLAttrList* attrlist)
{
	uint32_t loop_loc;
	uint32_t loop_end;

	loop_loc = -1;
	loop_end = attrlist->data_capacity;

	while (++loop_loc < attrlist->data_capacity)
{
		DLAttr* attr = DL_AttrListGetAttr(attrlist, loop_loc);

		if (attr->value == NULL)
{
			continue;
		}

		DL_DeleteAttr(attr);
	}

	loop_loc = -1;
	// loop_end = attrlist->data_capacity;

	while (++loop_loc < attrlist->data_capacity)
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

/* ================ 
 * DLTexture
 * ================
 */

DLTexture* DL_CreateTexture (uint32_t width, uint32_t height, uint8_t unit_type, size_t unit_size, size_t unit_stride)
{
	DLTexture* texture = DL_System_PushTexture();

	size_t data_capacity = width * height;

	texture->data = calloc(data_capacity, unit_size);
	texture->data_capacity = data_capacity;
	texture->data_unit_type = unit_type;
	texture->data_unit_size = unit_size;
	texture->data_unit_stride = unit_stride;
	texture->width = width;
	texture->height = height;

	return texture;
}

DLTexture* DL_CreateTextureD (uint32_t width, uint32_t height)
{
	DLTexture* texture = DL_System_PushTexture();

	size_t data_capacity = width * height;

	texture->data = calloc(data_capacity, DL_TEXTURE_DEF_UNIT_SIZE);
	texture->data_capacity = data_capacity;
	texture->data_unit_type = DL_TEXTURE_DEF_UNIT_TYPE;
	texture->data_unit_size = DL_TEXTURE_DEF_UNIT_SIZE;
	texture->data_unit_stride = DL_TEXTURE_DEF_UNIT_STRIDE;
	texture->width = width;
	texture->height = height;

	return texture;
}

void DL_DeleteTexture (DLTexture* texture)
{
	free(texture->data);
	texture->data = NULL;

	DL_System_PopTexture(texture);
}

DLTexture* DL_CloneTexture (DLTexture* texture)
{
	DLTexture* texture_n = DL_System_PushTexture();
	memcpy(texture_n, texture, sizeof(DLTexture));

	size_t data_size = texture_n->data_capacity * texture_n->data_unit_size;

	texture_n->data = malloc(data_size);
	memcpy(texture_n->data, texture->data, data_size);
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

void DL_TextureUseShader (DLTexture* texture, DLShader* path)
{
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

/* ================ 
 * DLShader
 * ================
 */

DLShader* DL_CreateShader ()
{
	DLShader* shader = DL_System_PushShader();

	shader->func = NULL;

	return shader;
}

void DL_DeleteShader (DLShader* shader)
{
	DL_DeleteAttrList(&shader->attrlist);

	DL_System_PopShader(shader);
}

void DL_InitShaderAttrList (DLShader* shader, uint32_t capacity)
{
	DL_InitAttrList(&shader->attrlist, capacity);
}

uint32_t DL_GetShaderAttrLocation (DLShader* shader, char* id)
{
	return DL_AttrListGetAttrLocation(&shader->attrlist, id);
}

void DL_BindShaderAttrLocation (DLShader* shader, uint32_t location, char* id)
{
	DL_AttrListBindAttrLocation(&shader->attrlist, location, id);
}

void DL_InitShaderAttr (DLShader* shader, uint32_t location, uint8_t type, size_t size, size_t stride)
{
	DLAttr* attr = DL_AttrListGetAttr(&shader->attrlist, location);
	DL_InitAttr(attr, type, size, stride);
}

void DL_GetShaderAttrValue (DLShader* shader, void* to, uint32_t location)
{
	DLAttr* attr = DL_AttrListGetAttr(&shader->attrlist, location);
	DL_AttrGetValue(attr, to);
}

void DL_SetShaderAttrValue (DLShader* shader, void* from, uint32_t location)
{
	DLAttr* attr = DL_AttrListGetAttr(&shader->attrlist, location);
	DL_AttrSetValue(attr, from);
}

/* ================ 
 * DLPath
 * ================
 */

DLPath* DL_CreatePath ()
{
	DLPath* path = DL_System_PushPath();

	path->func = NULL;

	return path;
}

void DL_DeletePath (DLPath* path)
{
	DL_DeleteAttrList(&path->attrlist);

	DL_System_PopPath(path);
}

void DL_InitPathAttrList (DLPath* path, uint32_t capacity)
{
	DL_InitAttrList(&path->attrlist, capacity);
}

uint32_t DL_GetPathAttrLocation (DLPath* path, char* id)
{
	return DL_AttrListGetAttrLocation(&path->attrlist, id);
}

void DL_BindPathAttrLocation (DLPath* path, uint32_t location, char* id)
{
	DL_AttrListBindAttrLocation(&path->attrlist, location, id);
}

void DL_InitPathAttr (DLPath* path, uint32_t location, uint8_t type, size_t size, size_t stride)
{
	DLAttr* attr = DL_AttrListGetAttr(&path->attrlist, location);
	DL_InitAttr(attr, type, size, stride);
}

void DL_GetPathAttrValue (DLPath* path, void* to, uint32_t location)
{
	DLAttr* attr = DL_AttrListGetAttr(&path->attrlist, location);
	DL_AttrGetValue(attr, to);
}

void DL_SetPathAttrValue (DLPath* path, void* from, uint32_t location)
{
	DLAttr* attr = DL_AttrListGetAttr(&path->attrlist, location);
	DL_AttrSetValue(attr, from);
}