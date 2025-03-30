#include <DL/dldefines.h>

#ifndef DL_CORE_H
#define DL_CORE_H

/* "Includes" to prevent header recursion
 */
struct dlslRunner;
typedef struct dlslRunner dlslRunner;

/* Struct Declarations
 */
struct dlBuffer;
struct dlSurface;
struct dlShader;
struct dlPath;
struct dlAttrib;
struct dlAttrMap;
struct dlCode;

/* Typedef Struct Declarations
 */
typedef struct dlBuffer dlBuffer;
typedef struct dlSurface dlSurface;
typedef struct dlShader dlShader;
typedef struct dlPath dlPath;
typedef struct dlAttrib dlAttrib;
typedef struct dlAttrMap dlAttrMap;
typedef struct dlCode dlCode;

/* Struct Definitions
 */
struct dlAttrib
{
	DLvoid_p ptr;
	DLtype type;
	DLuint size;
};

struct dlAttrMap
{
	dlAttrib* attrs;
	DLchar_p* attrs_id;
	DLuint capacity;
};

struct dlCode
{
	DLdouble* data;
	DLuint size;
	DLuint csize;
};

struct dlBuffer
{
	DLvoid_p data;
	DLtype type;
	DLuint size;
	DLuint csize;
	DLuint usize;
};

struct dlSurface
{
	// Data
	DLvoid_p data;
	DLuint size;
	DLuint csize;

	// Unit
	DLtype utype;
	DLuint usize;
	DLuint ustride;

	// Surface
	DLuint width;
	DLuint height;
};

struct dlShader
{
	dlAttrMap attrmap;
	dlCode code;

	DLuint attr_loc_coord;
	DLuint attr_loc_value;
};

struct dlPath
{
	dlAttrMap attrmap;
	dlCode code;

	DLuint attr_loc_buffer;
};

/* dlBuffer
 */

void dlBuffer_init (dlBuffer* buffer, DLtype type, DLuint csize, DLuint usize);
void dlBuffer_free (dlBuffer* buffer);

void dlBuffer_clone (dlBuffer* buffer_dest, dlBuffer* buffer_source);
void dlBuffer_copy (dlBuffer* buffer_dest, dlBuffer* buffer_source);

void dlBuffer_clear (dlBuffer* buffer);
void dlBuffer_fill (dlBuffer* buffer, DLvoid_p source);

void dlBuffer_setData (dlBuffer* buffer, DLvoid_p source, DLuint size);
void dlBuffer_getData (dlBuffer* buffer, DLvoid_p dest);

DLvoid_p dlBuffer_getDataUnitP (dlBuffer* buffer, DLuint location);
void     dlBuffer_getDataUnit (dlBuffer* buffer, DLvoid_p dest, DLuint location);
void     dlBuffer_setDataUnit (dlBuffer* buffer, DLvoid_p source, DLuint location);

/* dlSurface
 */

void dlSurface_init (dlSurface* surface, DLtype type, DLuint usize, DLuint ustride, DLuint width, DLuint height);
void dlSurface_free (dlSurface* surface);

void dlSurface_clone (dlSurface* surface_dest, dlSurface* surface_source);
void dlSurface_copy (dlSurface* surface_dest, dlSurface* surface_source);

void dlSurface_fill (dlSurface* surface, DLvoid_p source);

void dlSurface_getData (dlSurface* surface, DLvoid_p dest);
void dlSurface_setData (dlSurface* surface, DLvoid_p source);

DLvoid_p dlSurface_getPixelPI (dlSurface* surface, DLuint index, DLuint offset);
DLvoid_p dlSurface_getPixelP (dlSurface* surface, DLuint x, DLuint y, DLuint offset);
void     dlSurface_getPixelI (dlSurface* surface, DLvoid_p dest, DLuint index, DLuint offset);
void     dlSurface_getPixel (dlSurface* surface, DLvoid_p dest, DLuint x, DLuint y, DLuint offset);
void dlSurface_setPixelI (dlSurface* surface, DLvoid_p source, DLuint index, DLuint offset);
void dlSurface_setPixel (dlSurface* surface, DLvoid_p source, DLuint x, DLuint y, DLuint offset);

/* dlShader
 */

void dlShader_init (dlShader* shader);
void dlShader_free (dlShader* shader);

void dlShader_apply (dlShader* shader, dlBuffer* buffer, dlslRunner* runner);

/* dlPath
 */

void dlPath_init (dlPath* path);
void dlPath_free (dlPath* path);

void dlPath_apply (dlPath* path, dlBuffer* buffer, dlslRunner* runner);

/* dlAttrib
 */

void dlAttrib_init (dlAttrib* attr);
void dlAttrib_free (dlAttrib* attr);

void dlAttrib_setPtrValue (dlAttrib* attr, DLvoid_p source);
void dlAttrib_getPtrValue (dlAttrib* attr, DLvoid_p dest);

/* dlAttrMap
 */

void dlAttrMap_init (dlAttrMap* attrmap, DLuint capacity);
void dlAttrMap_free (dlAttrMap* attrmap);

void dlAttrMap_bindAttribID (dlAttrMap* attrmap, DLuint location, DLchar_p id);
DLuint dlAttrMap_getAttribLocation (dlAttrMap* attrmap, DLchar_p id);

/* dlCode
 */

void dlCode_init (dlCode* code);
void dlCode_free (dlCode* code);

void dlCode_load (dlCode* code, DLdouble* data, DLuint csize);

#endif