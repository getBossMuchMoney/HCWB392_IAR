/*****************************************************************************
 * @file    main.c
 * @version     
 * @brief
 *          Demonstrate BLE operation.
 *          Includes the basic initialization and the loop for kernel(BLE) operations.
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
#include "rf_phy.h"
#include "ble_stack_status.h"

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void setMCU_SystemPowerDown(void);
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/**************************************************************************
 * Extern Function
 **************************************************************************/
extern BleStackStatus BLE_StackInit(void);
extern void setMCU_SystemPowerDown(void);

#pragma push
//#pragma Otime
#pragma Ospace

/**
 *******************************************************************************
 ** \brief System clock init function
 **
 ** \param [in] None
 **
 ** \retval None
 **
 ******************************************************************************/
static void SystemClk_Init(void)
{
    stc_clk_sysclk_cfg_t    stcSysClkCfg;
    stc_clk_xtal_cfg_t      stcXtalCfg;
    stc_clk_mpll_cfg_t      stcMpllCfg;
    stc_sram_config_t       stcSramConfig;
    //stc_port_pub_set_t      stcPortPubSet;

    MEM_ZERO_STRUCT(stcSysClkCfg);
    MEM_ZERO_STRUCT(stcXtalCfg);
    MEM_ZERO_STRUCT(stcMpllCfg);
    MEM_ZERO_STRUCT(stcSramConfig);   
    //MEM_ZERO_STRUCT(stcPortPubSet);

    /* Set bus clk div. */
    stcSysClkCfg.enHclkDiv = ClkSysclkDiv1;   // Max 200MHz
    stcSysClkCfg.enExclkDiv = ClkSysclkDiv2;  // Max 100MHz
    stcSysClkCfg.enPclk0Div = ClkSysclkDiv1;  // Max 200MHz
    stcSysClkCfg.enPclk1Div = ClkSysclkDiv2;  // Max 100MHz
    stcSysClkCfg.enPclk2Div = ClkSysclkDiv4;  // Max 60MHz, Cur 50MHz
    stcSysClkCfg.enPclk3Div = ClkSysclkDiv4;  // Max 50MHz
    stcSysClkCfg.enPclk4Div = ClkSysclkDiv2;  // Max 100MHz
    CLK_SysClkConfig(&stcSysClkCfg);
		
    /* Switch system clock source to MPLL. */
    /* Use Xtal32 as MPLL source. */
    stcXtalCfg.enMode = ClkXtalModeOsc;
    stcXtalCfg.enDrv = ClkXtalLowDrv;
    stcXtalCfg.enFastStartup = Enable;	
    CLK_XtalConfig(&stcXtalCfg);
    CLK_XtalCmd(Enable);
//		M4_ICG->ICG1 = 1u;
//		CLK_HrcCmd(Enable);
    /* MPLL config (HRC / pllmDiv * plln / PllpDiv = 200M). */
    stcMpllCfg.pllmDiv = 1u;
    stcMpllCfg.plln = 50u;  
    stcMpllCfg.PllpDiv = 2u;
    stcMpllCfg.PllqDiv = 2u;
    stcMpllCfg.PllrDiv = 2u;
//    CLK_SetPllSource(ClkPllSrcHRC);
		CLK_SetPllSource(ClkPllSrcXTAL);
    CLK_MpllConfig(&stcMpllCfg);

    /* flash read wait cycle setting */
    EFM_Unlock();
    EFM_SetLatency(EFM_LATENCY_5);//4 cycle in 168M, 5 clcye in 200M
    EFM_Lock();

    /* sram read/write wait cycle setting */
    stcSramConfig.u8SramIdx = Sram12Idx | Sram3Idx | SramRetIdx;
    stcSramConfig.enSramRC = SramCycle2;
    stcSramConfig.enSramWC = SramCycle2;
    SRAM_Init(&stcSramConfig); 

    /* GPIO read wait cycle setting */
    //stcPortPubSet.enReadWait = WaitCycle3; //need wait 3 cycle in 126~200M CLK
    //PORT_PubSetting(&stcPortPubSet);
    
    /* Enable MPLL. */
    CLK_MpllCmd(Enable);

    /* Wait MPLL ready. */
    while (Set != CLK_GetFlagStatus(ClkFlagMPLLRdy))
    {
    }

    /* Switch system clock source to MPLL. */
    CLK_SetSysClkSource(CLKSysSrcMPLL);
}


void UartPortInit(void)
{
		PORT_SetFunc(PortC, Pin06, Func_Usart3_Tx, Disable);
    PORT_SetFunc(PortC, Pin07, Func_Usart3_Rx, Disable);
}

/*!
   \brief main loop for initialization and BLE kernel
*/
int main(void)
{
    BLE_Addr_Param bleAddrParam;
    BleStackStatus status;

    extern void BleApp_Main(void);
    extern BleStackStatus BleApp_Init(void);

    /* Init System, IP clock and multi-function I/O. */
    SystemClk_Init();

    /* Open UART0 for debug */
    UART_PrintfInit(M4_USART3,115200,UartPortInit);

    /* Init BLE Stack */
    status = BLE_StackInit();
    if (status != BLESTACK_STATUS_SUCCESS)
    {
        printf("BLE_StackInit() returns fail %d\n", status);
        while (1);
    }

    printf("------------------------------------\r\n");
    printf("  BLE demo: BeaconRx start...\r\n");
    printf("------------------------------------\r\n");
    printf("Chip_ID=0x%x\r\n",getBLE_ChipId());

    /* Set BD ADDR */
    bleAddrParam.addrType = PUBLIC_ADDR;
//    bleAddrParam.addr[0] = 0x81;
//    bleAddrParam.addr[1] = 0x82;
//    bleAddrParam.addr[2] = 0x83;
//    bleAddrParam.addr[3] = 0x84;
//    bleAddrParam.addr[4] = 0x85;
//    bleAddrParam.addr[5] = 0x56;
    bleAddrParam.addr[0] =  M4_EFM->UQID3 & 0x0FF;
    bleAddrParam.addr[1] = (M4_EFM->UQID3 >>8) & 0x0FF;
    bleAddrParam.addr[2] = (M4_EFM->UQID3 >>16) & 0x0FF;
    bleAddrParam.addr[3] = (M4_EFM->UQID3 >>24) & 0x0FF;
    bleAddrParam.addr[4] =  M4_EFM->UQID2 & 0x0FF;
    bleAddrParam.addr[5] = (M4_EFM->UQID2 >>8) & 0x0FF;  
    setBLE_BleDeviceAddr(&bleAddrParam);
    printf("ble addr:%x,%x,%x,%x,%x,%x",bleAddrParam.addr[0],bleAddrParam.addr[1],bleAddrParam.addr[2],bleAddrParam.addr[3],bleAddrParam.addr[4],bleAddrParam.addr[5]);
    if (status != BLESTACK_STATUS_SUCCESS)
    {
        printf("setBLE_BleDeviceAddr() returns fail %d\n", status);
    }

    /* Initial BLE App */
    status = BleApp_Init();
    if (status != BLESTACK_STATUS_SUCCESS)
    {
        printf("BleApp_Init() returns fail %d\n", status);
        while (1);
    }

    while (1)
    {
        /* Run BLE kernel, the task priority is LL > Host */
        if (setBLE_KernelStateHandle() == BLESTACK_STATUS_FREE)
        {
            BleApp_Main();

            /* System enter Power Down mode & wait interrupt event. */
            setMCU_SystemPowerDown();
        }
    }
}

/**
 *******************************************************************************
 ** \brief SystemPowerDown function
 **
 ** \param [in]  None
 **
 ** \retval none
 **
 ******************************************************************************/
static void setMCU_SystemPowerDown(void)
{
    if(getRF_Mode() == BLERFMODE_SLEEP)  //RF_sleep
    {
       /* Enter to Power-down mode */
    }
    else
    {   
				//clk idle   			
    }
}

/**
 *******************************************************************************
 ** \brief Delay function, delay 1ms approximately
 **
 ** \param [in]  u32Cnt                 ms
 **
 ** \retval none
 **
 ******************************************************************************/
void Tiny_Delay1ms(uint32_t u32Cnt)
{
    volatile uint32_t i = 0ul;
    uint32_t u32Cyc = 0ul;

    u32Cyc = SystemCoreClock;     //200M
    u32Cyc = u32Cyc / 20000ul;
    while (u32Cnt-- > 0ul)
    {
        i = u32Cyc;
        while (i-- > 0ul)
        {
            ;
        }
    }
}

/**
 *******************************************************************************
 ** \brief Delay function, delay 1us approximately
 **
 ** \param [in]  u32Cnt                 us
 **
 ** \retval none
 **
 ******************************************************************************/
void Tiny_Delay1us(uint32_t u32Cnt)
{
    uint32_t u32Cyc = 1ul;
    volatile uint32_t i = 0ul;

    if(SystemCoreClock > 10000000ul)    //200M
    {
        u32Cyc = SystemCoreClock / 20000000ul;
        while(u32Cnt-- > 0ul)
        {
            i = u32Cyc;
            while (i-- > 0ul)
            {
                ;
            }
        }
    }
    else
    {
         while(u32Cnt-- > 0ul)
         {
            ;
         }
    }
}

#pragma pop




