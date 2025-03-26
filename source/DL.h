#ifndef DL_h
#define DL_h

/* Type defines for DL.
 */
// DLbool
#define DL_TRUE  1
#define DL_FALSE 0

// DLobject
#define DL_BUFFER 0x0
#define DL_SHADER 0x1
#define DL_PATH   0x2

// DLtype
#define DL_TYPE_COUNT 8
#define DL_NONE    0x00
#define DL_BYTE    0x01
#define DL_UBYTE   0x02
#define DL_SHORT   0x03
#define DL_USHORT  0x04
#define DL_INT     0x05
#define DL_UINT    0x06
#define DL_FLOAT   0x07
#define DL_DOUBLE  0x08

typedef char            DLchar;
typedef char*           DLchar_p;

typedef void*           DLvoid_p;

typedef char            DLbyte;
typedef unsigned char   DLubyte;
typedef int             DLint;
typedef unsigned int    DLuint;
typedef short           DLshort;
typedef unsigned short  DLushort;
typedef float           DLfloat;
typedef double          DLdouble;

typedef unsigned char DLbool;
typedef unsigned char DLobject;
typedef unsigned char DLtype;

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

extern DLbool* DLarray_buffers_unavailable;
extern DLbool* DLarray_shaders_unavailable;
extern DLbool* DLarray_paths_unavailable;

extern DLuint DLarray_buffers_capacity;
extern DLuint DLarray_shaders_capacity;
extern DLuint DLarray_paths_capacity;

extern DLuint DLarray_buffers_count;
extern DLuint DLarray_shaders_count;
extern DLuint DLarray_paths_count;

extern DLuint* DLarray_types;

extern struct DLSLVM DL_vm;

/* DL Objects - Definitions.
 */
struct DLBuffer
{
	DLvoid_p data;
	DLtype type;
	DLuint size;
};

struct DLAttrs
{
	DLvoid_p* v_values;
	DLchar_p* v_keys;
	DLtype*   v_types;
	DLuint*   v_sizes;
	DLuint capacity;
};

struct DLCode
{
	double* data;
	DLuint size;
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
DLuint DL_getTypeSize (DLtype type);

DLuint DL_arrayBufferAdd (struct DLBuffer buffer);
DLuint DL_arrayShaderAdd (struct DLShader shader);
DLuint DL_arrayPathAdd (struct DLPath path);

struct DLBuffer* DL_arrayBufferGet (DLuint buffer);
struct DLShader* DL_arrayShaderGet (DLuint shader);
struct DLPath* DL_arrayPathGet (DLuint path);

// DLBuffer
struct DLBuffer DL_createBuffer (DLtype type, DLuint size);
void DL_freeBuffer (struct DLBuffer* buffer);

void DL_bufferGetValue (struct DLBuffer* buffer, DLuint location, void* to);
void DL_bufferGetData (struct DLBuffer* buffer, void* to);
void DL_bufferLoadData (struct DLBuffer* buffer, void* data);

// DLAttrs
struct DLAttrs DL_createAttrs (DLuint capacity);
void DL_freeAttrs (struct DLAttrs* attrs);

DLuint DL_getAttribLocation (struct DLAttrs* attrs, char* key);
void DL_bindAttribLocation (struct DLAttrs* attrs, DLuint location, char* key);
void DL_bindAttribPointer (struct DLAttrs* attrs, DLuint location, void* pointer);
void DL_bindAttribType (struct DLAttrs* attrs, DLuint location, DLtype type);
void DL_bindAttribSize (struct DLAttrs* attrs, DLuint location, DLuint size);
void DL_bindAttrib (struct DLAttrs* attrs, DLuint location, void* pointer, DLtype type, DLuint size);
void DL_attrsLoadBuffer (struct DLAttrs* attrs, struct DLBuffer* buffer);
void DL_attrsLoadArray (struct DLAttrs* attrs, void* array, DLuint array_usize);

void DL_getAttribValue (struct DLAttrs* attrs, DLuint location, void* to);

// DLCode
struct DLCode DL_createCode ();
void DL_freeCode (struct DLCode* code);

void DL_codeLoadData (struct DLCode* code, double* data, DLuint data_size);

// DLShader
struct DLShader DL_createShader ();
void DL_freeShader (struct DLShader* shader);

// void DL_initShader (struct DLShader* shader, DLuint attrs_capacity);

// DLPath
struct DLPath DL_createPath ();
void DL_freePath (struct DLPath* path);

// void DL_initPath (struct DLPath* path, DLuint attrs_capacity);

/* DL public methods.
 */

// DL
void dlInit ();
void dlTerminate ();

// DLBuffer
DLuint dlCreateBuffer (DLuint size, DLuint usize);
void dlFreeBuffer (DLuint buffer);

void dlBufferGetData (DLuint buffer, void* to);
void dlBufferLoadData (DLuint buffer, void* data);

// DLShader
DLuint dlCreateShader ();
void dlFreeShader (DLuint shader);

DLuint dlShaderGetAttribLocation (DLuint shader, char* key);
void dlShaderBindAttribLocation (DLuint shader, DLuint location, char* key);
void dlShaderBindAttribPointer (DLuint shader, DLuint location, void* pointer);
void dlShaderBindAttribType (DLuint shader, DLuint location, DLtype type);
void dlShaderBindAttrib (DLuint shader, DLuint location, void* pointer, DLtype type, DLuint size);
void dlShaderAttrsLoadBuffer (DLuint shader, DLuint buffer);
void dlShaderAttrsLoadArray (DLuint shader, void* array, DLuint array_usize);

// Temporary methods
void dlShaderLoadCode (DLuint shader, double* code, DLuint code_size);

void dlApplyShader (DLuint shader, DLuint buffer);

// DLPath
DLuint dlCreatePath ();
void dlFreePath (DLuint path);

DLuint dlPathGetAttribLocation (DLuint path, char* key);
void dlPathBindAttribLocation (DLuint path, DLuint location, char* key);
void dlPathBindAttribPointer (DLuint path, DLuint location, void* pointer);
void dlPathBindAttribType (DLuint path, DLuint location, DLtype type);
void dlPathBindAttrib (DLuint path, DLuint location, void* pointer, DLtype type, DLuint size);
void dlPathAttrsLoadBuffer (DLuint path, DLuint buffer);
void dlPathAttrsLoadArray (DLuint path, void* array, DLuint array_usize);

// Temporary methods
void dlPathLoadCode (DLuint path, double* code, DLuint code_size);

void dlApplyPath (DLuint path, DLuint buffer);

#endif