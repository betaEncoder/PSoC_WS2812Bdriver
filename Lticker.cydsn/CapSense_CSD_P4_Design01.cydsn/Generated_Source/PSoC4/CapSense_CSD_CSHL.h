/*******************************************************************************
* File Name: CapSense_CSD_CSHL.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the High Level APIs
*  for CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_CSHL_CapSense_CSD_H)
#define CY_CAPSENSE_CSD_CSHL_CapSense_CSD_H

#include "CapSense_CSD.h"


/***************************************
*   Condition compilation parameters
***************************************/

#define CapSense_CSD_SIGNAL_SIZE                    (8u)
#define CapSense_CSD_AUTO_RESET                     (0u)
#define CapSense_CSD_RAW_FILTER_MASK                (8u)

/* Signal size definition */
#define CapSense_CSD_SIGNAL_SIZE_UINT8              (8u)
#define CapSense_CSD_SIGNAL_SIZE_UINT16             (16u)

/* Auto reset definition */
#define CapSense_CSD_AUTO_RESET_DISABLE             (0u)
#define CapSense_CSD_AUTO_RESET_ENABLE              (1u)

/* Mask for RAW and POS filters */
#define CapSense_CSD_MEDIAN_FILTER                  (0x01u)
#define CapSense_CSD_AVERAGING_FILTER               (0x02u)
#define CapSense_CSD_IIR2_FILTER                    (0x04u)
#define CapSense_CSD_IIR4_FILTER                    (0x08u)
#define CapSense_CSD_JITTER_FILTER                  (0x10u)
#define CapSense_CSD_IIR8_FILTER                    (0x20u)
#define CapSense_CSD_IIR16_FILTER                   (0x40u)
                                                        

/***************************************
*           API Constants
***************************************/

/* Widgets constants definition */
#define CapSense_CSD_LINEARSLIDER0__LS        (0u)

#define CapSense_CSD_TOTAL_DIPLEXED_SLIDERS_COUNT        (0u)
#define CapSense_CSD_TOTAL_LINEAR_SLIDERS_COUNT          (1u)
#define CapSense_CSD_TOTAL_RADIAL_SLIDERS_COUNT          (0u)
#define CapSense_CSD_TOTAL_TOUCH_PADS_COUNT              (0u)
#define CapSense_CSD_TOTAL_BUTTONS_COUNT                 (0u)
#define CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT          (0u)
#define CapSense_CSD_TOTAL_GENERICS_COUNT                (0u)

#define CapSense_CSD_POS_FILTERS_MASK                    (16u)
#define CapSense_CSD_LINEAR_SLIDERS_POS_FILTERS_MASK     (16u)
#define CapSense_CSD_RADIAL_SLIDERS_POS_FILTERS_MASK     (0u)
#define CapSense_CSD_TOUCH_PADS_POS_FILTERS_MASK         (0u)

#define CapSense_CSD_UNUSED_DEBOUNCE_COUNTER_INDEX       (0u)

#define CapSense_CSD_TOTAL_PROX_SENSORS_COUNT            (0u)

#define CapSense_CSD_END_OF_SLIDERS_INDEX                (0u)
#define CapSense_CSD_END_OF_TOUCH_PAD_INDEX              (0u)
#define CapSense_CSD_END_OF_BUTTONS_INDEX                (0u)
#define CapSense_CSD_END_OF_MATRIX_BUTTONS_INDEX         (0u)
#define CapSense_CSD_END_OF_WIDGETS_INDEX                (1u)



#define CapSense_CSD_TOTAL_SLIDERS_COUNT            ( CapSense_CSD_TOTAL_LINEAR_SLIDERS_COUNT + \
                                                          CapSense_CSD_TOTAL_RADIAL_SLIDERS_COUNT )
                                                          
#define CapSense_CSD_TOTAL_CENTROIDS_COUNT          ( CapSense_CSD_TOTAL_SLIDERS_COUNT + \
                                                         (CapSense_CSD_TOTAL_TOUCH_PADS_COUNT*2u) )

#define CapSense_CSD_TOTAL_WIDGET_COUNT             ( CapSense_CSD_TOTAL_LINEAR_SLIDERS_COUNT + \
                                                          CapSense_CSD_TOTAL_RADIAL_SLIDERS_COUNT + \
                                                          CapSense_CSD_TOTAL_TOUCH_PADS_COUNT + \
                                                          CapSense_CSD_TOTAL_BUTTONS_COUNT + \
                                                          CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT )
                                                           
#define CapSense_CSD_ANY_POS_FILTER                 ( CapSense_CSD_MEDIAN_FILTER | \
                                                          CapSense_CSD_AVERAGING_FILTER | \
                                                          CapSense_CSD_IIR2_FILTER | \
                                                          CapSense_CSD_IIR4_FILTER | \
                                                          CapSense_CSD_JITTER_FILTER )
                                                         
#define CapSense_CSD_IS_DIPLEX_SLIDER               ( CapSense_CSD_TOTAL_DIPLEXED_SLIDERS_COUNT > 0u)

#define CapSense_CSD_IS_NON_DIPLEX_SLIDER           ( (CapSense_CSD_TOTAL_LINEAR_SLIDERS_COUNT - \
                                                           CapSense_CSD_TOTAL_DIPLEXED_SLIDERS_COUNT) > 0u)
#define CapSense_CSD_ADD_SLIDER_TYPE                ((CapSense_CSD_TOTAL_RADIAL_SLIDERS_COUNT > 0u) ? \
                                                        ((CapSense_CSD_TOTAL_TOUCH_PADS_COUNT > 0u) || \
                                                         (CapSense_CSD_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) : 0u)

#define CapSense_CSD_TOTAL_PROX_SENSOR_COUNT		(CapSense_CSD_TOTAL_PROX_SENSORS_COUNT)

#define CapSense_CSD_WIDGETS_TBL_SIZE               ( CapSense_CSD_TOTAL_WIDGET_COUNT + \
                                                          CapSense_CSD_TOTAL_GENERICS_COUNT)
                                                          
#define CapSense_CSD_WIDGET_PARAM_TBL_SIZE		    (CapSense_CSD_TOTAL_BUTTONS_COUNT + \
                                                        CapSense_CSD_TOTAL_CENTROIDS_COUNT + \
                                                          CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT * 2u)                                                          
												  
#define CapSense_CSD_RESOLUTIONS_TBL_SIZE       (CapSense_CSD_WIDGET_PARAM_TBL_SIZE + \
													 CapSense_CSD_TOTAL_GENERICS_COUNT)

#define CapSense_CSD_THRESHOLD_TBL_SIZE			(CapSense_CSD_WIDGET_PARAM_TBL_SIZE)
#define CapSense_CSD_DEBOUNCE_CNT_TBL_SIZE		(CapSense_CSD_WIDGET_PARAM_TBL_SIZE)


#define CapSense_CSD_NOT_WIDGET		                (0xFFFFFFFFu)
														  
/*Types of centroids */
#define CapSense_CSD_TYPE_RADIAL_SLIDER             (0x01u)
#define CapSense_CSD_TYPE_LINEAR_SLIDER             (0x02u)
#define CapSense_CSD_TYPE_GENERIC                   (0xFFu)

/* Defines if sensors or widgets are active */
#define CapSense_CSD_SENSOR_IS_ACTIVE               (0x01u)
#define CapSense_CSD_SENSOR_1_IS_ACTIVE     		(0x01u)
#define CapSense_CSD_SENSOR_2_IS_ACTIVE     		(0x02u)
#define CapSense_CSD_WIDGET_IS_ACTIVE               (0x01u)

/* Defines diplex type of Slider */
#define CapSense_CSD_IS_DIPLEX                      (0x80u)

/* Defines fingers positions on Slider  */
#define CapSense_CSD_POS_PREV                       (0u)
#define CapSense_CSD_POS                            (1u)
#define CapSense_CSD_POS_NEXT                       (2u)
#define CapSense_CSD_CENTROID_ROUND_VALUE           (0x7F00u)
#define CapSense_CSD_MAXIMUM_CENTROID               (0xFFu)

#define CapSense_CSD_NEGATIVE_NOISE_THRESHOLD       (20u)
#define CapSense_CSD_LOW_BASELINE_RESET             (5u)


/***************************************
*        Function Prototypes
***************************************/

void CapSense_CSD_InitializeSensorBaseline(uint32 sensor);
void CapSense_CSD_InitializeAllBaselines(void);
void CapSense_CSD_InitializeEnabledBaselines(void);
void CapSense_CSD_UpdateSensorBaseline(uint32 sensor);
void CapSense_CSD_UpdateEnabledBaselines(void);
uint16 CapSense_CSD_GetBaselineData(uint32 sensor);
void CapSense_CSD_SetBaselineData(uint32 sensor, uint16 data);
void CapSense_CSD_BaseInit(uint32 sensor);

#if (CapSense_CSD_IS_DIPLEX_SLIDER)
	uint8 CapSense_CSD_FindMaximum(uint8 offset, uint8 count, uint8 fingerThreshold, const uint8 *diplex);
#else 
	uint8 CapSense_CSD_FindMaximum(uint8 offset, uint8 count, uint8 fingerThreshold);
#endif /* (CapSense_CSD_IS_DIPLEX_SLIDER) */

uint8 CapSense_CSD_CalcCentroid(uint8 maximum, uint8 offset, \
                                    uint8 count, uint16 resolution, uint8 noiseThreshold);

uint8 CapSense_CSD_GetFingerThreshold(uint32 widget);
uint8 CapSense_CSD_GetNoiseThreshold(uint32 widget);
uint8 CapSense_CSD_GetFingerHysteresis(uint32 widget);
uint8 CapSense_CSD_GetNegativeNoiseThreshold(uint32 widget);

#if(CapSense_CSD_TUNING_METHOD != CapSense_CSD__TUNING_NONE)
	void CapSense_CSD_SetFingerThreshold(uint32 widget, uint8 value);
	void CapSense_CSD_SetNoiseThreshold(uint32 widget, uint8 value);
	void CapSense_CSD_SetFingerHysteresis(uint32 widget, uint8 value);
	void CapSense_CSD_SetNegativeNoiseThreshold(uint32 widget, uint8 value);
	void CapSense_CSD_SetDebounce(uint32 widget, uint8 value);
	void CapSense_CSD_SetLowBaselineReset(uint32 sensor, uint8 value);
#endif /* (CapSense_CSD_TUNING_METHOD != CapSense_CSD__TUNING_NONE) */

uint8 CapSense_CSD_GetDiffCountData(uint32 sensor);
void CapSense_CSD_SetDiffCountData(uint32 sensor, uint8 value);								
							
uint32 CapSense_CSD_CheckIsSensorActive(uint32 sensor);
uint32 CapSense_CSD_CheckIsWidgetActive(uint32 widget);
uint32 CapSense_CSD_CheckIsAnyWidgetActive(void);
void CapSense_CSD_EnableWidget(uint32 widget);
void CapSense_CSD_DisableWidget(uint32 widget);


#if (CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT)
    uint32 CapSense_CSD_GetMatrixButtonPos(uint32 widget, uint8* pos);
#endif /* (CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT) */

#if((CapSense_CSD_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (CapSense_CSD_TOTAL_LINEAR_SLIDERS_COUNT > 0u))
    uint16 CapSense_CSD_GetCentroidPos(uint32 widget);
#endif /* ((CapSense_CSD_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (CapSense_CSD_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) */
#if((CapSense_CSD_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (CapSense_CSD_TOTAL_LINEAR_SLIDERS_COUNT > 0u))
    uint16 CapSense_CSD_GetRadialCentroidPos(uint32 widget);
#endif /* #if((CapSense_CSD_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (CapSense_CSD_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) */
#if (CapSense_CSD_TOTAL_TOUCH_PADS_COUNT)
    uint32 CapSense_CSD_GetTouchCentroidPos(uint32 widget, uint16* pos);
#endif /* (CapSense_CSD_TOTAL_TOUCH_PADS_COUNT) */

uint32 CapSense_CSD_GetWidgetNumber(uint32 sensor);
uint8 CapSense_CSD_GetLowBaselineReset(uint32 sensor);
uint8 CapSense_CSD_GetDebounce(uint32 widget);

/***************************************
*        Obsolete Names
***************************************/
#define CapSense_CSD_SensorRaw				CapSense_CSD_sensorRaw
#define CapSense_CSD_SensorEnableMask		CapSense_CSD_sensorEnableMask
#define CapSense_CSD_SensorBaseline			CapSense_CSD_sensorBaseline
#define CapSense_CSD_SensorBaselineLow		CapSense_CSD_sensorBaselineLow
#define CapSense_CSD_SensorSignal			CapSense_CSD_sensorSignal
#define CapSense_CSD_SensorOnMask			CapSense_CSD_sensorOnMask
#define CapSense_CSD_LowBaselineResetCnt	CapSense_CSD_lowBaselineResetCnt

#endif /* CY_CAPSENSE_CSD_CSHL_CapSense_CSD_H */

/* [] END OF FILE */
