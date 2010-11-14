#ifndef __LINKEDQUEUE_H__
#define __LINKEDQUEUE_H__


/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include     "CUtil.h"
#include     "LinkedList.h"


/************************************************************************/
/*                                          LinkedLinkedQueue definition                                                                         */
/************************************************************************/
typedef struct  Tag_LinkedQueue {
        LinkedList          list;       /* LinkedLinkedQueue container, used LinkedList */
        
        /************************************************************************/
        /*                                              LinkedLinkedQueue methods                                                                      */
        /************************************************************************/
        /**
         * Test LinkedLinkedQueue is empty or not.
         * @param queue -- The LinkedLinkedQueue create by newLinkedQueue function.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    (*isEmpty)(struct Tag_LinkedQueue* queue);
        /**
         * Get LinkedQueue's size.
         * @param queue -- The LinkedQueue create by newLinkedQueue function.
         * @return    size of LinkedQueue.
         */
        UINT     (*getSize)(struct Tag_LinkedQueue* queue);
        /**
         * Add string to the LinkedQueue.
         * @param queue -- The LinkedQueue create by newLinkedQueue function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addString)(struct Tag_LinkedQueue* queue,  const CHAR* value);
        /**
         * Add char to the LinkedQueue.
         * @param queue -- The LinkedQueue create by newLinkedQueue function.
         * @param value -- key value, char type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addChar)(struct Tag_LinkedQueue* queue,  const CHAR value);
        /**
         * Add char to the LinkedQueue.
         * @param queue -- The LinkedQueue create by newLinkedQueue function.
         * @param value -- key value, BYTE type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addByte)(struct Tag_LinkedQueue* queue,  const BYTE value);
        /**
         * Add char to the LinkedQueue.
         * @param queue -- The LinkedQueue create by newLinkedQueue function.
         * @param value -- key value, SHORT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addShort)(struct Tag_LinkedQueue* queue,  const SHORT value);
        /**
         * Add int to the LinkedQueue.
         * @param queue -- The LinkedQueue create by newLinkedQueue function.
         * @param value -- key value, INT type.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    ( *addInt)(struct Tag_LinkedQueue* queue,  const INT value);
        /**
         * Add int to the LinkedQueue.
         * @param queue -- The LinkedQueue create by newLinkedQueue function.
         * @param value -- key value, UINT type.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    ( *addUint)(struct Tag_LinkedQueue* queue,  const UINT value);
        /**
         * Add int to the LinkedQueue.
         * @param queue -- The LinkedQueue create by newLinkedQueue function.
         * @param value -- key value, LONG type.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    ( *addLong)(struct Tag_LinkedQueue* queue,  const LONG value);
        /**
         * Add int to the LinkedQueue.
         * @param queue -- The LinkedQueue create by newLinkedQueue function.
         * @param value -- key value, ULONG type.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    ( *addUlong)(struct Tag_LinkedQueue* queue,  const ULONG value);
        /**
         * Add string to the LinkedQueue.
         * @param queue -- The LinkedQueue create by newLinkedQueue function.
         * @param value -- key value, float type.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    ( *addFloat)(struct Tag_LinkedQueue* queue,  const FLOAT value);
        /**
         * Add double to the LinkedQueue.
         * @param queue -- The LinkedQueue create by newLinkedQueue function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addDouble)(struct Tag_LinkedQueue* queue,  const DOUBLE value);
        /**
         * Add Object pointer to the LinkedQueue.
         * @param queue -- The LinkedQueue create by newLinkedQueue function.
         * @param value -- key value, void* type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addObject)(struct Tag_LinkedQueue* queue,  const OBJECT value);
        /**
         * remove value from LinkedQueue by hash key.
         * @param queue -- The LinkedQueue create by newLinkedQueue function.
         * @param key -- hash key, need string type.
         * @return    void type value, should cast the value type when used.The return value should free by invoker.
         */
        OBJECT (*remove)(struct Tag_LinkedQueue* queue);
        /**
         * get value from LinkedQueue but not remove it.
         * @param queue -- The LinkedQueue create by newLinkedQueue function.
         * @param key -- hash key, need string type.
         * @return    void type value, should cast the value type when used.The return value should free by invoker.
         */
        OBJECT  (*peek)(struct Tag_LinkedQueue* queue);

        VOID     (*print)(struct Tag_LinkedQueue* queue);

}T_LinkedQueue, *LinkedQueue;




/************************************************************************/
/*                                                                  Prototypes                                                         */
/************************************************************************/
/**
 * Create LinkedQueue .
 * @return   LinkedQueue initial by capacity. NULL if create failed.
 */
LinkedQueue	newLinkedQueue();

/**
 * Free LinkedQueue memory.
 * @param queue -- The LinkedQueue create by newLinkedQueue function.
 * @return    CUTILFAILED / CUTILSUCCESS.
 */
UINT     deleteLinkedQueue(LinkedQueue queue);


#endif /* __LINKEDQUEUE_H__ */

