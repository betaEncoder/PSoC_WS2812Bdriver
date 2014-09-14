/*******************************************************************************
* File Name: CapSense_1_SMS.h
* Version 2.0
*
* Description:
*  This file provides the declarations of the wrapper between the CapSense CSD component 
*  and Auto Tuning library.
*
* Note:
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_CAPSENSE_CSD_SMS_CapSense_1_H)
#define CY_CAPSENSE_CSD_SMS_CapSense_1_H

#include "CapSense_1.h"
#include "CapSense_1_PVT.h"

#if(0u != CapSense_1_CSHL_API_GENERATE)
	#include "CapSense_1_CSHL.h"
#endif /* (0u != CapSense_1_CSHL_API_GENERATE) */

#define CapSense_1_CALIBRATION_RESOLUTION	(0x0FFF0000u)

#define CapSense_1_THRESHOLD_1                (220u)
#define CapSense_1_THRESHOLD_2                (237u)
#define CapSense_1_THRESHOLD_3                (245u)
#define CapSense_1_THRESHOLD_4                (250u)

#define CapSense_1_CALIBRATION_FREQ_KHZ		(3000u)
#define CapSense_1_CALIBRATION_MD  		    (4u)

#if (0u != CapSense_1_IS_M0S8PERI_BLOCK)
	#define CapSense_1_CALIBRATION_ASD		(CYDEV_BCLK__HFCLK__KHZ /\
													 CapSense_1_CALIBRATION_FREQ_KHZ)
#else
	#define CapSense_1_MIN_IMO_FREQ_KHZ		(6000u)
	#if(CYDEV_BCLK__HFCLK__KHZ < CapSense_1_MIN_IMO_FREQ_KHZ)
		#define CapSense_1_CALIBRATION_ASD			(1u)
	#else
		#define CapSense_1_CALIBRATION_ASD	(CYDEV_BCLK__HFCLK__KHZ / CapSense_1_CALIBRATION_MD /\
												 	 CapSense_1_CALIBRATION_FREQ_KHZ)
	#endif /* (CYDEV_BCLK__HFCLK__KHZ < CapSense_1_MIN_IMO_FREQ_KHZ) */
#endif /* (0u != CapSense_1_IS_M0S8PERI_BLOCK) */

#define CapSense_1_SENSITIVITY_MASK        	(0x0Fu)
#define CapSense_1_FLEXIBLE_THRESHOLDS_EN  	(1u)
#define CapSense_1_CAL_RAW_COUNT           	(3482u)

void CapSense_1_AutoTune(void);
void CapSense_1_UpdateThresholds(uint32 sensor);
void CapSense_1_SetSensitivity(uint32 sensor, uint32 value);
void CapSense_1_SetAnalogSwitchesSrcDirect(void);
uint16 CapSense_1_GetNoiseEnvelope(uint32 sensor);
void CapSense_1_NormalizeWidgets(uint32 widgetsNum, uint8 *dataPtr);
uint8 CapSense_1_GetSensitivityCoefficient(uint32 sensor);
uint16 CapSense_1_GetNormalizedDiffCountData(uint32 sensor);


/***************************************************
*    Obsolete Names (will be removed in future)
***************************************************/
#define baNoiseEnvelope			noiseEnvelopeTbl
#define baRunningDifference		runningDifferenceTbl
#define baSignRegister			signRegisterTbl
#define waSampleMin				sampleMinTbl
#define waSampleMax				sampleMaxTbl
#define waPreviousSample		previousSampleTbl
#define baK						kValueTbl   			
#define baSpeed					scanSpeedTbl			


#endif  /* (CY_CAPSENSE_CSD_SMS_CapSense_1_H) */

/* [] END OF FILE */
