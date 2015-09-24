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

#if !defined(EEPROM_H)
#define EEPROM_H

#include <project.h>
    
#define EEPROM_ID   0x50    /* 0b1010000 = 0x50 in hex - E2 E1 E0 tied to GND */

#define READ    1
#define WRITE   0
#define ACK     0
#define NACK    1

void EEPROM_write(uint16_t mem_address, uint8_t value);    
uint8_t EEPROM_read(uint16_t mem_address);

#define EEPROM_K_D_P_ADD    0x0001
#define EEPROM_K_D_Q_ADD    0x0002
#define EEPROM_K_D_R_ADD    0x0003



#endif
/* [] END OF FILE */
