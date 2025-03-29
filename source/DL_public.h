#include <DL_defines.h>

#ifndef DL_PUBLIC_H
#define DL_PUBLIC_H

/* DL
 */

void dlInit ();
void dlTerminate ();

/* DLBuffer
 */

DLuint dlCreateBuffer (DLtype type, DLuint size);
void   dlFreeBuffer (DLuint buffer);

void dlClearBuffer (DLuint buffer);
void dlFillBuffer (DLuint buffer, DLvoid_p source);

void dlBufferData (DLuint buffer, DLvoid_p source, DLuint size);
void dlBufferGetData (DLuint buffer, DLvoid_p dest);

/* DLShader
 */

DLuint dlCreateShader ();
void   dlFreeShader ();

void dlShaderBindAttrib (DLuint shader, DLuint location, DLvoid_p ptr, DLtype type, DLuint size);
void dlShaderBindAttribPtr (DLuint shader, DLuint location, DLvoid_p ptr);
void dlShaderBindAttribType (DLuint shader, DLuint location, DLtype type);
void dlShaderBindAttribSize (DLuint shader, DLuint location, DLuint size);

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