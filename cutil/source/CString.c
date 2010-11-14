/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include    "CString.h"


/************************************************************************/
/*                                                   String methods implement                                                  */
/************************************************************************/

static String String_createVoidString();

/**
 * Get String's size.
 * @param str -- The String create by String_new function.
 * @return    size of String.
 */
static UINT    String_getLength(String str)
{
        if (str != NULL)
                return str->length;
        else
                return CUTILFAILED;
}


static CHAR String_charAt(String str, UINT index)
{
    if(str != NULL)
    {
        if(index<0 || index>=str->length)
        {
            return CUTILFAILED;
        }
        return str->strValue->value[index + str->offset];
    }
    return CUTILFAILED;
}


static UINT String_equals(String str1, String str2)
{
    UINT   i = 0;
    if(str1==NULL && str2==NULL)
    {
        return CUTILSUCCESS;
    }
    if (str1==NULL || str2==NULL)
    {
        return CUTILFAILED;
    }
    if (str1->length != str2->length)
    {
        return CUTILFAILED;
    }

    for (i=0; i<str1->length; i++)
    {
        if (str1->strValue->value[str1->offset + i] != str2->strValue->value[str2->offset + i])
        {
            return CUTILFAILED;
        }
    }
    return CUTILSUCCESS;
}


static INT String_compareTo(String str1, String str2)
{
    UINT   i = 0;
    UINT   min = 0;

    if(str1==NULL && str2==NULL)
    {
        return 0;
    }
    if (str1==NULL || str2==NULL)
    {
        return 1;
    }

    min = (str1->length <= str2->length) ? str1->length : str2->length;

    for (i=0; i<min; i++)
    {
        if (str1->strValue->value[str1->offset + i] != str2->strValue->value[str2->offset + i])
        {
            return (int)(str1->strValue->value[str1->offset + i] - str2->strValue->value[str2->offset + i]);
        }
    }

    if (str1->length > str2->length)
    {
        return 1;
    }
    else if (str1->length == str2->length)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}


static UINT  String_indexOf(String str, CHAR ch, UINT offset)
{
    UINT   i = 0;
    UINT   counts = 0;
    if (str==NULL || str->strValue==NULL || str->strValue->value==NULL || offset<0 || offset > str->length)
    {
        return -1;
    }

    counts = str->length - offset;

    for (i=0; i<counts; i++)
    {
        if (ch == str->strValue->value[str->offset + offset + i])
        {
            return i;
        }
    }
    return -1;
}


static UINT  String_lastIndexOf(String str, CHAR ch, UINT offset)
{
    UINT   i = 0;
    UINT   counts = 0;
    UINT   index = 0;
    if (str==NULL || str->strValue==NULL || str->strValue->value==NULL || offset<0 || offset > str->length)
    {
        return -1;
    }

    counts = str->length - offset;

    for (i=counts-1; i>=0; i--)
    {
        if (ch == str->strValue->value[str->offset + i])
        {
            return index;
        }
        index += 1;
    }
    return -1;
}


String   String_subString(String str, UINT beginIndex, UINT endIndex)
{
    String s = NULL;
    if (str==NULL || beginIndex<0 || endIndex>str->length || beginIndex>endIndex)
    {
        return NULL;
    }

    s = String_createVoidString();
    if(s != NULL)
    {
        s->strValue = str->strValue;
        s->strValue->reference += 1;
        s->offset = str->offset + beginIndex;
        s->length = endIndex - beginIndex;
    }
    return s;
}


static String* String_split(String str, CHAR ch, UINT *count)
{
    UINT i = 0;
    UINT beginIndex = 0;
    UINT endIndex = 0;
    UINT matchNum = 0;
    String *strArray = NULL;

    if (str==NULL || count==NULL || str->strValue==NULL || str->strValue->value==NULL)
    {
        return NULL;
    }

    for (i=0; i<str->length; i++)
    {
        if (ch == str->strValue->value[str->offset + i])
        {
            (*count) += 1;
        }
    }

    if ((*count) > 0)
    {
        (*count) += 1;
    }

    strArray = (String *)balloc(sizeof(String) * (*count));
    if (strArray == NULL)
    {
        (*count) = 0;
        return NULL;
    }

    for(i=0; i<str->length; i++)
    {
        if (ch == str->strValue->value[str->offset + i])
        {
            endIndex = i;
            if (endIndex > beginIndex)
            {
                strArray[matchNum] = str->subString(str, beginIndex, endIndex);
                matchNum += 1;
                beginIndex = endIndex + 1;
            }
        }
    }

    if ((*count) >0)
    {
        endIndex = i;
        if (endIndex > beginIndex)
        {
            strArray[matchNum] = str->subString(str, beginIndex, endIndex);
        }
    }

    return strArray;
}


static CHAR*   String_toCharArray(String str)
{
    CHAR* array = NULL;
    if (str==NULL || str->strValue==NULL || str->strValue->value==NULL)
    {
        return NULL;
    }

    if (str->length == 0)
    {
        return NULL;
    }

    array = (CHAR*)balloc(sizeof(CHAR) * (str->length+1));
    if (array == NULL)
    {
        return NULL;
    }
    memset(array, 0, sizeof(CHAR) * (str->length+1));
    memcpy(array, &str->strValue->value[str->offset], (str->length * sizeof(CHAR)));
    return array;
}


UINT String_startWith(String str, CHAR* prex)
{
    UINT len = 0;
    UINT i = 0;
    if (str==NULL || prex==NULL)
    {
        return CUTILFAILED;
    }
    
    len = strlen(prex);
    if (str->length < len)
    {
        return CUTILFAILED;
    }

    for (i=0; i<len; i++)
    {
        if (str->strValue->value[i] != prex[i])
        {
            return CUTILFAILED;
        }
    }

    return CUTILSUCCESS;
}


UINT String_endWith(String str, CHAR* prex)
{
    UINT len = 0;
    UINT i = 0;
    if (str==NULL || prex==NULL)
    {
        return CUTILFAILED;
    }

    len = strlen(prex);
    if (str->length < len)
    {
        return CUTILFAILED;
    }

    for (i=len-1; i>0; i--)
    {
        if (str->strValue->value[str->length - len + i] != prex[i])
        {
            return CUTILFAILED;
        }
    }

    return CUTILSUCCESS;
}

static  UINT   String_toUpperCase(String *str)
{
    String       newStr = NULL;
    CHAR*   value = NULL;
    UINT       i = 0;

    if (*str == NULL)
    {
        return CUTILFAILED;
    }
    value = (*str)->toCharArray(*str);
    if (value == NULL)
    {
        return CUTILFAILED;
    }
    for(i=0; i<(*str)->length; i++)
    {
        if (value[i]>='a' && value[i]<='z')
        {
            value[i] -= 32;
        }
    }

    newStr = newString(value);
    bfree(value);
    deleteString(*str);
    *str = newStr;
    return CUTILSUCCESS;
}


static UINT       String_toLowerCase(String *str)
{
    String       newStr = NULL;
    CHAR*   value = NULL;
    UINT       i = 0;

    if (*str == NULL)
    {
        return CUTILFAILED;
    }
    value = (*str)->toCharArray(*str);
    if (value == NULL)
    {
        return CUTILFAILED;
    }
    for(i=0; i<(*str)->length; i++)
    {
        if (value[i]>='A' && value[i]<='Z')
        {
            value[i] += 32;
        }
    }

    newStr = newString(value);
    bfree(value);
    deleteString(*str);
    (*str) = newStr;
    return CUTILSUCCESS;
}

static VOID       String_print(String str)
{
    CHAR*   value = NULL;

    if (str == NULL)
    {
        return;
    }
    value = str->toCharArray(str);
    if (value == NULL)
    {
        return;
    }
    printf("%s\n", value);
    bfree(value); 
}


static String   String_createVoidString()
{
    String str = NULL;
    str = (String)balloc(sizeof(T_String));
    if (str == NULL)
    {
        return NULL;
    }
    memset(str, 0, sizeof(T_String));
    
    /* initial String methods */
    str->getLength = String_getLength;
    str->charAt = String_charAt;
    str->equals = String_equals;
    str->compareTo = String_compareTo;
    str->indexOf = String_indexOf;
    str->lastIndexOf = String_lastIndexOf;
    str->subString = String_subString;
    str->split = String_split;
    str->toCharArray = String_toCharArray;
    str->startWith = String_startWith;
    str->endWith = String_endWith;
    str->toUpperCase = String_toUpperCase;
    str->toLowerCase = String_toLowerCase;
    str->print = String_print;

    return str;
}
/************************************************************************/
/*                                                String    Prototypes                                                         */
/************************************************************************/
/**
 * Create String and init the capacity.
 * @param capacity -- The initial String capacity.
 * @return   String initial by capacity. NULL if create failed.
 */
String	newString(CHAR* s)
{
    size_t    len = 0;
    String str = NULL;
    StringValue strValue = NULL;

    if (s == NULL)
    {
        return NULL;
    }

    str = String_createVoidString();
    if (str == NULL)
    {
            return NULL;
    }

    len = strlen(s);
    if (len > 0)
    {
        strValue = (StringValue)balloc(sizeof(T_StringValue));
        if (strValue == NULL)
        {
            bfree(str);
            return NULL;
        }
        memset(strValue, 0, sizeof(T_StringValue));
        strValue->value = (CHAR*)balloc(sizeof(CHAR)*(len+1));
        if (strValue->value == NULL)
        {
            bfree(strValue);
            bfree(str);
            return NULL;
        }
        memset(strValue->value, 0, (len+1)*sizeof(CHAR));
        memcpy(strValue->value, s, len*sizeof(CHAR));
    }
    str->offset = 0;
    str->strValue = strValue;
    str->strValue->reference += 1;
    str->length = (UINT)len;

    return str;
}

/**
 * Free String memory.
 * @param str -- The String create by String_new function.
 * @return    ARRAYLISTSUCCESS / ARRAYLISTFAILED.
 */
UINT    deleteString(String str)
{
        if (str != NULL)
        {
            if(str->strValue != NULL)
            {
                str->strValue->reference -= 1;
                if (str->strValue->reference == 0)
                {
                    bfree(str->strValue->value);
                    bfree(str->strValue);
                }
            }
            bfree(str);
        }
    return CUTILSUCCESS;
}

