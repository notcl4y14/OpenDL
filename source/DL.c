#include <stdlib.h>
#include <string.h>

#include <DL.h>
#include <DLSL.h>

// 
// 

struct DLBuffer* DLarray_buffers;
struct DLShader* DLarray_shaders;
struct DLPath* DLarray_paths;

DLbool* DLarray_buffers_unavailable;
DLbool* DLarray_shaders_unavailable;
DLbool* DLarray_paths_unavailable;

DLuint DLarray_buffers_capacity;
DLuint DLarray_shaders_capacity;
DLuint DLarray_paths_capacity;

DLuint DLarray_buffers_count;
DLuint DLarray_shaders_count;
DLuint DLarray_paths_count;

DLuint* DLarray_types;
DLerror DL_error;

struct DLSLVM DL_vm;

// 
// 

DLuint DL_getTypeSize (DLtype type)
{
	switch (type)
	{
		case DL_BYTE:
		case DL_UBYTE:
			return 1;

		case DL_SHORT:
		case DL_USHORT:
			return 2;

		case DL_INT:
		case DL_UINT:
			return 4;

		case DL_FLOAT:
			return 4;

		case DL_DOUBLE:
			return 8;

		default:
			return 0;
	}
}

DLuint DL_arrayBufferAdd (struct DLBuffer buffer)
{
	DLuint location = -1;

	while (++location < DLarray_buffers_capacity)
	{
		if (DLarray_buffers_unavailable[location] == DL_FALSE)
		{
			DLarray_buffers[location] = buffer;
			DLarray_buffers_count++;
			return location;
		}
	}

	// Reallocate
	DLarray_buffers_capacity *= 2;
	DLarray_buffers = realloc(DLarray_buffers, DLarray_buffers_capacity);

	DLarray_buffers[location] = buffer;
	DLarray_buffers_unavailable[location] = DL_TRUE;
	DLarray_buffers_count++;

	return location;
}

DLuint DL_arrayShaderAdd (struct DLShader shader)
{
	DLuint location = -1;

	while (++location < DLarray_shaders_capacity)
	{
		if (DLarray_shaders_unavailable[location] == DL_FALSE)
		{
			DLarray_shaders[location] = shader;
			DLarray_shaders_count++;
			return location;
		}
	}

	// Reallocate
	DLarray_shaders_capacity *= 2;
	DLarray_shaders = realloc(DLarray_shaders, DLarray_shaders_capacity);

	DLarray_shaders[location] = shader;
	DLarray_shaders_unavailable[location] = DL_TRUE;
	DLarray_shaders_count++;

	return location;
}

DLuint DL_arrayPathAdd (struct DLPath path)
{
	DLuint location = -1;

	while (++location < DLarray_paths_capacity)
	{
		if (DLarray_paths_unavailable[location] == DL_FALSE)
		{
			DLarray_paths_count++;
			DLarray_paths[location] = path;
			return location;
		}
	}

	// Reallocate
	DLarray_paths_capacity *= 2;
	DLarray_paths = realloc(DLarray_paths, DLarray_paths_capacity);

	DLarray_paths[location] = path;
	DLarray_paths_unavailable[location] = DL_TRUE;
	DLarray_paths_count++;

	return location;
}

// 

struct DLBuffer* DL_arrayBufferGet (DLuint location)
{
	return &DLarray_buffers[location];
}

struct DLShader* DL_arrayShaderGet (DLuint location)
{
	return &DLarray_shaders[location];
}

struct DLPath* DL_arrayPathGet (DLuint location)
{
	return &DLarray_paths[location];
}

// 
// 

struct DLBuffer DL_createBuffer (DLtype type, DLuint size)
{
	struct DLBuffer buffer;

	buffer.data = calloc(size, DLarray_types[type]);
	buffer.type = type;
	buffer.size = size;

	return buffer;
}

void DL_freeBuffer (struct DLBuffer* buffer)
{
	free(buffer->data);
}

// 

void DL_bufferGetValue (struct DLBuffer* buffer, DLuint location, void* to)
{
	// TODO: optimize this
	DLuint type_size = DLarray_types[buffer->type];
	memcpy(to, (char*)(buffer->data) + (location * type_size), type_size);
}

void DL_bufferGetData (struct DLBuffer* buffer, void* to)
{
	memcpy(to, buffer->data, buffer->size * DLarray_types[buffer->type]);
}

void DL_bufferLoadData (struct DLBuffer* buffer, void* data)
{
	// TODO: optimize this
	DLuint type_size = DLarray_types[buffer->type];
	memset(buffer->data, 0, buffer->size * type_size);
	memcpy(buffer->data, data, buffer->size * type_size);
}

// 
// 

struct DLAttrs DL_createAttrs (DLuint capacity)
{
	struct DLAttrs attrs;

	attrs.v_values = calloc(capacity, sizeof(DLvoid_p));
	attrs.v_keys = calloc(capacity, sizeof(DLchar_p));
	attrs.v_sizes = calloc(capacity, sizeof(DLuint));
	attrs.v_types = calloc(capacity, sizeof(DLtype));
	attrs.capacity = capacity;

	return attrs;
}

void DL_freeAttrs (struct DLAttrs* attrs)
{
	DLuint loop_index = -1;

	while (++loop_index < attrs->capacity)
	{
		char* key = attrs->v_keys[loop_index];

		if (key == NULL)
		{
			continue;
		}

		free(attrs->v_keys[loop_index]);
	}

	free(attrs->v_values);
	free(attrs->v_keys);
	free(attrs->v_sizes);
	free(attrs->v_types);
}

// 

DLuint DL_getAttribLocation (struct DLAttrs* attrs, char* key)
{
	DLuint loop_index = -1;

	while (++loop_index < attrs->capacity)
	{
		if (strcmp(attrs->v_keys[loop_index], key) == 0)
		{
			return loop_index;
		}
	}

	return -1;
}

void DL_bindAttribLocation (struct DLAttrs* attrs, DLuint location, char* key)
{
	DLuint key_len = strlen(key);
	attrs->v_keys[location] = malloc(key_len);
	strcpy(attrs->v_keys[location], key);
}

void DL_bindAttribPointer (struct DLAttrs* attrs, DLuint location, void* pointer)
{
	attrs->v_values[location] = pointer;
}

void DL_bindAttribSize (struct DLAttrs* attrs, DLuint location, DLuint size)
{
	attrs->v_sizes[location] = size;
}

void DL_bindAttribType (struct DLAttrs* attrs, DLuint location, DLtype type)
{
	attrs->v_types[location] = type;
}

void DL_attrsLoadBuffer (struct DLAttrs* attrs, struct DLBuffer* buffer)
{
	DLuint location = -1;

	while (++location < attrs->capacity)
	{
		attrs->v_values[location] = (char*)(buffer->data) + (location * DLarray_types[buffer->type]);
		attrs->v_sizes[location] = DLarray_types[buffer->type];
	}
}

void DL_attrsLoadArray (struct DLAttrs* attrs, void* array, DLuint array_usize)
{
	DLuint location = -1;

	while (++location < attrs->capacity)
	{
		attrs->v_values[location] = (char*)(array) + (location * array_usize);
		attrs->v_sizes[location] = array_usize;
	}
}

// 

void DL_getAttribValue (struct DLAttrs* attrs, DLuint location, void* to)
{
	memcpy(to, attrs->v_values[location], attrs->v_sizes[location]);
}

// 
// 

struct DLCode DL_createCode ()
{
	struct DLCode code;

	code.data = NULL;
	code.size = 0;

	return code;
}

void DL_freeCode (struct DLCode* code)
{
	free(code->data);
}

// 

void DL_codeLoadData (struct DLCode* code, double* data, DLuint data_size)
{
	DLuint copy_size = data_size * sizeof(double);

	code->data = malloc(copy_size);
	memcpy(code->data, data, copy_size);

	code->size = data_size;
}

// 
// 

struct DLShader DL_createShader ()
{
	struct DLShader shader;

	shader.attrs.v_values = NULL;
	shader.attrs.v_keys = NULL;
	shader.attrs.v_sizes = NULL;
	shader.attrs.v_types = NULL;
	shader.attrs.capacity = 0;

	shader.code.data = NULL;
	shader.code.size = 0;

	return shader;
}

void DL_freeShader (struct DLShader* shader)
{
	DL_freeAttrs(&shader->attrs);
	DL_freeCode(&shader->code);
}

// 

void DL_shaderBindAttrib_value (struct DLShader* shader, DLuint location)
{
	shader->value_attr_loc = location;
}

void DL_shaderBindAttrib_index (struct DLShader* shader, DLuint location)
{
	shader->index_attr_loc = location;
	shader->attrs.v_types[location] = DL_UINT;
}

// 
// 

struct DLPath DL_createPath ()
{
	struct DLPath path;

	path.attrs.v_values = NULL;
	path.attrs.v_keys = NULL;
	path.attrs.v_sizes = NULL;
	path.attrs.v_types = NULL;
	path.attrs.capacity = 0;

	path.code.data = NULL;
	path.code.size = 0;

	return path;
}

void DL_freePath (struct DLPath* path)
{
	DL_freeAttrs(&path->attrs);
	DL_freeCode(&path->code);
}

// 

void DL_pathBindAttrib_buffer (struct DLPath* path, DLuint location)
{
	if (location > path->attrs.capacity)
	{
		DL_error = DL_E_LOC_OOB;
		return;
	}

	path->buffer_attr_loc = location;
}

// 
// 

// 
// 

void dlInit ()
{
	DLarray_buffers_capacity = 16;
	DLarray_shaders_capacity = 16;
	DLarray_paths_capacity = 16;

	DLarray_buffers_count = 0;
	DLarray_shaders_count = 0;
	DLarray_paths_count = 0;

	DLarray_buffers = calloc(DLarray_buffers_capacity, sizeof(struct DLBuffer));
	DLarray_shaders = calloc(DLarray_shaders_capacity, sizeof(struct DLShader));
	DLarray_paths = calloc(DLarray_paths_capacity, sizeof(struct DLPath));

	DLarray_buffers_unavailable = calloc(DLarray_buffers_capacity, sizeof(DLbool));
	DLarray_shaders_unavailable = calloc(DLarray_shaders_capacity, sizeof(DLbool));
	DLarray_paths_unavailable = calloc(DLarray_paths_capacity, sizeof(DLbool));

	DLarray_types = malloc(DL_TYPE_COUNT * sizeof(DLubyte));

	// Manually adding sizes of each type so that the use of
	// DL_getTypeSize can be avoided
	DLarray_types[DL_BYTE] = 1;
	DLarray_types[DL_UBYTE] = 1;
	DLarray_types[DL_SHORT] = 2;
	DLarray_types[DL_USHORT] = 2;
	DLarray_types[DL_INT] = 4;
	DLarray_types[DL_UINT] = 4;
	DLarray_types[DL_FLOAT] = 4;
	DLarray_types[DL_DOUBLE] = 8;

	DL_vm = DLSL_createVM(64);
}

void dlTerminate ()
{
	DLuint location;

	location = -1;

	while (++location < DLarray_buffers_capacity)
	{
		if (DLarray_buffers_unavailable[location] == DL_TRUE)
		{
			DL_freeBuffer(DL_arrayBufferGet(location));
		}
	}

	location = -1;

	while (++location < DLarray_shaders_capacity)
	{
		if (DLarray_shaders_unavailable[location] == DL_TRUE)
		{
			DL_freeShader(DL_arrayShaderGet(location));
		}
	}

	location = -1;

	while (++location < DLarray_paths_capacity)
	{
		if (DLarray_paths_unavailable[location] == DL_TRUE)
		{
			DL_freePath(DL_arrayPathGet(location));
		}
	}

	free(DLarray_buffers);
	free(DLarray_shaders);
	free(DLarray_paths);

	free(DLarray_buffers_unavailable);
	free(DLarray_shaders_unavailable);
	free(DLarray_paths_unavailable);

	free(DLarray_types);

	DLSL_freeVM(&DL_vm);
}

// 
// 

DLuint dlCreateBuffer (DLuint size, DLuint usize)
{
	struct DLBuffer buffer = DL_createBuffer(size, usize);
	return DL_arrayBufferAdd(buffer);
}

void dlFreeBuffer (DLuint buffer)
{
	DL_freeBuffer(DL_arrayBufferGet(buffer));
	DLarray_buffers_unavailable[buffer] = DL_FALSE;
}

// 

void dlBufferGetData (DLuint buffer, void* to)
{
	DL_bufferGetData(DL_arrayBufferGet(buffer), to);
}

void dlBufferLoadData (DLuint buffer, void* data)
{
	DL_bufferLoadData(DL_arrayBufferGet(buffer), data);
}

// 
// 

DLuint dlCreateShader ()
{
	struct DLShader shader = DL_createShader();
	return DL_arrayShaderAdd(shader);
}

void dlFreeShader (DLuint shader)
{
	DL_freeShader(DL_arrayShaderGet(shader));
	DLarray_shaders_unavailable[shader] = DL_FALSE;
}

// 

DLuint dlShaderGetAttribLocation (DLuint shader, char* key)
{
	return DL_getAttribLocation(&DL_arrayShaderGet(shader)->attrs, key);
}

void dlShaderBindAttribLocation (DLuint shader, DLuint location, char* key)
{
	DL_bindAttribLocation(&DL_arrayShaderGet(shader)->attrs, location, key);
}

void dlShaderBindAttribPointer (DLuint shader, DLuint location, void* pointer)
{
	DL_bindAttribPointer(&DL_arrayShaderGet(shader)->attrs, location, pointer);
}

void dlShaderBindAttribType (DLuint shader, DLuint location, DLtype type)
{
	DL_bindAttribType(&DL_arrayShaderGet(shader)->attrs, location, type);
}

void dlShaderAttrsLoadBuffer (DLuint shader, DLuint buffer)
{
	DL_attrsLoadBuffer(&DL_arrayShaderGet(shader)->attrs, DL_arrayBufferGet(buffer));
}

void dlShaderAttrsLoadArray (DLuint shader, void* array, DLuint array_usize)
{
	DL_attrsLoadArray(&DL_arrayShaderGet(shader)->attrs, array, array_usize);
}

// 

void dlShaderLoadCode (DLuint shader, double* code, DLuint code_size)
{
	DL_codeLoadData(&DL_arrayShaderGet(shader)->code, code, code_size);
}

// 

void dlApplyShader (DLuint shader, DLuint buffer)
{
	struct DLShader* _shader = DL_arrayShaderGet(shader);
	struct DLBuffer* _buffer = DL_arrayBufferGet(buffer);

	// Initializing VM
	DL_vm.attrs = &_shader->attrs;

	// Free previous loaded VM code
	if (DL_vm.code != NULL)
	{
		free(DL_vm.code);
	}

	DLSL_vmLoadCode(&DL_vm, _shader->code.data, _shader->code.size);

	// Initializing variables that are "constant" in a function
	DLuint buf_unit_size = DLarray_types[_buffer->type];

	_shader->attrs.v_types[_shader->value_attr_loc] = _buffer->type;

	DLuint buf_index = -1;

	while (++buf_index < _buffer->size)
	{
		DLvoid_p value = (DLchar_p)(_buffer->data) + (buf_index * buf_unit_size);

		// Updating Attributes
		_shader->attrs.v_values[_shader->value_attr_loc] = value;
		_shader->attrs.v_values[_shader->index_attr_loc] = &buf_index;;

		DLSL_vmRun(&DL_vm);
	}
}

// 
// 

DLuint dlCreatePath ()
{
	struct DLPath path = DL_createPath();
	return DL_arrayPathAdd(path);
}

void dlFreePath (DLuint path)
{
	DL_freePath(DL_arrayPathGet(path));
	DLarray_paths_unavailable[path] = DL_FALSE;
}

// 

DLuint dlPathGetAttribLocation (DLuint path, char* key)
{
	return DL_getAttribLocation(&DL_arrayPathGet(path)->attrs, key);
}

void dlPathBindAttribLocation (DLuint path, DLuint location, char* key)
{
	DL_bindAttribLocation(&DL_arrayPathGet(path)->attrs, location, key);
}

void dlPathBindAttribPointer (DLuint path, DLuint location, void* pointer)
{
	DL_bindAttribPointer(&DL_arrayPathGet(path)->attrs, location, pointer);
}

void dlPathBindAttribType (DLuint path, DLuint location, DLtype type)
{
	DL_bindAttribType(&DL_arrayPathGet(path)->attrs, location, type);
}

void dlPathAttrsLoadBuffer (DLuint path, DLuint buffer)
{
	DL_attrsLoadBuffer(&DL_arrayPathGet(path)->attrs, DL_arrayBufferGet(buffer));
}

void dlPathAttrsLoadArray (DLuint path, void* array, DLuint array_usize)
{
	DL_attrsLoadArray(&DL_arrayPathGet(path)->attrs, array, array_usize);
}

// 

void dlPathLoadCode (DLuint path, double* code, DLuint code_size)
{
	DL_codeLoadData(&DL_arrayPathGet(path)->code, code, code_size);
}

// 

void dlApplyPath (DLuint path, DLuint buffer)
{
	struct DLPath* _path = DL_arrayPathGet(path);
	struct DLBuffer* _buffer = DL_arrayBufferGet(buffer);

	// Initializing Attributes
	_path->attrs.v_values[_path->buffer_attr_loc] = _buffer;

	// Initializing VM
	DL_vm.attrs = &_path->attrs;

	// Free previous loaded VM code
	if (DL_vm.code != NULL)
	{
		free(DL_vm.code);
	}

	DLSL_vmLoadCode(&DL_vm, _path->code.data, _path->code.size);

	// Running VM
	DLSL_vmRun(&DL_vm);
}