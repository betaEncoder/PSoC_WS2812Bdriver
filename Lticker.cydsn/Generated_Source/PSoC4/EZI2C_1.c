/*******************************************************************************
* File Name: EZI2C_1.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the SCB Component.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "EZI2C_1_PVT.h"

#if(EZI2C_1_SCB_MODE_I2C_INC)
    #include "EZI2C_1_I2C_PVT.h"
#endif /* (EZI2C_1_SCB_MODE_I2C_INC) */

#if(EZI2C_1_SCB_MODE_EZI2C_INC)
    #include "EZI2C_1_EZI2C_PVT.h"
#endif /* (EZI2C_1_SCB_MODE_EZI2C_INC) */

#if(EZI2C_1_SCB_MODE_SPI_INC || EZI2C_1_SCB_MODE_UART_INC)
    #include "EZI2C_1_SPI_UART_PVT.h"
#endif /* (EZI2C_1_SCB_MODE_SPI_INC || EZI2C_1_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for unconfigured mode */
#if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common config vars */
    uint8 EZI2C_1_scbMode = EZI2C_1_SCB_MODE_UNCONFIG;
    uint8 EZI2C_1_scbEnableWake;
    uint8 EZI2C_1_scbEnableIntr;

    /* I2C config vars */
    uint8 EZI2C_1_mode;
    uint8 EZI2C_1_acceptAddr;

    /* SPI/UART config vars */
    volatile uint8 * EZI2C_1_rxBuffer;
    uint8  EZI2C_1_rxDataBits;
    uint32 EZI2C_1_rxBufferSize;

    volatile uint8 * EZI2C_1_txBuffer;
    uint8  EZI2C_1_txDataBits;
    uint32 EZI2C_1_txBufferSize;

    /* EZI2C config vars */
    uint8 EZI2C_1_numberOfAddr;
    uint8 EZI2C_1_subAddrSize;
#endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 EZI2C_1_initVar = 0u;

#if !defined (CY_REMOVE_EZI2C_1_CUSTOM_INTR_HANDLER)
    cyisraddress EZI2C_1_customIntrHandler = NULL;
#endif /* !defined (CY_REMOVE_EZI2C_1_CUSTOM_INTR_HANDLER) */


/***************************************
*    Private Function Prototypes
***************************************/

static void EZI2C_1_ScbEnableIntr(void);
static void EZI2C_1_ScbModeStop(void);


/*******************************************************************************
* Function Name: EZI2C_1_Init
********************************************************************************
*
* Summary:
*  Initializes the SCB component to operate in one of the selected configurations:
*  I2C, SPI, UART or EZ I2C.
*  When the configuration is set to ÅgUnconfigured SCBÅh, this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SCB_I2CInit, SCB_SpiInit, SCB_UartInit or SCB_EzI2CInit.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void EZI2C_1_Init(void)
{
#if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    if(EZI2C_1_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        EZI2C_1_initVar = 0u; /* Clear init var */
    }
    else
    {
        /* Initialization was done before call */
    }

#elif(EZI2C_1_SCB_MODE_I2C_CONST_CFG)
    EZI2C_1_I2CInit();

#elif(EZI2C_1_SCB_MODE_SPI_CONST_CFG)
    EZI2C_1_SpiInit();

#elif(EZI2C_1_SCB_MODE_UART_CONST_CFG)
    EZI2C_1_UartInit();

#elif(EZI2C_1_SCB_MODE_EZI2C_CONST_CFG)
    EZI2C_1_EzI2CInit();

#endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: EZI2C_1_Enable
********************************************************************************
*
* Summary:
*  Enables the SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void EZI2C_1_Enable(void)
{
#if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if(!EZI2C_1_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        EZI2C_1_CTRL_REG |= EZI2C_1_CTRL_ENABLED;

        EZI2C_1_ScbEnableIntr();
    }
#else
    EZI2C_1_CTRL_REG |= EZI2C_1_CTRL_ENABLED;

    EZI2C_1_ScbEnableIntr();
#endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: EZI2C_1_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to ÅgUnconfigured SCBÅh, the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZ I2C. Otherwise this function does not enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  EZI2C_1_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void EZI2C_1_Start(void)
{
    if(0u == EZI2C_1_initVar)
    {
        EZI2C_1_Init();
        EZI2C_1_initVar = 1u; /* Component was initialized */
    }

    EZI2C_1_Enable();
}


/*******************************************************************************
* Function Name: EZI2C_1_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component and its interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void EZI2C_1_Stop(void)
{
#if(EZI2C_1_SCB_IRQ_INTERNAL)
    EZI2C_1_DisableInt();
#endif /* (EZI2C_1_SCB_IRQ_INTERNAL) */

    EZI2C_1_CTRL_REG &= (uint32) ~EZI2C_1_CTRL_ENABLED;  /* Disable SCB block */

#if(EZI2C_1_SCB_IRQ_INTERNAL)
    EZI2C_1_ClearPendingInt();
#endif /* (EZI2C_1_SCB_IRQ_INTERNAL) */

    EZI2C_1_ScbModeStop(); /* Calls scbMode specific Stop function */
}


/*******************************************************************************
* Function Name: EZI2C_1_SetCustomInterruptHandler
********************************************************************************
*
* Summary:
*  Registers a function to be called by the internal interrupt handler.
*  First the function that is registered is called, then the internal interrupt
*  handler performs any operations such as software buffer management functions
*  before the interrupt returns.  It is the user's responsibility not to break the
*  software buffer operations. Only one custom handler is supported, which is
*  the function provided by the most recent call.
*  At initialization time no custom handler is registered.
*
* Parameters:
*  func: Pointer to the function to register.
*        The value NULL indicates to remove the current custom interrupt
*        handler.
*
* Return:
*  None
*
*******************************************************************************/
void EZI2C_1_SetCustomInterruptHandler(cyisraddress func)
{
#if !defined (CY_REMOVE_EZI2C_1_CUSTOM_INTR_HANDLER)
    EZI2C_1_customIntrHandler = func; /* Register interrupt handler */
#else
    if(NULL != func)
    {
        /* Suppress compiler warning */
    }
#endif /* !defined (CY_REMOVE_EZI2C_1_CUSTOM_INTR_HANDLER) */
}


/*******************************************************************************
* Function Name: EZI2C_1_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables an interrupt for a specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void EZI2C_1_ScbEnableIntr(void)
{
#if(EZI2C_1_SCB_IRQ_INTERNAL)
    #if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Enable interrupt in the NVIC */
        if(0u != EZI2C_1_scbEnableIntr)
        {
            EZI2C_1_EnableInt();
        }
    #else
        EZI2C_1_EnableInt();

    #endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (EZI2C_1_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: EZI2C_1_ScbModeStop
********************************************************************************
*
* Summary:
*  Calls the Stop function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void EZI2C_1_ScbModeStop(void)
{
#if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    if(EZI2C_1_SCB_MODE_I2C_RUNTM_CFG)
    {
        EZI2C_1_I2CStop();
    }
    else if(EZI2C_1_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        EZI2C_1_EzI2CStop();
    }
    else
    {
        /* Do nohing for other modes */
    }
#elif(EZI2C_1_SCB_MODE_I2C_CONST_CFG)
    EZI2C_1_I2CStop();

#elif(EZI2C_1_SCB_MODE_EZI2C_CONST_CFG)
    EZI2C_1_EzI2CStop();

#endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: EZI2C_1_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartTxRx:  Direction for UART.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EZI2C_1_SetPins(uint32 mode, uint32 subMode, uint32 uartTxRx)
    {
        uint32 hsiomSel [EZI2C_1_SCB_PINS_NUMBER];
        uint32 pinsDm   [EZI2C_1_SCB_PINS_NUMBER];
        uint32 pinsInBuf = 0u;

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for(i = 0u; i < EZI2C_1_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = EZI2C_1_HSIOM_DEF_SEL;
            pinsDm[i]    = EZI2C_1_PIN_DM_ALG_HIZ;
        }

        if((EZI2C_1_SCB_MODE_I2C   == mode) ||
           (EZI2C_1_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[EZI2C_1_MOSI_SCL_RX_PIN_INDEX] = EZI2C_1_HSIOM_I2C_SEL;
            hsiomSel[EZI2C_1_MISO_SDA_TX_PIN_INDEX] = EZI2C_1_HSIOM_I2C_SEL;

            pinsDm[EZI2C_1_MOSI_SCL_RX_PIN_INDEX] = EZI2C_1_PIN_DM_OD_LO;
            pinsDm[EZI2C_1_MISO_SDA_TX_PIN_INDEX] = EZI2C_1_PIN_DM_OD_LO;
        }
    #if(!EZI2C_1_CY_SCBIP_V1_I2C_ONLY)
        else if(EZI2C_1_SCB_MODE_SPI == mode)
        {
            hsiomSel[EZI2C_1_MOSI_SCL_RX_PIN_INDEX] = EZI2C_1_HSIOM_SPI_SEL;
            hsiomSel[EZI2C_1_MISO_SDA_TX_PIN_INDEX] = EZI2C_1_HSIOM_SPI_SEL;
            hsiomSel[EZI2C_1_SCLK_PIN_INDEX]        = EZI2C_1_HSIOM_SPI_SEL;

            if(EZI2C_1_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[EZI2C_1_MOSI_SCL_RX_PIN_INDEX] = EZI2C_1_PIN_DM_DIG_HIZ;
                pinsDm[EZI2C_1_MISO_SDA_TX_PIN_INDEX] = EZI2C_1_PIN_DM_STRONG;
                pinsDm[EZI2C_1_SCLK_PIN_INDEX]        = EZI2C_1_PIN_DM_DIG_HIZ;

            #if(EZI2C_1_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[EZI2C_1_SS0_PIN_INDEX] = EZI2C_1_HSIOM_SPI_SEL;
                pinsDm  [EZI2C_1_SS0_PIN_INDEX] = EZI2C_1_PIN_DM_DIG_HIZ;
            #endif /* (EZI2C_1_SS1_PIN) */

            #if(EZI2C_1_MISO_SDA_TX_PIN)
                /* Disable input buffer */
                 pinsInBuf |= EZI2C_1_MISO_SDA_TX_PIN_MASK;
            #endif /* (EZI2C_1_MISO_SDA_TX_PIN_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[EZI2C_1_MOSI_SCL_RX_PIN_INDEX] = EZI2C_1_PIN_DM_STRONG;
                pinsDm[EZI2C_1_MISO_SDA_TX_PIN_INDEX] = EZI2C_1_PIN_DM_DIG_HIZ;
                pinsDm[EZI2C_1_SCLK_PIN_INDEX]        = EZI2C_1_PIN_DM_STRONG;

            #if(EZI2C_1_SS0_PIN)
                hsiomSel [EZI2C_1_SS0_PIN_INDEX] = EZI2C_1_HSIOM_SPI_SEL;
                pinsDm   [EZI2C_1_SS0_PIN_INDEX] = EZI2C_1_PIN_DM_STRONG;
                pinsInBuf                                |= EZI2C_1_SS0_PIN_MASK;
            #endif /* (EZI2C_1_SS0_PIN) */

            #if(EZI2C_1_SS1_PIN)
                hsiomSel [EZI2C_1_SS1_PIN_INDEX] = EZI2C_1_HSIOM_SPI_SEL;
                pinsDm   [EZI2C_1_SS1_PIN_INDEX] = EZI2C_1_PIN_DM_STRONG;
                pinsInBuf                                |= EZI2C_1_SS1_PIN_MASK;
            #endif /* (EZI2C_1_SS1_PIN) */

            #if(EZI2C_1_SS2_PIN)
                hsiomSel [EZI2C_1_SS2_PIN_INDEX] = EZI2C_1_HSIOM_SPI_SEL;
                pinsDm   [EZI2C_1_SS2_PIN_INDEX] = EZI2C_1_PIN_DM_STRONG;
                pinsInBuf                                |= EZI2C_1_SS2_PIN_MASK;
            #endif /* (EZI2C_1_SS2_PIN) */

            #if(EZI2C_1_SS3_PIN)
                hsiomSel [EZI2C_1_SS3_PIN_INDEX] = EZI2C_1_HSIOM_SPI_SEL;
                pinsDm   [EZI2C_1_SS3_PIN_INDEX] = EZI2C_1_PIN_DM_STRONG;
                pinsInBuf                                |= EZI2C_1_SS3_PIN_MASK;
            #endif /* (EZI2C_1_SS2_PIN) */

                /* Disable input buffers */
            #if(EZI2C_1_MOSI_SCL_RX_PIN)
                pinsInBuf |= EZI2C_1_MOSI_SCL_RX_PIN_MASK;
            #endif /* (EZI2C_1_MOSI_SCL_RX_PIN) */

             #if(EZI2C_1_MOSI_SCL_RX_WAKE_PIN)
                pinsInBuf |= EZI2C_1_MOSI_SCL_RX_WAKE_PIN_MASK;
            #endif /* (EZI2C_1_MOSI_SCL_RX_WAKE_PIN) */

            #if(EZI2C_1_SCLK_PIN)
                pinsInBuf |= EZI2C_1_SCLK_PIN_MASK;
            #endif /* (EZI2C_1_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if(EZI2C_1_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[EZI2C_1_MISO_SDA_TX_PIN_INDEX] = EZI2C_1_HSIOM_UART_SEL;
                pinsDm  [EZI2C_1_MISO_SDA_TX_PIN_INDEX] = EZI2C_1_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if(0u != (EZI2C_1_UART_RX & uartTxRx))
                {
                    hsiomSel[EZI2C_1_MOSI_SCL_RX_PIN_INDEX] = EZI2C_1_HSIOM_UART_SEL;
                    pinsDm  [EZI2C_1_MOSI_SCL_RX_PIN_INDEX] = EZI2C_1_PIN_DM_DIG_HIZ;
                }

                if(0u != (EZI2C_1_UART_TX & uartTxRx))
                {
                    hsiomSel[EZI2C_1_MISO_SDA_TX_PIN_INDEX] = EZI2C_1_HSIOM_UART_SEL;
                    pinsDm  [EZI2C_1_MISO_SDA_TX_PIN_INDEX] = EZI2C_1_PIN_DM_STRONG;

                #if(EZI2C_1_MISO_SDA_TX_PIN)
                     pinsInBuf |= EZI2C_1_MISO_SDA_TX_PIN_MASK;
                #endif /* (EZI2C_1_MISO_SDA_TX_PIN_PIN) */
                }
            }
        }
    #endif /* (!EZI2C_1_CY_SCBIP_V1_I2C_ONLY) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settigns do not effect the pin output if HSIOM is other than GPIO */

    #if(EZI2C_1_MOSI_SCL_RX_PIN)
        EZI2C_1_SET_HSIOM_SEL(EZI2C_1_MOSI_SCL_RX_HSIOM_REG,
                                       EZI2C_1_MOSI_SCL_RX_HSIOM_MASK,
                                       EZI2C_1_MOSI_SCL_RX_HSIOM_POS,
                                       hsiomSel[EZI2C_1_MOSI_SCL_RX_PIN_INDEX]);

        EZI2C_1_spi_mosi_i2c_scl_uart_rx_SetDriveMode((uint8) pinsDm[EZI2C_1_MOSI_SCL_RX_PIN_INDEX]);

        EZI2C_1_SET_INP_DIS(EZI2C_1_spi_mosi_i2c_scl_uart_rx_INP_DIS,
                                     EZI2C_1_spi_mosi_i2c_scl_uart_rx_MASK,
                                     (0u != (pinsInBuf & EZI2C_1_MOSI_SCL_RX_PIN_MASK)));
    #endif /* (EZI2C_1_MOSI_SCL_RX_PIN) */

    #if(EZI2C_1_MOSI_SCL_RX_WAKE_PIN)
        EZI2C_1_SET_HSIOM_SEL(EZI2C_1_MOSI_SCL_RX_WAKE_HSIOM_REG,
                                       EZI2C_1_MOSI_SCL_RX_WAKE_HSIOM_MASK,
                                       EZI2C_1_MOSI_SCL_RX_WAKE_HSIOM_POS,
                                       hsiomSel[EZI2C_1_MOSI_SCL_RX_WAKE_PIN_INDEX]);

        EZI2C_1_spi_mosi_i2c_scl_uart_rx_wake_SetDriveMode((uint8)
                                                               pinsDm[EZI2C_1_MOSI_SCL_RX_WAKE_PIN_INDEX]);

        EZI2C_1_SET_INP_DIS(EZI2C_1_spi_mosi_i2c_scl_uart_rx_wake_INP_DIS,
                                     EZI2C_1_spi_mosi_i2c_scl_uart_rx_wake_MASK,
                                     (0u != (pinsInBuf & EZI2C_1_MOSI_SCL_RX_WAKE_PIN_MASK)));

         /* Set interrupt on falling edge */
        EZI2C_1_SET_INCFG_TYPE(EZI2C_1_MOSI_SCL_RX_WAKE_INTCFG_REG,
                                        EZI2C_1_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK,
                                        EZI2C_1_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS,
                                        EZI2C_1_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (EZI2C_1_MOSI_SCL_RX_WAKE_PIN) */

    #if(EZI2C_1_MISO_SDA_TX_PIN)
        EZI2C_1_SET_HSIOM_SEL(EZI2C_1_MISO_SDA_TX_HSIOM_REG,
                                       EZI2C_1_MISO_SDA_TX_HSIOM_MASK,
                                       EZI2C_1_MISO_SDA_TX_HSIOM_POS,
                                       hsiomSel[EZI2C_1_MISO_SDA_TX_PIN_INDEX]);

        EZI2C_1_spi_miso_i2c_sda_uart_tx_SetDriveMode((uint8) pinsDm[EZI2C_1_MISO_SDA_TX_PIN_INDEX]);

        EZI2C_1_SET_INP_DIS(EZI2C_1_spi_miso_i2c_sda_uart_tx_INP_DIS,
                                     EZI2C_1_spi_miso_i2c_sda_uart_tx_MASK,
                                    (0u != (pinsInBuf & EZI2C_1_MISO_SDA_TX_PIN_MASK)));
    #endif /* (EZI2C_1_MOSI_SCL_RX_PIN) */

    #if(EZI2C_1_SCLK_PIN)
        EZI2C_1_SET_HSIOM_SEL(EZI2C_1_SCLK_HSIOM_REG, EZI2C_1_SCLK_HSIOM_MASK,
                                       EZI2C_1_SCLK_HSIOM_POS, hsiomSel[EZI2C_1_SCLK_PIN_INDEX]);

        EZI2C_1_spi_sclk_SetDriveMode((uint8) pinsDm[EZI2C_1_SCLK_PIN_INDEX]);

        EZI2C_1_SET_INP_DIS(EZI2C_1_spi_sclk_INP_DIS,
                             EZI2C_1_spi_sclk_MASK,
                            (0u != (pinsInBuf & EZI2C_1_SCLK_PIN_MASK)));
    #endif /* (EZI2C_1_SCLK_PIN) */

    #if(EZI2C_1_SS0_PIN)
        EZI2C_1_SET_HSIOM_SEL(EZI2C_1_SS0_HSIOM_REG, EZI2C_1_SS0_HSIOM_MASK,
                                       EZI2C_1_SS0_HSIOM_POS, hsiomSel[EZI2C_1_SS0_PIN_INDEX]);

        EZI2C_1_spi_ss0_SetDriveMode((uint8) pinsDm[EZI2C_1_SS0_PIN_INDEX]);

        EZI2C_1_SET_INP_DIS(EZI2C_1_spi_ss0_INP_DIS,
                                     EZI2C_1_spi_ss0_MASK,
                                     (0u != (pinsInBuf & EZI2C_1_SS0_PIN_MASK)));
    #endif /* (EZI2C_1_SS1_PIN) */

    #if(EZI2C_1_SS1_PIN)
        EZI2C_1_SET_HSIOM_SEL(EZI2C_1_SS1_HSIOM_REG, EZI2C_1_SS1_HSIOM_MASK,
                                       EZI2C_1_SS1_HSIOM_POS, hsiomSel[EZI2C_1_SS1_PIN_INDEX]);

        EZI2C_1_spi_ss1_SetDriveMode((uint8) pinsDm[EZI2C_1_SS1_PIN_INDEX]);

        EZI2C_1_SET_INP_DIS(EZI2C_1_spi_ss1_INP_DIS,
                                     EZI2C_1_spi_ss1_MASK,
                                     (0u != (pinsInBuf & EZI2C_1_SS1_PIN_MASK)));
    #endif /* (EZI2C_1_SS1_PIN) */

    #if(EZI2C_1_SS2_PIN)
        EZI2C_1_SET_HSIOM_SEL(EZI2C_1_SS2_HSIOM_REG, EZI2C_1_SS2_HSIOM_MASK,
                                       EZI2C_1_SS2_HSIOM_POS, hsiomSel[EZI2C_1_SS2_PIN_INDEX]);

        EZI2C_1_spi_ss2_SetDriveMode((uint8) pinsDm[EZI2C_1_SS2_PIN_INDEX]);

        EZI2C_1_SET_INP_DIS(EZI2C_1_spi_ss2_INP_DIS,
                                     EZI2C_1_spi_ss2_MASK,
                                     (0u != (pinsInBuf & EZI2C_1_SS2_PIN_MASK)));
    #endif /* (EZI2C_1_SS2_PIN) */

    #if(EZI2C_1_SS3_PIN)
        EZI2C_1_SET_HSIOM_SEL(EZI2C_1_SS3_HSIOM_REG,  EZI2C_1_SS3_HSIOM_MASK,
                                       EZI2C_1_SS3_HSIOM_POS, hsiomSel[EZI2C_1_SS3_PIN_INDEX]);

        EZI2C_1_spi_ss3_SetDriveMode((uint8) pinsDm[EZI2C_1_SS3_PIN_INDEX]);

        EZI2C_1_SET_INP_DIS(EZI2C_1_spi_ss3_INP_DIS,
                                     EZI2C_1_spi_ss3_MASK,
                                     (0u != (pinsInBuf & EZI2C_1_SS3_PIN_MASK)));
    #endif /* (EZI2C_1_SS3_PIN) */
    }

#endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
