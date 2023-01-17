#ifndef ASP_H
#define ASP_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdint.h>
#include <postgresql/libpq-fe.h>
    
#include "asp_protocol.h"
    
typedef struct {// структура модуля тушения
    uint8_t ext_mod;            // Модуль тушения 0/1 исправен/неисправен
    uint8_t com_ext_mod;         // Связь с модулем тушения 0/1 исправен/неисправен
    uint8_t dotushivanie;      // Выполняется дотушивание 0/1 выполняется/не выполняется
    uint8_t quench_completed;   // Тушение завершено 0/1 тушение не завершено/тушение завершено
    uint8_t ext_progress;       // Выполняется тушение 0/1 выполняется/ не выполняется
    uint8_t fire_detected;      // Зафиксирован пожар 0/1  зафиксирован/не зафиксирован
    uint8_t attention_detected; // Зафиксировано состояние "Внимание" 0/1 зафиксировано/ не зафиксировано
    uint8_t ext_is_not_possible;  // Тушение невозможно 0/1 невозможно/возможно
} ExtModule;    

typedef struct {// структура с информацией о направлении пожаротушения
    uint8_t direction;    // Код направления пожаротушения
    uint8_t fault;        // Неисправность
    uint8_t warning;        // Предупреждение
    uint8_t fire;           // Пожар
    uint8_t manual;         // Ручной запуск пожаротушения
    uint8_t all_extinguishers; // Все запуски тушения
    uint8_t auto_off_dir;       // Автоматика отключена
    uint8_t extinguishing;  // Выполняется тушение
    uint8_t extinguish_ended;  // Тушение завершено 
    uint8_t extinguish_impossible;   // Тушение невозможно
    
    // Параметры, используемые только для отладки
    ExtModule fire_ext_mod;
    uint8_t li_result;     // статус линейного извещателя
    uint8_t dp_result;	  // статус датчика пламени
    uint8_t up1_result;    // статус устройства пожаротушения - 1 (УП - 1)
    uint8_t up2_result;	  // статус устройства пожаротушения - 2 (УП - 2)
    uint8_t up3_result;	  // статус устройства пожаротушения - 3 (УП - 3)
    uint8_t dt_mode;       // режим работы датчика температуры
    uint8_t dt_result;     // статус датчика температуры
    uint8_t pw_result;     // состояние питания
    uint8_t cur_result;    // статус токоограничения    
} direction;
    
typedef struct {
    uint32_t id;
    uint8_t status;
    direction control_dir;
    direction agregat_dir;
    direction operator_dir;
} struct_asp_params;

uint8_t asp_get_count(PGconn *conn);
void asp_struct_init(PGconn *conn, struct_asp_params *asp, int asp_count);
uint8_t asp_connect(const char *dev_name);// инициализация последовательного порта
int asp_send_request(const char *dev_name, uint8_t *tx_buffer, uint8_t tx_buffer_len); // отправка запроса
uint8_t asp_read_answer(uint8_t *rx_buffer, uint8_t rx_buffer_len, uint8_t fd); // чтение ответа
void asp_response(uint8_t *rx_buffer, struct_asp_params *asp);
void asp_charact_insert_db(PGconn *conn, int asp_id, int charact_id, float value);
void asp_update_db(PGconn *conn, struct_asp_params *asp);

#ifdef __cplusplus
}
#endif

#endif /* ASP_H */
