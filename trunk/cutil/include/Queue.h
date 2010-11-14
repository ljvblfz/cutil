#ifndef __QUEUE_H__
#define __QUEUE_H__


/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include     "CUtil.h"
#include     "ArrayList.h"


/************************************************************************/
/*                                          Queue definition                                                                         */
/************************************************************************/
typedef struct  Tag_Queue {
        ArrayList          list;       /* Queue container, used ArrayList */
        
        /************************************************************************/
        /*                                              Queue methods                                                                      */
        /************************************************************************/
        /**
         * Test Queue is empty or not.
         * @param queue -- The Queue create by newQueue function.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    (*isEmpty)(struct Tag_Queue* queue);
        /**
         * Get Queue's size.
         * @param queue -- The Queue create by newQueue function.
         * @return    size of Queue.
         */
        UINT     (*getSize)(struct Tag_Queue* queue);
        /**
         * Add string to the Queue.
         * @param queue -- The Queue create by newQueue function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addString)(struct Tag_Queue* queue,  CHAR* value);
        /**
         * Add char to the Queue.
         * @param queue -- The Queue create by newQueue function.
         * @param value -- key value, char type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addChar)(struct Tag_Queue* queue,  const CHAR value);
        /**
         * Add char to the Queue.
         * @param queue -- The Queue create by newQueue function.
         * @param value -- key value, BYTE type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addByte)(struct Tag_Queue* queue,  const BYTE value);
        /**
         * Add char to the Queue.
         * @param queue -- The Queue create by newQueue function.
         * @param value -- key value, SHORT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addShort)(struct Tag_Queue* queue,  const SHORT value);
        /**
         * Add int to the Queue.
         * @param queue -- The Queue create by newQueue function.
         * @param value -- key value, INT type.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    ( *addInt)(struct Tag_Queue* queue,  const INT value);
        /**
         * Add int to the Queue.
         * @param queue -- The Queue create by newQueue function.
         * @param value -- key value, UINT type.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    ( *addUint)(struct Tag_Queue* queue,  const UINT value);
        /**
         * Add int to the Queue.
         * @param queue -- The Queue create by newQueue function.
         * @param value -- key value, LONG type.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    ( *addLong)(struct Tag_Queue* queue,  const LONG value);
        /**
         * Add int to the Queue.
         * @param queue -- The Queue create by newQueue function.
         * @param value -- key value, ULONG type.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    ( *addUlong)(struct Tag_Queue* queue,  const ULONG value);
        /**
         * Add string to the Queue.
         * @param queue -- The Queue create by newQueue function.
         * @param value -- key value, float type.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    ( *addFloat)(struct Tag_Queue* queue,  const FLOAT value);
        /**
         * Add double to the Queue.
         * @param queue -- The Queue create by newQueue function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addDouble)(struct Tag_Queue* queue,  const DOUBLE value);
        /**
         * Add Object pointer to the Queue.
         * @param queue -- The Queue create by newQueue function.
         * @param value -- key value, void* type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addObject)(struct Tag_Queue* queue,  const OBJECT value);
        /**
         * remove value from Queue by hash key.
         * @param queue -- The Queue create by newQueue function.
         * @param key -- hash key, need string type.
         * @return    void type value, should cast the value type when used.The return value should free by invoker.
         */
        OBJECT (*remove)(struct Tag_Queue* queue);

        OBJECT (*peek)(struct Tag_Queue* queue);

        VOID      (*print)(struct Tag_Queue* queue);

}T_Queue, *Queue;




/************************************************************************/
/*                                                                  Prototypes                                                         */
/************************************************************************/
/**
 * Create Queue and init the capacity.
 * @param capacity -- The initial Queue capacity.
 * @return   Queue initial by capacity. NULL if create failed.
 */
Queue	newQueue(UINT capacity);

/**
 * Free Queue memory.
 * @param queue -- The Queue create by newQueue function.
 * @return    CUTILFAILED / CUTILSUCCESS.
 */
UINT     deleteQueue(Queue queue);


#endif /* __QUEUE_H__ */

