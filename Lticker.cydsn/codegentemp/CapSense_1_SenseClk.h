/*******************************************************************************
* File Name: CapSense_1_SenseClk.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_CapSense_1_SenseClk_H)
#define CY_CLOCK_CapSense_1_SenseClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void CapSense_1_SenseClk_StartEx(uint32 alignClkDiv);
#define CapSense_1_SenseClk_Start() \
    CapSense_1_SenseClk_StartEx(CapSense_1_SenseClk__PA_DIV_ID)

#else

void CapSense_1_SenseClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void CapSense_1_SenseClk_Stop(void);

void CapSense_1_SenseClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 CapSense_1_SenseClk_GetDividerRegister(void);
uint8  CapSense_1_SenseClk_GetFractionalDividerRegister(void);

#define CapSense_1_SenseClk_Enable()                         CapSense_1_SenseClk_Start()
#define CapSense_1_SenseClk_Disable()                        CapSense_1_SenseClk_Stop()
#define CapSense_1_SenseClk_SetDividerRegister(clkDivider, reset)  \
    CapSense_1_SenseClk_SetFractionalDividerRegister((clkDivider), 0u)
#define CapSense_1_SenseClk_SetDivider(clkDivider)           CapSense_1_SenseClk_SetDividerRegister((clkDivider), 1u)
#define CapSense_1_SenseClk_SetDividerValue(clkDivider)      CapSense_1_SenseClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define CapSense_1_SenseClk_DIV_ID     CapSense_1_SenseClk__DIV_ID

#define CapSense_1_SenseClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define CapSense_1_SenseClk_CTRL_REG   (*(reg32 *)CapSense_1_SenseClk__CTRL_REGISTER)
#define CapSense_1_SenseClk_DIV_REG    (*(reg32 *)CapSense_1_SenseClk__DIV_REGISTER)

#define CapSense_1_SenseClk_CMD_DIV_SHIFT          (0u)
#define CapSense_1_SenseClk_CMD_PA_DIV_SHIFT       (8u)
#define CapSense_1_SenseClk_CMD_DISABLE_SHIFT      (30u)
#define CapSense_1_SenseClk_CMD_ENABLE_SHIFT       (31u)

#define CapSense_1_SenseClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << CapSense_1_SenseClk_CMD_DISABLE_SHIFT))
#define CapSense_1_SenseClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << CapSense_1_SenseClk_CMD_ENABLE_SHIFT))

#define CapSense_1_SenseClk_DIV_FRAC_MASK  (0x000000F8u)
#define CapSense_1_SenseClk_DIV_FRAC_SHIFT (3u)
#define CapSense_1_SenseClk_DIV_INT_MASK   (0xFFFFFF00u)
#define CapSense_1_SenseClk_DIV_INT_SHIFT  (8u)

#else 

#define CapSense_1_SenseClk_DIV_REG        (*(reg32 *)CapSense_1_SenseClk__REGISTER)
#define CapSense_1_SenseClk_ENABLE_REG     CapSense_1_SenseClk_DIV_REG
#define CapSense_1_SenseClk_DIV_FRAC_MASK  CapSense_1_SenseClk__FRAC_MASK
#define CapSense_1_SenseClk_DIV_FRAC_SHIFT (16u)
#define CapSense_1_SenseClk_DIV_INT_MASK   CapSense_1_SenseClk__DIVIDER_MASK
#define CapSense_1_SenseClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_CapSense_1_SenseClk_H) */

/* [] END OF FILE */
