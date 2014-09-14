/*******************************************************************************
* File Name: CapSense_1_INT.c
* Version 2.0
*
* Description:
*  This file provides the source code of the  Interrupt Service Routine (ISR)
*  for the CapSense CSD component.
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

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START CapSense_1_ISR_INTC` */

/* `#END` */

/* Extern functions declarations, Start and Compete scan */
extern void CapSense_1_PreScan(uint32 sensor);
extern void CapSense_1_PostScan(uint32 sensor);

extern uint8 CapSense_1_FindNextSensor(uint8 snsIndex);
 
/* Global variables and arrays */
extern volatile uint8 CapSense_1_csdStatusVar;
extern volatile uint8 CapSense_1_sensorIndex;

static uint8 CapSense_1_snsIndexTmp;

extern volatile uint8 CapSense_1_sensorEnableMask[];
extern uint8 CapSense_1_sensorEnableMaskBackup[];

/*******************************************************************************
* Function Name: CapSense_1_ISR
********************************************************************************
*
* Summary:
*  This ISR is executed when the measure window is closed. The measure window 
*  depends on the sensor scan resolution parameter. 
*  The ISR has two modes: 
*   1. Scans a single sensor and stores the measure result.
*   2. Stores the result of the current measure and starts the next scan till all 
*      the enabled sensors are scanned.
*  This interrupt handler is only used in one channel designs.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense_1_csv - used to provide the status and mode of the scanning process.
*   Mode - a single scan or scan of all the enabled sensors.
*   Status - scan is in progress or ready for new scan.
*  CapSense_1_sensorIndex - used to store a sensor scanning sensor number.
*
* Reentrant:
*  No
*
*******************************************************************************/
CY_ISR(CapSense_1_ISR)
{	
	/*  Place your Interrupt code here. */
    /* `#START CapSense_1_ISR_ENTER` */

    /* `#END` */

	CyIntDisable(CapSense_1_ISR_NUMBER);
    
    CapSense_1_CSD_INTR_REG = 1u;

    CapSense_1_PostScan((uint32)CapSense_1_sensorIndex);
            
    if ((CapSense_1_csdStatusVar & CapSense_1_SW_CTRL_SINGLE_SCAN) != 0u)
    {
        CapSense_1_csdStatusVar &= (uint8)~CapSense_1_SW_STS_BUSY;
    }
    else
    {
        /* Proceed scanning */
        CapSense_1_sensorIndex = CapSense_1_FindNextSensor(CapSense_1_sensorIndex);
        
        /* Check end of scan */
        if(CapSense_1_sensorIndex < CapSense_1_TOTAL_SENSOR_COUNT)
        {
            CapSense_1_PreScan((uint32)CapSense_1_sensorIndex);
        }
        else
        {
            CapSense_1_csdStatusVar &= (uint8)~CapSense_1_SW_STS_BUSY;

			 /* Check if widget has been scanned */
			if((CapSense_1_csdStatusVar & CapSense_1_SW_CTRL_WIDGET_SCAN) != 0u)
			{
			    /* Restore sensorEnableMask array */
				for(CapSense_1_snsIndexTmp = 0u; 
				    CapSense_1_snsIndexTmp < CapSense_1_TOTAL_SENSOR_MASK; 
					CapSense_1_snsIndexTmp++)
				{
					/* Backup sensorEnableMask array */
					CapSense_1_sensorEnableMask[CapSense_1_snsIndexTmp] = CapSense_1_sensorEnableMaskBackup[CapSense_1_snsIndexTmp];
				}
			}
        } 
    }
    CyIntEnable(CapSense_1_ISR_NUMBER);
	
	/*  Place your Interrupt code here. */
    /* `#START CapSense_1_ISR_EXIT` */

    /* `#END` */
}

/* [] END OF FILE */
