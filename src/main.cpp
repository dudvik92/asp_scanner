/**@file main.cpp
 * \brief Опросчик АСПТ
 * 
 * \details Производит периодический опрос состояния АСПТ через порт RS-485
 * \author Василий Елькин
 */
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/time.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <errno.h>
#include <postgresql/libpq-fe.h>
#include <libconfig.h>

#include <termios.h>

#include "baedb_defines.h"

#include "asp_protocol.h"
#include "asp.h"
#include "asp_print.h"
#include "asp_status.h"

#include "debug.h"

#define VERSION_MAJOR       1
#define VERSION_MINOR       1

#define CYCLE_TIME          2

#define ASP_SOCKET          "/usr/local/ea/altair/cgi/asp.sock"

#define CFG_FILE            "/usr/local/ea/altair/config.cfg"         /*!<\brief Путь до конфигурационного файла */
#define PID_FILE            "/var/run/asp_scanner.pid"
#define LOG_FILE            (char *)"/usr/local/ea/altair/logs/asp_scanner.log"     /**<@brief Путь до лог-файла */

#define CYCLE_TIME          2 //минимальное время цикла

using namespace std;

uint8_t run = 1;

uint8_t surv_dir[] = {ALL_ASP, OPERATOR_DIRECTION, CONTROL_DIRECTION, AGREGAT_DIRECTION};

void signal_handler(int signal) {
    switch(signal) {
        case SIGINT:
        case SIGKILL:
        case SIGTERM:
            run = 0;
            DShow("\nОстанов!\n");
            break;
        case SIGSEGV:
            exit(EXIT_FAILURE);
    }
}

int do_sock_work(int sockfd, struct_asp_params *asp_str, const char *asp_device) {
    int flag = 0; // Флаг отправки команды
    char buf[100];
    struct sockaddr_un from;
    socklen_t fromlen = sizeof(struct sockaddr_un);
    
    if (int cmd_len = recvfrom(sockfd, buf, sizeof(buf), MSG_DONTWAIT, ((struct sockaddr *)&from), &fromlen) != -1) {
        uint8_t tx[20] = {0};        
        DShow("Команда от: %s длиной %d\n", (&from)->sun_path, cmd_len);
        for (int i = 0; i < cmd_len; i++) {
            switch (buf[i]) {
                case 1:
                    DShow("\tКоманда не обрабатывается\n");
                    break;
                case 2:
                    DShow("\tна отключение/включение автоматики 2\n");
                    if (asp_str->operator_dir.auto_off_dir) {
                        gener_req(AUTO_OFF, OPERATOR_DIRECTION, tx, 0x00);
                        asp_send_request(asp_device, tx, sizeof(tx));
                    } else {
                        gener_req(AUTO_OFF, OPERATOR_DIRECTION, tx);
                        asp_send_request(asp_device, tx, sizeof(tx));
                    }
                    flag++;
                    break;
                case 3:
                    DShow("\tна отключение/включение автоматики 3\n");
                    if (asp_str->control_dir.auto_off_dir){
                        gener_req(AUTO_OFF, CONTROL_DIRECTION, tx, 0x00);
                        asp_send_request(asp_device, tx, sizeof(tx));
                    } else {
                        gener_req(AUTO_OFF, CONTROL_DIRECTION, tx);
                        asp_send_request(asp_device, tx, sizeof(tx));
                    }  
                    flag++;                  
                    break;
                case 4:
                    DShow("\tна отключение/включение автоматики 4\n");
                    if (asp_str->agregat_dir.auto_off_dir) {
                        gener_req(AUTO_OFF, AGREGAT_DIRECTION, tx, 0x00);
                        asp_send_request(asp_device, tx, sizeof(tx));
                    } else {
                        gener_req(AUTO_OFF, AGREGAT_DIRECTION, tx);
                        asp_send_request(asp_device, tx, sizeof(tx));
                    }
                    flag++;
                    break;
                case 5:
                    DShow("\tКоманда не обрабатывается\n");
                    break;
                case 6:
                    DShow("\tКоманда не обрабатывается\n");
                    break;
                case 7:
                    DShow("\tна тушение пожара 2\n");
                    gener_req(START_EXTINGUESH, OPERATOR_DIRECTION, tx);
                    asp_send_request(asp_device, tx, sizeof(tx));
                    flag++;
                    break;
                case 8:
                    DShow("\tна тушение пожара 3\n");
                    gener_req(START_EXTINGUESH, CONTROL_DIRECTION, tx);
                    asp_send_request(asp_device, tx, sizeof(tx));
                    flag++;
                    break;
                case 9:
                    DShow("\tна тушение пожара 4\n");
                    gener_req(START_EXTINGUESH, AGREGAT_DIRECTION, tx);
                    asp_send_request(asp_device, tx, sizeof(tx));
                    flag++;
                    break;
                case 10:
                    DShow("\tКоманда не обрабатывается\n");
                    break;
                case 11:
                    DShow("\tна отмену\n");
                    gener_req(RESET_COMMAND, ALL_ASP, tx);
                    asp_send_request(asp_device, tx, sizeof(tx));
                    flag++;
                    break;
                
                default:
                    DShow("\tнеизвестная команда");
                    break;
            }
        }
        
        char answ = 0;

        if(int send_len = sendto(sockfd, &answ, sizeof(answ), 0, ((struct sockaddr *)&from), fromlen) != sizeof(answ)) {
            DShow("Не удалось отправить ответ! Код: %d\n", send_len);
        }

        memset(buf, 0, 100);
    }
    if (flag){
        return 0; // Была выполнена отправка команды
    } else {
        return 1; // Отправка команды не выполнялась
    }
}

int timeval_subtract ( struct timeval *result,  struct timeval *x,  struct timeval *y) {
    /* Perform the carry for the later subtraction by updating y. */
    if (x->tv_usec < y->tv_usec) {
        int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
        y->tv_usec -= 1000000 * nsec;
        y->tv_sec += nsec;
    }
    if (x->tv_usec - y->tv_usec > 1000000) {
        int nsec = (x->tv_usec - y->tv_usec) / 1000000;
        y->tv_usec += 1000000 * nsec;
        y->tv_sec -= nsec;
    }

    /* Compute the time remaining to wait.
    tv_usec is certainly positive. */
    result->tv_sec = x->tv_sec - y->tv_sec;
    result->tv_usec = x->tv_usec - y->tv_usec;

    /* Return 1 if result is negative. */
    return x->tv_sec < y->tv_sec;
}

/*!\brief Функция проверки того, что текущая копия программы - единственная запущенная.
 * \param [in] lock_fd - указатель на файловый дискриптор lock-файла
 * \return Файловый дескритор файла pid
 */
int set_lock() {
    int lock_fd = open(PID_FILE, O_RDWR|O_CREAT|O_TRUNC);
    
    if (flock(lock_fd, LOCK_EX|LOCK_NB) == -1) {
        cout << "Приложение уже запущено или недостаточно привилегий!" << endl;
        exit(1);
    }
          
    dprintf(lock_fd, "%d", getpid());
    
    return lock_fd;
}

/*!\brief Функция освобождения lock-файла.
 * \param [in] lock_fd - файловый дискриптор lock-файла
 * \return none
 */
void free_lock(int lock_fd) {
    close(lock_fd);
    remove(PID_FILE);
}

/**
 * @brief Функция демонизации приложения
 * 
 * @return Код ошибки - 0 -  если все хорошо
 */
int demonization() {
    pid_t process_id = 0;
    pid_t sid = 0;

    process_id = fork();
    
    if (process_id < 0) {
        cout << "Не удалось сделать форк!" << endl;
        exit(1);
    }
    
    if (process_id > 0) {
        exit(0);
    }
    
    umask(0);
    
    sid = setsid();
    if(sid < 0) {
        exit(1);
    }
    
    chdir("/");
    
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    open("/dev/null", O_RDWR);
    dup2(STDIN_FILENO, STDOUT_FILENO);
    dup2(STDIN_FILENO, STDERR_FILENO);

    return 0;
}

int main(int argc, char** argv) {
    signal(SIGINT, signal_handler);
    signal(SIGKILL, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGSEGV, signal_handler);
    
    set_log_file(LOG_FILE);
    
    int lock_fd = 0;            /**<@brief Переменная дескриптора, где хранится PID процесса */

    if (argc > 1) {
        if (argc > 2) {
            printf("Недопустимо использование более одного аргумента!\n");
            return 1;
        } else {
            if (!strcmp (argv[1], "-h")) {
                printf("Опросчик АСПТ по RS-485\n\t-h - показать эту страницу;\n\t-v - версия программы;\n\t-d - запустить как консольное приложение с выводом отладочной информации;\nЗапуск программы на исполнение в штатном ржиме осуществляется без параметров.\n\n");
                return 0;
            } else if (!strcmp (argv[1], "-v")) {
                printf("Версия программы - %d.%d\n\r", VERSION_MAJOR, VERSION_MINOR);
                return 0;
            } else if (strcmp(argv[1], "-d") == 0) {
                lock_fd = set_lock();
                printf("Включено отображение отладочных сообщений\n");
                show_debug_messages();
            } else {
                printf("Неверный аргумент!Для справки используйте -h!\n");
                return 1;
            } 
        }
    } else {
        demonization();
        lock_fd = set_lock();
    }
    
    config_t cfg;
    const char *tmp_str;
    config_init(&cfg);
    
    char bd_user[16];
    char bd_pass[16];
    char bd_name[16];
    char asp_device[16];
    
    if(!config_read_file(&cfg, CFG_FILE)) {
        RShow("Проблема чтения конфигурационного файл: %s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return -1;
    }
    if (config_lookup_string(&cfg, "bd_user", &tmp_str)) {
        snprintf(bd_user, 16, "%s", tmp_str);
        DShow ("bd_user: %s\n", bd_user);
    }
    if (config_lookup_string(&cfg, "bd_pass", &tmp_str)) {
        snprintf(bd_pass, 16, "%s", tmp_str);
        DShow ("bd_pass: %s\n", bd_pass);
    }
    if (config_lookup_string(&cfg, "bd_name", &tmp_str)) {
        snprintf(bd_name, 16, "%s", tmp_str);
        DShow ("bd_name: %s\n", bd_name);
    }
    if (config_lookup_string(&cfg, "asp_device", &tmp_str)) {
        snprintf(asp_device, 16, "%s", tmp_str);
        DShow ("asp_device: %s\n", asp_device);
    }
    config_destroy(&cfg);
    
    char pg_conn_str[512];              /*!<\brief Строка подключения к БД */
    
    snprintf (pg_conn_str, 512, "user=%s password=%s host=localhost dbname=%s", bd_user, bd_pass, bd_name);
    DShow("Строка подключения к БД: %s\n", pg_conn_str);
    
    int asp_con = asp_connect(asp_device);    
    while (asp_con == 0 && run) {
        RShow("Ошибка выполнения asp_connect!\n");
        
        struct timespec ts = { .tv_sec = CYCLE_TIME, .tv_nsec = 0};
        nanosleep(&ts, NULL);

        asp_con = asp_connect(asp_device);
    }
    
    //Подключение к БД
    PGconn *conn = PQconnectdb(pg_conn_str);
    if (PQstatus(conn) == CONNECTION_BAD) {
        RShow("Не удается подключиться к базе данных!\n");
        exit(-1);
    }
    
    uint8_t asp_count = asp_get_count(conn);

    struct_asp_params *asp = (struct_asp_params*) calloc(asp_count, sizeof(struct_asp_params));

    asp_struct_init(conn, asp, asp_count);
    
    PQfinish(conn);
    
    struct sockaddr_un server_addr;

    int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    
    //Подготовка сокета
    memset(&server_addr, 0, sizeof(server_addr)); 
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, ASP_SOCKET, 104);
    
    umask(0);
    
    remove(ASP_SOCKET);

    if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
        RShow("Не удалось забиндить сокет: %s\n", strerror(errno));
        run=0;
    }
   
    while(run) {
        struct timeval starttime, endtime, difftime;
        gettimeofday(&starttime, 0);
        struct timespec wait_answ = { .tv_sec = 0, .tv_nsec = 400 * 1000 * 1000}; 
        
        //Подключение к БД
        PGconn *conn = PQconnectdb(pg_conn_str);
        if (PQstatus(conn) == CONNECTION_BAD) {
            RShow("Не удается подключиться к базе данных!\n");
            exit(-1);
        }
        
        set_asp_status_unavailable(asp); // Устанавливаем статус АСП: недоступен
        
        for(uint8_t i = 0; i < sizeof(surv_dir); i++) { // Отправка запросов к АСП по направлениям
            int fd = -1;
            
            uint8_t tx[20] = {0};    // Подготовка массива для передачи
            
            // Проверка наличия команд для отправки
            if (!do_sock_work(sockfd, asp, asp_device)){ // Проверка выполненной отправки команды изменения состояния АСП
                nanosleep(&wait_answ, NULL);
            }
            
            gener_req(STATE, surv_dir[i], tx); // Формирование запроса
            fd = asp_send_request(asp_device, tx, sizeof(tx)); // отправка запроса
            nanosleep(&wait_answ, NULL);
            
            uint8_t rx[64] = {0};    // Подготовка массива для приема 
            if ((fd > 0) && asp_read_answer(rx, sizeof(rx), fd)) {// если ответ есть и пройдена проверка контрольной суммы
                set_asp_status_ok(asp);
                asp_response(rx, asp); // обработка ответа
                DShow("Статус АСП - %d (прием ответа по направлению %d)\n", asp->status, surv_dir[i]);
            } else {
                DShow("Статус АСП - %d (неудача приема ответа по направлению %d)\n", asp->status, surv_dir[i]);
                continue;
            }
        }
        
        // Вывод отладночной информации о состоянии направлений пожаротушения
        asp_print_struct(asp->operator_dir); 
        asp_print_struct(asp->control_dir);
        asp_print_struct(asp->agregat_dir);
        
        asp_update_db(conn, asp);  // Обновление значений в базе данных

        PQfinish(conn);  
                        
        do {
            gettimeofday(&endtime, 0);
            timeval_subtract(&difftime, &endtime, &starttime);

            struct timespec ts = { .tv_sec = 0, .tv_nsec = 10 * 1000 * 1000};
            nanosleep(&ts, NULL);
        } while ((difftime.tv_sec<CYCLE_TIME) && run);  
        DShow("Время цикла: %ld.%06ld\n", difftime.tv_sec, difftime.tv_usec);
    }
    
    //Завершение работы с сокетом
    close(sockfd);
    unlink(ASP_SOCKET);

    free_lock(lock_fd);
    return 0;
}
