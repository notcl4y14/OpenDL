#include <DL/dlpublic.h>
#include <DL/dlcore.h>
#include <DL/dlsystem.h>

/* ////////////////
 * DL
 * ////////////////
 */

void dlInit ()
{
	DL_init();
}

void dlTerminate ()
{
	DL_free();
}

/* ////////////////
 * dlBuffer
 * ////////////////
 */

DLuint dlCreateBuffer (DLtype type, DLuint size)
{
	dlBuffer buffer;
	dlBuffer_init(&buffer, type, size, DL_type_sizes[type]);
	DLuint location = DL_add_buffer(buffer);
	return location;
}

void dlFreeBuffer (DLuint buffer)
{
	DL_buffers_count--;
	DL_buffers_available[buffer] = DL_TRUE;

	dlBuffer_free(&DL_buffers[buffer]);
}

// 

void dlClearBuffer (DLuint buffer)
{
	dlBuffer_clear(&DL_buffers[buffer]);
}

void dlFillBuffer (DLuint buffer, DLvoid_p source)
{
	dlBuffer_fill(&DL_buffers[buffer], source);
}

// 

DLuint dlBufferClone (DLuint buffer)
{
	dlBuffer* buffer_source = &DL_buffers[buffer];
	dlBuffer buffer_dest;
	dlBuffer_clone(&buffer_dest, buffer_source);
	DLuint location = DL_add_buffer(buffer_dest);
	return location;
}

void dlBufferCopy (DLuint buffer_dest, DLuint buffer_source)
{
	dlBuffer* _buffer_dest = &DL_buffers[buffer_dest];

	// When copying a buffer, we need to free previous data
	dlBuffer_free(_buffer_dest);
	dlBuffer_copy(_buffer_dest, &DL_buffers[buffer_source]);
}

// 

void dlBufferData (DLuint buffer, DLvoid_p source, DLuint size)
{
	dlBuffer_setData(&DL_buffers[buffer], source, size);
}

void dlBufferGetData (DLuint buffer, DLvoid_p dest)
{
	dlBuffer_getData(&DL_buffers[buffer], dest);
}

/* ////////////////
 * dlShader
 * ////////////////
 */

DLuint dlCreateShader ()
{
	dlShader shader;
	dlShader_init(&shader);
	DLuint location = DL_add_shader(shader);
	return location;
}

void dlFreeShader (DLuint shader)
{
	DL_shaders_count--;
	DL_shaders_available[shader] = DL_TRUE;

	dlShader_free(&DL_shaders[shader]);
}

// 

void dlShaderBindAttrib (DLuint shader, DLuint location, DLvoid_p ptr, DLtype type, DLuint size)
{
	dlAttrib* attr = &DL_shaders[shader].attrmap.attrs[location];
	attr->ptr = ptr;
	attr->type = type;
	attr->size = size;
}

void dlShaderBindAttribPtr (DLuint shader, DLuint location, DLvoid_p ptr);
void dlShaderBindAttribType (DLuint shader, DLuint location, DLtype type);
void dlShaderBindAttribSize (DLuint shader, DLuint location, DLuint size);

// 

void dlShaderLoadCode (DLuint shader, DLdouble* code, DLuint code_size)
{
	dlCode* _code = &DL_shaders[shader].code;
	dlCode_load(_code, code, code_size);
}

void dlShaderBindCoordAttr (DLuint shader, DLuint location)
{
	DL_shaders[shader].attr_loc_coord = location;
}

void dlShaderBindValueAttr (DLuint shader, DLuint location)
{
	DL_shaders[shader].attr_loc_value = location;
}

// 

void dlShaderBindAttrLocation (DLuint shader, DLuint location, DLchar_p id)
{
	dlAttrMap_bindAttribID(&DL_shaders[shader].attrmap, location, id);
}

DLuint dlShaderGetAttrLocation (DLuint shader, DLchar_p id)
{
	DLuint location = dlAttrMap_getAttribLocation(&DL_shaders[shader].attrmap, id);
	return location;
}

// 

void dlShaderApply (DLuint shader, DLuint buffer)
{
	dlShader_apply(&DL_shaders[shader], &DL_buffers[buffer], &DL_dlslRunner);
}