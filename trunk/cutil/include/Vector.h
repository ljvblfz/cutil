#ifndef __VECTOR_H__
#define __VECTOR_H__


/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include     "CUtil.h"
#include     "Lock.h"

/************************************************************************/
/*                                          Vector definition                                                                     */
/************************************************************************/
typedef struct Tag_VectorEntry{
    UINT           valueType;
    OBJECT      value;
}T_VectorEntry, *VectorEntry;

typedef struct  Tag_Vector {
        ULONG               capacity;     /* capacity of hash buckets */
        ULONG               size;     /* current Vector size. */
        VectorEntry           *table;  /* Vector table */
        Lock                    lock;     /* Vector lock */
        
        /************************************************************************/
        /*                                              Vector methods                                                                  */
        /************************************************************************/
        /**
         * Test Vector is empty or not.
         * @param list -- The Vector create by newVector function.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    (*isEmpty)(struct Tag_Vector* list);
        /**
         * Get Vector's size.
         * @param list -- The Vector create by newVector function.
         * @return    size of Vector.
         */
        UINT     (*getSize)(struct Tag_Vector* list);
        /**
         * Get Vector's capacity.
         * @param list -- The Vector create by newVector function.
         * @return    size of Vector.
         */
        UINT     (*getCapacity)(struct Tag_Vector* list);
        /**
         * Add string to the Vector.
         * @param list -- The Vector create by newVector function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT      (*add)(struct Tag_Vector* list, OBJECT value, UINT valueType);
        /**
         * Add string to the Vector.
         * @param list -- The Vector create by newVector function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addString)(struct Tag_Vector* list,  CHAR* value);
        /**
         * Add char to the Vector.
         * @param list -- The Vector create by newVector function.
         * @param value -- key value, BYTE type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addByte)(struct Tag_Vector* list,  const BYTE value);
        /**
         * Add char to the Vector.
         * @param list -- The Vector create by newVector function.
         * @param value -- key value, char type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addChar)(struct Tag_Vector* list,  const CHAR value);
         /**
         * Add int to the Vector.
         * @param list -- The Vector create by newVector function.
         * @param value -- key value, SHORT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addShort)(struct Tag_Vector* list,  const SHORT value);
        /**
         * Add int to the Vector.
         * @param list -- The Vector create by newVector function.
         * @param value -- key value, INT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addInt)(struct Tag_Vector* list,  const INT value);
         /**
         * Add int to the Vector.
         * @param list -- The Vector create by newVector function.
         * @param value -- key value, UINT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addUint)(struct Tag_Vector* list,  const UINT value);
        /**
         * Add int to the Vector.
         * @param list -- The Vector create by newVector function.
         * @param value -- key value, LONG type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addLong)(struct Tag_Vector* list,  const LONG value);
        /**
         * Add int to the Vector.
         * @param list -- The Vector create by newVector function.
         * @param value -- key value, ULONG type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addUlong)(struct Tag_Vector* list,  const ULONG value);
        /**
         * Add string to the Vector.
         * @param list -- The Vector create by newVector function.
         * @param value -- key value, float type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addFloat)(struct Tag_Vector* list,  const FLOAT value);
        /**
         * Add double to the Vector.
         * @param list -- The Vector create by newVector function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addDouble)(struct Tag_Vector* list,  const DOUBLE value);
        /**
         * Add Object pointer to the Vector.
         * @param list -- The Vector create by newVector function.
         * @param value -- key value, void* type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addObject)(struct Tag_Vector* list,  const OBJECT value);
        /**
         * get value from Vector by hash key.
         * @param list -- The Vector create by newVector function.
         * @param key -- hash key, need string type.
         * @return    void type value, should cast the value type when used.
         */
        OBJECT (*get)(struct Tag_Vector* list, UINT index);
        /**
         * remove value from Vector by hash key.
         * @param list -- The Vector create by newVector function.
         * @param key -- hash key, need string type.
         * @return    void type value, should cast the value type when used.The return value should free by invoker.
         */
        OBJECT (*remove)(struct Tag_Vector* list, UINT index);


        int    (*indexOf)(struct Tag_Vector* list, OBJECT value, UINT valueType);

        int    (*lastIndexOf)(struct Tag_Vector* list, OBJECT value, UINT valueType);

        UINT      (*contains)(struct Tag_Vector* list, OBJECT value, UINT valueType);

        OBJECT  (*setByIndex)(struct Tag_Vector* list, UINT index, OBJECT value, UINT valueType );

        UINT  (*insert)(struct Tag_Vector* list, UINT index, OBJECT value, UINT valueType );

        struct Tag_Vector* (*clone)(struct Tag_Vector* list);

        VOID      (*print)(struct Tag_Vector* list);

        UINT       (*clear)(struct Tag_Vector* list);

}T_Vector, *Vector;




/************************************************************************/
/*                                                                  Prototypes                                                         */
/************************************************************************/
/**
 * Create Vector and init the capacity.
 * @param capacity -- The initial Vector capacity.
 * @param factor -- The initial Vector factor, used to dynamic expand the Vector.
 * @return   Vector initial by capacity and factor. NULL if create failed.
 */
Vector	newVector(UINT capacity);

/**
 * Free Vector memory.
 * @param list -- The Vector create by newVector function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
UINT     deleteVector(Vector list);


#endif /* __VECTOR_H__ */
