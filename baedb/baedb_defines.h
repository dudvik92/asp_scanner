#ifndef BAEDB_DEFINES_H
#define BAEDB_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

#define DB_ID_LEN   8       /*!<\brief Длина поля под идентификатор в БД */
    
#define DB_EPS_ID       0
#define DB_BPVS_ID      1
#define DB_BPI_ID       2
#define DB_BPSN_ID      3
#define DB_BPAKB_ID     4
#define DB_BKCH_ID      5
#define DB_MKU_ID       6
#define DB_MDS_ID       7
#define DB_BPN_ID       8
#define DB_BKUT_ID      9
#define DB_VU_ID        10
#define DB_BKR_ID       11
#define DB_ASP_ID       12
#define DB_BPAKBBSCH_ID 13
    
#define DB_SVR_ID           1    
#define DB_ENIP_1_ID        2
#define DB_ENIP_2_ID        3
#define DB_ENIP_3_ID        4
    
#define ALTAIR_SVR_TYPE     1     /*!<\brief Тип поддерживаемого ЩВР */
#define ALTAIR_ENIP_TYPE    1     /*!<\brief Тип поддерживаемого ЭНИП в ЩВР */

//статусы устройств
#define STATUS_OK           0
#define STATUS_WARNING      1
#define STATUS_ERROR        2
#define STATUS_UNAVAILABLE  3

//характеристики всех блоков кроме ЩВР и его состовляющих
#define EPS_offset                              0
    
#define CHARACT_EPS_voice_flag                  EPS_offset + 1

#define BPVS_offset                             EPS_offset + 1

#define CHARACT_BPVS_status                     BPVS_offset + 1
#define CHARACT_BPVS_S_UA                       BPVS_offset + 2
#define CHARACT_BPVS_S_UB                       BPVS_offset + 3
#define CHARACT_BPVS_S_UC                       BPVS_offset + 4
#define CHARACT_BPVS_temp                       BPVS_offset + 5
#define CHARACT_BPVS_SH1_UA                     BPVS_offset + 6
#define CHARACT_BPVS_SH1_UB                     BPVS_offset + 7
#define CHARACT_BPVS_SH1_UC                     BPVS_offset + 8
#define CHARACT_BPVS_SH1_freq                   BPVS_offset + 9
#define CHARACT_BPVS_SH1_I_A                    BPVS_offset + 10
#define CHARACT_BPVS_SH1_I_B                    BPVS_offset + 11
#define CHARACT_BPVS_SH1_I_C                    BPVS_offset + 12
#define CHARACT_BPVS_SH2_UA                     BPVS_offset + 13
#define CHARACT_BPVS_SH2_UB                     BPVS_offset + 14
#define CHARACT_BPVS_SH2_UC                     BPVS_offset + 15
#define CHARACT_BPVS_SH2_freq                   BPVS_offset + 16
#define CHARACT_BPVS_SH2_I_A                    BPVS_offset + 17
#define CHARACT_BPVS_SH2_I_B                    BPVS_offset + 18
#define CHARACT_BPVS_SH2_I_C                    BPVS_offset + 19
#define CHARACT_BPVS_S_freq                     BPVS_offset + 20
#define CHARACT_BPVS_P                          BPVS_offset + 21
#define CHARACT_BPVS_kont_azou                  BPVS_offset + 22
#define CHARACT_BPVS_kont_ks1                   BPVS_offset + 23
#define CHARACT_BPVS_kont_ks2                   BPVS_offset + 24
#define CHARACT_BPVS_kont_ksh                   BPVS_offset + 25
#define CHARACT_BPVS_sync                       BPVS_offset + 26
#define CHARACT_BPVS_sync1                      BPVS_offset + 27
#define CHARACT_BPVS_sync2                      BPVS_offset + 28
#define CHARACT_BPVS_asym                       BPVS_offset + 29
#define CHARACT_BPVS_osh_kont_azou_f            BPVS_offset + 30
#define CHARACT_BPVS_osh_kont_azou_n            BPVS_offset + 31
#define CHARACT_BPVS_osh_kont_ks1_f             BPVS_offset + 32
#define CHARACT_BPVS_osh_kont_ks1_n             BPVS_offset + 33
#define CHARACT_BPVS_osh_kont_ks2_f             BPVS_offset + 34
#define CHARACT_BPVS_osh_kont_ks2_n             BPVS_offset + 35
#define CHARACT_BPVS_osh_kont_ksh_f             BPVS_offset + 36
#define CHARACT_BPVS_osh_kont_ksh_n             BPVS_offset + 37
#define CHARACT_BPVS_zah_sh1                    BPVS_offset + 38
#define CHARACT_BPVS_zah_sh2                    BPVS_offset + 39
#define CHARACT_BPVS_azou_napr_na_korp          BPVS_offset + 40
#define CHARACT_BPVS_azou_big_rezistance        BPVS_offset + 41
#define CHARACT_BPVS_azou_small_rezistance      BPVS_offset + 42
#define CHARACT_BPVS_osh_azou_1                 BPVS_offset + 43
#define CHARACT_BPVS_osh_azou_2                 BPVS_offset + 44
#define CHARACT_BPVS_osh_azou_3                 BPVS_offset + 45
#define CHARACT_BPVS_osh_azou_4                 BPVS_offset + 46
#define CHARACT_BPVS_osh_azou_5                 BPVS_offset + 47
#define CHARACT_BPVS_osh_azou_6                 BPVS_offset + 48
#define CHARACT_BPVS_SH1_full_P                 BPVS_offset + 49
#define CHARACT_BPVS_SH1_active_P               BPVS_offset + 50
#define CHARACT_BPVS_SH2_full_P                 BPVS_offset + 51
#define CHARACT_BPVS_SH2_active_P               BPVS_offset + 52
   
#define BPI_offset                              BPVS_offset + 52
    
#define CHARACT_BPI_status                      BPI_offset + 1
#define CHARACT_BPI_ist_U_A                     BPI_offset + 2
#define CHARACT_BPI_ist_U_B                     BPI_offset + 3
#define CHARACT_BPI_ist_U_C                     BPI_offset + 4
#define CHARACT_BPI_ist_freq                    BPI_offset + 5
#define CHARACT_BPI_ist_I_A                     BPI_offset + 6
#define CHARACT_BPI_ist_I_B                     BPI_offset + 7
#define CHARACT_BPI_ist_I_C                     BPI_offset + 8
#define CHARACT_BPI_ist_P                       BPI_offset + 9
#define CHARACT_BPI_SH1_U_A                     BPI_offset + 10
#define CHARACT_BPI_SH1_U_B                     BPI_offset + 11
#define CHARACT_BPI_SH1_U_C                     BPI_offset + 12
#define CHARACT_BPI_SH1_freq                    BPI_offset + 13
#define CHARACT_BPI_SH1_I_A                     BPI_offset + 14
#define CHARACT_BPI_SH1_I_B                     BPI_offset + 15
#define CHARACT_BPI_SH1_I_C                     BPI_offset + 16
#define CHARACT_BPI_temp                        BPI_offset + 17
#define CHARACT_BPI_SH2_U_A                     BPI_offset + 18
#define CHARACT_BPI_SH2_U_B                     BPI_offset + 19
#define CHARACT_BPI_SH2_U_C                     BPI_offset + 20
#define CHARACT_BPI_SH2_freq                    BPI_offset + 21
#define CHARACT_BPI_SH2_I_A                     BPI_offset + 22
#define CHARACT_BPI_SH2_I_B                     BPI_offset + 23
#define CHARACT_BPI_SH2_I_C                     BPI_offset + 24
#define CHARACT_BPI_L1_U_A                      BPI_offset + 25
#define CHARACT_BPI_L1_U_B                      BPI_offset + 26
#define CHARACT_BPI_L1_U_C                      BPI_offset + 27
#define CHARACT_BPI_L1_I_A                      BPI_offset + 28
#define CHARACT_BPI_L1_I_B                      BPI_offset + 29
#define CHARACT_BPI_L1_I_C                      BPI_offset + 30
#define CHARACT_BPI_L2_U_A                      BPI_offset + 31
#define CHARACT_BPI_L2_U_B                      BPI_offset + 32
#define CHARACT_BPI_L2_U_C                      BPI_offset + 33
#define CHARACT_BPI_L2_I_A                      BPI_offset + 34
#define CHARACT_BPI_L2_I_B                      BPI_offset + 35
#define CHARACT_BPI_L2_I_C                      BPI_offset + 36
#define CHARACT_BPI_kont_ki                     BPI_offset + 37
#define CHARACT_BPI_kont_k11                    BPI_offset + 38
#define CHARACT_BPI_kont_k12                    BPI_offset + 39
#define CHARACT_BPI_kont_kl11                   BPI_offset + 40
#define CHARACT_BPI_kont_kl21                   BPI_offset + 41
#define CHARACT_BPI_sync                        BPI_offset + 42
#define CHARACT_BPI_sync1                       BPI_offset + 43
#define CHARACT_BPI_sync2                       BPI_offset + 44
#define CHARACT_BPI_zah_SH1                     BPI_offset + 45
#define CHARACT_BPI_zah_SH2                     BPI_offset + 46
#define CHARACT_BPI_zah_L1                      BPI_offset + 47
#define CHARACT_BPI_zah_L2                      BPI_offset + 48
#define CHARACT_BPI_osh_kont_k11_f              BPI_offset + 49
#define CHARACT_BPI_osh_kont_k11_n              BPI_offset + 50
#define CHARACT_BPI_osh_kont_k12_f              BPI_offset + 51
#define CHARACT_BPI_osh_kont_k12_n              BPI_offset + 52
#define CHARACT_BPI_osh_kont_kl11_f             BPI_offset + 53
#define CHARACT_BPI_osh_kont_kl11_n             BPI_offset + 54
#define CHARACT_BPI_osh_kont_kl21_f             BPI_offset + 55
#define CHARACT_BPI_osh_kont_kl21_n             BPI_offset + 56
#define CHARACT_BPI_SH1_full_P                  BPI_offset + 57
#define CHARACT_BPI_SH1_active_P                BPI_offset + 58
#define CHARACT_BPI_SH2_full_P                  BPI_offset + 59
#define CHARACT_BPI_SH2_active_P                BPI_offset + 60
    
#define BPSN_offset                             BPI_offset + 60
    
#define CHARACT_BPSN_status                     BPSN_offset + 1
#define CHARACT_BPSN_SH1_UA                     BPSN_offset + 2
#define CHARACT_BPSN_SH1_UB                     BPSN_offset + 3
#define CHARACT_BPSN_SH1_UC                     BPSN_offset + 4
#define CHARACT_BPSN_SH2_UA                     BPSN_offset + 5
#define CHARACT_BPSN_SH2_UB                     BPSN_offset + 6
#define CHARACT_BPSN_SH2_UC                     BPSN_offset + 7
#define CHARACT_BPSN_UA                         BPSN_offset + 8
#define CHARACT_BPSN_UB                         BPSN_offset + 9
#define CHARACT_BPSN_UC                         BPSN_offset + 10
#define CHARACT_BPSN_Ik1_A                      BPSN_offset + 11
#define CHARACT_BPSN_Ik1_B                      BPSN_offset + 12
#define CHARACT_BPSN_Ik1_C                      BPSN_offset + 13
#define CHARACT_BPSN_temp                       BPSN_offset + 14
#define CHARACT_BPSN_Ik2_A                      BPSN_offset + 15
#define CHARACT_BPSN_Ik2_B                      BPSN_offset + 16
#define CHARACT_BPSN_Ik2_C                      BPSN_offset + 17
#define CHARACT_BPSN_Ik3_A                      BPSN_offset + 18
#define CHARACT_BPSN_Ik3_B                      BPSN_offset + 19
#define CHARACT_BPSN_Ik3_C                      BPSN_offset + 20
#define CHARACT_BPSN_Ik4_A                      BPSN_offset + 21
#define CHARACT_BPSN_Ik4_B                      BPSN_offset + 22
#define CHARACT_BPSN_Ik4_C                      BPSN_offset + 23
#define CHARACT_BPSN_kont_k1                    BPSN_offset + 24
#define CHARACT_BPSN_kont_k2                    BPSN_offset + 25
#define CHARACT_BPSN_kont_k3                    BPSN_offset + 26
#define CHARACT_BPSN_kont_k4                    BPSN_offset + 27
#define CHARACT_BPSN_kont_sn1                   BPSN_offset + 28
#define CHARACT_BPSN_kont_sn2                   BPSN_offset + 29
#define CHARACT_BPSN_zah_k1                     BPSN_offset + 30
#define CHARACT_BPSN_zah_k2                     BPSN_offset + 31
#define CHARACT_BPSN_zah_k3                     BPSN_offset + 32
#define CHARACT_BPSN_zah_k4                     BPSN_offset + 33
#define CHARACT_BPSN_osh_kont_sn1_f             BPSN_offset + 34
#define CHARACT_BPSN_osh_kont_sn1_n             BPSN_offset + 35
#define CHARACT_BPSN_osh_kont_sn2_f             BPSN_offset + 36
#define CHARACT_BPSN_osh_kont_sn2_n             BPSN_offset + 37
#define CHARACT_BPSN_osh_kont_k1                BPSN_offset + 38
#define CHARACT_BPSN_osh_kont_k2                BPSN_offset + 39
#define CHARACT_BPSN_osh_kont_k3                BPSN_offset + 40
#define CHARACT_BPSN_osh_kont_k4                BPSN_offset + 41
 
#define BPAKB_offset                            BPSN_offset + 41
    
#define CHARACT_BPAKB_status                    BPAKB_offset + 1
#define CHARACT_BPAKB_UVU                       BPAKB_offset + 2
#define CHARACT_BPAKB_UAKB                      BPAKB_offset + 3
#define CHARACT_BPAKB_IVU                       BPAKB_offset + 4
#define CHARACT_BPAKB_IAKB                      BPAKB_offset + 5
#define CHARACT_BPAKB_Ik1                       BPAKB_offset + 6
#define CHARACT_BPAKB_Ik2                       BPAKB_offset + 7
#define CHARACT_BPAKB_Ik3                       BPAKB_offset + 8
#define CHARACT_BPAKB_Ik4                       BPAKB_offset + 9
#define CHARACT_BPAKB_temp                      BPAKB_offset + 10
#define CHARACT_BPAKB_kont_vu                   BPAKB_offset + 11
#define CHARACT_BPAKB_kont_k1                   BPAKB_offset + 12
#define CHARACT_BPAKB_kont_k2                   BPAKB_offset + 13
#define CHARACT_BPAKB_kont_k3                   BPAKB_offset + 14
#define CHARACT_BPAKB_kont_k4                   BPAKB_offset + 15
#define CHARACT_BPAKB_zah_k1                    BPAKB_offset + 16
#define CHARACT_BPAKB_zah_k2                    BPAKB_offset + 17
#define CHARACT_BPAKB_zah_k3                    BPAKB_offset + 18
#define CHARACT_BPAKB_zah_k4                    BPAKB_offset + 19
#define CHARACT_BPAKB_osh_kont_vu               BPAKB_offset + 20
#define CHARACT_BPAKB_osh_kont_k1               BPAKB_offset + 21
#define CHARACT_BPAKB_osh_kont_k2               BPAKB_offset + 22
#define CHARACT_BPAKB_osh_kont_k3               BPAKB_offset + 23
#define CHARACT_BPAKB_osh_kont_k4               BPAKB_offset + 24
    
#define BKCH_offset                             BPAKB_offset + 24
    
#define CHARACT_BKCH_status                     BKCH_offset + 1
#define CHARACT_BKCH_freq                       BKCH_offset + 2
#define CHARACT_BKCH_ufreq                      BKCH_offset + 3
#define CHARACT_BKCH_rej                        BKCH_offset + 4
#define CHARACT_BKCH_temp                       BKCH_offset + 5
    
#define MKU_offset                              BKCH_offset + 5
    
#define CHARACT_MKU_status                      MKU_offset + 1    
#define CHARACT_MKU_U1                          MKU_offset + 2
#define CHARACT_MKU_U2                          MKU_offset + 3
#define CHARACT_MKU_U3                          MKU_offset + 4
#define CHARACT_MKU_I1                          MKU_offset + 5
#define CHARACT_MKU_I2                          MKU_offset + 6
#define CHARACT_MKU_I3                          MKU_offset + 7
#define CHARACT_MKU_cosfi                       MKU_offset + 8
#define CHARACT_MKU_activ_P                     MKU_offset + 9
#define CHARACT_MKU_temp_OZ                     MKU_offset + 10
#define CHARACT_MKU_davl_masl                   MKU_offset + 11
#define CHARACT_MKU_freq                        MKU_offset + 12
#define CHARACT_MKU_rele_vkl_TPN                MKU_offset + 13
#define CHARACT_MKU_vozd_zahl_zakr              MKU_offset + 14
#define CHARACT_MKU_vozd_zahl_otkr              MKU_offset + 15
#define CHARACT_MKU_avt_dozat_masl              MKU_offset + 16
#define CHARACT_MKU_luki_zakr                   MKU_offset + 17
#define CHARACT_MKU_luki_otkr                   MKU_offset + 18
#define CHARACT_MKU_zaluz_zakr                  MKU_offset + 19
#define CHARACT_MKU_zaluz_otkr                  MKU_offset + 20
#define CHARACT_MKU_rele_start                  MKU_offset + 21
#define CHARACT_MKU_vih_komm_app                MKU_offset + 22
#define CHARACT_MKU_kont_vkl_N                  MKU_offset + 23
#define CHARACT_MKU_sopr_izol_low               MKU_offset + 24
#define CHARACT_MKU_masl_low                    MKU_offset + 25
#define CHARACT_MKU_masl_high                   MKU_offset + 26
#define CHARACT_MKU_OZ_level_low                MKU_offset + 27
#define CHARACT_MKU_succes_start                MKU_offset + 28
#define CHARACT_MKU_SPPG                        MKU_offset + 29
#define CHARACT_MKU_SPPO                        MKU_offset + 30
#define CHARACT_MKU_sist_regul_U_gen_sost       MKU_offset + 31
#define CHARACT_MKU_P01                         MKU_offset + 32
#define CHARACT_MKU_P02                         MKU_offset + 33
#define CHARACT_MKU_P03                         MKU_offset + 34
#define CHARACT_MKU_P04                         MKU_offset + 35
#define CHARACT_MKU_P06                         MKU_offset + 36
#define CHARACT_MKU_P07                         MKU_offset + 37
#define CHARACT_MKU_P08                         MKU_offset + 38
#define CHARACT_MKU_P09                         MKU_offset + 39
#define CHARACT_MKU_A00                         MKU_offset + 40
#define CHARACT_MKU_A01                         MKU_offset + 41
#define CHARACT_MKU_A02                         MKU_offset + 42
#define CHARACT_MKU_A03                         MKU_offset + 43
#define CHARACT_MKU_A04                         MKU_offset + 44
#define CHARACT_MKU_A05                         MKU_offset + 45
#define CHARACT_MKU_A06                         MKU_offset + 46
#define CHARACT_MKU_A07                         MKU_offset + 47
#define CHARACT_MKU_A08                         MKU_offset + 48
#define CHARACT_MKU_A09                         MKU_offset + 49
#define CHARACT_MKU_A10                         MKU_offset + 50
#define CHARACT_MKU_A11                         MKU_offset + 51
#define CHARACT_MKU_A12                         MKU_offset + 52
#define CHARACT_MKU_A13                         MKU_offset + 53
#define CHARACT_MKU_A14                         MKU_offset + 54
#define CHARACT_MKU_A15                         MKU_offset + 55
#define CHARACT_MKU_A16                         MKU_offset + 56
#define CHARACT_MKU_A17                         MKU_offset + 57
#define CHARACT_MKU_PP01                        MKU_offset + 58
#define CHARACT_MKU_PP02                        MKU_offset + 59
#define CHARACT_MKU_PP03                        MKU_offset + 60
#define CHARACT_MKU_PP05                        MKU_offset + 61
#define CHARACT_MKU_PP06                        MKU_offset + 62
#define CHARACT_MKU_PP07                        MKU_offset + 63
#define CHARACT_MKU_PP08                        MKU_offset + 64
#define CHARACT_MKU_PP09                        MKU_offset + 65
#define CHARACT_MKU_PP10                        MKU_offset + 66
#define CHARACT_MKU_local_mode                  MKU_offset + 67
#define CHARACT_MKU_remote_mode                 MKU_offset + 68
#define CHARACT_MKU_progr_mode                  MKU_offset + 69
#define CHARACT_MKU_kalibr_mode                 MKU_offset + 70
#define CHARACT_MKU_sync_mode                   MKU_offset + 71
#define CHARACT_MKU_test_mode                   MKU_offset + 72
#define CHARACT_MKU_reset_osh_mode              MKU_offset + 73
#define CHARACT_MKU_DG_blocked                  MKU_offset + 74
#define CHARACT_MKU_DG_working                  MKU_offset + 75
#define CHARACT_MKU_DG_start_proc               MKU_offset + 76
#define CHARACT_MKU_DG_stop_proc                MKU_offset + 77
#define CHARACT_MKU_DG_warming_mode             MKU_offset + 78
#define CHARACT_MKU_DG_cooling_mode             MKU_offset + 79
#define CHARACT_MKU_DG_working_rezh_no_avar     MKU_offset + 80
#define CHARACT_MKU_DG_avar_signal              MKU_offset + 81
#define CHARACT_MKU_DG_GPN                      MKU_offset + 82
#define CHARACT_MKU_DG_working_rezh             MKU_offset + 83
#define CHARACT_MKU_load_vkl                    MKU_offset + 84
#define CHARACT_MKU_load_otkl                   MKU_offset + 85
#define CHARACT_MKU_avar_led_on                 MKU_offset + 86
#define CHARACT_MKU_rezh_stat_on                MKU_offset + 87
#define CHARACT_MKU_rezh_ogran_zash             MKU_offset + 88

#define MDS_offset                              MKU_offset + 88     /*!<\brief Отступ характеристик МДС */

#define CHARACT_MDS_status                      MDS_offset + 1                  /*!<\brief Сетевая доступность */
#define CHARACT_MDS_sensor1_break               MDS_offset + 2                  /*!<\brief Обрыв датчика 1 */ 
#define CHARACT_MDS_sensor2_break               MDS_offset + 3                  /*!<\brief Обрыв датчика 2 */      
#define CHARACT_MDS_sensor3_break               MDS_offset + 4                  /*!<\brief Обрыв датчика 3 */ 
#define CHARACT_MDS_temp1                       MDS_offset + 5                  /*!<\brief Температура 1 */ 
#define CHARACT_MDS_temp2                       MDS_offset + 6                  /*!<\brief Температура 2 */ 
#define CHARACT_MDS_temp3                       MDS_offset + 7                  /*!<\brief Температура 3 */
    
#define BPN_offset                              MDS_offset + 7
    
#define CHARACT_BPN_status                      BPN_offset + 1                  /*!<\brief Сетевая доступность */
#define CHARACT_BPN_load1                       BPN_offset + 2                  /*!<\brief Нагрузка 1 */
#define CHARACT_BPN_load2                       BPN_offset + 3                  /*!<\brief Нагрузка 2 */

#define BKUT_offset                             BPN_offset + 3 
    
#define CHARACT_BKUT_status                     BKUT_offset + 1                 /*!<\brief Сетевая доступность */
#define CHARACT_BKUT_tank1_state                BKUT_offset + 2                 /*!<\brief Уровень бака 1 */
#define CHARACT_BKUT_tank2_state                BKUT_offset + 3                 /*!<\brief Уровень бака 2 */
#define CHARACT_BKUT_tank1_low                  BKUT_offset + 4                 /*!<\brief Аварийный уровень топлива в баке 1 */
#define CHARACT_BKUT_tank2_low                  BKUT_offset + 5                 /*!<\brief Аварийный уровень топлива в баке 2 */
    
#define VU_offset                               BKUT_offset + 5
    
#define CHARACT_VU_status                       VU_offset + 1                   /*!<\brief Сетевая доступность */
#define CHARACT_VU_voltage                      VU_offset + 2                   /*!<\brief Выходное напряжение */
#define CHARACT_VU_mps1_overheat                VU_offset + 3                   /*!<\brief Перегрев МПС 1 */
#define CHARACT_VU_mps1_work_sig                VU_offset + 4                   /*!<\brief Сигнал работа МПС 1 */
#define CHARACT_VU_mps1_front_fan_state         VU_offset + 5                   /*!<\brief Состояние передних вентиляторов МПС 1 */
#define CHARACT_VU_mps1_rear_fan_state          VU_offset + 6                   /*!<\brief Сосятоние задних вентиляторов МПС 1 */
#define CHARACT_VU_mps1_communication_lost      VU_offset + 7                   /*!<\brief Потеря связи МПС 1 */
#define CHARACT_VU_mps1_temp                    VU_offset + 8                   /*!<\brief Температура МПС 1 */
#define CHARACT_VU_mps2_overheat                VU_offset + 9                   /*!<\brief Перегрев МПС 2 */
#define CHARACT_VU_mps2_work_sig                VU_offset + 10                  /*!<\brief Сигнал работа МПС 2 */
#define CHARACT_VU_mps2_front_fan_state         VU_offset + 11                  /*!<\brief Состояние передних вентиляторов МПС 2 */
#define CHARACT_VU_mps2_rear_fan_state          VU_offset + 12                  /*!<\brief Сосятоние задних вентиляторов МПС 2 */
#define CHARACT_VU_mps2_communication_lost      VU_offset + 13                  /*!<\brief Потеря связи МПС 2 */
#define CHARACT_VU_mps2_temp                    VU_offset + 14                  /*!<\brief Температура МПС 2 */
#define CHARACT_VU_mps3_overheat                VU_offset + 15                  /*!<\brief Перегрев МПС 3 */
#define CHARACT_VU_mps3_work_sig                VU_offset + 16                  /*!<\brief Сигнал работа МПС 3 */
#define CHARACT_VU_mps3_front_fan_state         VU_offset + 17                  /*!<\brief Состояние передних вентиляторов МПС 3 */
#define CHARACT_VU_mps3_rear_fan_state          VU_offset + 18                  /*!<\brief Сосятоние задних вентиляторов МПС 3 */
#define CHARACT_VU_mps3_communication_lost      VU_offset + 19                  /*!<\brief Потеря связи МПС 3 */
#define CHARACT_VU_mps3_temp                    VU_offset + 20                  /*!<\brief Температура МПС 3 */
#define CHARACT_VU_mps4_overheat                VU_offset + 21                  /*!<\brief Перегрев МПС 4 */
#define CHARACT_VU_mps4_work_sig                VU_offset + 22                  /*!<\brief Сигнал работа МПС 4 */
#define CHARACT_VU_mps4_front_fan_state         VU_offset + 23                  /*!<\brief Состояние передних вентиляторов МПС 4 */
#define CHARACT_VU_mps4_rear_fan_state          VU_offset + 24                  /*!<\brief Сосятоние задних вентиляторов МПС 4 */
#define CHARACT_VU_mps4_communication_lost      VU_offset + 25                  /*!<\brief Потеря связи МПС 4 */
#define CHARACT_VU_mps4_temp                    VU_offset + 26                  /*!<\brief Температура МПС 4 */

#define BKR27_offset                            VU_offset + 26
    
#define CHARACT_BKR27_status                    BKR27_offset + 1                /*!<\brief Сетевая доступность */
#define CHARACT_BKR27_avtomat_state             BKR27_offset + 2                /*!<\brief Состояние тумблера «АВТОМАТ» (0 – ручной, 1–автомат) */
#define CHARACT_BKR27_oper_confirm_needed       BKR27_offset + 3                /*!<\brief Необходимость подтверждения операции (0 – нет, 1 – да) */
#define CHARACT_BKR27_UV_vkl                    BKR27_offset + 4                /*!<\brief Состояние УВ (0-откл, 1-подкл) */
#define CHARACT_BKR27_UV_avar                   BKR27_offset + 5                /*!<\brief Авария УВ */
#define CHARACT_BKR27_UV_overload               BKR27_offset + 6                /*!<\brief Перегрузка УВ */
#define CHARACT_BKR27_EA_vkl                    BKR27_offset + 7                /*!<\brief Состояние ЭА (0-откл, 1-подкл) */
#define CHARACT_BKR27_EA_avar                   BKR27_offset + 8                /*!<\brief Авария ЭА */
#define CHARACT_BKR27_EA_overload               BKR27_offset + 9                /*!<\brief Перегрузка ЭА */
#define CHARACT_BKR27_UV_drain                  BKR27_offset + 10               /*!<\brief Состояние утечки УВ (0-нет, 1-да) */
#define CHARACT_BKR27_EA_drain                  BKR27_offset + 11               /*!<\brief Состояние утечки ЭА (0-нет, 1-да) */
#define CHARACT_BKR27_drain_save_state          BKR27_offset + 12               /*!<\brief Состояние защиты от токов утечки (0-выкл, 1-вкл) */
#define CHARACT_BKR27_bus_overvoltage           BKR27_offset + 13               /*!<\brief Повышенное напряжение шины (0-нет, 1-да) */
#define CHARACT_BKR27_bus_undervoltage          BKR27_offset + 14               /*!<\brief Пониженное напряжение шины (0-нет, 1-да) */
#define CHARACT_BKR27_BPAKB_SES_drain           BKR27_offset + 15               /*!<\brief Утечка тока на линии БП АКБ CЭС (0-да, 1-нет) */
#define CHARACT_BKR27_BPAKB_BSCH_drain          BKR27_offset + 16               /*!<\brief Утечка тока на линии БП АКБ БШ (0-да, 1-нет) */
#define CHARACT_BKR27_bus_voltage               BKR27_offset + 17               /*!<\brief Напряжение шины */
#define CHARACT_BKR27_UV_current                BKR27_offset + 18               /*!<\brief Ток УВ */
#define CHARACT_BKR27_EA_current                BKR27_offset + 19               /*!<\brief Ток ЭА */
#define CHARACT_BKR27_potrSB1_connection        BKR27_offset + 20               /*!<\brief Выход Потр.СБ1 состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_potrSB1_vkl               BKR27_offset + 21               /*!<\brief Выход Потр.СБ1 включен/выключен (0 – выкл, 1 – вкл) */
#define CHARACT_BKR27_potrSB1_avar              BKR27_offset + 22               /*!<\brief Выход Потр.СБ1 авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_potrSB1_overload          BKR27_offset + 23               /*!<\brief Выход Потр.СБ1 перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_potrSB1_current           BKR27_offset + 24               /*!<\brief Выход Потр.СБ1 ток */
#define CHARACT_BKR27_potrSB2_connection        BKR27_offset + 25               /*!<\brief Выход Потр СБ2 состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_potrSB2_vkl               BKR27_offset + 26               /*!<\brief Выход Потр СБ2 включен/выключен (0 – выкл, 1 – вкл) */
#define CHARACT_BKR27_potrSB2_avar              BKR27_offset + 27               /*!<\brief Выход Потр СБ2 авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_potrSB2_overload          BKR27_offset + 28               /*!<\brief Выход Потр СБ2 перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_potrSB2_current           BKR27_offset + 29               /*!<\brief Выход Потр СБ2 ток */
#define CHARACT_BKR27_potrSB3_connection        BKR27_offset + 30               /*!<\brief Выход Потр.СБ3 состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_potrSB3_vkl               BKR27_offset + 31               /*!<\brief Выход Потр.СБ3 включен/выключен (0 – выкл, 1 – вкл) */
#define CHARACT_BKR27_potrSB3_avar              BKR27_offset + 32               /*!<\brief Выход Потр.СБ3 авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_potrSB3_overload          BKR27_offset + 33               /*!<\brief Выход Потр.СБ3 перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_potrSB3_current           BKR27_offset + 34               /*!<\brief Выход Потр.СБ3 ток */
#define CHARACT_BKR27_SA_connection             BKR27_offset + 35               /*!<\brief Выход СА состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_SA_vkl                    BKR27_offset + 36               /*!<\brief Выход СА включен/выключен (0 – выкл, 1 – вкл) */
#define CHARACT_BKR27_SA_avar                   BKR27_offset + 37               /*!<\brief Выход СА авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_SA_overload               BKR27_offset + 38               /*!<\brief Выход СА перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_SA_current                BKR27_offset + 39               /*!<\brief Выход СА ток */
#define CHARACT_BKR27_invertor_connection       BKR27_offset + 40               /*!<\brief Инвертор состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_invertor_vkl              BKR27_offset + 41               /*!<\brief Инвертор включен/выключен (0 - выкл, 1 - вкл) */
#define CHARACT_BKR27_invertor_avar             BKR27_offset + 42               /*!<\brief Инвертор авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_invertor_overload         BKR27_offset + 43               /*!<\brief Инвертор перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_invertor_current          BKR27_offset + 44               /*!<\brief Инвертор ток */
#define CHARACT_BKR27_RS1_SB1_connection        BKR27_offset + 45               /*!<\brief Выход РС1(СБ1) состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_RS1_SB1_vkl               BKR27_offset + 46               /*!<\brief Выход РС1(СБ1) включен/выключен (0 - выкл, 1 - вкл) */
#define CHARACT_BKR27_RS1_SB1_avar              BKR27_offset + 47               /*!<\brief Выход РС1(СБ1) авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_RS1_SB1_overload          BKR27_offset + 48               /*!<\brief Выход РС1(СБ1) перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_RS1_SB1_current           BKR27_offset + 49               /*!<\brief Выход РС1(СБ1) ток */
#define CHARACT_BKR27_RS1_SB3_connection        BKR27_offset + 50               /*!<\brief Выход РС1(СБ3) состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_RS1_SB3_vkl               BKR27_offset + 51               /*!<\brief Выход РС1(СБ3) включен/выключен (0 - выкл, 1 - вкл) */
#define CHARACT_BKR27_RS1_SB3_avar              BKR27_offset + 52               /*!<\brief Выход РС1(СБ3) авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_RS1_SB3_overload          BKR27_offset + 53               /*!<\brief Выход РС1(СБ3) перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_RS1_SB3_current           BKR27_offset + 54               /*!<\brief Выход РС1(СБ3) ток */
#define CHARACT_BKR27_RS2_SB1_connection        BKR27_offset + 55               /*!<\brief Выход РС2(СБ1) состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_RS2_SB1_vkl               BKR27_offset + 56               /*!<\brief Выход РС2(СБ1) включен/выключен (0 - выкл, 1 - вкл) */
#define CHARACT_BKR27_RS2_SB1_avar              BKR27_offset + 57               /*!<\brief Выход РС2(СБ1) авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_RS2_SB1_overload          BKR27_offset + 58               /*!<\brief Выход РС2(СБ1) перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_RS2_SB1_current           BKR27_offset + 59               /*!<\brief Выход РС2(СБ1) ток */
#define CHARACT_BKR27_RS2_SB3_connection        BKR27_offset + 60               /*!<\brief Выход РС2(СБ3) состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_RS2_SB3_vkl               BKR27_offset + 61               /*!<\brief Выход РС2(СБ3) включен/выключен (0 - выкл, 1 - вкл) */
#define CHARACT_BKR27_RS2_SB3_avar              BKR27_offset + 62               /*!<\brief Выход РС2(СБ3) авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_RS2_SB3_overload          BKR27_offset + 63               /*!<\brief Выход РС2(СБ3) перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_RS2_SB3_current           BKR27_offset + 64               /*!<\brief Выход РС2(СБ3) ток */
#define CHARACT_BKR27_kond_connection           BKR27_offset + 65               /*!<\brief Кондиционер состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_kond_vkl                  BKR27_offset + 66               /*!<\brief Кондиционер включен/выключен (0 - выкл, 1 - вкл) */
#define CHARACT_BKR27_kond_avar                 BKR27_offset + 67               /*!<\brief Кондиционер авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_kond_overload             BKR27_offset + 68               /*!<\brief Кондиционер перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_kond_current              BKR27_offset + 69               /*!<\brief Кондиционер ток */
#define CHARACT_BKR27_FVUA_connection           BKR27_offset + 70               /*!<\brief ФВУА состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_FVUA_vkl                  BKR27_offset + 71               /*!<\brief ФВУА включен/выключен (0 - выкл, 1 - вкл) */
#define CHARACT_BKR27_FVUA_avar                 BKR27_offset + 72               /*!<\brief ФВУА авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_FVUA_overload             BKR27_offset + 73               /*!<\brief ФВУА перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_FVUA_current              BKR27_offset + 74               /*!<\brief ФВУА ток */
#define CHARACT_BKR27_mask_light_connection     BKR27_offset + 75               /*!<\brief Освещение маск. состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_mask_light_vkl            BKR27_offset + 76               /*!<\brief Освещение маск. включен/выключен (0 - выкл, 1 - вкл) */
#define CHARACT_BKR27_mask_light_avar           BKR27_offset + 77               /*!<\brief Освещение маск. авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_mask_light_overload       BKR27_offset + 78               /*!<\brief Освещение маск. перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_mask_light_current        BKR27_offset + 79               /*!<\brief Освещение маск. ток */
#define CHARACT_BKR27_main_light_connection     BKR27_offset + 80               /*!<\brief Освещение общ. состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_main_light_vkl            BKR27_offset + 81               /*!<\brief Освещение общ. включен/выключен (0 - выкл, 1 - вкл) */
#define CHARACT_BKR27_main_light_avar           BKR27_offset + 82               /*!<\brief Освещение общ. авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_main_light_overload       BKR27_offset + 83               /*!<\brief Освещение общ. перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_main_light_current        BKR27_offset + 84               /*!<\brief Освещение общ. ток */
#define CHARACT_BKR27_dezh_light_connection     BKR27_offset + 85               /*!<\brief Освещение деж. состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_dezh_light_vkl            BKR27_offset + 86               /*!<\brief Освещение деж. включен/выключен (0 - выкл, 1 - вкл) */
#define CHARACT_BKR27_dezh_light_avar           BKR27_offset + 87               /*!<\brief Освещение деж. авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_dezh_light_overload       BKR27_offset + 88               /*!<\brief Освещение деж. перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_dezh_light_current        BKR27_offset + 89               /*!<\brief Освещение деж. ток */
#define CHARACT_BKR27_input_light_connection    BKR27_offset + 90               /*!<\brief Освещение вводы состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_input_light_vkl           BKR27_offset + 91               /*!<\brief Освещение вводы включен/выключен (0 - выкл, 1 - вкл) */
#define CHARACT_BKR27_input_light_avar          BKR27_offset + 92               /*!<\brief Освещение вводы авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_input_light_overload      BKR27_offset + 93               /*!<\brief Освещение вводы перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_input_light_current       BKR27_offset + 94               /*!<\brief Освещение вводы ток */
#define CHARACT_BKR27_warmer_connection         BKR27_offset + 95               /*!<\brief Отопитель состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_warmer_vkl                BKR27_offset + 96               /*!<\brief Отопитель включен/выключен (0 - выкл, 1 - вкл) */
#define CHARACT_BKR27_warmer_avar               BKR27_offset + 97               /*!<\brief Отопитель авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_warmer_overload           BKR27_offset + 98               /*!<\brief Отопитель перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_warmer_current            BKR27_offset + 99               /*!<\brief Отопитель ток */
#define CHARACT_BKR27_AKB_SES_connection        BKR27_offset + 100              /*!<\brief Выход АКБ СЭС состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_AKB_SES_vkl               BKR27_offset + 101              /*!<\brief Выход АКБ СЭС включен/выключен (0 - выкл, 1 - вкл) */
#define CHARACT_BKR27_AKB_SES_avar              BKR27_offset + 102              /*!<\brief Выход АКБ СЭС авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_AKB_SES_overload          BKR27_offset + 103              /*!<\brief Выход АКБ СЭС перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_AKB_SES_current           BKR27_offset + 104              /*!<\brief Выход АКБ СЭС ток */
#define CHARACT_BKR27_AKB_BSCH_connection       BKR27_offset + 105              /*!<\brief Выход АКБ БШ состояние связи (0 – норм, 1 – авария) */
#define CHARACT_BKR27_AKB_BSCH_vkl              BKR27_offset + 106              /*!<\brief Выход АКБ БШ включен/выключен (0 - выкл, 1 - вкл) */
#define CHARACT_BKR27_AKB_BSCH_avar             BKR27_offset + 107              /*!<\brief Выход АКБ БШ авария (0 – норм, 1 – авария) */
#define CHARACT_BKR27_AKB_BSCH_overload         BKR27_offset + 108              /*!<\brief Выход АКБ БШ перегрузка (0 – нет, 1 – есть) */
#define CHARACT_BKR27_AKB_BSCH_current          BKR27_offset + 109              /*!<\brief Выход АКБ БШ ток */

#define ASP_offset                                      BKR27_offset + 109

#define CHARACT_ASP_status                              ASP_offset + 1              /*!<\brief Статус АСП*/
#define CHARACT_ASP_oper_fault                          ASP_offset + 2
#define CHARACT_ASP_oper_warning                        ASP_offset + 3
#define CHARACT_ASP_oper_fire                           ASP_offset + 4
#define CHARACT_ASP_oper_manual                         ASP_offset + 5
#define CHARACT_ASP_oper_all_extinguishers              ASP_offset + 6
#define CHARACT_ASP_oper_auto_off                       ASP_offset + 7
#define CHARACT_ASP_oper_extinguishing                  ASP_offset + 8
#define CHARACT_ASP_oper_extinguish_ended               ASP_offset + 9
#define CHARACT_ASP_oper_extinguish_impossible          ASP_offset + 10
#define CHARACT_ASP_control_fault                       ASP_offset + 11
#define CHARACT_ASP_control_warning                     ASP_offset + 12
#define CHARACT_ASP_control_fire                        ASP_offset + 13
#define CHARACT_ASP_control_manual                      ASP_offset + 14
#define CHARACT_ASP_control_all_extinguishers           ASP_offset + 15
#define CHARACT_ASP_control_auto_off                    ASP_offset + 16
#define CHARACT_ASP_control_extinguishing               ASP_offset + 17
#define CHARACT_ASP_control_extinguish_ended            ASP_offset + 18
#define CHARACT_ASP_control_extinguish_impossible       ASP_offset + 19
#define CHARACT_ASP_agregat_fault                       ASP_offset + 20
#define CHARACT_ASP_agregat_warning                     ASP_offset + 21
#define CHARACT_ASP_agregat_fire                        ASP_offset + 22
#define CHARACT_ASP_agregat_manual                      ASP_offset + 23
#define CHARACT_ASP_agregat_all_extinguishers           ASP_offset + 24
#define CHARACT_ASP_agregat_auto_off                    ASP_offset + 25
#define CHARACT_ASP_agregat_extinguishing               ASP_offset + 26
#define CHARACT_ASP_agregat_extinguish_ended            ASP_offset + 27
#define CHARACT_ASP_agregat_extinguish_impossible       ASP_offset + 28

#define BPAKBBSCH_offset                                ASP_offset + 28

#define CHARACT_BPAKBBSCH_status                        BPAKBBSCH_offset + 1
#define CHARACT_BPAKBBSCH_AKB_podkl                     BPAKBBSCH_offset + 2
#define CHARACT_BPAKBBSCH_VS_EA_podkl                   BPAKBBSCH_offset + 3
#define CHARACT_BPAKBBSCH_OZ_vkl                        BPAKBBSCH_offset + 4
#define CHARACT_BPAKBBSCH_AKB_U_low                     BPAKBBSCH_offset + 5
#define CHARACT_BPAKBBSCH_AKB_U_high                    BPAKBBSCH_offset + 6
#define CHARACT_BPAKBBSCH_AKB_temp                      BPAKBBSCH_offset + 7
#define CHARACT_BPAKBBSCH_I_direction                   BPAKBBSCH_offset + 8
#define CHARACT_BPAKBBSCH_AKB_I                         BPAKBBSCH_offset + 9
#define CHARACT_BPAKBBSCH_SH_U                          BPAKBBSCH_offset + 10
#define CHARACT_BPAKBBSCH_AKB_U                         BPAKBBSCH_offset + 11
    
//характеристики ЩВР и его состовляющих
#define SVR_offset                      0
    
#define CHARACT_SVR_state               SVR_offset + 1    /*!<\brief Смещение в БД для статуса ЩВР */
#define CHARACT_SVR_in_line_state       SVR_offset + 2    /*!<\brief Смещение в БД для статуса входной линии ЩВР */
#define CHARACT_SVR_1_line_state        SVR_offset + 3    /*!<\brief Смещение в БД для статуса 1-ой выходной линии ЩВР */
#define CHARACT_SVR_2_line_state        SVR_offset + 4    /*!<\brief Смещение в БД для статуса 2-ой выходной линии ЩВР */
#define CHARACT_SVR_3_line_state        SVR_offset + 5    /*!<\brief Смещение в БД для статуса 3-ой выходной линии ЩВР */
    
#define ENIP_offset                     SVR_offset + 5

#define CHARACT_ENIP_state              ENIP_offset + 1   /*!<\brief Смещение в БД для статуса ЭНИП */
#define CHARACT_ENIP_temp               ENIP_offset + 2   /*!<\brief Смещение в БД для температуры ЭНИП */
#define CHARACT_ENIP_U_A                ENIP_offset + 3   /*!<\brief Смещение в БД для напряжения на фазе A */
#define CHARACT_ENIP_U_B                ENIP_offset + 4   /*!<\brief Смещение в БД для напряжения на фазе B */
#define CHARACT_ENIP_U_C                ENIP_offset + 5   /*!<\brief Смещение в БД для напряжения на фазе C */
#define CHARACT_ENIP_U_ABC              ENIP_offset + 6   /*!<\brief Смещение в БД для напряжения линейного среднего */
#define CHARACT_ENIP_I_A                ENIP_offset + 7   /*!<\brief Смещение в БД для тока на фазе A */
#define CHARACT_ENIP_I_B                ENIP_offset + 8   /*!<\brief Смещение в БД для тока на фазе B */
#define CHARACT_ENIP_I_C                ENIP_offset + 9   /*!<\brief Смещение в БД для тока на фазе C */
#define CHARACT_ENIP_I_ABC              ENIP_offset + 10  /*!<\brief Смещение в БД для тока среднего */
#define CHARACT_ENIP_P_A                ENIP_offset + 11  /*!<\brief Смещение в БД для мощности на фазе A */
#define CHARACT_ENIP_P_B                ENIP_offset + 12  /*!<\brief Смещение в БД для мощности на фазе B */
#define CHARACT_ENIP_P_C                ENIP_offset + 13  /*!<\brief Смещение в БД для мощности на фазе C */
#define CHARACT_ENIP_P_ABC              ENIP_offset + 14  /*!<\brief Смещение в БД для мощности суммарной */
#define CHARACT_ENIP_DI1                ENIP_offset + 15  /*!<\brief Смещение в БД для значения на цифровом входе 1 */
#define CHARACT_ENIP_DI2                ENIP_offset + 16  /*!<\brief Смещение в БД для значения на цифровом входе 2 */
#define CHARACT_ENIP_DI3                ENIP_offset + 17  /*!<\brief Смещение в БД для значения на цифровом входе 3 */
#define CHARACT_ENIP_DO1                ENIP_offset + 18  /*!<\brief Смещение в БД для значения на цифровом выходе 1 */
    
#define ALTAIR_ENIP_VALUE_COUNT  17    /*!<\brief Число параметров ЕНИП в БД */

#ifdef __cplusplus
}
#endif

#endif /* BAEDB_DEFINES_H */