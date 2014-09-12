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
        for(i=0;i<2048;i++);
            CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, 0xa1);
            CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, ~(0xa1));
            CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, 0xa1);
            CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, ~(0xa1));
            CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, 0xa1);
            CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, ~(0xa1));
/*            CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, 0xa1);
            CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, 0xa1);
            CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, 0xa1);
            CY_SET_REG8(WS2812driver_1_pulseGen_u0__F1_REG,5);  // pulse 1
            CY_SET_REG8(WS2812driver_1_pulseGen_u0__F1_REG,17); // pulse 0
            CY_SET_REG8(WS2812driver_1_pulseGen_u0__F1_REG,5);
            CY_SET_REG8(WS2812driver_1_pulseGen_u0__F1_REG,17);
            CY_SET_REG8(WS2812driver_1_pulseGen_u0__F1_REG,5);  // pulse 1
            CY_SET_REG8(WS2812driver_1_pulseGen_u0__F1_REG,17); // pulse 0
            CY_SET_REG8(WS2812driver_1_pulseGen_u0__F1_REG,5);
            CY_SET_REG8(WS2812driver_1_pulseGen_u0__F1_REG,17);*/
            
    }
}

/* [] END OF FILE */
