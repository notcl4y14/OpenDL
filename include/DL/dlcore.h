#include <DL/dldefines.h>

#ifndef DL_CORE_H
#define DL_CORE_H

/* Struct member name meanings.
 * OpenDL code has a lot of struct members that might be confusing like
 * stride of DLAttribute is not the same as stride of DLSurface. Struct member
 * name prefixes fix that problem (and creates a new one like what even is usstride or
 * duc(name)). The prefixes can be combined to, for example, ubstride - a base size of unit stride.
 * ================
 * Property values
 * s(name) - an actual size of property (used for specifying stride value size)
 * b(name) - a base size of property (opposite of `s`)
 * c(name) - a count of property (basically the same as `b`)
 * Property types
 * (name)  - whatever would that be
 * d(name) - a data property
 * u(name) - a unit property (utype, usize, ustride)
 * v(name) - a value property (vtype, vsize, vstride)
 */

/* Struct Declarations
 */
struct DLBuffer;
struct DLSurface;
struct DLShader;
struct DLPath;
struct DLAttrib;
struct DLAttrMap;
struct DLCode;

/* Typedef Struct Declarations
 */
typedef struct DLBuffer DLBuffer;
typedef struct DLSurface DLSurface;
typedef struct DLShader DLShader;
typedef struct DLPath DLPath;
typedef struct DLAttrib DLAttrib;
typedef struct DLAttrMap DLAttrMap;
typedef struct DLCode DLCode;

/* Struct Definitions
 */
struct DLAttrib
{
	// Value
	DLvoid_p value;
	DLtype   vtype;
	DLuint   vsize;
	DLuint   vbstride;
	DLuint   vsstride;
};

struct DLAttrMap
{
	DLAttrib* attrs;
	DLchar_p* attrs_id;
	DLuint capacity;
};

struct DLCode
{
	DLdouble* data;
	DLuint ssize;
	DLuint csize;
};

struct DLBuffer
{
	// Data
	DLvoid_p data;
	DLuint ssize;
	DLuint csize;

	// Unit
	DLtype utype;
	DLuint usize;
};

struct DLSurface
{
	// Data
	DLvoid_p data;
	DLuint ssize;
	DLuint csize;

	// Unit
	DLtype utype;
	DLuint usize;
	DLuint ubstride;
	DLuint usstride;

	// Surface
	DLuint width;
	DLuint height;
};

struct DLShader
{
	DLAttrMap attrmap;
	DLCode code;

	DLuint attr_loc_coord;
	DLuint attr_loc_color;
};

struct DLPath
{
	DLAttrMap attrmap;
	DLCode code;

	DLuint attr_loc_surface;
};

/* DLBuffer
 */

DLBuffer* DLBuffer_create ();
void      DLBuffer_delete (DLBuffer* buffer);

void DLBuffer_init (DLBuffer* buffer, DLtype type, DLuint csize, DLuint usize);

DLBuffer* DLBuffer_clone (DLBuffer* buffer);
void      DLBuffer_copy (DLBuffer* buffer_dest, DLBuffer* buffer_source);

void DLBuffer_clear (DLBuffer* buffer);
void DLBuffer_fill (DLBuffer* buffer, DLvoid_p source);

void DLBuffer_getData (DLBuffer* buffer, DLvoid_p dest);
void DLBuffer_loadData (DLBuffer* buffer, DLvoid_p source, DLuint size);

DLvoid_p DLBuffer_getDataUnitP (DLBuffer* buffer, DLuint location);
void     DLBuffer_getDataUnit (DLBuffer* buffer, DLvoid_p dest, DLuint location);
void     DLBuffer_setDataUnit (DLBuffer* buffer, DLvoid_p source, DLuint location);

/* DLSurface
 */

DLSurface* DLSurface_create ();
void       DLSurface_delete (DLSurface* surface);

void DLSurface_init (DLSurface* surface,
                     DLtype type,
                     DLuint usize,
                     DLuint ustride,
                     DLuint width,
                     DLuint height);

DLSurface* DLSurface_clone (DLSurface* surface);
void       DLSurface_copy (DLSurface* surface_dest, DLSurface* surface_source);

void DLSurface_fill (DLSurface* surface, DLvoid_p source);

void DLSurface_getData (DLSurface* surface, DLvoid_p dest);
void DLSurface_loadData (DLSurface* surface, DLvoid_p source);

DLvoid_p DLSurface_getPixelPI (DLSurface* surface, DLuint index, DLuint offset);
DLvoid_p DLSurface_getPixelP (DLSurface* surface, DLuint x, DLuint y, DLuint offset);
void     DLSurface_getPixelI (DLSurface* surface, DLvoid_p dest, DLuint index, DLuint offset);
void     DLSurface_getPixel (DLSurface* surface, DLvoid_p dest, DLuint x, DLuint y, DLuint offset);
void DLSurface_setPixelI (DLSurface* surface, DLvoid_p source, DLuint index, DLuint offset);
void DLSurface_setPixel (DLSurface* surface, DLvoid_p source, DLuint x, DLuint y, DLuint offset);

/* DLShader
 */

DLShader* DLShader_create ();
void      DLShader_delete (DLShader* shader);

void DLShader_init (DLShader* shader, DLuint attrmap_capacity);

void DLShader_loadCode (DLShader* shader, DLdouble* code, DLuint code_size);

DLuint DLShader_getAttrLocation (DLShader* shader, DLchar_p id);
void DLShader_bindAttrLocation (DLShader* shader, DLuint loc, DLchar_p id);
void DLShader_bindAttrParams (DLShader* shader, DLuint loc, DLtype type, DLuint size, DLuint stride);

void DLShader_apply (DLShader* shader, DLSurface* surface);

/* DLPath
 */

DLPath* DLPath_create ();
void    DLPath_delete (DLPath* path);

void DLPath_init (DLPath* path, DLuint attrmap_capacity);

void DLPath_loadCode (DLPath* path, DLdouble* code, DLuint code_size);

DLuint DLPath_getAttrLocation (DLPath* path, DLchar_p id);
void DLPath_bindAttrLocation (DLPath* path, DLuint loc, DLchar_p id);
void DLPath_bindAttrParams (DLPath* path, DLuint loc, DLtype type, DLuint size, DLuint stride);

void DLPath_apply (DLPath* path, DLSurface* surface);

/* DLAttrib
 */

void DLAttrib_init (DLAttrib* attr, DLuint size, DLuint stride);
void DLAttrib_free (DLAttrib* attr);

void DLAttrib_reallocValue (DLAttrib* attr, DLuint size);
void DLAttrib_bindValue (DLAttrib* attr, DLvoid_p source);

/* DLAttrMap
 */

void DLAttrMap_init (DLAttrMap* attrmap, DLuint capacity);
void DLAttrMap_free (DLAttrMap* attrmap);

DLuint DLAttrMap_getAttrLocation (DLAttrMap* attrmap, DLchar_p id);
void   DLAttrMap_bindAttrLocation (DLAttrMap* attrmap, DLuint location, DLchar_p id);

/* DLCode
 */

void DLCode_init (DLCode* code);
void DLCode_free (DLCode* code);

void DLCode_load (DLCode* code, DLdouble* data, DLuint csize);

#endif