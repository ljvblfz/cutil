/************************************************************************/
/*                                                             Include Files                                                           */
/************************************************************************/
#include    "LinkedList.h"

/************************************************************************/
/*                                            private LinkedList methods implement                                       */
/************************************************************************/
static LinkedEntry   newLinkedEntry(OBJECT value, UINT valueType, LinkedEntry next, LinkedEntry previous)
{
    LinkedEntry            entry = NULL;
    OBJECT      obj = NULL;
    UINT           len = 0;

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
            /* copy the object's address to list entry. When get a object, should use getObject method. */
            memcpy(obj, &value, sizeof(OBJECT));
            break;
        }
    }

    entry = (LinkedEntry)balloc(sizeof(T_LinkedEntry));
    if (entry == NULL)
    {
        if (obj != NULL)
        {
            bfree(obj);
        }
        return NULL;
    }
    memset(entry, 0, sizeof(T_LinkedEntry));

    entry->value = obj;
    entry->valueType = valueType;
    entry->previous = previous;
    entry->next = next;

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

static UINT addBefore(LinkedList list, OBJECT value, UINT valueType, LinkedEntry entry)
{
    LinkedEntry newentry = NULL;

    if (entry == NULL)
    {
        entry = list->header;
    }
    newentry = newLinkedEntry(value, valueType, entry, entry->previous);
    if (newentry == NULL)
    {
        return CUTILFAILED;
    }
    newentry->previous->next = newentry;
    newentry->next->previous = newentry;
    list->size += 1;
    return CUTILSUCCESS;
}


/** 
 * Return the value of removed entry. The return value should free by invoker. 
 */
static    OBJECT   removeLinkedEntry(LinkedList list, LinkedEntry entry)
{
    OBJECT value = NULL;
    WORD32 ptValue = 0;

    if (list==NULL || list->size==0 || entry==NULL)
    {
        return NULL;
    }

    entry->previous->next = entry->next;
    entry->next->previous = entry->previous;

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

static LinkedEntry entryByIndex(LinkedList list, UINT index)
{
    LinkedEntry entry = NULL;
    UINT i = 0;

    if (list==NULL || index<0 || index>=list->size)
    {
        return NULL;
    }

    entry = list->header;
    if (index < (list->size >> 1))
    {
        for (i=0; i<=index; i++)
        {
            entry = entry->next;
        }
    }
    else
    {
        for (i=list->size; i>index; i--)
        {
            entry = entry->previous;
        }
    }
    return entry;
}


static OBJECT  getLinkedEntryObjectValue(LinkedEntry entry)
{
    WORD32 ptValue = 0;   /* the real object value, must 32 bit unsigned int. If int not support 32 bit, use Long instead. */
    OBJECT value = NULL;
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
/*                                                       LinkedList methods implement                                       */
/************************************************************************/

/**
 * Test LinkedList is empty or not.
 * @param list -- The LinkedList create by LinkedList_new function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
static UINT    LinkedList_isEmpty(LinkedList list)
{
        if (list == NULL)
                return CUTILFAILED;

        return (list->size  ==  0) ? CUTILSUCCESS : CUTILFAILED;
}

/**
 * Get LinkedList's size.
 * @param list -- The LinkedList create by LinkedList_new function.
 * @return    size of LinkedList.
 */
static UINT    LinkedList_getSize(LinkedList list)
{
        if (list != NULL)
                return list->size;
        else
                return CUTILFAILED;
}


static LONG LinkedList_indexOf(LinkedList list, OBJECT value, UINT valueType) 
{
    LONG          index = 0;
    LinkedEntry        entry = NULL;
    OBJECT  entryValue = NULL;

    if (list == NULL || list->size==0)
    {
        return -1;
    }

    if (value == NULL)
    {
        for (entry=list->header->next; entry!=list->header; entry=entry->next)
        {
            if (entry->value == NULL)
                return index;
            index++;
        }
    }
    else
    {
        for (entry=list->header->next; entry!=list->header; entry=entry->next)
        {
            if (valueType == TYPE_OBJECT)
            {
                entryValue = getLinkedEntryObjectValue(entry);
            }
            else
            {
                entryValue = entry->value;
            }

            if (compateTo(entryValue, value, valueType) == 0)
                return index;
            index++;
        }
    }
    return -1;
}


static LONG LinkedList_lastIndexOf(LinkedList list, OBJECT value, UINT valueType) 
{
    LONG          index = 0;
    LinkedEntry        entry = NULL;
    OBJECT  entryValue = NULL;

    if (list == NULL || list->size==0)
    {
        return -1;
    }

    if (value == NULL)
    {
        for (entry=list->header->previous; entry!=list->header; entry=entry->previous)
        {
            if (entry->value == NULL)
                return index;
            index++;
        }
    }
    else
    {
        for (entry=list->header->previous; entry!=list->header; entry=entry->previous)
        {       
            if (valueType == TYPE_OBJECT)
            {
                entryValue = getLinkedEntryObjectValue(entry);
            }
            else
            {
                entryValue = entry->value;
            }

            if (compateTo(entryValue, value, valueType) == 0)
                return index;
            index++;
        }
    }
    return -1;
}

static    UINT    LinkedList_addFirst(LinkedList list, OBJECT value, UINT valueType)
{
    if (list==NULL)
    {
        return CUTILFAILED;
    }
    return addBefore(list, value, valueType, list->header->next);
}

static    UINT    LinkedList_addLast(LinkedList list, OBJECT value, UINT valueType)
{
    if (list==NULL)
    {
        return CUTILFAILED;
    }
    return addBefore(list, value, valueType, list->header);
}

static    UINT    LinkedList_add(LinkedList list, OBJECT value, UINT valueType)
{
    if (list==NULL)
    {
        return CUTILFAILED;
    }
    return addBefore(list, value, valueType, list->header);
}


static    UINT    LinkedList_addByIndex(LinkedList list, OBJECT value, UINT valueType, UINT index)
{
    if (list==NULL)
    {
        return CUTILFAILED;
    }
    return addBefore(list, value, valueType, (index==list->size ? list->header : entryByIndex(list, index)));
}


static    OBJECT    LinkedList_setByIndex(LinkedList list, OBJECT value, UINT valueType, UINT index)
{
    LinkedEntry    entry = NULL;
    LinkedEntry    newentry = NULL;
    OBJECT  oldValue = NULL;

    if (list==NULL)
    {
        return CUTILFAILED;
    }

    entry = entryByIndex(list, index);
    if (entry == NULL)
    {
        return NULL;
    }
    oldValue = entry->value;
    if (entry->valueType == TYPE_OBJECT)
    {
        oldValue = getLinkedEntryObjectValue(entry);
    }

    newentry = newLinkedEntry(value, valueType, entry->next, entry->previous);
    /* Create new entry failed, not update the list entry. */
    if (newentry != NULL)
    {
        entry->previous->next = newentry;
        entry->next->previous = newentry;
        bfree(entry); /* free the old entry. */
    }

    return oldValue;
}


static    UINT    LinkedList_contains(LinkedList list, OBJECT value, UINT valueType)
{
    if (list==NULL)
    {
        return CUTILFAILED;
    }
    if (LinkedList_indexOf(list, value, valueType) >= 0)
    {
        return CUTILSUCCESS;
    }
     return CUTILFAILED;
}


static    OBJECT    LinkedList_remove(LinkedList list, OBJECT value, UINT valueType)
{
    LinkedEntry e = NULL;

    if (list==NULL || list->size==0)
    {
        return CUTILFAILED;
    }

    if (value == NULL)
    {
        for (e=list->header->next; e!=list->header; e=e->next)
        {
            if (e->value == NULL)
            {
                return removeLinkedEntry(list, e);
            }
        }
    }
    else
    {
        for (e=list->header->next; e!=list->header; e=e->next)
        {
            if (0 == compateTo(e->value, value, valueType)) 
            {
                return removeLinkedEntry(list, e);
            }
        }
    }
    return NULL;
}

static    OBJECT    LinkedList_removeFirst(LinkedList list)
{
    if (list==NULL || list->size==0)
    {
        return NULL;
    }
    return LinkedList_remove(list, list->header->next->value, list->header->next->valueType);
}

static    OBJECT    LinkedList_removeLast(LinkedList list)
{
    if (list==NULL || list->size==0)
    {
        return NULL;
    }
    return LinkedList_remove(list, list->header->previous->value, list->header->previous->valueType);
}

static    UINT    LinkedList_clear(LinkedList list)
{
    LinkedEntry    entry = NULL;
    LinkedEntry    next = NULL;

    if (list==NULL || list->header==NULL || list->size==0)
    {
        return CUTILFAILED;
    }

    while(entry != list->header)
    {
        next = entry->next;
        
        if (entry->value != NULL)
        {
            bfree(entry->value);
        }
        bfree(entry);

        entry = next;
    }
    list->header->next = list->header->previous = list->header;
    list->size = 0;
    return CUTILSUCCESS;
}

/**
 * Add string to the LinkedList.
 * @param list -- The LinkedList create by newLinkedList function.
 * @param value -- key value, char* type / string.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedList_addString(LinkedList list, const CHAR* value)
{
    return LinkedList_add(list, (OBJECT)value, TYPE_STRING);
}

/**
 * Add char to the LinkedList.
 * @param list -- The LinkedList create by newLinkedList function.
 * @param value -- key value, char type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedList_addByte(LinkedList list, BYTE value)
{
    return LinkedList_add(list, (OBJECT)&value, TYPE_BYTE);
}

/**
 * Add char to the LinkedList.
 * @param list -- The LinkedList create by newLinkedList function.
 * @param value -- key value, char type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedList_addChar(LinkedList list, CHAR value)
{
    return LinkedList_add(list, (OBJECT)&value, TYPE_CHAR);
}

/**
 * Add int to the LinkedList.
 * @param list -- The LinkedList create by newLinkedList function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedList_addShort(LinkedList list, SHORT value)
{
    return LinkedList_add(list, (OBJECT)&value, TYPE_SHORT);
}

/**
 * Add int to the LinkedList.
 * @param list -- The LinkedList create by newLinkedList function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedList_addInt(LinkedList list, INT value)
{
    return LinkedList_add(list, (OBJECT)&value, TYPE_INT);
}

/**
 * Add int to the LinkedList.
 * @param list -- The LinkedList create by newLinkedList function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedList_addUint(LinkedList list, UINT value)
{
    return LinkedList_add(list, (OBJECT)&value, TYPE_UINT);
}

/**
 * Add int to the LinkedList.
 * @param list -- The LinkedList create by newLinkedList function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedList_addLong(LinkedList list, LONG value)
{
   return LinkedList_add(list, (OBJECT)&value, TYPE_LONG);
}

/**
 * Add int to the LinkedList.
 * @param list -- The LinkedList create by newLinkedList function.
 * @param value -- key value, int type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedList_addUlong(LinkedList list, ULONG value)
{
    return LinkedList_add(list, (OBJECT)&value, TYPE_ULONG);
}

/**
 * Add string to the LinkedList.
 * @param list -- The LinkedList create by newLinkedList function.
 * @param value -- key value, float type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedList_addFloat(LinkedList list, FLOAT value)
{
   return LinkedList_add(list, (OBJECT)&value, TYPE_FLOAT);
}

/**
 * Add double to the LinkedList.
 * @param list -- The LinkedList create by newLinkedList function.
 * @param value -- key value, char* type / string.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedList_addDouble(LinkedList list, DOUBLE value)
{
    return LinkedList_add(list, (OBJECT)&value, TYPE_DOUBLE);
}

/**
 * Add Object pointer to the LinkedList.
 * @param list -- The LinkedList create by newLinkedList function.
 * @param value -- key value, void* type.
 * @return    CUTILSUCCESS / CUTILFAILED..
 */
static UINT LinkedList_addObject(LinkedList list, const OBJECT value)
{
   return LinkedList_add(list, value, TYPE_OBJECT);
}

/**
 * get value from LinkedList by hash key.
 * @param list -- The LinkedList create by newLinkedList function.
 * @param key -- hash key, need string type.
 * @return    void type value, should cast the value type when used.
 */
static OBJECT  LinkedList_get(LinkedList list, UINT index)
{
    LinkedEntry            entry = NULL;
    WORD32    ptValue = 0;   /* the real object value, must 32 bit unsigned int. If int not support 32 bit, use Long instead. */
    OBJECT      value = NULL;

    if ((list == NULL) || (index >= list->size) || (index < 0))
    {
        return NULL;
    }

    entry = entryByIndex(list, index);
    if (entry == NULL)
    {
        return NULL;
    }
    /* get object value */
    if (entry->valueType == TYPE_OBJECT)
    {
        value = entry->value;
        if (value == NULL)
        {
            return NULL;
        }
        memcpy(&ptValue, value, sizeof(OBJECT));
        value = (OBJECT)ptValue;
        return value;
    }
    else
    {
        return entry->value;
    }
}

static    OBJECT    LinkedList_getFirst(LinkedList list)
{
    LinkedEntry            entry = NULL;
    WORD32    ptValue = 0;
    OBJECT      value = NULL;
    if (list==NULL || list->size==0)
    {
        return NULL;
    }

    entry = list->header->next;
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

static    OBJECT    LinkedList_getLast(LinkedList list)
{
    LinkedEntry            entry = NULL;
    WORD32    ptValue = 0;
    OBJECT      value = NULL;
    if (list==NULL || list->size==0)
    {
        return NULL;
    }

    entry = list->header->previous;
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

static    OBJECT    LinkedList_peek(LinkedList list)
{
    if (list==NULL || list->size==0)
    {
        return NULL;
    }
    return LinkedList_getFirst(list);
}


static OBJECT LinkedList_removeByIndex(LinkedList list, UINT index)
{
    LinkedEntry            entry = NULL;
    WORD32    ptValue = 0;   /* the real object value, must 32 bit unsigned int. If int not support 32 bit, use Long instead. */
    OBJECT      value = NULL;

    if ((list == NULL) || (index >= list->size) || (index < 0))
    {
        return NULL;
    }

    entry = entryByIndex(list, index);
    if (entry == NULL)
    {
        return NULL;
    }

    if (entry->valueType == TYPE_OBJECT)
    {
        value = removeLinkedEntry(list, entry);
        if (value == NULL)
        {
            return NULL;
        }
        memcpy(&ptValue, value, sizeof(OBJECT));
        value = (OBJECT)ptValue;
        return value;
    }
    else
    {
        return removeLinkedEntry(list, entry);
    }
}


static    LinkedList    LinkedList_clone(LinkedList list)
{
    LinkedList        newList = NULL;
    LinkedEntry      entry = NULL;

    if (list==NULL)
    {
        return NULL;
    }
    
    newList = newLinkedList();
    if (newList == NULL)
    {
        return NULL;
    }

    entry = list->header->next;
    while ((entry!=NULL) && (entry!=list->header))
    {
        newList->add(newList, entry->value, entry->valueType);
        entry = entry->next;
    }
    return newList;
}


static VOID   LinkedList_print(LinkedList list)
{
    LinkedEntry            entry = NULL;
    LinkedEntry            next = NULL;
    ULONG      index = 0;

    if (list==NULL || list->header==NULL || list->size==0)
    {
        return;
    }

    printf("\n\n------------------   LinkedList     Size: %ld    --------------------\n", list->size);
    entry = list->header->next;

    while(entry != list->header)
    {
        next = entry->next;
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
            printf("Index: %ld  |  Value: %p  |  Type: OBJECT\n", index,  getLinkedEntryObjectValue(entry));
            break;
        default:
            printf("Index: %ld  |  Type: UNKNOW\n", index);
            break;
        }
        entry = next;
        index ++;
    } /* end while */
    printf("\n----------------------------------------------------------------------\n\n");
}


/************************************************************************/
/*                                                LinkedList    Prototypes                                                         */
/************************************************************************/
/**
 * Create LinkedList and init the capacity.
 * @param capacity -- The initial LinkedList capacity.
 * @return   LinkedList initial by capacity. NULL if create failed.
 */
LinkedList	newLinkedList()
{
        LinkedList list = NULL;
        list = (LinkedList) balloc(sizeof(T_LinkedList));
        if (list == NULL)
        {
                return NULL;
        }
		memset(list, 0, sizeof(T_LinkedList));
      
        list->size = 0;
        list->header = newLinkedEntry(NULL, TYPE_VOID, NULL, NULL);
        list->header->previous = list->header->next = list->header;


        /** initial LinkedList function **/
        list->isEmpty = LinkedList_isEmpty;
        list->getSize = LinkedList_getSize;

        list->addByte = LinkedList_addByte;
        list->addShort = LinkedList_addShort;
        list->addChar = LinkedList_addChar;
        list->addString = LinkedList_addString;
        list->addInt = LinkedList_addInt;
        list->addUint = LinkedList_addUint;
        list->addLong = LinkedList_addLong;
        list->addUlong = LinkedList_addUlong;
        list->addFloat = LinkedList_addFloat;
        list->addDouble = LinkedList_addDouble;
        list->addObject = LinkedList_addObject;
        list->add = LinkedList_add;
        list->addByIndex = LinkedList_addByIndex;
        list->addFirst = LinkedList_addFirst;
        list->addLast = LinkedList_addLast;
        list->setByIndex = LinkedList_setByIndex;

        list->get = LinkedList_get;
        list->getFirst = LinkedList_getFirst;
        list->getLast = LinkedList_getLast;
        list->peek = LinkedList_peek;

        list->remove = LinkedList_remove;
        list->removeFirst = LinkedList_removeFirst;
        list->removeLast = LinkedList_removeLast;
        list->removeByIndex = LinkedList_removeByIndex;

        list->indexOf = LinkedList_indexOf;
        list->lastIndexOf = LinkedList_lastIndexOf;
        list->contains = LinkedList_contains;
        list->clear = LinkedList_clear;
        list->clone = LinkedList_clone;
        list->print = LinkedList_print;

        return list;
}

/**
 * Free LinkedList memory.
 * @param list -- The LinkedList create by LinkedList_new function.
 * @return    CUTILSUCCESS / CUTILFAILED.
 */
UINT    deleteLinkedList(LinkedList list)
{
    LinkedEntry    entry = NULL;
    LinkedEntry    next = NULL;

    if (list==NULL || list->header==NULL || list->size==0)
    {
        return CUTILFAILED;
    }
    entry = list->header->next;

    while(entry != list->header)
    {
        next = entry->next;

        if (entry->value != NULL)
        {
            bfree(entry->value);
        }
        bfree(entry);

        entry = next;
    }
    
    bfree(list);
    return CUTILSUCCESS;
}


