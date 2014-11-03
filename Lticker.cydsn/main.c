/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    //Clock_1_Start();
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    int i;
    for(;;)
    {
        /* Place your application code here. */
        CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, 0x1);
        CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, 0x1);
        CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, 0x0);
        CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, 0x1);
        CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, 0x0);
        CY_SET_REG8(WS2812driver_1_shifter_u0__F1_REG, 0x1);
        CY_SET_REG8(WS2812driver_1_shifter_u0__F1_REG, 0x0);
        CY_SET_REG8(WS2812driver_1_shifter_u0__F1_REG, 0x1);
        CY_SET_REG8(WS2812driver_1_shifter_u0__F1_REG, 0x1);
        for(i=0;i<4096;i++);
    }
}

/* [] END OF FILE */
