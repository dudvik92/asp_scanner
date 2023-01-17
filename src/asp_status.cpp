/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "asp_status.h"

void set_asp_status_ok(struct_asp_params *asp) {
    if (STATUS_UNAVAILABLE == asp->status)
        asp->status = STATUS_OK;
}

void set_asp_status_warning(struct_asp_params *asp) {
    if (STATUS_OK == asp->status)
        asp->status = STATUS_WARNING;
}

void set_asp_status_error(struct_asp_params *asp) {
    if (STATUS_OK == asp->status || STATUS_WARNING == asp->status)
        asp->status = STATUS_ERROR;
}

void set_asp_status_unavailable(struct_asp_params *asp) {
    asp->status = STATUS_UNAVAILABLE;
}

