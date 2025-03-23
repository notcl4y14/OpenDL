#ifndef DL_h
#define DL_h

/* Type defines for DL.
 */
#define DL_TRUE 1
#define DL_FALSE 0

typedef unsigned int size_dl;
typedef unsigned int loc_dl;

typedef unsigned char bool_dl;

/* DL Objects - Declarations.
 */
struct DLBuffer;
struct DLAttrs;
struct DLShader;
struct DLPath;

/* DLSL Object Declaration.
 * This is used to avoid header recursion.
 */
struct DLSLVM;

/* Global DL Object Arrays.
 */
// TODO: Add an indicator that tells whether the object is available or not
extern struct DLBuffer* DLarray_buffers;
extern struct DLShader* DLarray_shaders;
extern struct DLPath* DLarray_paths;

extern bool_dl* DLarray_buffers_unavailable;
extern bool_dl* DLarray_shaders_unavailable;
extern bool_dl* DLarray_paths_unavailable;

extern size_dl DLarray_buffers_capacity;
extern size_dl DLarray_shaders_capacity;
extern size_dl DLarray_paths_capacity;

extern size_dl DLarray_buffers_count;
extern size_dl DLarray_shaders_count;
extern size_dl DLarray_paths_count;

extern struct DLSLVM DL_vm;

/* DL Objects - Definitions.
 */
struct DLBuffer
{
	void*   data;
	size_dl size;
	size_dl usize;
};

struct DLAttrs
{
	void**   v_values;
	char**   v_keys;
	size_dl* v_sizes;
	size_dl capacity;
};

struct DLCode
{
	double* data;
	size_dl size;
};

struct DLShader
{
	struct DLAttrs attrs;
	struct DLCode code;
};

struct DLPath
{
	struct DLAttrs attrs;
	struct DLCode code;
};

/* DL "private" methods.
 */

// DL
loc_dl DL_arrayBufferAdd (struct DLBuffer buffer);
loc_dl DL_arrayShaderAdd (struct DLShader shader);
loc_dl DL_arrayPathAdd (struct DLPath path);

struct DLBuffer* DL_arrayBufferGet (loc_dl buffer);
struct DLShader* DL_arrayShaderGet (loc_dl shader);
struct DLPath* DL_arrayPathGet (loc_dl path);

// DLBuffer
struct DLBuffer DL_createBuffer (size_dl size, size_dl usize);
void DL_freeBuffer (struct DLBuffer* buffer);

void DL_bufferGetData (struct DLBuffer* buffer, void* to);
void DL_bufferLoadData (struct DLBuffer* buffer, void* data);

// DLAttrs
struct DLAttrs DL_createAttrs (size_dl capacity);
void DL_freeAttrs (struct DLAttrs* attrs);

loc_dl DL_getAttribLocation (struct DLAttrs* attrs, char* key);
void DL_bindAttribLocation (struct DLAttrs* attrs, loc_dl location, char* key);
void DL_bindAttribPointer (struct DLAttrs* attrs, loc_dl location, void* pointer);
void DL_bindAttribSize (struct DLAttrs* attrs, loc_dl location, size_dl size);
void DL_attrsLoadBuffer (struct DLAttrs* attrs, struct DLBuffer* buffer);
void DL_attrsLoadArray (struct DLAttrs* attrs, void* array, size_dl array_usize);

// DLCode
struct DLCode DL_createCode ();
void DL_freeCode (struct DLCode* code);

void DL_codeLoadData (struct DLCode* code, double* data, size_dl data_size);

// DLShader
struct DLShader DL_createShader ();
void DL_freeShader (struct DLShader* shader);

// void DL_initShader (struct DLShader* shader, size_dl attrs_capacity);

// DLPath
struct DLPath DL_createPath ();
void DL_freePath (struct DLPath* path);

// void DL_initPath (struct DLPath* path, size_dl attrs_capacity);

/* DL public methods.
 */

// DL
void dlInit ();
void dlTerminate ();

// DLBuffer
loc_dl dlCreateBuffer (size_dl size, size_dl usize);
void dlFreeBuffer (loc_dl buffer);

void dlBufferGetData (loc_dl buffer, void* to);
void dlBufferLoadData (loc_dl buffer, void* data);

// DLShader
loc_dl dlCreateShader ();
void dlFreeShader (loc_dl shader);

loc_dl dlShaderGetAttribLocation (loc_dl shader, char* key);
void dlShaderBindAttribLocation (loc_dl shader, loc_dl location, char* key);
void dlShaderBindAttribPointer (loc_dl shader, loc_dl location, void* pointer);
void dlShaderAttrsLoadBuffer (loc_dl shader, loc_dl buffer);
void dlShaderAttrsLoadArray (loc_dl shader, void* array, size_dl array_usize);

// Temporary methods
void dlShaderLoadCode (loc_dl shader, double* code, size_dl code_size);

void dlApplyShader (loc_dl shader, loc_dl buffer);

// DLPath
loc_dl dlCreatePath ();
void dlFreePath (loc_dl path);

loc_dl dlPathGetAttribLocation (loc_dl path, char* key);
void dlPathBindAttribLocation (loc_dl path, loc_dl location, char* key);
void dlPathBindAttribPointer (loc_dl path, loc_dl location, void* pointer);
void dlPathAttrsLoadBuffer (loc_dl path, loc_dl buffer);
void dlPathAttrsLoadArray (loc_dl path, void* array, size_dl array_usize);

// Temporary methods
void dlPathLoadCode (loc_dl path, double* code, size_dl code_size);

void dlApplyPath (loc_dl path, loc_dl buffer);

#endif