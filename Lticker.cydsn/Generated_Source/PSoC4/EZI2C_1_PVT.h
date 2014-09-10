/*******************************************************************************
* File Name: .h
* Version 1.20
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_EZI2C_1_H)
#define CY_SCB_PVT_EZI2C_1_H

#include "EZI2C_1.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define EZI2C_1_SetI2CExtClkInterruptMode(interruptMask) EZI2C_1_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define EZI2C_1_ClearI2CExtClkInterruptSource(interruptMask) EZI2C_1_CLEAR_INTR_I2C_EC(interruptMask)
#define EZI2C_1_GetI2CExtClkInterruptSource()                (EZI2C_1_INTR_I2C_EC_REG)
#define EZI2C_1_GetI2CExtClkInterruptMode()                  (EZI2C_1_INTR_I2C_EC_MASK_REG)
#define EZI2C_1_GetI2CExtClkInterruptSourceMasked()          (EZI2C_1_INTR_I2C_EC_MASKED_REG)

#if(!EZI2C_1_CY_SCBIP_V1_I2C_ONLY)
/* APIs to service INTR_SPI_EC register */
#define EZI2C_1_SetSpiExtClkInterruptMode(interruptMask) EZI2C_1_WRITE_INTR_SPI_EC_MASK(interruptMask)
#define EZI2C_1_ClearSpiExtClkInterruptSource(interruptMask) EZI2C_1_CLEAR_INTR_SPI_EC(interruptMask)
#define EZI2C_1_GetExtSpiClkInterruptSource()                 (EZI2C_1_INTR_SPI_EC_REG)
#define EZI2C_1_GetExtSpiClkInterruptMode()                   (EZI2C_1_INTR_SPI_EC_MASK_REG)
#define EZI2C_1_GetExtSpiClkInterruptSourceMasked()           (EZI2C_1_INTR_SPI_EC_MASKED_REG)
#endif /* (!EZI2C_1_CY_SCBIP_V1_I2C_ONLY) */

#if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void EZI2C_1_SetPins(uint32 mode, uint32 subMode, uint32 uartTxRx);
#endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if !defined (CY_REMOVE_EZI2C_1_CUSTOM_INTR_HANDLER)
    extern cyisraddress EZI2C_1_customIntrHandler;
#endif /* !defined (CY_REMOVE_EZI2C_1_CUSTOM_INTR_HANDLER) */

extern EZI2C_1_BACKUP_STRUCT EZI2C_1_backup;

#if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common config vars */
    extern uint8 EZI2C_1_scbMode;
    extern uint8 EZI2C_1_scbEnableWake;
    extern uint8 EZI2C_1_scbEnableIntr;

    /* I2C config vars */
    extern uint8 EZI2C_1_mode;
    extern uint8 EZI2C_1_acceptAddr;

    /* SPI/UART config vars */
    extern volatile uint8 * EZI2C_1_rxBuffer;
    extern uint8   EZI2C_1_rxDataBits;
    extern uint32  EZI2C_1_rxBufferSize;

    extern volatile uint8 * EZI2C_1_txBuffer;
    extern uint8   EZI2C_1_txDataBits;
    extern uint32  EZI2C_1_txBufferSize;

    /* EZI2C config vars */
    extern uint8 EZI2C_1_numberOfAddr;
    extern uint8 EZI2C_1_subAddrSize;
#endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*  Conditional Macro
****************************************/

#if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Define run time operation mode */
    #define EZI2C_1_SCB_MODE_I2C_RUNTM_CFG     (EZI2C_1_SCB_MODE_I2C      == EZI2C_1_scbMode)
    #define EZI2C_1_SCB_MODE_SPI_RUNTM_CFG     (EZI2C_1_SCB_MODE_SPI      == EZI2C_1_scbMode)
    #define EZI2C_1_SCB_MODE_UART_RUNTM_CFG    (EZI2C_1_SCB_MODE_UART     == EZI2C_1_scbMode)
    #define EZI2C_1_SCB_MODE_EZI2C_RUNTM_CFG   (EZI2C_1_SCB_MODE_EZI2C    == EZI2C_1_scbMode)
    #define EZI2C_1_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (EZI2C_1_SCB_MODE_UNCONFIG == EZI2C_1_scbMode)

    /* Define wakeup enable */
    #define EZI2C_1_SCB_WAKE_ENABLE_CHECK        (0u != EZI2C_1_scbEnableWake)
#endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */

#endif /* (CY_SCB_PVT_EZI2C_1_H) */


/* [] END OF FILE */
