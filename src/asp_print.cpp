#include "asp_protocol.h"

#include "asp_print.h"

#include "debug.h"
#include "asp.h"

using namespace std;

void asp_print_struct(direction StructForPrint) {
    DShow("\n");
    
    switch(StructForPrint.direction) {
        case OPERATOR_DIRECTION:
            DShow("Направление: Операторский отсек\n");
            break;
        case CONTROL_DIRECTION:
            DShow("Направление: Отсек управления\n");
            break;
        case AGREGAT_DIRECTION:
            DShow("Направление: Агрегатный отсек\n");
            break;
    }
    
    if (StructForPrint.fault) {
        DShow("Неисправности:\t\t\tприсутствуют\n");
    } else {
        DShow("Неисправности:\t\t\tотсутствуют\n");
    }

    if(StructForPrint.warning) {
        DShow("Состояние \"Внимание\" на данном направлении\n");
    }
    
    if(StructForPrint.fire) {
        DShow("Состояние \"Пожар\" на данном направлении\n");
    } 
    
    if(StructForPrint.manual) {
        DShow("Выполнен ручной запуск пожаротушения на данном направлении\n");
    } 
    
    if(StructForPrint.all_extinguishers) {
        DShow("Произведены все запуски пожаротушения\n");
    }
    
    if(StructForPrint.auto_off_dir) {
        DShow("Автоматика отключена на данном направлении\n");
    } 
    
    if(StructForPrint.extinguishing) {
        DShow("Выполняется тушение пожара на данном направлении\n");
    } 

    if(StructForPrint.extinguish_ended) {
        DShow("Тушение пожара на данном направлении завершено\n");
    } 
    
    if(StructForPrint.extinguish_impossible) {
        DShow("Тушение пожара на данном направлении НЕВОЗМОЖНО\n");
    } 
    
    if (StructForPrint.fire_ext_mod.ext_mod) {
        DShow("Исправность модуля тушения:\tнеисправен\n");
    } else {
        DShow("Исправность модуля тушения:\tисправен\n");
    }

    if(StructForPrint.fire_ext_mod.com_ext_mod) {
        DShow("Связь с модулем тушения:\tотсутствует\n");
    } else {
        DShow("Связь с модулем тушения:\tустановлена\n");
    }
    
    if(StructForPrint.fire_ext_mod.dotushivanie) {
        DShow("Выполняется дотушивание:\tвыполняется\n");
    } else {
        DShow("Выполняется дотушивание:\tне выполняется\n");
    }
    
    if(StructForPrint.fire_ext_mod.quench_completed) {
        DShow("Завершение тушения:\t\tнезавершено\n");
    } else {
        DShow("Завершение тушения:\t\tне завершено\n");
    }
    
    if(StructForPrint.fire_ext_mod.ext_progress) {
        DShow("Выполняется тушение:\t\tвыполняется\n");
    } else {
        DShow("Выполняется тушение:\t\tне выполняется\n");
    }
    
    if(StructForPrint.fire_ext_mod.fire_detected) {
        DShow("Фиксация пожара:\t\tзафиксирован\n");
    } else {
        DShow("Фиксация пожара:\t\tне зафиксирован\n");
    }
    
    if(StructForPrint.fire_ext_mod.attention_detected) {
        DShow("Состояние \"Внимание\":\t\tзафиксировано\n");
    } else {
        DShow("Состояние \"Внимание\":\t\tне зафиксировано\n");
    }
    if(StructForPrint.fire_ext_mod.ext_is_not_possible) {
        DShow("Возможность тушения:\t\tтушение невозможно\n");
    } else {
        DShow("Возможность тушения:\t\tтушение возможно\n");
    }

    switch(StructForPrint.li_result) {
        case 0: 
            DShow("Линейный извещатель:\t\tНорма\n");
            break;

        case 1:
            DShow("Линейный извещатель:\t\tВнимание\n");
            break;

        case 2:
            DShow("Линейный извещатель:\t\tЗафиксирован пожар\n");
            break;

        case 3:
            DShow("Линейный извещатель:\t\tОбщая неисправность\n");
            break;

        case 4:
            DShow("Линейный извещатель:\t\tОбрыв\n");
            break;

        case 5:
            DShow("Линейный извещатель:\t\tКороткое замыкание\n");
            break;

        case 6:
            DShow("Линейный извещатель:\t\tЗамыкание вывода на корпус\n");
            break;

        case 7:
            DShow("Линейный извещатель:\t\tПерезагрузка\n");
            break;

        case 8:
            DShow("Линейный извещатель:\t\tПрочие неисправности\n");
            break;
    }

    switch(StructForPrint.dp_result) {
        case 0: 
            DShow("Датчик пламени:\t\t\tНорма\n");
            break;

        case 1:
            DShow("Датчик пламени:\t\t\t\"Внимание\"\n");
            break;

        case 2:
            DShow("Датчик пламени:\t\t\tПожар\n");
            break;

        case 3:
            DShow("Датчик пламени:\t\t\tОбщая неисправность\n");
            break;

        case 4:
            DShow("Датчик пламени:\t\t\tОбрыв\n");
            break;

        case 5:
            DShow("Датчик пламени:\t\t\tКороткое замыкание\n");
            break;

        case 6:
            DShow("Датчик пламени:\t\t\tЗамыкание вывода на корпус\n");
            break;

        case 7:
            DShow("Датчик пламени:\t\t\tПерезагрузка\n");
            break;

        case 8:
            DShow("Датчик пламени:\t\t\tПрочие неисправности\n");
            break;
    }

    switch(StructForPrint.up1_result) {
        case UP_NORMAL:
            DShow("Устройство пожаротушения 1:\tНорма\n");
            break;

        case UP_CONNECT_BROKEN:
            DShow("Устройство пожаротушения 1:\tОбрыв\n");
            break;

        case UP_KZ:
            DShow("Устройство пожаротушения 1:\tКороткое замыкание\n");
            break;

        case UP_RESERVE:
            DShow("Устройство пожаротушения 1:\tРезерв\n");
            break;

        case UP_ACTIVATION1:
            DShow("Устройство пожаротушения 1:\tВключение\n");
            break;
    }

    switch(StructForPrint.up2_result) {
        case UP_NORMAL:
            DShow("Устройство пожаротушения 2:\tНорма\n");
            break;

        case UP_CONNECT_BROKEN:
            DShow("Устройство пожаротушения 2:\tОбрыв\n");
            break;

        case UP_KZ:
            DShow("Устройство пожаротушения 2:\tКороткое замыкание\n");
            break;

        case UP_RESERVE:
            DShow("Устройство пожаротушения 2:\tРезерв\n");
            break;

        case UP_ACTIVATION1:
            DShow("Устройство пожаротушения 2:\tВключение\n");
            break;
    }

    switch(StructForPrint.up3_result) {
        case UP_NORMAL:
            DShow("Устройство пожаротушения 3:\tНорма\n");
            break;

        case UP_CONNECT_BROKEN:
            DShow("Устройство пожаротушения 3:\tОбрыв\n");
            break;

        case UP_KZ:
            DShow("Устройство пожаротушения 3:\tКороткое замыкание\n");
            break;

        case UP_RESERVE:
            DShow("Устройство пожаротушения 3:\tРезерв\n");
            break;

        case UP_ACTIVATION1:
            DShow("Устройство пожаротушения 3:\tВключение\n");
            break;
    }

    if(StructForPrint.dt_mode) {
        DShow("Датчик температуры:\t\tРежим дотушивания\n");
    } else {
        DShow("Датчик температуры:\t\tОбычный режим\n");
    }
    switch(StructForPrint.dt_result) {
        case 0:
            DShow("Датчик температуры:\t\tНорма\n");
            break;

        case 1:
            DShow("Датчик температуры:\t\tВнимание\n");
            break;

        case 2:
            DShow("Датчик температуры:\t\tПожар\n");
            break;

        case 3:
            DShow("Датчик температуры:\t\tОбщая неисправность\n");
            break;

        case 4:
            DShow("Датчик температуры:\t\tОбрыв\n");
            break;

        case 5:
            DShow("Датчик температуры:\t\tКороткое замыкание\n");
            break;

        case 6: 
            DShow("Датчик температуры:\t\tПоказания меньше -55 гр. Цельсия\n");
            break;

        case 7:
            DShow("Датчик температуры:\t\tПоказания выше 220 гр. Цельсия\n");
            break;

        case 8:
            DShow("Датчик температуры:\t\tМгновенное изменение температуры\n");
            break;

        case 9:
            DShow("Датчик температуры:\t\tПрочие неисправности\n");
            break;
    }

    switch(StructForPrint.pw_result) {
        case PW_NORMAL:
            DShow("Состояние питания:\t\tНорма\n");
            break;

        case PW_UP:
            DShow("Состояние питания:\t\tВыше нормы\n");
            break;

        case PW_DOWN:
            DShow("Состояние питания:\t\tНиже нормы\n");
            break;

        case PW_CRIT_DOWN:
            DShow("Состояние питания:\t\tКритически низкое\n");
            break;
    }

    switch(StructForPrint.cur_result) {
        case CUR_NORMAL:
            DShow("Токоограничение:\t\tНорма\n");
            break;

        case CUR_FAULT:
            DShow("Токоограничение:\t\tНеисправность\n");
            break;

        case CUR_KZ:
            DShow("Токоограничение:\t\tКороткое замыкание\n");
            break;

        case CUR_RESERVE:
            DShow("Токоограничение:\t\tРезерв\n");
            break;

        case CUR_ACTIVATION1:
            DShow("Токоограничение:\t\tВключение токоограничения\n");
            break;
    }
    
    DShow("\n");
}
