/**************************************************************************//**
* @file       ble_profile.h
* @brief      Provide the declarations that for BLE Profile subsystem needed.
*
 *****************************************************************************
 * Copyright (C) 2022, XiaoHua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
*****************************************************************************/

#ifndef _BLE_PROFILE_H_
#define _BLE_PROFILE_H_

#include <stdint.h>
#include "ble_host.h"
#include "ble_service_base.h"
#include "ble_service_gap.h"
#include "ble_service_gatt.h"
#include "ble_service_dis.h"
#include "ble_service_udf01s.h"


/**************************************************************************
 * Profile Application GENERAL Public Definitions and Functions
 **************************************************************************/
/** @defgroup profileAppGeneralFunc Profile Application General Definitions and Functions
* @{
* @details Here shows the general definitions of the application profile.
* @}
**************************************************************************/
/** Define the maximum number of BLE GAP service link. */
#define MAX_NUM_CONN_GAP            1

/** Define the maximum number of BLE GATT service link. */
#define MAX_NUM_CONN_GATT           1

/** Define the maximum number of BLE DIS service link. */
#define MAX_NUM_CONN_DIS            1

/** Define the maximum number of BLE UDF01 service link. */
#define MAX_NUM_CONN_UDF01S         1


/** Extern maximum Number of Host Connection Link Definition. */
extern const uint8_t MAX_NUM_CONN_HOST;


/**************************************************************************
 * Profile Application LINK HOST ID = 0 Public Definitions and Functions
 **************************************************************************/

/** BLE Application Link 0 Profile Attribute Information Structure.
*/
typedef struct BLEProfile_Link0_Info
{
    uint8_t              hostId;                  /**< Host id. */
    BleMode              bleState;                /**< Current BLE mode. */
    uint8_t              subState;                /**< Current link substate. */
    BLEATT_GAP_Info      serviceGAP_info_c;       /**< GAP information (client). */
    BLEATT_GATT_Info     serviceGATT_info_c;      /**< GATT information (client). */
    BLEATT_DIS_Info      serviceDIS_info_c;       /**< DIS Service information (client). */
    BLEATT_UDF01S_Info   serviceUDF01S_info_c;    /**< UDF01 Service information (client). */
} BLEProfile_Link0_Info;



/** Extern BLE Application Link 0 Profile Attribute Information Initialization.
*/
extern BLEProfile_Link0_Info bleProfile_link0_info;


/** Get BLE LINK0 Service Information
 *
 * @attention MUST call this API to get service information after received @ref BLECMD_EVENT_ATT_DATABASE_PARSING_FINISHED
 *
 * @param[in] hostId : the link's host id.
 * @param[out] attInfo : a pointer to INK0 attribute information
 *
 * @retval BLESTACK_STATUS_ERR_INVALID_HOSTID : Error host id.
 * @retval BLESTACK_STATUS_ERR_INVALID_PARAM : Invalid parameter.
 * @retval BLESTACK_STATUS_SUCCESS  : Setting success.
*/
BleStackStatus getBLELink0_ServiceHandles(uint8_t hostId, BLEProfile_Link0_Info *attInfo);

#endif // _BLE_PROFILE_H_

