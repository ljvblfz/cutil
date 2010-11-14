#ifndef __STRINGBUFFER_H__
#define __STRINGBUFFER_H__

/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include    "CUtil.h"
#include    "CString.h"
#include    "Lock.h"


/************************************************************************/
/*                                          StringBuffer definition                                                                          */
/************************************************************************/

typedef struct  Tag_StringBuffer {
        UINT               capacity;      /* capacity of the StringBuffer */
        UINT               length;          /*  length of the StringBuffer. */
        CHAR*           value;            /*  value of the StringBuffer. */

        Lock                lock;             /* StringBuffer lock */
        
        /************************************************************************/
        /*                                               StringBuffer methods                                                             */
        /************************************************************************/
        /**
         * Get StringBuffer's size.
         * @param sbuf -- The StringBuffer create by newString function.
         * @return    size of StringBuffer.
         */
        UINT       (*getLength)(struct Tag_StringBuffer* sbuf);
        /**
         * Get StringBuffer's size.
         * @param sbuf -- The StringBuffer create by newStringBuffer function.
         * @return    size of StringBuffer.
         */
        UINT       (*getCapacity)(struct Tag_StringBuffer* sbuf);
       
        CHAR      (*charAt)(struct Tag_StringBuffer* sbuf, UINT index);

        UINT       (*setCharAt)(struct Tag_StringBuffer* sbuf, UINT index, CHAR ch);

        UINT       (*deleteCharAt)(struct Tag_StringBuffer* sbuf, UINT index);

        UINT       (*appendChar)(struct Tag_StringBuffer* sbuf, CHAR value);

        UINT       (*appendString)(struct Tag_StringBuffer* sbuf, String value);

        UINT       (*appendStringBuffer)(struct Tag_StringBuffer* sbuf, struct Tag_StringBuffer* value);

        UINT       (*appendInt)(struct Tag_StringBuffer* sbuf, INT value);

        UINT       (*appendFloat)(struct Tag_StringBuffer* sbuf, FLOAT value);

        UINT       (*appendDouble)(struct Tag_StringBuffer* sbuf, DOUBLE value);

        UINT       (*appendLong)(struct Tag_StringBuffer* sbuf, LONG value);

        UINT       (*appendCharArray)(struct Tag_StringBuffer* sbuf, CHAR* value);

        UINT       (*appendSubCharArray)(struct Tag_StringBuffer* sbuf, CHAR* value, UINT beginIndex, UINT endIndex);

        UINT       (*deleteValue)(struct Tag_StringBuffer* sbuf, UINT beginIndex, UINT endIndex);

        UINT       (*replaceByCharArray)(struct Tag_StringBuffer* sbuf, UINT beginIndex, UINT endIndex, CHAR* value);

        UINT       (*replaceByString)(struct Tag_StringBuffer* sbuf, UINT beginIndex, UINT endIndex, String value);

        UINT       (*insertChar)(struct Tag_StringBuffer* sbuf, UINT offset, CHAR value);

        UINT       (*insertInt)(struct Tag_StringBuffer* sbuf, UINT offset, INT value);

        UINT       (*insertLong)(struct Tag_StringBuffer* sbuf, UINT offset, LONG value);

        UINT       (*insertFloat)(struct Tag_StringBuffer* sbuf, UINT offset, FLOAT value);

        UINT       (*insertDouble)(struct Tag_StringBuffer* sbuf, UINT offset, DOUBLE value);

        UINT       (*insertCharArray)(struct Tag_StringBuffer* sbuf, UINT offset, CHAR* value);

        UINT       (*insertSubCharArray)(struct Tag_StringBuffer* sbuf, UINT offset, CHAR* value, UINT beginIndex, UINT endIndex);

        UINT       (*insertString)(struct Tag_StringBuffer* sbuf, UINT offset, String value);

        UINT       (*insertStringBuffer)(struct Tag_StringBuffer* sbuf, UINT offset, struct Tag_StringBuffer* value);

        UINT       (*indexOf)(struct Tag_StringBuffer* sbuf, CHAR ch, UINT offset);

        UINT       (*lastIndexOf)(struct Tag_StringBuffer* sbuf, CHAR ch, UINT offset);

        struct Tag_StringBuffer*       (*reverse)(struct Tag_StringBuffer* sbuf);

        String       (*toString)(struct Tag_StringBuffer* sbuf);

        String       (*subString)(struct Tag_StringBuffer* sbuf, UINT beginIndex, UINT endIndex);

        VOID       (*print)(struct Tag_StringBuffer* sbuf);

}T_StringBuffer, *StringBuffer;


/************************************************************************/
/*                                                                  Prototypes                                                         */
/************************************************************************/
/**
 * Create StringBuffer and init the capacity.
 * @param s -- The initial StringBuffer.
 * @return   StringBuffer initial by s. NULL if create failed.
 */
StringBuffer	newStringBuffer(UINT capacity);

/**
 * Free StringBuffer memory.
 * @param sbuf -- The StringBuffer create by newStringBuffer function.
 * @return    STRINGSUCCESS.
 */
UINT     deleteStringBuffer(StringBuffer sbuf);

#endif /* __STRINGBUFFER_H__ */

