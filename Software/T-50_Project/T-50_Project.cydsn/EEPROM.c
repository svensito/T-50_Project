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

/* EEPROM Handling */

#include <EEPROM.h>

extern uint8_t eeprom_conn;

void EEPROM_write(uint16_t mem_address, uint8_t value)
{
    if(I2CM_I2CMasterSendStart(EEPROM_ID, WRITE)==0)
    {
        I2CM_I2CMasterWriteByte(mem_address>>8);
        I2CM_I2CMasterWriteByte(mem_address);
        I2CM_I2CMasterWriteByte(value);
        I2CM_I2C_MASTER_GENERATE_STOP;
        eeprom_conn = 1;
    }
    else 
    {
        eeprom_conn = 0;
        I2CM_I2C_MASTER_GENERATE_STOP;
    }
}

uint8_t EEPROM_read(uint16_t mem_address)
{
    uint8_t buf = 0;
    if(I2CM_I2CMasterSendStart(EEPROM_ID, WRITE)==0)
    {
        //UART_1_UartPutString("Start OK ");
        I2CM_I2CMasterWriteByte(mem_address>>8);
        //UART_1_UartPutString("Mem H ");
        I2CM_I2CMasterWriteByte(mem_address);
        //UART_1_UartPutString("Mem L ");
        I2CM_I2CMasterSendRestart(EEPROM_ID, READ);
        //UART_1_UartPutString("Rst ");
        buf = I2CM_I2CMasterReadByte(NACK);
        I2CM_I2C_MASTER_GENERATE_STOP;
        eeprom_conn = 1;
    } 
    else 
    {
        eeprom_conn = 0;
        I2CM_I2C_MASTER_GENERATE_STOP;
    }
    return buf;
}

/* [] END OF FILE */
