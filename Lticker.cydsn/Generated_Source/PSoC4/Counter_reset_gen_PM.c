/*******************************************************************************
* File Name: Counter_reset_gen_PM.c  
* Version 2.40
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "Counter_reset_gen.h"

static Counter_reset_gen_backupStruct Counter_reset_gen_backup;


/*******************************************************************************
* Function Name: Counter_reset_gen_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Counter_reset_gen_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Counter_reset_gen_SaveConfig(void) 
{
    #if (!Counter_reset_gen_UsingFixedFunction)

        Counter_reset_gen_backup.CounterUdb = Counter_reset_gen_ReadCounter();

        #if (CY_UDB_V0)
            Counter_reset_gen_backup.CounterPeriod = Counter_reset_gen_ReadPeriod();
            Counter_reset_gen_backup.CompareValue = Counter_reset_gen_ReadCompare();
            Counter_reset_gen_backup.InterruptMaskValue = Counter_reset_gen_STATUS_MASK;
        #endif /* CY_UDB_V0 */

        #if(!Counter_reset_gen_ControlRegRemoved)
            Counter_reset_gen_backup.CounterControlRegister = Counter_reset_gen_ReadControlRegister();
        #endif /* (!Counter_reset_gen_ControlRegRemoved) */

    #endif /* (!Counter_reset_gen_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_reset_gen_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Counter_reset_gen_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_reset_gen_RestoreConfig(void) 
{      
    #if (!Counter_reset_gen_UsingFixedFunction)

        #if (CY_UDB_V0)
            uint8 Counter_reset_gen_interruptState;
        #endif  /* (CY_UDB_V0) */

       Counter_reset_gen_WriteCounter(Counter_reset_gen_backup.CounterUdb);

        #if (CY_UDB_V0)
            Counter_reset_gen_WritePeriod(Counter_reset_gen_backup.CounterPeriod);
            Counter_reset_gen_WriteCompare(Counter_reset_gen_backup.CompareValue);

            Counter_reset_gen_interruptState = CyEnterCriticalSection();
            Counter_reset_gen_STATUS_AUX_CTRL |= Counter_reset_gen_STATUS_ACTL_INT_EN_MASK;
            CyExitCriticalSection(Counter_reset_gen_interruptState);

            Counter_reset_gen_STATUS_MASK = Counter_reset_gen_backup.InterruptMaskValue;
        #endif  /* (CY_UDB_V0) */

        #if(!Counter_reset_gen_ControlRegRemoved)
            Counter_reset_gen_WriteControlRegister(Counter_reset_gen_backup.CounterControlRegister);
        #endif /* (!Counter_reset_gen_ControlRegRemoved) */

    #endif /* (!Counter_reset_gen_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_reset_gen_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Counter_reset_gen_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_reset_gen_Sleep(void) 
{
    #if(!Counter_reset_gen_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_reset_gen_CTRL_ENABLE == (Counter_reset_gen_CONTROL & Counter_reset_gen_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_reset_gen_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_reset_gen_backup.CounterEnableState = 0u;
        }
    #else
        Counter_reset_gen_backup.CounterEnableState = 1u;
        if(Counter_reset_gen_backup.CounterEnableState != 0u)
        {
            Counter_reset_gen_backup.CounterEnableState = 0u;
        }
    #endif /* (!Counter_reset_gen_ControlRegRemoved) */
    
    Counter_reset_gen_Stop();
    Counter_reset_gen_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_reset_gen_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Counter_reset_gen_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_reset_gen_Wakeup(void) 
{
    Counter_reset_gen_RestoreConfig();
    #if(!Counter_reset_gen_ControlRegRemoved)
        if(Counter_reset_gen_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_reset_gen_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Counter_reset_gen_ControlRegRemoved) */
    
}


/* [] END OF FILE */
