/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include    "Stack.h"

/************************************************************************/
/*                                                       Stack methods implement                                              */
/************************************************************************/

/**
 * Test Stack is empty or not.
 * @param stack -- The Stack create by newStack function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
static UINT    Stack_isEmpty(Stack stack)
{
        if ((stack==NULL) || (stack->list==NULL))
                return CUTILFAILED;

        return (stack->list->size  ==  0) ? CUTILSUCCESS : CUTILFAILED;
}

/**
 * Get Stack's size.
 * @param stack -- The Stack create by newStack function.
 * @return    size of Stack.
 */
static UINT    Stack_getSize(Stack stack)
{
        if ((stack!=NULL) || (stack->list!=NULL))
                return stack->list->size;
        else
                return CUTILFAILED;
}

/**
 * Add string to the Stack.
 * @param stack -- The Stack create by newStack function.
 * @param value -- key value, char* type / string.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Stack_pushString(Stack stack, CHAR* value)
{
    return stack->list->addString(stack->list, value);
}

/**
 * Add char to the Stack.
 * @param stack -- The Stack create by newStack function.
 * @param value -- key value, BYTE type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Stack_pushByte(Stack stack, BYTE value)
{
    return stack->list->addByte(stack->list, value);
}

/**
 * Add char to the Stack.
 * @param stack -- The Stack create by newStack function.
 * @param value -- key value, char type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Stack_pushChar(Stack stack, CHAR value)
{
    return stack->list->addChar(stack->list, value);
}

/**
 * Add int to the Stack.
 * @param stack -- The Stack create by newStack function.
 * @param value -- key value, SHORT type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Stack_pushShort(Stack stack, SHORT value)
{
  return stack->list->addShort(stack->list, value);
}

/**
 * Add int to the Stack.
 * @param stack -- The Stack create by newStack function.
 * @param value -- key value, INT type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Stack_pushInt(Stack stack, INT value)
{
  return stack->list->addInt(stack->list, value);
}

/**
 * Add int to the Stack.
 * @param stack -- The Stack create by newStack function.
 * @param value -- key value, UINT type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Stack_pushUint(Stack stack, UINT value)
{
  return stack->list->addUint(stack->list, value);
}

/**
 * Add int to the Stack.
 * @param stack -- The Stack create by newStack function.
 * @param value -- key value, LONG type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Stack_pushLong(Stack stack, LONG value)
{
  return stack->list->addLong(stack->list, value);
}

/**
 * Add int to the Stack.
 * @param stack -- The Stack create by newStack function.
 * @param value -- key value, ULONG type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Stack_pushUlong(Stack stack, ULONG value)
{
  return stack->list->addUlong(stack->list, value);
}

/**
 * Add string to the Stack.
 * @param stack -- The Stack create by newStack function.
 * @param value -- key value, float type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Stack_pushFloat(Stack stack, FLOAT value)
{
   return stack->list->addFloat(stack->list, value);
}

/**
 * Add double to the Stack.
 * @param stack -- The Stack create by newStack function.
 * @param value -- key value, char* type / string.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Stack_pushDouble(Stack stack, DOUBLE value)
{
  return stack->list->addDouble(stack->list, value);
}

/**
 * Add Object pointer to the Stack.
 * @param stack -- The Stack create by newStack function.
 * @param value -- key value, void* type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Stack_pushObject(Stack stack, const OBJECT value)
{
    return stack->list->addObject(stack->list, value);
}

static OBJECT Stack_pop(Stack stack)
{
    return stack->list->remove(stack->list, stack->list->size-1);
}

static OBJECT Stack_peek(Stack stack)
{
    return stack->list->get(stack->list, stack->list->size-1);
}

static VOID Stack_print(Stack stack)
{
    if (stack == NULL)
    {
        return;
    }
    stack->list->print(stack->list);
}


/************************************************************************/
/*                                                Stack    Prototypes                                                         */
/************************************************************************/
/**
 * Create Stack and init the capacity.
 * @param capacity -- The initial Stack capacity.
 * @return   Stack initial by capacity. NULL if create failed.
 */
Stack	newStack(UINT capacity)
{
        Stack stack = NULL;
        ArrayList list = NULL;

        /* initial Stack */
        stack = (Stack) balloc(sizeof(T_Stack));
        if (stack == NULL)
        {
                return NULL;
        }
		memset(stack, 0, sizeof(T_Stack));   

        /* initial ArrayList */
        list = newArrayList(capacity);
        if (list == NULL)
        {
            bfree(stack);
            return NULL;
        }
        stack->list = list;

        /** initial Stack function **/
        stack->isEmpty = Stack_isEmpty;
        stack->getSize = Stack_getSize;

        stack->pushByte = Stack_pushByte;
        stack->pushChar = Stack_pushChar;
        stack->pushString = Stack_pushString;
        stack->pushShort = Stack_pushShort;
        stack->pushInt = Stack_pushInt;
        stack->pushUint = Stack_pushUint;
        stack->pushLong = Stack_pushLong;
        stack->pushUlong = Stack_pushUlong;
        stack->pushFloat = Stack_pushFloat;
        stack->pushDouble = Stack_pushDouble;
        stack->pushObject = Stack_pushObject;

        stack->pop = Stack_pop;
        stack->peek = Stack_peek;
        stack->print = Stack_print;

        return stack;
}

/**
 * Free Stack memory.
 * @param stack -- The Stack create by newStack function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
UINT    deleteStack(Stack stack)
{
        if (stack == NULL)
                return CUTILFAILED;

         if (stack->list != NULL)
         {
            deleteArrayList(stack->list);
         }
       
        bfree(stack);
        return CUTILSUCCESS;
}

