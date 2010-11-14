#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__


/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include     "CUtil.h"

/************************************************************************/
/*                                          ArrayList definition                                                                     */
/************************************************************************/
typedef struct Tag_ArrayEntry{
    UINT           valueType;
    OBJECT      value;
}T_ArrayEntry, *ArrayEntry;

typedef struct  Tag_ArrayList {
        ULONG               capacity;     /* capacity of hash buckets */
        ULONG               size;     /* current ArrayList size. */
        ArrayEntry        *table;  /* ArrayList table */
        
        /************************************************************************/
        /*                                              ArrayList methods                                                                  */
        /************************************************************************/
        /**
         * Test ArrayList is empty or not.
         * @param list -- The ArrayList create by newArrayList function.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    (*isEmpty)(struct Tag_ArrayList* list);
        /**
         * Get ArrayList's size.
         * @param list -- The ArrayList create by newArrayList function.
         * @return    size of ArrayList.
         */
        UINT     (*getSize)(struct Tag_ArrayList* list);
        /**
         * Get ArrayList's capacity.
         * @param list -- The ArrayList create by newArrayList function.
         * @return    size of ArrayList.
         */
        UINT     (*getCapacity)(struct Tag_ArrayList* list);
        /**
         * Add string to the ArrayList.
         * @param list -- The ArrayList create by newArrayList function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT      (*add)(struct Tag_ArrayList* list, OBJECT value, UINT valueType);
        /**
         * Add string to the ArrayList.
         * @param list -- The ArrayList create by newArrayList function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addString)(struct Tag_ArrayList* list,  CHAR* value);
        /**
         * Add char to the ArrayList.
         * @param list -- The ArrayList create by newArrayList function.
         * @param value -- key value, BYTE type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addByte)(struct Tag_ArrayList* list,  const BYTE value);
        /**
         * Add char to the ArrayList.
         * @param list -- The ArrayList create by newArrayList function.
         * @param value -- key value, char type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addChar)(struct Tag_ArrayList* list,  const CHAR value);
         /**
         * Add int to the ArrayList.
         * @param list -- The ArrayList create by newArrayList function.
         * @param value -- key value, SHORT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addShort)(struct Tag_ArrayList* list,  const SHORT value);
        /**
         * Add int to the ArrayList.
         * @param list -- The ArrayList create by newArrayList function.
         * @param value -- key value, INT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addInt)(struct Tag_ArrayList* list,  const INT value);
         /**
         * Add int to the ArrayList.
         * @param list -- The ArrayList create by newArrayList function.
         * @param value -- key value, UINT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addUint)(struct Tag_ArrayList* list,  const UINT value);
        /**
         * Add int to the ArrayList.
         * @param list -- The ArrayList create by newArrayList function.
         * @param value -- key value, LONG type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addLong)(struct Tag_ArrayList* list,  const LONG value);
        /**
         * Add int to the ArrayList.
         * @param list -- The ArrayList create by newArrayList function.
         * @param value -- key value, ULONG type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addUlong)(struct Tag_ArrayList* list,  const ULONG value);
        /**
         * Add string to the ArrayList.
         * @param list -- The ArrayList create by newArrayList function.
         * @param value -- key value, float type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addFloat)(struct Tag_ArrayList* list,  const FLOAT value);
        /**
         * Add double to the ArrayList.
         * @param list -- The ArrayList create by newArrayList function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addDouble)(struct Tag_ArrayList* list,  const DOUBLE value);
        /**
         * Add Object pointer to the ArrayList.
         * @param list -- The ArrayList create by newArrayList function.
         * @param value -- key value, void* type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addObject)(struct Tag_ArrayList* list,  const OBJECT value);
        /**
         * get value from ArrayList by hash key.
         * @param list -- The ArrayList create by newArrayList function.
         * @param key -- hash key, need string type.
         * @return    void type value, should cast the value type when used.
         */
        OBJECT (*get)(struct Tag_ArrayList* list, UINT index);
        /**
         * remove value from ArrayList by hash key.
         * @param list -- The ArrayList create by newArrayList function.
         * @param key -- hash key, need string type.
         * @return    void type value, should cast the value type when used.The return value should free by invoker.
         */
        OBJECT (*remove)(struct Tag_ArrayList* list, UINT index);


        int    (*indexOf)(struct Tag_ArrayList* list, OBJECT value, UINT valueType);

        int    (*lastIndexOf)(struct Tag_ArrayList* list, OBJECT value, UINT valueType);

        UINT      (*contains)(struct Tag_ArrayList* list, OBJECT value, UINT valueType);

        OBJECT  (*setByIndex)(struct Tag_ArrayList* list, UINT index, OBJECT value, UINT valueType );

        UINT  (*insert)(struct Tag_ArrayList* list, UINT index, OBJECT value, UINT valueType );

        struct Tag_ArrayList* (*clone)(struct Tag_ArrayList* list);

        VOID      (*print)(struct Tag_ArrayList* list);

        UINT       (*clear)(struct Tag_ArrayList* list);

}T_ArrayList, *ArrayList;




/************************************************************************/
/*                                                                  Prototypes                                                         */
/************************************************************************/
/**
 * Create ArrayList and init the capacity.
 * @param capacity -- The initial ArrayList capacity.
 * @param factor -- The initial ArrayList factor, used to dynamic expand the ArrayList.
 * @return   ArrayList initial by capacity and factor. NULL if create failed.
 */
ArrayList	newArrayList(UINT capacity);

/**
 * Free ArrayList memory.
 * @param list -- The ArrayList create by newArrayList function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
UINT     deleteArrayList(ArrayList list);


#endif /* __ARRAYLIST_H__ */
