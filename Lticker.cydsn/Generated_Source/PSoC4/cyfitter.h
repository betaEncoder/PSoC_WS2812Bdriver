#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include <cydevice_trm.h>

/* Pin_1 */
#define Pin_1__0__DM__MASK 0x07u
#define Pin_1__0__DM__SHIFT 0
#define Pin_1__0__DR CYREG_PRT2_DR
#define Pin_1__0__HSIOM CYREG_HSIOM_PORT_SEL2
#define Pin_1__0__HSIOM_MASK 0x0000000Fu
#define Pin_1__0__HSIOM_SHIFT 0u
#define Pin_1__0__INTCFG CYREG_PRT2_INTCFG
#define Pin_1__0__INTSTAT CYREG_PRT2_INTSTAT
#define Pin_1__0__MASK 0x01u
#define Pin_1__0__OUT_SEL CYREG_UDB_PA2_CFG10
#define Pin_1__0__OUT_SEL_SHIFT 0u
#define Pin_1__0__OUT_SEL_VAL 3u
#define Pin_1__0__PA__CFG0 CYREG_UDB_PA2_CFG0
#define Pin_1__0__PA__CFG1 CYREG_UDB_PA2_CFG1
#define Pin_1__0__PA__CFG10 CYREG_UDB_PA2_CFG10
#define Pin_1__0__PA__CFG11 CYREG_UDB_PA2_CFG11
#define Pin_1__0__PA__CFG12 CYREG_UDB_PA2_CFG12
#define Pin_1__0__PA__CFG13 CYREG_UDB_PA2_CFG13
#define Pin_1__0__PA__CFG14 CYREG_UDB_PA2_CFG14
#define Pin_1__0__PA__CFG2 CYREG_UDB_PA2_CFG2
#define Pin_1__0__PA__CFG3 CYREG_UDB_PA2_CFG3
#define Pin_1__0__PA__CFG4 CYREG_UDB_PA2_CFG4
#define Pin_1__0__PA__CFG5 CYREG_UDB_PA2_CFG5
#define Pin_1__0__PA__CFG6 CYREG_UDB_PA2_CFG6
#define Pin_1__0__PA__CFG7 CYREG_UDB_PA2_CFG7
#define Pin_1__0__PA__CFG8 CYREG_UDB_PA2_CFG8
#define Pin_1__0__PA__CFG9 CYREG_UDB_PA2_CFG9
#define Pin_1__0__PC CYREG_PRT2_PC
#define Pin_1__0__PC2 CYREG_PRT2_PC2
#define Pin_1__0__PORT 2u
#define Pin_1__0__PS CYREG_PRT2_PS
#define Pin_1__0__SHIFT 0
#define Pin_1__DR CYREG_PRT2_DR
#define Pin_1__INTCFG CYREG_PRT2_INTCFG
#define Pin_1__INTSTAT CYREG_PRT2_INTSTAT
#define Pin_1__MASK 0x01u
#define Pin_1__PA__CFG0 CYREG_UDB_PA2_CFG0
#define Pin_1__PA__CFG1 CYREG_UDB_PA2_CFG1
#define Pin_1__PA__CFG10 CYREG_UDB_PA2_CFG10
#define Pin_1__PA__CFG11 CYREG_UDB_PA2_CFG11
#define Pin_1__PA__CFG12 CYREG_UDB_PA2_CFG12
#define Pin_1__PA__CFG13 CYREG_UDB_PA2_CFG13
#define Pin_1__PA__CFG14 CYREG_UDB_PA2_CFG14
#define Pin_1__PA__CFG2 CYREG_UDB_PA2_CFG2
#define Pin_1__PA__CFG3 CYREG_UDB_PA2_CFG3
#define Pin_1__PA__CFG4 CYREG_UDB_PA2_CFG4
#define Pin_1__PA__CFG5 CYREG_UDB_PA2_CFG5
#define Pin_1__PA__CFG6 CYREG_UDB_PA2_CFG6
#define Pin_1__PA__CFG7 CYREG_UDB_PA2_CFG7
#define Pin_1__PA__CFG8 CYREG_UDB_PA2_CFG8
#define Pin_1__PA__CFG9 CYREG_UDB_PA2_CFG9
#define Pin_1__PC CYREG_PRT2_PC
#define Pin_1__PC2 CYREG_PRT2_PC2
#define Pin_1__PORT 2u
#define Pin_1__PS CYREG_PRT2_PS
#define Pin_1__SHIFT 0

/* Pin_2 */
#define Pin_2__0__DM__MASK 0x38u
#define Pin_2__0__DM__SHIFT 3
#define Pin_2__0__DR CYREG_PRT2_DR
#define Pin_2__0__HSIOM CYREG_HSIOM_PORT_SEL2
#define Pin_2__0__HSIOM_MASK 0x000000F0u
#define Pin_2__0__HSIOM_SHIFT 4u
#define Pin_2__0__INTCFG CYREG_PRT2_INTCFG
#define Pin_2__0__INTSTAT CYREG_PRT2_INTSTAT
#define Pin_2__0__MASK 0x02u
#define Pin_2__0__OUT_SEL CYREG_UDB_PA2_CFG10
#define Pin_2__0__OUT_SEL_SHIFT 2u
#define Pin_2__0__OUT_SEL_VAL 2u
#define Pin_2__0__PA__CFG0 CYREG_UDB_PA2_CFG0
#define Pin_2__0__PA__CFG1 CYREG_UDB_PA2_CFG1
#define Pin_2__0__PA__CFG10 CYREG_UDB_PA2_CFG10
#define Pin_2__0__PA__CFG11 CYREG_UDB_PA2_CFG11
#define Pin_2__0__PA__CFG12 CYREG_UDB_PA2_CFG12
#define Pin_2__0__PA__CFG13 CYREG_UDB_PA2_CFG13
#define Pin_2__0__PA__CFG14 CYREG_UDB_PA2_CFG14
#define Pin_2__0__PA__CFG2 CYREG_UDB_PA2_CFG2
#define Pin_2__0__PA__CFG3 CYREG_UDB_PA2_CFG3
#define Pin_2__0__PA__CFG4 CYREG_UDB_PA2_CFG4
#define Pin_2__0__PA__CFG5 CYREG_UDB_PA2_CFG5
#define Pin_2__0__PA__CFG6 CYREG_UDB_PA2_CFG6
#define Pin_2__0__PA__CFG7 CYREG_UDB_PA2_CFG7
#define Pin_2__0__PA__CFG8 CYREG_UDB_PA2_CFG8
#define Pin_2__0__PA__CFG9 CYREG_UDB_PA2_CFG9
#define Pin_2__0__PC CYREG_PRT2_PC
#define Pin_2__0__PC2 CYREG_PRT2_PC2
#define Pin_2__0__PORT 2u
#define Pin_2__0__PS CYREG_PRT2_PS
#define Pin_2__0__SHIFT 1
#define Pin_2__DR CYREG_PRT2_DR
#define Pin_2__INTCFG CYREG_PRT2_INTCFG
#define Pin_2__INTSTAT CYREG_PRT2_INTSTAT
#define Pin_2__MASK 0x02u
#define Pin_2__PA__CFG0 CYREG_UDB_PA2_CFG0
#define Pin_2__PA__CFG1 CYREG_UDB_PA2_CFG1
#define Pin_2__PA__CFG10 CYREG_UDB_PA2_CFG10
#define Pin_2__PA__CFG11 CYREG_UDB_PA2_CFG11
#define Pin_2__PA__CFG12 CYREG_UDB_PA2_CFG12
#define Pin_2__PA__CFG13 CYREG_UDB_PA2_CFG13
#define Pin_2__PA__CFG14 CYREG_UDB_PA2_CFG14
#define Pin_2__PA__CFG2 CYREG_UDB_PA2_CFG2
#define Pin_2__PA__CFG3 CYREG_UDB_PA2_CFG3
#define Pin_2__PA__CFG4 CYREG_UDB_PA2_CFG4
#define Pin_2__PA__CFG5 CYREG_UDB_PA2_CFG5
#define Pin_2__PA__CFG6 CYREG_UDB_PA2_CFG6
#define Pin_2__PA__CFG7 CYREG_UDB_PA2_CFG7
#define Pin_2__PA__CFG8 CYREG_UDB_PA2_CFG8
#define Pin_2__PA__CFG9 CYREG_UDB_PA2_CFG9
#define Pin_2__PC CYREG_PRT2_PC
#define Pin_2__PC2 CYREG_PRT2_PC2
#define Pin_2__PORT 2u
#define Pin_2__PS CYREG_PRT2_PS
#define Pin_2__SHIFT 1

/* Pin_3 */
#define Pin_3__0__DM__MASK 0x1C0u
#define Pin_3__0__DM__SHIFT 6
#define Pin_3__0__DR CYREG_PRT2_DR
#define Pin_3__0__HSIOM CYREG_HSIOM_PORT_SEL2
#define Pin_3__0__HSIOM_MASK 0x00000F00u
#define Pin_3__0__HSIOM_SHIFT 8u
#define Pin_3__0__INTCFG CYREG_PRT2_INTCFG
#define Pin_3__0__INTSTAT CYREG_PRT2_INTSTAT
#define Pin_3__0__MASK 0x04u
#define Pin_3__0__OUT_SEL CYREG_UDB_PA2_CFG10
#define Pin_3__0__OUT_SEL_SHIFT 4u
#define Pin_3__0__OUT_SEL_VAL 1u
#define Pin_3__0__PA__CFG0 CYREG_UDB_PA2_CFG0
#define Pin_3__0__PA__CFG1 CYREG_UDB_PA2_CFG1
#define Pin_3__0__PA__CFG10 CYREG_UDB_PA2_CFG10
#define Pin_3__0__PA__CFG11 CYREG_UDB_PA2_CFG11
#define Pin_3__0__PA__CFG12 CYREG_UDB_PA2_CFG12
#define Pin_3__0__PA__CFG13 CYREG_UDB_PA2_CFG13
#define Pin_3__0__PA__CFG14 CYREG_UDB_PA2_CFG14
#define Pin_3__0__PA__CFG2 CYREG_UDB_PA2_CFG2
#define Pin_3__0__PA__CFG3 CYREG_UDB_PA2_CFG3
#define Pin_3__0__PA__CFG4 CYREG_UDB_PA2_CFG4
#define Pin_3__0__PA__CFG5 CYREG_UDB_PA2_CFG5
#define Pin_3__0__PA__CFG6 CYREG_UDB_PA2_CFG6
#define Pin_3__0__PA__CFG7 CYREG_UDB_PA2_CFG7
#define Pin_3__0__PA__CFG8 CYREG_UDB_PA2_CFG8
#define Pin_3__0__PA__CFG9 CYREG_UDB_PA2_CFG9
#define Pin_3__0__PC CYREG_PRT2_PC
#define Pin_3__0__PC2 CYREG_PRT2_PC2
#define Pin_3__0__PORT 2u
#define Pin_3__0__PS CYREG_PRT2_PS
#define Pin_3__0__SHIFT 2
#define Pin_3__DR CYREG_PRT2_DR
#define Pin_3__INTCFG CYREG_PRT2_INTCFG
#define Pin_3__INTSTAT CYREG_PRT2_INTSTAT
#define Pin_3__MASK 0x04u
#define Pin_3__PA__CFG0 CYREG_UDB_PA2_CFG0
#define Pin_3__PA__CFG1 CYREG_UDB_PA2_CFG1
#define Pin_3__PA__CFG10 CYREG_UDB_PA2_CFG10
#define Pin_3__PA__CFG11 CYREG_UDB_PA2_CFG11
#define Pin_3__PA__CFG12 CYREG_UDB_PA2_CFG12
#define Pin_3__PA__CFG13 CYREG_UDB_PA2_CFG13
#define Pin_3__PA__CFG14 CYREG_UDB_PA2_CFG14
#define Pin_3__PA__CFG2 CYREG_UDB_PA2_CFG2
#define Pin_3__PA__CFG3 CYREG_UDB_PA2_CFG3
#define Pin_3__PA__CFG4 CYREG_UDB_PA2_CFG4
#define Pin_3__PA__CFG5 CYREG_UDB_PA2_CFG5
#define Pin_3__PA__CFG6 CYREG_UDB_PA2_CFG6
#define Pin_3__PA__CFG7 CYREG_UDB_PA2_CFG7
#define Pin_3__PA__CFG8 CYREG_UDB_PA2_CFG8
#define Pin_3__PA__CFG9 CYREG_UDB_PA2_CFG9
#define Pin_3__PC CYREG_PRT2_PC
#define Pin_3__PC2 CYREG_PRT2_PC2
#define Pin_3__PORT 2u
#define Pin_3__PS CYREG_PRT2_PS
#define Pin_3__SHIFT 2

/* Clock_1 */
#define Clock_1__DIVIDER_MASK 0x0000FFFFu
#define Clock_1__ENABLE CYREG_CLK_DIVIDER_A00
#define Clock_1__ENABLE_MASK 0x80000000u
#define Clock_1__MASK 0x80000000u
#define Clock_1__REGISTER CYREG_CLK_DIVIDER_A00

/* WS2812driver_1 */
#define WS2812driver_1_pulseGen__16BIT_A0_REG CYREG_UDB_W16_A0_00
#define WS2812driver_1_pulseGen__16BIT_A1_REG CYREG_UDB_W16_A1_00
#define WS2812driver_1_pulseGen__16BIT_D0_REG CYREG_UDB_W16_D0_00
#define WS2812driver_1_pulseGen__16BIT_D1_REG CYREG_UDB_W16_D1_00
#define WS2812driver_1_pulseGen__16BIT_DP_AUX_CTL_REG CYREG_UDB_W16_ACTL_00
#define WS2812driver_1_pulseGen__16BIT_F0_REG CYREG_UDB_W16_F0_00
#define WS2812driver_1_pulseGen__16BIT_F1_REG CYREG_UDB_W16_F1_00
#define WS2812driver_1_pulseGen__32BIT_A0_REG CYREG_UDB_W32_A0_00
#define WS2812driver_1_pulseGen__32BIT_A1_REG CYREG_UDB_W32_A1_00
#define WS2812driver_1_pulseGen__32BIT_D0_REG CYREG_UDB_W32_D0_00
#define WS2812driver_1_pulseGen__32BIT_D1_REG CYREG_UDB_W32_D1_00
#define WS2812driver_1_pulseGen__32BIT_DP_AUX_CTL_REG CYREG_UDB_W32_ACTL_00
#define WS2812driver_1_pulseGen__32BIT_F0_REG CYREG_UDB_W32_F0_00
#define WS2812driver_1_pulseGen__32BIT_F1_REG CYREG_UDB_W32_F1_00
#define WS2812driver_1_pulseGen__A0_A1_REG CYREG_UDB_CAT16_A_00
#define WS2812driver_1_pulseGen__A0_REG CYREG_UDB_W8_A0_00
#define WS2812driver_1_pulseGen__A1_REG CYREG_UDB_W8_A1_00
#define WS2812driver_1_pulseGen__D0_D1_REG CYREG_UDB_CAT16_D_00
#define WS2812driver_1_pulseGen__D0_REG CYREG_UDB_W8_D0_00
#define WS2812driver_1_pulseGen__D1_REG CYREG_UDB_W8_D1_00
#define WS2812driver_1_pulseGen__DP_AUX_CTL_REG CYREG_UDB_W8_ACTL_00
#define WS2812driver_1_pulseGen__F0_F1_REG CYREG_UDB_CAT16_F_00
#define WS2812driver_1_pulseGen__F0_REG CYREG_UDB_W8_F0_00
#define WS2812driver_1_pulseGen__F1_REG CYREG_UDB_W8_F1_00
#define WS2812driver_1_pulseGen_PI__16BIT_STATUS_AUX_CTL_REG CYREG_UDB_W16_ACTL_00
#define WS2812driver_1_pulseGen_PI__16BIT_STATUS_REG CYREG_UDB_W16_ST_00
#define WS2812driver_1_pulseGen_PI__32BIT_MASK_REG CYREG_UDB_W32_MSK_00
#define WS2812driver_1_pulseGen_PI__32BIT_STATUS_AUX_CTL_REG CYREG_UDB_W32_ACTL_00
#define WS2812driver_1_pulseGen_PI__32BIT_STATUS_REG CYREG_UDB_W32_ST_00
#define WS2812driver_1_pulseGen_PI__MASK_REG CYREG_UDB_W8_MSK_00
#define WS2812driver_1_pulseGen_PI__STATUS_AUX_CTL_REG CYREG_UDB_W8_ACTL_00
#define WS2812driver_1_pulseGen_PI__STATUS_REG CYREG_UDB_W8_ST_00
#define WS2812driver_1_shifter_u0__A0_A1_REG CYREG_UDB_CAT16_A_03
#define WS2812driver_1_shifter_u0__A0_REG CYREG_UDB_W8_A0_03
#define WS2812driver_1_shifter_u0__A1_REG CYREG_UDB_W8_A1_03
#define WS2812driver_1_shifter_u0__D0_D1_REG CYREG_UDB_CAT16_D_03
#define WS2812driver_1_shifter_u0__D0_REG CYREG_UDB_W8_D0_03
#define WS2812driver_1_shifter_u0__D1_REG CYREG_UDB_W8_D1_03
#define WS2812driver_1_shifter_u0__DP_AUX_CTL_REG CYREG_UDB_W8_ACTL_03
#define WS2812driver_1_shifter_u0__F0_F1_REG CYREG_UDB_CAT16_F_03
#define WS2812driver_1_shifter_u0__F0_REG CYREG_UDB_W8_F0_03
#define WS2812driver_1_shifter_u0__F1_REG CYREG_UDB_W8_F1_03

/* Miscellaneous */
#define CYDEV_BCLK__HFCLK__HZ 40000000U
#define CYDEV_BCLK__HFCLK__KHZ 40000U
#define CYDEV_BCLK__HFCLK__MHZ 40U
#define CYDEV_BCLK__SYSCLK__HZ 40000000U
#define CYDEV_BCLK__SYSCLK__KHZ 40000U
#define CYDEV_BCLK__SYSCLK__MHZ 40U
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PANTHER 4u
#define CYDEV_CHIP_DIE_PSOC4A 2u
#define CYDEV_CHIP_DIE_PSOC5LP 5u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC4
#define CYDEV_CHIP_JTAG_ID 0x04C81193u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_4A 2u
#define CYDEV_CHIP_MEMBER_4D 3u
#define CYDEV_CHIP_MEMBER_5A 4u
#define CYDEV_CHIP_MEMBER_5B 5u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_4A
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_MEMBER_USED
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PANTHER_ES0 0u
#define CYDEV_CHIP_REV_PANTHER_ES1 1u
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4D_ES0 0u
#define CYDEV_CHIP_REVISION_4D_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_4A_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REVISION_USED
#define CYDEV_CONFIG_READ_ACCELERATOR 1
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_DEBUG_PROTECT_KILL 4
#define CYDEV_DEBUG_PROTECT_OPEN 1
#define CYDEV_DEBUG_PROTECT CYDEV_DEBUG_PROTECT_OPEN
#define CYDEV_DEBUG_PROTECT_PROTECTED 2
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_Disable
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_ENABLE 0
#define CYDEV_HEAP_SIZE 0x0100
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_STACK_SIZE 0x0400
#define CYDEV_USE_BUNDLED_CMSIS 1
#define CYDEV_VARIABLE_VDDA 1
#define CYDEV_VDDA 3.3
#define CYDEV_VDDA_MV 3300
#define CYDEV_VDDD 3.3
#define CYDEV_VDDD_MV 3300
#define CYIPBLOCK_M0S8_CTBM_VERSION 0
#define CYIPBLOCK_m0s8cpuss_VERSION 0
#define CYIPBLOCK_m0s8csd_VERSION 0
#define CYIPBLOCK_m0s8gpio2_VERSION 0
#define CYIPBLOCK_m0s8hsiom4a_VERSION 0
#define CYIPBLOCK_m0s8lcd_VERSION 0
#define CYIPBLOCK_m0s8lpcomp_VERSION 0
#define CYIPBLOCK_m0s8pclk_VERSION 0
#define CYIPBLOCK_m0s8sar_VERSION 0
#define CYIPBLOCK_m0s8scb_VERSION 0
#define CYIPBLOCK_m0s8srssv2_VERSION 1
#define CYIPBLOCK_m0s8tcpwm_VERSION 0
#define CYIPBLOCK_m0s8udbif_VERSION 0
#define CYIPBLOCK_S8_GPIO_VERSION 2
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
