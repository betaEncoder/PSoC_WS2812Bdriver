/* ========================================
 * File Name: WS2812driver_1.h  
 * Version 1.0
 * Copyright betaEncoder, 2014
 * All Rights Reserved
 * This software is released under the MIT License, see LICENSE.txt.
 * ========================================
*/

#include <cytypes.h>

/***************************************
*           API Constants        
***************************************/
// fifo numbers
#define FIFO_F0 0
#define FIFO_F1 1


/***************************************
*        Function Prototypes             
***************************************/
// usualy, private function
inline void WS2812driver_1_write_byte(unsigned char buff, unsigned char fifo);


// write data array to buffer
void WS2812driver_1_write2fifo(unsigned char* buff, unsigned char len);

/* [] END OF FILE */
