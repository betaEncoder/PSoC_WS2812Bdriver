/*******************************************************************************
* File Name: CapSense_1.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the CapSense CSD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_CapSense_1_H)
#define CY_CAPSENSE_CSD_CapSense_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "core_cm0_psoc4.h"
#include "CyLib.h"

#include "CapSense_1_IP.h"

#include "CapSense_1_SenseClk.h"
#include "CapSense_1_SampleClk.h"

/* Constants set by Customizer */
#define CapSense_1_TOTAL_SENSOR_COUNT            (5u)
#define CapSense_1_TOTAL_SCANSLOT_COUNT          (5u)
#define CapSense_1_TOTAL_IMMUNITY_NUM            (5u)
#define CapSense_1_IS_STREET_FIGHTER             (0u)

/* Define Sensors */
#define CapSense_1_SENSOR_LINEARSLIDER0_E0__LS    (0u)
#define CapSense_1_SENSOR_LINEARSLIDER0_E1__LS    (1u)
#define CapSense_1_SENSOR_LINEARSLIDER0_E2__LS    (2u)
#define CapSense_1_SENSOR_LINEARSLIDER0_E3__LS    (3u)
#define CapSense_1_SENSOR_LINEARSLIDER0_E4__LS    (4u)
/* AMux Cmod, Comparator and Idac Channels definitions */
#define CapSense_1_AMuxCH_CMOD_CHANNEL          (0u)
#define CapSense_1_AMuxCH_CMP_VP_CHANNEL        (1u)
#define CapSense_1_AMuxCH_IDAC_CHANNEL          (2u)


#define CapSense_1_TOTAL_SENSOR_MASK (((CapSense_1_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)	

/* Interrupt handler */
CY_ISR_PROTO(CapSense_1_ISR);

/* ISR Number and Priority to work with CyLib functions */
#define CapSense_1_ISR_NUMBER        (CapSense_1_ISR__INTC_NUMBER)
#define CapSense_1_ISR_PRIORITY      (CapSense_1_ISR__INTC_PRIOR_NUM)

/***************************************
*   Condition compilation parameters
***************************************/

#define CapSense_1_CONNECT_INACTIVE_SNS       (0u)
#define CapSense_1_IS_COMPLEX_SCANSLOTS       (0u)

#define CapSense_1_IDAC_CNT                   (2u)
#define CapSense_1_IDAC1_POLARITY             (0u)
#define CapSense_1_IDAC1_RANGE_VALUE          (0u)
#define CapSense_1_IDAC2_RANGE_VALUE          (0u)

#define CapSense_1_MULTIPLE_FREQUENCY_SET     (1u)
#define CapSense_1_FILTER_ENABLE			    (0u)
#define CapSense_1_PRS_OPTIONS                (0u)

#define CapSense_1_WATER_PROOF                (0u)

#define CapSense_1_TUNING_METHOD              (2u)
#define CapSense_1_TUNER_API_GENERATE         (0u)

#define CapSense_1_CSHL_API_GENERATE          (1u)

#define CapSense_1_CMOD_PREGARGE_OPTION       (1u)
#define CapSense_1_CSH_TANK_PREGARGE_OPTION   (1u)
#define CapSense_1_IS_SHIELD_ENABLE           (0u)
#define CapSense_1_CSH_TANK_ENABLE            (0u)

#define CapSense_1_SHIELD_DELAY               (0u)
#define CapSense_1_AUTOCALIBRATION_ENABLE		(0u)

#define CapSense_1_IS_OVERSAMPLING_EN         (1u)

#define CapSense_1_CSD_4B_PWM_MODE			(0u)
#define CapSense_1_CSD_4B_PWM_COUNT			(0u)

/**************************************
*    Enumerated Types and Parameters
**************************************/

/* Current source definitions */
#define CapSense_1__IDAC_SOURCE 0
#define CapSense_1__IDAC_SINK 1

#define CapSense_1__IDAC_4X 0
#define CapSense_1__IDAC_8X 1

#define CapSense_1__PRS_NONE 0
#define CapSense_1__PRS_8BITS 1
#define CapSense_1__PRS_12BITS 2
#define CapSense_1__PRS_AUTO 3

/* Connection of inactive sensors definitions */
#define CapSense_1__GROUND 0
#define CapSense_1__HIZ_ANALOG 1
#define CapSense_1__SHIELD 2

/* Precharge options definitions */
#define CapSense_1__CAPPRIOBUF 0
#define CapSense_1__CAPPRVREF 1

/* Method of tunning */
#define CapSense_1__TUNING_NONE 0
#define CapSense_1__TUNING_MANUAL 1
#define CapSense_1__TUNING_AUTO 2

/* Dead band PWM modulator options */
#define CapSense_1__PWM_OFF 0
#define CapSense_1__PWM_HIGH 2
#define CapSense_1__PWM_LOW 3


#define CapSense_1_DELAY_EXTRACYCLES_NUM			(9u)
#define CapSense_1_GLITCH_ELIMINATION_TIMEOUT		(5u)
#define CapSense_1_GLITCH_ELIMINATION_CYCLES_CALC	(CapSense_1_GLITCH_ELIMINATION_TIMEOUT * CYDEV_BCLK__SYSCLK__MHZ)

#if(CapSense_1_GLITCH_ELIMINATION_CYCLES_CALC >= CapSense_1_DELAY_EXTRACYCLES_NUM)
	#define CapSense_1_GLITCH_ELIMINATION_CYCLES (CapSense_1_GLITCH_ELIMINATION_CYCLES_CALC -\
													    CapSense_1_DELAY_EXTRACYCLES_NUM)
#else
	#define CapSense_1_GLITCH_ELIMINATION_CYCLES (CapSense_1_GLITCH_ELIMINATION_CYCLES_CALC)
#endif /* (CapSense_1_GLITCH_ELIMINATION_CYCLES_CALC >= CapSense_1_DELAY_EXTRACYCLES_NUM) */

#define CapSense_1_INITIAL_CLK_DIVIDER			(CYDEV_BCLK__HFCLK__KHZ / CYDEV_BCLK__SYSCLK__KHZ)


/* Structure to save registers before going to sleep */
typedef struct
{
    uint8 enableState;
} CapSense_1_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void CapSense_1_Init(void);
void CapSense_1_CsdHwBlockInit(void);
void CapSense_1_Enable(void);
void CapSense_1_Start(void);
void CapSense_1_Stop(void);
void CapSense_1_SaveConfig(void);
void CapSense_1_Sleep(void);
void CapSense_1_RestoreConfig(void);
void CapSense_1_Wakeup(void);
uint32 CapSense_1_IsBusy(void);
void CapSense_1_ScanSensor(uint32 sensor);
void CapSense_1_ScanWidget(uint32 widget);
void CapSense_1_ScanEnabledWidgets(void);
uint16 CapSense_1_ReadSensorRaw(uint32 sensor);
void CapSense_1_WriteSensorRaw(uint32 sensor, uint16 value);
void CapSense_1_ClearSensors(void);
void CapSense_1_SetShieldDelay(uint32 delay);
uint32 CapSense_1_ReadCurrentScanningSensor(void);

uint32 CapSense_1_GetScanResolution(uint32 widget);
uint32 CapSense_1_GetSenseClkDivider(uint32 sensor);
uint32 CapSense_1_GetModulatorClkDivider(uint32 sensor);
uint32 CapSense_1_GetModulationIDAC(uint32 sensor);
uint32 CapSense_1_GetCompensationIDAC(uint32 sensor);
uint32 CapSense_1_GetIDACRange(void);

#if (CapSense_1_TUNING_METHOD != CapSense_1__TUNING_NONE)
	void CapSense_1_SetScanResolution(uint32 widget, uint32 resolution);
    void CapSense_1_SetSenseClkDivider(uint32 sensor, uint32 senseClk);
	void CapSense_1_SetModulatorClkDivider(uint32 sensor, uint32 modulatorClk);
	void CapSense_1_SetModulationIDAC(uint32 sensor, uint32 modIdacValue);
	void CapSense_1_SetCompensationIDAC(uint32 sensor, uint32 compIdacValue);
	void CapSense_1_SetIDACRange(uint32 iDacRange);
#endif /* (CapSense_1_TUNING_METHOD != CapSense_1__TUNING_NONE) */


void CapSense_1_SetDriveModeAllPins(uint32 driveMode);
void CapSense_1_RestoreDriveModeAllPins(void);
void CapSense_1_SetUnscannedSensorState(uint32 sensor, uint32 sensorState);

/***************************************
*           API Constants
***************************************/

/* PWM Resolution */
#define CapSense_1_CNT_MSB_RESOLUTION_8_BITS  (0x00u)
#define CapSense_1_CNT_MSB_RESOLUTION_9_BITS  (0x01u)
#define CapSense_1_CNT_MSB_RESOLUTION_10_BITS (0x03u)
#define CapSense_1_CNT_MSB_RESOLUTION_11_BITS (0x07u)
#define CapSense_1_CNT_MSB_RESOLUTION_12_BITS (0x0Fu)
#define CapSense_1_CNT_MSB_RESOLUTION_13_BITS (0x1Fu)
#define CapSense_1_CNT_MSB_RESOLUTION_14_BITS (0x3Fu)
#define CapSense_1_CNT_MSB_RESOLUTION_15_BITS (0x7Fu)
#define CapSense_1_CNT_MSB_RESOLUTION_16_BITS (0xFFu)

#define CapSense_1_ONE_CYCLE					(0x00010000Lu)

#define CapSense_1_WINDOW_APPEND          	(0xFFFF0000Lu)
#define CapSense_1_RESOLUTION_6_BITS      	(0x003F0000Lu)
#define CapSense_1_RESOLUTION_7_BITS      	(0x007F0000Lu)
#define CapSense_1_RESOLUTION_8_BITS          (0x00FF0000Lu)
#define CapSense_1_RESOLUTION_9_BITS          (0x01FF0000Lu)
#define CapSense_1_RESOLUTION_10_BITS         (0x03FF0000Lu)
#define CapSense_1_RESOLUTION_11_BITS         (0x07FF0000Lu)
#define CapSense_1_RESOLUTION_12_BITS         (0x0FFF0000Lu)
#define CapSense_1_RESOLUTION_13_BITS         (0x1FFF0000Lu)
#define CapSense_1_RESOLUTION_14_BITS         (0x3FFF0000Lu)
#define CapSense_1_RESOLUTION_15_BITS         (0x7FFF0000Lu)
#define CapSense_1_RESOLUTION_16_BITS         (0xFFFF0000Lu)

#define CapSense_1_RESOLUTION_OFFSET  	(16u)
#define CapSense_1_MSB_RESOLUTION_OFFSET  (24u)

/* Software Status Register Bit Masks */
#define CapSense_1_SW_STS_BUSY                (0x01u)
/* Software Control Register Bit Masks */
#define CapSense_1_SW_CTRL_SINGLE_SCAN        (0x80u)

/* Software Control Register Bit Masks for scanning one widget */
#define CapSense_1_SW_CTRL_WIDGET_SCAN        (0x40u)

/* Flag for complex scan slot */
#define CapSense_1_COMPLEX_SS_FLAG            (0x80u)

/* Flag for scanning is complete */
#define CapSense_1_NOT_SENSOR                 (0xFFFFFFFFLu)

/* Number of bits for each pin in PC register. */
#define CapSense_1_PC_PIN_CFG_SIZE		    (0x03u)

/* Number of bits for each pin in HSIOM register. */
#define CapSense_1_HSIOM_PIN_CFG_SIZE	        (0x04u)

/***************************************
*             Registers
***************************************/

#define CapSense_1_CSD_ID_REG             (*(reg32 *)  CapSense_1_CSD_FFB__CSD_ID)
#define CapSense_1_CSD_ID_PTR             ( (reg32 *)  CapSense_1_CSD_FFB__CSD_ID)

#define CapSense_1_CSD_CFG_REG            (*(reg32 *)  CapSense_1_CSD_FFB__CSD_CONFIG)
#define CapSense_1_CSD_CFG_PTR            ( (reg32 *)  CapSense_1_CSD_FFB__CSD_CONFIG)

#define CapSense_1_CSD_IDAC_REG           (*(reg32 *)  CapSense_1_IDAC1_cy_psoc4_idac__CSD_IDAC)
#define CapSense_1_CSD_IDAC_PTR           ( (reg32 *)  CapSense_1_IDAC1_cy_psoc4_idac__CSD_IDAC)

#define CapSense_1_CSD_CNT_REG            (*(reg32 *) CapSense_1_CSD_FFB__CSD_COUNTER)
#define CapSense_1_CSD_CNT_PTR            ( (reg32 *) CapSense_1_CSD_FFB__CSD_COUNTER)

#define CapSense_1_CSD_STAT_REG           (*(reg32 *) CapSense_1_CSD_FFB__CSD_STATUS)
#define CapSense_1_CSD_STAT_PTR           ( (reg32 *) CapSense_1_CSD_FFB__CSD_STATUS)

#define CapSense_1_CSD_INTR_REG           (*(reg32 *) CapSense_1_CSD_FFB__CSD_INTR)
#define CapSense_1_CSD_INTR_PTR           ( (reg32 *) CapSense_1_CSD_FFB__CSD_INTR)

#define CapSense_1_CSD_INTR_SET_REG       (*(reg32 *) CapSense_1_CSD_FFB__CSD_INTR_SET)
#define CapSense_1_CSD_INTR_SET_PTR       ( (reg32 *) CapSense_1_CSD_FFB__CSD_INTR_SET)

#define CapSense_1_CSD_4B_PWM_REG         (*(reg32 *) CapSense_1_CSD_FFB__CSD_PWM)
#define CapSense_1_CSD_4B_PWM_PTR         ( (reg32 *) CapSense_1_CSD_FFB__CSD_PWM)

#define CapSense_1_CSD_TRIM1_REG          (*(reg32 *) CYREG_CSD_TRIM1)
#define CapSense_1_CSD_TRIM1_PTR          ( (reg32 *) CYREG_CSD_TRIM1)

#define CapSense_1_CSD_TRIM2_REG          (*(reg32 *) CYREG_CSD_TRIM2)
#define CapSense_1_CSD_TRIM2_PTR          ( (reg32 *) CYREG_CSD_TRIM2)

#define CapSense_1_SFLASH_CSD_TRIM1_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)
#define CapSense_1_SFLASH_CSD_TRIM1_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)

#define CapSense_1_SFLASH_CSD_TRIM2_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
#define CapSense_1_SFLASH_CSD_TRIM2_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)


/* Port function select */
#define CapSense_1_PORT_SEL0_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL0 )
#define CapSense_1_PORT_SEL0_PTR          ( (reg32 *) CYREG_HSIOM_PORT_SEL0 )

#define CapSense_1_PORT_SEL1_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL1 )
#define CapSense_1_PORT_SEL1_PTR          ( (reg32 *) CYREG_HSIOM_PORT_SEL1 )

#define CapSense_1_PORT_SEL2_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL2 )
#define CapSense_1_PORT_SEL2_PTR          ( (reg32 *) CYREG_HSIOM_PORT_SEL2 )

#define CapSense_1_PORT_SEL3_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL3 )
#define CapSense_1_PORT_SEL3_PTR          ( (reg32 *) CYREG_HSIOM_PORT_SEL3 )

#define CapSense_1_PORT_SEL4_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL4 )
#define CapSense_1_PORT_SEL4_PTR          ( (reg32 *) CYREG_HSIOM_PORT_SEL4 )

#if (0u == CapSense_1_IS_M0S8IOSS_BLOCK)
	
	/* Port DR and PC registers */
	#define CapSense_1_PORT0_DR_REG           (*(reg32 *) CYREG_PRT0_DR )
	#define CapSense_1_PORT0_DR_PTR           ( (reg32 *) CYREG_PRT0_DR )

	#define CapSense_1_PORT1_DR_REG           (*(reg32 *) CYREG_PRT1_DR )
	#define CapSense_1_PORT1_DR_PTR           ( (reg32 *) CYREG_PRT1_DR )

	#define CapSense_1_PORT2_DR_REG           (*(reg32 *) CYREG_PRT2_DR )
	#define CapSense_1_PORT2_DR_PTR           ( (reg32 *) CYREG_PRT2_DR )

	#define CapSense_1_PORT3_DR_REG           (*(reg32 *) CYREG_PRT3_DR )
	#define CapSense_1_PORT3_DR_PTR           ( (reg32 *) CYREG_PRT3_DR )

	#define CapSense_1_PORT4_DR_REG           (*(reg32 *) CYREG_PRT4_DR )
	#define CapSense_1_PORT4_DR_PTR           ( (reg32 *) CYREG_PRT4_DR )

	/* Port DR and PC registers */
	#define CapSense_1_PORT0_PC_REG           (*(reg32 *) CYREG_PRT0_PC )
	#define CapSense_1_PORT0_PC_PTR           ( (reg32 *) CYREG_PRT0_PC )

	#define CapSense_1_PORT1_PC_REG           (*(reg32 *) CYREG_PRT1_PC )
	#define CapSense_1_PORT1_PC_PTR           ( (reg32 *) CYREG_PRT1_PC )

	#define CapSense_1_PORT2_PC_REG           (*(reg32 *) CYREG_PRT2_PC )
	#define CapSense_1_PORT2_PC_PTR           ( (reg32 *) CYREG_PRT2_PC )

	#define CapSense_1_PORT3_PC_REG           (*(reg32 *) CYREG_PRT3_PC )
	#define CapSense_1_PORT3_PC_PTR           ( (reg32 *) CYREG_PRT3_PC )

	#define CapSense_1_PORT4_PC_REG           (*(reg32 *) CYREG_PRT4_PC )
	#define CapSense_1_PORT4_PC_PTR           ( (reg32 *) CYREG_PRT4_PC )
	
    #define CapSense_1_CMOD_CONNECTION_REG        (CapSense_1_PORT_SEL4_REG)
    #define CapSense_1_CMOD_PORT_PC_REG           (CapSense_1_PORT4_PC_REG)
    #define CapSense_1_CMOD_PORT_DR_REG           (CapSense_1_PORT4_DR_REG)
	
	#define CapSense_1_CTANK_CONNECTION_REG        (CapSense_1_PORT_SEL4_REG)
    #define CapSense_1_CTANK_PORT_PC_REG           (CapSense_1_PORT4_PC_REG)
    #define CapSense_1_CTANK_PORT_DR_REG           (CapSense_1_PORT4_DR_REG)
#else
		
	/* Port DR and PC registers */
	#define CapSense_1_PORT0_DR_REG           (*(reg32 *) CYREG_GPIO_PRT0_DR )
	#define CapSense_1_PORT0_DR_PTR           ( (reg32 *) CYREG_GPIO_PRT0_DR )

	#define CapSense_1_PORT1_DR_REG           (*(reg32 *) CYREG_GPIO_PRT1_DR )
	#define CapSense_1_PORT1_DR_PTR           ( (reg32 *) CYREG_GPIO_PRT1_DR )

	#define CapSense_1_PORT2_DR_REG           (*(reg32 *) CYREG_GPIO_PRT2_DR )
	#define CapSense_1_PORT2_DR_PTR           ( (reg32 *) CYREG_GPIO_PRT2_DR )

	#define CapSense_1_PORT3_DR_REG           (*(reg32 *) CYREG_GPIO_PRT3_DR )
	#define CapSense_1_PORT3_DR_PTR           ( (reg32 *) CYREG_GPIO_PRT3_DR )

	#define CapSense_1_PORT4_DR_REG           (*(reg32 *) CYREG_GPIO_PRT4_DR )
	#define CapSense_1_PORT4_DR_PTR           ( (reg32 *) CYREG_GPIO_PRT4_DR )

	/* Port DR and PC registers */
	#define CapSense_1_PORT0_PC_REG           (*(reg32 *) CYREG_GPIO_PRT0_PC )
	#define CapSense_1_PORT0_PC_PTR           ( (reg32 *) CYREG_GPIO_PRT0_PC )

	#define CapSense_1_PORT1_PC_REG           (*(reg32 *) CYREG_GPIO_PRT1_PC )
	#define CapSense_1_PORT1_PC_PTR           ( (reg32 *) CYREG_GPIO_PRT1_PC )

	#define CapSense_1_PORT2_PC_REG           (*(reg32 *) CYREG_GPIO_PRT2_PC )
	#define CapSense_1_PORT2_PC_PTR           ( (reg32 *) CYREG_GPIO_PRT2_PC )

	#define CapSense_1_PORT3_PC_REG           (*(reg32 *) CYREG_GPIO_PRT3_PC )
	#define CapSense_1_PORT3_PC_PTR           ( (reg32 *) CYREG_GPIO_PRT3_PC )

	#define CapSense_1_PORT4_PC_REG           (*(reg32 *) CYREG_GPIO_PRT4_PC )
	#define CapSense_1_PORT4_PC_PTR           ( (reg32 *) CYREG_GPIO_PRT4_PC )
	
    #define CapSense_1_CMOD_CONNECTION_REG        (CapSense_1_PORT_SEL0_REG)
    #define CapSense_1_CMOD_PORT_PC_REG           (CapSense_1_PORT0_PC_REG)
    #define CapSense_1_CMOD_PORT_DR_REG           (CapSense_1_PORT0_DR_REG)
	
	#define CapSense_1_CTANK_CONNECTION_REG        (CapSense_1_PORT_SEL0_REG)
    #define CapSense_1_CTANK_PORT_PC_REG           (CapSense_1_PORT0_PC_REG)
    #define CapSense_1_CTANK_PORT_DR_REG           (CapSense_1_PORT0_DR_REG)
#endif /* (0u == CapSense_1_IS_M0S8IOSS_BLOCK) */



/***************************************
*       Register Constants
***************************************/

/* Port configuration defines */
#define CapSense_1_CSD_HSIOM_MASK             (0x0000000FLu)
#define CapSense_1_CSD_SENSE_PORT_MODE        (0x00000004Lu)
#define CapSense_1_CSD_SHIELD_PORT_MODE       (0x00000005Lu)

#define CapSense_1_CSD_PIN_MODE_MASK          (0x00000007Lu)
#define CapSense_1_CSD_PIN_DRIVE_MASK         (0x00000001Lu)


#if (0u == CapSense_1_M0S8CSD_BLOCK_VER)
	#define CapSense_1_CSD_CMOD_CONNECTION_MASK   (0x00000F00Lu)
	#define CapSense_1_CSD_CMOD_TO_AMUXBUS_A      (0x00000600Lu)
	#define CapSense_1_CSD_CMOD_TO_AMUXBUS_B      (0x00000700Lu)
	
	#define CapSense_1_CSD_CTANK_CONNECTION_MASK  (0x0000F000Lu)
	#define CapSense_1_CSD_CTANK_TO_AMUXBUS_A     (0x00006000Lu)
	#define CapSense_1_CSD_CTANK_TO_AMUXBUS_B     (0x00007000Lu)
	
	#define  CapSense_1_CSD_CMOD_PC_MASK          (0x000001C0Lu)
	#define  CapSense_1_CSD_CTANK_PC_MASK         (0x00000E00Lu)

	#define  CapSense_1_CMOD_PC_STRONG_MODE       (0x00000180Lu)
	#define  CapSense_1_CMOD_PC_HIGH_Z_MODE       (0x00000000Lu)

	#define  CapSense_1_CTANK_PC_STRONG_MODE      (0x00000C00Lu)
	#define  CapSense_1_CTANK_PC_HIGH_Z_MODE      (0x00000000Lu)

	#define  CapSense_1_CMOD_DR_VSSIO 			(0x00000004Lu)
	#define  CapSense_1_CMOD_DR_VDDIO				(0x00000000Lu)
	#define  CapSense_1_CMOD_DR_MASK				(0x00000004Lu)

	#define  CapSense_1_CTANK_DR_VSSIO 			(0x00000008Lu)
	#define  CapSense_1_CTANK_DR_VDDIO			(0x00000000Lu)
	#define  CapSense_1_CTANK_DR_MASK 			(0x00000008Lu)
#else
	#define CapSense_1_CSD_CMOD_CONNECTION_MASK   (0x000F0000Lu)
	#define CapSense_1_CSD_CMOD_TO_AMUXBUS_A      (0x00060000Lu)
	#define CapSense_1_CSD_CMOD_TO_AMUXBUS_B      (0x00070000Lu)
	
	#define CapSense_1_CSD_CTANK_CONNECTION_MASK  (0x00000F00Lu)
	#define CapSense_1_CSD_CTANK_TO_AMUXBUS_A     (0x00000600Lu)
	#define CapSense_1_CSD_CTANK_TO_AMUXBUS_B     (0x00000700Lu)
	
	#define  CapSense_1_CSD_CMOD_PC_MASK          (0x00007000Lu)
	#define  CapSense_1_CSD_CTANK_PC_MASK         (0x000001C0Lu)

	#define  CapSense_1_CMOD_PC_STRONG_MODE       (0x00006000Lu)
	#define  CapSense_1_CMOD_PC_HIGH_Z_MODE       (0x00000000Lu)

	#define  CapSense_1_CTANK_PC_STRONG_MODE      (0x00000180Lu)
	#define  CapSense_1_CTANK_PC_HIGH_Z_MODE      (0x00000000Lu)

	#define  CapSense_1_CMOD_DR_VSSIO 			(0x00000010Lu)
	#define  CapSense_1_CMOD_DR_VDDIO				(0x00000000Lu)
	#define  CapSense_1_CMOD_DR_MASK				(0x00000010Lu)

	#define  CapSense_1_CTANK_DR_VSSIO 			(0x00000004Lu)
	#define  CapSense_1_CTANK_DR_VDDIO			(0x00000000Lu)
	#define  CapSense_1_CTANK_DR_MASK 			(0x00000004Lu)
#endif  /* (0u == CapSense_1_M0S8CSD_BLOCK_VER) */


#define  CapSense_1_CMOD_PIN_NUMBER			(CapSense_1_Cmod__0__SHIFT)
#define  CapSense_1_CMOD_PRT_NUMBER			(CapSense_1_Cmod__0__PORT)

#if(0u != CapSense_1_CSH_TANK_ENABLE)
	#define  CapSense_1_CTANK_PIN_NUMBER			(CapSense_1_Csh_tank__0__SHIFT)
	#define  CapSense_1_CTANK_PRT_NUMBER			(CapSense_1_Csh_tank__0__PORT)
#endif /* (0u != CapSense_1_CSH_TANK_ENABLE) */	


/* ID register fields position */
#define CapSense_1_CSD_ID_ID__POS              (0x00u)
#define CapSense_1_CSD_ID_REV__POS             (0x10u)

#define CapSense_1_CSD_ID_ID                   (0xFFLu << CapSense_1_CSD_ID_ID__POS)
#define CapSense_1_CSD_ID_REV                  (0xFFLu << CapSense_1_CSD_ID_REV__POS)


/* CSD_CONFIG register fields position */
#define CapSense_1_CSD_CFG_DSI_SAMPLE_EN_POS  (0x00u)
#define CapSense_1_CSD_CFG_SAMPLE_SYNC_POS    (0x01u)
#define	CapSense_1_CSD_CFG_FILTER_EN_POS		(0x03u)
#define CapSense_1_CSD_CFG_PRS_CLEAR_POS      (0x05u)
#define CapSense_1_CSD_CFG_PRS_SELECT_POS     (0x06u)
#define CapSense_1_CSD_CFG_PRS_12_8_POS       (0x07u)
#define CapSense_1_CSD_CFG_DSI_SENSE_EN_POS   (0x08u)
#define CapSense_1_CSD_CFG_SHIELD_DELAY_POS   (0x09u)
#define CapSense_1_CSD_CFG_SENSE_COMP_BW_POS  (0x0Bu)
#define CapSense_1_CSD_CFG_SENSE_EN_POS       (0x0Cu)
#define CapSense_1_CSD_CFG_REFBUF_EN_POS      (0x0Du)
#define CapSense_1_CSD_CFG_CHARGE_IO_POS      (0x0Eu)
#define CapSense_1_CSD_CFG_COMP_PIN_POS       (0x0Fu)
#define CapSense_1_CSD_CFG_POLARITY_POS       (0x10u)
#define CapSense_1_CSD_CFG_MUTUAL_CAP_POS     (0x12u)
#define CapSense_1_CSD_CFG_SENSE_COMP_EN_POS  (0x13u)
#define CapSense_1_CSD_CFG_REFBUF_OUTSEL_POS  (0x15u)
#define CapSense_1_CSD_CFG_SENSE_INSEL_POS    (0x16u)
#define CapSense_1_CSD_REFBUF_DRV_POS			(0x17u)
#define CapSense_1_CSD_CFG_DDFTSEL_POS		(0x1Au)
#define CapSense_1_CSD_CFG_ADFTEN_POS         (0x1Du)
#define CapSense_1_CSD_CFG_DDFTCOMP_POS       (0x1Eu)
#define CapSense_1_CSD_CFG_ENABLE_POS         (0x1Fu)


/* CSD_STATUS register fields position */
#define CapSense_1_CSD_STAT_CSD_CHARGE_POS    (0x00u)
#define CapSense_1_CSD_STAT_CSD_SENSE_POS     (0x01u)
#define CapSense_1_CSD_STAT_COMP_OUT_POS      (0x02u)
#define CapSense_1_CSD_STAT_SAMPLE_POS        (0x03u)


/* CSD_IDAC control register fields position */
#define CapSense_1_CSD_IDAC1_MODE_MASK_POS		(0x08u)
#define CapSense_1_CSD_IDAC1_MODE_FIXED_POS		(0x08u)
#define CapSense_1_CSD_IDAC1_MODE_VARIABLE_POS	(0x08u)
#define CapSense_1_CSD_IDAC1_MODE_DSI_POS			(0x08u)
#define CapSense_1_CSD_IDAC1_RANGE_8X_POS			(0x0Au)
#define CapSense_1_CSD_IDAC1_DATA_MASK_POS		(0x00u)

#define CapSense_1_CSD_IDAC2_MODE_MASK_POS		(0x18u)
#define CapSense_1_CSD_IDAC2_MODE_FIXED_POS		(0x18u)
#define CapSense_1_CSD_IDAC2_MODE_VARIABLE_POS	(0x18u)
#define CapSense_1_CSD_IDAC2_MODE_DSI_POS			(0x18u)
#define CapSense_1_CSD_IDAC2_RANGE_8X_POS			(0x1Au)
#define CapSense_1_CSD_IDAC2_DATA_MASK_POS		(0x10u)


/* CSD_COUNTER register fields position */
#define CapSense_1_CSD_CNT_COUNTER_POS        (0x00u)
#define CapSense_1_CSD_CNT_PERIOD_POS         (0x10u)


/* CSD_CONFIRG register definitions */
#define CapSense_1_CSD_CFG_DSI_SAMPLE_EN       (0x01Lu << CapSense_1_CSD_CFG_DSI_SAMPLE_EN_POS)
#define CapSense_1_CSD_CFG_SAMPLE_SYNC         (0x01Lu << CapSense_1_CSD_CFG_SAMPLE_SYNC_POS)
#define	CapSense_1_CSD_CFG_FILTER_EN			 (0x01Lu << CapSense_1_CSD_CFG_FILTER_EN_POS)
#define CapSense_1_CSD_CFG_PRS_CLEAR           (0x01Lu << CapSense_1_CSD_CFG_PRS_CLEAR_POS)
#define CapSense_1_CSD_CFG_PRS_SELECT          (0x01Lu << CapSense_1_CSD_CFG_PRS_SELECT_POS)
#define CapSense_1_CSD_CFG_PRS_12_8            (0x01Lu << CapSense_1_CSD_CFG_PRS_12_8_POS)
#define CapSense_1_CSD_CFG_DSI_SENSE_EN        (0x01Lu << CapSense_1_CSD_CFG_DSI_SENSE_EN_POS)
#define CapSense_1_CSD_CFG_SHIELD_DELAY_MASK   (0x03Lu << CapSense_1_CSD_CFG_SHIELD_DELAY_POS)
#define CapSense_1_CSD_CFG_SENSE_COMP_BW       (0x01Lu << CapSense_1_CSD_CFG_SENSE_COMP_BW_POS)
#define CapSense_1_CSD_CFG_SENSE_EN            (0x01Lu << CapSense_1_CSD_CFG_SENSE_EN_POS)
#define CapSense_1_CSD_CFG_REFBUF_EN           (0x01Lu << CapSense_1_CSD_CFG_REFBUF_EN_POS)
#define CapSense_1_CSD_CFG_CHARGE_IO           (0x01Lu << CapSense_1_CSD_CFG_CHARGE_IO_POS)
#define CapSense_1_CSD_CFG_COMP_PIN_CH2   	 (0x01Lu << CapSense_1_CSD_CFG_COMP_PIN_POS)
#define CapSense_1_CSD_CFG_POLARITY_VDDIO      (0x01Lu << CapSense_1_CSD_CFG_POLARITY_POS)
#define CapSense_1_CSD_CFG_MUTUAL_CAP          (0x01Lu << CapSense_1_CSD_CFG_MUTUAL_CAP_POS)
#define CapSense_1_CSD_CFG_SENSE_COMP_EN       (0x01Lu << CapSense_1_CSD_CFG_SENSE_COMP_EN_POS)
#define CapSense_1_CSD_CFG_REFBUF_OUTSEL       (0x01Lu << CapSense_1_CSD_CFG_REFBUF_OUTSEL_POS)
#define CapSense_1_CSD_CFG_SENSE_INSEL         (0x01Lu << CapSense_1_CSD_CFG_SENSE_INSEL_POS)
#define CapSense_1_CSD_REFBUF_DRV_MASK		 (0x03Lu << CapSense_1_CSD_REFBUF_DRV_POS)
#define CapSense_1_CSD_REFBUF_DRV_LOW			 (0x01Lu << CapSense_1_CSD_REFBUF_DRV_POS)
#define CapSense_1_CSD_REFBUF_DRV_MEDIUM		 (0x02Lu << CapSense_1_CSD_REFBUF_DRV_POS)
#define CapSense_1_CSD_REFBUF_DRV_HIGH		 (0x03Lu << CapSense_1_CSD_REFBUF_DRV_POS)
#define CapSense_1_CSD_CFG_DDFTSEL_MASK        (0x07Lu << CapSense_1_CSD_CFG_DDFTSEL_POS)
#define CapSense_1_CSD_CFG_ADFTEN              (0x01Lu << CapSense_1_CSD_CFG_ADFTEN_POS)
#define CapSense_1_CSD_CFG_DDFTCOMP_MASK       (0x03Lu << CapSense_1_CSD_CFG_DDFTCOMP_POS)
#define CapSense_1_CSD_CFG_DDFTCOMP_REFCOMP    (0x01Lu << CapSense_1_CSD_CFG_DDFTCOMP_POS)
#define CapSense_1_CSD_CFG_DDFTCOMP_SENSECOMP  (0x02Lu << CapSense_1_CSD_CFG_DDFTCOMP_POS)
#define CapSense_1_CSD_CFG_ENABLE              (0x01Lu << CapSense_1_CSD_CFG_ENABLE_POS)


/* CSD_STATUS register definitions */
#define CapSense_1_CSD_STAT_CSD_CHARGE         (0x01Lu << CapSense_1_CSD_STAT_CSD_CHARGE_POS)
#define CapSense_1_CSD_STAT_CSD_SENSE          (0x01Lu << CapSense_1_CSD_STAT_CSD_SENSE_POS)
#define CapSense_1_CSD_STAT_COMP_OUT           (0x01Lu << CapSense_1_CSD_STAT_COMP_OUT_POS)
#define CapSense_1_CSD_STAT_SAMPLE             (0x01Lu << CapSense_1_CSD_STAT_SAMPLE_POS)

/* CSD_IDAC control register definitions */
#define CapSense_1_CSD_IDAC1_MODE_MASK          (0x03Lu << CapSense_1_CSD_IDAC1_MODE_MASK_POS)
#define CapSense_1_CSD_IDAC1_MODE_FIXED         (0x01Lu << CapSense_1_CSD_IDAC1_MODE_FIXED_POS)
#define CapSense_1_CSD_IDAC1_MODE_VARIABLE      (0x02Lu << CapSense_1_CSD_IDAC1_MODE_VARIABLE_POS)
#define CapSense_1_CSD_IDAC1_MODE_DSI           (0x03Lu << CapSense_1_CSD_IDAC1_MODE_DSI_POS)
#define CapSense_1_CSD_IDAC1_RANGE_8X           (0x01Lu << CapSense_1_CSD_IDAC1_RANGE_8X_POS)
#define CapSense_1_CSD_IDAC1_DATA_MASK          (0xFFLu << CapSense_1_CSD_IDAC1_DATA_MASK_POS)

#define CapSense_1_CSD_IDAC2_MODE_MASK          (0x03Lu << CapSense_1_CSD_IDAC2_MODE_MASK_POS)
#define CapSense_1_CSD_IDAC2_MODE_FIXED         (0x01Lu << CapSense_1_CSD_IDAC2_MODE_FIXED_POS)
#define CapSense_1_CSD_IDAC2_MODE_VARIABLE      (0x02Lu << CapSense_1_CSD_IDAC2_MODE_VARIABLE_POS)
#define CapSense_1_CSD_IDAC2_MODE_DSI           (0x03Lu << CapSense_1_CSD_IDAC2_MODE_DSI_POS)
#define CapSense_1_CSD_IDAC2_RANGE_8X           (0x01Lu << CapSense_1_CSD_IDAC2_RANGE_8X_POS)
#define CapSense_1_CSD_IDAC2_DATA_MASK          (0x7FLu << CapSense_1_CSD_IDAC2_DATA_MASK_POS)

#define CapSense_1_CSD_IDAC2_DATA_OFFSET        (16u)

#define CapSense_1_CSD_IDAC1_TRIM_MASK          (0xFFFFFFF0u)
#define CapSense_1_CSD_IDAC2_TRIM_MASK          (0xFFFFFF0Fu)

#define CapSense_1_CSFLASH_TRIM_IDAC1_MASK      (0x0Fu)
#define CapSense_1_CSFLASH_TRIM_IDAC2_MASK      (0xF0)

#define CapSense_1_CSD_4B_PWM_MODE_OFFSET		  (4u)
#define CapSense_1_CSD_4B_PWM_MODE_DEFAULT      (CapSense_1_CSD_4B_PWM_MODE << CapSense_1_CSD_4B_PWM_MODE_OFFSET)

#define CapSense_1_CSD_4B_PWM_COUNT_MASK		  (0x0000000Fu)
#define CapSense_1_CSD_4B_PWM_MODE_MASK		  (0x00000030u)


#define CapSense_1_CSD_IDAC_PRECHARGE_CONFIG	  (CapSense_1_CSD_IDAC1_MODE_FIXED |\
													   CapSense_1_PRECHARGE_IDAC1_VAL)

/* CSD_COUNTER register definitions */
#define CapSense_1_CSD_CNT_COUNTER             (0xFFLu << CapSense_1_CSD_CNT_COUNTER_POS )
#define CapSense_1_CSD_CNT_PERIOD              (0xFFLu << CapSense_1_CSD_CNT_PERIOD_POS)


#define CapSense_1_CSD_PRS_8_BIT                (0x00000000u)
#define CapSense_1_CSD_PRS_12_BIT               (CapSense_1_CSD_CFG_PRS_12_8)
#define	CapSense_1_PRS_MODE_MASK				  (CapSense_1_CSD_CFG_PRS_12_8)

/***************************************
*    Initial Parameter Constants
***************************************/

#if (0u != CapSense_1_FILTER_ENABLE)
    #define CapSense_1_DEFAULT_FILTER_STATE    (CapSense_1_CSD_CFG_FILTER_EN)
	
#else
	#define CapSense_1_DEFAULT_FILTER_STATE	 (0u)
	
#endif /* (CapSense_1_PRS_OPTIONS == CapSense_1_PRS_8BITS) */

#define	CapSense_1_DEFAULT_CSD_4B_PWM_CONFIG 	 (CapSense_1_CSD_4B_PWM_MODE_DEFAULT | CapSense_1_CSD_4B_PWM_COUNT)

/* Set PRS */
#if (CapSense_1_PRS_OPTIONS == CapSense_1__PRS_8BITS)
    #define CapSense_1_DEFAULT_MODULATION_MODE    CapSense_1_CSD_CFG_PRS_SELECT

#elif (CapSense_1_PRS_OPTIONS == CapSense_1__PRS_12BITS)
    #define CapSense_1_DEFAULT_MODULATION_MODE	CapSense_1_CSD_CFG_PRS_12_8 |\
														CapSense_1_CSD_CFG_PRS_SELECT
#else
	#define CapSense_1_DEFAULT_MODULATION_MODE	(0u)
#endif /* (CapSense_1_PRS_OPTIONS == CapSense_1_PRS_8BITS) */

/* Set IDAC ranges */
#if (CapSense_1_IDAC1_RANGE_VALUE == CapSense_1__IDAC_8X)
    #define CapSense_1_DEFAULT_IDAC1_RANGE    CapSense_1_CSD_IDAC1_RANGE_8X
    #define CapSense_1_DEFAULT_IDAC2_RANGE    CapSense_1_CSD_IDAC2_RANGE_8X
#else
    #define CapSense_1_DEFAULT_IDAC1_RANGE    (0u)
    #define CapSense_1_DEFAULT_IDAC2_RANGE    (0u)
#endif /* (CapSense_1_IDAC1_RANGE_VALUE == CapSense_1_IDAC_RANGE_8X) */

/* Set IDAC polarity */
#if(CapSense_1_IDAC1_POLARITY == CapSense_1__IDAC_SINK)

    #define CapSense_1_DEFAULT_IDAC_POLARITY	 CapSense_1_CSD_CFG_POLARITY_VDDIO
	#define CapSense_1_CMOD_DR_CONFIG			 CapSense_1_CMOD_DR_VDDIO	
	#define CapSense_1_CTANK_DR_CONFIG	     CapSense_1_CTANK_DR_VDDIO
#else

    #define CapSense_1_DEFAULT_IDAC_POLARITY	 (0u)
	#define CapSense_1_CMOD_DR_CONFIG			 CapSense_1_CMOD_DR_VSSIO	
	#define CapSense_1_CTANK_DR_CONFIG	     CapSense_1_CTANK_DR_VSSIO 
#endif /* (CapSense_1_IDAC_OPTIONS == CapSense_1_IDAC_SINK) */

#define CapSense_1_SNS_GROUND_CONNECT       (6u)
#define CapSense_1_SNS_HIZANALOG_CONNECT    (0u)

/* Inactive sensors connection configuration */
#if (CapSense_1_CONNECT_INACTIVE_SNS == CapSense_1__GROUND)
    #define CapSense_1_CSD_INACTIVE_CONNECT       (CapSense_1_SNS_GROUND_CONNECT)
#else
    #define CapSense_1_CSD_INACTIVE_CONNECT       (CapSense_1_SNS_HIZANALOG_CONNECT)
#endif /* CapSense_1_CONNECT_INACTIVE_SNS == CapSense_1__GROUND */

#if(CapSense_1_IS_SHIELD_ENABLE)
    #define CapSense_1_SHIELD_PORT_NUMBER CapSense_1_Shield__PORT
    #define CapSense_1_SHIELD_PIN_NUMBER  CapSense_1_Shield__SHIFT
#endif /* (CapSense_1_IS_SHIELD_ENABLE) */

/* Defining default CSD configuration according to settings in customizer. */
#define CapSense_1_DEFAULT_CSD_CONFIG             (CapSense_1_DEFAULT_FILTER_STATE |\
														 CapSense_1_DEFAULT_MODULATION_MODE |\
                                                         CapSense_1_CSD_CFG_SENSE_COMP_BW |\
                                                         CapSense_1_DEFAULT_IDAC_POLARITY |\
                                                         CapSense_1_CSD_CFG_REFBUF_OUTSEL |\
                                                         CapSense_1_CSD_REFBUF_DRV_HIGH)

#define CapSense_1_CSD_CONFIG_MASK				(CapSense_1_CSD_CFG_FILTER_EN |\
														 CapSense_1_CSD_CFG_PRS_SELECT |\
														 CapSense_1_CSD_CFG_PRS_12_8 |\
														 CapSense_1_CSD_CFG_SENSE_COMP_BW |\
														 CapSense_1_CSD_CFG_REFBUF_EN |\
														 CapSense_1_CSD_CFG_REFBUF_OUTSEL |\
														 CapSense_1_CSD_CFG_POLARITY_VDDIO |\
														 CapSense_1_CSD_CFG_REFBUF_OUTSEL  |\
														 CapSense_1_CSD_REFBUF_DRV_MASK) 


/* Defining the default IDACs configuration according to settings in customizer. */
#if (CapSense_1_IDAC_CNT == 1u)
	#define CapSense_1_DEFAULT_CSD_IDAC_CONFIG        (CapSense_1_CSD_IDAC1_MODE_VARIABLE |\
	                                                         CapSense_1_DEFAULT_IDAC1_RANGE)
#else
	#define CapSense_1_DEFAULT_CSD_IDAC_CONFIG        (CapSense_1_CSD_IDAC1_MODE_VARIABLE |\
	                                                         CapSense_1_CSD_IDAC2_MODE_FIXED |\
	                                                         CapSense_1_DEFAULT_IDAC1_RANGE |\
	                                                         CapSense_1_DEFAULT_IDAC2_RANGE)
#endif /* (CapSense_1_IDAC_CNT == 1u) */

/* Defining mask intended for clearing bits related to pre-charging options. */
#define CapSense_1_PRECHARGE_CONFIG_MASK			(CapSense_1_CSD_CFG_REFBUF_EN |\
														 CapSense_1_CSD_CFG_CHARGE_IO |\
														 CapSense_1_CSD_CFG_COMP_PIN_CH2  |\
														 CapSense_1_CSD_CFG_REFBUF_OUTSEL)

/* Cmod precharge mode configuration */
#if(CapSense_1_CMOD_PREGARGE_OPTION == CapSense_1__CAPPRVREF)

	#define CapSense_1_CMOD_PRECHARGE_CONFIG 		(CapSense_1_CSD_CFG_REFBUF_EN |\
														 CapSense_1_CSD_CFG_COMP_PIN_CH2)
														 
#else

	#define CapSense_1_CMOD_PRECHARGE_CONFIG 		(CapSense_1_CSD_CFG_REFBUF_OUTSEL |\
														 CapSense_1_CSD_CFG_REFBUF_EN |\
														 CapSense_1_CSD_CFG_CHARGE_IO)
														 
#endif /* (CapSense_1_CMOD_PREGARGE_OPTION == CapSense_1__CAPPRVREF) */


/* Ctank precharge mode configuration */
#if(CapSense_1_CSH_TANK_PREGARGE_OPTION == CapSense_1__CAPPRVREF)
		
	#if(0u != CapSense_1_IS_SHIELD_ENABLE)
		#define  CapSense_1_CTANK_PRECHARGE_CONFIG	(CapSense_1_CSD_CFG_REFBUF_EN |\
															 CapSense_1_CSD_CFG_PRS_CLEAR |\
															 CapSense_1_CSD_CFG_REFBUF_OUTSEL)
	#else
		#define  CapSense_1_CTANK_PRECHARGE_CONFIG	(CapSense_1_CSD_CFG_REFBUF_OUTSEL |\
															 CapSense_1_CSD_CFG_PRS_CLEAR)
	#endif /* (0u != CapSense_1_IS_SHIELD_ENABLE) */
	
#else

	#define  CapSense_1_CTANK_PRECHARGE_CONFIG	(CapSense_1_CSD_CFG_REFBUF_OUTSEL |\
														 CapSense_1_CSD_CFG_REFBUF_EN |\
														 CapSense_1_CSD_CFG_CHARGE_IO |\
														 CapSense_1_CSD_CFG_PRS_CLEAR |\
														 CapSense_1_CSD_CFG_COMP_PIN_CH2)
#endif /* (CapSense_1_CSH_TANK_PREGARGE_OPTION == CapSense_1__CAPPRIOBUF) */

/* SmartSense functions */
#if (CapSense_1_TUNING_METHOD == CapSense_1__TUNING_AUTO)
    extern uint8 CapSense_1_lowLevelTuningDone;
    extern void CapSense_1_AutoTune(void);
#endif /* (CapSense_1_TUNING_METHOD == CapSense_1__TUNING_AUTO) */

extern uint16 CapSense_1_sensorRaw[CapSense_1_TOTAL_SENSOR_COUNT];

#define CapSense_1_MAX_UINT_8					(0xFFu)
#define CapSense_1_MAX_UINT_16				(0xFFFFu)
#define CapSense_1_MAX_UINT_32				(0xFFFFFFFFLu)

/***************************************************
*    Obsolete Names (will be removed in future)
***************************************************/
#define  CapSense_1_PrescalersTuningDone         CapSense_1_prescalersTuningDone
#define  CapSense_1_SensorRaw	                   CapSense_1_sensorRaw
#define  CapSense_1_PRSResolutionTbl             CapSense_1_prsResolutionTbl
#define  CapSense_1_SensorEnableMask             CapSense_1_sensorEnableMask
#define  CapSense_1_Clk1DividerVal               CapSense_1_senseClkDividerVal
#define  CapSense_1_Clk2DividerVal               CapSense_1_sampleClkDividerVal
#define  CapSense_1_PrtSelTbl                    CapSense_1_prtSelTbl
#define  CapSense_1_PrtCfgTbl                    CapSense_1_prtCfgTbl
#define  CapSense_1_PrtDRTbl                     CapSense_1_prtDRTbl
#define  CapSense_1_idac1Settings				   CapSense_1_modulationIDAC	
#define  CapSense_1_idac2Settings                CapSense_1_compensationIDAC

#endif /* CY_CAPSENSE_CSD_CapSense_1_H */


 /* [] END OF FILE */
