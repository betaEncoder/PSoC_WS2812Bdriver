/*******************************************************************************
* File Name: CapSense_CSD_SMS.h
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
#if !defined(CY_CAPSENSE_CSD_SMS_CapSense_CSD_H)
#define CY_CAPSENSE_CSD_SMS_CapSense_CSD_H

#include "CapSense_CSD.h"
#include "CapSense_CSD_PVT.h"

#if(0u != CapSense_CSD_CSHL_API_GENERATE)
	#include "CapSense_CSD_CSHL.h"
#endif /* (0u != CapSense_CSD_CSHL_API_GENERATE) */

#define CapSense_CSD_CALIBRATION_RESOLUTION	(0x0FFF0000u)

#define CapSense_CSD_THRESHOLD_1                (220u)
#define CapSense_CSD_THRESHOLD_2                (237u)
#define CapSense_CSD_THRESHOLD_3                (245u)
#define CapSense_CSD_THRESHOLD_4                (250u)

#define CapSense_CSD_CALIBRATION_FREQ_KHZ		(3000u)
#define CapSense_CSD_CALIBRATION_MD  		    (2u)

#if (0u != CapSense_CSD_IS_M0S8PERI_BLOCK)
	#define CapSense_CSD_CALIBRATION_ASD		(CYDEV_BCLK__HFCLK__KHZ /\
													 CapSense_CSD_CALIBRATION_FREQ_KHZ)
#else
	#define CapSense_CSD_MIN_IMO_FREQ_KHZ		(6000u)
	#if(CYDEV_BCLK__HFCLK__KHZ < CapSense_CSD_MIN_IMO_FREQ_KHZ)
		#define CapSense_CSD_CALIBRATION_ASD			(1u)
	#else
		#define CapSense_CSD_CALIBRATION_ASD	(CYDEV_BCLK__HFCLK__KHZ / CapSense_CSD_CALIBRATION_MD /\
												 	 CapSense_CSD_CALIBRATION_FREQ_KHZ)
	#endif /* (CYDEV_BCLK__HFCLK__KHZ < CapSense_CSD_MIN_IMO_FREQ_KHZ) */
#endif /* (0u != CapSense_CSD_IS_M0S8PERI_BLOCK) */

#define CapSense_CSD_SENSITIVITY_MASK        	(0x0Fu)
#define CapSense_CSD_FLEXIBLE_THRESHOLDS_EN  	(0u)
#define CapSense_CSD_CAL_RAW_COUNT           	(3482u)

void CapSense_CSD_AutoTune(void);
void CapSense_CSD_UpdateThresholds(uint32 sensor);
void CapSense_CSD_SetSensitivity(uint32 sensor, uint32 value);
void CapSense_CSD_SetAnalogSwitchesSrcDirect(void);
uint16 CapSense_CSD_GetNoiseEnvelope(uint32 sensor);
void CapSense_CSD_NormalizeWidgets(uint32 widgetsNum, uint8 *dataPtr);
uint8 CapSense_CSD_GetSensitivityCoefficient(uint32 sensor);
uint16 CapSense_CSD_GetNormalizedDiffCountData(uint32 sensor);


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


#endif  /* (CY_CAPSENSE_CSD_SMS_CapSense_CSD_H) */

/* [] END OF FILE */
