#include <stdlib.h>
#include <string.h>

#include <DL_core.h>
#include <DL_system.h>

// void DLBuffer_init (DLBuffer* buffer, DLtype type, DLuint size)
// {
// 	buffer->data = calloc(size, sizeof(DLvoid_p));
// 	buffer->type = type;
// 	buffer->usize = DL_type_sizes[type];
// 	buffer->csize = size;
// 	buffer->size = buffer->usize * buffer->csize;
// }

/* ////////////////
 * DLBuffer
 * ////////////////
 */

void DLBuffer_init (DLBuffer* buffer, DLtype type, DLuint csize, DLuint usize)
{
	buffer->data = calloc(csize, usize);
	buffer->type = type;
	buffer->usize = usize;
	buffer->csize = csize;
	buffer->size = csize * usize;
}

void DLBuffer_free (DLBuffer* buffer)
{
	free(buffer->data);
}

// 

void DLBuffer_clear (DLBuffer* buffer)
{
	memset(buffer->data, 0, buffer->size);
}

void DLBuffer_fill (DLBuffer* buffer, DLvoid_p source)
{
	DLuint data_loc = -1;

	while (++data_loc < buffer->csize)
	{
		DLvoid_p dest_ptr = (DLchar_p)(buffer->data) + (data_loc * buffer->usize);
		memcpy(dest_ptr, source, buffer->usize);
	}
}

// 

void DLBuffer_setData (DLBuffer* buffer, DLvoid_p source, DLuint size)
{
	memcpy(buffer->data, source, size);
}

void DLBuffer_getData (DLBuffer* buffer, DLvoid_p dest)
{
	memcpy(dest, buffer->data, buffer->size);
}

// 

void DLBuffer_setDataUnit (DLBuffer* buffer, DLvoid_p source, DLuint location)
{
	DLvoid_p dest_ptr = (DLchar_p)(buffer->data) + (location * buffer->usize);
	memcpy(dest_ptr, source, buffer->usize);
}

DLvoid_p DLBuffer_getDataUnitP (DLBuffer* buffer, DLuint location)
{
	return (DLchar_p)(buffer->data) + (location * buffer->usize);
}

void DLBuffer_getDataUnit (DLBuffer* buffer, DLvoid_p dest, DLuint location)
{
	DLvoid_p source_ptr = (DLchar_p)(buffer->data) + (location * buffer->usize);
	memcpy(dest, source_ptr, buffer->usize);
}

/* ////////////////
 * DLShader
 * ////////////////
 */

void DLShader_init (DLShader* shader)
{
	shader->attrmap.attrs = NULL;
	shader->attrmap.attrs_id = NULL;
	shader->attrmap.capacity = 0;
}

void DLShader_free (DLShader* shader)
{
	DLAttribMap_free(&shader->attrmap);
}

// 

void DLShader_apply (DLShader* shader, DLBuffer* buffer)
{
	return;
}

/* ////////////////
 * DLPath
 * ////////////////
 */

void DLPath_init (DLPath* path)
{
	path->attrmap.attrs = NULL;
	path->attrmap.attrs_id = NULL;
	path->attrmap.capacity = 0;
}

void DLPath_free (DLPath* path)
{
	DLAttribMap_free(&path->attrmap);
}

// 

void DLPath_apply (DLPath* path, DLBuffer* buffer)
{
	return;
}

/* ////////////////
 * DLAttribute
 * ////////////////
 */

void DLAttribute_init (DLAttribute* attr)
{
	attr->ptr = NULL;
	attr->type = DL_NONE;
	attr->size = 0;
}

void DLAttribute_free (DLAttribute* attr)
{
	free(attr->ptr);
}

// 

void DLAttribute_setValue (DLAttribute* attr, DLvoid_p source)
{
	attr->ptr = source;
}

void DLAttribute_getValue (DLAttribute* attr, DLvoid_p dest)
{
	memcpy(dest, attr->ptr, attr->size);
}

/* ////////////////
 * DLAttribMap
 * ////////////////
 */

void DLAttribMap_init (DLAttribMap* attrmap, DLuint capacity)
{
	attrmap->attrs = calloc(capacity, sizeof(DLAttribute));
	attrmap->attrs_id = calloc(capacity, sizeof(DLchar_p*));
	attrmap->capacity = capacity;
}

void DLAttribMap_free (DLAttribMap* attrmap)
{
	DLuint loop_loc = -1;

	while (++loop_loc < attrmap->capacity)
	{
		DLchar_p id = attrmap->attrs_id[loop_loc];

		if (id == NULL)
		{
			continue;
		}

		free(id);
	}

	free(attrmap->attrs);
	free(attrmap->attrs_id);
}

// 

void DLAttribMap_bindAttribID (DLAttribMap* attrmap, DLuint location, DLchar_p id)
{
	DLuint id_len = strlen(id);
	attrmap->attrs_id[location] = malloc(id_len);
	memcpy(attrmap->attrs_id[location], id, id_len);
}

DLuint DLAttribMap_getAttribLocation (DLAttribMap* attrmap, DLchar_p id)
{
	DLuint attrs_loc = -1;

	while (++attrs_loc < attrmap->capacity)
	{
		DLchar_p attr_id = attrmap->attrs_id[attrs_loc];

		if (strcmp(id, attr_id) == 0)
		{
			return attrs_loc;
		}
	}

	return -1;
}