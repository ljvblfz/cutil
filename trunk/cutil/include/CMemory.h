#ifndef __CMEMORY_H__
#define __CMEMORY_H__


/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include     "CUtil.h"
#include     "Lock.h"


/************************************************************************/
/*                                                       Memory structure define                                                */
/************************************************************************/
/**
 * Memory Entry.
 * address point to memory.
 * the memory structure like this:
 * struct Memory{
 *     BYTE  flag;          // memory flag. available=0, used=1
 *     BYTE  poolIndex;// memory pool index, the index is the pool index in MemoryPool configure.
 *     BYTE[size];         // memory, size equals to MemoryPool size
 *     BYTE[2];             // end flag. 0xFDFD
 * }
 * available and availableQueue should initial in init function
 */
typedef struct Tag_MemoryEntry
{
    VOID*                                address;    /* memory address */
    struct Tag_MemoryEntry*     next;         /* pool entry size */
}T_MemoryEntry, *MemoryEntry;

/**
 * Memory pool should configure before initial.
 * size and counts should initial in configure.
 * available and availableQueue should initial in init function
 */
typedef struct Tag_MemoryPool
{
    WORD32            size;              /* pool entry size */
    WORD32            counts;         /* pool entry count */
    WORD32            available;      /* pool entry available count */

    BYTE*                pMemoryPool; /* memory pool, a whole memory for the pool entry. */    
    MemoryEntry       ptHeader;    /* available queue header */     
    MemoryEntry       ptTail;          /* available queue tail */
}T_MemoryPool, *MemoryPool;


/************************************************************************/
/*                                                                  Prototypes                                                         */
/************************************************************************/
INT    initMemoryPool();

VOID    destroyMemoryPool();

VOID*  balloc(WORD32 size);

VOID   bfree(VOID* address);

#endif /* __CMEMORY_H__ */

