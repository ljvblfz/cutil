/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include    "LinkedQueue.h"


/************************************************************************/
/*                                                       LinkedLinkedQueue methods implement                                             */
/************************************************************************/

/**
 * Test LinkedQueue is empty or not.
 * @param queue -- The LinkedQueue create by newLinkedQueue function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
static UINT    LinkedQueue_isEmpty(LinkedQueue queue)
{
        if (queue==NULL || queue->list==NULL)
                return CUTILFAILED;

        return (queue->list->size  ==  0) ? CUTILSUCCESS : CUTILFAILED;
}

/**
 * Get LinkedQueue's size.
 * @param queue -- The LinkedQueue create by newLinkedQueue function.
 * @return    size of LinkedQueue.
 */
static UINT    LinkedQueue_getSize(LinkedQueue queue)
{
        if ((queue!=NULL) && (queue->list!=NULL))
                return queue->list->size;
        else
                return CUTILFAILED;
}

/**
 * Add string to the LinkedQueue.
 * @param queue -- The LinkedQueue create by newLinkedQueue function.
 * @param value -- key value, char* type / string.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedQueue_addString(LinkedQueue queue, const CHAR* value)
{
    return queue->list->addString(queue->list, value);
}

/**
 * Add char to the LinkedQueue.
 * @param queue -- The LinkedQueue create by newLinkedQueue function.
 * @param value -- key value, char type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedQueue_addChar(LinkedQueue queue, CHAR value)
{
    return queue->list->addChar(queue->list, value);
}

/**
 * Add char to the LinkedQueue.
 * @param queue -- The LinkedQueue create by newLinkedQueue function.
 * @param value -- key value, BYTE type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedQueue_addByte(LinkedQueue queue, BYTE value)
{
    return queue->list->addByte(queue->list, value);
}

/**
 * Add char to the LinkedQueue.
 * @param queue -- The LinkedQueue create by newLinkedQueue function.
 * @param value -- key value, SHORT type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedQueue_addShort(LinkedQueue queue, SHORT value)
{
    return queue->list->addShort(queue->list, value);
}

/**
 * Add int to the LinkedQueue.
 * @param queue -- The LinkedQueue create by newLinkedQueue function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedQueue_addInt(LinkedQueue queue, INT value)
{
  return queue->list->addInt(queue->list, value);
}

/**
 * Add int to the LinkedQueue.
 * @param queue -- The LinkedQueue create by newLinkedQueue function.
 * @param value -- key value, UINT type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedQueue_addUint(LinkedQueue queue, UINT value)
{
  return queue->list->addUint(queue->list, value);
}

/**
 * Add int to the LinkedQueue.
 * @param queue -- The LinkedQueue create by newLinkedQueue function.
 * @param value -- key value, LONG type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedQueue_addLong(LinkedQueue queue, LONG value)
{
  return queue->list->addLong(queue->list, value);
}

/**
 * Add int to the LinkedQueue.
 * @param queue -- The LinkedQueue create by newLinkedQueue function.
 * @param value -- key value, ULONG type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedQueue_addUlong(LinkedQueue queue, ULONG value)
{
  return queue->list->addUlong(queue->list, value);
}

/**
 * Add string to the LinkedQueue.
 * @param queue -- The LinkedQueue create by newLinkedQueue function.
 * @param value -- key value, float type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedQueue_addFloat(LinkedQueue queue, FLOAT value)
{
   return queue->list->addFloat(queue->list, value);
}

/**
 * Add double to the LinkedQueue.
 * @param queue -- The LinkedQueue create by newLinkedQueue function.
 * @param value -- key value, char* type / string.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedQueue_addDouble(LinkedQueue queue, DOUBLE value)
{
  return queue->list->addDouble(queue->list, value);
}

/**
 * Add Object pointer to the LinkedQueue.
 * @param queue -- The LinkedQueue create by newLinkedQueue function.
 * @param value -- key value, void* type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedQueue_addObject(LinkedQueue queue, const OBJECT value)
{
    return queue->list->addObject(queue->list, value);
}

static OBJECT LinkedQueue_remove(LinkedQueue queue)
{
    return queue->list->removeFirst(queue->list);
}

static OBJECT LinkedQueue_peek(LinkedQueue queue)
{
    return queue->list->getFirst(queue->list);
}

static VOID     LinkedQueue_print(LinkedQueue queue)
{
    queue->list->print(queue->list);
}

/************************************************************************/
/*                                                LinkedQueue    Prototypes                                                         */
/************************************************************************/
/**
 * Create LinkedQueue and init the capacity.
 * @param capacity -- The initial LinkedQueue capacity.
 * @return   LinkedQueue initial by capacity. NULL if create failed.
 */
LinkedQueue	newLinkedQueue()
{
        LinkedQueue queue = NULL;
        LinkedList list = NULL;

        /* initial LinkedQueue */
        queue = (LinkedQueue) balloc(sizeof(T_LinkedQueue));
        if (queue == NULL)
        {
                return NULL;
        }
		memset(queue, 0, sizeof(T_LinkedQueue));   

        /* initial ArrayList */
        list = newLinkedList();
        if (list == NULL)
        {
            bfree(queue);
            return NULL;
        }
        queue->list = list;

        /** initial LinkedQueue function **/
        queue->isEmpty = LinkedQueue_isEmpty;
        queue->getSize = LinkedQueue_getSize;

        queue->addChar = LinkedQueue_addChar;
        queue->addByte = LinkedQueue_addByte;
        queue->addShort = LinkedQueue_addShort;
        queue->addString = LinkedQueue_addString;
        queue->addInt = LinkedQueue_addInt;
        queue->addUint = LinkedQueue_addUint;
        queue->addLong = LinkedQueue_addLong;
        queue->addUlong = LinkedQueue_addUlong;
        queue->addFloat = LinkedQueue_addFloat;
        queue->addDouble = LinkedQueue_addDouble;
        queue->addObject = LinkedQueue_addObject;

        queue->remove = LinkedQueue_remove;
        queue->peek = LinkedQueue_peek;

        queue->print = LinkedQueue_print;

        return queue;
}

/**
 * Free LinkedQueue memory.
 * @param queue -- The LinkedQueue create by newLinkedQueue function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
UINT    deleteLinkedQueue(LinkedQueue queue)
{
        if (queue == NULL)
                return CUTILFAILED;

         if (queue->list != NULL)
         {
            deleteLinkedList(queue->list);
         }
       
        bfree(queue);
        return CUTILSUCCESS;
}

