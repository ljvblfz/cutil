/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include    "StringBuilder.h"


/************************************************************************/
/*                                                         define                                                                          */
/************************************************************************/
#define     DEFAULT_MAX_CAPACITY                            1 << 30
#define     DEFAULT_STRINGBUFFER_CAPACITY        16


/************************************************************************/
/*                                                    StringBuilder methods implement                                        */
/************************************************************************/
/**
 * Get StringBuilder's size.
 * @param sbuf -- The StringBuilder create by StringBuilder_new function.
 * @return    size of StringBuilder.
 */
static UINT    StringBuilder_getLength(StringBuilder sbuf)
{
        if (sbuf != NULL)
                return sbuf->length;
        else
                return CUTILFAILED;
}

/**
 * Get StringBuilder's capacity.
 * @param sbuf -- The StringBuilder create by StringBuilder_new function.
 * @return    size of StringBuilder.
 */
static UINT    StringBuilder_getCapacity(StringBuilder sbuf)
{
        if (sbuf != NULL)
                return sbuf->capacity;
        else
                return CUTILFAILED;
}


static CHAR StringBuilder_charAt(StringBuilder sbuf, UINT index)
{
    if(sbuf != NULL)
    {
        if(index<0 || index>=sbuf->length)
        {
            return CUTILFAILED;
        }
        return sbuf->value[index];
    }
    return CUTILFAILED;
}

static UINT StringBuilder_setCharAt(StringBuilder sbuf, UINT index, CHAR ch)
{
    if(sbuf != NULL)
    {
        if(index<0 || index>=sbuf->length)
        {
            return CUTILFAILED;
        }
        sbuf->value[index] = ch;
    }
    return CUTILFAILED;
}

static UINT StringBuilder_deleteCharAt(StringBuilder sbuf, UINT index)
{
    UINT i = 0;
    if(sbuf != NULL)
    {
        if(index<0 || index>=sbuf->length)
        {
            return CUTILFAILED;
        }

        for (i=index; i<sbuf->length; i++)
        {
            sbuf->value[index] = sbuf->value[index + 1];
        }
        sbuf->value[sbuf->length] = '\0';
        sbuf->length -= 1;
    }
    return CUTILFAILED;
}


static UINT StringBuilder_deleteValue(StringBuilder sbuf, UINT beginIndex, UINT endIndex)
{
    UINT i = 0;
    if(sbuf != NULL)
    {
        if(beginIndex<0 || endIndex>=sbuf->length || beginIndex>=endIndex)
        {
            return CUTILFAILED;
        }

        for (i=0; i<sbuf->length-endIndex; i++)
        {
            sbuf->value[beginIndex+i] = sbuf->value[endIndex + i];
        }
        sbuf->length -= (endIndex - beginIndex);
        sbuf->value[sbuf->length] = '\0';
    }
    return CUTILFAILED;
}


static UINT StringBuilder_append(StringBuilder sbuf, CHAR* value, UINT length)
{
    UINT newCapacity = 0;
    CHAR *newValue = NULL;

    if (sbuf==NULL || value==NULL || length<=0)
    {
        return CUTILFAILED;
    }

    if (value == sbuf->value)
    {
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
                 return CUTILFAILED;
             }
             memset(newValue, 0, (sizeof(CHAR) * newCapacity));
             memcpy(newValue, sbuf->value, (sizeof(CHAR) * sbuf->length));

             bfree(sbuf->value);
             sbuf->value = newValue;
             sbuf->capacity = newCapacity;

        #if LOGSUPPORT
           clog(LOG_INFO, "expand StringBuilder OK, capacity: %d\n", newCapacity);
        #endif
         }      
    }/*end  if ((sbuf->length+length) >= sbuf->capacity) */
    memcpy(&sbuf->value[sbuf->length], value, length*sizeof(CHAR));
    sbuf->length += length;

    return CUTILSUCCESS;
}


static UINT StringBuilder_appendChar(StringBuilder sbuf, CHAR value)
{
    return StringBuilder_append(sbuf, &value, 1);
}


static UINT StringBuilder_appendCharArray(StringBuilder sbuf, CHAR* value)
{
    return StringBuilder_append(sbuf, value, strlen(value));
}


static UINT StringBuilder_appendSubCharArray(StringBuilder sbuf, CHAR* value, UINT beginIndex, UINT endIndex)
{
    UINT len = 0;
    len = strlen(value);
    if (beginIndex<0 || endIndex>len || beginIndex>=endIndex)
    {
        return CUTILFAILED;
    }
    return StringBuilder_append(sbuf, &value[beginIndex], (endIndex-beginIndex +1));
}

static UINT StringBuilder_appendInt(StringBuilder sbuf, INT value)
{
    CHAR a[40] = {0}; /* MAX INT length is 32. */
    sprintf(a, "%d", value);
    return StringBuilder_append(sbuf, a, strlen(a));
}

static UINT StringBuilder_appendLong(StringBuilder sbuf, LONG value)
{
    CHAR a[100] = {0};
    sprintf(a, "%ld", value);
    return StringBuilder_append(sbuf, a, strlen(a));
}

static UINT StringBuilder_appendFloat(StringBuilder sbuf, FLOAT value)
{
    CHAR a[100] = {0};
    sprintf(a, "%f", value);
    return StringBuilder_append(sbuf, a, strlen(a));
}

static UINT StringBuilder_appendDouble(StringBuilder sbuf, DOUBLE value)
{
    CHAR a[100] = {0};
    sprintf(a, "%f", value);
    return StringBuilder_append(sbuf, a, strlen(a));
}

static UINT StringBuilder_appendString(StringBuilder sbuf, String str)
{
    CHAR* a = NULL;
    if (str==NULL || str->strValue==NULL || str->strValue->value==NULL)
    {
        return CUTILFAILED;
    }
    a = &str->strValue->value[str->offset];
    return StringBuilder_append(sbuf, a, str->length);
}

static UINT StringBuilder_appendStringBuilder(StringBuilder sbuf, StringBuilder sValue)
{
    if (sValue==NULL || sValue->value==NULL)
    {
        return CUTILFAILED;
    }
    return StringBuilder_append(sbuf, sValue->value, sValue->length);
}


static UINT StringBuilder_insert(StringBuilder sbuf, UINT offset, CHAR* value, UINT length)
{
    UINT i = 0;
    UINT moveCounts = 0;
    UINT newCapacity = 0;
    CHAR *newValue = NULL;

    if (sbuf==NULL || value==NULL || length<=0 || offset<0 || offset>sbuf->length)
    {
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
           clog(LOG_INFO, "expand StringBuilder OK, capacity: %d\n", newCapacity);
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

    return CUTILSUCCESS;
}


static UINT StringBuilder_insertChar(StringBuilder sbuf, UINT offset, CHAR value)
{
    return StringBuilder_insert(sbuf, offset, &value, 1);
}


static UINT StringBuilder_insertCharArray(StringBuilder sbuf, UINT offset, CHAR* value)
{
    return StringBuilder_insert(sbuf, offset, value, strlen(value));
}


static UINT StringBuilder_insertSubCharArray(StringBuilder sbuf, UINT offset, CHAR* value, UINT beginIndex, UINT endIndex)
{
    UINT len = 0;
    len = strlen(value);
    if (beginIndex<0 || endIndex>len || beginIndex>=endIndex)
    {
        return CUTILFAILED;
    }
    return StringBuilder_insert(sbuf, offset, value, (endIndex-beginIndex));
}

static UINT StringBuilder_insertInt(StringBuilder sbuf, UINT offset, INT value)
{
    CHAR a[40] = {0}; /* MAX INT length is 32. */
    sprintf(a, "%d", value);
    return StringBuilder_insert(sbuf, offset, a, strlen(a));
}

static UINT StringBuilder_insertLong(StringBuilder sbuf, UINT offset, LONG value)
{
    CHAR a[100] = {0};
    sprintf(a, "%ld", value);
    return StringBuilder_insert(sbuf, offset, a, strlen(a));
}

static UINT StringBuilder_insertFloat(StringBuilder sbuf, UINT offset, FLOAT value)
{
    CHAR a[100] = {0};
    sprintf(a, "%f", value);
    return StringBuilder_insert(sbuf, offset, a, strlen(a));
}

static UINT StringBuilder_insertDouble(StringBuilder sbuf, UINT offset, DOUBLE value)
{
    CHAR a[100] = {0};
    sprintf(a, "%f", value);
    return StringBuilder_insert(sbuf, offset, a, strlen(a));
}

static UINT StringBuilder_insertString(StringBuilder sbuf, UINT offset, String str)
{
    CHAR* a = NULL;
    if (str==NULL || str->strValue==NULL || str->strValue->value==NULL)
    {
        return CUTILFAILED;
    }
    a = &str->strValue->value[str->offset];
    return StringBuilder_insert(sbuf, offset, a, str->length);
}

static UINT StringBuilder_insertStringBuilder(StringBuilder sbuf, UINT offset, StringBuilder sValue)
{
    if (sValue==NULL || sValue->value==NULL)
    {
        return CUTILFAILED;
    }
    return StringBuilder_insert(sbuf, offset, sValue->value, sValue->length);
}

static UINT  StringBuilder_indexOf(StringBuilder sbuf, CHAR ch, UINT offset)
{
    UINT   i = 0;
    UINT   counts = 0;
    if (sbuf==NULL || offset<0 || offset > sbuf->length)
    {
        return -1;
    }

    counts = sbuf->length - offset;

    for (i=0; i<counts; i++)
    {
        if (ch == sbuf->value[offset + i])
        {
            return i;
        }
    }
    return -1;
}


static UINT  StringBuilder_lastIndexOf(StringBuilder sbuf, CHAR ch, UINT offset)
{
    UINT   i = 0;
    UINT   counts = 0;
    UINT   index = 0;
    if (sbuf==NULL || offset<0 || offset > sbuf->length)
    {
        return -1;
    }

    counts = sbuf->length - offset;

    for (i=counts-1; i>=0; i--)
    {
        if (ch == sbuf->value[offset + i])
        {
            return index;
        }
        index += 1;
    }
    return -1;
}

static String   StringBuilder_subString(StringBuilder sbuf, UINT beginIndex, UINT endIndex)
{
    String   s = NULL;
    UINT   length = 0;
    CHAR* value = NULL;

    if (sbuf==NULL || beginIndex<0 || endIndex>sbuf->length || beginIndex>endIndex)
    {
        return NULL;
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
    return s;
}

static StringBuilder   StringBuilder_reverse(StringBuilder sbuf)
{
    UINT   len = 0;
    UINT   i = 0;
    CHAR temp;

    if (sbuf==NULL || sbuf->value==NULL)
    {
        return NULL;
    }

   len = sbuf->length / 2;
   for(i=0; i<len; i++)
   {
       temp = sbuf->value[i];
       sbuf->value[i] = sbuf->value[sbuf->length - 1 -i];
       sbuf->value[sbuf->length - 1 - i] = temp;
   }

   return sbuf;
}

static String   StringBuilder_toString(StringBuilder sbuf)
{
    if (sbuf==NULL || sbuf->value==NULL)
    {
        return NULL;
    }
    return newString(sbuf->value);
}

static VOID     StringBuilder_print(StringBuilder sbuf)
{
    if (sbuf==NULL || sbuf->value==NULL)
    {
        printf("StringBuilder is NULL.\n");
    }

    printf("StringBuilder: length=%d, capacity=%d\n       value: %s\n", sbuf->length, sbuf->capacity, sbuf->value);
}
/************************************************************************/
/*                                                StringBuilder    Prototypes                                                         */
/************************************************************************/
/**
 * Create StringBuilder and init the capacity.
 * @param capacity -- The initial StringBuilder capacity.
 * @return   StringBuilder initial by capacity. NULL if create failed.
 */
StringBuilder	newStringBuilder(UINT capacity)
{
    StringBuilder sbuf = NULL;

    if (capacity <= 0)
    {
        capacity = DEFAULT_STRINGBUFFER_CAPACITY;
    }

    sbuf = (StringBuilder)balloc(sizeof(T_StringBuilder));
    if (sbuf == NULL)
    {
            return NULL;
    }
    memset(sbuf, 0, sizeof(T_StringBuilder));

    sbuf->value = (CHAR *)balloc(sizeof(CHAR) * capacity);
    if (sbuf->value == NULL)
    {
        bfree(sbuf);
        return NULL;
    }
    memset(sbuf->value, 0, (sizeof(CHAR) * capacity));

    sbuf->length = 0;
    sbuf->capacity = capacity;

    /* initial StringBuilder methods */
    sbuf->getLength = StringBuilder_getLength;
    sbuf->getCapacity = StringBuilder_getCapacity;
    sbuf->charAt = StringBuilder_charAt;
    sbuf->setCharAt = StringBuilder_setCharAt;

    sbuf->deleteCharAt = StringBuilder_deleteCharAt;
    sbuf->deleteValue = StringBuilder_deleteValue;

//    sbuf->replaceByCharArray = StringBuilder_replaceByCharArray;
//    sbuf->replaceByString = StringBuilder_replaceByString;

    sbuf->appendChar = StringBuilder_appendChar;
    sbuf->appendCharArray = StringBuilder_appendCharArray;
    sbuf->appendSubCharArray = StringBuilder_appendSubCharArray;
    sbuf->appendInt = StringBuilder_appendInt;
    sbuf->appendLong = StringBuilder_appendLong;
    sbuf->appendFloat = StringBuilder_appendFloat;
    sbuf->appendDouble = StringBuilder_appendDouble;
    sbuf->appendString = StringBuilder_appendString;
    sbuf->appendStringBuilder = StringBuilder_appendStringBuilder;

    sbuf->insertChar = StringBuilder_insertChar;
    sbuf->insertCharArray = StringBuilder_insertCharArray;
    sbuf->insertSubCharArray = StringBuilder_insertSubCharArray;
    sbuf->insertInt = StringBuilder_insertInt;
    sbuf->insertLong = StringBuilder_insertLong;
    sbuf->insertFloat = StringBuilder_insertFloat;
    sbuf->insertDouble = StringBuilder_insertDouble;
    sbuf->insertString = StringBuilder_insertString;
    sbuf->insertStringBuilder = StringBuilder_insertStringBuilder;

    sbuf->indexOf = StringBuilder_indexOf;
    sbuf->lastIndexOf = StringBuilder_lastIndexOf;

    sbuf->reverse = StringBuilder_reverse;

    sbuf->toString = StringBuilder_toString;
    sbuf->subString = StringBuilder_subString;

    sbuf->print = StringBuilder_print;

    return sbuf;
}

/**
 * Free StringBuilder memory.
 * @param sbuf -- The StringBuilder create by StringBuilder_new function.
 * @return    ARRAYLISTSUCCESS / ARRAYLISTFAILED.
 */
UINT    deleteStringBuilder(StringBuilder sbuf)
{
        if (sbuf != NULL)
        {
            if(sbuf->value != NULL)
            {
                    bfree(sbuf->value);
            }
            bfree(sbuf);
        }
    return CUTILSUCCESS;
}

