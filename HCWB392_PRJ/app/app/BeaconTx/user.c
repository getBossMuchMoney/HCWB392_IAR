/*****************************************************************************
 * @file    user.c
 * @version     
 * @brief
 *          Demonstrate how to use LIB pre-build function to start and stop a BLE
 *           connection.
 *****************************************************************************
 * Copyright (C) 2022, XiaoHua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *****************************************************************************/
#include <stdio.h>
#include "BleAppSetting.h"
#include "ble_cmd.h"
#include "ble_event.h"
#include "ble_Host.h"

//Advertising parameters
#define APP_ADV_INTERVAL_MIN       160U       //160*0.625ms=100ms
#define APP_ADV_INTERVAL_MAX       160U       //160*0.625ms=100ms


/**************************************************************************
 * Variable
**************************************************************************/
uint8_t ble_state;

/**************************************************************************
* Function Prototype Declarations
**************************************************************************/
static void BleEvent_Callback(BleCmdEvent event, void *param);



#pragma push
//#pragma Otime
#pragma Ospace
/**************************************************************************
* Functions
**************************************************************************/
BleStackStatus BleApp_Init(void)
{
    BleStackStatus status;

    /* set company Id*/
    status = setBLE_CompanyId(((uint16_t)BLE_COMPANY_ID_H << 8) | BLE_COMPANY_ID_L);

    /* register command event callback function */
    setBLE_RegisterBleEvent(BleEvent_Callback);

    return status;
}

BleStackStatus Ble_AdvInit(void)
{
    BleStackStatus status;
    BLE_Adv_Param advParam;

    uint8_t advData_ibeacon_format[] =
    {
        30,                                                                           // iBecaon data format total Length
        GAP_AD_TYPE_LENGTH_2, GAP_AD_TYPE_FLAGS, GAP_FLAGS_BR_EDR_NOT_SUPPORTED,      // GAP_ADTYPE_BREDR_NOT_SUPPORTED
        0x1A,                                                                         // length of this data including the data type byte
        GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA,                                       // manufacturer specific data type
        0x64,                                                                         // Company ID - Low Byte
        0x08,                                                                         // Company ID - High Byte
        0x02,                                                                         // Beacon
        0x15,                                                                         // data Length
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                               // 128 bit-UUID - Test
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x01,                                                                   // Major ID
        0x00, 0x01,                                                                   // Minor ID
        0xC8,                                                                         // Power - The 2's complement of the calibrated Tx power
    };

    // Adv. parameter init
    advParam.advType = ADV_TYPE_ADV_NONCONN_IND;
    advParam.advIntervalMin = APP_ADV_INTERVAL_MIN;
    advParam.advIntervalMax = APP_ADV_INTERVAL_MAX;
    advParam.advChannelMap = ADV_CHANNEL_ALL;
    advParam.advFilterPolicy = ADV_FILTER_POLICY_ACCEPT_ALL;
    status = setBLE_AdvParam(&advParam);
    BLESTACK_STATUS_CHECK(status);

    // Adv. data init
    status = setBLE_AdvData((uint8_t *)advData_ibeacon_format, sizeof(advData_ibeacon_format));
    BLESTACK_STATUS_CHECK(status);

    return BLESTACK_STATUS_SUCCESS;
}

BleStackStatus Ble_AdvStart(uint8_t hostId)
{
    BleStackStatus status;

    status = Ble_AdvInit();
    BLESTACK_STATUS_CHECK(status);

    status = setBLE_AdvEnable(hostId);
    BLESTACK_STATUS_CHECK(status);

    return BLESTACK_STATUS_SUCCESS;
}

void BleApp_Main(void)
{
    BleStackStatus status;

    if (ble_state == STATE_BLE_STANDBY)
    {
        // enable beacon advertisement
        status = Ble_AdvStart(BLE_HOSTID_RESERVED);
        if (status == BLESTACK_STATUS_SUCCESS)
        {
            ble_state = STATE_BLE_ADVERTISING;
        }
    }
    else if (ble_state == STATE_BLE_ADVERTISING)
    {

    }
} //end of BleApp_Main()
#pragma pop


/* GAP Callback Function */
static void BleEvent_Callback(BleCmdEvent event, void *param)
{
    switch (event)
    {
    case BLECMD_EVENT_ADV_COMPLETE:
        if (ble_state == STATE_BLE_ADVERTISING)
        {
            printf("Advertising...\r\n");
        }
        break;

    case BLECMD_EVENT_SCAN_REPORT:
        break;

    case BLECMD_EVENT_CONN_COMPLETE:
        break;

    case BLECMD_EVENT_DISCONN_COMPLETE:
        break;

    case BLECMD_EVENT_CONN_UPDATE_COMPLETE:
        break;

    case BLECMD_EVENT_PHY_UPDATE_COMPLETE:
        break;

    case BLECMD_EVENT_STK_GEN_METHOD:
        break;

    case BLECMD_EVENT_PASSKEY_CONFIRM:
        break;

    case BLECMD_EVENT_AUTH_STATUS:
        break;

    default:
        break;
    }
}

