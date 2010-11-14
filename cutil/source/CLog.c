/*
 *	CLog.c -- Runtime log source file
 *
 *	log and analysis runtime information.
 *
 * CLog.c, v 1.0 2010/06/06 14:44:50, Eric Wang
 */

#include "CLog.h"

#include    <stdio.h>
#include    <stdarg.h>

/**
 *  log the information to console or file.
 * @param level   log level, value should be LogType.
 * @param information to log.
 */
int  clog (int level, char* format, ...)
{
    int n = 0;
    va_list ap;

    switch(level)
    {
        case LOG_INFO:
        {
            vprintf("INFO:  ", NULL);
            break;
        }
        case LOG_WARNING:
        {
            vprintf("WARNING:  ", NULL);
            break;
        }
        case LOG_ERROR:
        {
            vprintf("ERROR:  ", NULL);
            break;
        }
        default:
            break;
    }

    va_start(ap, format);
    n = vprintf(format, ap);
    va_end(ap);
    return n;
}

