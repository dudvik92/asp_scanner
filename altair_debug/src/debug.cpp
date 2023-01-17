/*! \file debug.cpp
    Файл содержит функции для вывода отладочной информации.
*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

#include "debug.h"

int debug = 0;

char *log_file_path = NULL;

/**
 * @brief Функция установки пути до файла лога
 * @param file Путь к лог-файлу
 */
void set_log_file(char *file) {
    log_file_path = file;
}

/**
 * @brief Функция включения отображения отладочной информации в консоль
 * @param none
 */
void show_debug_messages() {
    debug = 1;
    log_file_path = NULL;
}

/**
 * Функция вывода отладочной информации в файл.
 * @param [in] format_str – строка для вывода.
 */
void DShow(const char *format_str, ...) {
    if (debug) {
        va_list parameters;
        char str[1024];
        FILE *log_fp;

        char time_buf[30] = {0};
        struct timeval tv;
        gettimeofday(&tv, 0);
        time_t time_now = time(0);   // get time now
        struct tm *now = localtime(&time_now);
        snprintf(time_buf, sizeof(time_buf), "%d-%02d-%02d %02d:%02d:%02d:%03d ", (now->tm_year + 1900), (now->tm_mon + 1), now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, (int)tv.tv_usec / 1000);

        va_start(parameters, format_str);
        memset(str, 0, sizeof(str));
        vsprintf(str, format_str, parameters);
        va_end(parameters);

        if (log_file_path != NULL) {
            log_fp = fopen(log_file_path, "a+");
            if (!log_fp)
                return;
        } else {
            log_fp = stderr;
        }

        fwrite(time_buf, 1, strlen(time_buf), log_fp);
        fwrite(str, 1, strlen(str), log_fp);
        
        if (log_file_path != NULL) {
            fclose(log_fp);
        }
    }
}

/**
 * @brief Функция вывода информации об ошибках при отладке в файл.
 * @param [in] format_str – строка для вывода.
 */
void DShowError (const char *format_str, ... )
{
    if (debug) {
        va_list parameters;
        char str[1024];
        FILE *log_fp;

        char time_buf[30] = {0};
        struct timeval tv;
        gettimeofday(&tv, 0);
        time_t time_now = time(0);   // get time now
        struct tm *now = localtime(&time_now);
        snprintf(time_buf, sizeof(time_buf), "%d-%02d-%02d %02d:%02d:%02d:%03d ", (now->tm_year + 1900), (now->tm_mon + 1), now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, (int)tv.tv_usec / 1000);

        va_start(parameters, format_str);
        memset(str, 0, sizeof(str));
        vsprintf(str, format_str, parameters);
        sprintf(str, "%s\n", strerror(errno));
        va_end(parameters);

        if (log_file_path != NULL) {
            log_fp = fopen(log_file_path, "a+");
            if (!log_fp)
                return;
        } else {
            log_fp = stderr;
        }

        fwrite(time_buf, 1, strlen(time_buf), log_fp);
        fwrite(str, 1, strlen(str), log_fp);
        
        if (log_file_path != NULL) {
            fclose(log_fp);
        }
    }
}

/**
 * @brief Функция вывода релизной информации в файл.
 * @param [in] format_str – строка для вывода.
 */
void RShow(const char *format_str, ...) {
    va_list parameters;
    char str[1024];
    FILE *log_fp;

    char time_buf[30] = {0};
    struct timeval tv;
    gettimeofday(&tv, 0);
    time_t time_now = time(0);   // get time now
    struct tm *now = localtime(&time_now);
    snprintf(time_buf, sizeof(time_buf), "%d-%02d-%02d %02d:%02d:%02d:%03d ", (now->tm_year + 1900), (now->tm_mon + 1), now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, (int)tv.tv_usec / 1000);

    va_start(parameters, format_str);
    memset(str, 0, sizeof(str));
    vsprintf(str, format_str, parameters);
    va_end(parameters);

    if (log_file_path != NULL) {
        log_fp = fopen(log_file_path, "a+");
        if (!log_fp)
            return;
    } else {
        log_fp = stderr;
    }

    fwrite(time_buf, 1, strlen(time_buf), log_fp);
    fwrite(str, 1, strlen(str), log_fp);
    
    if (log_file_path != NULL) {
        fclose(log_fp);
    }
}

/**
 * @brief Функция вывода информации об ошибках в релизе в файл.
 * @param [in] format_str – строка для вывода.
 */
void RShowError (const char *format_str, ... )
{
    va_list parameters;
    char str[1024];
    FILE *log_fp;

    char time_buf[30] = {0};
    struct timeval tv;
    gettimeofday(&tv, 0);
    time_t time_now = time(0);   // get time now
    struct tm *now = localtime(&time_now);
    snprintf(time_buf, sizeof(time_buf), "%d-%02d-%02d %02d:%02d:%02d:%03d ", (now->tm_year + 1900), (now->tm_mon + 1), now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, (int)tv.tv_usec / 1000);

    va_start(parameters, format_str);
    memset(str, 0, sizeof(str));
    vsprintf(str, format_str, parameters);
    sprintf(str, "%s\n", strerror(errno));
    va_end(parameters);

    if (log_file_path != NULL) {
        log_fp = fopen(log_file_path, "a+");
        if (!log_fp)
            return;
    } else {
        log_fp = stderr;
    }

    fwrite(time_buf, 1, strlen(time_buf), log_fp);
    fwrite(str, 1, strlen(str), log_fp);
    
    if (log_file_path != NULL) {
        fclose(log_fp);
    }
}
