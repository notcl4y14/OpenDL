#include <DL/dldefines.h>

#ifndef DL_UTIL_H
#define DL_UTIL_H

/* Copies a value of one type to a value of another type
 * with casting the value.
 * copydt - copy different type(s)
 */
void DLutil_copydt (DLvoid_p dest_v, DLtype dest_t, DLvoid_p source_v, DLtype source_t);

#endif