#include <DL/dldefines.h>
#include <DL/dlcore.h>
#include <DL/dlsl.h>

#ifndef DL_SYSTEM_H
#define DL_SYSTEM_H

extern DLuint*   DL_type_sizes;

extern DLSLRunner DL_DLSLRunner;

void DL_init ();
void DL_terminate ();

#endif