#include <DL_defines.h>

#ifndef DL_CORE_H
#define DL_CORE_H

/* "Includes" to prevent header recursion
 */
struct DLSLRunner;
typedef struct DLSLRunner DLSLRunner;

/* Struct Declarations
 */
struct DLBuffer;
struct DLShader;
struct DLPath;
struct DLAttribute;
struct DLAttribMap;
struct DLCode;

/* Typedef Struct Declarations
 */
typedef struct DLBuffer DLBuffer;
typedef struct DLShader DLShader;
typedef struct DLPath DLPath;
typedef struct DLAttribute DLAttribute;
typedef struct DLAttribMap DLAttribMap;
typedef struct DLCode DLCode;

/* Struct Definitions
 */
struct DLAttribute
{
	DLvoid_p ptr;
	DLtype type;
	DLuint size;
};

struct DLAttribMap
{
	DLAttribute* attrs;
	DLchar_p* attrs_id;
	DLuint capacity;
};

struct DLCode
{
	DLdouble* data;
	DLuint size;
	DLuint csize;
};

struct DLBuffer
{
	DLvoid_p data;
	DLtype type;
	DLuint size;
	DLuint csize;
	DLuint usize;
};

struct DLShader
{
	DLAttribMap attrmap;
	DLCode code;

	DLuint attr_loc_index;
	DLuint attr_loc_value;
};

struct DLPath
{
	DLAttribMap attrmap;
	DLCode code;

	DLuint attr_loc_buffer;
};

/* DLBuffer
 */

void DLBuffer_init (DLBuffer* buffer, DLtype type, DLuint csize, DLuint usize);
void DLBuffer_free (DLBuffer* buffer);

void DLBuffer_clear (DLBuffer* buffer);
void DLBuffer_fill (DLBuffer* buffer, DLvoid_p source);

void DLBuffer_clone (DLBuffer* buffer_dest, DLBuffer* buffer_source);
void DLBuffer_copy (DLBuffer* buffer_dest, DLBuffer* buffer_source);

void DLBuffer_setData (DLBuffer* buffer, DLvoid_p source, DLuint size);
void DLBuffer_getData (DLBuffer* buffer, DLvoid_p dest);

void     DLBuffer_setDataUnit (DLBuffer* buffer, DLvoid_p source, DLuint location);
DLvoid_p DLBuffer_getDataUnitP (DLBuffer* buffer, DLuint location);
void     DLBuffer_getDataUnit (DLBuffer* buffer, DLvoid_p dest, DLuint location);

/* DLShader
 */

void DLShader_init (DLShader* shader);
void DLShader_free (DLShader* shader);

void DLShader_apply (DLShader* shader, DLBuffer* buffer, DLSLRunner* runner);

/* DLPath
 */

void DLPath_init (DLPath* path);
void DLPath_free (DLPath* path);

void DLPath_apply (DLPath* path, DLBuffer* buffer, DLSLRunner* runner);

/* DLAttribute
 */

void DLAttribute_init (DLAttribute* attr);
void DLAttribute_free (DLAttribute* attr);

void DLAttribute_setValue (DLAttribute* attr, DLvoid_p source);
void DLAttribute_getValue (DLAttribute* attr, DLvoid_p dest);

/* DLAttribMap
 */

void DLAttribMap_init (DLAttribMap* attrmap, DLuint capacity);
void DLAttribMap_free (DLAttribMap* attrmap);

void DLAttribMap_bindAttribID (DLAttribMap* attrmap, DLuint location, DLchar_p id);
DLuint DLAttribMap_getAttribLocation (DLAttribMap* attrmap, DLchar_p id);

/* DLCode
 */

void DLCode_init (DLCode* code);
void DLCode_free (DLCode* code);

void DLCode_load (DLCode* code, DLdouble* data, DLuint csize);

#endif