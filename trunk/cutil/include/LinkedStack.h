#ifndef __LINKEDSTACK_H__
#define __LINKEDSTACK_H__


/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include     "CUtil.h"
#include     "LinkedList.h"


/************************************************************************/
/*                                          LinkedStack definition                                                                         */
/************************************************************************/
typedef struct  Tag_LinkedStack {
        LinkedList          list;       /* LinkedStack container, used LinkedList */
        
        /************************************************************************/
        /*                                              LinkedStack methods                                                                      */
        /************************************************************************/
        /**
         * Test LinkedStack is empty or not.
         * @param stack -- The LinkedStack create by newLinkedStack function.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    (*isEmpty)(struct Tag_LinkedStack* stack);
        /**
         * Get LinkedStack's size.
         * @param stack -- The LinkedStack create by newLinkedStack function.
         * @return    size of LinkedStack.
         */
        UINT     (*getSize)(struct Tag_LinkedStack* stack);
         /**
         * Add string to the LinkedStack.
         * @param stack -- The LinkedStack create by newLinkedStack function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushString)(struct Tag_LinkedStack* stack,  const CHAR* value);
        /**
         * Add char to the LinkedStack.
         * @param stack -- The LinkedStack create by newLinkedStack function.
         * @param value -- key value, BYTE type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushByte)(struct Tag_LinkedStack* stack,  const BYTE value);
        /**
         * Add char to the LinkedStack.
         * @param stack -- The LinkedStack create by newLinkedStack function.
         * @param value -- key value, char type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushChar)(struct Tag_LinkedStack* stack,  const CHAR value);
        /**
         * Add char to the LinkedStack.
         * @param stack -- The LinkedStack create by newLinkedStack function.
         * @param value -- key value, SHORT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushShort)(struct Tag_LinkedStack* stack,  const SHORT value);
        /**
         * Add int to the LinkedStack.
         * @param stack -- The LinkedStack create by newLinkedStack function.
         * @param value -- key value, INT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushInt)(struct Tag_LinkedStack* stack,  const INT value);
        /**
         * Add int to the LinkedStack.
         * @param stack -- The LinkedStack create by newLinkedStack function.
         * @param value -- key value, UINT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushUint)(struct Tag_LinkedStack* stack,  const UINT value);
        /**
         * Add int to the LinkedStack.
         * @param stack -- The LinkedStack create by newLinkedStack function.
         * @param value -- key value, LONG type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushLong)(struct Tag_LinkedStack* stack,  const LONG value);
        /**
         * Add int to the LinkedStack.
         * @param stack -- The LinkedStack create by newLinkedStack function.
         * @param value -- key value, ULONG type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushUlong)(struct Tag_LinkedStack* stack,  const ULONG value);
        /**
         * Add string to the LinkedStack.
         * @param stack -- The LinkedStack create by newLinkedStack function.
         * @param value -- key value, float type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushFloat)(struct Tag_LinkedStack* stack,  const FLOAT value);
        /**
         * Add double to the LinkedStack.
         * @param stack -- The LinkedStack create by newLinkedStack function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushDouble)(struct Tag_LinkedStack* stack,  const DOUBLE value);
        /**
         * Add Object pointer to the LinkedStack.
         * @param stack -- The LinkedStack create by newLinkedStack function.
         * @param value -- key value, void* type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *pushObject)(struct Tag_LinkedStack* stack,  const OBJECT value);
        /**
         * pop value from LinkedStack by hash key.
         * @param stack -- The LinkedStack create by newLinkedStack function.
         * @param key -- hash key, need string type.
         * @return    void type value, should cast the value type when used.The return value should free by invoker.
         */
        OBJECT (*pop)(struct Tag_LinkedStack* stack);
        /**
         * pop value from LinkedStack by hash key.
         * @param stack -- The LinkedStack create by newLinkedStack function.
         * @param key -- hash key, need string type.
         * @return    void type value, should cast the value type when used.The return value should free by invoker.
         */
        OBJECT (*peek)(struct Tag_LinkedStack* stack);

        VOID     (*print)(struct Tag_LinkedStack* stack);

}T_LinkedStack, *LinkedStack;




/************************************************************************/
/*                                                                  Prototypes                                                         */
/************************************************************************/
/**
 * Create LinkedStack and init the capacity.
 * @param capacity -- The initial LinkedStack capacity.
 * @return   LinkedStack initial by capacity. NULL if create failed.
 */
LinkedStack	newLinkedStack();

/**
 * Free LinkedStack memory.
 * @param stack -- The LinkedStack create by newLinkedStack function.
 * @return    CUTILFAILED / CUTILSUCCESS.
 */
UINT     deleteLinkedStack(LinkedStack stack);


#endif /* __LINKEDSTACK_H__ */

