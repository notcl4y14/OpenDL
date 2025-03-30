#include <DL/dldefines.h>

#ifndef DL_PUBLIC_H
#define DL_PUBLIC_H

/* DL
 */

void dlInit ();
void dlTerminate ();

/* dlBuffer
 */

DLuint dlCreateBuffer (DLtype type, DLuint size);
void   dlFreeBuffer (DLuint buffer);

DLuint dlCloneBuffer (DLuint buffer);
void   dlCopyBuffer (DLuint buffer_dest, DLuint buffer_source);

void dlClearBuffer (DLuint buffer);
void dlFillBuffer (DLuint buffer, DLvoid_p source);

void dlBufferLoadData (DLuint buffer, DLvoid_p source, DLuint size);
void dlBufferGetData (DLuint buffer, DLvoid_p dest);

/* dlSurface
 */

DLuint dlCreateSurface (DLtype type, DLuint width, DLuint height);
DLuint dlCreateSurfaceE (DLtype type, DLuint stride, DLuint width, DLuint height);
void   dlFreeBuffer (DLuint surface);

DLuint dlCloneSurface (DLuint surface);
void   dlCopySurface (DLuint surface_dest, DLuint surface_source);

void dlFillSurface (DLuint surface, DLvoid_p source);

void dlSurfaceLoadData (DLuint surface, DLvoid_p source, DLuint size);
void dlSurfaceGetData (DLuint surface, DLvoid_p dest);

/* DLShader
 */

DLuint dlCreateShader ();
void   dlFreeShader ();

void dlShaderBindAttrib (DLuint shader, DLuint location, DLvoid_p ptr, DLtype type, DLuint size);
void dlShaderBindAttribPtr (DLuint shader, DLuint location, DLvoid_p ptr);
void dlShaderBindAttribType (DLuint shader, DLuint location, DLtype type);
void dlShaderBindAttribSize (DLuint shader, DLuint location, DLuint size);

void dlShaderLoadCode (DLuint shader, DLdouble* code, DLuint code_size);
void dlShaderBindCoordAttr (DLuint shader, DLuint location);
void dlShaderBindValueAttr (DLuint shader, DLuint location);

void   dlShaderBindAttrLocation (DLuint shader, DLuint location, DLchar_p id);
DLuint dlShaderGetAttrLocation (DLuint shader, DLchar_p id);

void dlShaderApply (DLuint shader, DLuint buffer);

/* DLPath
 */

DLuint dlCreatePath ();
void   dlFreePath ();

void dlPathBindAttrib (DLuint path, DLuint location, DLvoid_p ptr, DLtype type, DLuint size);
void dlPathBindAttribPtr (DLuint path, DLuint location, DLvoid_p ptr);
void dlPathBindAttribType (DLuint path, DLuint location, DLtype type);
void dlPathBindAttribSize (DLuint path, DLuint location, DLuint size);

void   dlPathBindAttrLocation (DLuint path, DLuint location, DLchar_p id);
DLuint dlPathGetAttrLocation (DLuint path, DLchar_p id);

void dlPathApply (DLuint path, DLuint buffer);

#endif