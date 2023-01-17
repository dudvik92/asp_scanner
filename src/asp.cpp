#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <termios.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include "asp.h"
#include "db.h"
#include "asp_protocol.h"

#include "debug.h"
#include "asp_status.h"

#include "baedb_defines.h"

/*------CRC8-----*/
#define POLY 0x8c
#define INI 0xff
/*---------------*/

using namespace std;

uint8_t crc8(uint8_t *mas, uint8_t len) {   
    uint8_t dat, crc, fb, st_byt;
    st_byt = 0; crc = INI;
    do {
        dat = mas[st_byt];
        for(uint8_t i = 0; i < 8; i++) {  // счетчик битов в байте
            fb = crc ^ dat;
            fb &= 1;
            crc >>= 1;
            dat >>= 1;
            if( fb == 1 ) crc ^= POLY; // полином
        }
        st_byt++;
    } while( st_byt < len ); // счетчик байтов в массиве
  return crc;
}

uint8_t asp_get_count(PGconn *conn) {
    uint8_t device_count = 0;
    PGresult *res;

    char device_type_buf[DB_ID_LEN] = {0};
    snprintf(device_type_buf, sizeof (device_type_buf), "%d", DB_ASP_ID);

    string query = "SELECT count(*) FROM table_list_eps_blocks WHERE eps_block_type_id ='";
    query += device_type_buf;
    query += "'";

    res = PQexec(conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        RShow("Не удалось вычитать число блоков с типом: %d!\n", DB_MDS_ID);
    }

    device_count = atoi(PQgetvalue(res, 0, 0));

    PQclear(res);

    return device_count;
}

void asp_struct_init(PGconn *conn, struct_asp_params *asp, int asp_count) {
    PGresult *res;

    char device_type_buf[DB_ID_LEN] = {0};
    snprintf(device_type_buf, sizeof (device_type_buf), "%d", DB_ASP_ID);

    string query = "SELECT eps_block_id, eps_block_addr, eps_block_num FROM table_list_eps_blocks WHERE eps_block_type_id ='";
    query += device_type_buf;
    query += "' ORDER BY eps_block_num";

    res = PQexec(conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        RShow("Не удалось вычитать адрес АСП!\n");
    }

    for (int i = 0; i < asp_count; i++) {
        asp[i].id = atoi(PQgetvalue(res, i, 0));

        asp[i].status = STATUS_UNAVAILABLE;
    }

    PQclear(res);
}

uint8_t asp_connect(const char * dev_name) {
    //read and write in sync mode
    int fd = open(dev_name, O_RDWR | O_NOCTTY);
    if(fd < 0) {
        RShow("open device \"%s\" error: %d\n", dev_name, fd);
        return 0; // возвращаем флаг об неудачной инициализации порта
    }
 
    struct termios port_settings;
    bzero(&port_settings, sizeof(port_settings));
    //
    port_settings.c_cflag |= CREAD;
    port_settings.c_cflag |= CLOCAL;
    //
    port_settings.c_cc[VMIN] = 100;
    //delay, x0.2 sec
    port_settings.c_cc[VTIME] = 2;
    //flush serial port
    int fres = tcflush(fd, TCIFLUSH);
    if (fres < 0) {
        RShow("tcflush() error %d\n", fres);
        close(fd);
        return 0;
    }
    //set baud rate
    fres = cfsetispeed(&port_settings, B4800);
    if (fres < 0) {
        RShow("cfsetispeed() error %d\n", fres);
        close(fd);
        return 0;
    }
    
    fres = cfsetospeed(&port_settings, B4800);
    if (fres < 0) {
        RShow("cfsetospeed() error %d\n", fres);
        close(fd);
        return 0;
    }
    //set character size: 8.
    port_settings.c_cflag &= ~CSIZE;
    port_settings.c_cflag |= CS8;
    //set flow cotrol: none
    port_settings.c_cflag &= ~(CRTSCTS);
    //set parity: none
    port_settings.c_cflag &= ~(PARENB);
    port_settings.c_iflag |= IGNPAR;
    //set stop bits: 1
    port_settings.c_cflag &= ~(CSTOPB);
    //apply port settings
    fres = tcsetattr(fd, TCSANOW, &port_settings);
    if (fres < 0) {
        RShow("tcsetattr() error %d\n", fres);
        close(fd);
        return 0;
    }
    close(fd);
    return 1; // возвращаем флаг об успешной инициализации порта
}

int asp_send_request(const char * dev_name, uint8_t *tx_buffer, uint8_t tx_buffer_len) {
    uint8_t crcBuf[7] = {0};
    for(uint8_t i = 0; i < sizeof(crcBuf); i++) 
    {
            crcBuf[i] = tx_buffer[i+10]; // запись типа сообщения, типа изделия и текста сообщения в буфер для вычисления crc
    }
    tx_buffer[REQUEST_CRC8_BYTE_INDEX] = crc8(crcBuf, sizeof(crcBuf)); // установка контрольной суммы

    int fd = open(dev_name, O_RDWR | O_NONBLOCK | O_NOCTTY | O_NDELAY);
    
    if (fd < 0) {
        RShow("Запрос: open port error: no such file or directory\n");
    } else {
        int err = write(fd, tx_buffer, tx_buffer_len);

        if(err < 0) {
            RShow("Запрос: ошибка записи\n");
        } 
    }
    return fd;
}

uint8_t asp_read_answer(uint8_t *rx_buffer, uint8_t rx_buffer_len, uint8_t fd) {
    if (fd >= 0) { // если дескриптор файла верный, то...         
        uint8_t answer_crc8_byte_index2 = 0;
        uint8_t start_mes_byte = 0; // Переменная начала текста сообщения из ответа АСП
        uint8_t stop_mes_byte = 0; // Переменная конца текста сообщения из ответа АСП
        
        int res = read(fd, rx_buffer, rx_buffer_len); 
     
        if( res < 0) {
            RShow("Ответ: ошибка чтения\n");
            close(fd);
            return 0; // неудача чтения
        } else if (res == 0) {
            RShow("Ответ: нет ответа\n");
            close(fd);
            return 0; // неудача чтения
        }  
        
        // Вычисление длины сообщения
        for (int i = 0; i < rx_buffer_len; i++) {
            if ((rx_buffer[i] == 0x10) && (rx_buffer[i + 1] == 0x01) && !start_mes_byte) {
                start_mes_byte = i + 2;
            }
            if (rx_buffer[i] == 0x10 && rx_buffer[i + 1] == 0x26 && !stop_mes_byte) {
                stop_mes_byte = i - 2;
                answer_crc8_byte_index2 = i - 1;
                break;
            }
        }
        
        uint8_t len_crc_buf = stop_mes_byte - start_mes_byte + 1; // Переменная для длины текста сообщения, необходимого для подсчета CRC
        uint8_t * crc_buf = new uint8_t [len_crc_buf]; // промежуточный буфер для подсчета crc 
        
        for(int i = 0; i < len_crc_buf; i++) {// заполнение промежуточного буфера значениями из ответа
            crc_buf[i] = rx_buffer[i+start_mes_byte];
        }        

        if (rx_buffer[answer_crc8_byte_index2] != crc8(crc_buf, len_crc_buf)){  // проверка crc8 
            uint8_t count = 0;
            uint8_t crc_buf_v2[15] = {0}; // новый буфер из 15 элементов для подсчета CRC 
            
            for(uint8_t i = 0; i < len_crc_buf; i++) {// заполнение нового буфера, убирая задвоенныйе элементы 
                if ((crc_buf[i] == 0) || (crc_buf[i] == 0xff) || (crc_buf[i] != crc_buf[i+1])) {
                    crc_buf_v2[count] = crc_buf[i];
                    count++;
                }
                if (count > sizeof(crc_buf_v2)) break;
            }
            
            if (rx_buffer[answer_crc8_byte_index2] != crc8(crc_buf_v2, sizeof(crc_buf_v2))){
                RShow("Ответ: ошибка контрольной суммы\n");
                close(fd);
                return 0; // неудача чтения    
            } else {
                count = 0;
                for(int i = 0; i < rx_buffer_len; i++) {  // Изменям приемный буфер, убрав задвоенные байты 
                    if ((rx_buffer[i] == 0) || (rx_buffer[i] == 0xff) || (rx_buffer[i] != rx_buffer[i+1])) {
                        rx_buffer[count] = rx_buffer[i];
                        count++;
                    }
                }
            }
        }
        
        delete [] crc_buf;
        close(fd);
        return 1; // успех чтения
    } else {
        close(fd);
        RShow("Неверный дескриптор\n");
    }
    return 0; // неудача чтения
}

void asp_response(uint8_t *rx_buffer, struct_asp_params *asp) {	
    
    if (rx_buffer[DIRECTION_BYTE_INDEX] == ALL_ASP){

        if (rx_buffer[FAULT_ASP_BYTE] & FAULT_ASP_BIT){
            set_asp_status_warning(asp);
        }
        asp->operator_dir.fault = rx_buffer[FAULT_ASP_BYTE] & FAULT_OPERATOR_DIRECTION_BIT ? 1:0; 
        asp->agregat_dir.fault = rx_buffer[FAULT_ASP_BYTE] & FAULT_AGREGAT_DIRECTION_BIT ? 1:0;
        asp->control_dir.fault = rx_buffer[FAULT_ASP_BYTE] & FAULT_CONTROL_DIRECTION_BIT ? 1:0;
        
        //RShow("asp_str->operator_dir.fault=%d, agregat_dir.fault =%d, control_dir.fault =%d\n", asp->operator_dir.fault, asp->agregat_dir.fault, asp->control_dir.fault); // Тест статуса АСП
        if (asp->operator_dir.fault || asp->agregat_dir.fault || asp->control_dir.fault){
            RShow("По одному из направлений ПРЕДУПРЕЖДЕНИЕ!");
            set_asp_status_warning(asp);
        }

        asp->operator_dir.fire = rx_buffer[FIRE_ASP_BYTE] & FIRE_OPERATOR_DIRECTION_BIT ? 1:0; 
        asp->agregat_dir.fire = rx_buffer[FIRE_ASP_BYTE] & FIRE_AGREGAT_DIRECTION_BIT ? 1:0;
        asp->control_dir.fire = rx_buffer[FIRE_ASP_BYTE] & FIRE_CONTROL_DIRECTION_BIT ? 1:0;
        
        if (asp->operator_dir.fire || asp->agregat_dir.fire || asp->control_dir.fire){
            RShow("По одному из направлений ПОЖАР!");
            set_asp_status_error(asp);
        }

        asp->operator_dir.auto_off_dir = rx_buffer[AUTO_OFF_ASP_BYTE] & AUTO_OFF_OPERATOR_DIRECTION_BIT ? 1:0; 
        asp->agregat_dir.auto_off_dir = rx_buffer[AUTO_OFF_ASP_BYTE] & AUTO_OFF_AGREGAT_DIRECTION_BIT ? 1:0;
        asp->control_dir.auto_off_dir = rx_buffer[AUTO_OFF_ASP_BYTE] & AUTO_OFF_CONTROL_DIRECTION_BIT ? 1:0;
        
        if (asp->operator_dir.auto_off_dir || asp->agregat_dir.auto_off_dir || asp->control_dir.auto_off_dir){
            RShow("По одному из направлений ОТКЛЮЧЕНА АВТОМАТИКА!");
            set_asp_status_warning(asp);
        }

        asp->operator_dir.manual = rx_buffer[MANUAL_ASP_BYTE] & MANUAL_OPERATOR_DIRECTION_BIT ? 1:0; 
        asp->agregat_dir.manual = rx_buffer[MANUAL_ASP_BYTE] & MANUAL_AGREGAT_DIRECTION_BIT ? 1:0;
        asp->control_dir.manual = rx_buffer[MANUAL_ASP_BYTE] & MANUAL_CONTROL_DIRECTION_BIT ? 1:0;
        
        if (asp->operator_dir.manual || asp->agregat_dir.manual || asp->control_dir.manual){
            RShow("По одному из направлений РУЧНОЙ ЗАПУСК ПОЖАРОТУШЕНИЯ!");
            set_asp_status_error(asp);
        }        

        asp->operator_dir.all_extinguishers = rx_buffer[ALL_EXT_ASP_BYTE] & ALL_EXT_OPERATOR_DIRECTION_BIT ? 1:0; 
        asp->agregat_dir.all_extinguishers = rx_buffer[ALL_EXT_ASP_BYTE] & ALL_EXT_AGREGAT_DIRECTION_BIT ? 1:0;
        asp->control_dir.all_extinguishers = rx_buffer[ALL_EXT_ASP_BYTE] & ALL_EXT_CONTROL_DIRECTION_BIT ? 1:0;

        asp->operator_dir.warning = rx_buffer[ATTENTION_ASP_BYTE] & ATTENTION_OPERATOR_DIRECTION_BIT ? 1:0; 
        asp->agregat_dir.warning = rx_buffer[ATTENTION_ASP_BYTE] & ATTENTION_AGREGAT_DIRECTION_BIT ? 1:0;
        asp->control_dir.warning = rx_buffer[ATTENTION_ASP_BYTE] & ATTENTION_CONTROL_DIRECTION_BIT ? 1:0;
    } else {
        uint8_t ext_mod;            // Модуль тушения 0/1 исправен/неисправен
        uint8_t com_ext_mod;         // Связь с модулем тушения 0/1 исправен/неисправен
        uint8_t dotushivanie;      // Выполняется дотушивание 1/0 выполняется/не выполняется
        uint8_t quench_completed;   // Тушение завершено 0/1 тушение не завершено/тушение завершено 
        uint8_t ext_progress;       // Выполняется тушение 1/0 выполняется/ не выполняется 
        uint8_t fire_detected;      // Зафиксирован пожар 1/0  зафиксирован/не зафиксирован
        uint8_t attention_detected; // Зафиксировано состояние "Внимание" 1/0 зафиксировано/ не зафиксировано
        uint8_t ext_is_not_possible;  // Тушение невозможно 1/0 невозможно/возможно

        ext_mod                 = rx_buffer[EXT_MODULE_BYTE] & EXT_MOD_BIT              ? 1:0;
        com_ext_mod             = rx_buffer[EXT_MODULE_BYTE] & COM_EXT_MOD_BIT            ? 1:0;
        dotushivanie            = rx_buffer[EXT_MODULE_BYTE] & DOTUSH_BIT         ? 1:0;  
        quench_completed        = rx_buffer[EXT_MODULE_BYTE] & QUENCH_COMPLETED_BIT     ? 1:0;  
        ext_progress            = rx_buffer[EXT_MODULE_BYTE] & EXT_PROGRESS_BIT         ? 1:0;   
        fire_detected           = rx_buffer[EXT_MODULE_BYTE] & FIRE_DETECT_BIT        ? 1:0;   
        attention_detected      = rx_buffer[EXT_MODULE_BYTE] & ATTENTION_DETECT_BIT   ? 1:0;  
        ext_is_not_possible     = rx_buffer[EXT_MODULE_BYTE] & EXT_IS_NOT_POSSIBLE_BI  ? 1:0;


                    /*Байт состояния 2: линейный извещатель*/

        uint8_t li_result = 0;

        switch(rx_buffer[LI_DP_BYTE] >> LI_OFFSET & 0b00001111) {
            case LI_NORMAL:
                li_result = LI_NORMAL;
                break;

            case LI_ATTENTION1:
                li_result = LI_ATTENTION1;
                break;

            case LI_ATTENTION2:
                li_result = LI_ATTENTION1;
                break;

            case LI_ATTENTION3:
                li_result = LI_ATTENTION1;
                break;

            case LI_FIRE1:
                li_result = LI_FIRE;
                break;

            case LI_FIRE2:
                li_result = LI_FIRE;
                break;

            case LI_FIRE3:
                li_result = LI_FIRE;
                break;

            case LI_FIRE4:
                li_result = LI_FIRE;
                break;

            case GENERAL_FAULT:
                li_result = GENERAL_FAULT_RES;
                break;

            case CONNECT_BROKEN:
                li_result = CONNECT_BROKEN_RES;
                break;

            case LI_KZ:
                li_result = LI_KZ_RES;
                break;

            case LI_KZ_GND1:
                li_result = LI_KZ_GND_RES;
                break;

            case LI_KZ_GND2:
                li_result = LI_KZ_GND_RES;
                break;

            case LI_SENSOR_FAIL:
                li_result = LI_SENSOR_FAIL_RES;
                break;

            case OTHER_FAULTS1:
                li_result = OTHER_FAULTS_RES;
                break;

            case OTHER_FAULTS2:
                li_result = OTHER_FAULTS_RES;
                break;
        }

        /*Байт состояния 2: датчик пламени*/

        uint8_t dp_result;

        switch(rx_buffer[LI_DP_BYTE] & 0b00001111) {
            case LI_NORMAL:
                dp_result = LI_NORMAL;
                break;

            case LI_ATTENTION1:
                dp_result = LI_ATTENTION1;
                break;

            case LI_ATTENTION2:
                dp_result = LI_ATTENTION1;
                break;

            case LI_ATTENTION3:
                dp_result = LI_ATTENTION1;
                break;

            case LI_FIRE1:
                dp_result = LI_FIRE;
                break;

            case LI_FIRE2:
                dp_result = LI_FIRE;
                break;

            case LI_FIRE3:
                dp_result = LI_FIRE;
                break;

            case LI_FIRE4:
                dp_result = LI_FIRE;
                break;

            case GENERAL_FAULT:
                dp_result = GENERAL_FAULT_RES;
                break;

            case CONNECT_BROKEN:
                dp_result = CONNECT_BROKEN_RES;
                break;

            case LI_KZ:
                dp_result = LI_KZ_RES;
                break;

            case LI_KZ_GND1:
                dp_result = LI_KZ_GND_RES;
                break;

            case LI_KZ_GND2:
                dp_result = LI_KZ_GND_RES;
                break;

            case LI_SENSOR_FAIL:
                dp_result = LI_SENSOR_FAIL_RES;
                break;

            case OTHER_FAULTS1:
                dp_result = OTHER_FAULTS_RES;
                break;

            case OTHER_FAULTS2:
                dp_result = OTHER_FAULTS_RES;
                break;
        }

        /*Байт состояния 3: устройство пожаротушения - 1 (УП - 1)*/

        uint8_t up1_result = 0;

        switch(rx_buffer[UP1_DT_BYTE] >> UP1_OFFSET & 0b00000111) {
            case UP_NORMAL:
                up1_result = UP_NORMAL;
                break;

            case UP_CONNECT_BROKEN:
                up1_result = UP_CONNECT_BROKEN;
                break;

            case UP_KZ:
                up1_result = UP_KZ;
                break;

            case UP_RESERVE:
                up1_result = UP_RESERVE;
                break;

            case UP_ACTIVATION1:
                up1_result = UP_ACTIVATION1;
                break;

            case UP_ACTIVATION2:
                up1_result = UP_ACTIVATION1;
                break;

            case UP_ACTIVATION3:
                up1_result = UP_ACTIVATION1;
                break;

            case UP_ACTIVATION4:
                up1_result = UP_ACTIVATION1;
                break;	
        }

        /*Байт состояния 3: датчик температуры максимально-дифференциальный*/

        uint8_t dt_result;
        uint8_t dt_mode = rx_buffer[UP1_DT_BYTE] & DT_MODE_BIT ? 1:0; // 0/1 обычный режим/режим дотушивания

        switch(rx_buffer[UP1_DT_BYTE] & 0b00001111) {
            case LI_NORMAL:
                dt_result = LI_NORMAL;
                break;

            case LI_ATTENTION1:
                dt_result = LI_ATTENTION1;
                break;

            case LI_ATTENTION2:
                dt_result = LI_ATTENTION1;
                break;

            case LI_ATTENTION3:
                dt_result = LI_ATTENTION1;
                break;

            case LI_FIRE1:
                dt_result = LI_FIRE;
                break;

            case LI_FIRE2:
                dt_result = LI_FIRE;
                break;

            case LI_FIRE3:
                dt_result = LI_FIRE;
                break;

            case LI_FIRE4:
                dt_result = LI_FIRE;
                break;

            case GENERAL_FAULT:
                dt_result = GENERAL_FAULT_RES;
                break;

            case CONNECT_BROKEN:
                dt_result = CONNECT_BROKEN_RES;
                break;

            case LI_KZ:
                dt_result = LI_KZ_RES;
                break;

            case DT_MIN_TEMP:
                dt_result = DT_MIN_TEMP_RES;
                break;

            case DT_MAX_TEMP:
                dt_result = DT_MAX_TEMP_RES;
                break;

            case DT_INSTANT_CHANGE:
                dt_result = DT_INSTANT_CHANGE_RES;
                break;

            case DT_OTHER_FAULTS1:
                dt_result = DT_OTHER_FAULTS_RES;
                break;

            case DT_OTHER_FAULTS2:
                dt_result = DT_OTHER_FAULTS_RES;
                break;
        }

        /*Байт состояния 4: состояние питания*/

        uint8_t pw_result = 0;

        switch(rx_buffer[PW_UP2_UP3_BYTE] >> PW_OFFSET & 0b00000011) {
            case PW_NORMAL:
                pw_result = PW_NORMAL;
                break;

            case PW_UP:
                pw_result = PW_UP;
                break;

            case PW_DOWN:
                pw_result = PW_DOWN;
                break;

            case PW_CRIT_DOWN:
                pw_result = PW_CRIT_DOWN;
                break;
        }

        /*Байт состояния 4: устройство пожаротушения - 3 (УП - 3)*/

        uint8_t up3_result;

        switch(rx_buffer[PW_UP2_UP3_BYTE] >> UP3_OFFSET & 0b00000111) {
            case UP_NORMAL:
                up3_result = UP_NORMAL;
                break;

            case UP_CONNECT_BROKEN:
                up3_result = UP_CONNECT_BROKEN;
                break;

            case UP_KZ:
                up3_result = UP_KZ;
                break;

            case UP_RESERVE:
                up3_result = UP_RESERVE;
                break;

            case UP_ACTIVATION1:
                up3_result = UP_ACTIVATION1;
                break;

            case UP_ACTIVATION2:
                up3_result = UP_ACTIVATION1;
                break;

            case UP_ACTIVATION3:
                up3_result = UP_ACTIVATION1;
                break;

            case UP_ACTIVATION4:
                up3_result = UP_ACTIVATION1;
                break;	
        }

        /*Байт состояния 4: устройство пожаротушения - 2 (УП - 2)*/

        uint8_t up2_result;

        switch(rx_buffer[PW_UP2_UP3_BYTE] & 0b00000111) {
            case UP_NORMAL:
                up2_result = UP_NORMAL;
                break;

            case UP_CONNECT_BROKEN:
                up2_result = UP_CONNECT_BROKEN;
                break;

            case UP_KZ:
                up2_result = UP_KZ;
                break;

            case UP_RESERVE:
                up2_result = UP_RESERVE;
                break;

            case UP_ACTIVATION1:
                up2_result = UP_ACTIVATION1;
                break;

            case UP_ACTIVATION2:
                up2_result = UP_ACTIVATION1;
                break;

            case UP_ACTIVATION3:
                up2_result = UP_ACTIVATION1;
                break;

            case UP_ACTIVATION4:
                up2_result = UP_ACTIVATION1;
                break;	
        }

        /*Байт состояния 5: токоограничение*/

        uint8_t cur_result;

        switch(rx_buffer[CUR_LIM_BYTE] & 0b00000111) {
            case CUR_NORMAL:
                cur_result = CUR_NORMAL;
                break;

            case CUR_FAULT:
                cur_result = CUR_FAULT;
                break;

            case CUR_KZ:
                cur_result = CUR_KZ;
                break;

            case CUR_RESERVE:
                cur_result = CUR_RESERVE;
                break;

            case CUR_ACTIVATION1:
                cur_result = CUR_ACTIVATION1;
                break;

            case CUR_ACTIVATION2:
                cur_result = CUR_ACTIVATION1;
                break;

            case CUR_ACTIVATION3:
                cur_result = CUR_ACTIVATION1;
                break;

            case CUR_ACTIVATION4:
                cur_result = CUR_ACTIVATION1;
                break;
        }
 
        if (ext_is_not_possible) {
            RShow("По данному направлению ТУШЕНИЕ НЕВОЗМОЖНО!");
            set_asp_status_error(asp);
        }
        
            /*--------------Инициализация структуры направления пожаротушения---------------*/

        switch(rx_buffer[DIRECTION_BYTE_INDEX]) {
            case OPERATOR_DIRECTION:
                asp->operator_dir.direction = OPERATOR_DIRECTION;
                asp->operator_dir.extinguishing = ext_progress;
                asp->operator_dir.extinguish_ended = quench_completed;
                asp->operator_dir.extinguish_impossible = ext_is_not_possible;

                //
                /*инициализация модуля тушения*/
                asp->operator_dir.fire_ext_mod.ext_mod              = ext_mod;
                asp->operator_dir.fire_ext_mod.com_ext_mod          = com_ext_mod;
                asp->operator_dir.fire_ext_mod.dotushivanie         = dotushivanie;
                asp->operator_dir.fire_ext_mod.quench_completed     = quench_completed;
                asp->operator_dir.fire_ext_mod.ext_progress         = ext_progress;
                asp->operator_dir.fire_ext_mod.fire_detected        = fire_detected;
                asp->operator_dir.fire_ext_mod.attention_detected   = attention_detected;
                asp->operator_dir.fire_ext_mod.ext_is_not_possible  = ext_is_not_possible;

                /*инициализация всего остального*/
                asp->operator_dir.li_result  = li_result;
                asp->operator_dir.dp_result  = dp_result;
                asp->operator_dir.up1_result = up1_result;
                asp->operator_dir.up2_result = up2_result;
                asp->operator_dir.up3_result = up3_result;
                asp->operator_dir.dt_mode    = dt_mode;
                asp->operator_dir.dt_result  = dt_result;
                asp->operator_dir.pw_result  = pw_result;
                asp->operator_dir.cur_result = cur_result;	

                break;

            case CONTROL_DIRECTION:
                asp->control_dir.direction = CONTROL_DIRECTION;
                asp->control_dir.extinguishing = ext_progress;
                asp->control_dir.extinguish_ended = quench_completed;
                asp->control_dir.extinguish_impossible = ext_is_not_possible;

                //
                /*инициализация модуля тушения*/
                asp->control_dir.fire_ext_mod.ext_mod            = ext_mod;
                asp->control_dir.fire_ext_mod.com_ext_mod         = com_ext_mod;
                asp->control_dir.fire_ext_mod.dotushivanie      = dotushivanie;
                asp->control_dir.fire_ext_mod.quench_completed   = quench_completed;
                asp->control_dir.fire_ext_mod.ext_progress       = ext_progress;
                asp->control_dir.fire_ext_mod.fire_detected      = fire_detected;
                asp->control_dir.fire_ext_mod.attention_detected = attention_detected;
                asp->control_dir.fire_ext_mod.ext_is_not_possible  = ext_is_not_possible;

                /*инициализация всего остального*/
                asp->control_dir.li_result  = li_result;
                asp->control_dir.dp_result  = dp_result;
                asp->control_dir.up1_result = up1_result;
                asp->control_dir.up2_result = up2_result;
                asp->control_dir.up3_result = up3_result;
                asp->control_dir.dt_mode    = dt_mode;
                asp->control_dir.dt_result  = dt_result;
                asp->control_dir.pw_result  = pw_result;
                asp->control_dir.cur_result = cur_result;	

                break;

            case AGREGAT_DIRECTION:
                asp->agregat_dir.direction = AGREGAT_DIRECTION;
                asp->agregat_dir.extinguishing = ext_progress;
                asp->agregat_dir.extinguish_ended = quench_completed;
                asp->agregat_dir.extinguish_impossible = ext_is_not_possible;

                //
                /*инициализация модуля тушения*/
                asp->agregat_dir.fire_ext_mod.ext_mod            = ext_mod;
                asp->agregat_dir.fire_ext_mod.com_ext_mod         = com_ext_mod;
                asp->agregat_dir.fire_ext_mod.dotushivanie      = dotushivanie;
                asp->agregat_dir.fire_ext_mod.quench_completed   = quench_completed;
                asp->agregat_dir.fire_ext_mod.ext_progress       = ext_progress;
                asp->agregat_dir.fire_ext_mod.fire_detected      = fire_detected;
                asp->agregat_dir.fire_ext_mod.attention_detected = attention_detected;
                asp->agregat_dir.fire_ext_mod.ext_is_not_possible  = ext_is_not_possible;

                /*инициализация всего остального*/
                asp->agregat_dir.li_result  = li_result;
                asp->agregat_dir.dp_result  = dp_result;
                asp->agregat_dir.up1_result = up1_result;
                asp->agregat_dir.up2_result = up2_result;
                asp->agregat_dir.up3_result = up3_result;
                asp->agregat_dir.dt_mode    = dt_mode;
                asp->agregat_dir.dt_result  = dt_result;
                asp->agregat_dir.pw_result  = pw_result;
                asp->agregat_dir.cur_result = cur_result;	

                break;

            default:
                DShow("Ответ не верный\n");
                break;
        }
    }     
}

/*!\brief Запись в БД конкретной характеристики АСП.
 * \param [in] conn - указатель на соединение с базой
 * \param [in]  - указатель на структуру параметров АСП 
 * \param [in] charact_id - id параметра в БД
 * \param [in] value - значение
 * \return none
 */
void asp_charact_insert_db(PGconn *conn, int asp_id, int charact_id, float value) {
    PGresult *res;
    string query = "";
    query = create_query_update_charact(asp_id, charact_id, value);
    res = PQexec(conn, query.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        RShow("Не удалось вставить данные по характеристике! Для АСП\n");
    }
    PQclear(res);
}

void asp_update_db(PGconn *conn, struct_asp_params *asp) {
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_status, asp->status);
    
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_oper_fault, asp->operator_dir.fault);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_oper_warning, asp->operator_dir.warning);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_oper_fire, asp->operator_dir.fire);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_oper_manual, asp->operator_dir.manual);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_oper_all_extinguishers, asp->operator_dir.all_extinguishers);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_oper_auto_off, asp->operator_dir.auto_off_dir);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_oper_extinguishing, asp->operator_dir.extinguishing);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_oper_extinguish_ended, asp->operator_dir.extinguish_ended);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_oper_extinguish_impossible, asp->operator_dir.extinguish_impossible);

    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_control_fault, asp->control_dir.fault);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_control_warning, asp->control_dir.warning);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_control_fire, asp->control_dir.fire);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_control_manual, asp->control_dir.manual);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_control_all_extinguishers, asp->control_dir.all_extinguishers);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_control_auto_off, asp->control_dir.auto_off_dir);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_control_extinguishing, asp->control_dir.extinguishing);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_control_extinguish_ended, asp->control_dir.extinguish_ended);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_control_extinguish_impossible, asp->control_dir.extinguish_impossible);

    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_agregat_fault, asp->agregat_dir.fault);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_agregat_warning, asp->agregat_dir.warning);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_agregat_fire, asp->agregat_dir.fire);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_agregat_manual, asp->agregat_dir.manual);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_agregat_all_extinguishers, asp->agregat_dir.all_extinguishers);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_agregat_auto_off, asp->agregat_dir.auto_off_dir);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_agregat_extinguishing, asp->agregat_dir.extinguishing);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_agregat_extinguish_ended, asp->agregat_dir.extinguish_ended);
    asp_charact_insert_db(conn, asp->id, CHARACT_ASP_agregat_extinguish_impossible, asp->agregat_dir.extinguish_impossible);
}

