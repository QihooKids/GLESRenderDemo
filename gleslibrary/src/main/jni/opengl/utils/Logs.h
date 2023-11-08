#ifndef LOGS_H_
#define LOGS_H_

#define  LOG_TAG    "logInfo"

#define _DEBUG_LOG_PRINT
#define _LOG_START_STREAM
typedef enum LogLevel{
    LOG_UNKNOWN = 0,
    LOG_DEFAULT,    /* only for SetMinPriority() */
    LOG_VERBOSE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
    LOG_SILENT, /* only for SetMinPriority(); must be last */
} LogLevel;

void __set_log_print(int logLevel, bool bFileLog, const char* path);
void __log_output_file(const char * _Format, ...);
void __log_printf(const char* _Format, ...);
void __log(int logLevel, const char* _Format, ...);

extern int  g_nLogLevel;
extern bool g_bLogFile;
extern char g_logPath[1024];

#ifdef ANDROID_NDK
    #include <stdio.h>
    #include <string.h>
	#include <android/log.h>
#else
	#include <stdio.h>
    #include <string.h>
#endif
#define  logE(...) __log(LOG_ERROR, __VA_ARGS__)
#define  logD(...) __log(LOG_DEBUG, __VA_ARGS__)
#define  logI(...) __log(LOG_INFO, __VA_ARGS__)

#endif

