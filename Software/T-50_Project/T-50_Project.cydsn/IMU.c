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

// #include <project.h>     // this is included in IMU.h file
#include <IMU.h>

extern void UART_1_UartPutNum();

#define READ    1
#define WRITE   0
#define ACK     0
#define NACK    1

/* Gyro subcomponents*/



/* x component*/
int8_t	gyro_x_h	= 0;
uint8_t gyro_x_l	= 0;
int16_t gyro_x		= 0;
extern int16_t turn_rate_p;
int16_t	gyro_p		= 0;

/* y component*/
int8_t	gyro_y_h	= 0;
uint8_t gyro_y_l	= 0;
int16_t gyro_y		= 0;
int16_t	gyro_q		= 0;
extern int16_t turn_rate_q;

/* z component*/
int8_t	gyro_z_h	= 0;
uint8_t gyro_z_l	= 0;
int16_t gyro_z		= 0;
int16_t	gyro_r		= 0;
extern int16_t turn_rate_r;

// Gyro temperature
int8_t	temperature	= 0;
uint8_t temperature_0	= 50;

// Gyro Calibration Variables
// idea: count 100 samples (IMU needs to be steady) and calculate the offset

int16_t gyro_p_offset = 0;
int16_t gyro_q_offset = 0;
int16_t gyro_r_offset = 0;
//int cal_complete = FALSE;	// Flag to cover if the calibration is complete
uint8_t error_stat = 0;

void write_gyro_registry_OLD(uint8_t registry, uint8_t data)
{
    I2CM_I2CMasterSendStart(L3GD20H_ADDRESS_SA0_HIGH, WRITE);
	I2CM_I2CMasterWriteByte(registry);
    I2CM_I2CMasterWriteByte(data);
    I2CM_I2C_MASTER_GENERATE_STOP;
    UART_1_UartPutString("W Stop Ok");
}
void write_gyro_registry(uint8_t registry, uint8_t data)
{
    I2CM_I2CMasterSendStart(L3GD20H_ADDRESS_SA0_HIGH, WRITE);
	UART_1_UartPutString("W Add Ok");
	I2CM_I2CMasterWriteByte(registry);
    UART_1_UartPutString("W Reg Ok");
    I2CM_I2CMasterWriteByte(data);
    UART_1_UartPutString("W Dat Ok");
    I2CM_I2C_MASTER_GENERATE_STOP;
    UART_1_UartPutString("W Stop Ok");    
}


int8_t read_gyro_registry(uint8_t registry)
{
	uint8_t data;
	I2CM_I2CMasterSendStart(L3GD20H_ADDRESS_SA0_HIGH, WRITE);
	I2CM_I2CMasterWriteByte(registry);
	I2CM_I2CMasterSendRestart(L3GD20H_ADDRESS_SA0_HIGH, READ);
	data = I2CM_I2CMasterReadByte(NACK);
    I2CM_I2C_MASTER_GENERATE_STOP;
    return(data);
}

void gyro_start(void)
{
    // CTRL REG 1
	write_gyro_registry(L3GD20H_CTRL_REG1, 0x0F);		// Enabling all axes read out and Power On -> 100 Hz output data rate
    //UART_1_UartPutNum(read_gyro_registry(L3GD20H_CTRL_REG1));
    // CTRL REG 2
	write_gyro_registry(L3GD20H_CTRL_REG2, 0x20);		// Normal Mode of High Pass Filter (High Bits), Filter Rate (Low Bits 0-9), Output Data Rate to 100 Hz (default)
    //UART_1_UartPutNum(read_gyro_registry(L3GD20H_CTRL_REG2));
    // CTRL REG 5
	write_gyro_registry(L3GD20H_CTRL_REG5, 0x10);		// High Pass Filter Enable (High Bit 1)
    //UART_1_UartPutNum(read_gyro_registry(L3GD20H_CTRL_REG5));
    UART_1_UartPutString("gyro started\r\n");
}

// Gyro turn rate reading
void gyro_read(void)
{
    struct turn_rates_s turns;
    I2CM_I2CMasterSendStart(L3GD20H_ADDRESS_SA0_HIGH, WRITE);
	I2CM_I2CMasterWriteByte(L3GD20H_OUT_X_L + 0b10000000); // add MSB to activate auto increment
	I2CM_I2CMasterSendRestart(L3GD20H_ADDRESS_SA0_HIGH, READ);
	gyro_x_l = I2CM_I2CMasterReadByte(ACK);
	gyro_x_h = I2CM_I2CMasterReadByte(ACK);
    gyro_y_l = I2CM_I2CMasterReadByte(ACK);
	gyro_y_h = I2CM_I2CMasterReadByte(ACK);
	gyro_z_l = I2CM_I2CMasterReadByte(ACK);
	gyro_z_h = I2CM_I2CMasterReadByte(NACK);
    I2CM_I2C_MASTER_GENERATE_STOP;
    gyro_x = (gyro_x_h<<8) | (gyro_x_l);
	gyro_y = (gyro_y_h<<8) | (gyro_y_l);
	gyro_z = (gyro_z_h<<8) | (gyro_z_l);
    turn_rate_p = gyro_x * 0.00875;						// the conversion comes from the default sensitivity value: FS = 250dps	-> 8.75mdps/digit
	turn_rate_q = gyro_y * 0.00875;
	turn_rate_r = gyro_z * 0.00875;						// see gyro datasheet page 10    
}


/* [] END OF FILE */
