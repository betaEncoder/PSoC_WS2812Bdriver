/* ========================================
 * File Name: `$INSTANCE_NAME`.h  
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
inline void `$INSTANCE_NAME`_write_byte(unsigned char buff, unsigned char fifo);


// write data array to buffer
void `$INSTANCE_NAME`_write2fifo(unsigned char* buff, unsigned char len);

/* [] END OF FILE */
