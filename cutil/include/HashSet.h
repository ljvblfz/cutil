#ifndef __HASHSET_H__
#define __HASHSET_H__


/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include     "CUtil.h"
#include     "HashMap.h"


/************************************************************************/
/*                                          HashSet definition                                                                         */
/************************************************************************/
typedef struct  Tag_HashSet {
        HashMap          map;       /* HashSet container, used HashMap */
        
        /************************************************************************/
        /*                                              HashSet methods                                                                      */
        /************************************************************************/
        /**
         * Test HashSet is empty or not.
         * @param set -- The HashSet create by newQueue function.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    (*isEmpty)(struct Tag_HashSet* set);
        /**
         * Get HashSet's size.
         * @param set -- The HashSet create by newQueue function.
         * @return    size of HashSet.
         */
        UINT     (*getSize)(struct Tag_HashSet* set);
        /**
         * Add string to the HashSet.
         * @param set -- The HashSet create by newQueue function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addString)(struct Tag_HashSet* set, CHAR* key,  CHAR* value);
        /**
         * Add char to the HashSet.
         * @param set -- The HashSet create by newQueue function.
         * @param value -- key value, char type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addChar)(struct Tag_HashSet* set,  CHAR* key, CHAR value);
        /**
         * Add char to the HashSet.
         * @param set -- The HashSet create by newQueue function.
         * @param value -- key value, BYTE type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addByte)(struct Tag_HashSet* set,  CHAR* key, BYTE value);
        /**
         * Add char to the HashSet.
         * @param set -- The HashSet create by newQueue function.
         * @param value -- key value, SHORT type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addShort)(struct Tag_HashSet* set,  CHAR* key, SHORT value);
        /**
         * Add int to the HashSet.
         * @param set -- The HashSet create by newQueue function.
         * @param value -- key value, INT type.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    ( *addInt)(struct Tag_HashSet* set,  CHAR* key, INT value);
        /**
         * Add int to the HashSet.
         * @param set -- The HashSet create by newQueue function.
         * @param value -- key value, UINT type.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    ( *addUint)(struct Tag_HashSet* set,  CHAR* key, UINT value);
        /**
         * Add int to the HashSet.
         * @param set -- The HashSet create by newQueue function.
         * @param value -- key value, LONG type.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    ( *addLong)(struct Tag_HashSet* set,  CHAR* key, LONG value);
        /**
         * Add int to the HashSet.
         * @param set -- The HashSet create by newQueue function.
         * @param value -- key value, ULONG type.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    ( *addUlong)(struct Tag_HashSet* set,  CHAR* key, ULONG value);
        /**
         * Add string to the HashSet.
         * @param set -- The HashSet create by newQueue function.
         * @param value -- key value, float type.
         * @return    CUTILSUCCESS / CUTILFAILED.
         */
        UINT    ( *addFloat)(struct Tag_HashSet* set,  CHAR* key, FLOAT value);
        /**
         * Add double to the HashSet.
         * @param set -- The HashSet create by newQueue function.
         * @param value -- key value, char* type / string.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addDouble)(struct Tag_HashSet* set,  CHAR* key, DOUBLE value);
        /**
         * Add Object pointer to the HashSet.
         * @param set -- The HashSet create by newQueue function.
         * @param value -- key value, void* type.
         * @return    CUTILSUCCESS / CUTILFAILED..
         */
        UINT    ( *addObject)(struct Tag_HashSet* set,  CHAR* key, OBJECT value);
        /**
         * get value from HashSet by hash key.
         * @param set -- The HashMap create by newHashSet function.
         * @param key -- hash key, need string type.
         * @return    void type value, should cast the value type when used.
         */
       OBJECT (*get)(struct Tag_HashSet* set, const CHAR* key);

       UINT    (*contains)(struct Tag_HashSet* set, const CHAR* key);

       VOID*    (*remove)(struct Tag_HashSet* set, const CHAR* key);

       UINT    (*clear)(struct Tag_HashSet* set);

}T_HashSet, *HashSet;




/************************************************************************/
/*                                                                  Prototypes                                                         */
/************************************************************************/
/**
 * Create a new, empty HashSet and init the capacity.
 * @param initCapacity -- The initial HashSet capacity.
 * @return   HashSet initial by capacity. NULL if create failed.
 */
HashSet	newHashSet(UINT initCapacity, FLOAT loadFactor);

/**
 * Free HashSet memory.
 * @param set -- The HashSet create by newHashSet function.
 * @return    CUTILFAILED / CUTILSUCCESS.
 */
UINT     deleteHashSet(HashSet set);


#endif /* __HASHSET_H__ */

