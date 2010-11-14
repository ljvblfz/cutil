/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include    "StringBuffer.h"


/************************************************************************/
/*                                                         define                                                                          */
/************************************************************************/
#define     DEFAULT_MAX_CAPACITY                            1 << 30
#define     DEFAULT_STRINGBUFFER_CAPACITY        16


/************************************************************************/
/*                                                    StringBuffer methods implement                                        */
/************************************************************************/
/**
 * Get StringBuffer's size.
 * @param sbuf -- The StringBuffer create by StringBuffer_new function.
 * @return    size of StringBuffer.
 */
static UINT    StringBuffer_getLength(StringBuffer sbuf)
{
    UINT   result = CUTILFAILED;

    if (sbuf == NULL)
    {
        return CUTILFAILED;
    }

    if (sbuf->lock->getLock(sbuf->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
                clog(LOG_ERROR, "Get getLength lock failed.\n");
        #endif
        return CUTILFAILED;
    }

    result = sbuf->length;
    if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
               clog(LOG_ERROR, "Release getLength lock failed.\n");
        #endif
    }

    return result;
}

/**
 * Get StringBuffer's capacity.
 * @param sbuf -- The StringBuffer create by StringBuffer_new function.
 * @return    size of StringBuffer.
 */
static UINT    StringBuffer_getCapacity(StringBuffer sbuf)
{
    UINT   result = CUTILFAILED;

    if (sbuf == NULL)
    {
        return CUTILFAILED;
    }

    if (sbuf->lock->getLock(sbuf->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
            clog(LOG_ERROR, "Get getCapacity lock failed.\n");
    #endif
        return CUTILFAILED;
    }

    result = sbuf->capacity;

    if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
            clog(LOG_ERROR, "Release getCapacity lock failed.\n");
    #endif
    }

    return result;
}


static CHAR StringBuffer_charAt(StringBuffer sbuf, UINT index)
{
    CHAR ch = 0;

    if (sbuf->lock->getLock(sbuf->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
                clog(LOG_ERROR, "Get charAt lock failed.\n");
        #endif
        return CUTILFAILED;
    }

    if(sbuf != NULL)
    {
        if(index<0 || index>=sbuf->length)
        {
            if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
            {
            #if LOGSUPPORT
               clog(LOG_ERROR, "Release charAt lock failed.\n");
            #endif
            }
            return CUTILFAILED;
        }

        ch = sbuf->value[index];

        if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
        {
        #if LOGSUPPORT
             clog(LOG_ERROR, "Release charAt lock failed.\n");
        #endif
        }
        return ch;
    }

    if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
       clog(LOG_ERROR, "Release charAt lock failed.\n");
    #endif
    }
    return CUTILFAILED;
}

static UINT StringBuffer_setCharAt(StringBuffer sbuf, UINT index, CHAR ch)
{
    if (sbuf->lock->getLock(sbuf->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
            clog(LOG_ERROR, "Get setCharAt lock failed.\n");
        #endif
        return CUTILFAILED;
    }

    if(sbuf != NULL)
    {
        if(index<0 || index>=sbuf->length)
        {
            if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
            {
            #if LOGSUPPORT
                clog(LOG_ERROR, "Release setCharAt lock failed.\n");
            #endif
            }
            return CUTILFAILED;
        }
        sbuf->value[index] = ch;
    }

    if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
        clog(LOG_ERROR, "Release setCharAt lock failed.\n");
    #endif
    }
    return CUTILFAILED;
}

static UINT StringBuffer_deleteCharAt(StringBuffer sbuf, UINT index)
{
    UINT i = 0;

    if (sbuf->lock->getLock(sbuf->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
           clog(LOG_ERROR, "Get setCharAt lock failed.\n");
        #endif
        return CUTILFAILED;
    }

    if(sbuf != NULL)
    {
        if(index<0 || index>=sbuf->length)
        {
            if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
            {
            #if LOGSUPPORT
               clog(LOG_ERROR, "Release setCharAt lock failed.\n");
            #endif
            }
            return CUTILFAILED;
        }

        for (i=index; i<sbuf->length; i++)
        {
            sbuf->value[index] = sbuf->value[index + 1];
        }
        sbuf->value[sbuf->length] = '\0';
        sbuf->length -= 1;
    }

    if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
        clog(LOG_ERROR, "Release setCharAt lock failed.\n");
    #endif
    }
    return CUTILFAILED;
}

static UINT StringBuffer_deleteValue(StringBuffer sbuf, UINT beginIndex, UINT endIndex)
{
    UINT i = 0;

    if (sbuf->lock->getLock(sbuf->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
           clog(LOG_ERROR, "Get deleteValue lock failed.\n");
        #endif
        return CUTILFAILED;
    }

    if(sbuf != NULL)
    {
        if(beginIndex<0 || endIndex>=sbuf->length || beginIndex>=endIndex)
        {
            if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
            {
            #if LOGSUPPORT
                clog(LOG_ERROR, "Release deleteValue lock failed.\n");
            #endif
            }
            return CUTILFAILED;
        }

        for (i=0; i<sbuf->length-endIndex; i++)
        {
            sbuf->value[beginIndex+i] = sbuf->value[endIndex + i];
        }
        sbuf->length -= (endIndex - beginIndex);
        sbuf->value[sbuf->length] = '\0';
    }

    if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
        clog(LOG_ERROR, "Release deleteValue lock failed.\n");
    #endif
    }
    return CUTILFAILED;
}


static UINT StringBuffer_append(StringBuffer sbuf, CHAR* value, UINT length)
{
    UINT newCapacity = 0;
    CHAR *newValue = NULL;

    if (sbuf==NULL || value==NULL || length<=0)
    {
        return CUTILFAILED;
    }

    if (sbuf->lock->getLock(sbuf->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
           clog(LOG_ERROR, "Get append lock failed.\n");
        #endif
        return CUTILFAILED;
    }

    if (value == sbuf->value)
    {
        if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
        {
        #if LOGSUPPORT
           clog(LOG_ERROR, "Release append lock failed.\n");
        #endif
        }
        #if LOGSUPPORT
            clog(LOG_ERROR, "Can not append one to itself.\n");
        #endif
        return CUTILFAILED;
    }
    /* if append value length greater than the available capacity, expand the capacity. */
    if ((sbuf->length+length) >= sbuf->capacity)
    {
         newCapacity = sbuf->capacity * 2;

         if(newCapacity < DEFAULT_MAX_CAPACITY)
         {
             newValue = (CHAR *)balloc(sizeof(CHAR) * newCapacity);
             if (newValue == NULL)
             {
                 if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
                 {
                    #if LOGSUPPORT
                       clog(LOG_ERROR, "Release append lock failed.\n");
                    #endif
                 }
                 return CUTILFAILED;
             }
             memset(newValue, 0, (sizeof(CHAR) * newCapacity));
             memcpy(newValue, sbuf->value, (sizeof(CHAR) * sbuf->length));

             bfree(sbuf->value);
             sbuf->value = newValue;
             sbuf->capacity = newCapacity;

            #if LOGSUPPORT
                 clog(LOG_INFO, "expand StringBuffer OK, capacity: %d\n", newCapacity);
            #endif
         }      
    }/*end  if ((sbuf->length+length) >= sbuf->capacity) */
    memcpy(&sbuf->value[sbuf->length], value, length*sizeof(CHAR));
    sbuf->length += length;

    if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
        clog(LOG_ERROR, "Release append lock failed.\n");
    #endif
    }
    return CUTILSUCCESS;
}


static UINT StringBuffer_appendChar(StringBuffer sbuf, CHAR value)
{
    return StringBuffer_append(sbuf, &value, 1);
}


static UINT StringBuffer_appendCharArray(StringBuffer sbuf, CHAR* value)
{
    return StringBuffer_append(sbuf, value, strlen(value));
}


static UINT StringBuffer_appendSubCharArray(StringBuffer sbuf, CHAR* value, UINT beginIndex, UINT endIndex)
{
    UINT len = 0;
    len = strlen(value);
    if (beginIndex<0 || endIndex>len || beginIndex>=endIndex)
    {
        return CUTILFAILED;
    }
    return StringBuffer_append(sbuf, &value[beginIndex], (endIndex-beginIndex +1));
}

static UINT StringBuffer_appendInt(StringBuffer sbuf, INT value)
{
    CHAR a[40] = {0}; /* MAX INT length is 32. */
    sprintf(a, "%d", value);
    return StringBuffer_append(sbuf, a, strlen(a));
}

static UINT StringBuffer_appendLong(StringBuffer sbuf, LONG value)
{
    CHAR a[100] = {0};
    sprintf(a, "%ld", value);
    return StringBuffer_append(sbuf, a, strlen(a));
}

static UINT StringBuffer_appendFloat(StringBuffer sbuf, FLOAT value)
{
    CHAR a[100] = {0};
    sprintf(a, "%f", value);
    return StringBuffer_append(sbuf, a, strlen(a));
}

static UINT StringBuffer_appendDouble(StringBuffer sbuf, DOUBLE value)
{
    CHAR a[100] = {0};
    sprintf(a, "%f", value);
    return StringBuffer_append(sbuf, a, strlen(a));
}

static UINT StringBuffer_appendString(StringBuffer sbuf, String str)
{
    CHAR* a = NULL;
    if (str==NULL || str->strValue==NULL || str->strValue->value==NULL)
    {
        return CUTILFAILED;
    }
    a = &str->strValue->value[str->offset];
    return StringBuffer_append(sbuf, a, str->length);
}

static UINT StringBuffer_appendStringBuffer(StringBuffer sbuf, StringBuffer sValue)
{
    if (sValue==NULL || sValue->value==NULL)
    {
        return CUTILFAILED;
    }
    return StringBuffer_append(sbuf, sValue->value, sValue->length);
}


static UINT StringBuffer_insert(StringBuffer sbuf, UINT offset, CHAR* value, UINT length)
{
    UINT i = 0;
    UINT moveCounts = 0;
    UINT newCapacity = 0;
    CHAR *newValue = NULL;

    if (sbuf==NULL || value==NULL || length<=0 || offset<0 || offset>sbuf->length)
    {
        return CUTILFAILED;
    }

    if (sbuf->lock->getLock(sbuf->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
            clog(LOG_ERROR, "Get insert lock failed.\n");
        #endif
        return CUTILFAILED;
    }
    /* if append value length greater than the available capacity, expand the capacity. */
    if ((sbuf->length+length) >= sbuf->capacity)
    {
        newCapacity = sbuf->capacity * 2;

        if(newCapacity < DEFAULT_MAX_CAPACITY)
        {
            newValue = (CHAR *)balloc(sizeof(CHAR) * newCapacity);
            if (newValue == NULL)
            {
                if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
                {
                #if LOGSUPPORT
                    clog(LOG_ERROR, "Release insert lock failed.\n");
                #endif
                }
                return CUTILFAILED;
            }
            memset(newValue, 0, (sizeof(CHAR) * newCapacity));
            memcpy(newValue, sbuf->value, (sizeof(CHAR) * offset)); /* copy the value before offset */ 
            memcpy(&newValue[offset], value, (sizeof(CHAR) * length)); /* insert the new value */
            memcpy(&newValue[offset+length], &sbuf->value[offset], (sizeof(CHAR) * (sbuf->length - offset))); /* copy the value after offset */

            bfree(sbuf->value);
            sbuf->value = newValue;
            sbuf->capacity = newCapacity;

            #if LOGSUPPORT
                clog(LOG_INFO, "expand StringBuffer OK, capacity: %d\n", newCapacity);
            #endif
        }      
    } /* end if ((sbuf->length+length) >= sbuf->capacity) */
    else
    {
        moveCounts = sbuf->length - offset;
        /* move the value after offset */
        for (i=0; i<moveCounts; i++)
        {
            sbuf->value[sbuf->length + length -1 - i] = sbuf->value[sbuf->length -1 - i];
        }
        memcpy(&sbuf->value[offset], value, length*sizeof(CHAR));
    }
    sbuf->length += length;

    if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
       clog(LOG_ERROR, "Release insert lock failed.\n");
    #endif
    }
    return CUTILSUCCESS;
}


static UINT StringBuffer_insertChar(StringBuffer sbuf, UINT offset, CHAR value)
{
    return StringBuffer_insert(sbuf, offset, &value, 1);
}


static UINT StringBuffer_insertCharArray(StringBuffer sbuf, UINT offset, CHAR* value)
{
    return StringBuffer_insert(sbuf, offset, value, strlen(value));
}


static UINT StringBuffer_insertSubCharArray(StringBuffer sbuf, UINT offset, CHAR* value, UINT beginIndex, UINT endIndex)
{
    UINT len = 0;
    len = strlen(value);
    if (beginIndex<0 || endIndex>len || beginIndex>=endIndex)
    {
        return CUTILFAILED;
    }
    return StringBuffer_insert(sbuf, offset, value, (endIndex-beginIndex));
}

static UINT StringBuffer_insertInt(StringBuffer sbuf, UINT offset, INT value)
{
    CHAR a[40] = {0}; /* MAX INT length is 32. */
    sprintf(a, "%d", value);
    return StringBuffer_insert(sbuf, offset, a, strlen(a));
}

static UINT StringBuffer_insertLong(StringBuffer sbuf, UINT offset, LONG value)
{
    CHAR a[100] = {0};
    sprintf(a, "%ld", value);
    return StringBuffer_insert(sbuf, offset, a, strlen(a));
}

static UINT StringBuffer_insertFloat(StringBuffer sbuf, UINT offset, FLOAT value)
{
    CHAR a[100] = {0};
    sprintf(a, "%f", value);
    return StringBuffer_insert(sbuf, offset, a, strlen(a));
}

static UINT StringBuffer_insertDouble(StringBuffer sbuf, UINT offset, DOUBLE value)
{
    CHAR a[100] = {0};
    sprintf(a, "%f", value);
    return StringBuffer_insert(sbuf, offset, a, strlen(a));
}

static UINT StringBuffer_insertString(StringBuffer sbuf, UINT offset, String str)
{
    CHAR* a = NULL;
    if (str==NULL || str->strValue==NULL || str->strValue->value==NULL)
    {
        return CUTILFAILED;
    }
    a = &str->strValue->value[str->offset];
    return StringBuffer_insert(sbuf, offset, a, str->length);
}

static UINT StringBuffer_insertStringBuffer(StringBuffer sbuf, UINT offset, StringBuffer sValue)
{
    if (sValue==NULL || sValue->value==NULL)
    {
        return CUTILFAILED;
    }
    return StringBuffer_insert(sbuf, offset, sValue->value, sValue->length);
}

static UINT  StringBuffer_indexOf(StringBuffer sbuf, CHAR ch, UINT offset)
{
    UINT   i = 0;
    UINT   counts = 0;
    if (sbuf==NULL || offset<0 || offset > sbuf->length)
    {
        return -1;
    }

    if (sbuf->lock->getLock(sbuf->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
           clog(LOG_ERROR, "Get insert lock failed.\n");
        #endif
        return CUTILFAILED;
    }

    counts = sbuf->length - offset;

    for (i=0; i<counts; i++)
    {
        if (ch == sbuf->value[offset + i])
        {
            if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
            {
            #if LOGSUPPORT
                clog(LOG_ERROR, "Release insert lock failed.\n");
            #endif
            }
            return i;
        }
    }

    if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
       clog(LOG_ERROR, "Release insert lock failed.\n");
    #endif
    }
    return -1;
}


static UINT  StringBuffer_lastIndexOf(StringBuffer sbuf, CHAR ch, UINT offset)
{
    UINT   i = 0;
    UINT   counts = 0;
    UINT   index = 0;
    if (sbuf==NULL || offset<0 || offset > sbuf->length)
    {
        return -1;
    }

    if (sbuf->lock->getLock(sbuf->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
           clog(LOG_ERROR, "Get insert lock failed.\n");
        #endif
        return CUTILFAILED;
    }

    counts = sbuf->length - offset;

    for (i=counts-1; i>=0; i--)
    {
        if (ch == sbuf->value[offset + i])
        {
            if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
            {
            #if LOGSUPPORT
                clog(LOG_ERROR, "Release insert lock failed.\n");
            #endif
            }
            return index;
        }
        index += 1;
    }

    if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
        clog(LOG_ERROR, "Release insert lock failed.\n");
    #endif
    }
    return -1;
}

String   StringBuffer_subString(StringBuffer sbuf, UINT beginIndex, UINT endIndex)
{
    String   s = NULL;
    UINT   length = 0;
    CHAR* value = NULL;

    if (sbuf==NULL || beginIndex<0 || endIndex>sbuf->length || beginIndex>endIndex)
    {
        return NULL;
    }

    if (sbuf->lock->getLock(sbuf->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
            clog(LOG_ERROR, "Get insert lock failed.\n");
        #endif
        return CUTILFAILED;
    }

    length = endIndex - beginIndex;
    value = (CHAR*)balloc(sizeof(CHAR) * (length+1));
    if (value == NULL)
    {
        return NULL;
    }
    memset(value, 0, sizeof(CHAR) * (length+1));
    memcpy(value, &sbuf->value[beginIndex], sizeof(CHAR) * length);

    s = newString(value);
    bfree(value);

    if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
       clog(LOG_ERROR, "Release insert lock failed.\n");
    #endif
    }

    return s;
}

StringBuffer   StringBuffer_reverse(StringBuffer sbuf)
{
    UINT   len = 0;
    UINT   i = 0;
    CHAR temp;

    if (sbuf==NULL || sbuf->value==NULL)
    {
        return NULL;
    }

    if (sbuf->lock->getLock(sbuf->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
           clog(LOG_ERROR, "Get insert lock failed.\n");
        #endif
        return CUTILFAILED;
    }

   len = sbuf->length / 2;
   for(i=0; i<len; i++)
   {
       temp = sbuf->value[i];
       sbuf->value[i] = sbuf->value[sbuf->length - 1 -i];
       sbuf->value[sbuf->length - 1 - i] = temp;
   }

   if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
   {
    #if LOGSUPPORT
       clog(LOG_ERROR, "Release insert lock failed.\n");
    #endif
   }

   return sbuf;
}

String   StringBuffer_toString(StringBuffer sbuf)
{
    String s = NULL;

    if (sbuf==NULL || sbuf->value==NULL)
    {
        return NULL;
    }

    if (sbuf->lock->getLock(sbuf->lock) == CUTILFAILED)
    {
        #if LOGSUPPORT
           clog(LOG_ERROR, "Get insert lock failed.\n");
        #endif
        return CUTILFAILED;
    }

    s = newString(sbuf->value);

    if (sbuf->lock->release(sbuf->lock) == CUTILFAILED)
    {
    #if LOGSUPPORT
        clog(LOG_ERROR, "Release insert lock failed.\n");
    #endif
    }

    return s;
}

static VOID     StringBuffer_print(StringBuffer sbuf)
{
    if (sbuf==NULL || sbuf->value==NULL)
    {
        printf("StringBuffer is NULL.\n");
    }

    printf("StringBuffer: length=%d, capacity=%d\n       value: %s\n", sbuf->length, sbuf->capacity, sbuf->value);
}
/************************************************************************/
/*                                                StringBuffer    Prototypes                                                         */
/************************************************************************/
/**
 * Create StringBuffer and init the capacity.
 * @param capacity -- The initial StringBuffer capacity.
 * @return   StringBuffer initial by capacity. NULL if create failed.
 */
StringBuffer	newStringBuffer(UINT capacity)
{
    StringBuffer sbuf = NULL;

    if (capacity <= 0)
    {
        capacity = DEFAULT_STRINGBUFFER_CAPACITY;
    }

    sbuf = (StringBuffer)balloc(sizeof(T_StringBuffer));
    if (sbuf == NULL)
    {
            return NULL;
    }
    memset(sbuf, 0, sizeof(T_StringBuffer));

    sbuf->value = (CHAR *)balloc(sizeof(CHAR) * capacity);
    if (sbuf->value == NULL)
    {
        bfree(sbuf);
        return NULL;
    }
    memset(sbuf->value, 0, (sizeof(CHAR) * capacity));

    sbuf->lock = newLock();
    if (sbuf->lock == NULL)
    {
        #if LOGSUPPORT
           clog(LOG_ERROR, "Initial Vector lock failed.\n");
        #endif
        bfree(sbuf->value);
        bfree(sbuf);

        return NULL;
    }

    sbuf->length = 0;
    sbuf->capacity = capacity;

    /* initial StringBuffer methods */
    sbuf->getLength = StringBuffer_getLength;
    sbuf->getCapacity = StringBuffer_getCapacity;
    sbuf->charAt = StringBuffer_charAt;
    sbuf->setCharAt = StringBuffer_setCharAt;

    sbuf->deleteCharAt = StringBuffer_deleteCharAt;
    sbuf->deleteValue = StringBuffer_deleteValue;

//    sbuf->replaceByCharArray = StringBuffer_replaceByCharArray;
//    sbuf->replaceByString = StringBuffer_replaceByString;

    sbuf->appendChar = StringBuffer_appendChar;
    sbuf->appendCharArray = StringBuffer_appendCharArray;
    sbuf->appendSubCharArray = StringBuffer_appendSubCharArray;
    sbuf->appendInt = StringBuffer_appendInt;
    sbuf->appendLong = StringBuffer_appendLong;
    sbuf->appendFloat = StringBuffer_appendFloat;
    sbuf->appendDouble = StringBuffer_appendDouble;
    sbuf->appendString = StringBuffer_appendString;
    sbuf->appendStringBuffer = StringBuffer_appendStringBuffer;

    sbuf->insertChar = StringBuffer_insertChar;
    sbuf->insertCharArray = StringBuffer_insertCharArray;
    sbuf->insertSubCharArray = StringBuffer_insertSubCharArray;
    sbuf->insertInt = StringBuffer_insertInt;
    sbuf->insertLong = StringBuffer_insertLong;
    sbuf->insertFloat = StringBuffer_insertFloat;
    sbuf->insertDouble = StringBuffer_insertDouble;
    sbuf->insertString = StringBuffer_insertString;
    sbuf->insertStringBuffer = StringBuffer_insertStringBuffer;

    sbuf->indexOf = StringBuffer_indexOf;
    sbuf->lastIndexOf = StringBuffer_lastIndexOf;

    sbuf->reverse = StringBuffer_reverse;

    sbuf->toString = StringBuffer_toString;
    sbuf->subString = StringBuffer_subString;

    sbuf->print = StringBuffer_print;

    return sbuf;
}

/**
 * Free StringBuffer memory.
 * @param sbuf -- The StringBuffer create by StringBuffer_new function.
 * @return    ARRAYLISTSUCCESS / ARRAYLISTFAILED.
 */
UINT    deleteStringBuffer(StringBuffer sbuf)
{
    if (sbuf != NULL)
    {
        if (sbuf->lock != NULL)
        {
            deleteLock(sbuf->lock);
        }

        if(sbuf->value != NULL)
        {
                bfree(sbuf->value);
        }
        bfree(sbuf);
    }
    return CUTILSUCCESS;
}

