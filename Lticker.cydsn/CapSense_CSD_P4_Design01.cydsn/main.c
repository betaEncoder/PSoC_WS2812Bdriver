/*******************************************************************************
* File Name: main.c
*
* Version: 1.10
*
* Description:
*  The project explains the usage of CapSense CSD component. The 2 buttons and
*  linear sliders are used as sensing elements. LED displays buttons active 
*  state and slider position is shown on LCD.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <device.h>

/* CapSense Slider resoluton is set to 127 (7 bits).
*  Since PWM has 16 bit resolution, slider position value should be shifted left
*  by 9 bits.
*/
#define SLIDER_POS_TO_COMPARE_SHIFT    (9u)

uint16 curPos, oldPos;

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*  Main function performs following functions:
*   1. Enable global interrupts.
*   2. Initialize CapSense CSD and Start the sensor scanning loop.
*   3. Process scanning results and display it on with LEDs.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
int main()
{
    /* Enable global interrupts */
    CyGlobalIntEnable;
    
    /* Start PWM and CapSense components */
    LED_CONTROL_Start();

    CapSense_CSD_Start();	

    /* Initialize baselines */ 
    CapSense_CSD_InitializeAllBaselines();
    
    while(1u)
    {
        /* Update all baselines */
        CapSense_CSD_UpdateEnabledBaselines();
        
   		/* Start scanning all enabled sensors */
    	CapSense_CSD_ScanEnabledWidgets();
    
        /* Wait for scanning to complete */
		while(CapSense_CSD_IsBusy() != 0);

		/* Display CapSense state using LEDs */
        CapSense_DisplayState();
    }
}

/*******************************************************************************
* Function Name: CapSense_DisplayState
********************************************************************************
* Summary:
*  Changes LEDs brightness by changing the duty cycle of PWM signals.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_DisplayState(void)
{
    /* Find Slider Position */
    curPos = CapSense_CSD_GetCentroidPos(CapSense_CSD_LINEARSLIDER0__LS);    
    
    /* Reset position */
    if(curPos == 0xFFFFu)
    {
        curPos = 0u;
    }
                
    /* Move bargraph */
    if (curPos != oldPos)
    {
        oldPos = curPos;
        /* Display Slider bargraph */
        if (curPos != 0u)
        {
            LED_CONTROL_WriteCompare((uint32)curPos << SLIDER_POS_TO_COMPARE_SHIFT);
        }        
    }
}


/* [] END OF FILE */
