#ifndef DEBUG_H
#define DEBUG_H

/**
 * @brief Функция установки пути до файла лога
 * @param file Путь к лог-файлу
 */
void set_log_file(char *file);

/**
 * @brief Функция включения отображения отладочной информации в консоль
 * @param none
 */
void show_debug_messages();

/**
 * @brief Функция вывода отладочной информации в файл.
 * @param [in] format_str – строка для вывода.
 */
void DShow(const char *format_str, ...);

/**
 * @brief Функция вывода информации об ошибках при отладке в файл.
 * @param [in] format_str – строка для вывода.
 */
void DShowError ( const char *format_str, ... );

/**
 * @brief Функция вывода релизной информации в файл.
 * @param [in] format_str – строка для вывода.
 */
void RShow(const char *format_str, ...);

/**
 * @brief Функция вывода информации об ошибках в релизе в файл.
 * @param [in] format_str – строка для вывода.
 */
void RShowError ( const char *format_str, ... );

#endif /* DEBUG_H */

