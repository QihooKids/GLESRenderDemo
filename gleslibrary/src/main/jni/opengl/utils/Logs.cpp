#include <cstdarg>
#include <sys/time.h>
#include "TCriticalSection.h"
#include "Logs.h"

#ifdef _DEBUG_LOG_PRINT
int g_nLogLevel = LOG_DEFAULT;
#else
int g_nLogLevel = LOG_SILENT;
#endif

#ifdef _DEBUG_LOG_OUTPUT_FILE
bool g_bLogFile = true;
#else
bool g_bLogFile = false;
#endif

char g_logPath[1024] = "/mnt/sdcard/jplayer_debug.log";


static comn::CriticalSection g_csFile;

void __log_printf(const char *Format, ...) {
    va_list args;
    va_start(args, Format);

    char buf[1024] = {0};
    vsprintf(buf, Format, args);
    va_end(args);

    char sz[600] = {0};
    time_t sec = time(nullptr);
    struct tm t = *localtime(&sec);
    struct timeval tv{};
    gettimeofday(&tv, nullptr);
    sprintf(sz, "[%d-%02d-%02d %02d:%02d:%02d.%03d] %s", t.tm_year + 1900, t.tm_mon + 1,
            t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, (int) (tv.tv_usec / 1000), buf);
    printf("%s", sz);
}

void __log_output_file(const char *Format, ...) {
    comn::AutoCritSec lock(g_csFile);
    FILE *pFile = fopen(g_logPath, "a+");
    if (pFile == nullptr)
        return;

    va_list args;
    va_start(args, Format);

    char buf[1024] = {0};
    vsprintf(buf, Format, args);
    va_end(args);

    char sz[600] = {0};
    time_t sec = time(nullptr);
    struct tm t = *localtime(&sec);
    struct timeval tv{};
    gettimeofday(&tv, nullptr);
    sprintf(sz, "[%d-%02d-%02d %02d:%02d:%02d.%03d] %s", t.tm_year + 1900, t.tm_mon + 1,
            t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, (int) (tv.tv_usec / 1000), buf);
    fwrite(sz, strlen(sz), 1, pFile);
    fclose(pFile);
}

void __set_log_print(int logLevel, bool bFileLog, const char *path) {
    g_nLogLevel = logLevel;
    g_bLogFile = bFileLog;
    if (path != nullptr && strlen(path) > 0)
        strcpy(g_logPath, path);
}

void __log(int logLevel, const char *Format, ...) {
    if (g_nLogLevel <= logLevel) {
        #ifdef ANDROID_NDK
                va_list args;
                va_start(args, Format);
                char buf[1024] = {0};
                vsprintf(buf, Format, args);
                va_end(args);
                __android_log_print(logLevel, LOG_TAG, buf, nullptr);
        #else
                 __log_printf(Format);
        #endif
        if (g_bLogFile)
            __log_output_file(Format);
    }
}