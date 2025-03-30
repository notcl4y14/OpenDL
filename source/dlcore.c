#include <stdlib.h>
#include <string.h>

#include <DL/dlcore.h>
#include <DL/dlsl.h>

/* ////////////////
 * dlBuffer
 * ////////////////
 */

void dlBuffer_init (dlBuffer* buffer, DLtype type, DLuint csize, DLuint usize)
{
	buffer->data = calloc(csize, usize);
	buffer->type = type;
	buffer->usize = usize;
	buffer->csize = csize;
	buffer->size = csize * usize;
}

void dlBuffer_free (dlBuffer* buffer)
{
	free(buffer->data);
}

// 

/* One of these might get deleted.
 * They serve different purpose but
 * do absolutely the same thing.
 */
void dlBuffer_clone (dlBuffer* buffer_dest, dlBuffer* buffer_source)
{
	*buffer_dest = *buffer_source;
}

void dlBuffer_copy (dlBuffer* buffer_dest, dlBuffer* buffer_source)
{
	*buffer_dest = *buffer_source;
}

// 

void dlBuffer_clear (dlBuffer* buffer)
{
	memset(buffer->data, 0, buffer->size);
}

void dlBuffer_fill (dlBuffer* buffer, DLvoid_p source)
{
	DLuint data_loc = -1;

	while (++data_loc < buffer->csize)
	{
		DLvoid_p dest_ptr = (DLchar_p)(buffer->data) + (data_loc * buffer->usize);
		memcpy(dest_ptr, source, buffer->usize);
	}
}

// 

void dlBuffer_getData (dlBuffer* buffer, DLvoid_p dest)
{
	memcpy(dest, buffer->data, buffer->size);
}

void dlBuffer_setData (dlBuffer* buffer, DLvoid_p source, DLuint size)
{
	memcpy(buffer->data, source, size);
}

// 

DLvoid_p dlBuffer_getDataUnitP (dlBuffer* buffer, DLuint location)
{
	return (DLchar_p)(buffer->data) + (location * buffer->usize);
}

void dlBuffer_getDataUnit (dlBuffer* buffer, DLvoid_p dest, DLuint location)
{
	DLvoid_p source_ptr = (DLchar_p)(buffer->data) + (location * buffer->usize);
	memcpy(dest, source_ptr, buffer->usize);
}

void dlBuffer_setDataUnit (dlBuffer* buffer, DLvoid_p source, DLuint location)
{
	DLvoid_p dest_ptr = (DLchar_p)(buffer->data) + (location * buffer->usize);
	memcpy(dest_ptr, source, buffer->usize);
}

// "Fun" Fact: For some reason I wrote dlSurface functions after dlShader functions
/* ////////////////
 * dlSurface
 * ////////////////
 */

void dlSurface_init (dlSurface* surface, DLtype type, DLuint usize, DLuint ustride, DLuint width, DLuint height)
{
	DLuint csize = width * height;

	surface->data = calloc(csize * ustride, usize);
	surface->size = csize * ustride * usize;
	surface->csize = csize;

	surface->utype = type;
	surface->usize = usize;
	surface->ustride = ustride;

	surface->width = width;
	surface->height = height;
}

void dlSurface_free (dlSurface* surface)
{
	free(surface->data);
}

// 

void dlSurface_clone (dlSurface* surface_dest, dlSurface* surface_source)
{
	*surface_dest = *surface_source;
}

void dlSurface_copy (dlSurface* surface_dest, dlSurface* surface_source)
{
	*surface_dest = *surface_source;
}

// 

void dlSurface_fill (dlSurface* surface, DLvoid_p source)
{
	DLuint loop_loc = -1;

	while (++loop_loc < surface->size)
	{
		DLvoid_p ptr_dest = dlSurface_getPixelPI(surface, loop_loc, 0);
		DLvoid_p ptr_source = (DLchar_p)(source) + ( (loop_loc % surface->ustride) * surface->usize);
		memcpy(ptr_dest, ptr_source, surface->usize);
	}
}

// 

void dlSurface_getData (dlSurface* surface, DLvoid_p dest)
{
	memcpy(dest, surface->data, surface->size);
}

void dlSurface_setData (dlSurface* surface, DLvoid_p source)
{
	memcpy(surface->data, source, surface->size);
}

// 

DLvoid_p dlSurface_getPixelPI (dlSurface* surface, DLuint index, DLuint offset)
{
	return (DLchar_p)(surface->data) + ((index + offset) * surface->ustride * surface->usize);
}

DLvoid_p dlSurface_getPixelP (dlSurface* surface, DLuint x, DLuint y, DLuint offset)
{
	return (DLchar_p)(surface->data) + ((y * surface->width + x + offset) * surface->ustride * surface->usize);
}

void dlSurface_getPixelI (dlSurface* surface, DLvoid_p dest, DLuint index, DLuint offset)
{
	memcpy(dest, dlSurface_getPixelPI(surface, index, offset), surface->usize);
}

void dlSurface_getPixel (dlSurface* surface, DLvoid_p dest, DLuint x, DLuint y, DLuint offset)
{
	memcpy(dest, dlSurface_getPixelP(surface, x, y, offset), surface->usize);
}

void dlSurface_setPixelI (dlSurface* surface, DLvoid_p source, DLuint index, DLuint offset)
{
	memcpy(dlSurface_getPixelPI(surface, index, offset), source, surface->usize);
}

void dlSurface_setPixel (dlSurface* surface, DLvoid_p source, DLuint x, DLuint y, DLuint offset)
{
	memcpy(dlSurface_getPixelP(surface, x, y, offset), source, surface->usize);
}

/* ////////////////
 * dlShader
 * ////////////////
 */

void dlShader_init (dlShader* shader)
{
	shader->attrmap.attrs = NULL;
	shader->attrmap.attrs_id = NULL;
	shader->attrmap.capacity = 0;

	shader->code.data = NULL;
	shader->code.size = 0;
	shader->code.csize = 0;

	shader->attr_loc_coord = 0;
	shader->attr_loc_value = 0;
}

void dlShader_free (dlShader* shader)
{
	dlAttrMap_free(&shader->attrmap);
	dlCode_free(&shader->code);
}

// 

void dlShader_apply (dlShader* shader, dlBuffer* buffer, dlslRunner* runner)
{
	if (runner->stack != NULL)
	{
		dlslRunner_free(runner);
	}

	dlslRunner_initStack(runner, 64);
	dlslRunner_bindCode(runner, &shader->code);
	dlslRunner_bindAttrMap(runner, &shader->attrmap);

	DLuint buffer_data_loc = -1;

	while (++buffer_data_loc < buffer->csize)
	{
		shader->attrmap.attrs[shader->attr_loc_coord].ptr = &buffer_data_loc;
		shader->attrmap.attrs[shader->attr_loc_value].ptr = dlBuffer_getDataUnitP(buffer, buffer_data_loc);

		dlslRunner_run(runner);
	}
}

/* ////////////////
 * dlPath
 * ////////////////
 */

void dlPath_init (dlPath* path)
{
	path->attrmap.attrs = NULL;
	path->attrmap.attrs_id = NULL;
	path->attrmap.capacity = 0;

	path->code.data = NULL;
	path->code.size = 0;
	path->code.csize = 0;

	path->attr_loc_buffer = 0;
}

void dlPath_free (dlPath* path)
{
	dlAttrMap_free(&path->attrmap);
	dlCode_free(&path->code);
}

// 

void dlPath_apply (dlPath* path, dlBuffer* buffer, dlslRunner* runner)
{
	path->attrmap.attrs[path->attr_loc_buffer].ptr = buffer->data;

	if (runner->stack != NULL)
	{
		dlslRunner_free(runner);
	}

	dlslRunner_initStack(runner, 64);
	dlslRunner_bindCode(runner, &path->code);
	dlslRunner_bindAttrMap(runner, &path->attrmap);

	dlslRunner_run(runner);
}

/* ////////////////
 * dlAttrib
 * ////////////////
 */

void dlAttrib_init (dlAttrib* attr)
{
	attr->ptr = NULL;
	attr->type = DL_NONE;
	attr->size = 0;
}

void dlAttrib_free (dlAttrib* attr)
{
	free(attr->ptr);
}

// 

void dlAttrib_setPtrValue (dlAttrib* attr, DLvoid_p source)
{
	memcpy(attr->ptr, source, attr->size);
}

void dlAttrib_getPtrValue (dlAttrib* attr, DLvoid_p dest)
{
	memcpy(dest, attr->ptr, attr->size);
}

/* ////////////////
 * dlAttrMap
 * ////////////////
 */

void dlAttrMap_init (dlAttrMap* attrmap, DLuint capacity)
{
	attrmap->attrs = calloc(capacity, sizeof(dlAttrib));
	attrmap->attrs_id = calloc(capacity, sizeof(DLchar_p));
	attrmap->capacity = capacity;
}

void dlAttrMap_free (dlAttrMap* attrmap)
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

void dlAttrMap_bindAttribID (dlAttrMap* attrmap, DLuint location, DLchar_p id)
{
	DLuint id_len = strlen(id);
	attrmap->attrs_id[location] = malloc(id_len);
	memcpy(attrmap->attrs_id[location], id, id_len);
}

DLuint dlAttrMap_getAttribLocation (dlAttrMap* attrmap, DLchar_p id)
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
 * dlCode
 * ////////////////
 */

void dlCode_init (dlCode* code)
{
	code->data = NULL;
	code->csize = 0;
	code->size = 0;
}

void dlCode_free (dlCode* code)
{
	free(code->data);
}

// 

void dlCode_load (dlCode* code, DLdouble* data, DLuint csize)
{
	DLuint data_size = csize * sizeof(double);

	code->data = malloc(data_size);
	code->size = data_size;
	code->csize = csize;

	memcpy(code->data, data, data_size);
}