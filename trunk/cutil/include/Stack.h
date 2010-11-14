#ifndef __STACK_H__
#define __STACK_H__


/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include     "CUtil.h"
#include     "ArrayList.h"


/************************************************************************/
/*                                          Stack definition                                                                         */
/************************************************************************/
typedef struct  Tag_Stack {
        ArrayList          list;       /* Stack container, used ArrayList */
        
        /************************************************************************/
        /*                                              Stack methods                                                                      */
        /************************************************************************/
        /**
         * Test Stack is empty or not.
         * @param stack -- The Stack create by newStack function.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    (*isEmpty)(struct Tag_Stack* stack);
        /**
         * Get Stack's size.
         * @param stack -- The Stack create by newStack function.
         * @return    size of Stack.
         */
        UINT     (*getSize)(struct Tag_Stack* stack);
         /**
         * Add string to the Stack.
         * @param stack -- The Stack create by newStack function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushString)(struct Tag_Stack* stack,  CHAR* value);
        /**
         * Add char to the Stack.
         * @param stack -- The Stack create by newStack function.
         * @param value -- key value, BYTE type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushByte)(struct Tag_Stack* stack,  const BYTE value);
        /**
         * Add char to the Stack.
         * @param stack -- The Stack create by newStack function.
         * @param value -- key value, char type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushChar)(struct Tag_Stack* stack,  const CHAR value);
        /**
         * Add char to the Stack.
         * @param stack -- The Stack create by newStack function.
         * @param value -- key value, SHORT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushShort)(struct Tag_Stack* stack,  const SHORT value);
        /**
         * Add int to the Stack.
         * @param stack -- The Stack create by newStack function.
         * @param value -- key value, INT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushInt)(struct Tag_Stack* stack,  const INT value);
        /**
         * Add int to the Stack.
         * @param stack -- The Stack create by newStack function.
         * @param value -- key value, UINT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushUint)(struct Tag_Stack* stack,  const UINT value);
        /**
         * Add int to the Stack.
         * @param stack -- The Stack create by newStack function.
         * @param value -- key value, LONG type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushLong)(struct Tag_Stack* stack,  const LONG value);
        /**
         * Add int to the Stack.
         * @param stack -- The Stack create by newStack function.
         * @param value -- key value, ULONG type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushUlong)(struct Tag_Stack* stack,  const ULONG value);
        /**
         * Add string to the Stack.
         * @param stack -- The Stack create by newStack function.
         * @param value -- key value, float type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushFloat)(struct Tag_Stack* stack,  const FLOAT value);
        /**
         * Add double to the Stack.
         * @param stack -- The Stack create by newStack function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushDouble)(struct Tag_Stack* stack,  const DOUBLE value);
        /**
         * Add Object pointer to the Stack.
         * @param stack -- The Stack create by newStack function.
         * @param value -- key value, void* type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushObject)(struct Tag_Stack* stack,  const OBJECT value);
        /**
         * pop value from Stack by hash key.
         * @param stack -- The Stack create by newStack function.
         * @param key -- hash key, need string type.
         * @return    void type value, should cast the value type when used.The return value should free by invoker.
         */
        OBJECT (*pop)(struct Tag_Stack* stack);
         /**
         *  peek value of Stack header, not remove the value.
         * @param stack -- The Stack create by newStack function.
         * @param key -- hash key, need string type.
         * @return    void type value, should cast the value type when used.The return value should free by invoker.
         */
        OBJECT (*peek)(struct Tag_Stack* stack);
        /**
         *  print the stack.
         * @param stack -- The Stack create by newStack function.
         * @param key -- hash key, need string type.
         * @return    void type value, should cast the value type when used.The return value should free by invoker.
         */
        VOID    (*print)(struct Tag_Stack* stack);

}T_Stack, *Stack;




/************************************************************************/
/*                                                                  Prototypes                                                         */
/************************************************************************/
/**
 * Create Stack and init the capacity.
 * @param capacity -- The initial Stack capacity.
 * @return   Stack initial by capacity. NULL if create failed.
 */
Stack	newStack(UINT capacity);

/**
 * Free Stack memory.
 * @param stack -- The Stack create by newStack function.
 * @return    CUTILFAILED / CUTILSUCCESS.
 */
UINT     deleteStack(Stack stack);


#endif /* __STACK_H__ */

