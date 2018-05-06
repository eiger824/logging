#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#include "log.h"

#define LOG_COLOR_SILENT        ""
#define LOG_COLOR_ERROR         "\033[1;31m"
#define LOG_COLOR_WARNING       "\033[1;33m"
#define LOG_COLOR_INFO          ""
#define LOG_COLOR_DEBUG         "\033[1;36m"
#define LOG_COLOR_DEFAULT       "\033[0m"

static const char* g_log_colors[] =  {
    LOG_COLOR_SILENT,
    LOG_COLOR_ERROR,
    LOG_COLOR_WARNING,
    LOG_COLOR_INFO,
    LOG_COLOR_DEBUG,
    NULL,
};

static struct timeval time_before, time_after, time_result;
static level_t g_level = LOG_SILENT;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void log_enable(level_t level)
{
    g_level = level;
}

void log_func_impl(level_t level, const char* filename, unsigned int line, const char* fmt, ...)
{
    if (level > g_level) {
        return;
    }

    pthread_mutex_lock(&mutex);

    char msg[1024]   = {0};
    char prefix[128] = {0};

    //update the time struct
    gettimeofday(&time_after, NULL);

    time_result.tv_sec = time_after.tv_sec - time_before.tv_sec;
    time_result.tv_usec = time_after.tv_usec - time_before.tv_usec;

    long int usecs = (long int)time_result.tv_usec;
    time_t timer;

    time(&timer);
    struct tm* tm_info = localtime(&timer);

    char  time_str[64] = {0};
    char usecs_str[24] = {0};
    time_str[strftime(time_str, 26, "%Y-%m-%d %H:%M:%S", tm_info)] = '\0';

    usecs_str[snprintf(usecs_str, sizeof usecs_str, "%06ld", usecs)] = '\0';

    snprintf(prefix, sizeof prefix,
             "%s[%s.%s] (%s:%d)", g_log_colors[level],
             time_str, usecs_str, filename, line);

    va_list args;
    va_start(args, fmt);
    vsnprintf(msg, sizeof msg, fmt, args);
    va_end(args);

    // Print it
    fprintf((level == LOG_ERROR || level == LOG_WARNING) ? stderr : stdout, "%s %s\n"LOG_COLOR_DEFAULT, prefix, msg);

    //and update time struct
    memcpy(&time_before, &time_after, sizeof(time_before));

    pthread_mutex_unlock(&mutex);
}
