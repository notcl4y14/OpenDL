#include <DL_public.h>
#include <DL_core.h>
#include <DL_system.h>

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
 * DLBuffer
 * ////////////////
 */

DLuint dlCreateBuffer (DLtype type, DLuint size)
{
	DLBuffer buffer;
	DLBuffer_init(&buffer, type, size, DL_type_sizes[type]);
	DLuint location = DL_add_buffer(buffer);
	return location;
}

void dlFreeBuffer (DLuint buffer)
{
	DL_buffers_count--;
	DL_buffers_available[buffer] = DL_TRUE;

	DLBuffer_free(&DL_buffers[buffer]);
}

// 

void dlClearBuffer (DLuint buffer)
{
	DLBuffer_clear(&DL_buffers[buffer]);
}

void dlFillBuffer (DLuint buffer, DLvoid_p source)
{
	DLBuffer_fill(&DL_buffers[buffer], source);
}

// 

DLuint dlBufferClone (DLuint buffer)
{
	DLBuffer* buffer_source = &DL_buffers[buffer];
	DLBuffer buffer_dest;
	DLBuffer_clone(&buffer_dest, buffer_source);
	DLuint location = DL_add_buffer(buffer_dest);
	return location;
}

void dlBufferCopy (DLuint buffer_dest, DLuint buffer_source)
{
	DLBuffer* _buffer_dest = &DL_buffers[buffer_dest];

	// When copying a buffer, we need to free previous data
	DLBuffer_free(_buffer_dest);
	DLBuffer_copy(_buffer_dest, &DL_buffers[buffer_source]);
}

// 

void dlBufferData (DLuint buffer, DLvoid_p source, DLuint size)
{
	DLBuffer_setData(&DL_buffers[buffer], source, size);
}

void dlBufferGetData (DLuint buffer, DLvoid_p dest)
{
	DLBuffer_getData(&DL_buffers[buffer], dest);
}

/* ////////////////
 * DLShader
 * ////////////////
 */

DLuint dlCreateShader ()
{
	DLShader shader;
	DLShader_init(&shader);
	DLuint location = DL_add_shader(shader);
	return location;
}

void dlFreeShader (DLuint shader)
{
	DL_shaders_count--;
	DL_shaders_available[shader] = DL_TRUE;

	DLShader_free(&DL_shaders[shader]);
}

// 

void dlShaderBindAttrib (DLuint shader, DLuint location, DLvoid_p ptr, DLtype type, DLuint size)
{
	DLAttribute* attr = &DL_shaders[shader].attrmap.attrs[location];
	attr->ptr = ptr;
	attr->type = type;
	attr->size = size;
}

void dlShaderBindAttribPtr (DLuint shader, DLuint location, DLvoid_p ptr);
void dlShaderBindAttribType (DLuint shader, DLuint location, DLtype type);
void dlShaderBindAttribSize (DLuint shader, DLuint location, DLuint size);

// 

void dlShaderBindAttrLocation (DLuint shader, DLuint location, DLchar_p id)
{
	DLAttribMap_bindAttribID(&DL_shaders[shader].attrmap, location, id);
}

DLuint dlShaderGetAttrLocation (DLuint shader, DLchar_p id)
{
	DLuint location = DLAttribMap_getAttribLocation(&DL_shaders[shader].attrmap, id);
	return location;
}

// 

void dlShaderApply (DLuint shader, DLuint buffer)
{
	DLShader_apply(&DL_shaders[shader], &DL_buffers[buffer], &DL_DLSLRunner);
}