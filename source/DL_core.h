#include <DL_defines.h>

#ifndef DL_CORE_H
#define DL_CORE_H

struct DLBuffer;
struct DLShader;
struct DLPath;
struct DLAttribute;
struct DLAttribMap;

typedef struct DLBuffer DLBuffer;
typedef struct DLShader DLShader;
typedef struct DLPath DLPath;
typedef struct DLAttribute DLAttribute;
typedef struct DLAttribMap DLAttribMap;

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
};

struct DLPath
{
	DLAttribMap attrmap;
};

/* DLBuffer
 */

// void DLBuffer_init (DLBuffer* buffer, DLtype type, DLuint size);
void DLBuffer_init (DLBuffer* buffer, DLtype type, DLuint csize, DLuint usize);
void DLBuffer_free (DLBuffer* buffer);

void DLBuffer_clear (DLBuffer* buffer);
void DLBuffer_fill (DLBuffer* buffer, DLvoid_p source);

void DLBuffer_setData (DLBuffer* buffer, DLvoid_p source, DLuint size);
void DLBuffer_getData (DLBuffer* buffer, DLvoid_p dest);

void     DLBuffer_setDataUnit (DLBuffer* buffer, DLvoid_p source, DLuint location);
DLvoid_p DLBuffer_getDataUnitP (DLBuffer* buffer, DLuint location);
void     DLBuffer_getDataUnit (DLBuffer* buffer, DLvoid_p dest, DLuint location);

/* DLShader
 */

void DLShader_init (DLShader* shader);
void DLShader_free (DLShader* shader);

void DLShader_apply (DLShader* shader, DLBuffer* buffer);

/* DLPath
 */

void DLPath_init (DLPath* path);
void DLPath_free (DLPath* path);

void DLPath_apply (DLPath* path, DLBuffer* buffer);

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

#endif