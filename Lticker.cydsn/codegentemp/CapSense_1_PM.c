/*******************************************************************************
* File Name: CapSense_1_PM.c
* Version 2.0
*
* Description:
*  This file provides Sleep APIs for CapSense CSD Component.
*
* Note:
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "CapSense_1.h"

static CapSense_1_BACKUP_STRUCT CapSense_1_backup =
{   
    0x00u, /* enableState; */
};


/*******************************************************************************
* Function Name: CapSense_1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the customer configuration of CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense_1_backup - used to save the component state before entering the  sleep 
*  mode and none-retention registers.
*
* Side Effects:
*  None
*
*******************************************************************************/
void CapSense_1_SaveConfig(void)
{
	if ((CapSense_1_CSD_CFG_REG & CapSense_1_CSD_CFG_ENABLE) != 0u)
	{
		CapSense_1_backup.enableState = 1u;
	}
}


/*******************************************************************************
* Function Name: CapSense_1_Sleep
********************************************************************************
*
* Summary:
*  Disables the Active mode power.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense_1_backup - used to save the component state before entering the sleep 
*  mode.
*
*******************************************************************************/
void CapSense_1_Sleep(void)
{
	CapSense_1_SaveConfig();
		
	/* Disable interrupt */
	CyIntDisable(CapSense_1_ISR_NUMBER);
	
	CapSense_1_CSD_CFG_REG &= ~(CapSense_1_CSD_CFG_SENSE_COMP_EN | CapSense_1_CSD_CFG_SENSE_EN);
	
	#if(CapSense_1_IDAC_CNT == 2u)
		CapSense_1_CSD_CFG_REG &= ~(CapSense_1_CSD_CFG_ENABLE);
	#endif /* (CapSense_1_IDAC_CNT == 2u) */
	
	/* Disable Clocks */
    CapSense_1_SenseClk_Stop();
    CapSense_1_SampleClk_Stop();
}


/*******************************************************************************
* Function Name: CapSense_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the CapSense configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Must be called only after CapSense_1_SaveConfig() routine. Otherwise 
*  the component configuration will be overwritten with its initial setting.  
*
* Global Variables:
*  CapSense_1_backup - used to save the component state before entering the sleep 
*  mode and none-retention registers.
*
*******************************************************************************/
void CapSense_1_RestoreConfig(void)
{

}
 
 
/*******************************************************************************
* Function Name: CapSense_1_Wakeup
********************************************************************************
*
* Summary:
*  Restores the CapSense configuration and non-retention register values. 
*  Restores the enabled state of the component by setting the Active mode power template 
*  bits for a number of components used within CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense_1_backup - used to save the component state before entering the sleep 
*  mode and none-retention registers.
*
*******************************************************************************/
void CapSense_1_Wakeup(void)
{
	/* Enable the Clocks */
    CapSense_1_SenseClk_Start();
    CapSense_1_SampleClk_Start();
    
	/* Restore CapSense Enable state */
    if (CapSense_1_backup.enableState != 0u)
    {
        CapSense_1_Enable();
    }
}


/* [] END OF FILE */
