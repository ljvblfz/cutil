#ifndef __CUTIL_H__
#define __CUTIL_H__

/************************************************************************/
/*                       Include files                                  */
/************************************************************************/
#include    <stdio.h>
#include    <stdlib.h>
#include    <memory.h>
#include    <string.h>

/************************************************************************/
/*                      Controller definition                           */
/************************************************************************/
#define     DEBUG                   1
#define     LOGSUPPORT       0
#define     USECMEMORY       1


/* Platform */
#define         WIN             1
#define         LINUX            0
#define         VXWORKS            0
#define         CE            0
#define         NW            0
#define         SCOV5            0
#define         UNIX            0
#define         LYNX            0
#define         MACOSX            0
#define         UW            0
#define         sparc            0
#define         SOLARIS            0
#define         QNX4            0
#define         ECOS            0
#define         NETWARE            0
/************************************************************************/
/*                             Include                                  */
/************************************************************************/
#if (DEBUG && LOGSUPPORT)
    #include "CLog.h"
#endif


/************************************************************************/
/*                     Date Type definition                             */
/************************************************************************/

/* word32, unsigned, 32bit. If int not 32bit, should replaced by unsigned long */
#ifndef WORD32
    typedef     unsigned int      WORD32;
#endif

#ifndef BYTE
    typedef     unsigned char      BYTE;
#endif

#ifndef SHORT
    typedef    short          SHORT;
#endif

#ifndef INT
    typedef     int          INT;
#endif

#ifndef UINT
    typedef     unsigned int          UINT;
#endif

#ifndef LONG
    typedef     long          LONG;
#endif

#ifndef ULONG
    typedef    unsigned long          ULONG;
#endif

#ifndef FLOAT
    typedef     float                     FLOAT;
#endif

#ifndef DOUBLE
    typedef     double                     DOUBLE;
#endif

#ifndef CHAR
    typedef     char                     CHAR;
#endif

#ifndef VOID
    typedef     void                     VOID;
#endif

#ifndef OBJECT
    typedef     void*                     OBJECT;
#endif


#define     CUTILFAILED           0
#define     CUTILSUCCESS       1

typedef enum
{
    TYPE_BYTE = 1,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_SHORT,
    TYPE_INT,
    TYPE_UINT,
    TYPE_LONG,
    TYPE_ULONG,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_OBJECT,
    TYPE_VOID
} VauleType;


/************************************************************************/
/*                           Define                                     */
/************************************************************************/
#if USECMEMORY
    extern VOID*      balloc(WORD32 size);
    extern VOID        bfree(VOID* address);
#else
    #define     balloc    malloc
    #define     bfree     free
#endif


#endif /* __CUTIL_H__ */
