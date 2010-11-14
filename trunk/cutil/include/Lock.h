#ifndef __LOCK_H__
#define __LOCK_H__


/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include     "CUtil.h"

/************************************************************************/
/*                                          Stack definition                                                                         */
/************************************************************************/
typedef struct  Tag_Lock {

        #if WIN
            VOID*    semaphore;
        #endif

        /************************************************************************/
        /*                                              Stack methods                                                                      */
        /************************************************************************/
        /**
         * Test Stack is empty or not.
         * @param stack -- The Stack create by newStack function.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    (*getLock)(struct Tag_Lock* lock);
        /**
         * Get Stack's size.
         * @param stack -- The Stack create by newStack function.
         * @return    size of Stack.
         */
        UINT     (*release)(struct Tag_Lock* lock);

}T_Lock, *Lock;




/************************************************************************/
/*                                                                  Prototypes                                                         */
/************************************************************************/
/**
 * Create Stack and init the capacity.
 * @param capacity -- The initial Stack capacity.
 * @return   Stack initial by capacity. NULL if create failed.
 */
Lock	newLock();

/**
 * Free Stack memory.
 * @param stack -- The Stack create by newStack function.
 * @return    CUTILFAILED / CUTILSUCCESS.
 */
UINT     deleteLock(Lock lock);


#endif /* __LOCK_H__ */

