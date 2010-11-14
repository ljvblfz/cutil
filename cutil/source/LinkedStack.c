/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include    "LinkedStack.h"

/************************************************************************/
/*                                                       LinkedStack methods implement                                              */
/************************************************************************/

/**
 * Test LinkedStack is empty or not.
 * @param stack -- The LinkedStack create by newLinkedStack function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
static UINT    LinkedStack_isEmpty(LinkedStack stack)
{
        if ((stack==NULL) || (stack->list==NULL))
                return CUTILFAILED;

        return (stack->list->size  ==  0) ? CUTILSUCCESS : CUTILFAILED;
}

/**
 * Get LinkedStack's size.
 * @param stack -- The LinkedStack create by newLinkedStack function.
 * @return    size of LinkedStack.
 */
static UINT    LinkedStack_getSize(LinkedStack stack)
{
        if ((stack!=NULL) || (stack->list!=NULL))
                return stack->list->size;
        else
                return CUTILFAILED;
}

/**
 * Add string to the LinkedStack.
 * @param stack -- The LinkedStack create by newLinkedStack function.
 * @param value -- key value, char* type / string.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedStack_pushString(LinkedStack stack, const CHAR* value)
{
    return stack->list->addString(stack->list, value);
}

/**
 * Add char to the LinkedStack.
 * @param stack -- The LinkedStack create by newLinkedStack function.
 * @param value -- key value, BYTE type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedStack_pushByte(LinkedStack stack, BYTE value)
{
    return stack->list->addByte(stack->list, value);
}

/**
 * Add char to the LinkedStack.
 * @param stack -- The LinkedStack create by newLinkedStack function.
 * @param value -- key value, char type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedStack_pushChar(LinkedStack stack, CHAR value)
{
    return stack->list->addChar(stack->list, value);
}

/**
 * Add int to the LinkedStack.
 * @param stack -- The LinkedStack create by newLinkedStack function.
 * @param value -- key value, SHORT type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedStack_pushShort(LinkedStack stack, SHORT value)
{
  return stack->list->addShort(stack->list, value);
}

/**
 * Add int to the LinkedStack.
 * @param stack -- The LinkedStack create by newLinkedStack function.
 * @param value -- key value, INT type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedStack_pushInt(LinkedStack stack, INT value)
{
  return stack->list->addInt(stack->list, value);
}

/**
 * Add int to the LinkedStack.
 * @param stack -- The LinkedStack create by newLinkedStack function.
 * @param value -- key value, UINT type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedStack_pushUint(LinkedStack stack, UINT value)
{
  return stack->list->addUint(stack->list, value);
}

/**
 * Add int to the LinkedStack.
 * @param stack -- The LinkedStack create by newLinkedStack function.
 * @param value -- key value, LONG type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedStack_pushLong(LinkedStack stack, LONG value)
{
  return stack->list->addLong(stack->list, value);
}

/**
 * Add int to the LinkedStack.
 * @param stack -- The LinkedStack create by newLinkedStack function.
 * @param value -- key value, ULONG type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedStack_pushUlong(LinkedStack stack, ULONG value)
{
  return stack->list->addUlong(stack->list, value);
}

/**
 * Add string to the LinkedStack.
 * @param stack -- The LinkedStack create by newLinkedStack function.
 * @param value -- key value, float type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedStack_pushFloat(LinkedStack stack, FLOAT value)
{
   return stack->list->addFloat(stack->list, value);
}

/**
 * Add double to the LinkedStack.
 * @param stack -- The LinkedStack create by newLinkedStack function.
 * @param value -- key value, char* type / string.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedStack_pushDouble(LinkedStack stack, DOUBLE value)
{
  return stack->list->addDouble(stack->list, value);
}

/**
 * Add Object pointer to the LinkedStack.
 * @param stack -- The LinkedStack create by newLinkedStack function.
 * @param value -- key value, void* type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedStack_pushObject(LinkedStack stack, const OBJECT value)
{
    return stack->list->addObject(stack->list, value);
}

static OBJECT LinkedStack_pop(LinkedStack stack)
{
    return stack->list->removeLast(stack->list);
}

static VOID     LinkedStack_print(LinkedStack stack)
{
    stack->list->print(stack->list);
}
/************************************************************************/
/*                                                LinkedStack    Prototypes                                                         */
/************************************************************************/
/**
 * Create LinkedStack.
 * @return   LinkedStack initial by capacity. NULL if create failed.
 */
LinkedStack	newLinkedStack()
{
        LinkedStack stack = NULL;
        LinkedList list = NULL;

        /* initial LinkedStack */
        stack = (LinkedStack) balloc(sizeof(T_LinkedStack));
        if (stack == NULL)
        {
                return NULL;
        }
		memset(stack, 0, sizeof(T_LinkedStack));   

        /* initial LinkedList */
        list = newLinkedList();
        if (list == NULL)
        {
            bfree(stack);
            return NULL;
        }
        stack->list = list;

        /** initial LinkedStack function **/
        stack->isEmpty = LinkedStack_isEmpty;
        stack->getSize = LinkedStack_getSize;

        stack->pushByte = LinkedStack_pushByte;
        stack->pushChar = LinkedStack_pushChar;
        stack->pushString = LinkedStack_pushString;
        stack->pushShort = LinkedStack_pushShort;
        stack->pushInt = LinkedStack_pushInt;
        stack->pushUint = LinkedStack_pushUint;
        stack->pushLong = LinkedStack_pushLong;
        stack->pushUlong = LinkedStack_pushUlong;
        stack->pushFloat = LinkedStack_pushFloat;
        stack->pushDouble = LinkedStack_pushDouble;
        stack->pushObject = LinkedStack_pushObject;

        stack->pop = LinkedStack_pop;
        stack->print = LinkedStack_print;

        return stack;
}

/**
 * Free LinkedStack memory.
 * @param stack -- The LinkedStack create by newLinkedStack function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
UINT    deleteLinkedStack(LinkedStack stack)
{
        if (stack == NULL)
                return CUTILFAILED;

         if (stack->list != NULL)
         {
            deleteLinkedList(stack->list);
         }
       
        bfree(stack);
        return CUTILSUCCESS;
}

