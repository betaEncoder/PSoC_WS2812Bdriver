/******************************************************************************
* Project Name		: CapSense_Proximity_Design
* File Name			: main.c
* Version 			: 1.0
* Device Used		: CY8C4014LQI-422
* Software Used		: PSoC Creator 3.0 SP1
* Compiler    		: ARM GCC 4.7.3
* Related Hardware	: CY8CKIT-040 PSoC 4 Kit 
*
********************************************************************************
*                           THEORY OF OPERATION
* The project will demonstrate CapSense Proximity & Software UART TX interface
* for viewing CapSense data. As the hand approaches the proximity wire-loop,
* the brightness of the LED increases (once the hand enters
* the proximity range). The brightness value depends on the hand distance.
*
* Hardware connection required for testing -
* LED	 	- P3_2 (connected in the board itself)
* Prox pin 	- P2_0 (requires an external wire/wire-loop connection)
* Cmod pin	- P0_4 (connected in the board itself)
* Tx pin	- P3_0 (hardwired in CY8CKIT-040 - selected through TX_PORT/TX_PIN
*					macro in 'main.h')
*
* Note: Debug is disabled by default in the project and UART TX line is enabled 
*		on SWD IO line (P3[0]). If debug is desired, the same can be enabled in
*		under 'System' tab in cywdr file. If debug is enabled, either TX should 
*		be disabled (by commenting out TX_ENABLE macro in ‘main.h’) or should be 
*		routed to another pin (by modifying TX_PORT and TX_PIN macros).
********************************************************************************
********************************************************************************
* Copyright (2014), Cypress Semiconductor Corporation. All Rights Reserved.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress)
* and is protected by and subject to worldwide patent protection (United
* States and foreign), United States copyright laws and international treaty
* provisions. Cypress hereby grants to licensee a personal, non-exclusive,
* non-transferable license to copy, use, modify, create derivative works of,
* and compile the Cypress Source Code and derivative works for the sole
* purpose of creating custom software in support of licensee product to be
* used only in conjunction with a Cypress integrated circuit as specified in
* the applicable agreement. Any reproduction, modification, translation,
* compilation, or representation of this software except as specified above 
* is prohibited without the express written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH 
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the 
* materials described herein. Cypress does not assume any liability arising out 
* of the application or use of any product or circuit described herein. Cypress 
* does not authorize its products for use as critical components in life-support 
* systems where a malfunction or failure may reasonably be expected to result in 
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of 
* such use and in doing so indemnifies Cypress against all charges. 
*
* Use of this Software may be limited by and subject to the applicable Cypress
* software license agreement. 
*******************************************************************************/

#include "main.h"

/******************************************************************************
* Function Name: main
*******************************************************************************
*
* Summary:
*  main() performs following functions:
*  1: Initialize Input and Output blocks
*  2: Scans & process Proximity sensor
*  3: Updates the PRSm duty based on sensor position & sends data over Tx
*
* Parameters:
*  None.
*
* Return:
*  None.
*
******************************************************************************/
int main()
{    
	uint8 proximityActive = 0, proximityActivePrevState = 0;
	
	/* Enable Global interrupts for CapSense operation */
	CyGlobalIntEnable;
	
	/* Initialize the input - CapSense block */
	
	/* 1. Enable Proximity sensor as it is disabled by default */
	CapSense_EnableWidget(CapSense_PROXIMITYSENSOR0__PROX);
	
	/* 2. Start CapSense block - Calibrates the proximity sensor for the set sensitivity setting (in the Scan Order tab of Component Configuration */
	CapSense_Start();
		
	/* 3. Initialize Proximity baseline */
	CapSense_InitializeSensorBaseline(PROXIMITY_SENSOR);	
	
	/* Setup the system output and timing blocks */
	/* 4. Setup WDT for generating periodic ISRs and initialize the output blocks - PRSm, UART Tx */
	Output_Init();
	
    for(;;)
    {
        /* Process input side - Proximity sensor */
		/* Check if CapSense block is busy or not and enable the next scan accordingly */
		if(CapSense_IsBusy() == NOT_BUSY)
		{						
			/* Update proximity sensor baseline */
			CapSense_UpdateSensorBaseline(PROXIMITY_SENSOR);
			
			/* Check if proximity sensor is active - thresholds are dynamically calculated during run-time
				proximityActive variable will have a non-zero value if Proximity was active */
			proximityActive = CapSense_CheckIsSensorActive(PROXIMITY_SENSOR);

			/* Process output if proximity sensor was active */
			if(proximityActive)
			{
				/* Code to process if proximity sensor is activated can be added here */
				
				/* Process the output data - PWM Duty - based on the proximity signal; */			
				Output_Process(CapSense_SensorSignal[PROXIMITY_SENSOR]);
			}

			/* Enter sleep if number of scans without any activity crossed threshold */
			if((sleepTimerCount >= ENTER_SLEEP_COUNTS))
			{
				System_Sleep();
			}

			
			/* Trigger the next Scan of proximity sensor */
			CapSense_ScanSensor(PROXIMITY_SENSOR);			
		}		
		
		
		/* Check for a falling edge of proximity sensor - prevState = ON & currState = OFF */
		if((proximityActivePrevState != 0) && (proximityActive == 0))
		{
			/* Process a one-time falling edge code here */
			
			/* Turn OFF PRSM output */
			PRSm_WriteCompare(LED_OFF_DUTY);
			
			/* Clear the calculated duty variable */
			calculatedDuty = LED_OFF_DUTY;
		}
		
		/* Save the current proximity state */
		proximityActivePrevState = proximityActive;
		
		/* Send data over UART if enabled */
		#ifdef	TX_ENABLE
			SendTxData();
		#endif	
    }
}



/******************************************************************************
* Function Name: Output_Init
*******************************************************************************
*
* Summary:
*  Output_Init() performs following functions:
*  1: Starts PRSm
*  2: Starts Software UART Tx component
*
* Parameters:
*  None.
*
* Return:
*  None.
*
******************************************************************************/
void Output_Init(void)
{	
	/* Set up WDT to generate the wakeup/timing ISR */
	/* Update the match register for generating a periodic WDT ISR. */
	/*Note: In order to do a periodic ISR using WDT, Match value needs to be
		updated every WDT ISR with the desired time value added on top of the
		existing match value */
	CySysWdtWriteMatch(WATCHDOG_TIMER_COUNT);
	
	/* Enable the WDT interrupt in SRSS INTR mask register */
	CySysWdtUnmaskInterrupt();
	
	/* Map the WatchDog_ISR vector to the WDT_ISR */
	WDT_ISR_StartEx(WatchDog_ISR);
	
	/* Start PRSm block */
	PRSm_Start();
	
	#ifdef TX_ENABLE
	/* Start software TX and assign a pin for the TX line */
	TX_StartEx(TX_PORT, TX_PIN);
	#endif
}

/******************************************************************************
* Function Name: System_Sleep
*******************************************************************************
*
* Summary:
*  System_Sleep() performs following functions:
*  1: Puts the various block used in the project to sleep.
*  2: Enters Device DeepSleep, WDT interrupt acts as the wakeup source
*  3: After device comes out of sleep, resumes the blocks put to sleep
*
* Parameters:
*  None.
*
* Return:
*  None.
*
******************************************************************************/
void System_Sleep(void)
{
	/* Put CapSense block to sleep */
	CapSense_Sleep();
	
	/* Put PRSm block to sleep*/
	PRSm_Sleep();
	
	/* Put device to sleep */
	CySysPmDeepSleep();
	
	/* Wakeup PRSm block once device is up */
	PRSm_Wakeup();
	
	/* Wakeup CapSense block */
	CapSense_Wakeup();
}

/******************************************************************************
* Function Name: Output_Process
*******************************************************************************
*
* Summary:
*  Output_Process() performs following functions:
*  1: Calculates the PRSm duty based on Proximity signal
*  2: Updates the duty to PRSm compare register
*
* Parameters:
*  uint8 signal - CapSense proximity signal value using which output is calculated
*
* Return:
*  None.
*
******************************************************************************/
void Output_Process(uint8 signal)
{
	/* Obtain the duty based on proximity sensor */
	calculatedDuty = PRSm_CalculateDuty(signal);	
	
	/* Write the calculated duty to the PRSm compare register */
	PRSm_WriteCompare(calculatedDuty);
}

/******************************************************************************
* Function Name: PRSm_CalculateDuty
*******************************************************************************
*
* Summary:
*  PRSm_CalculateDuty() calculates & returns the PRSm duty based on signal value 
*	passed.
*
* Parameters:
*  uint16 signal - Signal value with which the limits are compared & 
*					PRSm duty is calculated.
*
* Return:
*  uint32 pwmDuty - Calculated duty value.
*
******************************************************************************/
uint32 PRSm_CalculateDuty(uint16 signal)
{
	uint32 pwmDuty;
	
	/* Check if sensor signal value is above PROXIMITY_LOWER_LIMIT */
	if(CapSense_SensorSignal[PROXIMITY_SENSOR] > PROXIMITY_LOWER_LIMIT)
	{
		/* Check if sensor signal value is above PROXIMITY_UPPER_LIMIT */
		if(CapSense_SensorSignal[PROXIMITY_SENSOR] > PROXIMITY_UPPER_LIMIT)
		{
			/* PRSm duty = MAX Brightness */
			pwmDuty = PRSm_PWM_PERIOD_VALUE + 1;
		}
		else
		{
			/* Calculate the duty relative to signal's lower limit & upper limit */			
			pwmDuty = 1 + ((PRSm_PWM_PERIOD_VALUE * (signal - PROXIMITY_LOWER_LIMIT )) /(PROXIMITY_UPPER_LIMIT - PROXIMITY_LOWER_LIMIT));			
		}
		
		/* Clear sleep timer count - Disable the interrupt to prevent race condition because of interrupt access */		
		CySysWdtMaskInterrupt();
		sleepTimerCount = 0;
		CySysWdtUnmaskInterrupt();
	}
	else
	{
		/* If signal is below signal lower limit, turn OFF the PRSm (duty = 0) */
		pwmDuty = LED_OFF_DUTY;
	}
	
	/* return the calculated duty */
	return(pwmDuty);
}

#ifdef TX_ENABLE
/******************************************************************************
* Function Name: SendTxData
*******************************************************************************
*
* Summary:
*  SendTxData() sends the sensor data over UART Tx line
*
* Parameters:
*  None
*
* Return:
*  None
*
******************************************************************************/
void SendTxData(void)
{	
	/* Starting delimiter of a packet */
	TX_PutCRLF();
	
	/* Send debug data in MSB first fashion */
	TX_PutChar((uint8)(CapSense_rawFilterData1[PROXIMITY_SENSOR_INDEX]>>8));
	TX_PutChar((uint8)(CapSense_rawFilterData1[PROXIMITY_SENSOR_INDEX]));
	
	TX_PutChar((uint8)(CapSense_SensorBaseline[PROXIMITY_SENSOR_INDEX]>>8));
	TX_PutChar((uint8)(CapSense_SensorBaseline[PROXIMITY_SENSOR_INDEX]));
	
	TX_PutChar((uint8)(CapSense_SensorSignal[PROXIMITY_SENSOR_INDEX]>>8));
	TX_PutChar((uint8)(CapSense_SensorSignal[PROXIMITY_SENSOR_INDEX]));
	
	TX_PutChar((uint8)(calculatedDuty>>8));
	TX_PutChar((uint8)(calculatedDuty));
	
	/* End delimiter of a packet */
	TX_PutChar(0);
	TX_PutChar(0xFF);
	TX_PutChar(0xFF);
	
}
#endif

/******************************************************************************
* Function Name: WatchDog_ISR
*******************************************************************************
*
* Summary:
*  Watchdog Timer match ISR - Used for timing & sleep wakup source
*
* Parameters:
*  None.
*
* Return:
*  None.
*
******************************************************************************/
CY_ISR(WatchDog_ISR)
{
	/* Increment the sleepTimerCount variable & make sure it doesn't overflow beyond ENTER_SLEEP_COUNTS */
	if(sleepTimerCount < ENTER_SLEEP_COUNTS)
	{
		sleepTimerCount++;
	}
	
	/* Update match register to generate a periodic ISR  */
	CySysWdtWriteMatch((uint16)CySysWdtReadMatch() + WATCHDOG_TIMER_COUNT);	
	
	/* Clear WDT to prevent WDT reset */
	CySysWdtClearInterrupt();
}

/* [] END OF FILE */
