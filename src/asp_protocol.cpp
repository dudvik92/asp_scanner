/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <sys/types.h>
//#include <sys/stat.h>

#include "asp_protocol.h"


void gener_req(uint8_t type_req, uint8_t direct, uint8_t *tx_buffer, uint8_t duration){
    tx_buffer[0] = 0x10;        // Авторегистр 1
    tx_buffer[1] = 0x32;        // Синхронизация
    tx_buffer[2] = 0x10;        // Авторегистр 1
    tx_buffer[3] = 0x32;        // Синхронизация
    tx_buffer[4] = 0x10;        // Авторегистр 1
    tx_buffer[5] = 0x32;        // Синхронизация
    tx_buffer[6] = 0x10;        // Авторегистр 1
    tx_buffer[7] = 0x32;        // Синхронизация
    tx_buffer[8] = 0x10;        // Авторегистр 1
    tx_buffer[9] = 0x01;        // Начало заголовка
    tx_buffer[10] = type_req;   // Тип сообщения
    tx_buffer[11] = 0x03;       // Тип изделия
    tx_buffer[12] = 0xA6;       // Адрес УАПСТ (старший байт)
    tx_buffer[13] = 0x72;       // Адрес УАПСТ (младший байт)
    tx_buffer[14] = direct;     // Направление пожаротушения
    tx_buffer[15] = 0x00;       // Резерв    
    if (type_req == AUTO_OFF) {
        tx_buffer[16] = duration; // Длительность отключения автоматики (постоянно)
    } else {
        tx_buffer[16] = 0x00;   // Резерв
    }
    tx_buffer[17] = 0x00;       // Контрольная сумма
    tx_buffer[18] = 0x10;       // Авторегистр 1
    tx_buffer[19] = 0x26;       // Конец блока передачи
}



