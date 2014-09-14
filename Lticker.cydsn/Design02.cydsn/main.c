/*******************************************************************************
* Project Name:      CapSense_LowPower
* Version:           1.0
* Device Used:       CY8C4014LQI-422 
* Software Used:     PSoC Creator 3.0 SP1
* Compiler Used:     ARM GCC 4.7.3 
* Related Hardware:  CY8CKIT-040 
********************************************************************************
* Theory of Operation:
* This project demonstrates interfacing of a touchpad (6x5 sensors) with a low 
* power feature. Device goes to Deep-Sleep mode and wakes up periodically at 200ms
* when no touch is detected on the touchpad. Wake up interrupt period is configured 
* to 30ms when a touch is detected. Interrupts are obtained using the Watchdog timer. 
* To detect the touch, instead of scanning all the sensors, proximity sensor widget 
* is used. It is formed by ganging all the sensors of the touchpad row sensors. When 
* the touch is detected, touchpad sensors configuration is restored and entire touchpad 
* is scanned. The touch position information (x,y) is sent using UART to PC. 
*
*********************************************************************************
* Copyright (2014), Cypress Semiconductor Corporation.
********************************************************************************
* This software, including source code, documentation and related materials
* ("Software") is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and 
* foreign), United States copyright laws and international treaty provisions. 
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the 
* Cypress source code and derivative works for the sole purpose of creating 
* custom software in support of licensee product, such licensee product to be
* used only in conjunction with Cypress's integrated circuit as specified in the
* applicable agreement. Any reproduction, modification, translation, compilation,
* or representation of this Software except as specified above is prohibited 
* without the express written permission of Cypress.
* 
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes to the Software without notice. 
* Cypress does not assume any liability arising out of the application or use
* of Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use as critical components in any products 
* where a malfunction or failure may reasonably be expected to result in 
* significant injury or death ("High Risk Product"). By including Cypress's 
* product in a High Risk Product, the manufacturer of such system or application
* assumes all risk of such use and in doing so indemnifies Cypress against all
* liability. Use of this Software may be limited by and subject to the applicable
* Cypress software license agreement.
*/
#include <project.h>
#include "main.h"
#include "stdio.h"

/* This variable is used to generate required WDT interrupt period */ 
uint32 ILODelayCycles = WDT_MATCH_VALUE_200MS;

int main()
{	
	/* This variable is used to store the string of characters to be displayed on UART Terminal */
	char buffer[10]="";
	
	/* This variable is used to store the X and Y coordinates of the touchpad touch position */
	uint16 touchPos[2]={0,0};
	
	/* Proximity touch state */
	uint8 proximityState = 0;
	
	/* Touchpad touch state */
	uint8 touchState = 0;
	
	/* This variable is used to implement software counter */
	uint8 softCounter=0;			
	
   	/* Enable Global Interrupt */
    CyGlobalIntEnable; 
	
	/* Disable watchdog reset */
	CySysWdtDisable();	
	
	#if TUNING_ENABLE
		
	/* Enable Proximity sensor. Touchpad is enabled by default */	
	CapSense_EnableWidget(CapSense_PROXIMITYSENSOR0__PROX);
	
	/* Start the tuner */
	CapSense_TunerStart();	
	while(1)
	{
		/* Read and process the parameters received from host */
		CapSense_TunerComm();
	}
	
	#else 
		
	/* Start CapSense */	
	CapSense_Start();	

    /* Initialize baselines */ 
    CapSense_InitializeAllBaselines();
	
	/* Enable proximity widget */		
	CapSense_EnableWidget(CapSense_PROXIMITYSENSOR0__PROX);			
	
	#if TX_ENABLE
		
	/* Start software TX */
	SW_TX_Start();	
	
	#endif
	
	/* Update the match register for generating a periodic WDT ISR.
    Note: In order to do a periodic ISR using WDT, Match value needs to be
    updated every WDT ISR with the desired time value added on top of the
    existing match value */
    CySysWdtWriteMatch(ILODelayCycles);
      
    /* Enable the WDT interrupt in SRSS INTR mask register */
    CySysWdtUnmaskInterrupt();
  
    /* Map the WatchDog_ISR vector to the WDT_ISR */
    isr_WDT_StartEx(WDT_ISR);      	
	
	#endif	
	
	/* Print Charaters on PC UART Terminal */
	SW_TX_PutCRLF();	
	SW_TX_PutCRLF();
	SW_TX_PutString("CYPRESS SEMICONDUCTOR");
	SW_TX_PutCRLF();
	SW_TX_PutCRLF();
	SW_TX_PutString("PSoC 4000 - Starter Design: Low Power CapSense");
	SW_TX_PutCRLF();
	SW_TX_PutCRLF();
	SW_TX_PutString("  X    Y");
	SW_TX_PutCRLF();	
	
	for(;;)
    {	    
		/* Check the system state */
		if(proximityState == 0)
		{
			/* 200MS Deep-Sleep state, scan only proximity sensor */
			CapSense_ScanSensor(CapSense_SENSOR_PROXIMITYSENSOR0__PROX);
			
			/* Wait till the CapSense scan is complete */
			while(CapSense_IsBusy() != 0)
			{
				
			}			
			
			CapSense_UpdateSensorBaseline(CapSense_SENSOR_PROXIMITYSENSOR0__PROX);
			
			/* Check if proximity sensor is active */
			proximityState = CapSense_CheckIsWidgetActive(CapSense_PROXIMITYSENSOR0__PROX);			
		}
		
		if(proximityState)
		{				
			/* Configure the wake up period to 30ms */			
			ILODelayCycles = WDT_MATCH_VALUE_30MS;	
			
			/* Disable WDT interrupt */
			CySysWdtMaskInterrupt();
			
			/* Set WDT interrupt period */
			CySysWdtWriteMatch((uint16)CySysWdtReadCount() + ILODelayCycles);
				
			/* Enable WDT interrupt */
			CySysWdtUnmaskInterrupt();
						
			/* Disable proximity sensor widget */
			CapSense_DisableWidget(CapSense_PROXIMITYSENSOR0__PROX);
			
			/* Scan touchpad widget */
			CapSense_ScanEnabledWidgets();
			
	        /* CapSense is scanning; send the data via TX if the previous touch was active */			
			if(touchState)
			{	
				/* Print X and Y coordinates */																
				sprintf(buffer,"\r%3u  %3u",(uint8)touchPos[0], (uint8)touchPos[1]);					
				SW_TX_PutString(buffer);				
				touchState = 0;			
				softCounter = 0;
			}	
			
			/* Wait till the CapSense scan is complete */
			while(CapSense_IsBusy() != 0)
			{
			
			}
									
			/* Update baseline of touchpad widget */
	        CapSense_UpdateEnabledBaselines();	
			
			/* Find Slider Position */
	   		touchState = CapSense_GetTouchCentroidPos((uint32)CapSense_TOUCHPAD0__TP,touchPos);
			
			/* If the CapSense touch is inactive, increment the software counter */
			if(touchState == 0)
			{				
				softCounter++;					
			}			
						
			if(softCounter > 100)
			{
				/* CapSense touch is inactive for >3s. Increase Deep-Sleep duration */ 
				ILODelayCycles = WDT_MATCH_VALUE_200MS;									
				
				/* Reset counter */
				softCounter = 0;				
				
				/* Clear Proximity Sensor status */
				proximityState = 0;
				
				/* Enable Proximity sensor widget */
				CapSense_EnableWidget(CapSense_PROXIMITYSENSOR0__PROX);	
			}	
		}
		
		/* Prepare CapSense component for Deep-Sleep mode */
		CapSense_Sleep();
		
		/* Enter Deep-Sleep */
		CySysPmDeepSleep();			
		
		/* Reconfigure CapSense component after Deep-Sleep */
		CapSense_Wakeup();			
    }
}

/******************************************************************************
* Function Name: WDT_ISR_Handler
*******************************************************************************
*
* Summary:
* Interrupt Service Routine for the watchdog timer interrupt. The periodicity 
* of the interrupt is depended on the match value written into the counter 
* register using API - CySysWdtWriteMatch().
*
******************************************************************************/
CY_ISR(WDT_ISR)
{
	/* Clear WDT interrupt */ 
	CySysWdtClearInterrupt(); 
 
 	/* Write WDT_MATCH with current match value + desired match value */ 
 	CySysWdtWriteMatch((uint16)CySysWdtReadMatch()+ILODelayCycles); 
}
/* [] END OF FILE */
