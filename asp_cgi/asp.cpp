#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <inttypes.h>
#include <string>
#include <postgresql/libpq-fe.h>
#include <json/json.h>

#include <sys/un.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <errno.h>
#include <cstring> //strlen

#include <math.h> //round

#include <libconfig.h>

#include "baedb_defines.h"

#define CFG_FILE                "/usr/local/ea/altair/config.cfg"       /*!<\brief Путь до конфигурационного файла */

#define ASP_SOCKET              "/usr/local/ea/altair/cgi/asp.sock"
#define TMP_SOCKET              "/usr/local/ea/altair/cgi/XXXXXX"
#define TMP_SOCKET_LEN          32

uint8_t return_success () {
    json_object * jobj = json_object_new_object();
    
    json_object *jboolean = json_object_new_boolean(1);
    json_object_object_add(jobj,"success", jboolean);

    printf ("%s",json_object_to_json_string(jobj));
    return (EXIT_SUCCESS);
}

uint8_t return_error (uint8_t code) {
    json_object * jobj = json_object_new_object();
    
    json_object *jboolean = json_object_new_boolean(0);   
    json_object_object_add(jobj,"success", jboolean);
    
    json_object *jarray = json_object_new_object();
    json_object *jint = json_object_new_int(code);
    json_object_object_add(jarray,"code", jint);
    json_object *jstring = 0;
    switch (code) {
        case 1:
            jstring = json_object_new_string("Ошибка чтения конфигурационного файла!");
            break;
        case 2:
            jstring = json_object_new_string("Невозможно подключиться к БД!");
            break;
        case 3:
            jstring = json_object_new_string("Не удалось распознать входные данные!");
            break;
        case 4:
            jstring = json_object_new_string("Нераспознанный метод!");
            break;
        case 5:
            jstring = json_object_new_string("Нераспознанное действие!");
            break;
        case 6:
            jstring = json_object_new_string("Не удалось забиндить сокет!");
            break;
        case 7:
            jstring = json_object_new_string("Сервис взаимодействия с АСП не запущен!");
            break;
        case 8:
            jstring = json_object_new_string("Превышено ожидание ответа!");
            break;
        case 9:
            jstring = json_object_new_string("Отказ исполнения");
            break;
            
        default:
            jstring = json_object_new_string("Неизвестная ошибка!");
            break;
    }
    
    json_object_object_add(jarray,"message", jstring);
    json_object_object_add(jobj,"error", jarray);
        
    printf ("%s",json_object_to_json_string(jobj));
    return (EXIT_FAILURE);
}

int socket_work (int action) {
    struct sockaddr_un server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, ASP_SOCKET, 104); // XXX: should be limited to about 104 characters, system dependent

    char sock_name[TMP_SOCKET_LEN] = TMP_SOCKET;
    mktemp(sock_name);

    struct sockaddr_un client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, sock_name, 104);
    
    umask(0);

    //printf("Opening socket: %s\n", client_addr.sun_path);

    int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);

    if (bind(sockfd, (struct sockaddr *) &client_addr, sizeof(client_addr)) != 0) { 
        return 6;
    }

    char cmd_buf[2] = {0};
    cmd_buf[0] = action;

    if (sendto(sockfd, cmd_buf, strlen(cmd_buf), 0, (struct sockaddr *) &server_addr, sizeof(server_addr)) != strlen(cmd_buf)) {
        close(sockfd);
        unlink(sock_name);
        return 7;
    }

    char buf[100] = {0};
    int timeout = 30;

    while (timeout) {
        if(recv(sockfd, buf, sizeof(buf), MSG_DONTWAIT) != -1) {
            if (buf[0] != 0) {
                close(sockfd);
                unlink(sock_name);
                return 9;
            }
            close(sockfd);
            unlink(sock_name);
            return 0;
        }
        
        timeout--;
        struct timespec ts = { .tv_sec = 0, .tv_nsec = 100 * 1000 * 1000};
        nanosleep(&ts, NULL);
    }

    close(sockfd);
    unlink(sock_name);
    return 8;
}

float db_asp_select (PGconn *conn, int eps_charact_id) {
    PGresult *res;
    double value = 0;
    
    char eps_block_type_id_buf[3] = {0};
    snprintf(eps_block_type_id_buf, sizeof(eps_block_type_id_buf), "%d", DB_ASP_ID);
    char eps_block_num_buf[2] = {0};
    snprintf(eps_block_num_buf, sizeof(eps_block_num_buf), "%d", 1);
    char eps_charact_id_buf[4] = {0};
    snprintf(eps_charact_id_buf, sizeof(eps_charact_id_buf), "%d", eps_charact_id);
    
    std::string query = "SELECT eps_charact_value FROM table_eps_characts WHERE eps_id = 1 and eps_block_id = (SELECT eps_block_id FROM table_list_eps_blocks WHERE eps_block_type_id = '";
    query += eps_block_type_id_buf;
    query += "' and eps_block_num = '";
    query += eps_block_num_buf;
    query += "') and eps_charact_id = '";
    query += eps_charact_id_buf;
    query += "'";
    
    res = PQexec(conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        return value;
    }
    
    value = atof(PQgetvalue(res, 0, 0));
    
    PQclear(res);
    return value;
}

void asp_led_state (PGconn *conn, json_object *led) {
    int norm_state = db_asp_select(conn, CHARACT_ASP_status) != STATUS_UNAVAILABLE ? 1 : 0;
    
    int oper_fault = db_asp_select(conn, CHARACT_ASP_oper_fault);
    int oper_warning = db_asp_select(conn, CHARACT_ASP_oper_warning);
    int control_fault = db_asp_select(conn, CHARACT_ASP_control_fault);
    int control_warning = db_asp_select(conn, CHARACT_ASP_control_warning);
    int agregat_fault = db_asp_select(conn, CHARACT_ASP_agregat_fault);
    int agregat_warning = db_asp_select(conn, CHARACT_ASP_agregat_warning);
    
    int fault_state = (oper_fault + oper_warning + control_fault + control_warning + agregat_fault + agregat_warning) > 0 ? 2 : 0;
    
    int oper_fire = db_asp_select(conn, CHARACT_ASP_oper_fire);
    int control_fire = db_asp_select(conn, CHARACT_ASP_control_fire);
    int agregat_fire = db_asp_select(conn, CHARACT_ASP_agregat_fire);
    
    int fire_state = (oper_fire + control_fire + agregat_fire) > 0 ? 2 : 0;
    
    int avt_otkl_1_state = 0;
    int avt_otkl_2_state = db_asp_select(conn, CHARACT_ASP_oper_auto_off);
    int avt_otkl_3_state = db_asp_select(conn, CHARACT_ASP_control_auto_off);
    int avt_otkl_4_state = db_asp_select(conn, CHARACT_ASP_agregat_auto_off);
    int avt_otkl_5_state = 0;
    
    int fire_1_state = 0;
    int fire_2_state = db_asp_select(conn, CHARACT_ASP_oper_fire) > 0 ? 2 : 0;
    int fire_3_state = db_asp_select(conn, CHARACT_ASP_control_fire) > 0 ? 2 : 0;
    int fire_4_state = db_asp_select(conn, CHARACT_ASP_agregat_fire) > 0 ? 2 : 0;
    int fire_5_state = 0;
    
    int vkl_state = db_asp_select(conn, CHARACT_ASP_status) != STATUS_UNAVAILABLE ? 1 : 0;
    
    json_object *norm = json_object_new_int(norm_state);
    json_object_object_add(led, "norm", norm);
    json_object *fault = json_object_new_int(fault_state);
    json_object_object_add(led, "fault", fault);
    json_object *fire = json_object_new_int(fire_state);
    json_object_object_add(led, "fire", fire);
    json_object *avt_otkl_1 = json_object_new_int(avt_otkl_1_state);
    json_object_object_add(led, "avt_otkl_1", avt_otkl_1);
    json_object *avt_otkl_2 = json_object_new_int(avt_otkl_2_state);
    json_object_object_add(led, "avt_otkl_2", avt_otkl_2);
    json_object *avt_otkl_3 = json_object_new_int(avt_otkl_3_state);
    json_object_object_add(led, "avt_otkl_3", avt_otkl_3);
    json_object *avt_otkl_4 = json_object_new_int(avt_otkl_4_state);
    json_object_object_add(led, "avt_otkl_4", avt_otkl_4);
    json_object *avt_otkl_5 = json_object_new_int(avt_otkl_5_state);
    json_object_object_add(led, "avt_otkl_5", avt_otkl_5);
    json_object *fire_1 = json_object_new_int(fire_1_state);
    json_object_object_add(led, "fire_1", fire_1);
    json_object *fire_2 = json_object_new_int(fire_2_state);
    json_object_object_add(led, "fire_2", fire_2);
    json_object *fire_3 = json_object_new_int(fire_3_state);
    json_object_object_add(led, "fire_3", fire_3);
    json_object *fire_4 = json_object_new_int(fire_4_state);
    json_object_object_add(led, "fire_4", fire_4);
    json_object *fire_5 = json_object_new_int(fire_5_state);
    json_object_object_add(led, "fire_5", fire_5);
    json_object *vkl = json_object_new_int(vkl_state);
    json_object_object_add(led, "vkl", vkl);
}

void asp_diag_state(PGconn *conn, json_object *diag) {
    int oper_fault_state = db_asp_select(conn, CHARACT_ASP_oper_fault);
    int oper_warning_state = db_asp_select(conn, CHARACT_ASP_oper_warning);
    int oper_fire_state = db_asp_select(conn, CHARACT_ASP_oper_fire);
    int oper_manual_state = db_asp_select(conn, CHARACT_ASP_oper_manual);
    int oper_all_extinguishers_state = db_asp_select(conn, CHARACT_ASP_oper_all_extinguishers);
    int oper_auto_off_state = db_asp_select(conn, CHARACT_ASP_oper_auto_off);
    int oper_extinguishing_state = db_asp_select(conn, CHARACT_ASP_oper_extinguishing);
    int oper_extinguish_ended_state = db_asp_select(conn, CHARACT_ASP_oper_extinguish_ended);
    int oper_extinguish_impossible_state = db_asp_select(conn, CHARACT_ASP_oper_extinguish_impossible);
    
    int control_fault_state = db_asp_select(conn, CHARACT_ASP_control_fault);
    int control_warning_state = db_asp_select(conn, CHARACT_ASP_control_warning);
    int control_fire_state = db_asp_select(conn, CHARACT_ASP_control_fire);
    int control_manual_state = db_asp_select(conn, CHARACT_ASP_control_manual);
    int control_all_extinguishers_state = db_asp_select(conn, CHARACT_ASP_control_all_extinguishers);
    int control_auto_off_state = db_asp_select(conn, CHARACT_ASP_control_auto_off);
    int control_extinguishing_state = db_asp_select(conn, CHARACT_ASP_control_extinguishing);
    int control_extinguish_ended_state = db_asp_select(conn, CHARACT_ASP_control_extinguish_ended);
    int control_extinguish_impossible_state = db_asp_select(conn, CHARACT_ASP_control_extinguish_impossible);
    
    int agregat_fault_state = db_asp_select(conn, CHARACT_ASP_agregat_fault);
    int agregat_warning_state = db_asp_select(conn, CHARACT_ASP_agregat_warning);
    int agregat_fire_state = db_asp_select(conn, CHARACT_ASP_agregat_fire);
    int agregat_manual_state = db_asp_select(conn, CHARACT_ASP_agregat_manual);
    int agregat_all_extinguishers_state = db_asp_select(conn, CHARACT_ASP_agregat_all_extinguishers);
    int agregat_auto_off_state = db_asp_select(conn, CHARACT_ASP_agregat_auto_off);
    int agregat_extinguishing_state = db_asp_select(conn, CHARACT_ASP_agregat_extinguishing);
    int agregat_extinguish_ended_state = db_asp_select(conn, CHARACT_ASP_agregat_extinguish_ended);
    int agregat_extinguish_impossible_state = db_asp_select(conn, CHARACT_ASP_agregat_extinguish_impossible);

    json_object *o_fault = json_object_new_boolean(oper_fault_state);
    json_object_object_add(diag, "o_fault", o_fault);
    json_object *o_warning = json_object_new_boolean(oper_warning_state);
    json_object_object_add(diag, "o_warning", o_warning);
    json_object *o_fire = json_object_new_boolean(oper_fire_state);
    json_object_object_add(diag, "o_fire", o_fire);
    json_object *o_manual = json_object_new_boolean(oper_manual_state);
    json_object_object_add(diag, "o_manual", o_manual);
    json_object *o_all_ext_state = json_object_new_boolean(oper_all_extinguishers_state);
    json_object_object_add(diag, "o_all_ext_state", o_all_ext_state);
    json_object *o_avto_off = json_object_new_boolean(oper_auto_off_state);
    json_object_object_add(diag, "o_avto_off", o_avto_off);
    json_object *o_ext = json_object_new_boolean(oper_extinguishing_state);
    json_object_object_add(diag, "o_ext", o_ext);
    json_object *o_ext_end = json_object_new_boolean(oper_extinguish_ended_state);
    json_object_object_add(diag, "o_ext_end", o_ext_end);
    json_object *o_ext_impossible = json_object_new_boolean(oper_extinguish_impossible_state);
    json_object_object_add(diag, "o_ext_impossible", o_ext_impossible);
    json_object *c_fault = json_object_new_boolean(control_fault_state);
    json_object_object_add(diag, "c_fault", c_fault);
    json_object *c_warning = json_object_new_boolean(control_warning_state);
    json_object_object_add(diag, "c_warning", c_warning);
    json_object *c_fire = json_object_new_boolean(control_fire_state);
    json_object_object_add(diag, "c_fire", c_fire);
    json_object *c_manual = json_object_new_boolean(control_manual_state);
    json_object_object_add(diag, "c_manual", c_manual);
    json_object *c_all_ext_state = json_object_new_boolean(control_all_extinguishers_state);
    json_object_object_add(diag, "c_all_ext_state", c_all_ext_state);
    json_object *c_avto_off = json_object_new_boolean(control_auto_off_state);
    json_object_object_add(diag, "c_avto_off", c_avto_off);
    json_object *c_ext = json_object_new_boolean(control_extinguishing_state);
    json_object_object_add(diag, "c_ext", c_ext);
    json_object *c_ext_end = json_object_new_boolean(control_extinguish_ended_state);
    json_object_object_add(diag, "c_ext_end", c_ext_end);
    json_object *c_ext_impossible = json_object_new_boolean(control_extinguish_impossible_state);
    json_object_object_add(diag, "c_ext_impossible", c_ext_impossible);
    json_object *a_fault = json_object_new_boolean(agregat_fault_state);
    json_object_object_add(diag, "a_fault", a_fault);
    json_object *a_warning = json_object_new_boolean(agregat_warning_state);
    json_object_object_add(diag, "a_warning", a_warning);
    json_object *a_fire = json_object_new_boolean(agregat_fire_state);
    json_object_object_add(diag, "a_fire", a_fire);
    json_object *a_manual = json_object_new_boolean(agregat_manual_state);
    json_object_object_add(diag, "a_manual", a_manual);
    json_object *a_all_ext_state = json_object_new_boolean(agregat_all_extinguishers_state);
    json_object_object_add(diag, "a_all_ext_state", a_all_ext_state);
    json_object *a_avto_off = json_object_new_boolean(agregat_auto_off_state);
    json_object_object_add(diag, "a_avto_off", a_avto_off);
    json_object *a_ext = json_object_new_boolean(agregat_extinguishing_state);
    json_object_object_add(diag, "a_ext", a_ext);
    json_object *a_ext_end = json_object_new_boolean(agregat_extinguish_ended_state);
    json_object_object_add(diag, "a_ext_end", a_ext_end);
    json_object *a_ext_impossible = json_object_new_boolean(agregat_extinguish_impossible_state);
    json_object_object_add(diag, "a_ext_impossible", a_ext_impossible);
}

int main(int argc, char** argv) {  
    printf("Content-type: text/html; charset=utf-8\n\n");  //выводим хедер для правильной обработки
    
    config_t cfg;
    const char *tmp_str;
    config_init(&cfg);
    
    char bd_user[16];
    char bd_pass[16];
    char bd_name[16];
    
    if(! config_read_file(&cfg, CFG_FILE)) {
        config_destroy(&cfg);
        return (return_error(1));
    }
    if (config_lookup_string(&cfg, "bd_user", &tmp_str)) {
        snprintf(bd_user, 16, "%s", tmp_str);
    }
    if (config_lookup_string(&cfg, "bd_pass", &tmp_str)) {
        snprintf(bd_pass, 16, "%s", tmp_str);
    }
    if (config_lookup_string(&cfg, "bd_name", &tmp_str)) {
        snprintf(bd_name, 16, "%s", tmp_str);
    }
    config_destroy(&cfg);
    
    char pg_conn_str[512];
    snprintf (pg_conn_str, 512, "user=%s password=%s host=localhost dbname=%s", bd_user, bd_pass, bd_name);
    
    //Проверка возможности подключения к БД
    PGconn *conn;
    conn = PQconnectdb(pg_conn_str);
    if (PQstatus(conn) == CONNECTION_BAD) {
        return (return_error(2));
    }
    
    char *qs = getenv("QUERY_STRING");
    
    if (NULL==qs) {
        //Завершение работы с БД.
        PQfinish(conn); 
        
        return (return_error(3));
    }
    
    uint8_t method=0xff;
    
    sscanf(qs, "method=%hhu&", &method);
    
    if (method==1) { //опрос АСП 
        uint8_t action=0xff;

        sscanf(qs, "method=%hhu&action=%hhu", &method, &action);
        
        if (action == 1) {
             json_object *jobj = json_object_new_object();

             json_object *led = json_object_new_object();
             asp_led_state(conn, led);
             json_object_object_add(jobj, "led", led);

             printf ("%s",json_object_to_json_string(jobj));

            //Завершение работы с БД.
             PQfinish(conn); 
             return (EXIT_SUCCESS);
         } else if (action == 2) {
             json_object *jobj = json_object_new_object();

             json_object *diag = json_object_new_object();
             asp_diag_state(conn, diag);
             json_object_object_add(jobj, "diag", diag);

             printf ("%s",json_object_to_json_string(jobj));

            //Завершение работы с БД.
             PQfinish(conn); 
             return (EXIT_SUCCESS);
         }

         //Завершение работы с БД.
         PQfinish(conn); 
         return (return_error(5));
    } else if (method==2) { // управление АСП
        uint8_t action=0xff;

        sscanf(qs, "method=%hhu&action=%hhu", &method, &action);
        
        if (action > 0 && action < 12) {
            int result = socket_work(action);

            if (result) {
                //Завершение работы с БД.
                PQfinish(conn); 
                return (return_error(result));
            }

            //Завершение работы с БД.
            PQfinish(conn); 
            return (return_success());
        }
        //Завершение работы с БД.
        PQfinish(conn); 
        return (return_error(5));
    }

    //Завершение работы с БД.
    PQfinish(conn); 
    return (return_error(4));
}

