/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   asp_status.h
 * Author: dudka
 *
 * Created on 8 сентября 2021 г., 9:52
 */

#ifndef ASP_STATUS_H
#define ASP_STATUS_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "asp.h"
#include "baedb_defines.h"

void set_asp_status_ok(struct_asp_params *asp_str);

void set_asp_status_warning(struct_asp_params *asp_str);

void set_asp_status_error(struct_asp_params *asp_str);

void set_asp_status_unavailable(struct_asp_params *asp_str);

#ifdef __cplusplus
}
#endif

#endif /* ASP_STATUS_H */

