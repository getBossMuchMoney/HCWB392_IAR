/*****************************************************************************
 * Copyright (C) 2022, XiaoHua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *****************************************************************************/
#ifndef _BLEAPPSETTING_H_
#define _BLEAPPSETTING_H_


/**************************************************************************
 * Application Setting
 **************************************************************************/
// Define the maximum number of BLE connection link.
#define BLE_SUPPORT_NUM_CONN_MAX    0

// BLE stack supports device bonding if defined ENABLE_DEF.
#define BLE_SUPPORT_BOND            DISABLE_DEF

// BLE stack supports large MTU size if define ENABLE_DEF.
#define BLE_SUPPORT_MTU_LARGE       DISABLE_DEF

// BLE stack run in DTM mode.
#define BLE_DTM_ENABLE              DISABLE_DEF

// Set MTU size
#if (BLE_SUPPORT_MTU_LARGE == ENABLE_DEF)
#define BLE_MTU_SIZE                247
#else
#define BLE_MTU_SIZE                23
#endif

// Set device BLE company ID
#define BLE_COMPANY_ID_L            0x64
#define BLE_COMPANY_ID_H            0x08


#endif
