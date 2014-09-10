/*******************************************************************************
* File Name: EZI2C_1_EZI2C.h
* Version 1.20
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  EZI2C mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_EZI2C_EZI2C_1_H)
#define CY_SCB_EZI2C_EZI2C_1_H

#include "EZI2C_1.h"


/***************************************
*   Initial Parameter Constants
****************************************/

#define EZI2C_1_EZI2C_CLOCK_STRETCHING         (1u)
#define EZI2C_1_EZI2C_MEDIAN_FILTER_ENABLE     (1u)
#define EZI2C_1_EZI2C_NUMBER_OF_ADDRESSES      (0u)
#define EZI2C_1_EZI2C_PRIMARY_SLAVE_ADDRESS    (8u)
#define EZI2C_1_EZI2C_SECONDARY_SLAVE_ADDRESS  (9u)
#define EZI2C_1_EZI2C_SUB_ADDRESS_SIZE         (0u)
#define EZI2C_1_EZI2C_WAKE_ENABLE              (0u)
#define EZI2C_1_EZI2C_DATA_RATE                (100u)
#define EZI2C_1_EZI2C_SLAVE_ADDRESS_MASK       (254u)


/***************************************
*  Conditional Compilation Parameters
****************************************/

#if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)

    #define EZI2C_1_SUB_ADDRESS_SIZE16             (0u != EZI2C_1_subAddrSize)
    #define EZI2C_1_SECONDARY_ADDRESS_ENABLE       (0u != EZI2C_1_numberOfAddr)

    #define EZI2C_1_EZI2C_EC_AM_ENABLE         (0u != (EZI2C_1_CTRL_REG & \
                                                                EZI2C_1_CTRL_EC_AM_MODE))
    #define EZI2C_1_EZI2C_SCL_STRETCH_ENABLE   (0u != (EZI2C_1_GetI2CExtClkInterruptSourceMasked() & \
                                                                EZI2C_1_INTR_SLAVE_I2C_ADDR_MATCH))
    #define EZI2C_1_EZI2C_SCL_STRETCH_DISABLE       (!EZI2C_1_EZI2C_SCL_STRETCH_ENABLE)

    #define EZI2C_1_SECONDARY_ADDRESS_ENABLE_CONST  (1u)
    #define EZI2C_1_SUB_ADDRESS_SIZE16_CONST        (1u)
    #define EZI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST  (1u)
    #define EZI2C_1_EZI2C_SCL_STRETCH_DISABLE_CONST (1u)
    #define EZI2C_1_EZI2C_WAKE_ENABLE_CONST         (1u)

#else

    #define EZI2C_1_SUB_ADDRESS_SIZE16         (0u != EZI2C_1_EZI2C_SUB_ADDRESS_SIZE)
    #define EZI2C_1_SUB_ADDRESS_SIZE16_CONST   (EZI2C_1_SUB_ADDRESS_SIZE16)

    #define EZI2C_1_SECONDARY_ADDRESS_ENABLE        (0u != EZI2C_1_EZI2C_NUMBER_OF_ADDRESSES)
    #define EZI2C_1_SECONDARY_ADDRESS_ENABLE_CONST  (EZI2C_1_SECONDARY_ADDRESS_ENABLE)

    #define EZI2C_1_EZI2C_SCL_STRETCH_ENABLE        (0u != EZI2C_1_EZI2C_CLOCK_STRETCHING)
    #define EZI2C_1_EZI2C_SCL_STRETCH_DISABLE       (!EZI2C_1_EZI2C_SCL_STRETCH_ENABLE)
    #define EZI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST  (EZI2C_1_EZI2C_SCL_STRETCH_ENABLE)
    #define EZI2C_1_EZI2C_SCL_STRETCH_DISABLE_CONST (EZI2C_1_EZI2C_SCL_STRETCH_DISABLE)

    #define EZI2C_1_EZI2C_WAKE_ENABLE_CONST         (0u != EZI2C_1_EZI2C_WAKE_ENABLE)
    #define EZI2C_1_EZI2C_EC_AM_ENABLE              (0u != EZI2C_1_EZI2C_WAKE_ENABLE)

#endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */

#define EZI2C_1_EZI2C_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_EZI2C_1) || \
                                                   (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint32 enableClockStretch;
    uint32 enableMedianFilter;
    uint32 numberOfAddresses;
    uint32 primarySlaveAddr;
    uint32 secondarySlaveAddr;
    uint32 subAddrSize;
    uint32 enableWake;
} EZI2C_1_EZI2C_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

#if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    void EZI2C_1_EzI2CInit(const EZI2C_1_EZI2C_INIT_STRUCT *config);
#endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */

uint32 EZI2C_1_EzI2CGetActivity(void);

void   EZI2C_1_EzI2CSetAddress1(uint32 address);
uint32 EZI2C_1_EzI2CGetAddress1(void);
void   EZI2C_1_EzI2CSetBuffer1(uint32 bufSize, uint32 rwBoundary, volatile uint8 * buffer);
void   EZI2C_1_EzI2CSetReadBoundaryBuffer1(uint32 rwBoundary);

#if(EZI2C_1_SECONDARY_ADDRESS_ENABLE_CONST)
    void   EZI2C_1_EzI2CSetAddress2(uint32 address);
    uint32 EZI2C_1_EzI2CGetAddress2(void);
    void   EZI2C_1_EzI2CSetBuffer2(uint32 bufSize, uint32 rwBoundary, volatile uint8 * buffer);
    void   EZI2C_1_EzI2CSetReadBoundaryBuffer2(uint32 rwBoundary);
#endif /* (EZI2C_1_SECONDARY_ADDRESS_ENABLE_CONST) */

#if(EZI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST)
    CY_ISR_PROTO(EZI2C_1_EZI2C_STRETCH_ISR);
#endif /* (EZI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST) */

#if(EZI2C_1_EZI2C_SCL_STRETCH_DISABLE_CONST)
    CY_ISR_PROTO(EZI2C_1_EZI2C_NO_STRETCH_ISR);
#endif /* (EZI2C_1_EZI2C_SCL_STRETCH_DISABLE) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (EZI2C_1_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void EZI2C_1_EZI2CCyBtldrCommStart(void);
    void EZI2C_1_EZI2CCyBtldrCommStop (void);
    void EZI2C_1_EZI2CCyBtldrCommReset(void);
    cystatus EZI2C_1_EZI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus EZI2C_1_EZI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (EZI2C_1_EZI2C_BTLDR_COMM_ENABLED) */


/***************************************
*            API Constants
***************************************/

/* Configuration structure constants */
#define EZI2C_1_EZI2C_ONE_ADDRESS      (0u)
#define EZI2C_1_EZI2C_TWO_ADDRESSES    (1u)

#define EZI2C_1_EZI2C_PRIMARY_ADDRESS  (0u)
#define EZI2C_1_EZI2C_BOTH_ADDRESSES   (1u)

#define EZI2C_1_EZI2C_SUB_ADDR8_BITS   (0u)
#define EZI2C_1_EZI2C_SUB_ADDR16_BITS  (1u)

/* EZI2C_1_EzI2CGetActivity() return constants */
#define EZI2C_1_EZI2C_STATUS_SECOND_OFFSET (1u)
#define EZI2C_1_EZI2C_STATUS_READ1     ((uint32) (EZI2C_1_INTR_SLAVE_I2C_NACK))        /* Bit [1]   */
#define EZI2C_1_EZI2C_STATUS_WRITE1    ((uint32) (EZI2C_1_INTR_SLAVE_I2C_WRITE_STOP))  /* Bit [3]   */
#define EZI2C_1_EZI2C_STATUS_READ2     ((uint32) (EZI2C_1_INTR_SLAVE_I2C_NACK >> \
                                                           EZI2C_1_EZI2C_STATUS_SECOND_OFFSET)) /* Bit [0]   */
#define EZI2C_1_EZI2C_STATUS_WRITE2    ((uint32) (EZI2C_1_INTR_SLAVE_I2C_WRITE_STOP >> \
                                                           EZI2C_1_EZI2C_STATUS_SECOND_OFFSET)) /* Bit [2]   */
#define EZI2C_1_EZI2C_STATUS_ERR       ((uint32) (0x10u))                                       /* Bit [4]   */
#define EZI2C_1_EZI2C_STATUS_BUSY      ((uint32) (0x20u))                                       /* Bit [5]   */
#define EZI2C_1_EZI2C_CLEAR_STATUS     ((uint32) (0x1Fu))                                       /* Bits [0-4]*/
#define EZI2C_1_EZI2C_CMPLT_INTR_MASK  ((uint32) (EZI2C_1_INTR_SLAVE_I2C_NACK | \
                                                           EZI2C_1_INTR_SLAVE_I2C_WRITE_STOP))


/***************************************
*     Vars with External Linkage
***************************************/

#if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const EZI2C_1_EZI2C_INIT_STRUCT EZI2C_1_configEzI2C;
#endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*           FSM states
***************************************/

/* Returns to master when there is no data to transmit */
#define EZI2C_1_EZI2C_OVFL_RETURN  (0xFFu)

/* States of EZI2C Slave FSM */
#define EZI2C_1_EZI2C_FSM_OFFSET_HI8 ((uint8) (0x02u)) /* Idle state for 1 addr: waits for high byte offset */
#define EZI2C_1_EZI2C_FSM_OFFSET_LO8 ((uint8) (0x00u)) /* Idle state for 2 addr: waits for low byte offset  */
#define EZI2C_1_EZI2C_FSM_BYTE_WRITE ((uint8) (0x01u)) /* Data byte write state: byte by byte mode          */
#define EZI2C_1_EZI2C_FSM_WAIT_STOP  ((uint8) (0x03u)) /* Discards written bytes as they do not match write
                                                                   criteria */
#define EZI2C_1_EZI2C_FSM_WRITE_MASK ((uint8) (0x01u)) /* Incorporates write states: EZI2C_FSM_BYTE_WRITE and
                                                                   EZI2C_FSM_WAIT_STOP  */

#define EZI2C_1_EZI2C_FSM_IDLE     ((EZI2C_1_SUB_ADDRESS_SIZE16) ?      \
                                                (EZI2C_1_EZI2C_FSM_OFFSET_HI8) : \
                                                (EZI2C_1_EZI2C_FSM_OFFSET_LO8))

#define EZI2C_1_EZI2C_CONTINUE_TRANSFER    (1u)
#define EZI2C_1_EZI2C_COMPLETE_TRANSFER    (0u)

#define EZI2C_1_EZI2C_NACK_RECEIVED_ADDRESS  (0u)
#define EZI2C_1_EZI2C_ACK_RECEIVED_ADDRESS   (1u)

#define EZI2C_1_EZI2C_ACTIVE_ADDRESS1  (0u)
#define EZI2C_1_EZI2C_ACTIVE_ADDRESS2  (1u)


/***************************************
*       Macro Definitions
***************************************/

/* Access to global variables */
#if(EZI2C_1_SECONDARY_ADDRESS_ENABLE_CONST)

    #define EZI2C_1_EZI2C_UPDATE_LOC_STATUS(activeAddress, locStatus) \
            do{ \
                (locStatus) >>= (activeAddress); \
            }while(0)

    #define EZI2C_1_EZI2C_GET_INDEX(activeAddress) \
            ((EZI2C_1_EZI2C_ACTIVE_ADDRESS1 == (activeAddress)) ? \
                ((uint32) EZI2C_1_indexBuf1) :                    \
                ((uint32) EZI2C_1_indexBuf2))

    #define EZI2C_1_EZI2C_GET_OFFSET(activeAddress) \
            ((EZI2C_1_EZI2C_ACTIVE_ADDRESS1 == (activeAddress)) ? \
                ((uint32) EZI2C_1_offsetBuf1) :                   \
                ((uint32) EZI2C_1_offsetBuf2))

    #define EZI2C_1_EZI2C_SET_INDEX(activeAddress, locIndex) \
            do{ \
                if(EZI2C_1_EZI2C_ACTIVE_ADDRESS1 == (activeAddress)) \
                {    \
                    EZI2C_1_indexBuf1 = (uint16) (locIndex); \
                }    \
                else \
                {    \
                    EZI2C_1_indexBuf2 = (uint16) (locIndex); \
                }    \
            }while(0)

    #define EZI2C_1_EZI2C_SET_OFFSET(activeAddress, locOffset) \
            do{ \
                if(EZI2C_1_EZI2C_ACTIVE_ADDRESS1 == (activeAddress)) \
                {    \
                    EZI2C_1_offsetBuf1 = (uint8) (locOffset); \
                }    \
                else \
                {    \
                    EZI2C_1_offsetBuf2 = (uint8) (locOffset); \
                }    \
            }while(0)
#else
    #define EZI2C_1_EZI2C_UPDATE_LOC_STATUS(activeAddress, locStatus)  do{ /* Empty*/ }while(0)

    #define EZI2C_1_EZI2C_GET_INDEX(activeAddress)  ((uint32) (EZI2C_1_indexBuf1))

    #define EZI2C_1_EZI2C_GET_OFFSET(activeAddress) ((uint32) (EZI2C_1_offsetBuf1))

    #define EZI2C_1_EZI2C_SET_INDEX(activeAddress, locIndex) \
            do{ \
                EZI2C_1_indexBuf1 = (uint16) (locIndex); \
            }while(0)

    #define EZI2C_1_EZI2C_SET_OFFSET(activeAddress, locOffset) \
            do{ \
                EZI2C_1_offsetBuf1 = (uint8) (locOffset); \
            }while(0)

#endif  /* (EZI2C_1_SUB_ADDRESS_SIZE16_CONST) */


/***************************************
*      Common Register Settings
***************************************/

#define EZI2C_1_CTRL_EZI2C     (EZI2C_1_CTRL_MODE_I2C)

#define EZI2C_1_EZI2C_CTRL     (EZI2C_1_I2C_CTRL_S_GENERAL_IGNORE | \
                                         EZI2C_1_I2C_CTRL_SLAVE_MODE)

#define EZI2C_1_EZI2C_CTRL_AUTO    (EZI2C_1_I2C_CTRL_S_READY_ADDR_ACK      | \
                                             EZI2C_1_I2C_CTRL_S_READY_DATA_ACK      | \
                                             EZI2C_1_I2C_CTRL_S_NOT_READY_ADDR_NACK | \
                                             EZI2C_1_I2C_CTRL_S_NOT_READY_DATA_NACK)

#define EZI2C_1_EZI2C_RX_CTRL  ((EZI2C_1_FIFO_SIZE - 1u)   | \
                                          EZI2C_1_RX_CTRL_MSB_FIRST | \
                                          EZI2C_1_RX_CTRL_ENABLED)

#define EZI2C_1_EZI2C_TX_FIFO_CTRL (2u)
#define EZI2C_1_TX_LOAD_SIZE       (2u)

#define EZI2C_1_EZI2C_TX_CTRL  ((EZI2C_1_FIFO_SIZE - 1u)   | \
                                          EZI2C_1_TX_CTRL_MSB_FIRST | \
                                          EZI2C_1_TX_CTRL_ENABLED)

#define EZI2C_1_EZI2C_INTR_SLAVE_MASK  (EZI2C_1_INTR_SLAVE_I2C_BUS_ERROR | \
                                                 EZI2C_1_INTR_SLAVE_I2C_ARB_LOST  | \
                                                 EZI2C_1_INTR_SLAVE_I2C_STOP)

#define EZI2C_1_INTR_SLAVE_COMPLETE    (EZI2C_1_INTR_SLAVE_I2C_STOP | \
                                                 EZI2C_1_INTR_SLAVE_I2C_NACK | \
                                                 EZI2C_1_INTR_SLAVE_I2C_WRITE_STOP)


/***************************************
*    Initialization Register Settings
***************************************/

#if(EZI2C_1_SCB_MODE_EZI2C_CONST_CFG)

    #define EZI2C_1_EZI2C_DEFAULT_CTRL \
                                (EZI2C_1_GET_CTRL_ADDR_ACCEPT(EZI2C_1_EZI2C_NUMBER_OF_ADDRESSES) | \
                                 EZI2C_1_GET_CTRL_EC_AM_MODE (EZI2C_1_EZI2C_WAKE_ENABLE))

    #if(EZI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST)
        #define EZI2C_1_EZI2C_DEFAULT_I2C_CTRL (EZI2C_1_EZI2C_CTRL)
    #else
        #define EZI2C_1_EZI2C_DEFAULT_I2C_CTRL (EZI2C_1_EZI2C_CTRL_AUTO | EZI2C_1_EZI2C_CTRL)
    #endif /* (EZI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST) */


    #define EZI2C_1_EZI2C_DEFAULT_RX_MATCH \
                                (EZI2C_1_GET_I2C_8BIT_ADDRESS(EZI2C_1_EZI2C_PRIMARY_SLAVE_ADDRESS) | \
                                 EZI2C_1_GET_RX_MATCH_MASK   (EZI2C_1_EZI2C_SLAVE_ADDRESS_MASK))

    #define EZI2C_1_EZI2C_DEFAULT_RX_CTRL \
                                (EZI2C_1_GET_RX_CTRL_MEDIAN(EZI2C_1_EZI2C_MEDIAN_FILTER_ENABLE) | \
                                 EZI2C_1_EZI2C_RX_CTRL)

    #define EZI2C_1_EZI2C_DEFAULT_TX_CTRL  (EZI2C_1_EZI2C_TX_CTRL)

    #define EZI2C_1_EZI2C_DEFAULT_RX_FIFO_CTRL (0u)
    #if(EZI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST)
        #define EZI2C_1_EZI2C_DEFAULT_TX_FIFO_CTRL (0u)
    #else
        #define EZI2C_1_EZI2C_DEFAULT_TX_FIFO_CTRL (2u)
    #endif /* (EZI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST) */

    /* Interrupt sources */
    #define EZI2C_1_EZI2C_DEFAULT_INTR_I2C_EC_MASK (EZI2C_1_NO_INTR_SOURCES)
    #define EZI2C_1_EZI2C_DEFAULT_INTR_SPI_EC_MASK (EZI2C_1_NO_INTR_SOURCES)
    #define EZI2C_1_EZI2C_DEFAULT_INTR_MASTER_MASK (EZI2C_1_NO_INTR_SOURCES)
    #define EZI2C_1_EZI2C_DEFAULT_INTR_TX_MASK     (EZI2C_1_NO_INTR_SOURCES)

    #if(EZI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST)
        #define EZI2C_1_EZI2C_DEFAULT_INTR_RX_MASK     (EZI2C_1_NO_INTR_SOURCES)
        #define EZI2C_1_EZI2C_DEFAULT_INTR_SLAVE_MASK  (EZI2C_1_INTR_SLAVE_I2C_ADDR_MATCH | \
                                                                 EZI2C_1_EZI2C_INTR_SLAVE_MASK)
    #else
        #define EZI2C_1_EZI2C_DEFAULT_INTR_RX_MASK     (EZI2C_1_INTR_RX_NOT_EMPTY)
        #define EZI2C_1_EZI2C_DEFAULT_INTR_SLAVE_MASK  (EZI2C_1_INTR_SLAVE_I2C_START | \
                                                                 EZI2C_1_EZI2C_INTR_SLAVE_MASK)
    #endif /* (EZI2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST) */

#endif /* (EZI2C_1_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* (CY_SCB_EZI2C_EZI2C_1_H) */


/* [] END OF FILE */
