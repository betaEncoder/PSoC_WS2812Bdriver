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

#define BUSY        0x1
#define FIFO_FULL   0x2
#define FIFO_EMPTY  0x4

typedef struct _rgb{
    uint8 g;
    uint8 r;
    uint8 b;
}rgb_tag;

void WSDriverWriteByte(uint8 val){
        while(Status_Reg_1_Read()&FIFO_FULL){
            ;
        }
        CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, val);
}

void sendPixels(rgb_tag *rgb_tag, uint32 length){
    uint32 i;
    for(i=0;i<length;i++){
        WSDriverWriteByte(rgb_tag[i].g);
        WSDriverWriteByte(rgb_tag[i].r);
        WSDriverWriteByte(rgb_tag[i].b);
    }
}

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    int i;
    rgb_tag led[10] = {
        { 0x00, 0x0f, 0x00},
        { 0x0f, 0x00, 0x00},
        { 0x00, 0x00, 0x0f},
        { 0x0f, 0x0f, 0x0f},
        { 0x01, 0x01, 0x01},
        { 0x00, 0x08, 0x08},
        { 0x08, 0x08, 0x00},
        { 0x08, 0x00, 0x08},
        { 0x08, 0x08, 0x08},
        { 0x08, 0x08, 0x08}
    };
    for(;;)
    {
        /* Place your application code here. */
        for(i=0;i<255;i++);
        sendPixels(led, 10);
    }
}

/* [] END OF FILE */
