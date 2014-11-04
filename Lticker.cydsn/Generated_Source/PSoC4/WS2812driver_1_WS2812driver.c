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

#include <cytypes.h>
#include <WS2812driver.h>

inline void WS2812driver_1_write_byte(unsigned char buff, unsigned char fifo){
    if(fifo==0){
        CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, buff);
    }else{
        CY_SET_REG8(WS2812driver_1_shifter_u0__F1_REG, buff);
    }
}

void WS2812driver_1_write2fifo(unsigned char* buff, unsigned char len){
    unsigned char i;
    for(i=0;i<len;i++){
        if(i<5){
            WS2812driver_1_write_byte(buff[i], FIFO_F0);
        }else{
            WS2812driver_1_write_byte(buff[i], FIFO_F1);
        }
    }
}
/* [] END OF FILE */
