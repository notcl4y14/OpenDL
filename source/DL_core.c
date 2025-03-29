#include <stdlib.h>
#include <string.h>

#include <DL_core.h>
#include <DL_DLSL.h>

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

/* One of these might get deleted.
 * They serve different purpose but
 * do absolutely the same thing.
 */
void DLBuffer_clone (DLBuffer* buffer_dest, DLBuffer* buffer_source)
{
	*buffer_dest = *buffer_source;
}

void DLBuffer_copy (DLBuffer* buffer_dest, DLBuffer* buffer_source)
{
	// memcpy(buffer_dest->data, buffer_source->data, buffer_source->size);
	*buffer_dest = *buffer_source;
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

	shader->code.data = NULL;
	shader->code.size = 0;
	shader->code.csize = 0;

	shader->attr_loc_index = 0;
	shader->attr_loc_value = 0;
}

void DLShader_free (DLShader* shader)
{
	DLAttribMap_free(&shader->attrmap);
	DLCode_free(&shader->code);
}

// 

void DLShader_apply (DLShader* shader, DLBuffer* buffer, DLSLRunner* runner)
{
	if (runner->stack != NULL)
	{
		DLSLRunner_free(runner);
	}

	DLSLRunner_initStack(runner, 64);
	DLSLRunner_bindCode(runner, &shader->code);
	DLSLRunner_bindAttrMap(runner, &shader->attrmap);

	DLuint buffer_data_loc = -1;

	while (++buffer_data_loc < buffer->csize)
	{
		shader->attrmap.attrs[shader->attr_loc_index].ptr = &buffer_data_loc;
		shader->attrmap.attrs[shader->attr_loc_value].ptr = DLBuffer_getDataUnitP(buffer, buffer_data_loc);

		DLSLRunner_run(runner);
	}
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

	path->code.data = NULL;
	path->code.size = 0;
	path->code.csize = 0;

	path->attr_loc_buffer = 0;
}

void DLPath_free (DLPath* path)
{
	DLAttribMap_free(&path->attrmap);
	DLCode_free(&path->code);
}

// 

void DLPath_apply (DLPath* path, DLBuffer* buffer, DLSLRunner* runner)
{
	path->attrmap.attrs[path->attr_loc_buffer].ptr = buffer->data;

	if (runner->stack != NULL)
	{
		DLSLRunner_free(runner);
	}

	DLSLRunner_initStack(runner, 64);
	DLSLRunner_bindCode(runner, &path->code);
	DLSLRunner_bindAttrMap(runner, &path->attrmap);

	DLSLRunner_run(runner);
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
	memcpy(attr->ptr, source, attr->size);
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

/* ////////////////
 * DLCode
 * ////////////////
 */

void DLCode_init (DLCode* code)
{
	code->data = NULL;
	code->csize = 0;
	code->size = 0;
}

void DLCode_free (DLCode* code)
{
	free(code->data);
}

// 

void DLCode_load (DLCode* code, DLdouble* data, DLuint csize)
{
	DLuint data_size = csize * sizeof(double);

	code->data = malloc(data_size);
	code->size = data_size;
	code->csize = csize;

	memcpy(code->data, data, data_size);
}