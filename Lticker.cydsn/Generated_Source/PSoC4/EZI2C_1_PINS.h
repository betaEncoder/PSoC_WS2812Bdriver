/*******************************************************************************
* File Name: EZI2C_1_PINS.h
* Version 1.20
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_EZI2C_1_H)
#define CY_SCB_PINS_EZI2C_1_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define EZI2C_1_REMOVE_MOSI_SCL_RX_WAKE_PIN    (1u)
#define EZI2C_1_REMOVE_MOSI_SCL_RX_PIN         (1u)
#define EZI2C_1_REMOVE_MISO_SDA_TX_PIN         (1u)
#define EZI2C_1_REMOVE_SCLK_PIN                (1u)
#define EZI2C_1_REMOVE_SS0_PIN                 (1u)
#define EZI2C_1_REMOVE_SS1_PIN                 (1u)
#define EZI2C_1_REMOVE_SS2_PIN                 (1u)
#define EZI2C_1_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define EZI2C_1_REMOVE_I2C_PINS                (0u)
#define EZI2C_1_REMOVE_SPI_MASTER_PINS         (1u)
#define EZI2C_1_REMOVE_SPI_SLAVE_PINS          (1u)
#define EZI2C_1_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define EZI2C_1_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define EZI2C_1_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define EZI2C_1_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define EZI2C_1_REMOVE_UART_TX_PIN             (1u)
#define EZI2C_1_REMOVE_UART_RX_TX_PIN          (1u)
#define EZI2C_1_REMOVE_UART_RX_PIN             (1u)
#define EZI2C_1_REMOVE_UART_RX_WAKE_PIN        (1u)

/* Unconfigured pins */
#define EZI2C_1_MOSI_SCL_RX_WAKE_PIN   (0u == EZI2C_1_REMOVE_MOSI_SCL_RX_WAKE_PIN)
#define EZI2C_1_MOSI_SCL_RX_PIN        (0u == EZI2C_1_REMOVE_MOSI_SCL_RX_PIN)
#define EZI2C_1_MISO_SDA_TX_PIN        (0u == EZI2C_1_REMOVE_MISO_SDA_TX_PIN)
#define EZI2C_1_SCLK_PIN               (0u == EZI2C_1_REMOVE_SCLK_PIN)
#define EZI2C_1_SS0_PIN                (0u == EZI2C_1_REMOVE_SS0_PIN)
#define EZI2C_1_SS1_PIN                (0u == EZI2C_1_REMOVE_SS1_PIN)
#define EZI2C_1_SS2_PIN                (0u == EZI2C_1_REMOVE_SS2_PIN)
#define EZI2C_1_SS3_PIN                (0u == EZI2C_1_REMOVE_SS3_PIN)

/* Mode defined pins */
#define EZI2C_1_I2C_PINS               (0u == EZI2C_1_REMOVE_I2C_PINS)
#define EZI2C_1_SPI_MASTER_PINS        (0u == EZI2C_1_REMOVE_SPI_MASTER_PINS)
#define EZI2C_1_SPI_SLAVE_PINS         (0u == EZI2C_1_REMOVE_SPI_SLAVE_PINS)
#define EZI2C_1_SPI_MASTER_SS0_PIN     (0u == EZI2C_1_REMOVE_SPI_MASTER_SS0_PIN)
#define EZI2C_1_SPI_MASTER_SS1_PIN     (0u == EZI2C_1_REMOVE_SPI_MASTER_SS1_PIN)
#define EZI2C_1_SPI_MASTER_SS2_PIN     (0u == EZI2C_1_REMOVE_SPI_MASTER_SS2_PIN)
#define EZI2C_1_SPI_MASTER_SS3_PIN     (0u == EZI2C_1_REMOVE_SPI_MASTER_SS3_PIN)
#define EZI2C_1_UART_TX_PIN            (0u == EZI2C_1_REMOVE_UART_TX_PIN)
#define EZI2C_1_UART_RX_TX_PIN         (0u == EZI2C_1_REMOVE_UART_RX_TX_PIN)
#define EZI2C_1_UART_RX_PIN            (0u == EZI2C_1_REMOVE_UART_RX_PIN)
#define EZI2C_1_UART_RX_WAKE_PIN       (0u == EZI2C_1_REMOVE_UART_RX_WAKE_PIN)


/***************************************
*             Includes
****************************************/

#if(EZI2C_1_MOSI_SCL_RX_WAKE_PIN)
    #include "EZI2C_1_spi_mosi_i2c_scl_uart_rx_wake.h"
#endif /* (EZI2C_1_MOSI_SCL_RX_WAKE_PIN) */

#if(EZI2C_1_MOSI_SCL_RX_PIN)
    #include "EZI2C_1_spi_mosi_i2c_scl_uart_rx.h"
#endif /* (EZI2C_1_MOSI_SCL_RX_PIN) */

#if(EZI2C_1_MISO_SDA_TX_PIN)
    #include "EZI2C_1_spi_miso_i2c_sda_uart_tx.h"
#endif /* (EZI2C_1_MISO_SDA_TX_PIN_PIN) */

#if(EZI2C_1_SCLK_PIN)
    #include "EZI2C_1_spi_sclk.h"
#endif /* (EZI2C_1_SCLK_PIN) */

#if(EZI2C_1_SS0_PIN)
    #include "EZI2C_1_spi_ss0.h"
#endif /* (EZI2C_1_SS1_PIN) */

#if(EZI2C_1_SS1_PIN)
    #include "EZI2C_1_spi_ss1.h"
#endif /* (EZI2C_1_SS1_PIN) */

#if(EZI2C_1_SS2_PIN)
    #include "EZI2C_1_spi_ss2.h"
#endif /* (EZI2C_1_SS2_PIN) */

#if(EZI2C_1_SS3_PIN)
    #include "EZI2C_1_spi_ss3.h"
#endif /* (EZI2C_1_SS3_PIN) */

#if(EZI2C_1_I2C_PINS)
    #include "EZI2C_1_scl.h"
    #include "EZI2C_1_sda.h"
#endif /* (EZI2C_1_I2C_PINS) */

#if(EZI2C_1_SPI_MASTER_PINS)
    #include "EZI2C_1_sclk_m.h"
    #include "EZI2C_1_mosi_m.h"
    #include "EZI2C_1_miso_m.h"
#endif /* (EZI2C_1_SPI_MASTER_PINS) */

#if(EZI2C_1_SPI_SLAVE_PINS)
    #include "EZI2C_1_sclk_s.h"
    #include "EZI2C_1_mosi_s.h"
    #include "EZI2C_1_miso_s.h"
    #include "EZI2C_1_ss_s.h"
#endif /* (EZI2C_1_SPI_SLAVE_PINS) */

#if(EZI2C_1_SPI_MASTER_SS0_PIN)
    #include "EZI2C_1_ss0_m.h"
#endif /* (EZI2C_1_SPI_MASTER_SS0_PIN) */

#if(EZI2C_1_SPI_MASTER_SS1_PIN)
    #include "EZI2C_1_ss1_m.h"
#endif /* (EZI2C_1_SPI_MASTER_SS1_PIN) */

#if(EZI2C_1_SPI_MASTER_SS2_PIN)
    #include "EZI2C_1_ss2_m.h"
#endif /* (EZI2C_1_SPI_MASTER_SS2_PIN) */

#if(EZI2C_1_SPI_MASTER_SS3_PIN)
    #include "EZI2C_1_ss3_m.h"
#endif /* (EZI2C_1_SPI_MASTER_SS3_PIN) */

#if(EZI2C_1_UART_TX_PIN)
    #include "EZI2C_1_tx.h"
#endif /* (EZI2C_1_UART_TX_PIN) */

#if(EZI2C_1_UART_RX_TX_PIN)
    #include "EZI2C_1_rx_tx.h"
#endif /* (EZI2C_1_UART_RX_TX_PIN) */

#if(EZI2C_1_UART_RX_PIN)
    #include "EZI2C_1_rx.h"
#endif /* (EZI2C_1_UART_RX_PIN) */

#if(EZI2C_1_UART_RX_WAKE_PIN)
    #include "EZI2C_1_rx_wake.h"
#endif /* (EZI2C_1_UART_RX_WAKE_PIN) */


/***************************************
*              Registers
***************************************/

#if(EZI2C_1_MOSI_SCL_RX_WAKE_PIN)
    #define EZI2C_1_MOSI_SCL_RX_WAKE_HSIOM_REG  \
                                                (*(reg32 *) EZI2C_1_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define EZI2C_1_MOSI_SCL_RX_WAKE_HSIOM_PTR  \
                                                ( (reg32 *) EZI2C_1_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define EZI2C_1_MOSI_SCL_RX_WAKE_HSIOM_MASK \
                                                (EZI2C_1_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_MASK)
    #define EZI2C_1_MOSI_SCL_RX_WAKE_HSIOM_POS  \
                                                (EZI2C_1_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_SHIFT)

    #define EZI2C_1_MOSI_SCL_RX_WAKE_INTCFG_REG    (*(reg32 *) \
                                                              EZI2C_1_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)
    #define EZI2C_1_MOSI_SCL_RX_WAKE_INTCFG_PTR    ( (reg32 *) \
                                                              EZI2C_1_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)

    #define EZI2C_1_INTCFG_TYPE_MASK                  (0x03u)
    #define EZI2C_1_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS  (EZI2C_1_spi_mosi_i2c_scl_uart_rx_wake__SHIFT)
    #define EZI2C_1_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK ((uint32)                                           \
                                                                    ((uint32) EZI2C_1_INTCFG_TYPE_MASK << \
                                                                    EZI2C_1_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS))
#endif /* (EZI2C_1_MOSI_SCL_RX_WAKE_PIN) */

#if(EZI2C_1_MOSI_SCL_RX_PIN)
    #define EZI2C_1_MOSI_SCL_RX_HSIOM_REG      (*(reg32 *) EZI2C_1_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define EZI2C_1_MOSI_SCL_RX_HSIOM_PTR      ( (reg32 *) EZI2C_1_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define EZI2C_1_MOSI_SCL_RX_HSIOM_MASK     (EZI2C_1_spi_mosi_i2c_scl_uart_rx__0__HSIOM_MASK)
    #define EZI2C_1_MOSI_SCL_RX_HSIOM_POS      (EZI2C_1_spi_mosi_i2c_scl_uart_rx__0__HSIOM_SHIFT)
#endif /* (EZI2C_1_MOSI_SCL_RX_PIN) */

#if(EZI2C_1_MISO_SDA_TX_PIN)
    #define EZI2C_1_MISO_SDA_TX_HSIOM_REG      (*(reg32 *) EZI2C_1_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define EZI2C_1_MISO_SDA_TX_HSIOM_PTR      ( (reg32 *) EZI2C_1_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define EZI2C_1_MISO_SDA_TX_HSIOM_MASK     (EZI2C_1_spi_miso_i2c_sda_uart_tx__0__HSIOM_MASK)
    #define EZI2C_1_MISO_SDA_TX_HSIOM_POS      (EZI2C_1_spi_miso_i2c_sda_uart_tx__0__HSIOM_SHIFT)
#endif /* (EZI2C_1_MISO_SDA_TX_PIN_PIN) */

#if(EZI2C_1_SCLK_PIN)
    #define EZI2C_1_SCLK_HSIOM_REG     (*(reg32 *) EZI2C_1_spi_sclk__0__HSIOM)
    #define EZI2C_1_SCLK_HSIOM_PTR     ( (reg32 *) EZI2C_1_spi_sclk__0__HSIOM)
    #define EZI2C_1_SCLK_HSIOM_MASK    (EZI2C_1_spi_sclk__0__HSIOM_MASK)
    #define EZI2C_1_SCLK_HSIOM_POS     (EZI2C_1_spi_sclk__0__HSIOM_SHIFT)
#endif /* (EZI2C_1_SCLK_PIN) */

#if(EZI2C_1_SS0_PIN)
    #define EZI2C_1_SS0_HSIOM_REG      (*(reg32 *) EZI2C_1_spi_ss0__0__HSIOM)
    #define EZI2C_1_SS0_HSIOM_PTR      ( (reg32 *) EZI2C_1_spi_ss0__0__HSIOM)
    #define EZI2C_1_SS0_HSIOM_MASK     (EZI2C_1_spi_ss0__0__HSIOM_MASK)
    #define EZI2C_1_SS0_HSIOM_POS      (EZI2C_1_spi_ss0__0__HSIOM_SHIFT)
#endif /* (EZI2C_1_SS1_PIN) */

#if(EZI2C_1_SS1_PIN)
    #define EZI2C_1_SS1_HSIOM_REG      (*(reg32 *) EZI2C_1_spi_ss1__0__HSIOM)
    #define EZI2C_1_SS1_HSIOM_PTR      ( (reg32 *) EZI2C_1_spi_ss1__0__HSIOM)
    #define EZI2C_1_SS1_HSIOM_MASK     (EZI2C_1_spi_ss1__0__HSIOM_MASK)
    #define EZI2C_1_SS1_HSIOM_POS      (EZI2C_1_spi_ss1__0__HSIOM_SHIFT)
#endif /* (EZI2C_1_SS1_PIN) */

#if(EZI2C_1_SS2_PIN)
    #define EZI2C_1_SS2_HSIOM_REG     (*(reg32 *) EZI2C_1_spi_ss2__0__HSIOM)
    #define EZI2C_1_SS2_HSIOM_PTR     ( (reg32 *) EZI2C_1_spi_ss2__0__HSIOM)
    #define EZI2C_1_SS2_HSIOM_MASK    (EZI2C_1_spi_ss2__0__HSIOM_MASK)
    #define EZI2C_1_SS2_HSIOM_POS     (EZI2C_1_spi_ss2__0__HSIOM_SHIFT)
#endif /* (EZI2C_1_SS2_PIN) */

#if(EZI2C_1_SS3_PIN)
    #define EZI2C_1_SS3_HSIOM_REG     (*(reg32 *) EZI2C_1_spi_ss3__0__HSIOM)
    #define EZI2C_1_SS3_HSIOM_PTR     ( (reg32 *) EZI2C_1_spi_ss3__0__HSIOM)
    #define EZI2C_1_SS3_HSIOM_MASK    (EZI2C_1_spi_ss3__0__HSIOM_MASK)
    #define EZI2C_1_SS3_HSIOM_POS     (EZI2C_1_spi_ss3__0__HSIOM_SHIFT)
#endif /* (EZI2C_1_SS3_PIN) */

#if(EZI2C_1_I2C_PINS)
    #define EZI2C_1_SCL_HSIOM_REG     (*(reg32 *) EZI2C_1_scl__0__HSIOM)
    #define EZI2C_1_SCL_HSIOM_PTR     ( (reg32 *) EZI2C_1_scl__0__HSIOM)
    #define EZI2C_1_SCL_HSIOM_MASK    (EZI2C_1_scl__0__HSIOM_MASK)
    #define EZI2C_1_SCL_HSIOM_POS     (EZI2C_1_scl__0__HSIOM_SHIFT)

    #define EZI2C_1_SDA_HSIOM_REG     (*(reg32 *) EZI2C_1_sda__0__HSIOM)
    #define EZI2C_1_SDA_HSIOM_PTR     ( (reg32 *) EZI2C_1_sda__0__HSIOM)
    #define EZI2C_1_SDA_HSIOM_MASK    (EZI2C_1_sda__0__HSIOM_MASK)
    #define EZI2C_1_SDA_HSIOM_POS     (EZI2C_1_sda__0__HSIOM_SHIFT)
#endif /* (EZI2C_1_I2C_PINS) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define EZI2C_1_HSIOM_DEF_SEL      (0x00u)
#define EZI2C_1_HSIOM_GPIO_SEL     (0x00u)
#define EZI2C_1_HSIOM_UART_SEL     (0x09u)
#define EZI2C_1_HSIOM_I2C_SEL      (0x0Eu)
#define EZI2C_1_HSIOM_SPI_SEL      (0x0Fu)

#if(!EZI2C_1_CY_SCBIP_V1_I2C_ONLY)
    #define EZI2C_1_SCB_PINS_NUMBER    (7u)
#else
    #define EZI2C_1_SCB_PINS_NUMBER    (2u)
#endif /* (!EZI2C_1_CY_SCBIP_V1_I2C_ONLY) */

#define EZI2C_1_MOSI_SCL_RX_PIN_INDEX      (0u) /* RX pins without interrupt */
#define EZI2C_1_MOSI_SCL_RX_WAKE_PIN_INDEX (0u) /* RX pin with interrupt     */
#define EZI2C_1_MISO_SDA_TX_PIN_INDEX      (1u)
#define EZI2C_1_SCLK_PIN_INDEX             (2u)
#define EZI2C_1_SS0_PIN_INDEX              (3u)
#define EZI2C_1_SS1_PIN_INDEX              (4u)
#define EZI2C_1_SS2_PIN_INDEX              (5u)
#define EZI2C_1_SS3_PIN_INDEX              (6u)

#define EZI2C_1_MOSI_SCL_RX_PIN_MASK      ((uint32) 0x01u << EZI2C_1_MOSI_SCL_RX_PIN_INDEX)
#define EZI2C_1_MOSI_SCL_RX_WAKE_PIN_MASK ((uint32) 0x01u << EZI2C_1_MOSI_SCL_RX_WAKE_PIN_INDEX)
#define EZI2C_1_MISO_SDA_TX_PIN_MASK      ((uint32) 0x01u << EZI2C_1_MISO_SDA_TX_PIN_INDEX)
#define EZI2C_1_SCLK_PIN_MASK             ((uint32) 0x01u << EZI2C_1_SCLK_PIN_INDEX)
#define EZI2C_1_SS0_PIN_MASK              ((uint32) 0x01u << EZI2C_1_SS0_PIN_INDEX)
#define EZI2C_1_SS1_PIN_MASK              ((uint32) 0x01u << EZI2C_1_SS1_PIN_INDEX)
#define EZI2C_1_SS2_PIN_MASK              ((uint32) 0x01u << EZI2C_1_SS2_PIN_INDEX)
#define EZI2C_1_SS3_PIN_MASK              ((uint32) 0x01u << EZI2C_1_SS3_PIN_INDEX)

#define EZI2C_1_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin DM defines */
#define EZI2C_1_PIN_DM_ALG_HIZ  (0u)
#define EZI2C_1_PIN_DM_DIG_HIZ  (1u)
#define EZI2C_1_PIN_DM_OD_LO    (4u)
#define EZI2C_1_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Set bits-mask in register */
#define EZI2C_1_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit the in register */
#define EZI2C_1_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define EZI2C_1_SET_HSIOM_SEL(reg, mask, pos, sel) EZI2C_1_SET_REGISTER_BITS(reg, mask, pos, sel)
#define EZI2C_1_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        EZI2C_1_SET_REGISTER_BITS(reg, mask, pos, intType)
#define EZI2C_1_SET_INP_DIS(reg, mask, val) EZI2C_1_SET_REGISTER_BIT(reg, mask, val)

/* EZI2C_1_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  EZI2C_1_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if(EZI2C_1_I2C_PINS)
    #define EZI2C_1_SET_I2C_SCL_DR(val) EZI2C_1_scl_Write(val)

    #define EZI2C_1_SET_I2C_SCL_HSIOM_SEL(sel) \
                          EZI2C_1_SET_HSIOM_SEL(EZI2C_1_SCL_HSIOM_REG,  \
                                                         EZI2C_1_SCL_HSIOM_MASK, \
                                                         EZI2C_1_SCL_HSIOM_POS,  \
                                                         (sel))
    #define EZI2C_1_WAIT_SCL_SET_HIGH  (0u == EZI2C_1_scl_Read())

/* Unconfigured SCB: scl signal */
#elif(EZI2C_1_MOSI_SCL_RX_WAKE_PIN)
    #define EZI2C_1_SET_I2C_SCL_DR(val) \
                            EZI2C_1_spi_mosi_i2c_scl_uart_rx_wake_Write(val)

    #define EZI2C_1_SET_I2C_SCL_HSIOM_SEL(sel) \
                    EZI2C_1_SET_HSIOM_SEL(EZI2C_1_MOSI_SCL_RX_WAKE_HSIOM_REG,  \
                                                   EZI2C_1_MOSI_SCL_RX_WAKE_HSIOM_MASK, \
                                                   EZI2C_1_MOSI_SCL_RX_WAKE_HSIOM_POS,  \
                                                   (sel))

    #define EZI2C_1_WAIT_SCL_SET_HIGH  (0u == EZI2C_1_spi_mosi_i2c_scl_uart_rx_wake_Read())

#elif(EZI2C_1_MOSI_SCL_RX_PIN)
    #define EZI2C_1_SET_I2C_SCL_DR(val) \
                            EZI2C_1_spi_mosi_i2c_scl_uart_rx_Write(val)


    #define EZI2C_1_SET_I2C_SCL_HSIOM_SEL(sel) \
                            EZI2C_1_SET_HSIOM_SEL(EZI2C_1_MOSI_SCL_RX_HSIOM_REG,  \
                                                           EZI2C_1_MOSI_SCL_RX_HSIOM_MASK, \
                                                           EZI2C_1_MOSI_SCL_RX_HSIOM_POS,  \
                                                           (sel))

    #define EZI2C_1_WAIT_SCL_SET_HIGH  (0u == EZI2C_1_spi_mosi_i2c_scl_uart_rx_Read())

#else
    #define EZI2C_1_SET_I2C_SCL_DR(val) \
                                                    do{ ; }while(0)
    #define EZI2C_1_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ ; }while(0)

    #define EZI2C_1_WAIT_SCL_SET_HIGH  (0u)
#endif /* (EZI2C_1_MOSI_SCL_RX_PIN) */

/* SCB I2C: sda signal */
#if(EZI2C_1_I2C_PINS)
    #define EZI2C_1_WAIT_SDA_SET_HIGH  (0u == EZI2C_1_sda_Read())

/* Unconfigured SCB: sda signal */
#elif(EZI2C_1_MISO_SDA_TX_PIN)
    #define EZI2C_1_WAIT_SDA_SET_HIGH  (0u == EZI2C_1_spi_miso_i2c_sda_uart_tx_Read())

#else
    #define EZI2C_1_WAIT_SDA_SET_HIGH  (0u)
#endif /* (EZI2C_1_MOSI_SCL_RX_PIN) */

#endif /* (CY_SCB_PINS_EZI2C_1_H) */


/* [] END OF FILE */
