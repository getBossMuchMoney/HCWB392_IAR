#ifndef _BLE_SERVICE_DATA_EXCHANGE_H_
#define _BLE_SERVICE_DATA_EXCHANGE_H_

/**************************************************************************//**
 * @file  ble_service_data_exchange.h
*****************************************************************************/
#include "ble_cmd.h"
#include "ble_host.h"
#include "ble_service_base.h"

/**************************************************************************
 * Data Exchange Definitions
 **************************************************************************/
/** @defgroup DataExchange_def BLE Data Exchange Definitions
* @{
* @ingroup service_def
* @details Here shows the definitions of the Data Exchange service.
* @}
**************************************************************************/

/**
 * @ingroup DataExchange_def
 * @defgroup DataExchange_UUIDDef BLE Data Exchange UUID Definitions
 * @{
 * @details Here shows the definitions of the BLE Data Exchange UUID Definitions.
*/
extern const uint16_t ATTR_UUID_DATA_EXCHANGE_PRIMARY_SERVICE[];              /**< Data Exchange service UUID. */
extern const uint16_t ATTR_UUID_DATA_EXCHANGE_CHARC_WRITE[];                  /**< Data Exchange characteristic Write UUID. */
extern const uint16_t ATTR_UUID_DATA_EXCHANGE_CHARC_NOTIFY_INDICATE[];        /**< Data Exchange characteristic Notify and Indicate UUID. */
/** @} */



/**
 * @defgroup serviceDataExchange_ServiceChardef BLE Data Exchange Service and Characteristic Definitions
 * @{
 * @ingroup serviceDataExchange_def
 * @details Here shows the definitions of the Data sExchange service and characteristic.
 * @}
*/


/**
 * @ingroup serviceDataExchange_ServiceChardef
 * @{
*/
extern const ATTRIBUTE_BLE ATT_DATA_EXCHANGE_PRIMARY_SERVICE;
extern const ATTRIBUTE_BLE ATT_DATA_EXCHANGE_CHARACTERISTIC_WRITE;
extern const ATTRIBUTE_BLE ATT_DATA_EXCHANGE_WRITE;
extern const ATTRIBUTE_BLE ATT_DATA_EXCHANGE_CHARACTERISTIC_NOTIFY_INDICATE;
extern const ATTRIBUTE_BLE ATT_DATA_EXCHANGE_NOTIFY_INDICATE;
extern const ATTRIBUTE_BLE ATT_DATA_EXCHANGE_NOTIFY_INDICATE_CLIENT_CHARC_CONFIGURATION;
/** @} */

/** Data Exchange Service Definition
 * @ingroup serviceDataExchange_ServiceChardef
*/
#define ATT_DATA_EXCHANGE_SERVICE                                   \
    &ATT_DATA_EXCHANGE_PRIMARY_SERVICE,                             \
    &ATT_DATA_EXCHANGE_CHARACTERISTIC_WRITE,                        \
    &ATT_DATA_EXCHANGE_WRITE,                                       \
    &ATT_DATA_EXCHANGE_CHARACTERISTIC_NOTIFY_INDICATE,              \
    &ATT_DATA_EXCHANGE_NOTIFY_INDICATE,                             \
    &ATT_DATA_EXCHANGE_NOTIFY_INDICATE_CLIENT_CHARC_CONFIGURATION,  \


/**************************************************************************
 * Data Exchange Application Definitions
 ********** ****************************************************************/
/**
* @defgroup appDataExchange_def BLE Data Exchange Application Definitions
* @{
* @ingroup serviceDataExchange_def
* @details Here shows the definitions of the Data Exchange service for application.
* @}
**************************************************************************/
/**
 * @ingroup appDataExchange_def
 * @defgroup appDataExchange_def BLE Data Exchange Service and Characteristic Definitions
 * @{
 * @details Here shows the event definitions of the Data Exchange service.
*/
#define BLESERVICE_DATA_EXCHANGE_WRITE_EVENT                        0x01   /**< Data Exchange write write event. */
#define BLESERVICE_DATA_EXCHANGE_WRITE_RSP_EVENT                    0x02   /**< Data Exchange write write response event. */
#define BLESERVICE_DATA_EXCHANGE_NOTIFY_INDICATE_EVENT              0x03   /**< Data Exchange notify_indicate event. */
#define BLESERVICE_DATA_EXCHANGE_NOTIFY_INDICATE_CCCD_WRITE_EVENT   0x04   /**< Data Exchange notify_indicate cccd write event. */
#define BLESERVICE_DATA_EXCHANGE_NOTIFY_INDICATE_CCCD_READ_EVENT    0x05   /**< Data Exchange notify_indicate cccd read event. */
/** @} */


/**
 * @ingroup appDataExchange_def
 * @defgroup appDataExchange_structureDef BLE Data Exchange Structure Definitions
 * @{
 * @details Here shows the structure definitions of the Data Exchange service.
 * @}
*/

/** Data Exchange Service Handles Definition
 * @ingroup appDataExchange_def
*/
typedef struct BLEATT_DATA_EXCHANGE_Handles
{
    uint16_t hdl_write;                     /**< Handle of write. */
    uint16_t hdl_notify_indicate;           /**< Handle of notify and indicate. */
    uint16_t hdl_notify_indicate_cccd;      /**< Handle of notify and indicate cccd. */
} BLEATT_DATA_EXCHANGE_Handles;



/** Data Exchange Service Handles Definition
 * @ingroup appHRS_def
 * @note User defined.
*/
typedef struct BLEATT_DATA_EXCHANGE_Data
{
    uint16_t  notify_indicate_cccd;           /**< Notify and indicate cccd value */
} BLEATT_DATA_EXCHANGE_Data;



/** Data Exchange Application Data Structure Definition
 * @ingroup appDataExchange_structureDef
*/
typedef struct BLEATT_DATA_EXCHANGE_Info
{
    BleGattRole                     role;     /**< Host role */
    BLEATT_DATA_EXCHANGE_Handles    handles;  /**< Data Exchange Service attribute handles */
    BLEATT_DATA_EXCHANGE_Data       data;     /**< Data Exchange Service attribute data */
} BLEATT_DATA_EXCHANGE_Info;


/**
 * @ingroup appDataExchange_def
 * @defgroup appDataExchange_App BLE Data Exchange Definitions for Application
 * @{
 * @details Here shows the definitions of the Data Exchange service for application uses.
 * @}
*/

/** DataExchange_EventCallBack
 * @ingroup appDataExchange_App
 * @note This callback receives the Data Exchange service events. Each of these events can be associated with parameters.  *
 */
typedef void (*BleDataExchange_EventCallBack)(uint8_t hostId, uint8_t cmdAccess, uint8_t *data, uint16_t length);


/** DataExchange Service Initialization
 *
 * @ingroup appDataExchange_App
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
BleStackStatus setDataExchange_ServiceInit(uint8_t hostId, BleGattRole gattRole, BLEATT_DATA_EXCHANGE_Info *info, BleDataExchange_EventCallBack callback);


/** Get Data Exchange Service Handle Numbers
 *
 * @ingroup appDataExchange_App
 *
 * @attention - gattRole = @ref BLE_GATT_ROLE_CLIENT: \n
 *              MUST call this API to get service information after received @ref BLECMD_EVENT_ATT_DATABASE_PARSING_FINISHED  \n
 *            - gattRole = @ref BLE_GATT_ROLE_SERVER: \n
 *              MUST call this API to get service information before connection established. \n
 *
 * @param[in] hostId : the link's host id.
 * @param[out] info : a pointer to Data Exchange information
 *
 * @retval BLESTACK_STATUS_ERR_INVALID_HOSTID : Error host id.
 * @retval BLESTACK_STATUS_ERR_INVALID_PARAM : Invalid parameter.
 * @retval BLESTACK_STATUS_SUCCESS  : Setting success.
*/
BleStackStatus getDataExchange_ServiceHandles(uint8_t hostId, BLEATT_DATA_EXCHANGE_Info *info);

#endif  //#ifndef _BLE_SERVICE_DATA_EXCHANGE_H_
