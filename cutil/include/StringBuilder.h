#ifndef __STRINGBUILDER_H__
#define __STRINGBUILDER_H__

/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include    "CUtil.h"
#include    "CString.h"


/************************************************************************/
/*                                          StringBuilder definition                                                                          */
/************************************************************************/

typedef struct  Tag_StringBuilder {
        UINT               capacity;      /* capacity of the StringBuilder */
        UINT               length;          /*  length of the StringBuilder. */
        CHAR*           value;            /*  value of the StringBuilder. */
        
        /************************************************************************/
        /*                                               StringBuilder methods                                                             */
        /************************************************************************/
        /**
         * Get StringBuilder's size.
         * @param sbuf -- The StringBuilder create by newString function.
         * @return    size of StringBuilder.
         */
        UINT       (*getLength)(struct Tag_StringBuilder* sbuf);
        /**
         * Get StringBuilder's size.
         * @param sbuf -- The StringBuilder create by newStringBuilder function.
         * @return    size of StringBuilder.
         */
        UINT       (*getCapacity)(struct Tag_StringBuilder* sbuf);
       
        CHAR      (*charAt)(struct Tag_StringBuilder* sbuf, UINT index);

        UINT       (*setCharAt)(struct Tag_StringBuilder* sbuf, UINT index, CHAR ch);

        UINT       (*deleteCharAt)(struct Tag_StringBuilder* sbuf, UINT index);

        UINT       (*appendChar)(struct Tag_StringBuilder* sbuf, CHAR value);

        UINT       (*appendString)(struct Tag_StringBuilder* sbuf, String value);

        UINT       (*appendStringBuilder)(struct Tag_StringBuilder* sbuf, struct Tag_StringBuilder* value);

        UINT       (*appendInt)(struct Tag_StringBuilder* sbuf, INT value);

        UINT       (*appendFloat)(struct Tag_StringBuilder* sbuf, FLOAT value);

        UINT       (*appendDouble)(struct Tag_StringBuilder* sbuf, DOUBLE value);

        UINT       (*appendLong)(struct Tag_StringBuilder* sbuf, LONG value);

        UINT       (*appendCharArray)(struct Tag_StringBuilder* sbuf, CHAR* value);

        UINT       (*appendSubCharArray)(struct Tag_StringBuilder* sbuf, CHAR* value, UINT beginIndex, UINT endIndex);

        UINT       (*deleteValue)(struct Tag_StringBuilder* sbuf, UINT beginIndex, UINT endIndex);

        UINT       (*replaceByCharArray)(struct Tag_StringBuilder* sbuf, UINT beginIndex, UINT endIndex, CHAR* value);

        UINT       (*replaceByString)(struct Tag_StringBuilder* sbuf, UINT beginIndex, UINT endIndex, String value);

        UINT       (*insertChar)(struct Tag_StringBuilder* sbuf, UINT offset, CHAR value);

        UINT       (*insertInt)(struct Tag_StringBuilder* sbuf, UINT offset, INT value);

        UINT       (*insertLong)(struct Tag_StringBuilder* sbuf, UINT offset, LONG value);

        UINT       (*insertFloat)(struct Tag_StringBuilder* sbuf, UINT offset, FLOAT value);

        UINT       (*insertDouble)(struct Tag_StringBuilder* sbuf, UINT offset, DOUBLE value);

        UINT       (*insertCharArray)(struct Tag_StringBuilder* sbuf, UINT offset, CHAR* value);

        UINT       (*insertSubCharArray)(struct Tag_StringBuilder* sbuf, UINT offset, CHAR* value, UINT beginIndex, UINT endIndex);

        UINT       (*insertString)(struct Tag_StringBuilder* sbuf, UINT offset, String value);

        UINT       (*insertStringBuilder)(struct Tag_StringBuilder* sbuf, UINT offset, struct Tag_StringBuilder* value);

        UINT       (*indexOf)(struct Tag_StringBuilder* sbuf, CHAR ch, UINT offset);

        UINT       (*lastIndexOf)(struct Tag_StringBuilder* sbuf, CHAR ch, UINT offset);

        struct Tag_StringBuilder*       (*reverse)(struct Tag_StringBuilder* sbuf);

        String       (*toString)(struct Tag_StringBuilder* sbuf);

        String       (*subString)(struct Tag_StringBuilder* sbuf, UINT beginIndex, UINT endIndex);

        VOID       (*print)(struct Tag_StringBuilder* sbuf);

}T_StringBuilder, *StringBuilder;


/************************************************************************/
/*                                                                  Prototypes                                                         */
/************************************************************************/
/**
 * Create StringBuilder and init the capacity.
 * @param s -- The initial StringBuilder.
 * @return   StringBuilder initial by s. NULL if create failed.
 */
StringBuilder	newStringBuilder(UINT capacity);

/**
 * Free StringBuilder memory.
 * @param sbuf -- The StringBuilder create by newStringBuilder function.
 * @return    STRINGSUCCESS.
 */
UINT     deleteStringBuilder(StringBuilder sbuf);


VOID     printStringBuilder(StringBuilder sbuf);

#endif /* __STRINGBUILDER_H__ */

