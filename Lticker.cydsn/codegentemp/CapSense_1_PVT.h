/*******************************************************************************
* File Name: CapSense_1_PVT.h
* Version 2.0
*
* Description:
*  This file provides constants and structure declarations for the
*  CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_CAPSENSE_CSD_PVT_CapSense_1_H)
#define CY_CAPSENSE_CSD_PVT_CapSense_1_H

#include "CapSense_1.h"

#if(0u != CapSense_1_CSHL_API_GENERATE)
	#include "CapSense_1_CSHL.h"
#endif /* (0u != CapSense_1_CSHL_API_GENERATE) */

typedef struct
{
	uint8 pinNumber;
	uint8 portNumber;
	uint8 idacValue;
	uint16 senseClkDiv;
	uint16 sampleClkDiv;
	uint8 avgSamplesNum;
	uint16 calibrationCount;
	uint32 scanResolution;
}CapSense_1_CP_MEASURE_CONFIG;

typedef struct
{
    uint8 *idac1LevelsTbl;
    uint8 *idac2LevelsTbl;
    uint8 *sensetivityTbl;
    uint8 *chargeDivTbl;
    uint8 *modDivTbl;
    const uint8  *widgetNubmersTbl;
    uint32 *resolutionsTbl;
	uint8 const  *rawDataIndex;
	uint8 const *numberOfSensors;
    uint16 (*ptrGetRaw)(uint32 sensor);
	void (*ptrPreScan)(uint32 sensor);
	uint16 (*ptrReadSensorRaw)(uint32 sensor);
    uint32 (*ptrGetBitValue)(const uint8 table[], uint32 position);
	void (*ptrSetBitValue)(uint8 table[], uint32 position, uint32 value);
}CapSense_1_CONFIG_TYPE_POINTERS_P4_v2_0;

typedef struct
{
    uint8 totalScanslotsNum;
	uint8 totalWidgetsNum;
    uint8 totalSensorsNum;
	uint16 sensetivitySeed;
	uint16 hfclkFreq_MHz;
    CapSense_1_CONFIG_TYPE_POINTERS_P4_v2_0 const * pointers;
}CapSense_1_CONFIG_TYPE_P4_v2_0;

#define CapSense_1_AVG_SAMPLES_NUM		(1u)

extern const uint8 CapSense_1_widgetNumber[CapSense_1_TOTAL_SENSOR_COUNT];

/* Global variables and arrays */
extern volatile uint8 CapSense_1_csdStatusVar;
extern volatile uint8 CapSense_1_sensorIndex;

void CapSense_1_PreScan(uint32 sensor);
void CapSense_1_PostScan(uint32 sensor);

__INLINE void CapSense_1_EnableSensor(uint32 sensor);
__INLINE void CapSense_1_DisableSensor(uint32 sensor);

#if (CapSense_1_IS_COMPLEX_SCANSLOTS)
    void CapSense_1_EnableScanSlot(uint32 slot);
    void CapSense_1_DisableScanSlot(uint32 slot);
#else
    #define CapSense_1_EnableScanSlot(slot)   CapSense_1_EnableSensor(slot)
    #define CapSense_1_DisableScanSlot(slot)  CapSense_1_DisableSensor(slot)
#endif  /* End CapSense_1_IS_COMPLEX_SCANSLOTS */

void CapSense_1_EnableShieldElectrode(uint32 pinNumber, uint32 portNumber);

uint32 CapSense_1_GetBitValue(const uint8 table[], uint32 position);
void CapSense_1_SetBitValue(uint8 table[], uint32 position, uint32 value);

/* Find next sensor for One Channel design */
uint8 CapSense_1_FindNextSensor(uint8 snsIndex);

void CapSense_1_SetPinDriveMode(uint32 driveMode, uint32 pinNumber, uint32 portNumber);
void CapSense_1_CalibrateSensor(uint32 sensor, uint32 rawLevel, uint8 idacLevelsTbl[]);
uint16  CapSense_1_GetSensorRaw(uint32 sensor);

void CapSense_1_DisableBaselineIDAC(void);
void CapSense_1_EnableBaselineIDAC(const CapSense_1_CONFIG_TYPE_P4_v2_0 *config);

uint32 CapSense_1_GetLowCp(CapSense_1_CP_MEASURE_CONFIG *config);
uint32 CapSense_1_GetHighCp(const CapSense_1_CP_MEASURE_CONFIG *config);
uint32 CapSense_1_CalibrateIDAC(CapSense_1_CP_MEASURE_CONFIG *config);
uint16 CapSense_1_ScanSensorCp(const CapSense_1_CP_MEASURE_CONFIG *config);

void CapSense_1_ConnectElectrode(uint32 pinNumber, uint32 portNumber);
void CapSense_1_DisconnectElectrode(uint32 pinNumber, uint32 portNumber);

void TunePrescalers_P4_v2_0(CapSense_1_CONFIG_TYPE_P4_v2_0 *config);
void TuneSensitivity_P4_v2_0(CapSense_1_CONFIG_TYPE_P4_v2_0 *config);
void MeasureNoiseEnvelope_P4_v2_0(CapSense_1_CONFIG_TYPE_P4_v2_0 *config, const uint8 sensorNumber, const uint16 *rawData);
void CalculateThresholds_P4_v2_0(CapSense_1_CONFIG_TYPE_P4_v2_0 *config, const uint8 sensorNumber, const uint16 *rawData, const uint8 widget, uint8 *fingerThres, uint8 *noiseThres);
void CalibrateSensors_P4_v2_0(CapSense_1_CONFIG_TYPE_P4_v2_0 *config, uint16 rawLevel);
void CalibrateOneDAC_P4_v2_0(CapSense_1_CONFIG_TYPE_P4_v2_0 *config, uint16 rawLevel, uint32 curSensor, uint8 *idacLevelsTbl);


#endif /* CY_CAPSENSE_CSD_PVT_CapSense_1_H */
