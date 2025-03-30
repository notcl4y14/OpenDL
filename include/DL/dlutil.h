#include <DL/dldefines.h>

#ifndef DL_UTIL_H
#define DL_UTIL_H

/* Copies a value of one type to a value of another type
 * with casting the value.
 * copydt - copy different type(s)
 */
void DLutil_copydt (DLvoid_p dest_v, DLtype dest_t, DLvoid_p source_v, DLtype source_t);

/* Copies an array of values of one type to an array of values of another type
 * with casting the values.
 * copydts - copy different type(s) with stride
 */
void DLutil_copydts (DLvoid_p dest_v,
                     DLtype dest_t,
                     DLuint dest_sz,
                     DLuint dest_st,
                     DLvoid_p source_v,
                     DLtype source_t,
                     DLuint source_sz,
                     DLuint source_st);

#endif