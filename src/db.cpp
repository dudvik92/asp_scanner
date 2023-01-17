#include <stdio.h>

#include "db.h"

#include "baedb_defines.h"

/*!\brief Формирование строки для записи парамтра в БД.  АСП
 * \param [in] dev_id - ID АСП в БД
 * \param [in] charact_id - ID характеристики в БД
 * \param [in] value - значение параметра
 * \return query - строка для записи параметра в БД
 */
std::string create_query_update_charact(int dev_id, int charact_id, float value) {
    char charact_id_buf[DB_ID_LEN] = {0};
    char asp_id_buf[DB_ID_LEN] = {0};
    char value_buf[sizeof (float) + 1] = {0};
    snprintf(charact_id_buf, sizeof (charact_id_buf), "%d", charact_id);
    snprintf(asp_id_buf, sizeof (asp_id_buf), "%d", dev_id);
    snprintf(value_buf, sizeof (value_buf), "%.3f", value);

    std::string query = "UPDATE table_eps_characts SET eps_charact_value = ";
    query += value_buf;
    query += " WHERE eps_id = 1 AND eps_block_id = ";
    query += asp_id_buf;
    query += " AND eps_charact_id = ";
    query += charact_id_buf;
    return query;
}
