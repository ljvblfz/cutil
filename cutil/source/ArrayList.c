/****************************** Include ***********************************/
#include    "ArrayList.h"


/****************************** Constant ***********************************/
#define MAXIMUM_CAPACITY   1<<30  /* The default maximum capacity. */
#define DEFAULT_ARRAYLIST_CAPACITY   16  /* hash conflict max rehash count. */

/************************************************************************/
/*                                                       ArrayList Entry Methods                                               */
/************************************************************************/
ArrayList	newArrayList(UINT capacity);

/************************************************************************/
/*                                                       ArrayList Entry Methods                                               */
/************************************************************************/
static ArrayEntry   newArrayEntry(OBJECT value, UINT valueType)
{
    ArrayEntry       entry = NULL;
    OBJECT          obj = NULL;
    UINT               len = 0;

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

    entry = (ArrayEntry)balloc(sizeof(T_ArrayEntry));
    if (entry == NULL)
    {
        if (obj != NULL)
        {
            bfree(obj);
        }
        return NULL;
    }
    memset(entry, 0, sizeof(T_ArrayEntry));

    entry->value = obj;
    entry->valueType = valueType;

    return entry;
}

static INT  compateTo(OBJECT obj1, OBJECT obj2, UINT valueType)
{
    INT          result = -1;
    UINT       len1 = 0;
    UINT       len2 = 0;
    UINT       minLen = 0;
    UINT       i = 0;
    DOUBLE  temp = 0.0;
    CHAR*   objStr1 = NULL;
    CHAR*   objStr2 = NULL;

    if (obj1==NULL && obj2==NULL)
    {
        return 0;
    }
    if (obj1==NULL || obj2==NULL)
    {
        return 1;
    }

    switch(valueType)
    {
    case TYPE_BYTE:
        result = *((BYTE *)obj1) - *((BYTE *)obj2);
        break;
    case TYPE_CHAR:
        result = *((CHAR *)obj1) - *((CHAR *)obj2);
        break;
    case TYPE_SHORT:
        result = *((SHORT *)obj1) - *((SHORT *)obj2);
        break;
    case TYPE_INT:
        result = *((INT *)obj1) - *((INT *)obj2);
        break;
    case TYPE_UINT:
        result = *((UINT *)obj1) - *((UINT *)obj2);
        break;
    case TYPE_LONG:
        result = *((LONG *)obj1) - *((LONG *)obj2);
        break;
    case TYPE_ULONG:
        result = *((ULONG *)obj1) - *((ULONG *)obj2);
        break;
    case TYPE_FLOAT: /* should use float range */
        {
            temp = (DOUBLE)(*((FLOAT *)obj1) - *((FLOAT *)obj2));
            if (temp < -0.00001)
            {
                return -1;
            }
            else if (temp > 0.00001)
            {
                return 1;
            }
            else if ((temp >= -0.00001) && (temp <= 0.00001))
            {
                return 0;
            }
            break;
        }
    case TYPE_DOUBLE:
        {
            temp = (DOUBLE)(*((DOUBLE *)obj1) - *((DOUBLE *)obj2));
            if (temp < -0.00001)
            {
                return -1;
            }
            else if (temp > 0.00001)
            {
                return 1;
            }
            else if ((temp >= -0.00001) && (temp <= 0.00001))
            {
                return 0;
            }
            break;
        }
    case TYPE_OBJECT:
        /* obj1 is the address of  object, so obj2 should use address to compare. */
        result = (obj1 == obj2) ? 0 : 1;
        break;
    case TYPE_STRING:
        {
            objStr1 = (CHAR*)obj1;
            objStr2 = (CHAR*)obj2;
            len1 = strlen(objStr1);
            len2 = strlen(objStr2);
            minLen = (len1 < len2) ? len1 : len2; /* min length */

            for (i=0; i<minLen; i++)
            {
                if (objStr1[i] != objStr2[i])
                {
                    return (INT)(objStr1[i] - objStr2[i]);
                }
            }
            if (len1 < len2)
            {
                return (INT)objStr2[minLen];
            }
            else if (len1 > len2)
            {
                return (INT)objStr1[minLen];
            }
            else
            {
                return 0;
            }
        }
    default:
        break;
    }
    return result;
}


static    OBJECT   removeArrayEntry(ArrayList list, ArrayEntry entry)
{
    OBJECT value = NULL;
    WORD32 ptValue = 0;

    if (list==NULL || list->size==0 || entry==NULL)
    {
        return NULL;
    }

    value = entry->value;
    if (entry->valueType == TYPE_OBJECT)
    {
        memcpy(&ptValue, value, sizeof(OBJECT));
        value = (OBJECT)ptValue;
    }

    bfree(entry);
    list->size -= 1;
    return value;
}


static OBJECT  getEntryObjectValue(ArrayEntry entry)
{
    WORD32 ptValue = 0;
    OBJECT value = NULL;
    if (entry == NULL && entry->valueType!=TYPE_OBJECT)
    {
        return NULL;
    }
    value = entry->value;

    memcpy(&ptValue, value, sizeof(OBJECT));
    value = (OBJECT)ptValue;
    return value;
}

/************************************************************************/
/*                                                       ArrayList methods implement                                        */
/************************************************************************/

static UINT ensureCapacity(ArrayList list, WORD32 minCapacity)
{
    WORD32    newCapacity = 0;
    WORD32    index = 0;
    ArrayEntry* newTable = NULL;

    if (NULL == list)
    {
        return CUTILFAILED;
    }

    if (minCapacity >= list->capacity)      
    {
        newCapacity = (3 * list->capacity)/2 + 1;
        newTable = (ArrayEntry*)balloc(newCapacity * sizeof(ArrayEntry*));
        if (newTable == NULL)
        {
            #if LOGSUPPORT
                clog(LOG_ERROR, "ensureCapacity: Expend ArrayList failed.\n");
            #endif
            return CUTILFAILED;
        }
        memset(newTable, 0, (newCapacity * sizeof(ArrayEntry*)));
        list->capacity = newCapacity;

        /* copy the old table to the new table */
        for (index=0; index<list->size; index++)
        {
            newTable[index] = list->table[index];
        }
        /* free the old table */
        bfree(list->table);
        list->table = newTable;
#if LOGSUPPORT
        clog(LOG_INFO, "Expand ArrayList OK, the new capacity is: %d\n", newCapacity);
#endif
    }
    return CUTILSUCCESS;
}
/**
 * Test ArrayList is empty or not.
 * @param list -- The ArrayList create by ArrayList_new function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
static UINT    ArrayList_isEmpty(ArrayList list)
{
        if (list == NULL)
                return CUTILFAILED;

        return (list->size  ==  0) ? CUTILSUCCESS : CUTILFAILED;
}

/**
 * Get ArrayList's size.
 * @param list -- The ArrayList create by ArrayList_new function.
 * @return    size of ArrayList.
 */
static UINT    ArrayList_getSize(ArrayList list)
{
        if (list != NULL)
                return list->size;
        else
                return CUTILFAILED;
}

/**
 * Get ArrayList's capacity.
 * @param list -- The ArrayList create by ArrayList_new function.
 * @return    size of ArrayList.
 */
static UINT    ArrayList_getCapacity(ArrayList list)
{
        if (list != NULL)
                return list->capacity;
        else
                return CUTILFAILED;
}

/**
 * Add value to the ArrayList. If the key is available in the ArrayList, update the old value.
 * @param list -- The ArrayList create by ArrayList_new function.
 * @param key -- hash key, need string type.
 * @param value -- key value, void type.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
static UINT    ArrayList_add(ArrayList list, OBJECT value, UINT valueType)
{
       ArrayEntry    entry = NULL;

       /* ensure the ArrayList capacity */
       if (CUTILFAILED == ensureCapacity(list, list->size + 1))
       {
           return CUTILFAILED;
       }

       /* Add value to ArrayList */
       entry = newArrayEntry(value, valueType);
        list->table[list->size] = entry;
        list->size += 1;
        return CUTILSUCCESS;
}


static    UINT    ArrayList_insert(ArrayList list, UINT index, OBJECT value, UINT valueType )
{
    ArrayEntry    entry = NULL;
    WORD32    i = 0;

    if (list==NULL || index>list->size || index<0)
    {
        return CUTILFAILED;
    }

    /* ensure the ArrayList capacity */
    if (CUTILFAILED == ensureCapacity(list, list->size + 1))
    {
        return CUTILFAILED;
    }

    /* move entry */
    for (i=list->size; i>index; i--)
    {
        list->table[i] = list->table[i-1];
    }

    /* Add value to ArrayList */
    entry = newArrayEntry(value, valueType);
    list->table[index] = entry;
    list->size += 1;
    return CUTILSUCCESS;
}

/** 
 * clone ArrayList.
 */
static ArrayList ArrayList_clone(ArrayList list)
{
    WORD32    index = 0;
    ArrayList      newList = NULL;

    if (NULL == list)
    {
        return NULL;
    }
    /* clone ArrayList container */
    newList = newArrayList(list->capacity);
    if (newList == NULL)
    {
        return NULL;
    }

    /* clone list entry. */
    for (index=0; index<list->size; index++)
    {
        newList->add(newList, list->table[index]->value, list->table[index]->valueType);
    }
    return newList;
}


/**
 * Add string to the ArrayList.
 * @param list -- The ArrayList create by newArrayList function.
 * @param value -- key value, char* type / string.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT ArrayList_addString(ArrayList list, CHAR* value)
{
    return ArrayList_add(list, value, TYPE_STRING);
}

/**
 * Add char to the ArrayList.
 * @param list -- The ArrayList create by newArrayList function.
 * @param value -- key value, char type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT ArrayList_addByte(ArrayList list, BYTE value)
{
    return ArrayList_add(list, (OBJECT)&value, TYPE_BYTE);
}

/**
 * Add char to the ArrayList.
 * @param list -- The ArrayList create by newArrayList function.
 * @param value -- key value, char type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT ArrayList_addChar(ArrayList list, CHAR value)
{
   return ArrayList_add(list, (OBJECT)&value, TYPE_CHAR);
}

/**
 * Add int to the ArrayList.
 * @param list -- The ArrayList create by newArrayList function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT ArrayList_addShort(ArrayList list, SHORT value)
{
   return ArrayList_add(list, (OBJECT)&value, TYPE_SHORT);
}

/**
 * Add int to the ArrayList.
 * @param list -- The ArrayList create by newArrayList function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT ArrayList_addInt(ArrayList list, INT value)
{
    return ArrayList_add(list, (OBJECT)&value, TYPE_INT);
}

/**
 * Add int to the ArrayList.
 * @param list -- The ArrayList create by newArrayList function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT ArrayList_addUint(ArrayList list, UINT value)
{
   return ArrayList_add(list, (OBJECT)&value, TYPE_UINT);
}

/**
 * Add int to the ArrayList.
 * @param list -- The ArrayList create by newArrayList function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT ArrayList_addLong(ArrayList list, LONG value)
{
    return ArrayList_add(list, (OBJECT)&value, TYPE_LONG);
}

/**
 * Add int to the ArrayList.
 * @param list -- The ArrayList create by newArrayList function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT ArrayList_addUlong(ArrayList list, ULONG value)
{
   return ArrayList_add(list, (OBJECT)&value, TYPE_ULONG);
}

/**
 * Add string to the ArrayList.
 * @param list -- The ArrayList create by newArrayList function.
 * @param value -- key value, float type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT ArrayList_addFloat(ArrayList list, FLOAT value)
{
    return ArrayList_add(list, (OBJECT)&value, TYPE_FLOAT);
}

/**
 * Add double to the ArrayList.
 * @param list -- The ArrayList create by newArrayList function.
 * @param value -- key value, char* type / string.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT ArrayList_addDouble(ArrayList list, DOUBLE value)
{
    return ArrayList_add(list, (OBJECT)&value, TYPE_DOUBLE);
}

/**
 * Add Object pointer to the ArrayList.
 * @param list -- The ArrayList create by newArrayList function.
 * @param value -- key value, void* type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT ArrayList_addObject(ArrayList list, const OBJECT value)
{
    return ArrayList_add(list, value, TYPE_OBJECT);
}

/**
 * get value from ArrayList by hash key.
 * @param list -- The ArrayList create by newArrayList function.
 * @param key -- hash key, need string type.
 * @return    void type value, should cast the value type when used.
 */
static OBJECT  ArrayList_get(ArrayList list, UINT index)
{
    ArrayEntry   entry = NULL;
    OBJECT      value = NULL;
    WORD32    ptValue = 0;

    if ((list == NULL) || (index >= list->size) || (index < 0))
    {
        return NULL;
    }

    entry = list->table[index];
    if (entry == NULL)
    {
        return NULL;
    }
    value = entry->value;
    if (entry->valueType == TYPE_OBJECT)
    {
        memcpy(&ptValue, value, sizeof(OBJECT));
        value = (OBJECT)ptValue;
    }

    return value;
}


static OBJECT ArrayList_remove(ArrayList list, UINT index)
{
    ArrayEntry   entry = NULL;
    UINT           i = 0;

    if ((list == NULL) || (index >= list->size) || (index < 0))
    {
        return NULL;
    }

    entry = list->table[index];
    if (entry == NULL)
    {
        return NULL;
    }

    for(i=index; i<list->size; i++)
    {
        list->table[i] = list->table[i+1];
    }
    
    return removeArrayEntry(list, entry);
}



static int ArrayList_lastIndexOf(ArrayList list, OBJECT value, UINT valueType) 
{
    WORD32          index = 0;
    WORD32          i = 0;
    ArrayEntry        entry = NULL;
    OBJECT          entryValue = NULL;

    if (list == NULL || list->size==0)
    {
        return -1;
    }

    if (value == NULL)
    {
        for (index=list->size - 1; index>=0; index--)
        {
            entry = list->table[index];
            if (entry->value == NULL)
            {
                return i;
            }
            i++;
        }
    }
    else
    {
        for (index=list->size - 1; index>0; index--)
        {
            entry = list->table[index];
            if (valueType == TYPE_OBJECT)
            {
                entryValue = getEntryObjectValue(entry);
            }
            else
            {
                entryValue = entry->value;
            }

            if (compateTo(entryValue, value, valueType) == 0)
            {
                return i;
            }
            i++;
        }
    }
    return -1;
}


static int ArrayList_indexOf(ArrayList list, OBJECT value, UINT valueType) 
{
    WORD32          index = 0;
    ArrayEntry        entry = NULL;
    OBJECT  entryValue = NULL;

    if (list == NULL || list->size==0)
    {
        return -1;
    }

    if (value == NULL)
    {
        for (index=0; index<list->size; index++)
        {
            entry = list->table[index];
            if (entry->value == NULL)
            {
                return index;
            }
        }
    }
    else
    {
         for (index=0; index<list->size; index++)
        {    
            entry = list->table[index];
            if (valueType == TYPE_OBJECT)
            {
                entryValue = getEntryObjectValue(entry);
            }
            else
            {
                entryValue = entry->value;
            }

            if (compateTo(entryValue, value, valueType) == 0)
            {
                return index;
            }
        }
    }
    return -1;
}

static    UINT    ArrayList_contains(ArrayList list, OBJECT value, UINT valueType)
{
    if (list==NULL)
    {
        return CUTILFAILED;
    }
    if (ArrayList_indexOf(list, value, valueType) >= 0)
    {
        return CUTILSUCCESS;
    }
    return CUTILFAILED;
}

static    OBJECT    ArrayList_setByIndex(ArrayList list, UINT index, OBJECT value, UINT valueType )
{
    ArrayEntry    entry = NULL;
    ArrayEntry    newentry = NULL;
    OBJECT      oldValue = NULL;

    if (list==NULL)
    {
        return CUTILFAILED;
    }

    entry = list->table[index];
    if (entry == NULL)
    {
        return NULL;
    }
    oldValue = entry->value;
    if (entry->valueType == TYPE_OBJECT)
    {
        oldValue = getEntryObjectValue(entry);
    }

    newentry = newArrayEntry(value, valueType);
    /* Create new entry failed, not update the list entry. */
    if (newentry != NULL)
    {
        bfree(entry); /* free the old entry. */
    }
    list->table[index] = newentry;

    return oldValue;
}


static UINT ArrayList_clear(ArrayList list)
{
    WORD32    index = 0;
    ArrayEntry   entry = NULL;

    if (NULL == list)
    {
        return CUTILFAILED;
    }

    for (index=0; index<list->size; index++)
    {
        entry = list->table[index];
        if (NULL != entry->value) /* value can be NULL */
        {
            bfree(entry->value);
        }
        bfree(entry);
    }
    list->size = 0;
    return CUTILSUCCESS;
}


static VOID  ArrayList_print(ArrayList list)
{
    ULONG           index = 0;
    ArrayEntry   entry = NULL;

    if (list==NULL ||  list->size==0)
    {
        return;
    }

    printf("\n\n--------------   ArrayList     Capacity: %ld,    Size: %ld    -----------\n", list->capacity, list->size);

    for (index=0; index<list->size; index++)
    {
        entry = list->table[index];
        switch (entry->valueType)
        {
        case TYPE_BYTE:
            printf("Index: %ld  |  Value: %d  |  Type: BYTE\n", index,  *(BYTE *)entry->value);
            break;
        case TYPE_CHAR:
            printf("Index: %ld  |  Value: %c  |  Type: CHAR\n", index,  *(CHAR *)entry->value);
            break;
        case TYPE_SHORT:
            printf("Index: %ld  |  Value: %d  |  Type: SHORT\n", index,  *(SHORT *)entry->value);
            break;
        case TYPE_STRING:
            printf("Index: %ld  |  Value: %s  |  Type: STRING\n", index,  (CHAR *)entry->value);
            break;
        case TYPE_INT:
            printf("Index: %ld  |  Value: %d  |  Type: INT\n", index,  *(INT *)entry->value);
            break;
        case TYPE_UINT:
            printf("Index: %ld  |  Value: %d  |  Type: UINT\n", index,  *(UINT *)entry->value);
            break;
        case TYPE_LONG:
            printf("Index: %ld  |  Value: %ld  |  Type: LONG\n", index,  *(LONG *)entry->value);
            break;
        case TYPE_ULONG:
            printf("Index: %ld  |  Value: %ld  |  Type: ULONG\n", index,  *(ULONG *)entry->value);
            break;
        case TYPE_FLOAT:
            printf("Index: %ld  |  Value: %f  |  Type: FLOAT\n", index,  *(FLOAT *)entry->value);
            break;
        case TYPE_DOUBLE:
            printf("Index: %ld  |  Value: %f  |  Type: DOUBLE\n", index,  *(DOUBLE *)entry->value);
            break;
        case TYPE_OBJECT:
            printf("Index: %ld  |  Value: %p  |  Type: OBJECT\n", index,  getEntryObjectValue(entry));
            break;
        default:
            printf("Index: %ld  |  Type: UNKNOW\n", index);
            break;
        }
    } /* end for */
    printf("\n----------------------------------------------------------------------\n\n");
}

/************************************************************************/
/*                                                ArrayList    Prototypes                                                         */
/************************************************************************/
/**
 * Create ArrayList and init the capacity.
 * @param capacity -- The initial ArrayList capacity.
 * @return   ArrayList initial by capacity. NULL if create failed.
 */
ArrayList	newArrayList(UINT capacity)
{
        ArrayList list = NULL;
        list = (ArrayList) balloc(sizeof(T_ArrayList));
        if (list == NULL)
        {
                return NULL;
        }
		memset(list, 0, sizeof(T_ArrayList));

        if(capacity <= 0)
        {
            list->capacity = DEFAULT_ARRAYLIST_CAPACITY;
        }
        else
        {
            list->capacity = capacity;
        }    
        list->size = 0;

        list->table   = (ArrayEntry*)balloc(list->capacity * sizeof(ArrayEntry*));
        if (list->table == NULL)
        {
            bfree(list);
            return NULL;
        }
		memset(list->table, 0,  list->capacity * sizeof(ArrayEntry*));

        /** initial ArrayList function **/
        list->isEmpty = ArrayList_isEmpty;
        list->getSize = ArrayList_getSize;
        list->getCapacity = ArrayList_getCapacity;
        list->add = ArrayList_add;
        list->addByte = ArrayList_addByte;
        list->addShort = ArrayList_addShort;
        list->addChar = ArrayList_addChar;
        list->addString = ArrayList_addString;
        list->addInt = ArrayList_addInt;
        list->addUint = ArrayList_addUint;
        list->addLong = ArrayList_addLong;
        list->addUlong = ArrayList_addUlong;
        list->addFloat = ArrayList_addFloat;
        list->addDouble = ArrayList_addDouble;
        list->addObject = ArrayList_addObject;

        list->setByIndex = ArrayList_setByIndex;
        list->insert = ArrayList_insert;

        list->get = ArrayList_get;
        list->remove = ArrayList_remove;

        list->indexOf = ArrayList_indexOf;
        list->lastIndexOf = ArrayList_lastIndexOf;
        list->contains = ArrayList_contains;
        list->clone = ArrayList_clone;
        list->clear = ArrayList_clear;

        list->print = ArrayList_print;

        return list;
}

/**
 * Free ArrayList memory.
 * @param list -- The ArrayList create by ArrayList_new function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
UINT    deleteArrayList(ArrayList list)
{
        UINT     i = 0;
        if (list == NULL)
                return CUTILFAILED;

         if (list->table != NULL)
         {
            for(i = 0; i < list->size; i++)
            {
               if (list->table[i] != NULL)
               {
                       bfree(list->table[i]);
               }
            }
            bfree(list->table);
         }
       
        bfree(list);
        return CUTILSUCCESS;
}

