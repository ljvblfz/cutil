/*
 * Copyright (c) International Business Machines Corp., 2006
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
 * the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Author: Eric Wang
 * Update: 2010-06-07
 */
/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include    "HashMap.h"


/************************************************************************/
/*                                                         Constant                                                                     */
/************************************************************************/
static    LONG      DEFAULT_CAPACITY = 16;    /* The default initial capacity - Must be a power of 2. */
static    FLOAT     DEFAULT_FACTOR =  0.75f ;   /* The default load factor. */

#define MAXIMUM_CAPACITY   1<<30  /* The default maximum capacity. */

/************************************************************************/
/*                                                              HashEntry methods                                                 */
/************************************************************************/

/**
 * Create new hash entry, use void type key and value.
 * Allocate memory for key. The value should allocate memory by invoker.
 */
static HashEntry newHashEntry(CHAR* key, OBJECT value, const UINT valueType)
{
    HashEntry entry = NULL;
    OBJECT          obj = NULL;
    UINT       len = 0;

    /* In the HashMap value can be NULL. */
    if (key==NULL)
    {
        return NULL;
    }

    switch(valueType)
    {
    case TYPE_BYTE:
        {
            obj = (OBJECT)balloc(sizeof(BYTE));
            if (obj == NULL)
            {
                return NULL;
            }
            memset(obj, 0, sizeof(BYTE));
            memcpy(obj, value, sizeof(BYTE));
            break;
        }
    case TYPE_CHAR:
        {
            obj = (OBJECT)balloc(sizeof(CHAR));
            if (obj == NULL)
            {
                return NULL;
            }
            memset(obj, 0, sizeof(CHAR));
            memcpy(obj, value, sizeof(CHAR));
            break;
        }
    case TYPE_SHORT:
        {
            obj = (OBJECT)balloc(sizeof(SHORT));
            if (obj == NULL)
            {
                return NULL;
            }
            memset(obj, 0, sizeof(SHORT));
            memcpy(obj, value, sizeof(SHORT));
            break;
        }
    case TYPE_INT:
        {
            obj = (OBJECT)balloc(sizeof(INT));
            if (obj == NULL)
            {
                return NULL;
            }
            memset(obj, 0, sizeof(INT));
            memcpy(obj, value, sizeof(INT));
            break;
        }
    case TYPE_UINT:
        {
            obj = (OBJECT)balloc(sizeof(UINT));
            if (obj == NULL)
            {
                return NULL;
            }
            memset(obj, 0, sizeof(UINT));
            memcpy(obj, value, sizeof(UINT));
            break;
        }
    case TYPE_LONG:
        {
            obj = (OBJECT)balloc(sizeof(LONG));
            if (obj == NULL)
            {
                return NULL;
            }
            memset(obj, 0, sizeof(LONG));
            memcpy(obj, value, sizeof(LONG));
            break;
        }
    case TYPE_ULONG:
        {
            obj = (OBJECT)balloc(sizeof(ULONG));
            if (obj == NULL)
            {
                return NULL;
            }
            memset(obj, 0, sizeof(ULONG));
            memcpy(obj, value, sizeof(ULONG));
            break;
        }
    case TYPE_FLOAT:
        {
            obj = (OBJECT)balloc(sizeof(FLOAT));
            if (obj == NULL)
            {
                return NULL;
            }
            memset(obj, 0, sizeof(FLOAT));
            memcpy(obj, value, sizeof(FLOAT));
            break;
        }
    case TYPE_DOUBLE:
        {
            obj = (OBJECT)balloc(sizeof(DOUBLE));
            if (obj == NULL)
            {
                return NULL;
            }
            memset(obj, 0, sizeof(DOUBLE));
            memcpy(obj, value, sizeof(DOUBLE));
            break;
        }
    case TYPE_STRING:
        {
            len = strlen((CHAR *)value);

            obj = (OBJECT)balloc(sizeof(CHAR) * (len +1));
            if (obj == NULL)
            {
                return NULL;
            }
            memset(obj, 0, sizeof(CHAR) * (len +1));
            memcpy(obj, value, sizeof(CHAR)*len);
            break;
        }
    case TYPE_OBJECT:
        {
            obj = (OBJECT)balloc(sizeof(OBJECT));
            if (obj == NULL)
            {
                return NULL;
            }
            memset(obj, 0, sizeof(OBJECT));
            memcpy(obj, &value, sizeof(OBJECT));
            break;
        }
    }

    entry = (HashEntry)balloc(sizeof(T_HashEntry));
    if (entry == NULL)
    {
        if (obj != NULL)
        {
            bfree(obj);
        }
        return NULL;
    }
    memset(entry, 0, sizeof(T_HashEntry));

    len = strlen(key);
    entry->key = (CHAR *)balloc(sizeof(CHAR) * (len+1));
    if (entry->key == NULL)
    {
        return NULL;
    }
    memset(entry->key, 0, sizeof(CHAR) * (len+1));
    memcpy(entry->key, key, sizeof(CHAR) * len);

    entry->value = obj;
    entry->valueType = valueType;
    entry->next = NULL;

    return entry;
}

static OBJECT  getHashEntryObjectValue(HashEntry entry)
{
    WORD32       ptValue = 0;   /* the real object value, must 32 bit unsigned int. If int not support 32 bit, use Long instead. */
    OBJECT  value = NULL;
    if (entry == NULL)
    {
        return NULL;
    }

    value = entry->value;
    memcpy(&ptValue, value, sizeof(OBJECT));
    value = (OBJECT)ptValue;
    return value;
}


/************************************************************************/
/*                                                              HashMap methods                                                 */
/************************************************************************/

/**
 * hash code generate function.
 * Private function.
 * Applies a supplemental hash function to a given hashCode, which defends against poor quality hash functions.  
 * This is critical because HashMap uses power-of-two length hash tables, 
 that otherwise encounter collisions for hashCodes that do not differ in lower bits. 
 * Note: Null keys always map to hash 0, thus index 0.
 * @param      str      HashMap key.
 * @param      mapsize      HashMap capacity.
 * @return       hash code.
 */
static LONG    hashCode(const CHAR* key){
        LONG     hash = 0;
        LONG     x    = 0;
        UINT     i    = 0;
        UINT     len  = strlen(key);

        for(i = 0; i < len; key++, i++) {
                hash = (hash << 4) + (*key);
                if((x = hash & 0xF0000000L) != 0) {
                        hash ^= (x >> 24);
                        hash &= ~x;
                }
        }
        hash =  hash & 0x7FFFFFFF;

        hash ^= (hash>>20) ^ (hash >>12);
        return hash ^ (hash>>7) ^ (hash>>4);
}

/**
 * Returns index for hash code h.
 */
static LONG indexFor(LONG h, LONG length)
{
    return h & (length-1);
}


/**
 * Add a key-value to the HashMap. If the key is available in the HashMap, update the old value.
 * map is not NULL, ensure by invoker.
 * @param map -- The HashMap create by HashMap_new function.
 * @param key -- hash key, need string type.
 * @param value -- key value, void type.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
static UINT    HashMap_put(HashMap map, CHAR* key, OBJECT value, UINT valueType)
{
        LONG     hash = 0;
        LONG     index = 0;                  /* old HashMap capacity retrieve */
        LONG     newCapacity = 0;
        LONG     i = 0;
        LONG     oldCapacity = 0;

        HashEntry entry = NULL;
        HashEntry next = NULL;
        HashEntry*  newTable = NULL;
        HashEntry* oldTable = NULL;

        hash = hashCode(key);
        index = indexFor(hash, map->capacity);
        /* 1.  If the key exist, update it. */
        for(entry=map->table[index]; entry!=NULL; entry=entry->next)
        {
            if (0==strcmp(key, entry->key))
            {
                /* free the old value and set the new value to entry->value. */
                if (entry->value != NULL)
                {
                    bfree(entry->value);
                    entry->value = NULL;
                }
                entry->value = value;
                entry->valueType = valueType;
                printf("Update the value for key : %s\n", key);
                return CUTILSUCCESS;
            }
        }

        /* 2.  If the key not exist, create HashEntry and add to the HashMap */
        entry = map->table[index];

        map->table[index] = newHashEntry(key, value, valueType);
        if (map->table[index] == NULL)
        {
            /* Not modify the HashMap and return failed. */
            map->table[index] = entry;
            return CUTILFAILED;
        }
        map->table[index]->next = entry;
        map->size += 1;

        /* 3.  Check the HashMap capacity and  dynamic expend the HashMap*/
        if (map->size >= map->threshold)
        {
            newCapacity = map->capacity * 2;
             /* more than MAXIMUM_CAPACITY, exit */
            if (newCapacity > MAXIMUM_CAPACITY){
                #if (DEBUG && LOGSUPPORT)
                         clog(LOG_ERROR, "Hashmap maximum capacity overflow.\n");
                #endif
                return CUTILFAILED;
            }
            /* Create new table for expend the HashMap */
            newTable = (HashEntry *)balloc(newCapacity * sizeof(HashEntry));
            if (newTable == NULL)
            {
                #if (DEBUG && LOGSUPPORT)
                        clog(LOG_ERROR, "expend new hash table failed.\n");
                #endif
                printf("expend new hash table failed.\n");
                return CUTILFAILED;
            }
            memset(newTable, 0, newCapacity * sizeof(HashEntry));
            /*Keep old table and capacity. */
            oldTable = map->table;
            oldCapacity = map->capacity;
             /*Set new table and capacity to the HashMap. */
            map->table = newTable;
            map->capacity = newCapacity;
            map->threshold = (ULONG)(map->capacity * map->factor);
            /* Transfer old table to new table. */
            for (i=0; i<oldCapacity; i++)
            {
                entry = oldTable[i];
                if (entry != NULL)
                {
                    do 
                    {
                        next = entry->next;
                        index = indexFor(hashCode(entry->key), newCapacity);
                        entry->next = newTable[index];
                        newTable[index] = entry;
                        entry = next;
                    } while (entry != NULL);
                }
            } /*end  for (i=0; i<map->capacity; i++) */
            bfree(oldTable);
            printf("expend new hash table OK. capacity: %ld\n", newCapacity);
        }/*end if (map->size > (UINT)(map->capacity * map->factor)) */

        return CUTILSUCCESS;
}


/*************************  HashMap function implement  ***********************************/
/**
 * Test HashMap is empty or not.
 * @param map -- The HashMap create by newHashMap function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
static UINT    HashMap_isEmpty(HashMap map)
{
        if (map == NULL)
                return CUTILFAILED;

        return (map->size  ==  0) ? CUTILSUCCESS : CUTILFAILED;
}

/**
 * Get HashMap's size.
 * @param map -- The HashMap create by HashMap_new function.
 * @return    size of HashMap.
 */
static UINT    HashMap_getSize(HashMap map)
{
        if (map != NULL)
                return map->size;
        else
                return CUTILFAILED;
}

/**
 * Get HashMap's capacity.
 * @param map -- The HashMap create by newHashMap function.
 * @return    size of HashMap.
 */
static UINT    HashMap_getCapacity(HashMap map)
{
        if (map != NULL)
                return map->capacity;
        else
                return CUTILFAILED;
}

/**
 * Allocate newValue memory and copy value to it. 
 * The key value should allocate and copy in newHashEntry method.
 */

static UINT HashMap_putByte(HashMap map, CHAR* key, BYTE value)
{
    return HashMap_put(map, key, (OBJECT)&value, TYPE_BYTE);
}


static UINT HashMap_putChar(HashMap map, CHAR* key, CHAR value)
{
     return HashMap_put(map, key, (OBJECT)&value, TYPE_CHAR);
}


static UINT HashMap_putShort(HashMap map, CHAR* key, SHORT value)
{
    return HashMap_put(map, key, (OBJECT)&value, TYPE_SHORT);
}


static UINT HashMap_putInt(HashMap map, CHAR* key, INT value)
{
    return HashMap_put(map, key, (OBJECT)&value, TYPE_INT);
}


static UINT HashMap_putUint(HashMap map, CHAR* key, UINT value)
{
     return HashMap_put(map, key, (OBJECT)&value, TYPE_UINT);
}


static UINT HashMap_putLong(HashMap map, CHAR* key, LONG value)
{
     return HashMap_put(map, key, (OBJECT)&value, TYPE_LONG);
}


static UINT HashMap_putUlong(HashMap map, CHAR* key, ULONG value)
{
   return HashMap_put(map, key, (OBJECT)&value, TYPE_ULONG);
}

static UINT HashMap_putFloat(HashMap map, CHAR* key, FLOAT value)
{  
    return HashMap_put(map, key, (OBJECT)&value, TYPE_FLOAT);
}


static UINT HashMap_putDouble(HashMap map, CHAR* key, DOUBLE value)
{
    return HashMap_put(map, key, (OBJECT)&value, TYPE_DOUBLE);
}
/**
 * Allocate newValue memory and copy value to it. 
 * The key value should allocate and copy in newHashEntry method.
 */
static UINT HashMap_putString(HashMap map, CHAR* key, CHAR* value)
{
    return HashMap_put(map, key, (OBJECT)value, TYPE_STRING);
}


static UINT HashMap_putObject(HashMap map, CHAR* key, OBJECT value)
{
   return HashMap_put(map, key, value, TYPE_OBJECT);
}

/**
 * get value from HashMap by hash key.
 * @param map -- The HashMap create by hashmap_new function.
 * @param key -- hash key, need string type.
 * @return    void type value, should cast the value type when used.
 */
static OBJECT  HashMap_get(HashMap map, const CHAR* key)
{
    LONG     hash = 0;
    HashEntry entry = NULL;

    if ((map == NULL) || (map->table==NULL) || (key == NULL))
    {
        return NULL;
    }

      hash = hashCode(key);
      for (entry=map->table[indexFor(hash, map->capacity)]; entry!=NULL; entry=entry->next)
      {
            if (0 == strcmp(entry->key, key))
            {
                if (entry->valueType == TYPE_OBJECT)
                {
                    return getHashEntryObjectValue(entry);
                }
                return entry->value;
            }
      }
      return NULL;
}


static VOID*    HashMap_remove(HashMap map, const CHAR* key)
{
        LONG     hash = 0;
        LONG     index = 0;
        HashEntry prev = NULL;
        HashEntry entry = NULL;
        HashEntry next = NULL;
        VOID*     value = NULL;

        if ((map == NULL) || (map->table==NULL) || (key == NULL))
        {
            return NULL;
        }

        hash = hashCode(key);
        index = indexFor(hash, map->capacity);

        prev = map->table[index];
        entry = prev;
        while (entry != NULL)
        {
            next = entry->next;
            if (0 == strcmp(entry->key, key))
            {
                if (prev == entry) /* match the first HashEntry. */
                {
                    map->table[index] = next;
                }
                else
                {
                    prev->next = next;
                }
                /* delete entry */
                if (entry->key != NULL)
                {
                    bfree(entry->key);
                }
                if (entry->value != NULL)
                {
                    value = entry->value;
                    if (entry->valueType == TYPE_OBJECT)
                    {
                        value = getHashEntryObjectValue(entry);
                        bfree(entry->value); /* free the object pointer  */
                    }
                }
                bfree(entry);

                map->size -= 1;
                return value;
            }/* if (0 == strcmp(entry->key, key)) */
            prev = entry;
            entry = next;
        }/* while (entry != NULL) */

        return NULL;
}


static UINT    HashMap_clear(HashMap map)
{
    ULONG   i = 0;
    HashEntry entry = NULL;
    HashEntry next = NULL;

    if (map==NULL || map->table==NULL)
    {
        return CUTILFAILED;
    }

    for(i = 0; i < map->capacity; i++) 
    {
        entry = map->table[i];
        /* clear map table */
        map->table[i] = NULL;
        /* free entry memory */
        if (entry != NULL)
        {
            do 
            {
                next = entry->next;
                if (entry->key != NULL)
                {
                    bfree(entry->key);
                }
                if (entry->value != NULL)
                {
                    bfree(entry->value);
                }
                bfree(entry);
                entry = next;
            } while (entry != NULL);
        }
    } /* end for */
    return CUTILSUCCESS;
}


UINT    HashMap_contains(HashMap map, const CHAR* key)
{
    HashEntry    entry = NULL;

    if (map==NULL || key==NULL)
    {
        return CUTILFAILED;
    }

    for (entry=map->table[indexFor(hashCode(key), map->capacity)]; entry!=NULL; entry=entry->next)
    {
        if (0 == strcmp(entry->key, key))
        {
            return CUTILSUCCESS;
        }
    }
    return CUTILFAILED;
}

static HashMap HashMap_clone(HashMap map)
{
    HashMap newMap = NULL;
    HashEntry entry = NULL;
    ULONG  index = 0;

    if (map == NULL)
    {
        return NULL;
    }
    newMap = newHashMap(map->capacity, map->factor);
    if (newMap == NULL)
    {
        printf("Clone HashMap error.\n");
        return NULL;
    }

    for (index=0; index<map->capacity; index++)
    {
        entry = map->table[index];
        do 
        {
            if (NULL == entry)
            {
                break;
            }
            newMap->put(newMap, entry->key, entry->value, entry->valueType);

            entry = entry->next;
        } while (entry != NULL);
    } /* end for */
    newMap->size = map->size;
    newMap->threshold = map->threshold;
    return newMap;
}

static VOID   HashMap_printByIndex(HashMap map, ULONG index)
{
    HashEntry entry = NULL;
    HashEntry next = NULL;

    if (map==NULL)
    {
        printf("HashMap is NULL.\n");
        return;
    }
    if (index >= map->capacity )
    {
        printf("Index greater than HashMap's capacity.\n");
        return;
    }

    printf(" -----------   HashEntry   --------------\n");
    entry = map->table[index];
    if (entry != NULL)
    {
        do 
        {
            next = entry->next;
            switch (entry->valueType)
            {
            case TYPE_BYTE:
                printf("Index: %ld  |  Key: %s  |  Value: %d  |  Type: BYTE\n", index, entry->key, *(BYTE *)entry->value);
                break;
            case TYPE_CHAR:
                printf("Index: %ld  |  Key: %s  |  Value: %c  |  Type: CHAR\n", index, entry->key, *(CHAR *)entry->value);
                break;
            case TYPE_SHORT:
                printf("Index: %ld  |  Key: %s  |  Value: %d  |  Type: SHORT\n", index, entry->key, *(SHORT *)entry->value);
                break;
            case TYPE_STRING:
                printf("Index: %ld  |  Key: %s  |  Value: %s  |  Type: STRING\n", index, entry->key, (CHAR *)entry->value);
                break;
            case TYPE_INT:
                printf("Index: %ld  |  Key: %s  |  Value: %d  |  Type: INT\n", index, entry->key, *(INT *)entry->value);
                break;
            case TYPE_UINT:
                printf("Index: %ld  |  Key: %s  |  Value: %d  |  Type: UINT\n", index, entry->key, *(UINT *)entry->value);
                break;
            case TYPE_LONG:
                printf("Index: %ld  |  Key: %s  |  Value: %ld  |  Type: LONG\n", index, entry->key, *(LONG *)entry->value);
                break;
            case TYPE_ULONG:
                printf("Index: %ld  |  Key: %s  |  Value: %ld  |  Type: ULONG\n", index, entry->key, *(ULONG *)entry->value);
                break;
            case TYPE_FLOAT:
                printf("Index: %ld  |  Key: %s  |  Value: %f  |  Type: FLOAT\n", index, entry->key, *(FLOAT *)entry->value);
                break;
            case TYPE_DOUBLE:
                printf("Index: %ld  |  Key: %s  |  Value: %f  |  Type: DOUBLE\n", index, entry->key, *(DOUBLE *)entry->value);
                break;
            case TYPE_OBJECT:
                printf("Index: %ld  |  Key: %s  |  Value: %p  |  Type: OBJECT\n", index, entry->key, getHashEntryObjectValue(entry));
                break;
            default:
                printf("Index: %ld  |  Key: %s  |  Type: UNKNOW\n", index, entry->key);
                break;
            }
            entry = next;
        } while (entry != NULL);
    } /* end if */
}

static VOID   HashMap_print(HashMap map)
{
    ULONG     index = 0;
    HashEntry entry = NULL;
    HashEntry next = NULL;

    if (map==NULL)
    {
        printf("HashMap is NULL.\n");
        return;
    }
    if (index >= map->capacity )
    {
        printf("Index greater than HashMap's capacity.\n");
        return;
    }

    printf("\n\n--------------    HashMap     Size: %ld      Capacity: %ld      --------------\n", map->size, map->capacity);

    for(index = 0; index < map->capacity; index++) 
    {
        entry = map->table[index];
        if (entry != NULL)
        {
            do 
            {
                next = entry->next;
                switch (entry->valueType)
                {
                case TYPE_BYTE:
                    printf("Index: %ld  |  Key: %s  |  Value: %d  |  Type: BYTE\n", index, entry->key, *(BYTE *)entry->value);
                    break;
                case TYPE_CHAR:
                    printf("Index: %ld  |  Key: %s  |  Value: %c  |  Type: CHAR\n", index, entry->key, *(CHAR *)entry->value);
                    break;
                case TYPE_SHORT:
                    printf("Index: %ld  |  Key: %s  |  Value: %d  |  Type: SHORT\n", index, entry->key, *(SHORT *)entry->value);
                    break;
                case TYPE_STRING:
                    printf("Index: %ld  |  Key: %s  |  Value: %s  |  Type: STRING\n", index, entry->key, (CHAR *)entry->value);
                    break;
                case TYPE_INT:
                    printf("Index: %ld  |  Key: %s  |  Value: %d  |  Type: INT\n", index, entry->key, *(INT *)entry->value);
                    break;
                case TYPE_UINT:
                    printf("Index: %ld  |  Key: %s  |  Value: %d  |  Type: UINT\n", index, entry->key, *(UINT *)entry->value);
                    break;
                case TYPE_LONG:
                    printf("Index: %ld  |  Key: %s  |  Value: %ld  |  Type: LONG\n", index, entry->key, *(LONG *)entry->value);
                    break;
                case TYPE_ULONG:
                    printf("Index: %ld  |  Key: %s  |  Value: %ld  |  Type: ULONG\n", index, entry->key, *(ULONG *)entry->value);
                    break;
                case TYPE_FLOAT:
                    printf("Index: %ld  |  Key: %s  |  Value: %f  |  Type: FLOAT\n", index, entry->key, *(FLOAT *)entry->value);
                    break;
                case TYPE_DOUBLE:
                    printf("Index: %ld  |  Key: %s  |  Value: %f  |  Type: DOUBLE\n", index, entry->key, *(DOUBLE *)entry->value);
                    break;
                case TYPE_OBJECT:
                    printf("Index: %ld  |  Key: %s  |  Value: %p  |  Type: OBJECT\n", index, entry->key, getHashEntryObjectValue(entry));
                    break;
                default:
                    printf("Index: %ld  |  Key: %s  |  Type: UNKNOW\n", index, entry->key);
                    break;
                }
                entry = next;
            } while (entry != NULL);
        } /* end if */
    } /* end for */
}

/******************************  Prototypes ***********************************/
/**
 * Create HashMap and init the capacity.
 * @param capacity -- The initial HashMap capacity.
 * @param factor -- The initial HashMap factor, used to dynamic expand the HashMap.
 * @return   HashMap initial by capacity and factor. NULL if create failed.
 */
HashMap	newHashMap(LONG initCapacity, FLOAT loadFactor){
        LONG       capacity = 1;
        HashMap map = NULL;
        map = (HashMap) balloc(sizeof(T_HashMap));
        if (map == NULL){
                return NULL;
        }
		memset(map, 0, sizeof(T_HashMap));

         /* <0, use default capacity. */
        if(initCapacity <= 0){
            map->capacity = DEFAULT_CAPACITY;
        }
         /* >MAXIMUM_CAPACITY,  use MAXIMUM_CAPACITY capacity. */
        if (initCapacity > MAXIMUM_CAPACITY)
        {
            initCapacity = MAXIMUM_CAPACITY;
        }
        /* find a power of 2 >= initCapacity */
        while (capacity < initCapacity)
        {
            capacity <<= 1;
        }
         map->capacity = capacity;

        if(loadFactor <= 0.0f)
        {
            map->factor = DEFAULT_FACTOR;
        }
        else
        {
            map->factor = loadFactor;
         }

        map->size = 0;
        map->threshold = (LONG)(map->capacity * map->factor);

        map->table   = (HashEntry*)balloc(map->capacity * sizeof(HashEntry));
        if (map->table == NULL)
        {
            if(map != NULL)
            { /* Free HashMap header memory. */
                bfree(map);
                map = NULL;
            }
            return NULL;
        }
		memset(map->table, 0,  map->capacity * sizeof(HashEntry));

        /** initial HashMap function **/
        map->isEmpty = HashMap_isEmpty;
        map->getSize = HashMap_getSize;
        map->getCapacity = HashMap_getCapacity;

        map->put = HashMap_put;
        map->putByte = HashMap_putByte;
        map->putChar = HashMap_putChar;
        map->putShort = HashMap_putShort;
        map->putInt = HashMap_putInt;
        map->putUint = HashMap_putUint;
        map->putLong = HashMap_putLong;
        map->putUlong = HashMap_putUlong;
        map->putFloat = HashMap_putFloat;
        map->putDouble = HashMap_putDouble;
        map->putString = HashMap_putString;
        map->putObject = HashMap_putObject;

        map->get = HashMap_get;
        map->remove = HashMap_remove;
        map->clear = HashMap_clear;
        map->contains = HashMap_contains;
        map->clone = HashMap_clone;

        map->print = HashMap_print;
        map->printByIndex = HashMap_printByIndex;

        return map;
}

/**
 * Free HashMap memory.
 * @param map -- The HashMap create by HashMap_new function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
UINT    deleteHashMap(HashMap map)
{
        ULONG     i = 0;
        HashEntry entry = NULL;
        HashEntry next = NULL;

        if ((map == NULL) || (map->table==NULL))
        {
                return CUTILFAILED;
        }

        for(i = 0; i < map->capacity; i++) 
        {
            entry = map->table[i];
            if (entry != NULL)
            {
                do 
                {
                    next = entry->next;
                    if (entry->key != NULL)
                    {
                        bfree(entry->key);
                    }
                    if (entry->value != NULL)
                    {
                        bfree(entry->value);
                    }
                    entry = next;
                } while (entry != NULL);
            }
            bfree(entry);
        } /* end for */

        bfree(map->table);
        bfree(map);

        return CUTILSUCCESS;
}

