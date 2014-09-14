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
#include <string.h>

#define TIMEOUT     250
#define BUTTON_SCAN 20
#define LED_LENGTH  10

#define BUSY        0x1
#define FIFO_FULL   0x2
#define FIFO_EMPTY  0x4

// LED1つぶんのRGB値を持つ構造体
typedef struct _rgb{
    uint8 g;
    uint8 r;
    uint8 b;
}rgb_tag;

rgb_tag onboardLED;
rgb_tag initLed[LED_LENGTH] = {
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
};    // LEDの初期値
rgb_tag led[LED_LENGTH];

// 現在タッチしている場所
uint8 curPos;
uint32 sampleTimeout = 0;
uint8 buttonTimeout = 0;
uint8 mode = 0;

// WS2812ドライバ用1バイト送信関数
void WSDriverWriteByte(uint8 val){
        while(Status_Reg_1_Read()&FIFO_FULL){   // FIFOが空くまで待つ
            ;
        }
        CY_SET_REG8(WS2812driver_1_shifter_u0__F0_REG, val);
}

// WS2812ドライバ用ドライバ
void sendPixels(rgb_tag *rgb_tag, uint32 length){
    uint32 i;
    for(i=0;i<length;i++){
        WSDriverWriteByte(rgb_tag[i].g);
        WSDriverWriteByte(rgb_tag[i].r);
        WSDriverWriteByte(rgb_tag[i].b);
    }
}

void refreshLED(){
    int i;
    
    if(mode){
        // LEDを1つシフト
        for(i=LED_LENGTH-1;i>0;i--){
            led[i] = led[i-1];
        }
        
        if(curPos<32){
            led[0].r = 32 - curPos;
            led[0].g = curPos;
            led[0].b = 0;
        }else{
            led[0].r = 0;
            led[0].g = 64 - curPos;
            led[0].b = curPos - 32;
        }
    }else{
        rgb_tag temp = led[LED_LENGTH-1];
        // LEDをローテーション
        for(i=LED_LENGTH-1;i>0;i--){
            led[i] = led[i-1];
        }
        led[0] = temp;
    }
}

void buttonScan(){
    static uint8 prevButtonStatus = 1;
    uint8 currentButtonStatus = Pin_SW_Read();
    if(prevButtonStatus==1 && currentButtonStatus==0){
        // buttonPressed;
        mode ^= 1;
        if(mode==0){
            memcpy(led, initLed, sizeof(led));
        }
    }
    
    prevButtonStatus = currentButtonStatus;
}

void SysTick_Handler(){
    sampleTimeout++;
    if(sampleTimeout==TIMEOUT){
        sampleTimeout = 0;
        refreshLED();
    }
    
    buttonTimeout++;
    if(buttonTimeout==BUTTON_SCAN){
        buttonTimeout = 0;
        buttonScan();
    }
}

void CapSense_GetPosition(void)
{
    uint8 position;
    /* Find Slider Position */
    position = CapSense_1_GetCentroidPos(CapSense_1_LINEARSLIDER0__LS);    
    
    /* Reset position */
    if(position != 0xFFu)
    {
        curPos = position;
    }
                
    /* Apply PWM */
    if(curPos<32){
        onboardLED.r = 32 - curPos;
        onboardLED.g = curPos;
        onboardLED.b = 0;
    }else{
        onboardLED.r = 0;
        onboardLED.g = 64 - curPos;
        onboardLED.b = curPos - 32;
    }

    PWM_1_WriteCompare1(onboardLED.r);
    PWM_1_WriteCompare2(onboardLED.g);
    PWM_2_WriteCompare(onboardLED.b);
}

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    int i;
    for(i=0;i<2048;i++);     // 適当に待つ
    PWM_1_Start();
    PWM_2_Start();

    // 1msecごとに割り込み
    if (SysTick_Config( (40000000) / 1000)) { 
            while (1);                                  /* Capture error */
    }
    /* setup systick interrupt */
    CyIntSetSysVector(15,SysTick_Handler);
    
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    CapSense_1_Start();
    
    
    /* Initialize baselines */ 
    CapSense_1_InitializeAllBaselines();
    
    for(;;)
    {
        /* Place your application code here. */
        sendPixels(led, LED_LENGTH);    // LED10個分流し込む
        
        /* Update all baselines */
        CapSense_1_UpdateEnabledBaselines();
        
   		/* Start scanning all enabled sensors */
    	CapSense_1_ScanEnabledWidgets();
    
        /* Wait for scanning to complete */
		while(CapSense_1_IsBusy() != 0);

		/* Display CapSense state using LEDs */
        CapSense_GetPosition();
    }
}


/* [] END OF FILE */
