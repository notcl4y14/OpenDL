#ifndef DL_DEFINES_H
#define DL_DEFINES_H

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
#define DL_TYPE_COUNT 5
#define DL_NONE    0x00
#define DL_BYTE    0x01
#define DL_SHORT   0x02
#define DL_INT     0x03
#define DL_FLOAT   0x04
#define DL_DOUBLE  0x05

typedef void*           DLvoid_p;

typedef char            DLchar;
typedef char*           DLchar_p;

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

#endif