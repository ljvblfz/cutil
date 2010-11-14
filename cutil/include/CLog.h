/* 
 *	CLog.h -- Runtime log header
 *
 *	log and analysis runtime information.
 *
 * CLog.h, v 1.0 2010/06/06 14:44:50, Eric Wang
 */

#ifndef __CLOG_H__
#define __CLOG_H__

/******************************** Description *********************************/

/* 
 *	GoAhead Digest Access Authentication header. This defines the Digest 
 *	access authentication public APIs.  Include this header for files that 
 *	use DAA functions
 */

/************************************************************************/
/*                                                         Include                                                                        */
/************************************************************************/
#include    "CUtil.h"


/************************************************************************/
/*                                                         Definitions                                                                   */
/************************************************************************/

typedef enum{
    LOG_INFO       =      1,
    LOG_WARNING,
    LOG_ERROR
} LogType;


/************************************************************************/
/*                                           CLog definition                                                                          */
/************************************************************************/
/**
 *  log the information to console or file.
 * @param level   log level, value should be LogType.
 * @param information to log.
 */
int  clog (int level, char* format, ...);


#endif /* __CLOG_H__ */

