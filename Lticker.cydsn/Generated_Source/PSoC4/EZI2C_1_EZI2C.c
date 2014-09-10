/*******************************************************************************
* File Name: EZI2C_1_EZI2C.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  EZI2C mode.
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
#include "EZI2C_1_EZI2C_PVT.h"


/***************************************
*      EZI2C Private Vars
***************************************/

volatile uint8 EZI2C_1_curStatus; /* Status byte */
uint8 EZI2C_1_fsmState;           /* FSM state   */

/* Variables intended to be used with Buffer1: Primary slave address */
volatile uint8 * EZI2C_1_dataBuffer1; /* Pointer to data buffer1 */
uint16 EZI2C_1_bufSizeBuf1; /* Size of buffer1 in bytes      */
uint16 EZI2C_1_protectBuf1; /* Start index of write protected area buffer1 */
uint8 EZI2C_1_offsetBuf1; /* Current offset within buffer1 */
uint16 EZI2C_1_indexBuf1;  /* Current index within buffer1  */

#if(EZI2C_1_SECONDARY_ADDRESS_ENABLE_CONST)
    uint8 EZI2C_1_addrBuf1; /* Primary slave address. Used for software comparison   */
    uint8 EZI2C_1_addrBuf2; /* Secondary slave address. Used for software comparison */

    /* Variables intended to be used with Buffer1: Primary slave address */
    volatile uint8 * EZI2C_1_dataBuffer2; /* Pointer to data buffer2 */
    uint16 EZI2C_1_bufSizeBuf2; /* Size of buffer2 in bytes      */
    uint16 EZI2C_1_protectBuf2; /* Start index of write protected area buffer 2 */
    uint8 EZI2C_1_offsetBuf2; /* Current offset within buffer2 */
    uint16 EZI2C_1_indexBuf2;  /* Current index within buffer2  */
#endif /* (EZI2C_1_SECONDARY_ADDRESS_ENABLE_CONST) */


/***************************************
*      EZI2C Private Functions
***************************************/

#if(EZI2C_1_SECONDARY_ADDRESS_ENABLE_CONST)
    static uint32 EZI2C_1_EzI2CUpdateRxMatchReg(uint32 addr1, uint32 addr2);
#endif /* (EZI2C_1_SECONDARY_ADDRESS_ENABLE_CONST) */

#if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Config Structure Initialization
    ***************************************/

    /* Constant configuration of EZI2C */
    const EZI2C_1_EZI2C_INIT_STRUCT EZI2C_1_configEzI2C =
    {
        EZI2C_1_EZI2C_CLOCK_STRETCHING,
        EZI2C_1_EZI2C_MEDIAN_FILTER_ENABLE,
        EZI2C_1_EZI2C_NUMBER_OF_ADDRESSES,
        EZI2C_1_EZI2C_PRIMARY_SLAVE_ADDRESS,
        EZI2C_1_EZI2C_SECONDARY_SLAVE_ADDRESS,
        EZI2C_1_EZI2C_SUB_ADDRESS_SIZE,
        EZI2C_1_EZI2C_WAKE_ENABLE
    };

    /*******************************************************************************
    * Function Name: EZI2C_1_EzI2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the EZI2C operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EZI2C_1_EzI2CInit(const EZI2C_1_EZI2C_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to invalid function parameter */
        }
        else
        {
            /* Configure pins */
            EZI2C_1_SetPins(EZI2C_1_SCB_MODE_EZI2C, EZI2C_1_DUMMY_PARAM,
                                                                      EZI2C_1_DUMMY_PARAM);

            /* Store internal configuration */
            EZI2C_1_scbMode       = (uint8) EZI2C_1_SCB_MODE_EZI2C;
            EZI2C_1_scbEnableWake = (uint8) config->enableWake;
            EZI2C_1_scbEnableIntr = (uint8) EZI2C_1_SCB_IRQ_INTERNAL;

            EZI2C_1_numberOfAddr  = (uint8) config->numberOfAddresses;
            EZI2C_1_subAddrSize   = (uint8) config->subAddrSize;

            /* Configure I2C interface */
            EZI2C_1_CTRL_REG     = EZI2C_1_GET_CTRL_ADDR_ACCEPT(config->numberOfAddresses) |
                                            EZI2C_1_GET_CTRL_EC_AM_MODE (config->enableWake);

            EZI2C_1_I2C_CTRL_REG = EZI2C_1_EZI2C_CTRL;

        #if(EZI2C_1_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            EZI2C_1_SET_I2C_CFG_SDA_FILT_TRIM(EZI2C_1_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (EZI2C_1_CY_SCBIP_V0) */

            /* Configure RX direction */
            EZI2C_1_RX_CTRL_REG      = EZI2C_1_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                EZI2C_1_EZI2C_RX_CTRL;
            EZI2C_1_RX_FIFO_CTRL_REG = EZI2C_1_CLEAR_REG;

            /* Set default address and mask */
            if(EZI2C_1_EZI2C_PRIMARY_ADDRESS == config->numberOfAddresses)
            {
                EZI2C_1_RX_MATCH_REG = EZI2C_1_EzI2CUpdateRxMatchReg(config->primarySlaveAddr,
                                                                                       config->primarySlaveAddr);
            }
            else
            {
                EZI2C_1_RX_MATCH_REG = EZI2C_1_EzI2CUpdateRxMatchReg(config->primarySlaveAddr,
                                                                                       config->secondarySlaveAddr);
            }

            /* Configure TX direction */
            EZI2C_1_TX_CTRL_REG      = EZI2C_1_EZI2C_TX_CTRL;
            EZI2C_1_TX_FIFO_CTRL_REG = ((0u != (config->enableClockStretch)) ?
                                                 EZI2C_1_CLEAR_REG : EZI2C_1_EZI2C_TX_FIFO_CTRL);

            /* Configure interrupt sources */
        #if(EZI2C_1_CY_SCBIP_V0)
           EZI2C_1_INTR_SPI_EC_MASK_REG = EZI2C_1_NO_INTR_SOURCES;
        #endif /* (EZI2C_1_CY_SCBIP_V0) */

            EZI2C_1_INTR_I2C_EC_MASK_REG = EZI2C_1_NO_INTR_SOURCES;
            EZI2C_1_INTR_MASTER_MASK_REG = EZI2C_1_NO_INTR_SOURCES;
            EZI2C_1_INTR_SLAVE_MASK_REG  = EZI2C_1_EZI2C_INTR_SLAVE_MASK;
            EZI2C_1_INTR_TX_MASK_REG     = EZI2C_1_NO_INTR_SOURCES;

            /* Configure interrupt with EZI2C handler but do not enable it */
            CyIntDisable    (EZI2C_1_ISR_NUMBER);
            CyIntSetPriority(EZI2C_1_ISR_NUMBER, EZI2C_1_ISR_PRIORITY);
            (void) CyIntSetVector(EZI2C_1_ISR_NUMBER, (0u != (config->enableClockStretch)) ?
                                                                      (&EZI2C_1_EZI2C_STRETCH_ISR) :
                                                                      (&EZI2C_1_EZI2C_NO_STRETCH_ISR));

            if(0u != (config->enableClockStretch))
            {
                /* Configure interrupt sources */
                EZI2C_1_INTR_SLAVE_MASK_REG |= EZI2C_1_INTR_SLAVE_I2C_ADDR_MATCH;
                EZI2C_1_INTR_RX_MASK_REG     = EZI2C_1_NO_INTR_SOURCES;
            }
            else
            {
                /* Enable Auto ACK/NACK features */
                EZI2C_1_I2C_CTRL_REG |= EZI2C_1_EZI2C_CTRL_AUTO;

                /* Configure RX interrupt source */
                EZI2C_1_INTR_SLAVE_MASK_REG |= EZI2C_1_INTR_SLAVE_I2C_START;
                EZI2C_1_INTR_RX_MASK_REG     = EZI2C_1_INTR_RX_NOT_EMPTY;
            }

            /* Configure global variables */
            EZI2C_1_fsmState = EZI2C_1_EZI2C_FSM_IDLE;

            EZI2C_1_curStatus  = 0u;
            EZI2C_1_indexBuf1  = 0u;
            EZI2C_1_offsetBuf1 = 0u;
            EZI2C_1_indexBuf2  = 0u;
            EZI2C_1_offsetBuf2 = 0u;

            EZI2C_1_addrBuf1 = (uint8) config->primarySlaveAddr;
            EZI2C_1_addrBuf2 = (uint8) config->secondarySlaveAddr;
        }
    }

#else

    /*******************************************************************************
    * Function Name: EZI2C_1_EzI2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the EZI2C operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EZI2C_1_EzI2CInit(void)
    {
        /* Configure I2C interface */
        EZI2C_1_CTRL_REG     = EZI2C_1_EZI2C_DEFAULT_CTRL;
        EZI2C_1_I2C_CTRL_REG = EZI2C_1_EZI2C_DEFAULT_I2C_CTRL;

    #if(EZI2C_1_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        EZI2C_1_SET_I2C_CFG_SDA_FILT_TRIM(EZI2C_1_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (EZI2C_1_CY_SCBIP_V0) */

        /* Configure RX direction */
        EZI2C_1_RX_CTRL_REG      = EZI2C_1_EZI2C_DEFAULT_RX_CTRL;
        EZI2C_1_RX_FIFO_CTRL_REG = EZI2C_1_EZI2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        EZI2C_1_RX_MATCH_REG     = EZI2C_1_EZI2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        EZI2C_1_TX_CTRL_REG      = EZI2C_1_EZI2C_DEFAULT_TX_CTRL;
        EZI2C_1_TX_FIFO_CTRL_REG = EZI2C_1_EZI2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with EZI2C handler but do not enable it */
    #if !defined (CY_EXTERNAL_INTERRUPT_CONFIG)
        CyIntDisable    (EZI2C_1_ISR_NUMBER);
        CyIntSetPriority(EZI2C_1_ISR_NUMBER, EZI2C_1_ISR_PRIORITY);

    #if(EZI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST)
        (void) CyIntSetVector(EZI2C_1_ISR_NUMBER, &EZI2C_1_EZI2C_STRETCH_ISR);
    #else
        (void) CyIntSetVector(EZI2C_1_ISR_NUMBER, &EZI2C_1_EZI2C_NO_STRETCH_ISR);
    #endif /* (EZI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST) */

    #endif /* !defined (CY_EXTERNAL_INTERRUPT_CONFIG) */

        /* Configure interrupt sources */
    #if(EZI2C_1_CY_SCBIP_V0)
        EZI2C_1_INTR_SPI_EC_MASK_REG = EZI2C_1_EZI2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (EZI2C_1_CY_SCBIP_V0) */

        EZI2C_1_INTR_I2C_EC_MASK_REG = EZI2C_1_EZI2C_DEFAULT_INTR_I2C_EC_MASK;
        EZI2C_1_INTR_SLAVE_MASK_REG  = EZI2C_1_EZI2C_DEFAULT_INTR_SLAVE_MASK;
        EZI2C_1_INTR_MASTER_MASK_REG = EZI2C_1_EZI2C_DEFAULT_INTR_MASTER_MASK;
        EZI2C_1_INTR_RX_MASK_REG     = EZI2C_1_EZI2C_DEFAULT_INTR_RX_MASK;
        EZI2C_1_INTR_TX_MASK_REG     = EZI2C_1_EZI2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        EZI2C_1_fsmState = EZI2C_1_EZI2C_FSM_IDLE;

        EZI2C_1_curStatus  = 0u;
        EZI2C_1_indexBuf1  = 0u;
        EZI2C_1_offsetBuf1 = 0u;

    #if(EZI2C_1_SECONDARY_ADDRESS_ENABLE_CONST)
        EZI2C_1_indexBuf2  = 0u;
        EZI2C_1_offsetBuf2 = 0u;

        EZI2C_1_addrBuf1 = EZI2C_1_EZI2C_PRIMARY_SLAVE_ADDRESS;
        EZI2C_1_addrBuf2 = EZI2C_1_EZI2C_SECONDARY_SLAVE_ADDRESS;
    #endif /* (EZI2C_1_SECONDARY_ADDRESS_ENABLE_CONST) */
    }
#endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: EZI2C_1_EzI2CStop
********************************************************************************
*
* Summary:
*  Resets the EZI2C FSM into a default state and disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void EZI2C_1_EzI2CStop(void)
{
    /* Disable TX interrupt sources in order not to  cause the false interrupts trigger.
    * The incoming transaction will enable an appropriate TX interrupt.
    */
    EZI2C_1_SetTxInterruptMode(EZI2C_1_NO_INTR_SOURCES);

#if(EZI2C_1_CY_SCBIP_V0)
    /* Clear pending interrupt as after the block is disabled, the TX FIFO becomes empty and
    * the block does not gate the interrupt sources when disabled.
    */
    EZI2C_1_ClearPendingInt();
#endif /* (EZI2C_1_CY_SCBIP_V0) */

    EZI2C_1_fsmState = EZI2C_1_EZI2C_FSM_IDLE;
}


/*******************************************************************************
* Function Name: EZI2C_1_EzI2CGetActivity
********************************************************************************
*
* Summary:
*  Returns the EZI2C slave status.
*  The read, write and error status flags reset to zero after this function call.
*  The busy status flag is cleared when the transaction intended for the EZ
*  I2C slave completes.
*
* Parameters:
*  None
*
* Return:
*  Returns the status of the EZI2C Slave activity.
*
*******************************************************************************/
uint32 EZI2C_1_EzI2CGetActivity(void)
{
    uint32 status;
    uint32 slaveBusy;

    slaveBusy = 0u;

    EZI2C_1_DisableInt();  /* Lock from interruption */

    status = EZI2C_1_curStatus;

    /* Relay on address match event from HW as bus busy status */
#if(EZI2C_1_CY_SCBIP_V0)

    #if(EZI2C_1_EZI2C_SCL_STRETCH_DISABLE)
    {
        slaveBusy = (uint32) EZI2C_1_CHECK_INTR_SLAVE(EZI2C_1_INTR_SLAVE_I2C_ADDR_MATCH);
    }
    #endif
#else
    #if(EZI2C_1_EZI2C_SCL_STRETCH_DISABLE)
    {
        #if(EZI2C_1_EZI2C_EC_AM_ENABLE)
        {
            slaveBusy = (uint32) EZI2C_1_CHECK_INTR_I2C_EC(EZI2C_1_INTR_I2C_EC_WAKE_UP);
        }
        #else
        {
            slaveBusy = (uint32) EZI2C_1_CHECK_INTR_SLAVE(EZI2C_1_INTR_SLAVE_I2C_ADDR_MATCH);
        }
        #endif
    }
    #endif
#endif /* (EZI2C_1_CY_SCBIP_V0) */

    if(0u != slaveBusy)
    {
        status |= EZI2C_1_EZI2C_STATUS_BUSY;
    }

    EZI2C_1_curStatus &= ((uint8) ~EZI2C_1_EZI2C_CLEAR_STATUS);

    EZI2C_1_EnableInt();   /* Release lock */

    return(status);
}


/*******************************************************************************
* Function Name: EZI2C_1_EzI2CSetAddress1
********************************************************************************
*
* Summary:
*  Sets the primary I2C slave address.
*
* Parameters:
*  address: I2C slave address for the secondary device.
*           This address is the 7-bit right-justified slave address and does
*           not include the R/W bit.
*           This value may be any address between 0 and 127 (0x00 to 0x7F).
*
* Return:
*  None
*
*******************************************************************************/
void EZI2C_1_EzI2CSetAddress1(uint32 address)
{
    #if(EZI2C_1_SECONDARY_ADDRESS_ENABLE)
    {
        EZI2C_1_addrBuf1 = (uint8) address;

        EZI2C_1_RX_MATCH_REG = EZI2C_1_EzI2CUpdateRxMatchReg(address,
                                                                               (uint32) EZI2C_1_addrBuf2);
    }
    #else
    {
        uint32 matchReg;

        matchReg = EZI2C_1_RX_MATCH_REG;

        matchReg &= ((uint32) ~EZI2C_1_RX_MATCH_ADDR_MASK);            /* Clear address bits */
        matchReg |= ((uint32)  EZI2C_1_GET_I2C_8BIT_ADDRESS(address)); /* Set mask */

        EZI2C_1_RX_MATCH_REG = matchReg;
    }
    #endif
}


/*******************************************************************************
* Function Name: EZI2C_1_EzI2CGetAddress1
********************************************************************************
*
* Summary:
*  Gets the primary I2C slave 7-bit address.
*
* Parameters:
*  None
*
* Return:
*  Returns I2C slave address for the primary device.
*  This address is the 7-bit right-justified slave address and does not
*  include the R/W bit.
*  This value may be any address between 0 and 127 (0x00 to 0x7F).
*
*******************************************************************************/
uint32 EZI2C_1_EzI2CGetAddress1(void)
{
    uint32 address;

    #if(EZI2C_1_SECONDARY_ADDRESS_ENABLE)
    {
        address = (uint32) EZI2C_1_addrBuf1;
    }
    #else
    {
        address = (EZI2C_1_GET_RX_MATCH_ADDR(EZI2C_1_RX_MATCH_REG) >>
                   EZI2C_1_I2C_SLAVE_ADDR_POS);
    }
    #endif

    return(address);
}


/*******************************************************************************
* Function Name: EZI2C_1_EzI2CSetBuffer1
********************************************************************************
*
* Summary:
*  Sets up the data buffer to be exposed to the I2C master on a primary slave
*  address request.
*
* Parameters:
*  bufSize: Size of the buffer in bytes.
*  rwBoundary: Sets how many bytes are writeable in the beginning of the buffer.
*              This value must be less than or equal to the buffer size.
*              Data located at offset rwBoundry and greater are read only.
*  buffer: Pointer to the data buffer.
*
* Return:
*  None
*
*******************************************************************************/
void EZI2C_1_EzI2CSetBuffer1(uint32 bufSize, uint32 rwBoundary, volatile uint8 * buffer)
{
    if(NULL != buffer)
    {
        EZI2C_1_dataBuffer1 =  buffer;
        EZI2C_1_bufSizeBuf1 = (uint16) bufSize;
        EZI2C_1_protectBuf1 = (uint16) rwBoundary;
    }
}


/*******************************************************************************
* Function Name: EZI2C_1_EzI2CSetReadBoundaryBuffer1
********************************************************************************
*
* Summary:
*  Sets the read only boundary in the data buffer to be exposed to the I2C
*  master on a primary slave address request.
*
* Parameters:
*  rwBoundry: Sets how many bytes are writeable in the beginning of the buffer.
*             This value must be less than or equal to the buffer size.
*             Data located at offset rwBoundry and greater are read only.
*
* Return:
*  None
*
*******************************************************************************/
void EZI2C_1_EzI2CSetReadBoundaryBuffer1(uint32 rwBoundary)
{
    EZI2C_1_protectBuf1 = (uint16) rwBoundary;
}


#if(EZI2C_1_SECONDARY_ADDRESS_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: EZI2C_1_EzI2CUpdateRxMatchReg
    ********************************************************************************
    *
    * Summary:
    *  Returns the value of the RX MATCH register for addr1 and addr2. The addr1 is
    *  accepted as the primary address and it is written to RX_MATCH.ADDRESS
    *  (addr1 << 0x01).
    *  The RX_MATCH.MASK is set as follow: addr1 and addr2 equal bits set to 1
    *  otherwise 0.
    *
    * Parameters:
    *  addr1: I2C slave address for the primary device.
    *  addr2: I2C slave address for the secondary device.
    *         This address is the 7-bit right-justified slave address and does
    *         not include the R/W bit.
    *         This value may be any address between 0 and 127 (0x00 to 0x7F).
    *
    * Return:
    *  Value of RX MATCH register.
    *
    *******************************************************************************/
    static uint32 EZI2C_1_EzI2CUpdateRxMatchReg(uint32 addr1, uint32 addr2)
    {
        uint32 matchReg;

        matchReg  = ~(addr1 ^ addr2); /* If (addr1 and addr2) bit matches - mask bit equal 1, in other case 0 */

        matchReg  = (uint32) (EZI2C_1_GET_I2C_8BIT_ADDRESS(matchReg) << EZI2C_1_RX_MATCH_MASK_POS);
        matchReg |= EZI2C_1_GET_I2C_8BIT_ADDRESS(addr1);

        return(matchReg);
    }

    /*******************************************************************************
    * Function Name: EZI2C_1_EzI2CSetAddress2
    ********************************************************************************
    *
    * Summary:
    *  Sets the secondary I2C slave address.
    *
    * Parameters:
    *  address: I2C slave address for the secondary device.
    *           This address is the 7-bit right-justified slave address and does
    *           not include the R/W bit.
    *           This value may be any address between 0 and 127 (0x00 to 0x7F).
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EZI2C_1_EzI2CSetAddress2(uint32 address)
    {
        EZI2C_1_addrBuf2 = (uint8) address;

        EZI2C_1_RX_MATCH_REG = EZI2C_1_EzI2CUpdateRxMatchReg((uint32) EZI2C_1_addrBuf1,
                                                                               address);
    }


    /*******************************************************************************
    * Function Name: EZI2C_1_EzI2CGetAddress2
    ********************************************************************************
    *
    * Summary:
    *  Gets secondary the I2C slave 7-bit address.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Returns the I2C slave address for the secondary device.
    *  This address is a 7-bit right-justified slave address and does not
    *  include the R/W bit.
    *  This value may be any address between 0 and 127 (0x00 to 0x7F).
    *
    *******************************************************************************/
    uint32 EZI2C_1_EzI2CGetAddress2(void)
    {
        return((uint32) EZI2C_1_addrBuf2);
    }


    /*******************************************************************************
    * Function Name: EZI2C_1_EzI2CSetBuffer2
    ********************************************************************************
    *
    * Summary:
    *  Sets up the data buffer to be exposed to the I2C master on a secondary slave
    *  address request.
    *
    * Parameters:
    *  bufSize: Size of the buffer in bytes.
    *  rwBoundary: Sets how many bytes are writeable in the beginning of the buffer.
    *              This value must be less than or equal to the buffer size.
    *              Data located at offset rwBoundry and greater are read only.
    *  buffer: Pointer to the data buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EZI2C_1_EzI2CSetBuffer2(uint32 bufSize, uint32 rwBoundary, volatile uint8 * buffer)
    {
        if(NULL != buffer)
        {
            EZI2C_1_dataBuffer2 =  buffer;
            EZI2C_1_bufSizeBuf2 = (uint16) bufSize;
            EZI2C_1_protectBuf2 = (uint16) rwBoundary;
        }
    }


    /*******************************************************************************
    * Function Name: EZI2C_1_EzI2CSetReadBoundaryBuffer2
    ********************************************************************************
    *
    * Summary:
    *  Sets the read only boundary in the data buffer to be exposed to the I2C
    *  master on a secondary address request.
    *
    * Parameters:
    *  rwBoundary: Sets how many bytes are writeable at the beginning of the buffer.
    *              This value must be less than or equal to the buffer size.
    *              Data located at offset rwBoundry and greater are read only.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EZI2C_1_EzI2CSetReadBoundaryBuffer2(uint32 rwBoundary)
    {
        EZI2C_1_protectBuf2 = (uint16) rwBoundary;
    }

#endif /* (EZI2C_1_SECONDARY_ADDRESS_ENABLE_CONST) */


#if(EZI2C_1_EZI2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: EZI2C_1_EzI2CSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clock stretching is  enabled: Disables INTR_I2C_EC.WAKE_UP interrupt source.
    *  It triggers on the slave address match.
    *  Clock stretching is disabled: waits until the I2C slave becomes free and
    *  disables the block to perform reconfiguration from the active mode operation
    *  to deep sleep with wake up on the address match: enables the INTR_I2C_EC.WAKE_UP
    *  interrupt source and disables the INTR_S and INTR_TX interrupt sources.
    *  The block is disabled before reconfiguration and enabled when
    *  it is completed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EZI2C_1_EzI2CSaveConfig(void)
    {
    #if(EZI2C_1_CY_SCBIP_V0)

        #if(EZI2C_1_EZI2C_SCL_STRETCH_ENABLE)
        {
            /* Enable wakeup interrupt source on address match */
            EZI2C_1_SetI2CExtClkInterruptMode(EZI2C_1_INTR_I2C_EC_WAKE_UP);
        }
        #endif

    #else
        uint8 enableInt;

        enableInt = (uint8) EZI2C_1_INTR_I2C_EC_WAKE_UP;

        #if(EZI2C_1_EZI2C_SCL_STRETCH_ENABLE)
        {
            /* Enable interrupt source to wakeup the device */
            EZI2C_1_SetI2CExtClkInterruptMode(enableInt);
        }
        #else
        {
            for(;;) /* Wait for end of transaction intended to slave */
            {
                if(0u == (EZI2C_1_GetI2CExtClkInterruptSource() & EZI2C_1_INTR_I2C_EC_WAKE_UP))
                {
                    enableInt = CyEnterCriticalSection();

                    if(0u == (EZI2C_1_GetI2CExtClkInterruptSource() & EZI2C_1_INTR_I2C_EC_WAKE_UP))
                    {
                        /* Attempts to set NACK command before disable block */
                        EZI2C_1_I2C_SLAVE_GENERATE_NACK;

                        if(0u == (EZI2C_1_GetI2CExtClkInterruptSource() & EZI2C_1_INTR_I2C_EC_WAKE_UP))
                        {
                            /* NACK command was set before. It is safe to disable block */
                            EZI2C_1_CTRL_REG &= (uint32) ~EZI2C_1_CTRL_ENABLED;
                            EZI2C_1_DisableInt();

                            CyExitCriticalSection(enableInt);
                            break;
                        }
                        else
                        {
                            /* Clear NACK command to prevent data NACK */
                            EZI2C_1_I2C_SLAVE_CLEAR_NACK;
                        }
                    }

                    CyExitCriticalSection(enableInt);
                }
            }

            /* Disable all active mode interrupt sources */
            EZI2C_1_SetTxInterruptMode(EZI2C_1_NO_INTR_SOURCES);
            EZI2C_1_SetSlaveInterruptMode(EZI2C_1_NO_INTR_SOURCES);
            EZI2C_1_ClearPendingInt();
            EZI2C_1_EnableInt();

            /* Enable wakeup interrupt on address match */
            EZI2C_1_SetI2CExtClkInterruptMode(EZI2C_1_INTR_I2C_EC_WAKE_UP);

            enableInt = CyEnterCriticalSection();

            EZI2C_1_CTRL_REG |= (uint32) EZI2C_1_CTRL_ENABLED;
            EZI2C_1_I2C_SLAVE_GENERATE_NACK;

            CyExitCriticalSection(enableInt);
        }
        #endif
    #endif /* (EZI2C_1_CY_SCBIP_V0) */
    }


    /*******************************************************************************
    * Function Name: EZI2C_1_EzI2CRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Clock stretching is  enabled: Disables the INTR_I2C_EC.WAKE_UP interrupt source.
    *  Clock stretching is disabled: Reconfigures the EZI2C component from deep sleep
    *  (wake up on the address match) to active operation: disables the INTR_I2C_EC.WAKE_UP
    *  interrupt source and restores the INTR_S. interrupt sources to operate in
    *  the active mode. The block is disabled before reconfiguration and enabled when
    *  it is completed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EZI2C_1_EzI2CRestoreConfig(void)
    {
    #if(EZI2C_1_CY_SCBIP_V0)

        #if(EZI2C_1_EZI2C_SCL_STRETCH_ENABLE)
        {
            /* Disable wakeup interrupt on address match */
            EZI2C_1_SetI2CExtClkInterruptMode(EZI2C_1_NO_INTR_SOURCES);
        }
        #endif

    #else

        #if(EZI2C_1_EZI2C_SCL_STRETCH_ENABLE)
        {
            /* Disables wakeup interrupt source on address match */
            EZI2C_1_SetI2CExtClkInterruptMode(EZI2C_1_NO_INTR_SOURCES);
        }
        #else
        {
            /* NACK will be driven on the bus by wakeup or NACK command.
            * It is safe to disable block to restore active mode configuration.
            */
            EZI2C_1_CTRL_REG &= (uint32) ~EZI2C_1_CTRL_ENABLED;

            /* Restore active mode interrupt sources */
            EZI2C_1_SetI2CExtClkInterruptMode(EZI2C_1_NO_INTR_SOURCES);
            EZI2C_1_SetSlaveInterruptMode(EZI2C_1_EZI2C_INTR_SLAVE_MASK |
                                                   EZI2C_1_INTR_SLAVE_I2C_START);
            EZI2C_1_ClearPendingInt();

            EZI2C_1_CTRL_REG |= (uint32) EZI2C_1_CTRL_ENABLED;
        }
        #endif

    #endif /* (EZI2C_1_CY_SCBIP_V0) */
    }
#endif /* (EZI2C_1_EZI2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
