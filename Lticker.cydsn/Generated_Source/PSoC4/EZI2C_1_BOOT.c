/*******************************************************************************
* File Name: EZI2C_1_BOOT.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the bootloader
*  communication support in SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "EZI2C_1.h"

#if(EZI2C_1_SCB_MODE_I2C_INC)
    #include "EZI2C_1_I2C.h"
#endif /* (EZI2C_1_SCB_MODE_I2C_INC) */

#if(EZI2C_1_SCB_MODE_EZI2C_INC)
    #include "EZI2C_1_EZI2C.h"
#endif /* (EZI2C_1_SCB_MODE_EZI2C_INC) */

#if(EZI2C_1_SCB_MODE_SPI_INC || EZI2C_1_SCB_MODE_UART_INC)
    #include "EZI2C_1_SPI_UART.h"
#endif /* (EZI2C_1_SCB_MODE_SPI_INC || EZI2C_1_SCB_MODE_UART_INC) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_EZI2C_1) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/*******************************************************************************
* Function Name: EZI2C_1_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStart function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void EZI2C_1_CyBtldrCommStart(void)
{
    #if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
        if(EZI2C_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            EZI2C_1_I2CCyBtldrCommStart();
        }
        else if(EZI2C_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            EZI2C_1_SpiCyBtldrCommStart();
        }
        else if(EZI2C_1_SCB_MODE_UART_RUNTM_CFG)
        {
            EZI2C_1_UartCyBtldrCommStart();
        }
        else if(EZI2C_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
             EZI2C_1_EzI2CCyBtldrCommStart();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(EZI2C_1_SCB_MODE_I2C_CONST_CFG)
        EZI2C_1_I2CCyBtldrCommStart();

    #elif(EZI2C_1_SCB_MODE_SPI_CONST_CFG)
        EZI2C_1_SpiCyBtldrCommStart();

    #elif(EZI2C_1_SCB_MODE_UART_CONST_CFG)
        EZI2C_1_UartCyBtldrCommStart();

    #elif(EZI2C_1_SCB_MODE_EZI2C_CONST_CFG)
        EZI2C_1_EzI2CCyBtldrCommStart();

    #else
        /* Do nothing */

    #endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: EZI2C_1_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls CyBtldrCommStop function function of the bootloader communication
*  component for selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void EZI2C_1_CyBtldrCommStop(void)
{
    #if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
        if(EZI2C_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            EZI2C_1_I2CCyBtldrCommStop();
        }
        else if(EZI2C_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            EZI2C_1_SpiCyBtldrCommStop();
        }
        else if(EZI2C_1_SCB_MODE_UART_RUNTM_CFG)
        {
            EZI2C_1_UartCyBtldrCommStop();
        }
        else if(EZI2C_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            EZI2C_1_EzI2CCyBtldrCommStop();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(EZI2C_1_SCB_MODE_I2C_CONST_CFG)
        EZI2C_1_I2CCyBtldrCommStop();

    #elif(EZI2C_1_SCB_MODE_SPI_CONST_CFG)
        EZI2C_1_SpiCyBtldrCommStop();

    #elif(EZI2C_1_SCB_MODE_UART_CONST_CFG)
        EZI2C_1_UartCyBtldrCommStop();

    #elif(EZI2C_1_SCB_MODE_EZI2C_CONST_CFG)
        EZI2C_1_EzI2CCyBtldrCommStop();

    #else
        /* Do nothing */

    #endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: EZI2C_1_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommReset function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void EZI2C_1_CyBtldrCommReset(void)
{
    #if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
        if(EZI2C_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            EZI2C_1_I2CCyBtldrCommReset();
        }
        else if(EZI2C_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            EZI2C_1_SpiCyBtldrCommReset();
        }
        else if(EZI2C_1_SCB_MODE_UART_RUNTM_CFG)
        {
            EZI2C_1_UartCyBtldrCommReset();
        }
        else if(EZI2C_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            EZI2C_1_EzI2CCyBtldrCommReset();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(EZI2C_1_SCB_MODE_I2C_CONST_CFG)
        EZI2C_1_I2CCyBtldrCommReset();

    #elif(EZI2C_1_SCB_MODE_SPI_CONST_CFG)
        EZI2C_1_SpiCyBtldrCommReset();

    #elif(EZI2C_1_SCB_MODE_UART_CONST_CFG)
        EZI2C_1_UartCyBtldrCommReset();

    #elif(EZI2C_1_SCB_MODE_EZI2C_CONST_CFG)
        EZI2C_1_EzI2CCyBtldrCommReset();

    #else
        /* Do nothing */

    #endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: EZI2C_1_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommRead function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus EZI2C_1_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
        if(EZI2C_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = EZI2C_1_I2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(EZI2C_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = EZI2C_1_SpiCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(EZI2C_1_SCB_MODE_UART_RUNTM_CFG)
        {
            status = EZI2C_1_UartCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(EZI2C_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = EZI2C_1_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }

    #elif(EZI2C_1_SCB_MODE_I2C_CONST_CFG)
        status = EZI2C_1_I2CCyBtldrCommRead(pData, size, count, timeOut);

    #elif(EZI2C_1_SCB_MODE_SPI_CONST_CFG)
        status = EZI2C_1_SpiCyBtldrCommRead(pData, size, count, timeOut);

    #elif(EZI2C_1_SCB_MODE_UART_CONST_CFG)
        status = EZI2C_1_UartCyBtldrCommRead(pData, size, count, timeOut);

    #elif(EZI2C_1_SCB_MODE_EZI2C_CONST_CFG)
        status = EZI2C_1_EzI2CCyBtldrCommRead(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}


/*******************************************************************************
* Function Name: EZI2C_1_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommWrite  function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus EZI2C_1_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
        if(EZI2C_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = EZI2C_1_I2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(EZI2C_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = EZI2C_1_SpiCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(EZI2C_1_SCB_MODE_UART_RUNTM_CFG)
        {
            status = EZI2C_1_UartCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(EZI2C_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = EZI2C_1_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode */
        }
    #elif(EZI2C_1_SCB_MODE_I2C_CONST_CFG)
        status = EZI2C_1_I2CCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(EZI2C_1_SCB_MODE_SPI_CONST_CFG)
        status = EZI2C_1_SpiCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(EZI2C_1_SCB_MODE_UART_CONST_CFG)
        status = EZI2C_1_UartCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(EZI2C_1_SCB_MODE_EZI2C_CONST_CFG)
        status = EZI2C_1_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode */

    #endif /* (EZI2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_EZI2C_1) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */


/* [] END OF FILE */
