/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   asp_protocol.h
 * Author: dudka
 *
 * Created on 10 сентября 2021 г., 11:03
 */

#ifndef ASP_PROTOCOL_H
#define ASP_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdint.h>

/*-----------Тип сообщения---------*/
#define STATE                   0x33
#define AUTO_OFF                0x3A
#define START_EXTINGUESH        0x95
#define RESET_COMMAND           0x96    
    
/*----Направления пожаротушения----*/
//#define DVS_Direction            0x00
#define OPERATOR_DIRECTION      0x01
#define CONTROL_DIRECTION       0x02
#define AGREGAT_DIRECTION       0x03
    
#define ALL_ASP                 0x07 // Добавил запрос общего состояния АСП 2.08.21
/*--------------------------------*/
    
#define TYPE_REQ_BYTE_INDEX             10 // индекс байта "тип сообщения" в запросе
#define DIRECTION_BYTE_INDEX            14 // индекс байта "направление пожаротушения" в запросе
#define REQUEST_CRC8_BYTE_INDEX         17 // индекс байта контрольной суммы в запросе
/*-----------------------------------*/

/*--------------Ответ-----------------*/
#define ANSWER_CRC8_BYTE_INDEX          25 // индекс байта контрольной суммы в ответе
#define ANSWER_HIGH_BYTE_ADDRESS_INDEX  12  // индекс старшего байта адреса в ответе
#define ANSWER_HEGH_BYTE_ADDRESS        0x26 // старший байт адреса в ответе
/*------------------------------------*/
    
/* Байт состояния 1: модуль пожаротушения */
#define EXT_MODULE_BYTE             17 // индекс байта состояния 1
    
#define EXT_MOD_BIT                 1<<7
#define COM_EXT_MOD_BIT               1<<6
#define DOTUSH_BIT            1<<5
    
#define QUENCH_COMPLETED_BIT        1<<4
#define EXT_PROGRESS_BIT            1<<3
    
#define FIRE_DETECT_BIT           1<<2
#define ATTENTION_DETECT_BIT      1<<1    
    
#define EXT_IS_NOT_POSSIBLE_BI     1

////
    
/* Байт состояния 2: линейный извещатель и датчик пламени */
#define LI_DP_BYTE          18 // индекс байта состояния 2
#define LI_OFFSET           4 
#define LI_NORMAL              0
#define LI_ATTENTION1          1
#define LI_ATTENTION2          2
#define LI_ATTENTION3          3
#define LI_FIRE             2  
#define LI_FIRE1               4
#define LI_FIRE2               5
#define LI_FIRE3               6
#define LI_FIRE4               7 
#define GENERAL_FAULT       8
#define GENERAL_FAULT_RES   3
#define CONNECT_BROKEN      9
#define CONNECT_BROKEN_RES  4
#define LI_KZ                  10
#define LI_KZ_RES              5
#define LI_KZ_GND1       11
#define LI_KZ_GND2       12
#define LI_KZ_GND_RES     6
#define LI_SENSOR_FAIL      13
#define LI_SENSOR_FAIL_RES  7
#define OTHER_FAULTS1       14
#define OTHER_FAULTS2       15
#define OTHER_FAULTS_RES    8

/* Байт состояния 3: устройство пожаротушения - 1 (УП - 1) и датчик температуры максимально-дифференциальный */
#define UP1_DT_BYTE 19

/* Устройство пожаротушения - 1 (УП - 1) */
#define UP1_OFFSET          5
#define UP_NORMAL           0
#define UP_CONNECT_BROKEN   1
#define UP_KZ               2
#define UP_RESERVE          3
#define UP_ACTIVATION1      4
#define UP_ACTIVATION2      5
#define UP_ACTIVATION3      6
#define UP_ACTIVATION4      7

/* Датчик температуры максимально-дифференциальный */
#define DT_MODE_BIT             1<<4
#define DT_MIN_TEMP             11
#define DT_MIN_TEMP_RES         6
#define DT_MAX_TEMP             12
#define DT_MAX_TEMP_RES         7
#define DT_INSTANT_CHANGE       13
#define DT_INSTANT_CHANGE_RES   8 
#define DT_OTHER_FAULTS1        14
#define DT_OTHER_FAULTS2        15
#define DT_OTHER_FAULTS_RES     9

/* Байт состояния 4: состояние питания, устройство пожаротушения - 2 (УП - 2), устройство пожаротушения - 3 (УП - 3) */
#define PW_UP2_UP3_BYTE 20

/* Состояние питания */
#define PW_OFFSET       6
#define PW_NORMAL       0
#define PW_UP           1
#define PW_DOWN         2
#define PW_CRIT_DOWN    3

/* Устройство пожаротушения - 3 (УП - 3) */
#define UP3_OFFSET 3

/* Байт состояния 5: токоограничение */
#define CUR_LIM_BYTE    21
#define CUR_NORMAL      0
#define CUR_FAULT       1
#define CUR_KZ          2
#define CUR_RESERVE     3
#define CUR_ACTIVATION1 4
#define CUR_ACTIVATION2 5
#define CUR_ACTIVATION3 6
#define CUR_ACTIVATION4 7
    
/* Байт состояния АСП: Неисправности */
#define FAULT_ASP_BYTE                      17 
#define FAULT_ASP_BIT                       1<<7
#define FAULT_CONTROL_DIRECTION_BIT         1<<2
#define FAULT_AGREGAT_DIRECTION_BIT         1<<3
#define FAULT_OPERATOR_DIRECTION_BIT        1<<1
//#define FAULT_DVS_DIRECTION_BIT                 1

/* Байт состояния АСП: Пожары */
#define FIRE_ASP_BYTE                       18 
#define FIRE_CONTROL_DIRECTION_BIT          1<<2
#define FIRE_AGREGAT_DIRECTION_BIT          1<<3
#define FIRE_OPERATOR_DIRECTION_BIT         1<<1

/* Байт состояния АСП: Автоматика отключена */
#define AUTO_OFF_ASP_BYTE                   19  
#define AUTO_OFF_CONTROL_DIRECTION_BIT      1<<2
#define AUTO_OFF_AGREGAT_DIRECTION_BIT      1<<3
#define AUTO_OFF_OPERATOR_DIRECTION_BIT     1<<1      
    
/* Байт состояния АСП: Ручные запуски тушения */
#define MANUAL_ASP_BYTE                     20  
#define MANUAL_CONTROL_DIRECTION_BIT        1<<2
#define MANUAL_AGREGAT_DIRECTION_BIT        1<<3
#define MANUAL_OPERATOR_DIRECTION_BIT       1<<1        
    
/* Байт состояния АСП: Все запуски тушения */
#define ALL_EXT_ASP_BYTE                    21  
#define ALL_EXT_CONTROL_DIRECTION_BIT       1<<2
#define ALL_EXT_AGREGAT_DIRECTION_BIT       1<<3
#define ALL_EXT_OPERATOR_DIRECTION_BIT      1<<1  
    
/* Байт состояния АСП: Внимание */
#define ATTENTION_ASP_BYTE                  22  
#define ATTENTION_CONTROL_DIRECTION_BIT     1<<2
#define ATTENTION_AGREGAT_DIRECTION_BIT     1<<3
#define ATTENTION_OPERATOR_DIRECTION_BIT    1<<1 


void gener_req(uint8_t type_req, uint8_t direct, uint8_t *tx_buffer, uint8_t duration = 0xff); // Формирование массива запроса к АСП
        
    
#ifdef __cplusplus
}
#endif

#endif /* ASP_PROTOCOL_H */

