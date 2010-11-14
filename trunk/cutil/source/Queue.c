/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include    "Queue.h"


/************************************************************************/
/*                                                       Queue methods implement                                             */
/************************************************************************/

/**
 * Test Queue is empty or not.
 * @param queue -- The Queue create by newQueue function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
static UINT    Queue_isEmpty(Queue queue)
{
        if (queue==NULL || queue->list==NULL)
                return CUTILFAILED;

        return (queue->list->size  ==  0) ? CUTILSUCCESS : CUTILFAILED;
}

/**
 * Get Queue's size.
 * @param queue -- The Queue create by newQueue function.
 * @return    size of Queue.
 */
static UINT    Queue_getSize(Queue queue)
{
        if ((queue!=NULL) && (queue->list!=NULL))
                return queue->list->size;
        else
                return CUTILFAILED;
}

/**
 * Add string to the Queue.
 * @param queue -- The Queue create by newQueue function.
 * @param value -- key value, char* type / string.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Queue_addString(Queue queue, CHAR* value)
{
    return queue->list->addString(queue->list, value);
}

/**
 * Add char to the Queue.
 * @param queue -- The Queue create by newQueue function.
 * @param value -- key value, char type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Queue_addChar(Queue queue, CHAR value)
{
    return queue->list->addChar(queue->list, value);
}

/**
 * Add char to the Queue.
 * @param queue -- The Queue create by newQueue function.
 * @param value -- key value, BYTE type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Queue_addByte(Queue queue, BYTE value)
{
    return queue->list->addByte(queue->list, value);
}

/**
 * Add char to the Queue.
 * @param queue -- The Queue create by newQueue function.
 * @param value -- key value, SHORT type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Queue_addShort(Queue queue, SHORT value)
{
    return queue->list->addShort(queue->list, value);
}

/**
 * Add int to the Queue.
 * @param queue -- The Queue create by newQueue function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Queue_addInt(Queue queue, INT value)
{
  return queue->list->addInt(queue->list, value);
}

/**
 * Add int to the Queue.
 * @param queue -- The Queue create by newQueue function.
 * @param value -- key value, UINT type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Queue_addUint(Queue queue, UINT value)
{
  return queue->list->addUint(queue->list, value);
}

/**
 * Add int to the Queue.
 * @param queue -- The Queue create by newQueue function.
 * @param value -- key value, LONG type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Queue_addLong(Queue queue, LONG value)
{
  return queue->list->addLong(queue->list, value);
}

/**
 * Add int to the Queue.
 * @param queue -- The Queue create by newQueue function.
 * @param value -- key value, ULONG type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Queue_addUlong(Queue queue, ULONG value)
{
  return queue->list->addUlong(queue->list, value);
}

/**
 * Add string to the Queue.
 * @param queue -- The Queue create by newQueue function.
 * @param value -- key value, float type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Queue_addFloat(Queue queue, FLOAT value)
{
   return queue->list->addFloat(queue->list, value);
}

/**
 * Add double to the Queue.
 * @param queue -- The Queue create by newQueue function.
 * @param value -- key value, char* type / string.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Queue_addDouble(Queue queue, DOUBLE value)
{
  return queue->list->addDouble(queue->list, value);
}

/**
 * Add Object pointer to the Queue.
 * @param queue -- The Queue create by newQueue function.
 * @param value -- key value, void* type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Queue_addObject(Queue queue, const OBJECT value)
{
    return queue->list->addObject(queue->list, value);
}

static OBJECT Queue_remove(Queue queue)
{
    return queue->list->remove(queue->list, 0);
}

static OBJECT Queue_peek(Queue queue)
{
    return queue->list->get(queue->list, 0);
}

static VOID Queue_print(Queue queue)
{
    if (queue == NULL)
    {
        return;
    }

    queue->list->print(queue->list);
}

/************************************************************************/
/*                                                Queue    Prototypes                                                         */
/************************************************************************/
/**
 * Create Queue and init the capacity.
 * @param capacity -- The initial Queue capacity.
 * @return   Queue initial by capacity. NULL if create failed.
 */
Queue	newQueue(UINT capacity)
{
        Queue queue = NULL;
        ArrayList list = NULL;

        /* initial Queue */
        queue = (Queue) balloc(sizeof(T_Queue));
        if (queue == NULL)
        {
                return NULL;
        }
		memset(queue, 0, sizeof(T_Queue));   

        /* initial ArrayList */
        list = newArrayList(capacity);
        if (list == NULL)
        {
            bfree(queue);
            return NULL;
        }
        queue->list = list;

        /** initial Queue function **/
        queue->isEmpty = Queue_isEmpty;
        queue->getSize = Queue_getSize;

        queue->addChar = Queue_addChar;
        queue->addByte = Queue_addByte;
        queue->addShort = Queue_addShort;
        queue->addString = Queue_addString;
        queue->addInt = Queue_addInt;
        queue->addUint = Queue_addUint;
        queue->addLong = Queue_addLong;
        queue->addUlong = Queue_addUlong;
        queue->addFloat = Queue_addFloat;
        queue->addDouble = Queue_addDouble;
        queue->addObject = Queue_addObject;

        queue->peek = Queue_peek;
        queue->remove = Queue_remove;
        queue->print = Queue_print;

        return queue;
}

/**
 * Free Queue memory.
 * @param queue -- The Queue create by newQueue function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
UINT    deleteQueue(Queue queue)
{
        if (queue == NULL)
                return CUTILFAILED;

         if (queue->list != NULL)
         {
            deleteArrayList(queue->list);
         }
       
        bfree(queue);
        return CUTILSUCCESS;
}

