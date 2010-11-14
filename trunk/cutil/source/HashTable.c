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
#include    "HashTable.h"


/************************************************************************/
/*                                                         Constant                                                                     */
/************************************************************************/
static    LONG      DEFAULT_CAPACITY = 16;    /* The default initial capacity - Must be a power of 2. */
static    FLOAT     DEFAULT_FACTOR =  0.75f ;   /* The default load factor. */

#define MAXIMUM_CAPACITY   1<<30  /* The default maximum capacity. */

/************************************************************************/
/*                                                              HashTableEntry methods                                                 */
/************************************************************************/

/**
 * Create new hash entry, use void type key and value.
 * Allocate memory for key. The value should allocate memory by invoker.
 */
static HashTableEntry newHashTableEntry(CHAR* key, OBJECT value, const UINT valueType)
{
    HashTableEntry entry = NULL;
    OBJECT          obj = NULL;
    UINT       len = 0;

    /* In the HashTable value can be NULL. */
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

    entry = (HashTableEntry)balloc(sizeof(T_HashTableEntry));
    if (entry == NULL)
    {
        if (obj != NULL)
        {
            bfree(obj);
        }
        return NULL;
    }
    memset(entry, 0, sizeof(T_HashTableEntry));

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

static OBJECT  getHashTableEntryObjectValue(HashTableEntry entry)
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
/*                                                              HashTable methods                                                 */
/************************************************************************/

/**
 * hash code generate function.
 * Private function.
 * Applies a supplemental hash function to a given hashCode, which defends against poor quality hash functions.  
 * This is critical because HashTable uses power-of-two length hash tables, 
 that otherwise encounter collisions for hashCodes that do not differ in lower bits. 
 * Note: Null keys always map to hash 0, thus index 0.
 * @param      str      HashTable key.
 * @param      mapsize      HashTable capacity.
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
 * Add a key-value to the HashTable. If the key is available in the HashTable, update the old value.
 * map is not NULL, ensure by invoker.
 * @param map -- The HashTable create by HashTable_new function.
 * @param key -- hash key, need string type.
 * @param value -- key value, void type.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
static UINT    HashTable_put(HashTable map, CHAR* key, OBJECT value, UINT valueType)
{
        LONG     hash = 0;
        LONG     index = 0;                  /* old HashTable capacity retrieve */
        LONG     newCapacity = 0;
        LONG     i = 0;
        LONG     oldCapacity = 0;

        HashTableEntry entry = NULL;
        HashTableEntry next = NULL;
        HashTableEntry*  newTable = NULL;
        HashTableEntry* oldTable = NULL;

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

        /* 2.  If the key not exist, create HashTableEntry and add to the HashTable */
        entry = map->table[index];

        map->table[index] = newHashTableEntry(key, value, valueType);
        if (map->table[index] == NULL)
        {
            /* Not modify the HashTable and return failed. */
            map->table[index] = entry;
            return CUTILFAILED;
        }
        map->table[index]->next = entry;
        map->size += 1;

        /* 3.  Check the HashTable capacity and  dynamic expend the HashTable*/
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
            /* Create new table for expend the HashTable */
            newTable = (HashTableEntry *)balloc(newCapacity * sizeof(HashTableEntry));
            if (newTable == NULL)
            {
                #if (DEBUG && LOGSUPPORT)
                        clog(LOG_ERROR, "expend new hash table failed.\n");
                #endif
                printf("expend new hash table failed.\n");
                return CUTILFAILED;
            }
            memset(newTable, 0, newCapacity * sizeof(HashTableEntry));
            /*Keep old table and capacity. */
            oldTable = map->table;
            oldCapacity = map->capacity;
             /*Set new table and capacity to the HashTable. */
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


/*************************  HashTable function implement  ***********************************/
/**
 * Test HashTable is empty or not.
 * @param map -- The HashTable create by newHashTable function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
static UINT    HashTable_isEmpty(HashTable map)
{
        if (map == NULL)
                return CUTILFAILED;

        return (map->size  ==  0) ? CUTILSUCCESS : CUTILFAILED;
}

/**
 * Get HashTable's size.
 * @param map -- The HashTable create by HashTable_new function.
 * @return    size of HashTable.
 */
static UINT    HashTable_getSize(HashTable map)
{
        if (map != NULL)
                return map->size;
        else
                return CUTILFAILED;
}

/**
 * Get HashTable's capacity.
 * @param map -- The HashTable create by newHashTable function.
 * @return    size of HashTable.
 */
static UINT    HashTable_getCapacity(HashTable map)
{
        if (map != NULL)
                return map->capacity;
        else
                return CUTILFAILED;
}

/**
 * Allocate newValue memory and copy value to it. 
 * The key value should allocate and copy in newHashTableEntry method.
 */

static UINT HashTable_putByte(HashTable map, CHAR* key, BYTE value)
{
    return HashTable_put(map, key, (OBJECT)&value, TYPE_BYTE);
}


static UINT HashTable_putChar(HashTable map, CHAR* key, CHAR value)
{
     return HashTable_put(map, key, (OBJECT)&value, TYPE_CHAR);
}


static UINT HashTable_putShort(HashTable map, CHAR* key, SHORT value)
{
    return HashTable_put(map, key, (OBJECT)&value, TYPE_SHORT);
}


static UINT HashTable_putInt(HashTable map, CHAR* key, INT value)
{
    return HashTable_put(map, key, (OBJECT)&value, TYPE_INT);
}


static UINT HashTable_putUint(HashTable map, CHAR* key, UINT value)
{
     return HashTable_put(map, key, (OBJECT)&value, TYPE_UINT);
}


static UINT HashTable_putLong(HashTable map, CHAR* key, LONG value)
{
     return HashTable_put(map, key, (OBJECT)&value, TYPE_LONG);
}


static UINT HashTable_putUlong(HashTable map, CHAR* key, ULONG value)
{
   return HashTable_put(map, key, (OBJECT)&value, TYPE_ULONG);
}

static UINT HashTable_putFloat(HashTable map, CHAR* key, FLOAT value)
{  
    return HashTable_put(map, key, (OBJECT)&value, TYPE_FLOAT);
}


static UINT HashTable_putDouble(HashTable map, CHAR* key, DOUBLE value)
{
    return HashTable_put(map, key, (OBJECT)&value, TYPE_DOUBLE);
}
/**
 * Allocate newValue memory and copy value to it. 
 * The key value should allocate and copy in newHashTableEntry method.
 */
static UINT HashTable_putString(HashTable map, CHAR* key, CHAR* value)
{
    return HashTable_put(map, key, (OBJECT)value, TYPE_STRING);
}


static UINT HashTable_putObject(HashTable map, CHAR* key, OBJECT value)
{
   return HashTable_put(map, key, value, TYPE_OBJECT);
}

/**
 * get value from HashTable by hash key.
 * @param map -- The HashTable create by hashmap_new function.
 * @param key -- hash key, need string type.
 * @return    void type value, should cast the value type when used.
 */
static OBJECT  HashTable_get(HashTable map, const CHAR* key)
{
    LONG     hash = 0;
    HashTableEntry entry = NULL;

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
                    return getHashTableEntryObjectValue(entry);
                }
                return entry->value;
            }
      }
      return NULL;
}


static VOID*    HashTable_remove(HashTable map, const CHAR* key)
{
        LONG     hash = 0;
        LONG     index = 0;
        HashTableEntry prev = NULL;
        HashTableEntry entry = NULL;
        HashTableEntry next = NULL;
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
                if (prev == entry) /* match the first HashTableEntry. */
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
                        value = getHashTableEntryObjectValue(entry);
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


static UINT    HashTable_clear(HashTable map)
{
    ULONG   i = 0;
    HashTableEntry entry = NULL;
    HashTableEntry next = NULL;

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


UINT    HashTable_contains(HashTable map, const CHAR* key)
{
    HashTableEntry    entry = NULL;

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

static HashTable HashTable_clone(HashTable map)
{
    HashTable newMap = NULL;
    HashTableEntry entry = NULL;
    ULONG  index = 0;

    if (map == NULL)
    {
        return NULL;
    }
    newMap = newHashTable(map->capacity, map->factor);
    if (newMap == NULL)
    {
        printf("Clone HashTable error.\n");
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

static VOID   HashTable_printByIndex(HashTable map, ULONG index)
{
    HashTableEntry entry = NULL;
    HashTableEntry next = NULL;

    if (map==NULL)
    {
        printf("HashTable is NULL.\n");
        return;
    }
    if (index >= map->capacity )
    {
        printf("Index greater than HashTable's capacity.\n");
        return;
    }

    printf(" -----------   HashTableEntry   --------------\n");
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
                printf("Index: %ld  |  Key: %s  |  Value: %p  |  Type: OBJECT\n", index, entry->key, getHashTableEntryObjectValue(entry));
                break;
            default:
                printf("Index: %ld  |  Key: %s  |  Type: UNKNOW\n", index, entry->key);
                break;
            }
            entry = next;
        } while (entry != NULL);
    } /* end if */
}

static VOID   HashTable_print(HashTable map)
{
    ULONG     index = 0;
    HashTableEntry entry = NULL;
    HashTableEntry next = NULL;

    if (map==NULL)
    {
        printf("HashTable is NULL.\n");
        return;
    }
    if (index >= map->capacity )
    {
        printf("Index greater than HashTable's capacity.\n");
        return;
    }

    printf("\n\n--------------    HashTable     Size: %ld      Capacity: %ld      --------------\n", map->size, map->capacity);

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
                    printf("Index: %ld  |  Key: %s  |  Value: %p  |  Type: OBJECT\n", index, entry->key, getHashTableEntryObjectValue(entry));
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
 * Create HashTable and init the capacity.
 * @param capacity -- The initial HashTable capacity.
 * @param factor -- The initial HashTable factor, used to dynamic expand the HashTable.
 * @return   HashTable initial by capacity and factor. NULL if create failed.
 */
HashTable	newHashTable(LONG initCapacity, FLOAT loadFactor){
        LONG       capacity = 1;
        HashTable map = NULL;
        map = (HashTable) balloc(sizeof(T_HashTable));
        if (map == NULL){
                return NULL;
        }
		memset(map, 0, sizeof(T_HashTable));

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

        map->table   = (HashTableEntry*)balloc(map->capacity * sizeof(HashTableEntry));
        if (map->table == NULL)
        {
            if(map != NULL)
            { /* Free HashTable header memory. */
                bfree(map);
                map = NULL;
            }
            return NULL;
        }
		memset(map->table, 0,  map->capacity * sizeof(HashTableEntry));

        /** initial HashTable function **/
        map->isEmpty = HashTable_isEmpty;
        map->getSize = HashTable_getSize;
        map->getCapacity = HashTable_getCapacity;

        map->put = HashTable_put;
        map->putByte = HashTable_putByte;
        map->putChar = HashTable_putChar;
        map->putShort = HashTable_putShort;
        map->putInt = HashTable_putInt;
        map->putUint = HashTable_putUint;
        map->putLong = HashTable_putLong;
        map->putUlong = HashTable_putUlong;
        map->putFloat = HashTable_putFloat;
        map->putDouble = HashTable_putDouble;
        map->putString = HashTable_putString;
        map->putObject = HashTable_putObject;

        map->get = HashTable_get;
        map->remove = HashTable_remove;
        map->clear = HashTable_clear;
        map->contains = HashTable_contains;
        map->clone = HashTable_clone;

        map->print = HashTable_print;
        map->printByIndex = HashTable_printByIndex;

        return map;
}

/**
 * Free HashTable memory.
 * @param map -- The HashTable create by HashTable_new function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
UINT    deleteHashTable(HashTable map)
{
        ULONG     i = 0;
        HashTableEntry entry = NULL;
        HashTableEntry next = NULL;

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

