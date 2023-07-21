/************************************************************************
 *
 * File Name  : BLE_SERVICE_DATA_EXCHANGE.c
 * Description: This file contains the definitions and functions of BLE Data Exchange
 *
 *
 *************************************************************************
 *
 *      Copyright (c) 2020, All Right Reserved
 *      XHSC Microelectronics Co. Ltd.
 *      Taiwan, R.O.C.
 *
 *******************************************************************/
#include "ble_service_data_exchange.h"
#include "ble_profile.h"

/** ATTR_VALUE_DATA_EXCHANGE_General_Access
 * @note This callback receives the GATT events.  \n
 *  Each of these events can be associated with parameters.
 *
 */
void ATTR_VALUE_DATA_EXCHANGE_General_Access(BLE_Event_AttParam *attParam);


/**************************************************************************
 * DIS Service UUID Definitions
 **************************************************************************/

/** Data Exchange Service UUID.
 * @note 128-bits UUID
 * @note UUID: 00005301-0000-0041-4C50-574953450000
*/
const uint16_t ATTR_UUID_DATA_EXCHANGE_PRIMARY_SERVICE[] =
{
    0x0000, 0x5345,
    0x5749, 0x4C50,
    0x0041, 0x0000,
    0x5301, 0x0000,
};

/** Data Exchange characteristic Write UUID.
 * @note 128-bits UUID
 * @note UUID: 00005302-0000-0041-4C50-574953450000
*/
const uint16_t ATTR_UUID_DATA_EXCHANGE_CHARC_WRITE[] =
{
    0x0000, 0x5345,
    0x5749, 0x4C50,
    0x0041, 0x0000,
    0x5302, 0x0000,
};

/** Data Exchange characteristic Notify / Indicate UUID.
 * @note 128-bits UUID
 * @note UUID: 00005303-0000-0041-4C50-574953450000
*/
const uint16_t ATTR_UUID_DATA_EXCHANGE_CHARC_NOTIFY_INDICATE[] =
{
    0x0000, 0x5345,
    0x5749, 0x4C50,
    0x0041, 0x0000,
    0x5303, 0x0000,
};



/**************************************************************************
 * Data Exchange Service/ Characteristic Definitions
 **************************************************************************/
const ATTRIBUTE_BLE ATT_DATA_EXCHANGE_PRIMARY_SERVICE =
{
    (void *)ATTR_UUID_TYPE_PRIMARY_SERVICE,
    (void *)ATTR_UUID_DATA_EXCHANGE_PRIMARY_SERVICE,
    sizeof(ATTR_UUID_DATA_EXCHANGE_PRIMARY_SERVICE),
    (
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_VALUE_BOND_ENABLE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    ATTR_NULL_Access,                       //This function should be set to ATTR_NULL_Access when lenValue or uuidValue is a null value.
};


const ATTRIBUTE_BLE ATT_DATA_EXCHANGE_CHARACTERISTIC_WRITE =
{
    (void *)ATTR_UUID_TYPE_CHARACTERISTIC,
    (void *)ATTR_UUID_DATA_EXCHANGE_CHARC_WRITE,
    sizeof(ATTR_UUID_DATA_EXCHANGE_CHARC_WRITE),
    (
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |            //otherwise, 128bit UUID
        //ATT_VALUE_BOND_ENABLE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    ATTR_NULL_Access,                       //This function should be set to ATTR_NULL_Access when lenValue or uuidValue is a null value.
};


const ATTRIBUTE_BLE ATT_DATA_EXCHANGE_WRITE =
{
    (void *)ATTR_UUID_DATA_EXCHANGE_CHARC_WRITE,
    (void *)0,
    0,
    (
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        //GATT_DECLARATIONS_PROPERTIES_READ |
        GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (
        //ATT_TYPE_FORMAT_16UUID |
        //ATT_VALUE_BOND_ENABLE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    ATTR_VALUE_DATA_EXCHANGE_General_Access,       //ATTR_VALUE_DATA_EXCHANGE_General_Access,
};


const ATTRIBUTE_BLE ATT_DATA_EXCHANGE_CHARACTERISTIC_NOTIFY_INDICATE =
{
    (void *)ATTR_UUID_TYPE_CHARACTERISTIC,
    (uint16_t *)ATTR_UUID_DATA_EXCHANGE_CHARC_NOTIFY_INDICATE,
    sizeof(ATTR_UUID_DATA_EXCHANGE_CHARC_NOTIFY_INDICATE),
    (
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |            //otherwise, 128bit UUID
        //ATT_VALUE_BOND_ENABLE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    ATTR_NULL_Access,                       //This function should be set to ATTR_NULL_Access when lenValue or uuidValue is a null value.
};

const ATTRIBUTE_BLE ATT_DATA_EXCHANGE_NOTIFY_INDICATE =
{
    (void *)ATTR_UUID_DATA_EXCHANGE_CHARC_NOTIFY_INDICATE,
    (void *)0,
    0,
    (
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        //GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (
        //ATT_TYPE_FORMAT_16UUID |            //otherwise, 128bit UUID
        //ATT_VALUE_BOND_ENABLE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    ATTR_VALUE_DATA_EXCHANGE_General_Access,       //ATTR_VALUE_DATA_EXCHANGE_General_Access,
};


const ATTRIBUTE_BLE ATT_DATA_EXCHANGE_NOTIFY_INDICATE_CLIENT_CHARC_CONFIGURATION =
{
    (void *)ATTR_UUID_TYPE_CLIENT_CHARC_CONFIGURATION,
    (void *)0,
    0,
    (
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |            //otherwise, 128bit UUID
        //ATT_VALUE_BOND_ENABLE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    ATTR_VALUE_DATA_EXCHANGE_General_Access,       //ATTR_VALUE_DATA_EXCHANGE_General_Access,
};

/**************************************************************************
 * BLE Service << DataExchange >> Local Variable
 **************************************************************************/
#ifndef MAX_NUM_CONN_DATAEXCHANGE
// check MAX_NUM_CONN_DATAEXCHANGE if defined or set to default 1.
#define MAX_NUM_CONN_DATAEXCHANGE       1
#endif


// Service basic information
Service_Basic_Info                dataExchangeBasicInfo[MAX_NUM_CONN_DATAEXCHANGE];

// Data Exchange information
BLEATT_DATA_EXCHANGE_Info         *dataExchangeInfo[MAX_NUM_CONN_DATAEXCHANGE];

// Data Exchange callback function
BleDataExchange_EventCallBack     dataExchangeCallback[MAX_NUM_CONN_DATAEXCHANGE];

// Data Exchange registered total count
uint8_t dataExchange_count = 0;

/**************************************************************************
 * BLE Service << Data Exchange >> Public Function
 **************************************************************************/
/** DataExchange Service Initialization
 *
 * @param[in] hostId : the link's host id.
 * @param[in] gattRole : @ref BleGattRole "BLE GATT role".
 * @param[in] info : a pointer to DataExchange information.
 * @param[in] callback : a pointer to a callback function that receive the service events.
 *
 * @retval BLESTACK_STATUS_ERR_INVALID_HOSTID : Error host id.
 * @retval BLESTACK_STATUS_ERR_INVALID_PARAM : Invalid parameter.
 * @retval BLESTACK_STATUS_ERR_NOT_SUPPORTED : Registered services buffer full.
 * @retval BLESTACK_STATUS_SUCCESS  : Setting success.
*/
BleStackStatus setDataExchange_ServiceInit(uint8_t hostId, BleGattRole gattRole, BLEATT_DATA_EXCHANGE_Info *info, BleDataExchange_EventCallBack callback)
{
    BleStackStatus status;
    uint8_t config_index;

    if (info == NULL)
    {
        return BLESTACK_STATUS_ERR_INVALID_PARAM;
    }

    // init service basic information and get "config_index" & "dataExchange_count"
    status = setBLE_ServiceBasicInit(hostId, gattRole, MAX_NUM_CONN_DATAEXCHANGE, dataExchangeBasicInfo, &config_index, &dataExchange_count);
    BLESTACK_STATUS_CHECK(status);

    // Set service role
    info->role = gattRole;

    // Set Data Exchange data
    dataExchangeInfo[config_index] = info;

    // Register Data Exchange callback function
    dataExchangeCallback[config_index] = callback;

    // Get handles at initialization if role is set to BLE_GATT_ROLE_SERVER
    if (gattRole == BLE_GATT_ROLE_SERVER)
    {
        status = getDataExchange_ServiceHandles(hostId, dataExchangeInfo[config_index]);
        BLESTACK_STATUS_CHECK(status);
    }

    return BLESTACK_STATUS_SUCCESS;
}


/** Get Data Exchange Service Handle Numbers
 *
 * @attention - gattRole = @ref BLE_GATT_ROLE_CLIENT: \n
 *              MUST call this API to get service information after received @ref BLECMD_EVENT_ATT_DATABASE_PARSING_FINISHED  \n
 *            - gattRole = @ref BLE_GATT_ROLE_SERVER: \n
 *              MUST call this API to get service information before connection established. \n
 *
 * @param[in] hostId : the link's host id.
 * @param[out] info : a pointer to Data Exchange information.
 *
 * @retval BLESTACK_STATUS_ERR_INVALID_HOSTID : Error host id.
 * @retval BLESTACK_STATUS_ERR_INVALID_PARAM : Invalid parameter.
 * @retval BLESTACK_STATUS_SUCCESS  : Setting success.
*/
BleStackStatus getDataExchange_ServiceHandles(uint8_t hostId, BLEATT_DATA_EXCHANGE_Info *info)
{
    BleStackStatus status;

    // Get Data Exchange handles
    status = getBLEGATT_HandleNumAddr(hostId, info->role, (ATTRIBUTE_BLE *)&ATT_DATA_EXCHANGE_PRIMARY_SERVICE, (void *)&info->handles);
    BLESTACK_STATUS_CHECK(status);

    return BLESTACK_STATUS_SUCCESS;
}


/**************************************************************************
 * BLE Service << Data Exchange >> General Callback Function
 **************************************************************************/
static void bleDataExchange_PostEvent(BLE_Event_AttParam *attParam, BleDataExchange_EventCallBack *callback)
{
    // check callback is null or not
    SERVICE_CALLBACK_NULL_CHECK(*callback);

    // post event to user
    (*callback)(attParam->hostId, attParam->cmdAccess, attParam->data, attParam->length);
}

// handle DataExchange client GATT event
static void handle_DataExchange_client(uint8_t index, BLE_Event_AttParam *attParam)
{
    switch (attParam->cmdAccess)
    {
    case OPCODE_ATT_WRITE_RESPONSE:
        break;

    case OPCODE_ATT_HANDLE_VALUE_NOTIFICATION:
        if (attParam->hdlNum == dataExchangeInfo[index]->handles.hdl_notify_indicate)
        {
            // received notification from server -> post to user
            attParam->cmdAccess = BLESERVICE_DATA_EXCHANGE_NOTIFY_INDICATE_EVENT;
            bleDataExchange_PostEvent(attParam, &dataExchangeCallback[index]);
        }
        break;

    case OPCODE_ATT_HANDLE_VALUE_INDICATION:
        break;

    default:
        break;
    }
}

// handle DataExchange server GATT event
static void handle_DataExchange_server(uint8_t index, BLE_Event_AttParam *attParam)
{
    switch (attParam->cmdAccess)
    {
    case OPCODE_ATT_WRITE_COMMAND:
        if (attParam->hdlNum == dataExchangeInfo[index]->handles.hdl_write)
        {
            // received write command from client -> post to user
            attParam->cmdAccess = BLESERVICE_DATA_EXCHANGE_WRITE_EVENT;
            bleDataExchange_PostEvent(attParam, &dataExchangeCallback[index]);
        }
        break;

    case OPCODE_ATT_WRITE_REQUEST:
        if (attParam->hdlNum == dataExchangeInfo[index]->handles.hdl_notify_indicate_cccd)
        {
            // update server defined cccd value
            setBLEGATT_HandleCCCDWriteRequest(attParam->data, attParam->length, &dataExchangeInfo[index]->data.notify_indicate_cccd);
        }
        else if (attParam->hdlNum == dataExchangeInfo[index]->handles.hdl_write)
        {
            // received write request from client -> post to user
            attParam->cmdAccess = BLESERVICE_DATA_EXCHANGE_WRITE_EVENT;
            bleDataExchange_PostEvent(attParam, &dataExchangeCallback[index]);
        }
        break;

    case OPCODE_ATT_READ_REQUEST:
        if (attParam->hdlNum == dataExchangeInfo[index]->handles.hdl_notify_indicate_cccd)
        {
            // send cccd Read Response
            setBLEGATT_HandleCCCDReadRequest(attParam->hostId,
                                             dataExchangeInfo[index]->handles.hdl_notify_indicate_cccd,
                                             dataExchangeInfo[index]->data.notify_indicate_cccd);
        }
        break;

    default:
        break;
    }
}

void ATTR_VALUE_DATA_EXCHANGE_General_Access(BLE_Event_AttParam *attParam)
{
    uint8_t index;

    if (queryIndexByHostIdGattRole(attParam->hostId, attParam->gattRole, MAX_NUM_CONN_DATAEXCHANGE, dataExchangeBasicInfo, &index) != BLESTACK_STATUS_SUCCESS)
    {
        // Host id has not registered so there is no callback function -> do nothing
        return;
    }

    if (attParam->gattRole == BLE_GATT_ROLE_CLIENT)
    {
        // handle DataExchange client GATT event
        handle_DataExchange_client(index, attParam);
    }

    if (attParam->gattRole == BLE_GATT_ROLE_SERVER)
    {
        // handle DataExchange server GATT event
        handle_DataExchange_server(index, attParam);
    }
}

