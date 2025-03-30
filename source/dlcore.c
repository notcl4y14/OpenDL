#include <stdlib.h>
#include <string.h>

#include <DL/dlcore.h>
#include <DL/dlsystem.h>
#include <DL/dlsl.h>

/* ////////////////
 * DLBuffer
 * ////////////////
 */

DLBuffer* DLBuffer_create ()
{
	DLBuffer* buffer = calloc(sizeof(DLBuffer), 1);
	return buffer;
}

void DLBuffer_delete (DLBuffer* buffer)
{
	free(buffer->data);
	free(buffer);
}

// 

void DLBuffer_init (DLBuffer* buffer, DLtype type, DLuint csize, DLuint usize)
{
	buffer->data = calloc(csize, usize);
	buffer->size = csize * usize;
	buffer->csize = csize;

	buffer->utype = type;
	buffer->usize = usize;
}

// 

DLBuffer* DLBuffer_clone (DLBuffer* buffer)
{
	DLBuffer* buffer_n = calloc(sizeof(DLBuffer), 1);
	*buffer_n = *buffer;
	return buffer_n;
}

void DLBuffer_copy (DLBuffer* buffer_dest, DLBuffer* buffer_source)
{
	*buffer_dest = *buffer_source;
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

void DLBuffer_getData (DLBuffer* buffer, DLvoid_p dest)
{
	memcpy(dest, buffer->data, buffer->size);
}

void DLBuffer_loadData (DLBuffer* buffer, DLvoid_p source, DLuint size)
{
	memcpy(buffer->data, source, size);
}

// 

DLvoid_p DLBuffer_getDataUnitP (DLBuffer* buffer, DLuint location)
{
	return (DLchar_p)(buffer->data) + (location * buffer->usize);
}

void DLBuffer_getDataUnit (DLBuffer* buffer, DLvoid_p dest, DLuint location)
{
	DLvoid_p source_ptr = (DLchar_p)(buffer->data) + (location * buffer->usize);
	memcpy(dest, source_ptr, buffer->usize);
}

void DLBuffer_setDataUnit (DLBuffer* buffer, DLvoid_p source, DLuint location)
{
	DLvoid_p dest_ptr = (DLchar_p)(buffer->data) + (location * buffer->usize);
	memcpy(dest_ptr, source, buffer->usize);
}

// "Fun" Fact: For some reason I wrote DLSurface functions after DLShader functions
/* ////////////////
 * DLSurface
 * ////////////////
 */

DLSurface* DLSurface_create ()
{
	DLSurface* surface = calloc(sizeof(DLSurface), 1);
	return surface;
}

void DLSurface_delete (DLSurface* surface)
{
	free(surface->data);
	free(surface);
}

// 

void DLSurface_init (DLSurface* surface, DLtype type, DLuint usize, DLuint ustride, DLuint width, DLuint height)
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

// 

DLSurface* DLSurface_clone (DLSurface* surface)
{
	DLSurface* surface_n = calloc(sizeof(DLSurface), 1);
	*surface_n = *surface;
	return surface_n;
}

void DLSurface_copy (DLSurface* surface_dest, DLSurface* surface_source)
{
	*surface_dest = *surface_source;
}

// 

void DLSurface_fill (DLSurface* surface, DLvoid_p source)
{
	DLuint loop_loc = -1;

	while (++loop_loc < surface->size)
	{
		// ptr_source: base + (index % stride) * unit_size
		DLvoid_p ptr_dest = DLSurface_getPixelPI(surface, loop_loc, 0);
		DLvoid_p ptr_source = (DLchar_p)(source) + ( (loop_loc % surface->ustride) * surface->usize);

		memcpy(ptr_dest, ptr_source, surface->usize);
	}
}

// 

void DLSurface_getData (DLSurface* surface, DLvoid_p dest)
{
	memcpy(dest, surface->data, surface->size);
}

void DLSurface_loadData (DLSurface* surface, DLvoid_p source)
{
	memcpy(surface->data, source, surface->size);
}

// 

DLvoid_p DLSurface_getPixelPI (DLSurface* surface, DLuint index, DLuint offset)
{
	return (DLchar_p)(surface->data) + ((index + offset) * surface->ustride * surface->usize);
}

DLvoid_p DLSurface_getPixelP (DLSurface* surface, DLuint x, DLuint y, DLuint offset)
{
	return (DLchar_p)(surface->data) + ((y * surface->width + x + offset) * surface->ustride * surface->usize);
}

void DLSurface_getPixelI (DLSurface* surface, DLvoid_p dest, DLuint index, DLuint offset)
{
	memcpy(dest, DLSurface_getPixelPI(surface, index, offset), surface->usize);
}

void DLSurface_getPixel (DLSurface* surface, DLvoid_p dest, DLuint x, DLuint y, DLuint offset)
{
	memcpy(dest, DLSurface_getPixelP(surface, x, y, offset), surface->usize);
}

void DLSurface_setPixelI (DLSurface* surface, DLvoid_p source, DLuint index, DLuint offset)
{
	memcpy(DLSurface_getPixelPI(surface, index, offset), source, surface->usize);
}

void DLSurface_setPixel (DLSurface* surface, DLvoid_p source, DLuint x, DLuint y, DLuint offset)
{
	memcpy(DLSurface_getPixelP(surface, x, y, offset), source, surface->usize);
}

/* ////////////////
 * DLShader
 * ////////////////
 */

DLShader* DLShader_create ()
{
	DLShader* shader = calloc(sizeof(DLShader), 1);
	return shader;
}

void DLShader_delete (DLShader* shader)
{
	DLAttrMap_free(&shader->attrmap);
	DLCode_free(&shader->code);
	free(shader);
}

// 

void DLShader_init (DLShader* shader, DLuint attrmap_capacity)
{
	shader->attrmap.attrs = calloc(attrmap_capacity, sizeof(DLAttrib));
	shader->attrmap.attrs_id = calloc(attrmap_capacity, sizeof(DLchar_p));
	shader->attrmap.attrs_values = calloc(attrmap_capacity, sizeof(DLvoid_p));
	shader->attrmap.capacity = attrmap_capacity;

	shader->code.data = NULL;
	shader->code.size = 0;
	shader->code.csize = 0;

	shader->attr_loc_coord = 0;
	shader->attr_loc_color = 0;
}

// 

void DLShader_apply (DLShader* shader, DLSurface* surface)
{
	if (DL_DLSLRunner.stack != NULL)
	{
		DLSLRunner_free(&DL_DLSLRunner);
	}

	DLSLRunner_initStack(&DL_DLSLRunner, 64);
	DLSLRunner_bindCode(&DL_DLSLRunner, &shader->code);
	DLSLRunner_bindAttrMap(&DL_DLSLRunner, &shader->attrmap);
	
	DLAttrMap* shader_attrmap = &shader->attrmap;

	DLuint surface_data_loc = -1;

	while (++surface_data_loc < surface->csize)
	{
		DLAttrMap_bindAttrValue(shader_attrmap, shader->attr_loc_coord, &surface_data_loc);
		DLAttrMap_bindAttrValue(shader_attrmap, shader->attr_loc_color, DLSurface_getPixelPI(surface, surface_data_loc, 0));

		DLSLRunner_run(&DL_DLSLRunner);
	}
}

/* ////////////////
 * DLPath
 * ////////////////
 */

DLPath* DLPath_create ()
{
	DLPath* path = calloc(sizeof(DLPath), 1);
	return path;
}

void DLPath_delete (DLPath* path)
{
	DLAttrMap_free(&path->attrmap);
	DLCode_free(&path->code);
	free(path);
}

// 

void DLPath_init (DLPath* path, DLuint attrmap_capacity)
{
	path->attrmap.attrs = calloc(attrmap_capacity, sizeof(DLAttrib));
	path->attrmap.attrs_id = calloc(attrmap_capacity, sizeof(DLchar_p));
	path->attrmap.attrs_values = calloc(attrmap_capacity, sizeof(DLvoid_p));
	path->attrmap.capacity = attrmap_capacity;

	path->code.data = NULL;
	path->code.size = 0;
	path->code.csize = 0;

	path->attr_loc_surface = 0;
}

// 

void DLPath_apply (DLPath* path, DLSurface* surface)
{
	// path->attrmap.attrs[path->attr_loc_buffer].ptr = buffer->data;
	DLAttrMap_bindAttrValue(&path->attrmap, path->attr_loc_surface, &surface);

	if (DL_DLSLRunner.stack != NULL)
	{
		DLSLRunner_free(&DL_DLSLRunner);
	}

	DLSLRunner_initStack(&DL_DLSLRunner, 64);
	DLSLRunner_bindCode(&DL_DLSLRunner, &path->code);
	DLSLRunner_bindAttrMap(&DL_DLSLRunner, &path->attrmap);

	DLSLRunner_run(&DL_DLSLRunner);
}

/* ////////////////
 * DLAttrib
 * ////////////////
 */

void DLAttrib_init (DLAttrib* attr)
{
	attr->type = DL_NONE;
	attr->size = 0;
}

void DLAttrib_free (DLAttrib* attr)
{
}

/* ////////////////
 * DLAttrMap
 * ////////////////
 */

void DLAttrMap_init (DLAttrMap* attrmap, DLuint capacity)
{
	attrmap->attrs = calloc(capacity, sizeof(DLAttrib));
	attrmap->attrs_id = calloc(capacity, sizeof(DLchar_p));
	attrmap->attrs_values = calloc(capacity, sizeof(DLvoid_p));
	attrmap->capacity = capacity;
}

void DLAttrMap_free (DLAttrMap* attrmap)
{
	DLuint loop_loc;

	loop_loc = -1;

	while (++loop_loc < attrmap->capacity)
	{
		DLchar_p id = attrmap->attrs_id[loop_loc];

		if (id == NULL)
		{
			continue;
		}

		free(id);
	}

	loop_loc = -1;

	while (++loop_loc < attrmap->capacity)
	{
		DLvoid_p value = attrmap->attrs_values[loop_loc];

		if (value == NULL)
		{
			continue;
		}

		free(value);
	}

	free(attrmap->attrs);
	free(attrmap->attrs_id);
	free(attrmap->attrs_values);
}

// 

void DLAttrMap_bindAttrLocation (DLAttrMap* attrmap, DLuint location, DLchar_p id)
{
	DLuint id_len = strlen(id);
	attrmap->attrs_id[location] = malloc(id_len);
	memcpy(attrmap->attrs_id[location], id, id_len);
}

DLuint DLAttrMap_getAttrLocation (DLAttrMap* attrmap, DLchar_p id)
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

// 

void DLAttrMap_reallocAttrValue (DLAttrMap* attrmap, DLuint attr_loc, DLuint size)
{
	// TODO: Change to realloc if needed
	free(attrmap->attrs_values[attr_loc]);
	attrmap->attrs_values[attr_loc] = calloc(size, 1);
}

void DLAttrMap_bindAttrValue (DLAttrMap* attrmap, DLuint attr_loc, DLvoid_p source)
{
	DLvoid_p dest = attrmap->attrs_values[attr_loc];
	memcpy(dest, source, attrmap->attrs[attr_loc].size);
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

void DLCode_load (DLCode* code, DLdouble* data, DLuint size)
{
	DLuint csize = size / sizeof(DLdouble);

	code->data = malloc(size);
	code->size = size;
	code->csize = csize;

	memcpy(code->data, data, size);
}