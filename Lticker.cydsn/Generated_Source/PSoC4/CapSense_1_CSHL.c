/*******************************************************************************
* File Name: CapSense_1_CSHL.c
* Version 2.0
*
* Description:
*  This file provides the source code to the High Level APIs for the CapSesne
*  CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CapSense_1_CSHL.h"
#include "CapSense_1_PVT.h"

/* SmartSense functions */
#if (CapSense_1_TUNING_METHOD == CapSense_1__TUNING_AUTO)
    extern void CapSense_1_UpdateThresholds(uint32 sensor);
#endif /* (CapSense_1_TUNING_METHOD == CapSense_1__TUNING_AUTO) */

/* Median filter function prototype */
#if ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_MEDIAN_FILTER)) || \
      (0u != (CapSense_1_POS_FILTERS_MASK & CapSense_1_MEDIAN_FILTER)))
    uint16 CapSense_1_MedianFilter(uint16 x1, uint16 x2, uint16 x3);
#endif /* CapSense_1_RAW_FILTER_MASK && CapSense_1_POS_FILTERS_MASK */

/* Averaging filter function prototype */
#if ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_AVERAGING_FILTER)) || \
      (0u != (CapSense_1_POS_FILTERS_MASK & CapSense_1_AVERAGING_FILTER)) )
    uint16 CapSense_1_AveragingFilter(uint16 x1, uint16 x2, uint16 x3);
#endif /* CapSense_1_RAW_FILTER_MASK && CapSense_1_POS_FILTERS_MASK */

/* IIR2Filter(1/2prev + 1/2cur) filter function prototype */
#if ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR2_FILTER)) || \
      (0u != (CapSense_1_POS_FILTERS_MASK & CapSense_1_IIR2_FILTER)) )
    uint16 CapSense_1_IIR2Filter(uint16 x1, uint16 x2);
#endif /* CapSense_1_RAW_FILTER_MASK && CapSense_1_POS_FILTERS_MASK */

/* IIR4Filter(3/4prev + 1/4cur) filter function prototype */
#if ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR4_FILTER)) || \
      (0u != (CapSense_1_POS_FILTERS_MASK & CapSense_1_IIR4_FILTER)) )
    uint16 CapSense_1_IIR4Filter(uint16 x1, uint16 x2);
#endif /* CapSense_1_RAW_FILTER_MASK && CapSense_1_POS_FILTERS_MASK */

/* IIR8Filter(7/8prev + 1/8cur) filter function prototype - RawCounts only */
#if (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR8_FILTER))
    uint16 CapSense_1_IIR8Filter(uint16 x1, uint16 x2);
#endif /* CapSense_1_RAW_FILTER_MASK */

/* IIR16Filter(15/16prev + 1/16cur) filter function prototype - RawCounts only */
#if (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR16_FILTER))
    uint16 CapSense_1_IIR16Filter(uint16 x1, uint16 x2);
#endif /* CapSense_1_RAW_FILTER_MASK */

/* JitterFilter filter function prototype */
#if ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_JITTER_FILTER)) || \
      (0u != (CapSense_1_POS_FILTERS_MASK & CapSense_1_JITTER_FILTER)) )
    uint16 CapSense_1_JitterFilter(uint16 x1, uint16 x2);
#endif /* CapSense_1_RAW_FILTER_MASK && CapSense_1_POS_FILTERS_MASK */

/* Storage of filters data */
#if ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_MEDIAN_FILTER)) || \
      (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_AVERAGING_FILTER)) )

    uint16 CapSense_1_rawFilterData1[CapSense_1_TOTAL_SENSOR_COUNT];
    uint16 CapSense_1_rawFilterData2[CapSense_1_TOTAL_SENSOR_COUNT];

#elif ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR2_FILTER))   || \
        (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR4_FILTER))   || \
        (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_JITTER_FILTER)) || \
        (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR8_FILTER))   || \
        (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR16_FILTER)) )
        
    uint16 CapSense_1_rawFilterData1[CapSense_1_TOTAL_SENSOR_COUNT];
#endif  /* ( (CapSense_1_RAW_FILTER_MASK & CapSense_1_MEDIAN_FILTER) || \
        *    (CapSense_1_RAW_FILTER_MASK & CapSense_1_AVERAGING_FILTER) )
        */

extern uint16 CapSense_1_sensorRaw[CapSense_1_TOTAL_SENSOR_COUNT];
extern uint8 CapSense_1_sensorEnableMask[CapSense_1_TOTAL_SENSOR_MASK];
extern const uint8 CapSense_1_widgetNumber[CapSense_1_TOTAL_SENSOR_COUNT];

#if (CapSense_1_TUNING_METHOD != CapSense_1__TUNING_NONE)
	extern uint32 CapSense_1_widgetResolution[CapSense_1_RESOLUTIONS_TBL_SIZE];	
#endif /* (CapSense_1_TUNING_METHOD != CapSense_1__TUNING_NONE) */

uint16 CapSense_1_sensorBaseline[CapSense_1_TOTAL_SENSOR_COUNT] = {0u};
uint8 CapSense_1_sensorBaselineLow[CapSense_1_TOTAL_SENSOR_COUNT] = {0u};
uint8 CapSense_1_sensorSignal[CapSense_1_TOTAL_SENSOR_COUNT] = {0u};
uint8 CapSense_1_sensorOnMask[CapSense_1_TOTAL_SENSOR_MASK] = {0u};

uint8 CapSense_1_lowBaselineResetCnt[CapSense_1_TOTAL_SENSOR_COUNT];
uint8 CapSense_1_lowBaselineReset[CapSense_1_TOTAL_IMMUNITY_NUM] = {
    30u, 30u, 30u, 30u, 30u, 
};



#if (CapSense_1_TUNING_METHOD == CapSense_1__TUNING_AUTO)
	extern CapSense_1_CONFIG_TYPE_P4_v2_0 CapSense_1_config;
#endif  /* (CapSense_1_TUNING_METHOD == CapSense_1__TUNING_AUTO) */

/* Generated by Customizer */
uint8 CapSense_1_fingerThreshold[] = {
    100u, 
};

uint8 CapSense_1_noiseThreshold[CapSense_1_THRESHOLD_TBL_SIZE];

uint8 CapSense_1_negativeNoiseThreshold[CapSense_1_THRESHOLD_TBL_SIZE];

uint8 CapSense_1_hysteresis[CapSense_1_WIDGET_PARAM_TBL_SIZE];

uint8 CapSense_1_debounce[] = {
    1u, 
};

static uint8 CapSense_1_debounceCounter[] = {
    0u, 
};

const uint8 CapSense_1_rawDataIndex[] = {
    0u, /* LinearSlider0__LS */
};

const uint8 CapSense_1_numberOfSensors[] = {
    5u, /* LinearSlider0__LS */
};

static const uint16 CapSense_1_centroidMult[] = {
    4096u, 
};

static const uint8 CapSense_1_posFiltersMask[] = {
    0x8u, 
};

static uint8 CapSense_1_posFiltersData[] = {
    1u, 0u, 0u, 
};




/*******************************************************************************
* Function Name: CapSense_1_BaseInit
********************************************************************************
*
* Summary:
*  Loads the CapSense_1_sensorBaseline[sensor] array element with an 
*  initial value which is equal to the raw count value. 
*  Resets to zero CapSense_1_sensorBaselineLow[sensor] and 
*  CapSense_1_sensorSignal[sensor] array element.
*  Loads the CapSense_1_debounceCounter[sensor] array element with the initial 
*  value equal CapSense_1_debounce[].
*  Loads the CapSense_1_rawFilterData2[sensor] and 
*  CapSense_1_rawFilterData2[sensor] array element with an 
*  initial value which is equal to the raw count value if the raw data filter is enabled.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  CapSense_1_sensorBaseline[]    - used to store the baseline value.
*  CapSense_1_sensorBaselineLow[] - used to store the fraction byte of 
*  the baseline value.
*  CapSense_1_sensorSignal[]      - used to store a difference between 
*  the current value of raw data and the previous value of the baseline.
*  CapSense_1_debounceCounter[]   - used to store the current debounce 
*  counter of the sensor. The widgets which have this parameter are buttons, matrix 
*  buttons, proximity, and guard. All other widgets don't have the  debounce parameter
*  and use the last element of this array with value 0 (it means no debounce).
*  CapSense_1_rawFilterData1[]    - used to store a previous sample of 
*  any enabled raw data filter.
*  CapSense_1_rawFilterData2[]    - used to store before a previous sample
*  of the enabled raw data filter. Required only for median or average filters.
*
* Side Effects:
*  None
* 
*******************************************************************************/
void CapSense_1_BaseInit(uint32 sensor)
{
    #if ((CapSense_1_TOTAL_BUTTONS_COUNT) || (CapSense_1_TOTAL_MATRIX_BUTTONS_COUNT) || \
         (CapSense_1_TOTAL_GENERICS_COUNT))
        uint8 widget = CapSense_1_widgetNumber[sensor];
    #endif /* ((CapSense_1_TOTAL_MATRIX_BUTTONS_COUNT) || (CapSense_1_TOTAL_MATRIX_BUTTONS_COUNT)) */
    
    #if (CapSense_1_TOTAL_MATRIX_BUTTONS_COUNT)
        uint8 debounceIndex;
    #endif  /* (CapSense_1_TOTAL_MATRIX_BUTTONS_COUNT) */
    
    #if (CapSense_1_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        if(widget < CapSense_1_END_OF_WIDGETS_INDEX)
        {
    #endif  /* CapSense_1_TOTAL_GENERICS_COUNT */
    
    /* Initialize Baseline */
    CapSense_1_sensorBaseline[sensor] = CapSense_1_sensorRaw[sensor];
    CapSense_1_sensorBaselineLow[sensor] = 0u;
    CapSense_1_sensorSignal[sensor] = 0u;
        

    
    #if ((0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_MEDIAN_FILTER)) ||\
         (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_AVERAGING_FILTER)))

        CapSense_1_rawFilterData1[sensor] = CapSense_1_sensorRaw[sensor];
        CapSense_1_rawFilterData2[sensor] = CapSense_1_sensorRaw[sensor];
    
    #elif ((CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR2_FILTER) ||\
           (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR4_FILTER) ||\
           (CapSense_1_RAW_FILTER_MASK & CapSense_1_JITTER_FILTER) ||\
           (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR8_FILTER) ||\
           (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR16_FILTER))
            
        CapSense_1_rawFilterData1[sensor] = CapSense_1_sensorRaw[sensor];
    
    #else
        /* No Raw filters */
    #endif  /* ((CapSense_1_RAW_FILTER_MASK & CapSense_1_MEDIAN_FILTER) || \
            *   (CapSense_1_RAW_FILTER_MASK & CapSense_1_AVERAGING_FILTER))
            */
    
    #if (CapSense_1_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        }
    #endif  /* CapSense_1_TOTAL_GENERICS_COUNT */
}


/*******************************************************************************
* Function Name: CapSense_1_InitializeSensorBaseline
********************************************************************************
*
* Summary:
*  Loads the CapSense_1_sensorBaseline[sensor] array element with an 
*  initial value by scanning the selected sensor (one channel design) or a pair 
*  of sensors (two channels designs). The raw count value is copied into the 
*  baseline array for each sensor. The raw data filters are initialized if 
*  enabled.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  None
*
* Side Effects:
*  None
* 
*******************************************************************************/
void CapSense_1_InitializeSensorBaseline(uint32 sensor)
{
    /* Scan sensor */
    CapSense_1_ScanSensor(sensor);
    while(CapSense_1_IsBusy() != 0u)
    {
        /* Wait while sensor is busy */
    }
    
    /* Initialize Baseline, Signal and debounce counters */       
    CapSense_1_BaseInit(sensor);
}


/*******************************************************************************
* Function Name: CapSense_1_InitializeAllBaselines
********************************************************************************
*
* Summary:
*  Uses the CapSense_1_InitializeSensorBaseline function to load the 
*  CapSense_1_sensorBaseline[] array with an initial values by scanning 
*  all the sensors. The raw count values are copied into the baseline array for 
*  all the sensors. The raw data filters are initialized if enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None
*
* Side Effects:
*  None
* 
*******************************************************************************/
void CapSense_1_InitializeAllBaselines(void)
{
    uint32 i;
    
	for(i = 0u; i < CapSense_1_TOTAL_SCANSLOT_COUNT; i++)
	{
    	CapSense_1_InitializeSensorBaseline(i);
	}
}


/*******************************************************************************
* Function Name: CapSense_1_InitializeEnabledBaselines
********************************************************************************
*
* Summary:
*  Scans all the enabled widgets and the raw count values are copied into the 
*  baseline array for all the sensors enabled in the scanning process. The baselines 
*  are initialized with zero values for sensors disabled from the scanning process. 
*  The raw data filters are initialized if enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense_1_sensorRaw[] - used to store the sensors raw data.
*  CapSense_1_sensorEnableMask[ ] - used to store bit masks of the enabled sensors.
*
* Side Effects:
*  None
* 
*******************************************************************************/
void CapSense_1_InitializeEnabledBaselines(void)
{
    uint32 i;
    uint32 isSensorEnabled;
    
    CapSense_1_ScanEnabledWidgets();
    while(CapSense_1_IsBusy() != 0u)
    {
        /* Wait while sensor is busy */
    }
    
    for(i = 0u; i < CapSense_1_TOTAL_SENSOR_COUNT; i++)
    {
        isSensorEnabled = CapSense_1_GetBitValue(CapSense_1_sensorEnableMask, i);
        
        /* Clear raw data if sensor is disabled from scanning process */
        if(isSensorEnabled != 0u)
        {
            /* Initialize baselines */
            CapSense_1_BaseInit(i);
        }
    }
}  


/*******************************************************************************
* Function Name: CapSense_1_UpdateBaselineNoThreshold
********************************************************************************
*
* Summary:
*  Updates the CapSense_1_sensorBaseline[sensor] array element using the 
*  LP filter with k = 256. The signal calculates the difference of count by 
*  subtracting the previous baseline from the current raw count value and stores
*  it in CapSense_1_sensorSignal[sensor]. 
*  If the auto reset option is enabled, the baseline updated regards the noise threshold. 
*  If the auto reset option is disabled, the baseline stops updating; baseline is loaded 
*  with a raw count value if a signal is greater than zero and if signal is less 
*  than noise threshold.
*  Raw data filters are applied to the values if enabled before baseline 
*  calculation.
*
*  This API does not update the thresholds in the Smartsense Mode.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  CapSense_1_widgetNumber[]  - stores widget numbers.
*  CapSense_1_sensorBaseline[]    - used to store baseline value.
*  CapSense_1_sensorBaselineLow[] - used to store fraction byte of 
*  baseline value.
*  CapSense_1_sensorSignal[]      - used to store difference between 
*  current value of raw data and previous value of baseline.
*  CapSense_1_rawFilterData1[]    - used to store previous sample of 
*  any enabled raw data filter.
*  CapSense_1_rawFilterData2[]    - used to store before previous sample
*  of enabled raw data filter. Only required for median or average filters.
* 
* Side Effects:
*  None
* 
*******************************************************************************/
void CapSense_1_UpdateBaselineNoThreshold(uint32 sensor)
{
    uint32 calc;
	uint32 sign;
    uint16 tempRaw;
    uint16 filteredRawData;
    uint8 widget = CapSense_1_widgetNumber[sensor];
    uint8 noiseThreshold = CapSense_1_noiseThreshold[widget];
    
    #if (CapSense_1_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        if(widget < CapSense_1_END_OF_WIDGETS_INDEX)
        {
    #endif  /* CapSense_1_TOTAL_GENERICS_COUNT */
    
    filteredRawData = CapSense_1_sensorRaw[sensor];
    
    #if (CapSense_1_RAW_FILTER_MASK & CapSense_1_MEDIAN_FILTER)
        tempRaw = filteredRawData;
        filteredRawData = CapSense_1_MedianFilter(filteredRawData, CapSense_1_rawFilterData1[sensor], 
                                                        CapSense_1_rawFilterData2[sensor]);
        CapSense_1_rawFilterData2[sensor] = CapSense_1_rawFilterData1[sensor];
        CapSense_1_rawFilterData1[sensor] = tempRaw;
        
    #elif (CapSense_1_RAW_FILTER_MASK & CapSense_1_AVERAGING_FILTER)
        tempRaw = filteredRawData;
        filteredRawData = CapSense_1_AveragingFilter(filteredRawData, CapSense_1_rawFilterData1[sensor],
                                                           CapSense_1_rawFilterData2[sensor]);
        CapSense_1_rawFilterData2[sensor] = CapSense_1_rawFilterData1[sensor];
        CapSense_1_rawFilterData1[sensor] = tempRaw;
        
    #elif (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR2_FILTER)
        filteredRawData = CapSense_1_IIR2Filter(filteredRawData, CapSense_1_rawFilterData1[sensor]);
        CapSense_1_rawFilterData1[sensor] = filteredRawData;
        
    #elif (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR4_FILTER)
        filteredRawData = CapSense_1_IIR4Filter(filteredRawData, CapSense_1_rawFilterData1[sensor]);
        CapSense_1_rawFilterData1[sensor] = filteredRawData;
            
    #elif (CapSense_1_RAW_FILTER_MASK & CapSense_1_JITTER_FILTER)
        filteredRawData = CapSense_1_JitterFilter(filteredRawData, CapSense_1_rawFilterData1[sensor]);
        CapSense_1_rawFilterData1[sensor] = filteredRawData;
        
    #elif (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR8_FILTER)
        filteredRawData = CapSense_1_IIR8Filter(filteredRawData, CapSense_1_rawFilterData1[sensor]);
        CapSense_1_rawFilterData1[sensor] = filteredRawData;
        
    #elif (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR16_FILTER)
        filteredRawData = CapSense_1_IIR16Filter(filteredRawData, CapSense_1_rawFilterData1[sensor]);
        CapSense_1_rawFilterData1[sensor] = filteredRawData;
        
    #else
        /* No Raw filters */
    #endif  /* (CapSense_1_RAW_FILTER_MASK & CapSense_1_MEDIAN_FILTER) */

	#if (CapSense_1_TUNING_METHOD == CapSense_1__TUNING_AUTO)
	    MeasureNoiseEnvelope_P4_v2_0(&CapSense_1_config, (uint8)sensor, CapSense_1_sensorRaw);
	#endif /* (CapSense_1_TUNING_METHOD == CapSense_1__TUNING_AUTO) */

    /* Baseline calculation */
    /* Calculate difference RawData[cur] - Baseline[prev] */
    if(filteredRawData >= CapSense_1_sensorBaseline[sensor])
    {
		CapSense_1_lowBaselineResetCnt[sensor] = 0u;	
        tempRaw = filteredRawData - CapSense_1_sensorBaseline[sensor];
        sign = 1u;    /* Positive difference - Calculate the Signal */
    }
    else
    {
        tempRaw = CapSense_1_sensorBaseline[sensor] - filteredRawData;
        sign = 0u;    /* Negative difference - Do NOT calculate the Signal */
    }

	#if (CapSense_1_TUNING_METHOD != CapSense_1__TUNING_NONE)
	if((sign == 0u) && (tempRaw > (uint16) CapSense_1_negativeNoiseThreshold[widget]))
	#else
	if((sign == 0u) && (tempRaw > (uint16) CapSense_1_NEGATIVE_NOISE_THRESHOLD))
	#endif /* (CapSense_1_TUNING_METHOD != CapSense_1__TUNING_NONE) */ 
    {
        if(CapSense_1_lowBaselineResetCnt[sensor] >= CapSense_1_LOW_BASELINE_RESET)
        {
            CapSense_1_BaseInit(sensor);
            CapSense_1_lowBaselineResetCnt[sensor] = 0u;
        }
        else
        {
            CapSense_1_lowBaselineResetCnt[sensor]++;
        }
    }
    else
    {
        #if (CapSense_1_AUTO_RESET == CapSense_1_AUTO_RESET_DISABLE)
		#if (CapSense_1_TUNING_METHOD != CapSense_1__TUNING_NONE)			
			/* Update Baseline if lower than noiseThreshold */
			if ( (tempRaw <= noiseThreshold) || 
			 ((tempRaw < (uint16) CapSense_1_negativeNoiseThreshold[widget])
			   && (sign == 0u)))
			{
		#else
			/* Update Baseline if lower than noiseThreshold */
			if ( (tempRaw <= noiseThreshold) || 
				 ((tempRaw < (uint16) CapSense_1_NEGATIVE_NOISE_THRESHOLD)
				   && (sign == 0u)))
			{
		#endif /* (CapSense_1_TUNING_METHOD != CapSense_1__TUNING_NONE) */ 
        #endif /* (CapSense_1_AUTO_RESET == CapSense_1_AUTO_RESET_DISABLE) */
                /* Make full Baseline 23 bits */
                calc = (uint32) CapSense_1_sensorBaseline[sensor] << 8u;
                calc |= (uint32) CapSense_1_sensorBaselineLow[sensor];

                /* Add Raw Data to Baseline */
                calc += filteredRawData;

                /* Sub the high Baseline */
                calc -= CapSense_1_sensorBaseline[sensor];

                /* Put Baseline and BaselineLow */
                CapSense_1_sensorBaseline[sensor] = ((uint16) (calc >> 8u));
                CapSense_1_sensorBaselineLow[sensor] = ((uint8) calc);

                CapSense_1_lowBaselineResetCnt[sensor] = 0u;
        #if (CapSense_1_AUTO_RESET == CapSense_1_AUTO_RESET_DISABLE)
            }
        #endif /* (CapSense_1_AUTO_RESET == CapSense_1_AUTO_RESET_DISABLE) */
    }

    /* Calculate Signal if positive difference > noiseThreshold */
    if((tempRaw > (uint16) noiseThreshold) && (sign != 0u))
    {
        #if (CapSense_1_SIGNAL_SIZE == CapSense_1_SIGNAL_SIZE_UINT8)
            /* Over flow defence for uint8 */
            if (tempRaw > 0xFFu)
            {
                CapSense_1_sensorSignal[sensor] = 0xFFu;
            }    
            else 
            {
                CapSense_1_sensorSignal[sensor] = ((uint8) tempRaw);
            }
        #else
            CapSense_1_sensorSignal[sensor] = ((uint16) tempRaw);
        #endif  /* (CapSense_1_SIGNAL_SIZE == CapSense_1_SIGNAL_SIZE_UINT8) */
    }
    else
    {
        /* Signal is zero */
        CapSense_1_sensorSignal[sensor] = 0u;
    }

    #if (CapSense_1_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        }
    #endif  /* CapSense_1_TOTAL_GENERICS_COUNT */
}


/*******************************************************************************
* Function Name: CapSense_1_UpdateSensorBaseline
********************************************************************************
*
* Summary:
*  Updates the CapSense_1_sensorBaseline[sensor] array element using the 
*  LP filter with k = 256. The signal calculates the difference of count by 
*  subtracting the previous baseline from the current raw count value and stores
*  it in CapSense_1_sensorSignal[sensor]. 
*  If the auto reset option is enabled, the baseline updated regards the noise threshold. 
*  If the auto reset option is disabled, the baseline stops updating. 
*  Baseline is loaded with raw count value if a signal is greater than zero and  
*  if signal is less than noise threshold.
*  Raw data filters are applied to the values if enabled before baseline 
*  calculation.
*  This API updates the thresholds in the Smartsense Mode.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  CapSense_1_widgetNumber[]  - stores widget numbers.
* 
* Side Effects:
*  None
* 
*******************************************************************************/
 void CapSense_1_UpdateSensorBaseline(uint32 sensor)
{
    #if (CapSense_1_TOTAL_GENERICS_COUNT)
		uint32 widget;
		
		widget = CapSense_1_widgetNumber[sensor];
	
        /* Exclude generic widget */
        if(widget < CapSense_1_END_OF_WIDGETS_INDEX)
        {
    #endif  /* CapSense_1_TOTAL_GENERICS_COUNT */

    #if (CapSense_1_TUNING_METHOD == CapSense_1__TUNING_AUTO)
    	CapSense_1_UpdateThresholds(sensor);
    #endif /* (CapSense_1_TUNING_METHOD == CapSense_1__TUNING_AUTO) */

    CapSense_1_UpdateBaselineNoThreshold(sensor);
    
    #if (CapSense_1_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        }
    #endif  /* CapSense_1_TOTAL_GENERICS_COUNT */
}


/*******************************************************************************
* Function Name: CapSense_1_UpdateEnabledBaselines
********************************************************************************
*
* Summary:
*  Checks CapSense_1_sensorEnableMask[] array and calls the 
*  CapSense_1_UpdateSensorBaseline function to update the baselines 
*  for the enabled sensors.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense_1_sensorEnableMask[] - used to store the sensor scanning 
*  state.
*  CapSense_1_sensorEnableMask[0] contains the masked bits for sensors 
*   0 through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  CapSense_1_sensorEnableMask[1] contains the masked bits for 
*  sensors 8 through 15 (if needed), and so on.
*  0 - sensor doesn't scan by CapSense_1_ScanEnabledWidgets().
*  1 - sensor scans by CapSense_1_ScanEnabledWidgets().
* 
* Side Effects:
*  None
* 
*******************************************************************************/
 void CapSense_1_UpdateEnabledBaselines(void)
{
    uint32 i;
    uint32 isSensorEnabled;
    
    for(i = 0u; i < CapSense_1_TOTAL_SENSOR_COUNT; i++)
    {
        isSensorEnabled = CapSense_1_GetBitValue(CapSense_1_sensorEnableMask, i);
        
        if(0u != isSensorEnabled)
        {
            CapSense_1_UpdateSensorBaseline(i);
        }
    }
}


/*******************************************************************************
* Function Name: CapSense_1_GetBaselineData
********************************************************************************
*
* Summary:
*  This function reads the sensor baseline from the component.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  This API returns the baseline value of the sensor indicated by an argument.
*
* Global Variables:
*  CapSense_1_sensorBaseline[] - the array with an initial values by scanning
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint16 CapSense_1_GetBaselineData(uint32 sensor)
{
	return (CapSense_1_sensorBaseline[sensor]);
}


/*******************************************************************************
* Function Name: CapSense_1_SetBaselineData
********************************************************************************
*
* Summary:
*  This API writes the data value passed as an argument to the sensor baseline array.
*
* Parameters:
*  sensor:  Sensor number.
*  data:    Sensor baseline.
*
* Return:
*  None.
*
* Global Variables:
*  CapSense_1_sensorBaseline[] - the array with initial values by scanning
* 
* Side Effects:
*  None
*
*******************************************************************************/
void CapSense_1_SetBaselineData(uint32 sensor, uint16 data)
{
	CapSense_1_sensorBaseline[sensor] = data;
}


/*******************************************************************************
* Function Name: CapSense_1_GetDiffCountData
********************************************************************************
*
* Summary:
*  This function returns the Sensor Signal from the component.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  This API returns the difference count value of the sensor indicated by the 
*  argument. 
*
* Global Variables:
*  CapSense_1_sensorSignal[] - the array with difference counts for sensors
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint8 CapSense_1_GetDiffCountData(uint32 sensor)
{
	return (CapSense_1_sensorSignal[sensor]);
}


/*******************************************************************************
* Function Name: CapSense_1_SetDiffCountData
********************************************************************************
*
* Summary:
*  This API writes the data value passed as an argument to the sensor signal array.
*
* Parameters:
*  sensor:  Sensor number.
*  value:   Sensor signal.
*
* Return:
*  None. 
*
* Global Variables:
*  CapSense_1_sensorSignal[] - the array with difference counts for sensors
* 
* Side Effects:
*  None
*
*******************************************************************************/
void CapSense_1_SetDiffCountData(uint32 sensor, uint8 value)
{
    CapSense_1_sensorSignal[sensor] = value;
}


/*******************************************************************************
* Function Name: CapSense_1_GetFingerThreshold
********************************************************************************
*
* Summary:
*  This function reads the finger threshold from the component.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  This API returns the finger threshold of the widget indicated by the argument. 
*
* Global Variables:
*  CapSense_1_fingerThreshold[] - This array contains the level of signal 
*  for each widget that is determined if a finger is present on the widget.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint8 CapSense_1_GetFingerThreshold(uint32 widget)
{
	return(CapSense_1_fingerThreshold[widget]);
}


/*******************************************************************************
* Function Name: CapSense_1_GetNoiseThreshold
********************************************************************************
*
* Summary:
*  This function reads the noise threshold from the component.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  This API returns the noise threshold of the widget indicated by the argument. 
*
* Global Variables:
*  CapSense_1_noiseThreshold[] - This array contains the level of signal 
*  for each widget that determines the level of noise in the capacitive scan.
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint8 CapSense_1_GetNoiseThreshold(uint32 widget)
{
	return (CapSense_1_noiseThreshold[widget]);
}


/*******************************************************************************
* Function Name: CapSense_1_GetFingerHysteresis
********************************************************************************
*
* Summary:
*  This function reads the Hysteresis value from the component.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  This API returns the Hysteresis of the widget indicated by the argument. 
*
* Global Variables:
*  CapSense_1_hysteresis[] - This array contains the hysteresis value 
*   for each widget.
*  CapSense_1_widgetNumberSld - structure with dynamic sliders' parameters.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint8 CapSense_1_GetFingerHysteresis(uint32 widget)
{
	return(CapSense_1_hysteresis[widget]);
}


/*******************************************************************************
* Function Name: CapSense_1_GetNegativeNoiseThreshold
********************************************************************************
*
* Summary:
*  This function reads the negative noise threshold from the component.
*
* Parameters: 
*  None.
*
* Return Value: 
*  This API returns the negative noise threshold
*
* Global Variables:
*  CapSense_1_negativeNoiseThreshold - This variable specifies the negative 
*   difference between the raw count and baseline levels for Baseline resetting
*   to the raw count level.
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint8 CapSense_1_GetNegativeNoiseThreshold(uint32 widget)
{
#if (CapSense_1_TUNING_METHOD != CapSense_1__TUNING_NONE)
	return(CapSense_1_negativeNoiseThreshold[widget]);
#else
	return(CapSense_1_NEGATIVE_NOISE_THRESHOLD);
#endif /* (CapSense_1_TUNING_METHOD != CapSense_1__TUNING_NONE) */ 
}


#if(CapSense_1_TUNING_METHOD != CapSense_1__TUNING_NONE)
	/*******************************************************************************
	* Function Name: CapSense_1_SetFingerThreshold
	********************************************************************************
	*
	* Summary:
	*  This API sets the finger threshold value for a widget. 
	*
	* Parameters: 
	*  sensorNumber:  widget index. 
	*  value:  Finger threshold value for the widget.
	*
	* Return Value: 
	*  None
	*
	* Global Variables:
	*  CapSense_1_fingerThreshold[] - This array contains the level of signal 
	*   for each widget that determines if a finger is present on the widget.
	* 
	* Side Effects:
	*  None
	*
	*******************************************************************************/
	void CapSense_1_SetFingerThreshold(uint32 widget, uint8 value)
	{	
		CapSense_1_fingerThreshold[widget] = value;
	}


	/*******************************************************************************
	* Function Name: CapSense_1_SetNoiseThreshold
	********************************************************************************
	*
	* Summary:
	*  This API sets the Noise Threshold value for each widget.
	*
	* Parameters:
	*  widget:  Sensor index number.
	*  value:   Noise Threshold value for widget.
	*
	* Return Value: 
	*  None
	*
	* Global Variables:
	*  CapSense_1_noiseThreshold[] - This array contains the level of signal 
	*   for each widget that determines the level of noise in the capacitive scan.
	* 
	* Side Effects:
	*  None
	*
	*******************************************************************************/
	void CapSense_1_SetNoiseThreshold(uint32 widget, uint8 value)
	{
		CapSense_1_noiseThreshold[widget] = value;
	}


	/*******************************************************************************
	* Function Name: CapSense_1_SetFingerHysteresis
	********************************************************************************
	*
	* Summary:
	*  This API sets the Hysteresis value of a widget
	*
	* Parameters: 
	*  value:  Hysteresis value for widgets.
	*  widget:  widget number
	*
	* Return Value: 
	*  None
	*
	* Global Variables:
	*  CapSense_1_hysteresis[] - This array contains the hysteresis value for each widget.
	*  CapSense_1_widgetNumberSld - structure with dynamic sliders' parameters.
	*
	* Side Effects:
	*  None
	*
	*******************************************************************************/
	void CapSense_1_SetFingerHysteresis(uint32 widget, uint8 value)
	{
		CapSense_1_hysteresis[widget] = value;
	}


	/*******************************************************************************
	* Function Name: CapSense_1_SetNegativeNoiseThreshold
	********************************************************************************
	*
	* Summary:
	*  This API sets the Negative Noise Threshold value of a widget
	*
	* Parameters: 
	*  value:  Negative Noise Threshold value for widgets.
	*  widget: widget number
	*
	* Return Value: 
	*  None
	*
	* Global Variables:
	*  CapSense_1_negativeNoiseThreshold  - This parameter specifies the negative 
	*   difference between the raw count and baseline levels for Baseline resetting to 
	*   the raw count level.
	* 
	* Side Effects:
	*  None
	*
	*******************************************************************************/
	void CapSense_1_SetNegativeNoiseThreshold(uint32 widget, uint8 value)
	{
		CapSense_1_negativeNoiseThreshold[widget] = value;
	}


	/*******************************************************************************
	* Function Name: CapSense_1_SetDebounce
	********************************************************************************
	*
	* Summary:
	*  This API sets the debounce value for a widget.
	*
	* Parameters: 
	*  value:  Debounce value for widget.
	*  widget: widget index.
	*
	* Return Value: 
	*  None
	*
	* Global Variables:
	*  CapSense_1_debounce[] - This array contains the debounce value for each widget.
	*  CapSense_1_widgetNumberSld - structure with dynamic sliders' parameters.
	*
	* Side Effects:
	*  None
	*
	*******************************************************************************/
	void CapSense_1_SetDebounce(uint32 widget, uint8 value)
	{
		CapSense_1_debounce[widget] = value;
	}


	/*******************************************************************************
	* Function Name: CapSense_1_SetLowBaselineReset
	********************************************************************************
	*
	* Summary:
	*  This API sets the low baseline reset threshold value for the sensor.
	*
	* Parameters: 
	*  value: low baseline reset threshold value.
	*  sensor: Sensor index.
	*
	* Return Value: 
	*  None
	*
	* Global Variables:
	*  CapSense_1_lowBaselineReset[] - This array contains the Baseline update 
	*  threshold value for each sensor.
	* 
	* Side Effects:
	*  None
	*
	*******************************************************************************/
	void CapSense_1_SetLowBaselineReset(uint32 sensor, uint8 value)
	{
		CapSense_1_lowBaselineReset[sensor] = value;
	}
#endif /* (CapSense_1_TUNING_METHOD != CapSense_1__TUNING_NONE) */


/*******************************************************************************
* Function Name: CapSense_1_CheckIsSensorActive
********************************************************************************
*
* Summary:
*  Compares the CapSense_1_sensorSignal[sensor] array element to the finger
*  threshold of the widget it belongs to. The hysteresis and debounce are taken into 
*  account. The hysteresis is added or subtracted from the finger threshold 
*  based on whether the sensor is currently active. 
*  If the sensor is active, the threshold is lowered by the hysteresis amount.
*  If the sensor is inactive, the threshold is raised by the hysteresis amount.
*  The debounce counter is added to the sensor active transition.
*  This function updates the CapSense_1_sensorOnMask[] array element.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  Returns sensor state 1 if active, 0 if not active.
*
* Global Variables:
*  CapSense_1_sensorSignal[] - used to store the difference between 
*  the current value of raw data and a previous value of the baseline.
*  CapSense_1_debounceCounter[]   - used to store the current debounce 
*  counter of the sensor. the widget which have this parameter are buttons, matrix 
*  buttons, proximity, and guard. All other widgets don't have the  debounce parameter
*  and use the last element of this array with value 0 (it means no debounce).
*  CapSense_1_sensorOnMask[] - used to store the sensors on/off state.
*  CapSense_1_sensorOnMask[0] contains the masked bits for sensors 
*   0 through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  CapSense_1_sensorEnableMask[1] contains the masked bits for 
*  sensors 8 through 15 (if needed), and so on.
*  0 - sensor is inactive.
*  1 - sensor is active.
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint32 CapSense_1_CheckIsSensorActive(uint32 sensor)
{	
	uint8 widget;
	uint8 debounce;
	uint8 debounceIndex;
    
	uint8 fingerThreshold;
	uint8 hysteresis;
	
    /* Prepare to find debounce counter index */
    widget = CapSense_1_widgetNumber[sensor];
	
    fingerThreshold = CapSense_1_fingerThreshold[widget];
	hysteresis = CapSense_1_hysteresis[widget];
	debounce = CapSense_1_debounce[widget];	
	
	    debounceIndex = CapSense_1_UNUSED_DEBOUNCE_COUNTER_INDEX;
    CapSense_1_debounceCounter[debounceIndex] = 1u;

	
    /* Was on */
    if (0u != CapSense_1_GetBitValue(CapSense_1_sensorOnMask, sensor))
    {
        /* Hysteresis minus */
        if (CapSense_1_sensorSignal[sensor] < (fingerThreshold - hysteresis))
        {
	   		CapSense_1_SetBitValue(CapSense_1_sensorOnMask, sensor, 0u);
			/* Sensor inactive - reset Debounce counter */
            CapSense_1_debounceCounter[debounceIndex] = debounce;
        }
    }
    else    /* Was off */
    {
        /* Hysteresis plus */
        if (CapSense_1_sensorSignal[sensor] >= (fingerThreshold + hysteresis))
        {
			CapSense_1_debounceCounter[debounceIndex]--;
            /* Sensor active, decrement debounce counter */
            if(CapSense_1_debounceCounter[debounceIndex] == 0u)
            {
                CapSense_1_SetBitValue(CapSense_1_sensorOnMask, sensor, 1u); 
            }
        }
        else
        {
            /* Sensor inactive - reset Debounce counter */
            CapSense_1_debounceCounter[debounceIndex] = debounce;
        }
    }
    
    return ((uint32)((0u != CapSense_1_GetBitValue(CapSense_1_sensorOnMask, sensor)) ? 1u : 0u));
}


/*******************************************************************************
* Function Name: CapSense_1_CheckIsWidgetActive
********************************************************************************
*
* Summary:
*  Compares the CapSense_sensorSignal[] array element to the finger threshold of 
* the widget it belongs to. The hysteresis and debounce are taken into account. 
* The hysteresis is added or subtracted from the finger threshold based on whether
*  the sensor is currently active. If the sensor is active, the threshold is 
*  lowered by the hysteresis amount. If the sensor is inactive, the threshold 
*  is raised by the hysteresis amount. 
* The debounce counter added to the sensor active transition. 
* This function updates CapSense_sensorOnMask[] array element
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  Returns widget sensor state 1 if one or more sensors within widget is/are 
*  active, 0 if all sensors within widget are inactive.
*
* Global Variables:
*  rawDataIndex[] – Contains the  1st sensor position in the widget
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint32 CapSense_1_CheckIsWidgetActive(uint32 widget)
{
    uint32 rawIndex = (uint32)CapSense_1_rawDataIndex[widget];
    uint32 numOfSensors = (uint32)CapSense_1_numberOfSensors[widget] + rawIndex;
    uint32 state = 0u;

    /* Check all sensors of widget */
    do
    {
        if(CapSense_1_CheckIsSensorActive((uint32)rawIndex) != 0u)
        {
            state = CapSense_1_SENSOR_IS_ACTIVE;
        }
        rawIndex++;
    }
    while(rawIndex < numOfSensors);
    

    
    return state;
}


/*******************************************************************************
* Function Name: CapSense_1_CheckIsAnyWidgetActive
********************************************************************************
*
* Summary:
*  Compares all the sensors of the CapSense_1_Signal[] array to their finger 
*  threshold. Calls CapSense_1_CheckIsWidgetActive() for each widget so 
*  the CapSense_1_sensorOnMask[] array is up to date after calling this 
*  function.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  Returns 1 if any widget is active, 0 none of widgets are active.
*
* Global Variables:
*  None
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint32 CapSense_1_CheckIsAnyWidgetActive(void)
{

	    uint32 i;
    uint32 state = 0u;
    
    for(i = 0u; i < CapSense_1_TOTAL_WIDGET_COUNT; i++)
    {
        if (CapSense_1_CheckIsWidgetActive(i) != 0u)
        {
            state = CapSense_1_WIDGET_IS_ACTIVE;
        }
    }
    


    return state;
}


/*******************************************************************************
* Function Name: CapSense_1_EnableWidget
********************************************************************************
*
* Summary:
*  Enables all the widget elements (sensors) to the scanning process.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  None
*
* Global Variables:
*  CapSense_1_sensorEnableMask[] - used to store the sensor scanning 
*  state.
*  CapSense_1_sensorEnableMask[0] contains the masked bits for sensors 
*  0 through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  CapSense_1_sensorEnableMask[1] contains the masked bits for 
*  sensors 8 through 15 (if needed), and so on.
*  0 - sensor doesn't scan by CapSense_1_ScanEnabledWidgets().
*  1 - sensor scans by CapSense_1_ScanEnabledWidgets().
* 
* Side Effects:
*  None
*
*******************************************************************************/
void CapSense_1_EnableWidget(uint32 widget)
{

    uint8 rawIndex = CapSense_1_rawDataIndex[widget];
    uint8 numOfSensors = CapSense_1_numberOfSensors[widget] + rawIndex;
    
    /* Enable all sensors of widget */
    do
    {
        CapSense_1_SetBitValue(CapSense_1_sensorEnableMask, (uint32)rawIndex, 1u);
        rawIndex++;
    }
    while(rawIndex < numOfSensors);
}


/*******************************************************************************
* Function Name: CapSense_1_DisableWidget
********************************************************************************
*
* Summary:
*  Disables all the widget elements (sensors) from the scanning process.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  None
*
* Global Variables:
*  CapSense_1_sensorEnableMask[] - used to store the sensor scanning 
*  state.
*  CapSense_1_sensorEnableMask[0] contains the masked bits for sensors 
*  0 through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  CapSense_1_sensorEnableMask[1] contains the masked bits for 
*  sensors 8 through 15 (if needed), and so on.
*  0 - sensor isn't scanned by CapSense_1_ScanEnabledWidgets().
*  1 - sensor is scanned by CapSense_1_ScanEnabledWidgets().
* 
* Side Effects:
*  None
*
*******************************************************************************/
void CapSense_1_DisableWidget(uint32 widget)
{
    uint8 rawIndex = CapSense_1_rawDataIndex[widget];
    uint8 numOfSensors = CapSense_1_numberOfSensors[widget] + rawIndex;
   
    /* Disable all sensors of widget */
    do
    {

        CapSense_1_SetBitValue(CapSense_1_sensorEnableMask, (uint32)rawIndex, 0u);
        rawIndex++;
    }
    while(rawIndex < numOfSensors);
}


#if(CapSense_1_TOTAL_CENTROIDS_COUNT)
    /*******************************************************************************
    * Function Name: CapSense_1_FindMaximum
    ********************************************************************************
    *
    * Summary:
    *  Finds the index of the maximum element within a defined centroid. Checks 
    *  CapSense_1_sensorSignal[] within a defined centroid and 
    *  returns the index of the maximum element. The values below the finger threshold are 
    *  ignored.
    *  The centroid is defined by offset of the first element and a number of elements - count.
    *  The diplexed centroid requires at least two consecutive elements above
    *  FingerThreshold to find the index of the maximum element.
    * 
    * Parameters:
    *  offset:  Start index of centroid in CapSense_1_sensorSignal[] array.
    *  count:   number of elements within centroid.
    *  fingerThreshold:  Finger threshold.
    *  diplex:   pointer to diplex table.
    * 
    * Return:
    *  Returns the index of the maximum element within a defined centroid.
    *  If the index of the maximum element isn't found it returns 0xFF.
	*
	* Global Variables:
	*  CapSense_1_startOfSlider[] - contains the index of the first slider element
	* 
	* Side Effects: 
	*  None
	* 
    *******************************************************************************/
	#if (CapSense_1_IS_DIPLEX_SLIDER)
		uint8 CapSense_1_FindMaximum(uint8 offset, uint8 count, uint8 fingerThreshold, const uint8 *diplex)
	#else 
		uint8 CapSense_1_FindMaximum(uint8 offset, uint8 count, uint8 fingerThreshold)
	#endif /* (CapSense_1_IS_DIPLEX_SLIDER) */
    {
        uint8 i;
        #if (CapSense_1_IS_DIPLEX_SLIDER)        
            uint8 curPos = 0u;
            /* No centroid at Start */
            uint8 curCntrdSize = 0u;
            uint8 curCtrdStartPos = CapSense_1_MAXIMUM_CENTROID;
            /* Biggest centroid is zero */
            uint8 biggestCtrdSize = 0u;
            uint8 biggestCtrdStartPos = 0u;
        #endif /* (CapSense_1_IS_DIPLEX_SLIDER) */
        uint8 maximum = CapSense_1_MAXIMUM_CENTROID;
		
        uint8 temp = 0u;
        uint8 *startOfSlider = &CapSense_1_sensorSignal[offset];

        #if (CapSense_1_IS_DIPLEX_SLIDER)        
            if(diplex != 0u)
            {
                /* Initialize */
                i = 0u;
                
                /* Make slider x2 as Diplexed */
                count <<= 1u;
                while(1u)
                { 
                    if (startOfSlider[curPos] > 0u)    /* Looking for centroids */
                    {
                        if (curCtrdStartPos == CapSense_1_MAXIMUM_CENTROID)
                        {
                            /* Start of centroid */
                            curCtrdStartPos = i;
                            curCntrdSize++;
                        }
                        else
                        {
                            curCntrdSize++;
                        }
                    }
                    else   /* Select biggest and indicate zero start */
                    {          
                        if(curCntrdSize > 0u)
                        {
                            /* We are at the end of current */
                            if(curCntrdSize > biggestCtrdSize)
                            {
                                biggestCtrdSize = curCntrdSize;
                                biggestCtrdStartPos = curCtrdStartPos;
                            }
                            
                            curCntrdSize = 0u;
                            curCtrdStartPos = CapSense_1_MAXIMUM_CENTROID;
                        }
                    }
                    
                    i++; 
                    curPos = diplex[i];
                    if(i == count)
                    {
                        break;
                    }            
                }
                    
                    /* Find biggest centroid if two are same size, last one wins
                       We are at the end of current */
                if (curCntrdSize >= biggestCtrdSize) 
                {
                    biggestCtrdSize = curCntrdSize;
                    biggestCtrdStartPos = curCtrdStartPos;
                }
            }
            else
            {
                /* Without diplexing */ 
                biggestCtrdSize = count;
            }
                        

            /* Check centroid size */
            #if (CapSense_1_IS_NON_DIPLEX_SLIDER)
                if((biggestCtrdSize >= 2u) || ((biggestCtrdSize == 1u) && (diplex == 0u)))
            #else                    
                if(biggestCtrdSize >= 2u)
            #endif /* (CapSense_1_IS_NON_DIPLEX_SLIDER) */
                {
                    for (i = biggestCtrdStartPos; i < (biggestCtrdStartPos + biggestCtrdSize); i++)
                    {
                        #if (CapSense_1_IS_DIPLEX_SLIDER && CapSense_1_IS_NON_DIPLEX_SLIDER)
                            if (diplex == 0u)
                            {
                                curPos = i;
                            }
                            else
                            {
                                curPos = diplex[i];
                            }                    
                        #elif (CapSense_1_IS_DIPLEX_SLIDER)                    
                            curPos = diplex[i];                    
                        #endif /* (CapSense_1_IS_DIPLEX_SLIDER && CapSense_1_IS_NON_DIPLEX_SLIDER) */
                        /* Looking for greater element within centroid */
                        if(startOfSlider[curPos] > fingerThreshold)
                        {
                            if(startOfSlider[curPos] > temp)
                            {
                                maximum = i;
                                temp = startOfSlider[curPos];
                            }
                        }
                    }
                } 
        #else
            for (i = 0u; i < count; i++)
            {                      
                /* Looking for greater element within centroid */
                if(startOfSlider[i] > fingerThreshold)
                {
                    if(startOfSlider[i] > temp)
                    {
                        maximum = i;
                        temp = startOfSlider[i];
                    }
                }
            }    
        #endif /* (CapSense_1_IS_DIPLEX_SLIDER) */
        return (maximum);
    }
    
    
    /*******************************************************************************
    * Function Name: CapSense_1_CalcCentroid
    ********************************************************************************
    *
    * Summary:
    *  Returns a position value calculated according to the index of the maximum element and API
    *  resolution.
    *
    * Parameters:
    *  type:  widget type.
    *  diplex:  pointer to diplex table.
    *  maximum:  Index of maximum element within centroid.
    *  offset:   Start index of centroid in CapSense_1_sensorSignal[] array.
    *  count:    Number of elements within centroid.
    *  resolution:  multiplicator calculated according to centroid type and
    *  API resolution.
    *  noiseThreshold:  Noise threshold.
    * 
    * Return:
    *  Returns a position value of the slider.
	*
	* Side Effects: 
	*  None
	* 
    *******************************************************************************/
    uint8 CapSense_1_CalcCentroid(uint8 maximum, uint8 offset, 
                                        uint8 count, uint16 resolution, uint8 noiseThreshold)
    {
        #if ((CapSense_1_TOTAL_LINEAR_SLIDERS_COUNT > 0u) || (CapSense_1_TOTAL_TOUCH_PADS_COUNT > 0u))
            uint8 posPrev;
            uint8 posNext;
        #endif /* ((CapSense_1_TOTAL_LINEAR_SLIDERS_COUNT>0u) || (CapSense_1_TOTAL_TOUCH_PADS_COUNT>0u)) */
        
        /* Helps during centroid calculation */
        #if (CapSense_1_TOTAL_CENTROIDS_COUNT)
		    static uint8 CapSense_1_centroid[3u];
        #endif  /* (CapSense_1_TOTAL_CENTROIDS_COUNT) */
               
        #if (CapSense_1_IS_DIPLEX_SLIDER)                
            uint8 pos;
        #endif /* (CapSense_1_IS_DIPLEX_SLIDER) */

        uint8 position;
        uint32 numerator;
        int32 denominator;
		
		uint8  *startOfSlider = &CapSense_1_sensorSignal[offset];
		
        #if ((CapSense_1_TOTAL_LINEAR_SLIDERS_COUNT > 0u) || (CapSense_1_TOTAL_TOUCH_PADS_COUNT > 0u))
            posPrev = 0u;
            posNext = 0u;
        #endif /* ((CapSense_1_TOTAL_LINEAR_SLIDERS_COUNT>0u) || (CapSense_1_TOTAL_TOUCH_PADS_COUNT>0u)) */
     
        #if (CapSense_1_ADD_SLIDER_TYPE)
            if(type == CapSense_1_TYPE_RADIAL_SLIDER)
            {
        #endif /* (CapSense_1_ADD_SLIDER_TYPE) */

            #if (CapSense_1_TOTAL_RADIAL_SLIDERS_COUNT > 0u)                
                /* Copy Signal to the centroid array */
                CapSense_1_centroid[CapSense_1_POS] = startOfSlider[maximum];
                 
                /* Check borders for ROTARY Slider */
                if (maximum == 0u)                   /* Start of centroid */
                { 
                    CapSense_1_centroid[CapSense_1_POS_PREV] = startOfSlider[count - 1u];
                    CapSense_1_centroid[CapSense_1_POS_NEXT] = startOfSlider[1u];
                }
                else if (maximum == (count - 1u))    /* End of centroid */
                {
                    CapSense_1_centroid[CapSense_1_POS_PREV] = startOfSlider[maximum - 1u];
                    CapSense_1_centroid[CapSense_1_POS_NEXT] = startOfSlider[0u];
                }
                else                                /* Not first Not last */
                {
                    CapSense_1_centroid[CapSense_1_POS_PREV] = startOfSlider[maximum - 1u];
                    CapSense_1_centroid[CapSense_1_POS_NEXT] = startOfSlider[maximum + 1u];
                }
            #endif /* (CapSense_1_TOTAL_RADIAL_SLIDERS_COUNT > 0u) */

        #if (CapSense_1_ADD_SLIDER_TYPE)
            }
            else
            {
        #endif /* (CapSense_1_ADD_SLIDER_TYPE) */

            #if ((CapSense_1_TOTAL_LINEAR_SLIDERS_COUNT > 0u) || (CapSense_1_TOTAL_TOUCH_PADS_COUNT > 0u))
                #if (CapSense_1_IS_DIPLEX_SLIDER && CapSense_1_IS_NON_DIPLEX_SLIDER)                    
                    /* Calculate next and previous near to maximum */
                    if(diplex == 0u)
                    {
                        pos     = maximum;
                        posPrev = maximum - 1u;
                        posNext = maximum + 1u; 
                    }
                    else
                    {
                        pos     = diplex[maximum];
                        posPrev = diplex[maximum - 1u];
                        posNext = diplex[maximum + 1u];
                        count <<= 1u;
                    }                    
                #elif (CapSense_1_IS_DIPLEX_SLIDER)
                    /* Calculate next and previous near to maximum */
                    pos     = diplex[maximum];
                    posPrev = diplex[maximum - 1u];
                    posNext = diplex[maximum + 1u];
                    count <<= 1u;                    
                #else                    
                    /* Calculate next and previous near to maximum */
                    if (maximum >= 1u)
                    {
                        posPrev = maximum - 1u;
                    }
                    posNext = maximum + 1u;
                #endif /* (CapSense_1_IS_DIPLEX_SLIDER && CapSense_1_IS_NON_DIPLEX_SLIDER) */
                        
                /* Copy Signal to the centroid array */
                #if (CapSense_1_IS_DIPLEX_SLIDER)
                    CapSense_1_centroid[CapSense_1_POS] = startOfSlider[pos];
                #else
                    CapSense_1_centroid[CapSense_1_POS] = startOfSlider[maximum];
                #endif /* (CapSense_1_IS_DIPLEX_SLIDER) */
                    
                /* Check borders for LINEAR Slider */
                if (maximum == 0u)                   /* Start of centroid */
                { 
                    CapSense_1_centroid[CapSense_1_POS_PREV] = 0u;
                    CapSense_1_centroid[CapSense_1_POS_NEXT] = startOfSlider[posNext];
                }
                else if (maximum == ((count) - 1u)) /* End of centroid */
                {
                    CapSense_1_centroid[CapSense_1_POS_PREV] = startOfSlider[posPrev];
                    CapSense_1_centroid[CapSense_1_POS_NEXT] = 0u;
                }
                else                                /* Not first Not last */
                {
                    CapSense_1_centroid[CapSense_1_POS_PREV] = startOfSlider[posPrev];
                    CapSense_1_centroid[CapSense_1_POS_NEXT] = startOfSlider[posNext];
                }
            #endif /* ((CapSense_1_TOTAL_LINEAR_SLIDERS_COUNT>0u)||(CapSense_1_TOTAL_TOUCH_PADS_COUNT>0u))*/

        #if (CapSense_1_ADD_SLIDER_TYPE)
            }
        #endif /* (CapSense_1_ADD_SLIDER_TYPE) */
    
        /* Subtract noiseThreshold */
        if(CapSense_1_centroid[CapSense_1_POS_PREV] > noiseThreshold)
        {
            CapSense_1_centroid[CapSense_1_POS_PREV] -= noiseThreshold;
        }
        else
        {
            CapSense_1_centroid[CapSense_1_POS_PREV] = 0u;
        }
        
        /* Maximum always greater than fingerThreshold, so greater than noiseThreshold */
        CapSense_1_centroid[CapSense_1_POS] -= noiseThreshold;
        
        /* Subtract noiseThreshold */
        if(CapSense_1_centroid[CapSense_1_POS_NEXT] > noiseThreshold)
        {
            CapSense_1_centroid[CapSense_1_POS_NEXT] -= noiseThreshold;
        }
        else
        {
            CapSense_1_centroid[CapSense_1_POS_NEXT] = 0u;
        }
        
        
        /* Si+1 - Si-1 */
        numerator = (uint32) CapSense_1_centroid[CapSense_1_POS_NEXT] -
                    (uint32) CapSense_1_centroid[CapSense_1_POS_PREV];

        /* Si+1 + Si + Si-1 */
        denominator = (int32) CapSense_1_centroid[CapSense_1_POS_PREV] + 
                      (int32) CapSense_1_centroid[CapSense_1_POS] + 
                      (int32) CapSense_1_centroid[CapSense_1_POS_NEXT];
        
        /* (numerator/denominator) + maximum */
        denominator = (((int32)(uint32)((uint32)numerator << 8u)/denominator) + (int32)(uint32)((uint32) maximum << 8u));

        #if(CapSense_1_TOTAL_RADIAL_SLIDERS_COUNT > 0u)
            /* Only required for RADIAL Slider */
            if(denominator < 0)
            {
                denominator += (int32)((uint16)((uint16) count << 8u));
            }
        #endif /* (CapSense_1_TOTAL_RADIAL_SLIDERS_COUNT > 0u) */
        
        denominator *= (int16)resolution;
        
        /* Round result and put it to uint8 */
        position = ((uint8) HI16((uint32)denominator + CapSense_1_CENTROID_ROUND_VALUE));

        return (position);
    }    
#endif /* (CapSense_1_TOTAL_CENTROIDS_COUNT) */


#if((CapSense_1_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (CapSense_1_TOTAL_LINEAR_SLIDERS_COUNT > 0u))
    /*******************************************************************************
    * Function Name: CapSense_1_GetCentroidPos
    ********************************************************************************
    *
    * Summary:
    *  Checks the CapSense_1_Signal[ ] array for a centroid within
    *  a slider specified range. The centroid position is calculated according to the resolution
    *  specified in the CapSense customizer. The position filters are applied to the
    *  result if enabled.
    *
    * Parameters:
    *  widget:  Widget number.
    *  For every linear slider widget there are defines in this format:
    *  #define CapSense_1_"widget_name"__LS           5
    * 
    * Return:
    *  Returns a position value of the linear slider.
	*
	* Global Variables:
	*  None
	*
    * Side Effects:
    *  If any sensor within the slider widget is active, the function returns values
    *  from zero to the API resolution value set in the CapSense customizer. If no
    *  sensors are active, the function returns 0xFFFF. If an error occurs during
    *  execution of the centroid/diplexing algorithm, the function returns 0xFFFF.
    *  There are no checks of the widget type argument provided to this function.
    *  The unproper widget type provided will cause unexpected position calculations.
    *
    * Note:
    *  If noise counts on the slider segments are greater than the noise
    *  threshold, this subroutine may generate a false centroid result. The noise
    *  threshold should be set carefully (high enough above the noise level) so
    *  that noise will not generate a false centroid.
    *******************************************************************************/
    uint16 CapSense_1_GetCentroidPos(uint32 widget)
    {
        #if (CapSense_1_IS_DIPLEX_SLIDER)
            const uint8 *diplex;
        #endif /* (CapSense_1_IS_DIPLEX_SLIDER) */
                
        #if (0u != CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK)
            uint8 posIndex;
            uint8 firstTimeIndex = CapSense_1_posFiltersData[widget];
            uint8 posFiltersMask = CapSense_1_posFiltersMask[widget];  
        #endif /* (0u != CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK) */

        #if ((0u != (CapSense_1_MEDIAN_FILTER & CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK)) || \
             (0u != (CapSense_1_AVERAGING_FILTER & CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK)))
            uint8 tempPos;
        #endif /* ((0u != (CapSense_1_MEDIAN_FILTER & CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK)) || \
               *   (0u != (CapSense_1_AVERAGING_FILTER & CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK)))
               */

        uint8 maximum;
        uint16 position;
        uint8 offset = CapSense_1_rawDataIndex[widget];
        uint8 count = CapSense_1_numberOfSensors[widget];
                        
        #if (CapSense_1_IS_DIPLEX_SLIDER)
            if(widget < CapSense_1_TOTAL_DIPLEXED_SLIDERS_COUNT)
            {
                maximum = CapSense_1_diplexTable[widget];
                diplex = &CapSense_1_diplexTable[maximum];
            }
            else
            {
                diplex = 0u;
            }
        #endif /* (CapSense_1_IS_DIPLEX_SLIDER) */

		/* Find Maximum within centroid */      
		#if (CapSense_1_IS_DIPLEX_SLIDER)        
			maximum = CapSense_1_FindMaximum(offset, count, (uint8)CapSense_1_fingerThreshold[widget], diplex);
		#else
			maximum = CapSense_1_FindMaximum(offset, count, (uint8)CapSense_1_fingerThreshold[widget]);
		#endif /* (CapSense_1_IS_DIPLEX_SLIDER) */

        if (maximum != 0xFFu)
        {
            /* Calculate centroid */
            position = (uint16) CapSense_1_CalcCentroid(maximum, 
                         offset, count, CapSense_1_centroidMult[widget], CapSense_1_noiseThreshold[widget]);

            #if (0u != CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK)
                /* Check if this linear slider has enabled filters */
                if (0u != (posFiltersMask & CapSense_1_ANY_POS_FILTER))
                {
                    /* Calculate position to store filters data */
                    posIndex  = firstTimeIndex + 1u;
                    
                    if (0u == CapSense_1_posFiltersData[firstTimeIndex])
                    {
                        /* Init filters */
                        CapSense_1_posFiltersData[posIndex] = (uint8) position;
                        #if ((0u != (CapSense_1_MEDIAN_FILTER & \
                                     CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK)) || \
                             (0u != (CapSense_1_AVERAGING_FILTER & \
                                     CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK)))

                            if ( (0u != (posFiltersMask & CapSense_1_MEDIAN_FILTER)) || 
                                 (0u != (posFiltersMask & CapSense_1_AVERAGING_FILTER)) )
                            {
                                CapSense_1_posFiltersData[posIndex + 1u] = (uint8) position;
                            }
                        #endif /* ((0u != (CapSense_1_MEDIAN_FILTER & \
                               *           CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK)) || \
                               *   (0u != (CapSense_1_AVERAGING_FILTER & \
                               *           CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK)))
                               */
                        
                        CapSense_1_posFiltersData[firstTimeIndex] = 1u;
                    }
                    else
                    {
                        /* Do filtering */
                        #if (0u != (CapSense_1_MEDIAN_FILTER & CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & CapSense_1_MEDIAN_FILTER))
                            {
                                tempPos = (uint8) position;
                                position = CapSense_1_MedianFilter(position,
                                                                (uint16)CapSense_1_posFiltersData[posIndex],
                                                                (uint16)CapSense_1_posFiltersData[posIndex + 1u]);
                                CapSense_1_posFiltersData[posIndex + 1u] =
                                                                             CapSense_1_posFiltersData[posIndex];
                                CapSense_1_posFiltersData[posIndex] = tempPos;
                            }
                        #endif /*(0u != (CapSense_1_MEDIAN_FILTER &
                               *         CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK))
                               */

                        #if(0u!=(CapSense_1_AVERAGING_FILTER & CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & CapSense_1_AVERAGING_FILTER)) 
                            {
                                tempPos = (uint8) position;
                                position = CapSense_1_AveragingFilter(position,
                                                                (uint16)CapSense_1_posFiltersData[posIndex],
                                                                (uint16)CapSense_1_posFiltersData[posIndex + 1u]);
                                CapSense_1_posFiltersData[posIndex+1u]=CapSense_1_posFiltersData[posIndex];
                                CapSense_1_posFiltersData[posIndex] = tempPos;
                            }
                        #endif /* (0u != (CapSense_1_AVERAGING_FILTER & \
                               *           CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK))
                               */

                        #if (0u != (CapSense_1_IIR2_FILTER & CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK)) 
                            if (0u != (posFiltersMask & CapSense_1_IIR2_FILTER)) 
                            {
                                position = CapSense_1_IIR2Filter(position,
                                                                    (uint16)CapSense_1_posFiltersData[posIndex]);
                                CapSense_1_posFiltersData[posIndex] = (uint8) position;
                            }
                        #endif /* (0u != (CapSense_1_IIR2_FILTER & \
                               *          CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK))
                               */

                        #if (0u != (CapSense_1_IIR4_FILTER & CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & CapSense_1_IIR4_FILTER))
                            {
                                position = CapSense_1_IIR4Filter(position,
                                                                    (uint16)CapSense_1_posFiltersData[posIndex]);
                                CapSense_1_posFiltersData[posIndex] = (uint8) position;
                            }                                
                        #endif /* (0u != (CapSense_1_IIR4_FILTER & \
                               *          CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK))
                               */

                        #if (0u != (CapSense_1_JITTER_FILTER & CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & CapSense_1_JITTER_FILTER))
                            {
                                position = CapSense_1_JitterFilter(position,
                                                                    (uint16)CapSense_1_posFiltersData[posIndex]);
                                CapSense_1_posFiltersData[posIndex] = (uint8) position;
                            }
                        #endif /* (0u != (CapSense_1_JITTER_FILTER & \
                               *           CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK))
                               */
                    }
                }
            #endif /* (0u != CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK) */

        }
        else
        {
            /* Maximum wasn't found */
            position = 0xFFFFu;

            #if(0u != CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK)
                /* Reset filters */
                if(0u != (posFiltersMask & CapSense_1_ANY_POS_FILTER))
                {
                    CapSense_1_posFiltersData[firstTimeIndex] = 0u;
                }
            #endif /* (0u != CapSense_1_LINEAR_SLIDERS_POS_FILTERS_MASK) */
        }

        
        return (position);
    }
#endif /* ((CapSense_1_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (CapSense_1_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) */


#if((CapSense_1_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (CapSense_1_TOTAL_LINEAR_SLIDERS_COUNT > 0u))
    /*******************************************************************************
    * Function Name: CapSense_1_GetRadialCentroidPos
    ********************************************************************************
    *
    * Summary:
    *  Checks the CapSense_1_Signal[ ] array for a centroid within
    *  a slider specified range. The centroid position is calculated according to the resolution
    *  specified in the CapSense customizer. The position filters are applied to the
    *  result if enabled.
    *
    * Parameters:
    *  widget:  Widget number.
    *  For every radial slider widget there are defines in this format:
    *  #define CapSense_1_"widget_name"__RS           5
    * 
    * Return:
    *  Returns a position value of the radial slider.
    *
	* Global Variables:
	*  None.
	*
    * Side Effects:
    *  If any sensor within the slider widget is active, the function returns values
    *  from zero to the API resolution value set in the CapSense customizer. If no
    *  sensors are active, the function returns 0xFFFF.
    *  There are no checks of the widget type argument provided to this function.
    *  The unproper widget type provided will cause unexpected position calculations.
    *
    * Note:
    *  If noise counts on the slider segments are greater than the noise
    *  threshold, this subroutine may generate a false centroid result. The noise
    *  threshold should be set carefully (high enough above the noise level) so 
    *  that noise will not generate a false centroid.
    *
    *******************************************************************************/
     uint16 CapSense_1_GetRadialCentroidPos(uint32 widget)
    {
        #if (0u != CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK)
            uint8 posIndex;
            uint8 firstTimeIndex = CapSense_1_posFiltersData[widget];
            uint8 posFiltersMask = CapSense_1_posFiltersMask[widget]; 
        #endif /* (0u != CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK) */

        #if ((0u != (CapSense_1_MEDIAN_FILTER & CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK)) || \
             (0u != (CapSense_1_AVERAGING_FILTER & CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK)))
            uint8 tempPos;
        #endif /* ((0u != (CapSense_1_MEDIAN_FILTER & CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK)) || \
               *   (0u != (CapSense_1_AVERAGING_FILTER & CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK)))
               */

        uint8 maximum;
        uint16 position;
        uint8 offset = CapSense_1_rawDataIndex[widget];
        uint8 count = CapSense_1_numberOfSensors[widget];

		/* Find Maximum within centroid */      
		#if (CapSense_1_IS_DIPLEX_SLIDER)        
			maximum = CapSense_1_FindMaximum(offset, count, (uint8)CapSense_1_fingerThreshold[widget], 0u);
		#else
			maximum = CapSense_1_FindMaximum(offset, count, (uint8)CapSense_1_fingerThreshold[widget]);
		#endif /* (CapSense_1_IS_DIPLEX_SLIDER) */
        
        if (maximum != CapSense_1_MAXIMUM_CENTROID)
        {
            /* Calculate centroid */
            position = (uint16) CapSense_1_CalcCentroid(maximum, 
                         offset, count, CapSense_1_centroidMult[widget], CapSense_1_noiseThreshold[widget]);

            #if (0u != CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK)
                /* Check if this Radial slider has enabled filters */
                if (0u != (posFiltersMask & CapSense_1_ANY_POS_FILTER))
                {
                    /* Calculate position to store filters data */
                    posIndex  = firstTimeIndex + 1u;
                    
                    if (0u == CapSense_1_posFiltersData[firstTimeIndex])
                    {
                        /* Init filters */
                        CapSense_1_posFiltersData[posIndex] = (uint8) position;
                        #if ((0u != (CapSense_1_MEDIAN_FILTER & \
                                     CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK)) || \
                             (0u != (CapSense_1_AVERAGING_FILTER & \
                                     CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK)))

                            if ( (0u != (posFiltersMask & CapSense_1_MEDIAN_FILTER))  || 
                                 (0u != (posFiltersMask & CapSense_1_AVERAGING_FILTER)) )
                            {
                                CapSense_1_posFiltersData[posIndex + 1u] = (uint8) position;
                            }
                        #endif /* ((0u != (CapSense_1_MEDIAN_FILTER & \
                               *           CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK)) || \
                               *   (0u != (CapSense_1_AVERAGING_FILTER & \
                               *           CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK)))
                               */
                        
                        CapSense_1_posFiltersData[firstTimeIndex] = 1u;
                    }
                    else
                    {
                        /* Do filtering */
                        #if (0u != (CapSense_1_MEDIAN_FILTER & CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & CapSense_1_MEDIAN_FILTER))
                            {
                                tempPos = (uint8) position;
                                position = CapSense_1_MedianFilter(position,
                                                                        CapSense_1_posFiltersData[posIndex],
                                                                        CapSense_1_posFiltersData[posIndex + 1u]);
                                CapSense_1_posFiltersData[posIndex + 1u] = 
                                                                              CapSense_1_posFiltersData[posIndex];
                                CapSense_1_posFiltersData[posIndex] = tempPos;
                            }
                        #endif /* (0u != (CapSense_1_MEDIAN_FILTER & 
                               *          CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK))
                               */

                        #if (0u != (CapSense_1_AVERAGING_FILTER & \
                                    CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & CapSense_1_AVERAGING_FILTER))
                            {
                                tempPos = (uint8) position;
                                position = CapSense_1_AveragingFilter(position, 
                                                                       CapSense_1_posFiltersData[posIndex],
                                                                       CapSense_1_posFiltersData[posIndex + 1u]);
                                CapSense_1_posFiltersData[posIndex+1u]= CapSense_1_posFiltersData[posIndex];
                                CapSense_1_posFiltersData[posIndex] = tempPos;
                            }
                        #endif /* (0u != (CapSense_1_AVERAGING_FILTER & \
                               *          CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK))
                               */

                        #if (0u != (CapSense_1_IIR2_FILTER & CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & CapSense_1_IIR2_FILTER))
                            {
                                position = CapSense_1_IIR2Filter(position,
                                                                    (uint16)CapSense_1_posFiltersData[posIndex]);
                                CapSense_1_posFiltersData[posIndex] = (uint8) position;
                            }
                        #endif /* (0u != (CapSense_1_IIR2_FILTER & 
                               *          CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK))
                               */

                        #if (0u != (CapSense_1_IIR4_FILTER & CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & CapSense_1_IIR4_FILTER))
                            {
                                position = CapSense_1_IIR4Filter(position,
                                                                    (uint16)CapSense_1_posFiltersData[posIndex]);
                                CapSense_1_posFiltersData[posIndex] = (uint8) position;
                            }
                        #endif /* (0u != (CapSense_1_IIR4_FILTER & 
                               *          CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK))
                               */

                        #if (0u != (CapSense_1_JITTER_FILTER & CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & CapSense_1_JITTER_FILTER))
                            {
                                position = CapSense_1_JitterFilter(position, 
                                                                         CapSense_1_posFiltersData[posIndex]);
                                CapSense_1_posFiltersData[posIndex] = (uint8) position;
                            }
                        #endif /* (0u != (CapSense_1_JITTER_FILTER &
                               *           CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK))
                               */
                    }
                }
            #endif /* (0u != CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK) */

        }
        else
        {
            /* Maximum wasn't found?? */
            position = 0xFFFFu;

            #if (0u != CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK)
                /* Reset filters */
                if((posFiltersMask & CapSense_1_ANY_POS_FILTER) != 0u)
                {
                    CapSense_1_posFiltersData[firstTimeIndex] = 0u;
                }
            #endif /* (0u != CapSense_1_RADIAL_SLIDERS_POS_FILTERS_MASK) */
        }
        
        return (position);
    }
#endif /* ((CapSense_1_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (CapSense_1_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) */


#if(CapSense_1_TOTAL_TOUCH_PADS_COUNT > 0u)
    /*******************************************************************************
    * Function Name: CapSense_1_GetTouchCentroidPos
    ********************************************************************************
    *
    * Summary:
    *  If a finger is present on a touchpad, this function calculates the X and Y
    *  position of the finger by calculating the centroids within touchpad specified
    *  range. The X and Y positions are calculated according to the API resolutions set in the
    *  CapSense customizer. Returns 1 if a finger is on the touchpad.
    *  The position filter is applied to the result if enabled.
    *  This function is available only if a touch pad is defined by the CapSense
    *  customizer.
    *
    * Parameters:
    *  widget:  Widget number. 
    *  For every touchpad widget there are defines in this format:
    *  #define CapSense_1_"widget_name"__TP            5
    *
    *  pos:     Pointer to the array of two uint16 elements, where result
    *  result of calculation of X and Y position are stored.
    *  pos[0u]  - position of X
    *  pos[1u]  - position of Y
    *
    * Return:
    *  Returns a 1 if a finger is on the touch pad, 0 - if not.
	*
	* Global Variables:
	*  None.
	*
    * Side Effects:
    *   There are no checks of the widget type argument provided to this function.
    *   The unproper widget type provided will cause unexpected position
    *   calculations.
    *
    *******************************************************************************/
    uint32 CapSense_1_GetTouchCentroidPos(uint32 widget, uint16* pos)
    {
        #if (0u != CapSense_1_TOUCH_PADS_POS_FILTERS_MASK)
            uint8 posXIndex;
            uint8 posYIndex;
            uint8 firstTimeIndex = CapSense_1_posFiltersData[widget];
            uint8 posFiltersMask = CapSense_1_posFiltersMask[widget];
        #endif /* (0u != CapSense_1_TOUCH_PADS_POS_FILTERS_MASK) */

        #if ((0u != (CapSense_1_MEDIAN_FILTER & CapSense_1_TOUCH_PADS_POS_FILTERS_MASK)) || \
             (0u != (CapSense_1_AVERAGING_FILTER & CapSense_1_TOUCH_PADS_POS_FILTERS_MASK)))
            uint16 tempPos;
        #endif /* ((0u != (CapSense_1_MEDIAN_FILTER & CapSense_1_TOUCH_PADS_POS_FILTERS_MASK)) || \
               *   (0u != (CapSense_1_AVERAGING_FILTER & CapSense_1_TOUCH_PADS_POS_FILTERS_MASK)))
               */

        uint8 MaxX;
        uint8 MaxY;
        uint8 posX;
        uint8 posY;
        uint32 touch = 0u;
        uint8 offset = CapSense_1_rawDataIndex[widget];
        uint8 count = CapSense_1_numberOfSensors[widget];
        
        /* Find Maximum within X centroid */
        #if (CapSense_1_IS_DIPLEX_SLIDER)
            MaxX = CapSense_1_FindMaximum(offset, count, CapSense_1_fingerThreshold[widget], 0u);
        #else
            MaxX = CapSense_1_FindMaximum(offset, count, CapSense_1_fingerThreshold[widget]);
        #endif /* (CapSense_1_IS_DIPLEX_SLIDER) */

        if (MaxX != CapSense_1_MAXIMUM_CENTROID)
        {
            offset = CapSense_1_rawDataIndex[widget + 1u];
            count = CapSense_1_numberOfSensors[widget + 1u];

            /* Find Maximum within Y centroid */
            #if (CapSense_1_IS_DIPLEX_SLIDER)
                MaxY = CapSense_1_FindMaximum(offset, count, CapSense_1_fingerThreshold[widget + 1u], 0u);
            #else
                MaxY = CapSense_1_FindMaximum(offset, count, CapSense_1_fingerThreshold[widget + 1u]);
            #endif /* (CapSense_1_IS_DIPLEX_SLIDER) */

            if (MaxY != CapSense_1_MAXIMUM_CENTROID)
            {
                /* X and Y maximums are found = true touch */
                touch = 1u;
                
                /* Calculate Y centroid */
                posY = CapSense_1_CalcCentroid(MaxY, offset, count, 
                            CapSense_1_centroidMult[widget + 1u], CapSense_1_noiseThreshold[widget + 1u]);
                
                /* Calculate X centroid */
                offset = CapSense_1_rawDataIndex[widget];
                count = CapSense_1_numberOfSensors[widget];
                
                posX = CapSense_1_CalcCentroid(MaxX, offset, count, 
                            CapSense_1_centroidMult[widget],CapSense_1_noiseThreshold[widget]);
    
                #if (0u != CapSense_1_TOUCH_PADS_POS_FILTERS_MASK)
                    /* Check if this TP has enabled filters */
                    if (0u != (posFiltersMask & CapSense_1_ANY_POS_FILTER))
                    {
                        /* Calculate position to store filters data */
                        posXIndex  = firstTimeIndex + 1u;
                        posYIndex  = CapSense_1_posFiltersData[widget + 1u];
                        
                        if (0u == CapSense_1_posFiltersData[firstTimeIndex])
                        {
                            /* Init filters */
                            CapSense_1_posFiltersData[posXIndex] = posX;
                            CapSense_1_posFiltersData[posYIndex] = posY;

                            #if((0u != (CapSense_1_MEDIAN_FILTER & \
                                        CapSense_1_TOUCH_PADS_POS_FILTERS_MASK))|| \
                                (0u != (CapSense_1_AVERAGING_FILTER & \
                                        CapSense_1_TOUCH_PADS_POS_FILTERS_MASK)))

                                if ( (0u != (posFiltersMask & CapSense_1_MEDIAN_FILTER)) || 
                                     (0u != (posFiltersMask & CapSense_1_AVERAGING_FILTER)) )
                                {
                                    CapSense_1_posFiltersData[posXIndex + 1u] = posX;
                                    CapSense_1_posFiltersData[posYIndex + 1u] = posY;
                                }
                            #endif /* ((0u != (CapSense_1_MEDIAN_FILTER & \
                                   *           CapSense_1_TOUCH_PADS_POS_FILTERS_MASK)) || \
                                   *    (0u != (CapSense_1_AVERAGING_FILTER & \
                                   *            CapSense_1_TOUCH_PADS_POS_FILTERS_MASK)))
                                   */
                            
                            CapSense_1_posFiltersData[firstTimeIndex] = 1u;
                        }
                        else
                        {
                            /* Do filtering */
                            #if (0u != (CapSense_1_MEDIAN_FILTER & CapSense_1_TOUCH_PADS_POS_FILTERS_MASK))
                                if (0u != (posFiltersMask & CapSense_1_MEDIAN_FILTER))
                                {
                                    tempPos = posX;
                                    posX = (uint8) CapSense_1_MedianFilter(posX,
                                                                      CapSense_1_posFiltersData[posXIndex],
                                                                      CapSense_1_posFiltersData[posXIndex + 1u]);
                                    CapSense_1_posFiltersData[posXIndex + 1u] = 
                                                                             CapSense_1_posFiltersData[posXIndex];
                                    CapSense_1_posFiltersData[posXIndex] = tempPos;
                                    
                                    tempPos = posY;
                                    posY = (uint8) CapSense_1_MedianFilter(posY,
                                                                       CapSense_1_posFiltersData[posYIndex], 
                                                                       CapSense_1_posFiltersData[posYIndex + 1u]);
                                    CapSense_1_posFiltersData[posYIndex + 1u] = 
                                                                             CapSense_1_posFiltersData[posYIndex];
                                    CapSense_1_posFiltersData[posYIndex] = tempPos;
                                }
                                
                            #endif /* (0u != (CapSense_1_MEDIAN_FILTER & \
                                   *          CapSense_1_TOUCH_PADS_POS_FILTERS_MASK))
                                   */

                            #if(0u !=(CapSense_1_AVERAGING_FILTER & CapSense_1_TOUCH_PADS_POS_FILTERS_MASK))
                                if (0u != (posFiltersMask & CapSense_1_AVERAGING_FILTER))
                                {
                                    tempPos = posX;
                                    posX = (uint8) CapSense_1_AveragingFilter(posX,
                                                                       CapSense_1_posFiltersData[posXIndex], 
                                                                       CapSense_1_posFiltersData[posXIndex + 1u]);
                                    CapSense_1_posFiltersData[posXIndex + 1u] = 
                                                                             CapSense_1_posFiltersData[posXIndex];
                                    CapSense_1_posFiltersData[posXIndex] = tempPos;
                                    
                                    tempPos = posY;
                                    posY = (uint8) CapSense_1_AveragingFilter(posY, 
                                                                      CapSense_1_posFiltersData[posYIndex], 
                                                                      CapSense_1_posFiltersData[posYIndex + 1u]);
                                    CapSense_1_posFiltersData[posYIndex + 1u] = 
                                                                            CapSense_1_posFiltersData[posYIndex];
                                    CapSense_1_posFiltersData[posYIndex] = tempPos;
                                }

                            #endif /* (0u != (CapSense_1_AVERAGING_FILTER & \
                                   *           CapSense_1_TOUCH_PADS_POS_FILTERS_MASK))
                                   */

                            #if (0u != (CapSense_1_IIR2_FILTER & CapSense_1_TOUCH_PADS_POS_FILTERS_MASK))
                                if (0u != (posFiltersMask & CapSense_1_IIR2_FILTER))
                                {
                                    posX = (uint8) CapSense_1_IIR2Filter(posX, 
                                                                           CapSense_1_posFiltersData[posXIndex]);
                                    CapSense_1_posFiltersData[posXIndex] = posX;
                                    
                                    posY = (uint8) CapSense_1_IIR2Filter(posY, 
                                                                            CapSense_1_posFiltersData[posYIndex]);
                                    CapSense_1_posFiltersData[posYIndex] = posY;
                                }
                                
                            #endif /* (0u != (CapSense_1_IIR2_FILTER & \
                                   *          CapSense_1_TOUCH_PADS_POS_FILTERS_MASK))
                                   */

                            #if (0u != (CapSense_1_IIR4_FILTER & CapSense_1_TOUCH_PADS_POS_FILTERS_MASK))
                                if (0u != (posFiltersMask & CapSense_1_IIR4_FILTER))
                                {
                                    posX = (uint8) CapSense_1_IIR4Filter((uint16)posX,
                                                                    (uint16)CapSense_1_posFiltersData[posXIndex]);
                                    CapSense_1_posFiltersData[posXIndex] = posX;

                                    posY = (uint8) CapSense_1_IIR4Filter((uint16)posY,
                                                                    (uint16)CapSense_1_posFiltersData[posYIndex]);
                                    CapSense_1_posFiltersData[posYIndex] = posY;
                                }
                                
                            #endif /* (0u != (CapSense_1_IIR4_FILTER & \
                                   *           CapSense_1_TOUCH_PADS_POS_FILTERS_MASK))
                                   */

                            #if (0u != (CapSense_1_JITTER_FILTER & CapSense_1_TOUCH_PADS_POS_FILTERS_MASK))
                                if (0u != (posFiltersMask & CapSense_1_JITTER_FILTER))
                                    {
                                        posX = (uint8) CapSense_1_JitterFilter(posX, 
                                                                            CapSense_1_posFiltersData[posXIndex]);
                                        CapSense_1_posFiltersData[posXIndex] = posX;
                                        
                                        posY = (uint8) CapSense_1_JitterFilter(posY, 
                                                                            CapSense_1_posFiltersData[posYIndex]);
                                        CapSense_1_posFiltersData[posYIndex] = posY;
                                    }
                            #endif /* (0u != (CapSense_1_JITTER_FILTER & \
                                   *           CapSense_1_TOUCH_PADS_POS_FILTERS_MASK))
                                   */
                        }
                    }
                #endif /* (0u != CapSense_1_TOUCH_PADS_POS_FILTERS_MASK) */

                /* Save positions */
                pos[0u] = posX;
                pos[1u] = posY;
            }
        }

        #if (0u != CapSense_1_TOUCH_PADS_POS_FILTERS_MASK)
            if(touch == 0u)
            {
                /* Reset filters */
                if ((posFiltersMask & CapSense_1_ANY_POS_FILTER) != 0u)
                {
                    CapSense_1_posFiltersData[firstTimeIndex] = 0u;
                }
            }
        #endif /* (0u != CapSense_1_TOUCH_PADS_POS_FILTERS_MASK) */
        
        return (touch);
    }
#endif /* (CapSense_1_TOTAL_TOUCH_PADS_COUNT > 0u) */


#if ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_MEDIAN_FILTER)) || \
      (0u != (CapSense_1_POS_FILTERS_MASK & CapSense_1_MEDIAN_FILTER)) || \
      ((CapSense_1_TUNING_METHOD == CapSense_1__TUNING_AUTO)) )
    /*******************************************************************************
    * Function Name: CapSense_1_MedianFilter
    ********************************************************************************
    *
    * Summary:
    *  This is the Median filter function. 
    *  The median filter looks at the three most recent samples and reports the 
    *  median value.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *  x3:  Before previous value.
    *
    * Return:
    *  Returns filtered value.
	*
	* Global Variables:
	*  None.
	*
	* Side Effects:
	*  None
	* 
    *******************************************************************************/
    uint16 CapSense_1_MedianFilter(uint16 x1, uint16 x2, uint16 x3)
    {
        uint16 tmp;
        
        if (x1 > x2)
        {
            tmp = x2;
            x2 = x1;
            x1 = tmp;
        }
        
        if (x2 > x3)
        {
            x2 = x3;
        }
        
        return ((x1 > x2) ? x1 : x2);
    }
#endif /* ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_MEDIAN_FILTER)) || \
      (0u != (CapSense_1_POS_FILTERS_MASK & CapSense_1_MEDIAN_FILTER)) || \
      ((CapSense_1_TUNING_METHOD == CapSense_1__TUNING_AUTO)) ) */


#if ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_AVERAGING_FILTER)) || \
      (0u != (CapSense_1_POS_FILTERS_MASK & CapSense_1_AVERAGING_FILTER)) )
    /*******************************************************************************
    * Function Name: CapSense_1_AveragingFilter
    ********************************************************************************
    *
    * Summary:
    *  This is the Averaging filter function.
    *  The averaging filter looks at the three most recent samples of a position and
    *  reports the averaging value.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *  x3:  Before previous value.
    *
    * Return:
    *  Returns filtered value.
	*
	* Global Variables:
	*  None.
	*
	* Side Effects:
	*  None
	* 
    *******************************************************************************/
    uint16 CapSense_1_AveragingFilter(uint16 x1, uint16 x2, uint16 x3)
    {
        uint32 tmp = ((uint32)x1 + (uint32)x2 + (uint32)x3) / 3u;
        
        return ((uint16) tmp);
    }
#endif /* ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_AVERAGING_FILTER) || \
      (0u != (CapSense_1_POS_FILTERS_MASK & CapSense_1_AVERAGING_FILTER) ) */


#if ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR2_FILTER)) || \
      (0u != (CapSense_1_POS_FILTERS_MASK & CapSense_1_IIR2_FILTER)) )
    /*******************************************************************************
    * Function Name: CapSense_1_IIR2Filter
    ********************************************************************************
    *
    * Summary:
    *  This is the IIR1/2 filter function. IIR1/2 = 1/2current + 1/2previous.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *
    * Return:
    *  Returns filtered value.
	*
	* Global Variables:
	*  None.
	*
	* Side Effects:
	*  None
	* 
    *******************************************************************************/
    uint16 CapSense_1_IIR2Filter(uint16 x1, uint16 x2)
    {
        uint32 tmp;
        
        /* IIR = 1/2 Current Value+ 1/2 Previous Value */
        tmp = (uint32)x1 + (uint32)x2;
        tmp >>= 1u;
    
        return ((uint16) tmp);
    }
#endif /* ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR2_FILTER)) || \
       *    (0u != (CapSense_1_POS_FILTERS_MASK & CapSense_1_IIR2_FILTER)) )
       */


#if ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR4_FILTER)) || \
      (0u != (CapSense_1_POS_FILTERS_MASK & CapSense_1_IIR4_FILTER)) )
    /*******************************************************************************
    * Function Name: CapSense_1_IIR4Filter
    ********************************************************************************
    *
    * Summary:
    *  This is the IIR1/4 filter function. IIR1/4 = 1/4current + 3/4previous.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *
    * Return:
    *  Returns a filtered value.
	*
	* Global Variables:
	*  None.
	*
	* Side Effects:
	*  None
	* 
    *******************************************************************************/
    uint16 CapSense_1_IIR4Filter(uint16 x1, uint16 x2)
    {
        uint32 tmp;
        
        /* IIR = 1/4 Current Value + 3/4 Previous Value */
        tmp = (uint32)x1 + (uint32)x2;
        tmp += ((uint32)x2 << 1u);
        tmp >>= 2u;
        
        return ((uint16) tmp);
    }
#endif /* ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR4_FILTER)) || \
       *    (0u != (CapSense_1_POS_FILTERS_MASK & CapSense_1_IIR4_FILTER)) )
       */


#if ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_JITTER_FILTER)) || \
      (0u != (CapSense_1_POS_FILTERS_MASK & CapSense_1_JITTER_FILTER)) )
    /*******************************************************************************
    * Function Name: uint16 CapSense_1_JitterFilter
    ********************************************************************************
    *
    * Summary:
    *  This is the Jitter filter function.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *
    * Return:
    *  Returns filtered value.
	*
	* Global Variables:
	*  None.
	*
	* Side Effects:
	*  None
	* 
    *******************************************************************************/
    uint16 CapSense_1_JitterFilter(uint16 x1, uint16 x2)
    {
        if (x1 > x2)
        {
            x1--;
        }
        else
        {
            if (x1 < x2)
            {
                x1++;
            }
        }
    
        return x1;
    }
#endif /* ( (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_JITTER_FILTER)) || \
       *    (0u != (CapSense_1_POS_FILTERS_MASK & CapSense_1_JITTER_FILTER)) )
       */


#if (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR8_FILTER))
    /*******************************************************************************
    * Function Name: CapSense_1_IIR8Filter
    ********************************************************************************
    *
    * Summary:
    *  This is the IIR1/8 filter function. IIR1/8 = 1/8current + 7/8previous.
    *  Only applies for raw data.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *
    * Return:
    *  Returns filtered value.
	*
	* Global Variables:
	*  None.
	*
	* Side Effects:
	*  None
	* 
    *******************************************************************************/
    uint16 CapSense_1_IIR8Filter(uint16 x1, uint16 x2)
    {
        uint32 tmp;
        
        /* IIR = 1/8 Current Value + 7/8 Previous Value */
        tmp = (uint32)x1;
        tmp += (((uint32)x2 << 3u) - ((uint32)x2));
        tmp >>= 3u;
    
        return ((uint16) tmp);
    }
#endif /* (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR8_FILTER)) */


#if (0u != (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR16_FILTER))
    /*******************************************************************************
    * Function Name: CapSense_1_IIR16Filter
    ********************************************************************************
    *
    * Summary:
    *  This is the IIR1/16 filter function. IIR1/16 = 1/16current + 15/16previous.
    *  Only applies for raw data.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *
    * Return:
    *  Returns filtered value.
	*
	* Global Variables:
	*  None.
	*
	* Side Effects:
	*  None
	* 
    *******************************************************************************/
    uint16 CapSense_1_IIR16Filter(uint16 x1, uint16 x2)
    {
        uint32 tmp;
        
        /* IIR = 1/16 Current Value + 15/16 Previous Value */
        tmp = (uint32)x1;
        tmp += (((uint32)x2 << 4u) - ((uint32)x2));
        tmp >>= 4u;
        
        return ((uint16) tmp);
    }
#endif /* (CapSense_1_RAW_FILTER_MASK & CapSense_1_IIR16_FILTER) */


#if (0u != (CapSense_1_TOTAL_MATRIX_BUTTONS_COUNT))

    /*******************************************************************************
    * Function Name: CapSense_1_GetMatrixButtonPos
    ********************************************************************************
    *
    * Summary:
    *  Function calculates and returns a touch position (column and row) for the matrix
    *  button widget.
    *
    * Parameters:
    *  widget:  widget number;
    *  pos:     pointer to an array of two uint8, where touch position will be 
    *           stored:
    *           pos[0] - column position;
    *           pos[1] - raw position.
    *
    * Return:
    *  Returns 1 if row and column sensors of matrix button are active, 0 - in other
    *  cases.
	*
	* Global Variables:
	*  CapSense_1_fingerThreshold[ ] – used to store the finger threshold for all widgets.
	*  CapSense_1_sensorSignal[ ] – used to store a difference between the current value of 
	*  raw data and a previous value of the baseline.
	*
	* Side Effects:
	*  None
	* 
    *******************************************************************************/
    uint32 CapSense_1_GetMatrixButtonPos(uint32 widget, uint8* pos)
    {
        uint8 i;
        uint32 retVal = 0u;
        uint16 row_sig_max = 0u;
        uint16 col_sig_max = 0u;
        uint8 row_ind = 0u;
        uint8 col_ind = 0u;

        if (CapSense_1_CheckIsWidgetActive(widget) == 1u)
        {
            /* Find row number with maximal signal value */
            for(i = CapSense_1_rawDataIndex[widget]; i < (CapSense_1_rawDataIndex[widget] + \
                 CapSense_1_numberOfSensors[widget]); i++)
            {
                if (CapSense_1_sensorSignal[i] > col_sig_max)
                {
                    col_ind = i;
                    col_sig_max = CapSense_1_sensorSignal[i];
                }
            }

            /* Find row number with maximal signal value */
            for(i = CapSense_1_rawDataIndex[widget+1u]; i < (CapSense_1_rawDataIndex[widget+1u] + \
                 CapSense_1_numberOfSensors[widget+1u]); i++)
            {
                if (CapSense_1_sensorSignal[i] > row_sig_max)
                {
                    row_ind = i;
                    row_sig_max = CapSense_1_sensorSignal[i];
                }
            }

            if((col_sig_max >= CapSense_1_fingerThreshold[widget]) && \
               (row_sig_max >= CapSense_1_fingerThreshold[widget+1u]))
            {
                pos[0u] = col_ind - CapSense_1_rawDataIndex[widget];
                pos[1u] = row_ind - CapSense_1_rawDataIndex[widget+1u];
                retVal = 1u;
            }
        }
        return (retVal);
    }

#endif /* (0u != (CapSense_1_TOTAL_MATRIX_BUTTONS_COUNT)) */

/*******************************************************************************
* Function Name: CapSense_1_GetWidgetNumber
********************************************************************************
*
* Summary:
*  This API returns the widget number for the sensor.
*
* Parameters:
*  sensor: sensor index. The value of index can be 
*  from 0 to (CapSense_1_TOTAL_SENSOR_COUNT-1).
*
* Return:
*  This API returns the widget number for the sensor. 
*
* Global Variables:
*  CapSense_1_widgetNumber[]  - stores widget numbers.
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint32 CapSense_1_GetWidgetNumber(uint32 sensor)
{
	return((uint32)CapSense_1_widgetNumber[sensor]);
}

/*******************************************************************************
* Function Name: CapSense_1_GetLowBaselineReset
********************************************************************************
*
* Summary:
*  This API returns the low baseline reset threshold value for the  sensor.
*
* Parameters:
*  sensor: sensor index. The value of index can be 
*  from 0 to (CapSense_1_TOTAL_SENSOR_COUNT-1).
*
* Return:
*  low baseline reset threshold value a sensor.
*
* Global Variables:
*  CapSense_1_lowBaselineReset[]  - stores low baseline reset values.
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint8 CapSense_1_GetLowBaselineReset(uint32 sensor)
{
	return(CapSense_1_lowBaselineReset[sensor]);
}

/*******************************************************************************
* Function Name: CapSense_1_GetDebounce
********************************************************************************
*
* Summary:
*  This API returns a debounce value.
*
* Parameters:
*  sensor: sensor index. The value of index can be 
*  from 0 to (CapSense_1_TOTAL_SENSOR_COUNT-1).
*
* Return:
*  Debounce value 
*
* Global Variables:
*  CapSense_1_debounce[]  - stores the debounce value.
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint8 CapSense_1_GetDebounce(uint32 widget)
{
	return(CapSense_1_debounce[widget]);
}

/* [] END OF FILE */
