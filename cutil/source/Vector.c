/****************************** Include ***********************************/
#include    "Vector.h"


/****************************** Constant ***********************************/
#define MAXIMUM_CAPACITY   1<<30  /* The default maximum capacity. */
#define DEFAULT_ARRAYLIST_CAPACITY   16  /* hash conflict max rehash count. */

/************************************************************************/
/*                                                       Vector Entry Methods                                               */
/************************************************************************/
Vector	newVector(UINT capacity);

/************************************************************************/
/*                                                       Vector Entry Methods                                               */
/************************************************************************/
static VectorEntry   newVectorEntry(OBJECT value, UINT valueType)
{
    VectorEntry       entry = NULL;
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

    entry = (VectorEntry)balloc(sizeof(T_VectorEntry));
    if (entry == NULL)
    {
        if (obj != NULL)
        {
            bfree(obj);
        }
        return NULL;
    }
    memset(entry, 0, sizeof(T_VectorEntry));

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


static    OBJECT   removeVectorEntry(Vector list, VectorEntry entry)
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


static OBJECT  getEntryObjectValue(VectorEntry entry)
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
/*                                                       Vector methods implement                                        */
/************************************************************************/

static UINT ensureCapacity(Vector list, WORD32 minCapacity)
{
    WORD32    newCapacity = 0;
    WORD32    index = 0;
    VectorEntry* newTable = NULL;

    if (NULL == list)
    {
        return CUTILFAILED;
    }

    if (minCapacity >= list->capacity)      
    {
        newCapacity = (3 * list->capacity)/2 + 1;
        newTable = (VectorEntry*)balloc(newCapacity * sizeof(VectorEntry*));
        if (newTable == NULL)
        {
            #if LOGSUPPORT
                clog(LOG_ERROR, "ensureCapacity: Expend Vector failed.\n");
            #endif
            return CUTILFAILED;
        }
        memset(newTable, 0, (newCapacity * sizeof(VectorEntry*)));
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
                clog(LOG_INFO, "Expand Vector OK, the new capacity is: %d\n", newCapacity);
        #endif
    }
    return CUTILSUCCESS;
}
/**
 * Test Vector is empty or not.
 * @param list -- The Vector create by Vector_new function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
static UINT    Vector_isEmpty(Vector list)
{
    UINT   result = CUTILFAILED;

    if (list == NULL)
    {
        return CUTILFAILED;
    }

    if (list->lock->getLock(list->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
                clog(LOG_ERROR, "Get isEmpty lock failed.\n");
        #endif
        return CUTILFAILED;
    }

    result = (list->size  ==  0) ? CUTILSUCCESS : CUTILFAILED;

    if (list->lock->release(list->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
                clog(LOG_ERROR, "Release isEmpty lock failed.\n");
        #endif
    }

    return result;
}

/**
 * Get Vector's size.
 * @param list -- The Vector create by Vector_new function.
 * @return    size of Vector.
 */
static UINT    Vector_getSize(Vector list)
{
    UINT   result = CUTILFAILED;

    if (list == NULL)
    {
        return CUTILFAILED;
    }

    if (list->lock->getLock(list->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
            clog(LOG_ERROR, "Get getSize lock failed.\n");
        #endif
        return CUTILFAILED;
    }

    result = list->size;

    if (list->lock->release(list->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
            clog(LOG_ERROR, "Release getSize lock failed.\n");
    #endif
    }

    return result;
}

/**
 * Get Vector's capacity.
 * @param list -- The Vector create by Vector_new function.
 * @return    size of Vector.
 */
static UINT    Vector_getCapacity(Vector list)
{
    UINT   result = CUTILFAILED;

    if (list == NULL)
    {
        return CUTILFAILED;
    }

    if (list->lock->getLock(list->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
            clog(LOG_ERROR, "Get getSize lock failed.\n");
    #endif
        return CUTILFAILED;
    }

    result = list->capacity;

    if (list->lock->release(list->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
            clog(LOG_ERROR, "Release getSize lock failed.\n");
    #endif
    }

    return result;
}

/**
 * Add value to the Vector. If the key is available in the Vector, update the old value.
 * @param list -- The Vector create by Vector_new function.
 * @param key -- hash key, need string type.
 * @param value -- key value, void type.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
static UINT    Vector_add(Vector list, OBJECT value, UINT valueType)
{
       VectorEntry    entry = NULL;

       if (list->lock->getLock(list->lock) == CUTILFAILED)
       {
        #if LOGSUPPORT
              clog(LOG_ERROR, "Get add lock failed.\n");
        #endif
           return CUTILFAILED;
       }

       /* ensure the Vector capacity */
       if (CUTILFAILED == ensureCapacity(list, list->size + 1))
       {
           if (list->lock->release(list->lock) == CUTILFAILED)
           {
            #if LOGSUPPORT
                   clog(LOG_ERROR, "Release add lock failed.\n");
            #endif
           }
           return CUTILFAILED;
       }

       /* Add value to Vector */
       entry = newVectorEntry(value, valueType);
        list->table[list->size] = entry;
        list->size += 1;

        if (list->lock->release(list->lock) == CUTILFAILED)
        {
        #if LOGSUPPORT
              clog(LOG_ERROR, "Release add lock failed.\n");
        #endif
        }
        return CUTILSUCCESS;
}


static    UINT    Vector_insert(Vector list, UINT index, OBJECT value, UINT valueType )
{
    VectorEntry    entry = NULL;
    WORD32    i = 0;

    if (list==NULL || index>list->size || index<0)
    {
        return CUTILFAILED;
    }

    if (list->lock->getLock(list->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
                clog(LOG_ERROR, "Get insert lock failed.\n");
        #endif
        return CUTILFAILED;
    }

    /* ensure the Vector capacity */
    if (CUTILFAILED == ensureCapacity(list, list->size + 1))
    {
        if (list->lock->release(list->lock) == CUTILFAILED)
        {
        #if LOGSUPPORT
               clog(LOG_ERROR, "Release add lock failed.\n");
        #endif
        }
        return CUTILFAILED;
    }

    /* move entry */
    for (i=list->size; i>index; i--)
    {
        list->table[i] = list->table[i-1];
    }

    /* Add value to Vector */
    entry = newVectorEntry(value, valueType);
    list->table[index] = entry;
    list->size += 1;

    if (list->lock->release(list->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
            clog(LOG_ERROR, "Release add lock failed.\n");
    #endif
    }

    return CUTILSUCCESS;
}

/** 
 * clone Vector.
 */
static Vector Vector_clone(Vector list)
{
    WORD32    index = 0;
    Vector      newList = NULL;

    if (NULL == list)
    {
        return NULL;
    }

    if (list->lock->getLock(list->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
                clog(LOG_ERROR, "Get insert lock failed.\n");
        #endif
        return CUTILFAILED;
    }

    /* clone Vector container */
    newList = newVector(list->capacity);
    if (newList == NULL)
    {
        if (list->lock->release(list->lock) == CUTILFAILED)
        {
        #if LOGSUPPORT
              clog(LOG_ERROR, "Release add lock failed.\n");
        #endif
        }
        return NULL;
    }

    /* clone list entry. */
    for (index=0; index<list->size; index++)
    {
        newList->add(newList, list->table[index]->value, list->table[index]->valueType);
    }

    if (list->lock->release(list->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
            clog(LOG_ERROR, "Release add lock failed.\n");
    #endif
    }
    return newList;
}


/**
 * Add string to the Vector.
 * @param list -- The Vector create by newVector function.
 * @param value -- key value, char* type / string.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Vector_addString(Vector list, CHAR* value)
{
    return Vector_add(list, value, TYPE_STRING);
}

/**
 * Add char to the Vector.
 * @param list -- The Vector create by newVector function.
 * @param value -- key value, char type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Vector_addByte(Vector list, BYTE value)
{
    return Vector_add(list, (OBJECT)&value, TYPE_BYTE);
}

/**
 * Add char to the Vector.
 * @param list -- The Vector create by newVector function.
 * @param value -- key value, char type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Vector_addChar(Vector list, CHAR value)
{
   return Vector_add(list, (OBJECT)&value, TYPE_CHAR);
}

/**
 * Add int to the Vector.
 * @param list -- The Vector create by newVector function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Vector_addShort(Vector list, SHORT value)
{
   return Vector_add(list, (OBJECT)&value, TYPE_SHORT);
}

/**
 * Add int to the Vector.
 * @param list -- The Vector create by newVector function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Vector_addInt(Vector list, INT value)
{
    return Vector_add(list, (OBJECT)&value, TYPE_INT);
}

/**
 * Add int to the Vector.
 * @param list -- The Vector create by newVector function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Vector_addUint(Vector list, UINT value)
{
   return Vector_add(list, (OBJECT)&value, TYPE_UINT);
}

/**
 * Add int to the Vector.
 * @param list -- The Vector create by newVector function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Vector_addLong(Vector list, LONG value)
{
    return Vector_add(list, (OBJECT)&value, TYPE_LONG);
}

/**
 * Add int to the Vector.
 * @param list -- The Vector create by newVector function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Vector_addUlong(Vector list, ULONG value)
{
   return Vector_add(list, (OBJECT)&value, TYPE_ULONG);
}

/**
 * Add string to the Vector.
 * @param list -- The Vector create by newVector function.
 * @param value -- key value, float type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Vector_addFloat(Vector list, FLOAT value)
{
    return Vector_add(list, (OBJECT)&value, TYPE_FLOAT);
}

/**
 * Add double to the Vector.
 * @param list -- The Vector create by newVector function.
 * @param value -- key value, char* type / string.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Vector_addDouble(Vector list, DOUBLE value)
{
    return Vector_add(list, (OBJECT)&value, TYPE_DOUBLE);
}

/**
 * Add Object pointer to the Vector.
 * @param list -- The Vector create by newVector function.
 * @param value -- key value, void* type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT Vector_addObject(Vector list, const OBJECT value)
{
    return Vector_add(list, value, TYPE_OBJECT);
}

/**
 * get value from Vector by hash key.
 * @param list -- The Vector create by newVector function.
 * @param key -- hash key, need string type.
 * @return    void type value, should cast the value type when used.
 */
static OBJECT  Vector_get(Vector list, UINT index)
{
    VectorEntry   entry = NULL;
    OBJECT      value = NULL;
    WORD32    ptValue = 0;

    if ((list == NULL) || (index >= list->size) || (index < 0))
    {
        return NULL;
    }

    if (list->lock->getLock(list->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
                clog(LOG_ERROR, "Get insert lock failed.\n");
        #endif
        return CUTILFAILED;
    }

    entry = list->table[index];
    if (entry == NULL)
    {
        if (list->lock->release(list->lock) == CUTILFAILED)
        {
        #if LOGSUPPORT
              clog(LOG_ERROR, "Release add lock failed.\n");
        #endif
        }
        return NULL;
    }
    value = entry->value;
    if (entry->valueType == TYPE_OBJECT)
    {
        memcpy(&ptValue, value, sizeof(OBJECT));
        value = (OBJECT)ptValue;
    }

    if (list->lock->release(list->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
            clog(LOG_ERROR, "Release add lock failed.\n");
    #endif
    }
    return value;
}


static OBJECT Vector_remove(Vector list, UINT index)
{
    VectorEntry   entry = NULL;
    UINT           i = 0;
    OBJECT      result = NULL;

    if ((list == NULL) || (index >= list->size) || (index < 0))
    {
        return NULL;
    }

    if (list->lock->getLock(list->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
              clog(LOG_ERROR, "Get insert lock failed.\n");
        #endif
        return CUTILFAILED;
    }

    entry = list->table[index];
    if (entry == NULL)
    {
        if (list->lock->release(list->lock) == CUTILFAILED)
        {
        #if LOGSUPPORT
              clog(LOG_ERROR, "Release add lock failed.\n");
        #endif
        }
        return NULL;
    }

    for(i=index; i<list->size; i++)
    {
        list->table[i] = list->table[i+1];
    }
    
    result = removeVectorEntry(list, entry);

    if (list->lock->release(list->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
          clog(LOG_ERROR, "Release add lock failed.\n");
    #endif
    }
    return result;
}


static int Vector_lastIndexOf(Vector list, OBJECT value, UINT valueType) 
{
    WORD32          index = 0;
    WORD32          i = 0;
    VectorEntry        entry = NULL;
    OBJECT          entryValue = NULL;

    if (list == NULL || list->size==0)
    {
        return -1;
    }

    if (list->lock->getLock(list->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
                clog(LOG_ERROR, "Get lastIndexOf lock failed.\n");
        #endif
        return -1;
    }

    if (value == NULL)
    {
        for (index=list->size - 1; index>=0; index--)
        {
            entry = list->table[index];
            if (entry->value == NULL)
            {
                if (list->lock->release(list->lock) == CUTILFAILED)
                {
                #if LOGSUPPORT
                    clog(LOG_ERROR, "Release lastIndexOf lock failed.\n");
                #endif
                }
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
                if (list->lock->release(list->lock) == CUTILFAILED)
                {
                #if LOGSUPPORT
                    clog(LOG_ERROR, "Release lastIndexOf lock failed.\n");
                #endif
                }
                return i;
            }
            i++;
        }
    }

    if (list->lock->release(list->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
            clog(LOG_ERROR, "Release lastIndexOf lock failed.\n");
    #endif
    }
    return -1;
}


static int Vector_indexOf(Vector list, OBJECT value, UINT valueType) 
{
    WORD32          index = 0;
    VectorEntry        entry = NULL;
    OBJECT  entryValue = NULL;

    if (list == NULL || list->size==0)
    {
        return -1;
    }

    if (list->lock->getLock(list->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
                clog(LOG_ERROR, "Get indexOf lock failed.\n");
        #endif
        return -1;
    }

    if (value == NULL)
    {
        for (index=0; index<list->size; index++)
        {
            entry = list->table[index];
            if (entry->value == NULL)
            {
                if (list->lock->release(list->lock) == CUTILFAILED)
                {
                #if LOGSUPPORT
                     clog(LOG_ERROR, "Release indexOf lock failed.\n");
                #endif
                }
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
                if (list->lock->release(list->lock) == CUTILFAILED)
                {
                #if LOGSUPPORT
                     clog(LOG_ERROR, "Release indexOf lock failed.\n");
                #endif
                }
                return index;
            }
        }
    }

    if (list->lock->release(list->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
            clog(LOG_ERROR, "Release indexOf lock failed.\n");
    #endif
    }
    return -1;
}

static    UINT    Vector_contains(Vector list, OBJECT value, UINT valueType)
{
    if (list==NULL)
    {
        return CUTILFAILED;
    }
    if (Vector_indexOf(list, value, valueType) >= 0)
    {
        return CUTILSUCCESS;
    }
    return CUTILFAILED;
}

static    OBJECT    Vector_setByIndex(Vector list, UINT index, OBJECT value, UINT valueType )
{
    VectorEntry    entry = NULL;
    VectorEntry    newentry = NULL;
    OBJECT      oldValue = NULL;

    if (list==NULL)
    {
        return NULL;
    }

    if (list->lock->getLock(list->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
                clog(LOG_ERROR, "Get setByIndex lock failed.\n");
        #endif
        return NULL;
    }

    entry = list->table[index];
    if (entry == NULL)
    {
        if (list->lock->release(list->lock) == CUTILFAILED)
        {
        #if LOGSUPPORT
            clog(LOG_ERROR, "Release setByIndex lock failed.\n");
        #endif
        }
        return NULL;
    }
    oldValue = entry->value;
    if (entry->valueType == TYPE_OBJECT)
    {
        oldValue = getEntryObjectValue(entry);
    }

    newentry = newVectorEntry(value, valueType);
    /* Create new entry failed, not update the list entry. */
    if (newentry != NULL)
    {
        bfree(entry); /* free the old entry. */
    }
    list->table[index] = newentry;

    if (list->lock->release(list->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
       clog(LOG_ERROR, "Release setByIndex lock failed.\n");
    #endif
    }
    return oldValue;
}


static UINT Vector_clear(Vector list)
{
    WORD32    index = 0;
    VectorEntry   entry = NULL;

    if (NULL == list)
    {
        return CUTILFAILED;
    }

    if (list->lock->getLock(list->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
                clog(LOG_ERROR, "Get clear lock failed.\n");
        #endif
        return -1;
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

    if (list->lock->release(list->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
            clog(LOG_ERROR, "Release clear lock failed.\n");
    #endif
    }
    return CUTILSUCCESS;
}


static VOID  Vector_print(Vector list)
{
    ULONG           index = 0;
    VectorEntry   entry = NULL;

    if (list==NULL ||  list->size==0)
    {
        return;
    }

    if (list->lock->getLock(list->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
                clog(LOG_ERROR, "Get print lock failed.\n");
        #endif
        return;
    }

    printf("\n\n--------------   Vector     Capacity: %ld,    Size: %ld    -----------\n", list->capacity, list->size);

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

    if (list->lock->release(list->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
            clog(LOG_ERROR, "Release print lock failed.\n");
    #endif
    }
}

/************************************************************************/
/*                                                Vector    Prototypes                                                         */
/************************************************************************/
/**
 * Create Vector and init the capacity.
 * @param capacity -- The initial Vector capacity.
 * @return   Vector initial by capacity. NULL if create failed.
 */
Vector	newVector(UINT capacity)
{
        Vector list = NULL;
        list = (Vector) balloc(sizeof(T_Vector));
        if (list == NULL)
        {
            #if LOGSUPPORT
                    clog(LOG_ERROR, "Initial Vector failed.\n");
            #endif
            return NULL;
        }
		memset(list, 0, sizeof(T_Vector));

        list->lock = newLock();
        if (list->lock == NULL)
        {
            #if LOGSUPPORT
                  clog(LOG_ERROR, "Initial Vector lock failed.\n");
            #endif
            bfree(list);
            return NULL;
        }

        if(capacity <= 0)
        {
            list->capacity = DEFAULT_ARRAYLIST_CAPACITY;
        }
        else
        {
            list->capacity = capacity;
        }    
        list->size = 0;

        list->table   = (VectorEntry*)balloc(list->capacity * sizeof(VectorEntry*));
        if (list->table == NULL)
        {
            bfree(list);
            return NULL;
        }
		memset(list->table, 0,  list->capacity * sizeof(VectorEntry*));

        /** initial Vector function **/
        list->isEmpty = Vector_isEmpty;
        list->getSize = Vector_getSize;
        list->getCapacity = Vector_getCapacity;
        list->add = Vector_add;
        list->addByte = Vector_addByte;
        list->addShort = Vector_addShort;
        list->addChar = Vector_addChar;
        list->addString = Vector_addString;
        list->addInt = Vector_addInt;
        list->addUint = Vector_addUint;
        list->addLong = Vector_addLong;
        list->addUlong = Vector_addUlong;
        list->addFloat = Vector_addFloat;
        list->addDouble = Vector_addDouble;
        list->addObject = Vector_addObject;

        list->setByIndex = Vector_setByIndex;
        list->insert = Vector_insert;

        list->get = Vector_get;
        list->remove = Vector_remove;

        list->indexOf = Vector_indexOf;
        list->lastIndexOf = Vector_lastIndexOf;
        list->contains = Vector_contains;
        list->clone = Vector_clone;
        list->clear = Vector_clear;

        list->print = Vector_print;

        return list;
}

/**
 * Free Vector memory.
 * @param list -- The Vector create by Vector_new function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
UINT    deleteVector(Vector list)
{
        UINT     i = 0;
        if (list == NULL)
        {
                return CUTILFAILED;
        }

        if (list->lock != NULL)
        {
            deleteLock(list->lock);
        }

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

