/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include    <memory.h>
#include    "CMemory.h"

/************************************************************************/
/*                                                                  Definition                                                           */
/************************************************************************/
#define     GREEDY_ALLOCATE_STRATEGY    1  /* allocate available memory unit, from the fit queue, if no available, allocate big one. */

#define     FIT_ALLOCATE_STRATEGY        0  /* allocate fit memory unit, if no available, allocate failed. */

#define     USER_SYSTEM_MEMORY          1  /* If no available memory unit in memory pool, allocate from system memory. */
#define     SYSTEM_MEMORY_FLAG          0xFF  /* system index flag. */
#define     MEMORY_END_FLAG                 0xFD  /* memory end flag, should use two bytes. */


/************************************************************************/
/*                                                                  Configure                                                           */
/************************************************************************/
T_MemoryPool    atMemoryPool[] = 
{
    /*     size           count        available       Queue */
            {16,           10000,         0,                NULL,     NULL, NULL},
            {32,           10000,         0,             NULL,       NULL,  NULL},
            {64,           10000,         0,             NULL,       NULL,  NULL},
            {128,           10000,         0,             NULL,       NULL,  NULL},
            {256,           10000,         0,             NULL,       NULL,  NULL},
            {512,           10000,         0,              NULL,    NULL,   NULL}
};

BYTE       bMemoryPoolCount = sizeof(atMemoryPool) / sizeof(T_MemoryPool);

MemoryEntry   pUsedMemoryQueueHeader = NULL;
MemoryEntry   pUsedMemoryQueueTail = NULL;

Lock                    memoryPoolLock = NULL;             /* memory pool lock, for multithreading application */

/************************************************************************/
/*                                                      static Memory method                                                    */
/************************************************************************/
INT    initMemoryPool()
{
    BYTE              index;
    BYTE*            pMemoryUnit = NULL;   /* malloc pool memory from system memory. */
    MemoryEntry   previous = NULL;
    MemoryEntry   entry = NULL;

    WORD32    dwMemoryUnitSize = 0;
    WORD32    dwMemoryUnitCounts = 0;

    /* init memory pool lock. */
    memoryPoolLock = newLock();
    if (memoryPoolLock == NULL)
    {
        #if LOGSUPPORT
                clog(LOG_ERROR, "Initial memory pool lock failed.\n");
        #endif
        return -1;
    }

    /* check memory pool is validate. the memory pool size must be sort by asc order */
    for (index=0; index<bMemoryPoolCount-1; index++)
    {
        if (atMemoryPool[index].size > atMemoryPool[index+1].size)
        {
            #if LOGSUPPORT
                  clog(LOG_ERROR, "Initial memory pool configure failed. Memory pool size not order by asc. index[%d] > index[%d]", index, index+1);
            #endif
            return 1;
        }
    }

    /* initial memory pool */
    for (index=0; index<bMemoryPoolCount; index++)
    {
        /* initial memory entry queue. The available queue count must be equals to  memory pool's count, 
         * so we malloc a whole memory to hold all the available memory entry.
         * when we do operation to the available queue, this memory will malloc and free, the operation system
         * maybe use these memory entry again.
         * we can avoid memory part by this.
         */
        atMemoryPool[index].ptHeader = (MemoryEntry)malloc(sizeof(T_MemoryEntry));
        if (atMemoryPool[index].ptHeader == NULL)
        {
            #if LOGSUPPORT
                   clog(LOG_ERROR, "Initial memory pool header failed. memory pool index: %d, size: %ld, malloc size: %d\n", index, atMemoryPool[index].size, dwMemoryUnitSize);
            #endif
            return 2;
        }
        memset(atMemoryPool[index].ptHeader, 0, sizeof(T_MemoryEntry));

        atMemoryPool[index].ptTail = atMemoryPool[index].ptHeader;
        previous = atMemoryPool[index].ptHeader;

        /* malloc pool size-1. the header has allocated already. */
        for (dwMemoryUnitCounts = 1; dwMemoryUnitCounts<atMemoryPool[index].counts; dwMemoryUnitCounts++)
        {
            entry = (MemoryEntry)malloc(sizeof(T_MemoryEntry));
            if (entry == NULL)
            {
                #if LOGSUPPORT
                    clog(LOG_ERROR, "Initial memory pool entry failed. memory pool index: %d, size: %ld, malloc size: %d\n", index, atMemoryPool[index].size, dwMemoryUnitSize);
                #endif
                return 2;
            }
            memset(entry, 0, sizeof(T_MemoryEntry));
            previous->next = entry;
            previous = entry;
        }

        /* memory size should be memory pool size add 4.
         * one byte for used flag, one byte for index, two byte for end flag
         */
        dwMemoryUnitSize = atMemoryPool[index].counts * (atMemoryPool[index].size + 4);
        pMemoryUnit = NULL;
        pMemoryUnit = (BYTE *)malloc(dwMemoryUnitSize);
        if (pMemoryUnit == NULL)
        {
            #if LOGSUPPORT
                clog(LOG_ERROR, "Initial memory pool failed. memory pool index: %d, size: %ld, malloc size: %d\n", index, atMemoryPool[index].size, dwMemoryUnitSize);
            #endif
            return 3;
        }
        memset(pMemoryUnit, 0, dwMemoryUnitSize);

        atMemoryPool[index].pMemoryPool = pMemoryUnit;

        /* initial memory unit */
        for (dwMemoryUnitCounts = 0; dwMemoryUnitCounts<atMemoryPool[index].counts; dwMemoryUnitCounts++)
        {
            atMemoryPool[index].ptTail->address = pMemoryUnit;    /* set address to the available queue. */

            pMemoryUnit[0] = 1; /* used flag, 0-available, 1-used */
            pMemoryUnit[1] = index; /* index of memory pool which memory unit belong to. */
            pMemoryUnit[atMemoryPool[index].size + 2] = MEMORY_END_FLAG;
            pMemoryUnit[atMemoryPool[index].size + 3] = MEMORY_END_FLAG;           

            pMemoryUnit += (atMemoryPool[index].size+4); /* memory unit pointer increase. */

            if (dwMemoryUnitCounts != (atMemoryPool[index].counts-1))
            {
                atMemoryPool[index].ptTail = atMemoryPool[index].ptTail->next; /* ptTail move to next. */
            }
        }

        atMemoryPool[index].available = atMemoryPool[index].counts;
    }

    #if LOGSUPPORT
        clog(LOG_INFO, "Initial memory pool OK.");
    #endif

    return 0;
}


VOID    destroyMemoryPool()
{
    BYTE              index;
    MemoryEntry   entry = NULL;

    deleteLock(memoryPoolLock);

    for(index=0; index<bMemoryPoolCount; index++)
    {
        if (NULL != atMemoryPool[index].pMemoryPool)
        {
            free(atMemoryPool[index].pMemoryPool);
        }

        while (NULL != atMemoryPool[index].ptHeader)
        {
            entry = atMemoryPool[index].ptHeader;
            atMemoryPool[index].ptHeader = atMemoryPool[index].ptHeader->next;

            free(entry);
        }
    }
    pUsedMemoryQueueHeader = NULL;
    pUsedMemoryQueueTail = NULL;
}


VOID*  balloc(WORD32 size)
{
    BYTE   index = 0;
    BYTE* pMemoryUnit = NULL;

    if (memoryPoolLock->getLock(memoryPoolLock) == CUTILFAILED)
    {
        #if LOGSUPPORT
                clog(LOG_ERROR, "Get balloc lock failed.\n");
        #endif
        return NULL;
    }
    /**
     * Allocate strategy 1: 
     * Find all the available memory unit and return the one.
     * If the fit one is not available, allocate a one more than the fit one.
     * If no available memory unit in the memory pool,  allocate the memory from system memory.
     */
#if GREEDY_ALLOCATE_STRATEGY
    for (index=0; index<bMemoryPoolCount; index++)
    {
        if (size <= atMemoryPool[index].size)
        {
            if (atMemoryPool[index].available > 0)
            {
                pMemoryUnit = (BYTE *)(atMemoryPool[index].ptHeader->address);

                /* Remove from available queue and add to used queue. */
                if (pUsedMemoryQueueHeader == NULL)
                {
                    pUsedMemoryQueueHeader = atMemoryPool[index].ptHeader;
                    pUsedMemoryQueueTail = pUsedMemoryQueueHeader;
                }
                else
                {
                    pUsedMemoryQueueTail->next = atMemoryPool[index].ptHeader;
                    pUsedMemoryQueueTail = pUsedMemoryQueueTail->next;
                }

                atMemoryPool[index].ptHeader = atMemoryPool[index].ptHeader->next;
                /* available queue is empty, set ptTail to NULL. */
                if ( atMemoryPool[index].ptHeader == NULL)
                {
                    atMemoryPool[index].ptTail = NULL;
                }

                atMemoryPool[index].available -= 1;
                pUsedMemoryQueueTail->address = NULL;
                pUsedMemoryQueueTail->next = NULL;

                pMemoryUnit[0] = 1;   /* Set memory unit used flag true. */
                
                if (memoryPoolLock->release(memoryPoolLock) == CUTILFAILED)
                {
                    #if LOGSUPPORT
                         clog(LOG_ERROR, "Release balloc lock failed.\n");
                    #endif
                }
                return (VOID *)(pMemoryUnit+2);
            }
        }
    }
    #if LOGSUPPORT
        clog(LOG_INFO, "No available memory unit in memory pool. malloc size: %ld\n", size);
    #endif

    /* No available memory unit in memory pool, allocate from system memory. */
    #if USER_SYSTEM_MEMORY
        pMemoryUnit = (BYTE*)malloc(size + 2); /* allocate size+2, one byte for used flag, one byte set to system flag (0xFF) */
        if (pMemoryUnit == NULL)
        {
            #if LOGSUPPORT
                  clog(LOG_ERROR, "Allocate from system memory failed. malloc size: %ld\n", size);
            #endif
              if (memoryPoolLock->release(memoryPoolLock) == CUTILFAILED)
              {
                #if LOGSUPPORT
                      clog(LOG_ERROR, "Release balloc lock failed.\n");
                #endif
              }
            return NULL;
        }
        pMemoryUnit[0] = 1;
        pMemoryUnit[1] = SYSTEM_MEMORY_FLAG;
        memset(pMemoryUnit+2, 0, size);

        if (memoryPoolLock->release(memoryPoolLock) == CUTILFAILED)
        {
        #if LOGSUPPORT
              clog(LOG_ERROR, "Release balloc lock failed.\n");
        #endif
        }
        return (VOID *)(pMemoryUnit+2);
    #endif
#endif

    /**
     * Allocate strategy 2: 
     * Find all the available memory unit and return the one.
     * If the fit one is not available, allocate a one more than the fit one.
     * If no available memory unit in the memory pool,  allocate the memory from system memory.
     */
#if FIT_ALLOCATE_STRATEGY

#endif
}


VOID   bfree(VOID* address)
{
    BYTE*        pMemoryUnit = NULL;
    WORD32    dwMemorySize = 0;
    BYTE          index = 0;
    MemoryEntry   entry = NULL;

    if (NULL == address)
    {
        #if LOGSUPPORT
            clog(LOG_ERROR, "Free NULL address.\n");
        #endif
        return;
    }

    if (memoryPoolLock->getLock(memoryPoolLock) == CUTILFAILED)
    {
        #if LOGSUPPORT
            clog(LOG_ERROR, "Get bfree lock failed. Memory maybe leek, Address: %p\n", address);
        #endif
        return;
    }
    /* The memory allocate by balloc method must have two bytes flag before address. */
    pMemoryUnit = (BYTE*)((BYTE*)address-2); /* move the pointer two bytes before address */
    if (pMemoryUnit[0] == 0)
    {
        #if LOGSUPPORT
            clog(LOG_ERROR, "Dual free memory. Address: %p\n", address);
        #endif
        if (memoryPoolLock->release(memoryPoolLock) == CUTILFAILED)
        {
        #if LOGSUPPORT
               clog(LOG_ERROR, "Release balloc lock failed.\n");
        #endif
        }
        return;
    }
    else
    {
        index = pMemoryUnit[1];
        /* memory allocate from system, use free method to release. */
        if (index == SYSTEM_MEMORY_FLAG)
        {
            #if LOGSUPPORT
                clog(LOG_INFO, "Release system memory. Address: %p\n", address);
            #endif
            free(pMemoryUnit);
            if (memoryPoolLock->release(memoryPoolLock) == CUTILFAILED)
            {
            #if LOGSUPPORT
                 clog(LOG_ERROR, "Release balloc lock failed.\n");
            #endif
            }
            return;
        }
        else if (index >= bMemoryPoolCount)
        {
            #if LOGSUPPORT
                clog(LOG_ERROR, "Out of memory pool. This operator will not release the memory and maybe cause memory leak. index:%d, Address: %p\n", index, address);
            #endif
            if (memoryPoolLock->release(memoryPoolLock) == CUTILFAILED)
            {
            #if LOGSUPPORT
                   clog(LOG_ERROR, "Release balloc lock failed.\n");
            #endif
            }
            return;
        }
        else
        {
            dwMemorySize = atMemoryPool[index].size;
            /* check for the memory end flag. */
            if ((pMemoryUnit[dwMemorySize+2]==MEMORY_END_FLAG) && (pMemoryUnit[dwMemorySize+3]==MEMORY_END_FLAG))
            {
                if (pUsedMemoryQueueHeader != NULL)
                {
                    entry = pUsedMemoryQueueHeader;
                    pUsedMemoryQueueHeader = pUsedMemoryQueueHeader->next;
                
                    entry->address = pMemoryUnit;
                    entry->next = NULL;

                    /* Available queue is NULL, init the ptHeader and ptTail */
                    if (NULL == atMemoryPool[index].ptTail)
                    {
                        atMemoryPool[index].ptHeader = entry;
                        atMemoryPool[index].ptTail = entry;
                    }
                    else
                    {
                        atMemoryPool[index].ptTail->next = entry;
                        atMemoryPool[index].ptTail = atMemoryPool[index].ptTail->next;
                    }

                    atMemoryPool[index].available += 1;
                }
            }
            /* memory over write, fatal error. */
            else
            {
                #if LOGSUPPORT
                      clog(LOG_ERROR, "Fatal Error, Memory over write. Address: %p\n", address);
                #endif
              if (memoryPoolLock->release(memoryPoolLock) == CUTILFAILED)
              {
                #if LOGSUPPORT
                       clog(LOG_ERROR, "Release balloc lock failed.\n");
                #endif
              }
                return;
            }
        }
    } 

    if (memoryPoolLock->release(memoryPoolLock) == CUTILFAILED)
    {
    #if LOGSUPPORT
            clog(LOG_ERROR, "Release balloc lock failed.\n");
    #endif
    }
}

