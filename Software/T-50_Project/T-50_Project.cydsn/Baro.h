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

#if !defined(BARO_H)
#define BARO_H

#include <project.h>

    
/*-----------------------------------
    Barometer Address and Registers
    ---------------------------------*/    
#define BMP180_ADDR 0x77 // right justified 7-bit address as required in I2C Master
//#define BMP180_ADDR 0xEE // 7-bit address

#define	BMP180_REG_CONTROL 0xF4
#define	BMP180_REG_RESULT 0xF6

#define	BMP180_COMMAND_TEMPERATURE 0x2E
#define	BMP180_COMMAND_PRESSURE0 0x34
#define	BMP180_COMMAND_PRESSURE1 0x74
#define	BMP180_COMMAND_PRESSURE2 0xB4
#define	BMP180_COMMAND_PRESSURE3 0xF4    

void BMP180_baro_init(void);    
    
void BMP180_baro_trigger_temp(void);    
int32_t BMP180_baro_read_temp(void);    

void BMP180_baro_trigger_pressure(void);
int32_t BMP180_baro_read_pressure(void);

void BMP180_read_altitude(void);

#endif  // endif BARO_H
/* [] END OF FILE */
