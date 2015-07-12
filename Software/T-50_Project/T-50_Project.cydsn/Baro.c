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

#include <baro.h>

#define READ    1
#define WRITE   0
#define ACK     0
#define NACK    1

/* Altitude value */
//extern int32_t alt;     /* from main.c file */

//uint8_t cnt_baro  = 0;  /* baro counter */
//int32_t temp = 0;   // temperature reading by BMP180
//int32_t press = 0;   // pressure reading by BMP180

/* Calibration Values required for calculation of pressure and temperature */
    int16_t AC1, AC2, AC3 = 0;
    uint16_t AC4, AC5, AC6 = 0;
    int16_t B1, B2, B5, MB, MC, MD = 0;
    
extern void UART_1_UartPutNum();

// function to read 16 bit registry
uint16_t read_BMP180_registry(uint8_t registry)
{
    I2CM_I2CMasterSendStart(BMP180_ADDR, WRITE);
	CyDelay(1);
    I2CM_I2CMasterWriteByte(registry);
	I2CM_I2CMasterSendRestart(BMP180_ADDR, READ);
	uint8_t reg_h = I2CM_I2CMasterReadByte(ACK);
	uint8_t reg_l = I2CM_I2CMasterReadByte(NACK);
    I2CM_I2C_MASTER_GENERATE_STOP;
    uint16_t reg_value = ((reg_h << 8) | (reg_l));    
    return(reg_value);
}

void write_BMP180_registry(uint8_t registry, uint8_t data)
{
    I2CM_I2CMasterSendStart(BMP180_ADDR, WRITE);
	CyDelay(1);
    I2CM_I2CMasterWriteByte(registry);
    I2CM_I2CMasterWriteByte(data);
    I2CM_I2C_MASTER_GENERATE_STOP;
}

void BMP180_baro_init(void)
{
    /* Reading the values of the registers and calculate pressure*/
    AC1 = read_BMP180_registry(0xAA);
    UART_1_UartPutNum(AC1);
    UART_1_UartPutString("\r\n");
    CyDelay(1);
    
    AC2 = read_BMP180_registry(0xAC);
    UART_1_UartPutNum(AC2);
    UART_1_UartPutString("\r\n");
    CyDelay(1);
    
    AC3 = read_BMP180_registry(0xAE);
    UART_1_UartPutNum(AC3);
    UART_1_UartPutString("\r\n");
    CyDelay(1);
    
    AC4 = read_BMP180_registry(0xB0);
    UART_1_UartPutNum(AC4);
    UART_1_UartPutString("\r\n");
    CyDelay(1);
    
    AC5 = read_BMP180_registry(0xB2);
    UART_1_UartPutNum(AC5);
    UART_1_UartPutString("\r\n");
    CyDelay(1);
    
    AC6 = read_BMP180_registry(0xB4);
    UART_1_UartPutNum(AC6);
    UART_1_UartPutString("\r\n");
    CyDelay(1);
    
    B1 = read_BMP180_registry(0xB6);
    UART_1_UartPutNum(B1);
    UART_1_UartPutString("\r\n");
    CyDelay(1);
    
    B2 = read_BMP180_registry(0xB8);
    UART_1_UartPutNum(B2);
    UART_1_UartPutString("\r\n");
    CyDelay(1);
    
    MB = read_BMP180_registry(0xBA);
    UART_1_UartPutNum(MB);
    UART_1_UartPutString("\r\n");
    CyDelay(1);
    
    MC = read_BMP180_registry(0xBC);
    UART_1_UartPutNum(MC);
    UART_1_UartPutString("\r\n");
    CyDelay(1);
    
    MD = read_BMP180_registry(0xBE);
    UART_1_UartPutNum(MD);
    UART_1_UartPutString("\r\n");
    CyDelay(1);
    UART_1_UartPutString("BARO INIT COMPLETE\r\n");
}

void BMP180_baro_trigger_temp(void)
{
    write_BMP180_registry(BMP180_REG_CONTROL, BMP180_COMMAND_TEMPERATURE);
}

int32_t BMP180_baro_read_temp(void)
{
        int16_t t_raw = (int16_t) read_BMP180_registry(BMP180_REG_RESULT);
        //UART_1_UartPutString("\r\nT RAW: ");
        //UART_1_UartPutNum(t_raw);
        int32_t x1 = (t_raw-AC6)*AC5/(32768); // 2^15 = 32768
        //UART_1_UartPutString("\r\nT_x1: ");
        //UART_1_UartPutNum(x1);
        
        int32_t x2 = (MC*2048)/(x1+MD);       // 2^11 = 2048
        //UART_1_UartPutString("\r\nT_x2: ");
        //UART_1_UartPutNum(x2);
        
        B5 = x1+x2;   // B5 is also used for the pressure reading
        //UART_1_UartPutString("\r\nB5: ");
        //UART_1_UartPutNum(B5);
        int32_t t_true = ((B5+8)/16)/10;      // by 10 for degC (check datasheet page 15)
        return t_true;
}

void BMP180_baro_trigger_pressure(void)
{
    // Using Ultra Low Power Mode with 4.5ms conversion time
    write_BMP180_registry(BMP180_REG_CONTROL, BMP180_COMMAND_PRESSURE0);
}

int32_t BMP180_baro_read_pressure(void)
{
        uint16_t p_raw = (uint16_t)read_BMP180_registry(BMP180_REG_RESULT);
        //UART_1_UartPutString("\r\nP RAW: ");
        //UART_1_UartPutNum(p_raw);
        
        int32_t B6 = B5-4000;
        //UART_1_UartPutString("\r\nB6: ");
        //UART_1_UartPutNum(B6);
        
        int32_t x1 = (B2*((B6*B6)/4096))/2048;
        //UART_1_UartPutString("\r\nx1: ");
        //UART_1_UartPutNum(x1);
        
        int32_t x2 = AC2*B6 / 2048;
        //UART_1_UartPutString("\r\nx2: ");
        //UART_1_UartPutNum(x2);
        int32_t x3 = x1+x2;
        //UART_1_UartPutString("\r\nx3: ");
        //UART_1_UartPutNum(x3);
        
        int32_t B3 = ((AC1*4+x3)+2)/4;
        //UART_1_UartPutString("\r\nB3: ");
        //UART_1_UartPutNum(B3);
        
        x1 = AC3 * B6 / 8192;
        //UART_1_UartPutString("\r\nP_x1: ");
        //UART_1_UartPutNum(x1);
        
        x2 = (B1*(B6*B6/4096))/65536;
        //UART_1_UartPutString("\r\nP_x2: ");
        //UART_1_UartPutNum(x2);
        
        x3 = ((x1+x2)+2)/4;
        //UART_1_UartPutString("\r\nP_x3: ");
        //UART_1_UartPutNum(x3);
        
        uint32_t B4 = AC4*(uint32_t)(x3+32768)/32768;
        //UART_1_UartPutString("\r\nB4: ");
        //UART_1_UartPutNum(B4);
        
        uint32_t B7 = ((uint32_t)p_raw - B3) * (50000);
        //UART_1_UartPutString("\r\nB7: ");
        //UART_1_UartPutNum(B7);
        
        int32_t p_true = 0;
        if(B7 < 0x80000000)
        {
            p_true = B7*2/B4;    
        }
        else p_true = (B7/B4)*2;
        //UART_1_UartPutString("\r\nP: ");
        //UART_1_UartPutNum(p_true);
        
        x1 = (p_true / 256)*(p_true / 256);
                //UART_1_UartPutString("\r\nP_x1: ");
        //UART_1_UartPutNum(x1);
        
        x1 = (x1*3038)/65536;
                        //UART_1_UartPutString("\r\nP_x1: ");
        //UART_1_UartPutNum(x1);
        
        x2 = (-7357*p_true)/65536;
                //UART_1_UartPutString("\r\nP_x2: ");
        //UART_1_UartPutNum(x2);
        p_true = p_true + ((x1+x2+3791)/16);
                         //UART_1_UartPutString("\r\nP_TRUE: ");
        //UART_1_UartPutNum(p_true);               
        // by 10 for degC (check datasheet page 15)
        return p_true;
}

#ifdef bla
void BMP180_read_altitude(void)
{
        cnt_baro++;
        if(cnt_baro == 49)
        {
            // Trigger Temperature conversion and wait min 4.5ms
            BMP180_baro_trigger_temp();
        }
        if(cnt_baro == 50)
        {
            // Read temperature from Barometer
            temp = BMP180_baro_read_temp();

            UART_1_UartPutNum(temp);
            UART_1_UartPutString("; ");
        }
        if(cnt_baro == 51)
        {
            // Trigger pressure conversion and wait min 4.5ms
            BMP180_baro_trigger_pressure();
        }
        if(cnt_baro == 52)
        {
            
            // Read pressure and calculate pressure output
            press = BMP180_baro_read_pressure();
            UART_1_UartPutNum(press/100);
            UART_1_UartPutString("; ");
        }
        if(cnt_baro == 53)
        {
            cnt_baro = 0;
            // Calculate Altitude
            /* replace STD pressure with calibrated pressure */
            alt = (101325-(press))*0.0843;  // pressure in Pa -> 0.0843m / Pa of change
            
            //alt = 44330*(1-(((press/100)/1013)^(1/5)));
            UART_1_UartPutNum(alt);
            UART_1_UartPutString("\r\n");
        }
        return;
}
#endif
/* [] END OF FILE */
