/*******************************************************************************
* File Name: LED_RED.h  
* Version 2.0
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LED_RED_H) /* Pins LED_RED_H */
#define CY_PINS_LED_RED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LED_RED_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_RED_Write(uint8 value) ;
void    LED_RED_SetDriveMode(uint8 mode) ;
uint8   LED_RED_ReadDataReg(void) ;
uint8   LED_RED_Read(void) ;
uint8   LED_RED_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_RED_DRIVE_MODE_BITS        (3)
#define LED_RED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LED_RED_DRIVE_MODE_BITS))
#define LED_RED_DRIVE_MODE_SHIFT       (0x00u)
#define LED_RED_DRIVE_MODE_MASK        (0x07u << LED_RED_DRIVE_MODE_SHIFT)

#define LED_RED_DM_ALG_HIZ         (0x00u << LED_RED_DRIVE_MODE_SHIFT)
#define LED_RED_DM_DIG_HIZ         (0x01u << LED_RED_DRIVE_MODE_SHIFT)
#define LED_RED_DM_RES_UP          (0x02u << LED_RED_DRIVE_MODE_SHIFT)
#define LED_RED_DM_RES_DWN         (0x03u << LED_RED_DRIVE_MODE_SHIFT)
#define LED_RED_DM_OD_LO           (0x04u << LED_RED_DRIVE_MODE_SHIFT)
#define LED_RED_DM_OD_HI           (0x05u << LED_RED_DRIVE_MODE_SHIFT)
#define LED_RED_DM_STRONG          (0x06u << LED_RED_DRIVE_MODE_SHIFT)
#define LED_RED_DM_RES_UPDWN       (0x07u << LED_RED_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define LED_RED_MASK               LED_RED__MASK
#define LED_RED_SHIFT              LED_RED__SHIFT
#define LED_RED_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_RED_PS                     (* (reg32 *) LED_RED__PS)
/* Port Configuration */
#define LED_RED_PC                     (* (reg32 *) LED_RED__PC)
/* Data Register */
#define LED_RED_DR                     (* (reg32 *) LED_RED__DR)
/* Input Buffer Disable Override */
#define LED_RED_INP_DIS                (* (reg32 *) LED_RED__PC2)


#if defined(LED_RED__INTSTAT)  /* Interrupt Registers */

    #define LED_RED_INTSTAT                (* (reg32 *) LED_RED__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins LED_RED_H */


/* [] END OF FILE */
