/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include    "HashSet.h"


/************************************************************************/
/*                                                       HashSet methods implement                                             */
/************************************************************************/

/**
 * Test HashSet is empty or not.
 * @param set -- The HashSet create by newHashSet function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
static UINT    HashSet_isEmpty(HashSet set)
{
        if (set==NULL || set->map==NULL)
                return CUTILFAILED;

        return (set->map->size  ==  0) ? CUTILSUCCESS : CUTILFAILED;
}

/**
 * Get HashSet's size.
 * @param set -- The HashSet create by newHashSet function.
 * @return    size of HashSet.
 */
static UINT    HashSet_getSize(HashSet set)
{
        if ((set!=NULL) && (set->map!=NULL))
                return set->map->size;
        else
                return CUTILFAILED;
}

static UINT    HashSet_contains(HashSet set, const CHAR* key)
{
    if (set==NULL || set->map==NULL || key==NULL)
    {
        return CUTILFAILED;
    }

    return set->map->contains(set->map, key);
}

/**
 * Add string to the HashSet.
 * @param set -- The HashSet create by newHashSet function.
 * @param value -- key value, char* type / string.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT HashSet_addString(HashSet set, CHAR* key, CHAR* value)
{
    /* If the key exist, return failed.  */
    if (HashSet_contains(set, key) ==CUTILSUCCESS)
    {
        return CUTILFAILED;
    }
    return set->map->putString(set->map, key, value);
}

/**
 * Add char to the HashSet.
 * @param set -- The HashSet create by newHashSet function.
 * @param value -- key value, char type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT HashSet_addChar(HashSet set, CHAR* key, CHAR value)
{
    /* If the key exist, return failed.  */
    if (HashSet_contains(set, key) ==CUTILSUCCESS)
    {
        return CUTILFAILED;
    }
    return set->map->putChar(set->map, key, value);
}

/**
 * Add char to the HashSet.
 * @param set -- The HashSet create by newHashSet function.
 * @param value -- key value, BYTE type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT HashSet_addByte(HashSet set, CHAR* key, BYTE value)
{
    /* If the key exist, return failed.  */
    if (HashSet_contains(set, key) ==CUTILSUCCESS)
    {
        return CUTILFAILED;
    }
    return set->map->putByte(set->map, key, value);
}

/**
 * Add char to the HashSet.
 * @param set -- The HashSet create by newHashSet function.
 * @param value -- key value, SHORT type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT HashSet_addShort(HashSet set, CHAR* key, SHORT value)
{
    /* If the key exist, return failed.  */
    if (HashSet_contains(set, key) ==CUTILSUCCESS)
    {
        return CUTILFAILED;
    }
    return set->map->putShort(set->map, key, value);
}

/**
 * Add int to the HashSet.
 * @param set -- The HashSet create by newHashSet function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT HashSet_addInt(HashSet set, CHAR* key, INT value)
{
    /* If the key exist, return failed.  */
    if (HashSet_contains(set, key) ==CUTILSUCCESS)
    {
        return CUTILFAILED;
    }
    return set->map->putInt(set->map, key, value);
}

/**
 * Add int to the HashSet.
 * @param set -- The HashSet create by newHashSet function.
 * @param value -- key value, UINT type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT HashSet_addUint(HashSet set, CHAR* key, UINT value)
{
    /* If the key exist, return failed.  */
    if (HashSet_contains(set, key) ==CUTILSUCCESS)
    {
        return CUTILFAILED;
    }
    return set->map->putUint(set->map, key, value);
}

/**
 * Add int to the HashSet.
 * @param set -- The HashSet create by newHashSet function.
 * @param value -- key value, LONG type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT HashSet_addLong(HashSet set, CHAR* key, LONG value)
{
    /* If the key exist, return failed.  */
    if (HashSet_contains(set, key) ==CUTILSUCCESS)
    {
        return CUTILFAILED;
    }
    return set->map->putLong(set->map, key, value);
}

/**
 * Add int to the HashSet.
 * @param set -- The HashSet create by newHashSet function.
 * @param value -- key value, ULONG type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT HashSet_addUlong(HashSet set, CHAR* key, ULONG value)
{
    /* If the key exist, return failed.  */
    if (HashSet_contains(set, key) ==CUTILSUCCESS)
    {
        return CUTILFAILED;
    }
    return set->map->putUlong(set->map, key, value);
}

/**
 * Add string to the HashSet.
 * @param set -- The HashSet create by newHashSet function.
 * @param value -- key value, float type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT HashSet_addFloat(HashSet set, CHAR* key, FLOAT value)
{
    /* If the key exist, return failed.  */
    if (HashSet_contains(set, key) ==CUTILSUCCESS)
    {
        return CUTILFAILED;
    }
    return set->map->putFloat(set->map, key, value);
}

/**
 * Add double to the HashSet.
 * @param set -- The HashSet create by newHashSet function.
 * @param value -- key value, char* type / string.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT HashSet_addDouble(HashSet set, CHAR* key, DOUBLE value)
{
    /* If the key exist, return failed.  */
    if (HashSet_contains(set, key) ==CUTILSUCCESS)
    {
        return CUTILFAILED;
    }
    return set->map->putDouble(set->map, key, value);
}

/**
 * Add Object pointer to the HashSet.
 * @param set -- The HashSet create by newHashSet function.
 * @param value -- key value, void* type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT HashSet_addObject(HashSet set, CHAR* key, const OBJECT value)
{
    /* If the key exist, return failed.  */
    if (HashSet_contains(set, key) ==CUTILSUCCESS)
    {
        return CUTILFAILED;
    }
    return set->map->putObject(set->map, key, value);
}

static OBJECT HashSet_get(HashSet set, const CHAR* key)
{
    if (set==NULL || set->map==NULL || key==NULL)
    {
        return CUTILFAILED;
    }
    return set->map->get(set->map, key);
}

static VOID* HashSet_remove(HashSet set, const CHAR* key)
{
    if (set==NULL || set->map==NULL || key==NULL)
    {
        return NULL;
    }
    return set->map->remove(set->map, key);
}


static UINT    HashSet_clear(HashSet set)
{
    if (set==NULL || set->map==NULL)
    {
        return CUTILFAILED;
    }

    return set->map->clear(set->map);
}

/************************************************************************/
/*                                                HashSet    Prototypes                                                         */
/************************************************************************/
/**
 * Create HashSet and init the capacity.
 * @param capacity -- The initial HashSet capacity.
 * @return   HashSet initial by capacity. NULL if create failed.
 */
HashSet	newHashSet(UINT initCapacity, FLOAT loadFactor)
{
        HashSet set = NULL;
        HashMap map = NULL;

        /* initial HashSet */
        set = (HashSet) balloc(sizeof(T_HashSet));
        if (set == NULL)
        {
                return NULL;
        }
		memset(set, 0, sizeof(T_HashSet));   

        /* initial ArrayList */
        map = newHashMap(initCapacity, loadFactor);
        if (map == NULL)
        {
            bfree(set);
            return NULL;
        }
        set->map = map;

        /** initial HashSet function **/
        set->isEmpty = HashSet_isEmpty;
        set->getSize = HashSet_getSize;

        set->addChar = HashSet_addChar;
        set->addByte = HashSet_addByte;
        set->addShort = HashSet_addShort;
        set->addString = HashSet_addString;
        set->addInt = HashSet_addInt;
        set->addUint = HashSet_addUint;
        set->addLong = HashSet_addLong;
        set->addUlong = HashSet_addUlong;
        set->addFloat = HashSet_addFloat;
        set->addDouble = HashSet_addDouble;
        set->addObject = HashSet_addObject;

        set->get = HashSet_get;
        set->remove = HashSet_remove;
        set->contains = HashSet_contains;
        set->clear = HashSet_clear;

        return set;
}

/**
 * Free HashSet memory.
 * @param set -- The HashSet create by newHashSet function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
UINT    deleteHashSet(HashSet set)
{
        if (set == NULL)
                return CUTILFAILED;

         if (set->map != NULL)
         {
            deleteHashMap(set->map);
         }
       
        bfree(set);
        return CUTILSUCCESS;
}

