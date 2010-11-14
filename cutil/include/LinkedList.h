#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__


/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include     "CUtil.h"

/************************************************************************/
/*                                          LinkedList definition                                                                   */
/************************************************************************/
typedef struct Tag_LinkedEntry 
{
    OBJECT              value;
    UINT                   valueType;
    struct Tag_LinkedEntry   *previous;
    struct Tag_LinkedEntry   *next;
}T_LinkedEntry, *LinkedEntry;

typedef struct  Tag_LinkedList 
{
        ULONG                     size;     /* current LinkedList size. */
        LinkedEntry                header;
        
        /************************************************************************/
        /*                                              LinkedList methods                                                                */
        /************************************************************************/
        /**
         * Test LinkedList is empty or not.
         * @param list -- The LinkedList create by newLinkedList function.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    (*isEmpty)(struct Tag_LinkedList* list);
        /**
         * Get LinkedList's size.
         * @param list -- The LinkedList create by newLinkedList function.
         * @return    size of LinkedList.
         */
        UINT     (*getSize)(struct Tag_LinkedList* list);
        /**
         * Get LinkedList's capacity.
         * @param list -- The LinkedList create by newLinkedList function.
         * @return    size of LinkedList.
         */
        UINT     (*getCapacity)(struct Tag_LinkedList* list);
        /**
         * Add string to the LinkedList.
         * @param list -- The LinkedList create by newLinkedList function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addString)(struct Tag_LinkedList* list,  const CHAR* value);
        /**
         * Add char to the LinkedList.
         * @param list -- The LinkedList create by newLinkedList function.
         * @param value -- key value, BYTE type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addByte)(struct Tag_LinkedList* list,  const BYTE value);
        /**
         * Add char to the LinkedList.
         * @param list -- The LinkedList create by newLinkedList function.
         * @param value -- key value, char type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addChar)(struct Tag_LinkedList* list,  const CHAR value);
         /**
         * Add int to the LinkedList.
         * @param list -- The LinkedList create by newLinkedList function.
         * @param value -- key value, SHORT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addShort)(struct Tag_LinkedList* list,  const SHORT value);
        /**
         * Add int to the LinkedList.
         * @param list -- The LinkedList create by newLinkedList function.
         * @param value -- key value, INT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addInt)(struct Tag_LinkedList* list,  const INT value);
         /**
         * Add int to the LinkedList.
         * @param list -- The LinkedList create by newLinkedList function.
         * @param value -- key value, UINT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addUint)(struct Tag_LinkedList* list,  const UINT value);
        /**
         * Add int to the LinkedList.
         * @param list -- The LinkedList create by newLinkedList function.
         * @param value -- key value, LONG type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addLong)(struct Tag_LinkedList* list,  const LONG value);
        /**
         * Add int to the LinkedList.
         * @param list -- The LinkedList create by newLinkedList function.
         * @param value -- key value, ULONG type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addUlong)(struct Tag_LinkedList* list,  const ULONG value);
        /**
         * Add string to the LinkedList.
         * @param list -- The LinkedList create by newLinkedList function.
         * @param value -- key value, float type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addFloat)(struct Tag_LinkedList* list,  const FLOAT value);
        /**
         * Add double to the LinkedList.
         * @param list -- The LinkedList create by newLinkedList function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addDouble)(struct Tag_LinkedList* list,  const DOUBLE value);
        /**
         * Add Object pointer to the LinkedList.
         * @param list -- The LinkedList create by newLinkedList function.
         * @param value -- key value, void* type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addObject)(struct Tag_LinkedList* list,  const OBJECT value);


        UINT    (*add)(struct Tag_LinkedList* list, OBJECT value, UINT valueType);


        UINT    (*addFirst)(struct Tag_LinkedList* list, OBJECT value, UINT valueType);


        UINT    (*addLast)(struct Tag_LinkedList* list, OBJECT value, UINT valueType);


        OBJECT    (*getFirst)(struct Tag_LinkedList* list);


        OBJECT    (*getLast)(struct Tag_LinkedList* list);

        /**
         * get value from LinkedList by hash key.
         * @param list -- The LinkedList create by newLinkedList function.
         * @param key -- hash key, need string type.
         * @return    void type value, should cast the value type when used.
         */
        OBJECT (*get)(struct Tag_LinkedList* list, UINT index);
        /**
         * remove value from LinkedList by hash key.
         * @param list -- The LinkedList create by newLinkedList function.
         * @param key -- hash key, need string type.
         * @return    void type value, should cast the value type when used.The return value should free by invoker.
         */
        OBJECT (*removeByIndex)(struct Tag_LinkedList* list, UINT index);
        /**
         * remove value from LinkedList by hash key.
         * @param list -- The LinkedList create by newLinkedList function.
         * @param key -- hash key, need string type.
         * @return    void type value, should cast the value type when used.The return value should free by invoker.
         */
        OBJECT  (*remove)(struct Tag_LinkedList* list, OBJECT value, UINT valueType);

        OBJECT    (*removeFirst)(struct Tag_LinkedList* list);

        OBJECT    (*removeLast)(struct Tag_LinkedList* list);

        LONG      (*indexOf)(struct Tag_LinkedList* list, OBJECT value, UINT valueType);

        LONG      (*lastIndexOf)(struct Tag_LinkedList* list, OBJECT value, UINT valueType);

        UINT         (*contains)(struct Tag_LinkedList* list, OBJECT value, UINT valueType);

        UINT         (*clear)(struct Tag_LinkedList* list);

        UINT           (*addByIndex)(struct Tag_LinkedList* list, OBJECT value, UINT valueType, UINT index);

        OBJECT      (*setByIndex)(struct Tag_LinkedList* list, OBJECT value, UINT valueType, UINT index);

        OBJECT      (*peek)(struct Tag_LinkedList* list);

        struct Tag_LinkedList*      (*clone)(struct Tag_LinkedList* list);

        VOID          (*print)(struct Tag_LinkedList* list);

}T_LinkedList, *LinkedList;




/************************************************************************/
/*                                                                  Prototypes                                                         */
/************************************************************************/
/**
 * Create LinkedList and init the capacity.
 * @param capacity -- The initial LinkedList capacity.
 * @param factor -- The initial LinkedList factor, used to dynamic expand the LinkedList.
 * @return   LinkedList initial by capacity and factor. NULL if create failed.
 */
LinkedList	newLinkedList();

/**
 * Free LinkedList memory.
 * @param list -- The LinkedList create by newLinkedList function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
UINT     deleteLinkedList(LinkedList list);


#endif /* __LINKEDLIST_H__ */

