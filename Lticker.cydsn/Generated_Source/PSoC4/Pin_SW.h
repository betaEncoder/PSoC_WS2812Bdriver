/*******************************************************************************
* File Name: Pin_SW.h  
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

#if !defined(CY_PINS_Pin_SW_H) /* Pins Pin_SW_H */
#define CY_PINS_Pin_SW_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin_SW_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_SW_Write(uint8 value) ;
void    Pin_SW_SetDriveMode(uint8 mode) ;
uint8   Pin_SW_ReadDataReg(void) ;
uint8   Pin_SW_Read(void) ;
uint8   Pin_SW_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_SW_DRIVE_MODE_BITS        (3)
#define Pin_SW_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin_SW_DRIVE_MODE_BITS))
#define Pin_SW_DRIVE_MODE_SHIFT       (0x00u)
#define Pin_SW_DRIVE_MODE_MASK        (0x07u << Pin_SW_DRIVE_MODE_SHIFT)

#define Pin_SW_DM_ALG_HIZ         (0x00u << Pin_SW_DRIVE_MODE_SHIFT)
#define Pin_SW_DM_DIG_HIZ         (0x01u << Pin_SW_DRIVE_MODE_SHIFT)
#define Pin_SW_DM_RES_UP          (0x02u << Pin_SW_DRIVE_MODE_SHIFT)
#define Pin_SW_DM_RES_DWN         (0x03u << Pin_SW_DRIVE_MODE_SHIFT)
#define Pin_SW_DM_OD_LO           (0x04u << Pin_SW_DRIVE_MODE_SHIFT)
#define Pin_SW_DM_OD_HI           (0x05u << Pin_SW_DRIVE_MODE_SHIFT)
#define Pin_SW_DM_STRONG          (0x06u << Pin_SW_DRIVE_MODE_SHIFT)
#define Pin_SW_DM_RES_UPDWN       (0x07u << Pin_SW_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Pin_SW_MASK               Pin_SW__MASK
#define Pin_SW_SHIFT              Pin_SW__SHIFT
#define Pin_SW_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_SW_PS                     (* (reg32 *) Pin_SW__PS)
/* Port Configuration */
#define Pin_SW_PC                     (* (reg32 *) Pin_SW__PC)
/* Data Register */
#define Pin_SW_DR                     (* (reg32 *) Pin_SW__DR)
/* Input Buffer Disable Override */
#define Pin_SW_INP_DIS                (* (reg32 *) Pin_SW__PC2)


#if defined(Pin_SW__INTSTAT)  /* Interrupt Registers */

    #define Pin_SW_INTSTAT                (* (reg32 *) Pin_SW__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Pin_SW_H */


/* [] END OF FILE */
