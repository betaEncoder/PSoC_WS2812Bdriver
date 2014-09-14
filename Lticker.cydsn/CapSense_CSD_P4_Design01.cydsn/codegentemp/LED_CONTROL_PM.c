/*******************************************************************************
* File Name: LED_CONTROL_PM.c
* Version 1.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LED_CONTROL.h"

static LED_CONTROL_BACKUP_STRUCT LED_CONTROL_backup;


/*******************************************************************************
* Function Name: LED_CONTROL_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: LED_CONTROL_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_Sleep(void)
{
    if(0u != (LED_CONTROL_BLOCK_CONTROL_REG & LED_CONTROL_MASK))
    {
        LED_CONTROL_backup.enableState = 1u;
    }
    else
    {
        LED_CONTROL_backup.enableState = 0u;
    }

    LED_CONTROL_Stop();
    LED_CONTROL_SaveConfig();
}


/*******************************************************************************
* Function Name: LED_CONTROL_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: LED_CONTROL_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_Wakeup(void)
{
    LED_CONTROL_RestoreConfig();

    if(0u != LED_CONTROL_backup.enableState)
    {
        LED_CONTROL_Enable();
    }
}


/* [] END OF FILE */
