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
#include "rf_phy.h"
#include "ble_cmd.h"
#include "ble_event.h"


//Scan Parameters
#define SCAN_TYPE                       SCAN_TYPE_ACTIVE
#define SCAN_FILTER                     SCAN_FILTER_POLICY_ACCEPT_ALL
#define SCAN_WINDOW                     10U    //10*0.625ms=6.25ms
#define SCAN_INTERVAL                   10U    //10*0.625ms=6.25ms

/**************************************************************************
 * Variable
**************************************************************************/
uint8_t ble_state = STATE_BLE_STANDBY;;
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

BleStackStatus Ble_ScanInit(void)
{
    BleStackStatus status;
    BLE_Scan_Param scanParam;

    scanParam.scanType = SCAN_TYPE;
    scanParam.scanInterval = SCAN_INTERVAL;
    scanParam.scanWindow = SCAN_WINDOW;
    scanParam.scanFilterPolicy = SCAN_FILTER;
    status = setBLE_ScanParam(&scanParam);

    return status;
}

BleStackStatus Ble_ScanEnable(void)
{
    BleStackStatus status;

    status = Ble_ScanInit();
    BLESTACK_STATUS_CHECK(status);

    status = setBLE_ScanEnable();
    BLESTACK_STATUS_CHECK(status);

    return BLESTACK_STATUS_SUCCESS;
}

void BleApp_Main(void)
{
    BleStackStatus status;

    if (ble_state == STATE_BLE_STANDBY)
    {
        status = Ble_ScanEnable();
        if (status == BLESTACK_STATUS_SUCCESS)
        {
            ble_state = STATE_BLE_SCANNING;
        }
    }
    else if (ble_state == STATE_BLE_SCANNING)
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
        break;

    case BLECMD_EVENT_SCAN_COMPLETE:
        break;

    case BLECMD_EVENT_SCAN_REPORT:
    {
        BLE_Event_ScanReportParam *scanRepParam = (BLE_Event_ScanReportParam *)param;
        uint8_t nameStr[31];
        uint8_t nameLen;

        //User can filter data from the received data(scanRepParam->data)
        // or using "getBLE_GapAdDataByAdType()" function to filter
        // ex: get scanned deviceName
        getBLE_GapAdDataByAdType(scanRepParam, GAP_AD_TYPE_LOCAL_NAME_COMPLETE, nameStr, &nameLen);

        nameStr[nameLen] = '\0';
        printf("Found --> Name:%s Address: %02x:%02x:%02x:%02x:%02x:%02x\n",
               nameStr,
               scanRepParam->rptPeerAddr.addr[5], scanRepParam->rptPeerAddr.addr[4],
               scanRepParam->rptPeerAddr.addr[3], scanRepParam->rptPeerAddr.addr[2],
               scanRepParam->rptPeerAddr.addr[1], scanRepParam->rptPeerAddr.addr[0]);

        // received power
        printf("RSSI:%d\r\n", scanRepParam->rptRssi);
    }
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

