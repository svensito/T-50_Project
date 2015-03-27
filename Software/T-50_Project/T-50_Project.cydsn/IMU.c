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

/* ================================= */
/* GYRO VARIABLES					*/
/* ================================= */

/* x component*/
int8_t	gyro_x_h	= 0;
uint8_t gyro_x_l	= 0;
int16_t gyro_x		= 0;
extern int16_t turn_rate_p;		// from main.c file
int16_t	gyro_p		= 0;

/* y component*/
int8_t	gyro_y_h	= 0;
uint8_t gyro_y_l	= 0;
int16_t gyro_y		= 0;
int16_t	gyro_q		= 0;
extern int16_t turn_rate_q;		// from main.c file

/* z component*/
int8_t	gyro_z_h	= 0;
uint8_t gyro_z_l	= 0;
int16_t gyro_z		= 0;
int16_t	gyro_r		= 0;
extern int16_t turn_rate_r;		// from main.c file

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

/* ================================= */
/* ACC & MAG VARIABLES					*/
/* ================================= */

int8_t	acc_x_h		= 0;		// high bits of acc x reading
uint8_t	acc_x_l		= 0;		// low bits of acc x reading
int16_t acc_x		= 0;		// combined value of acc x reading
extern int16_t	acc_x_g;		// acc_x from main.c file

int8_t	acc_y_h		= 0;		// high bits of acc x reading
uint8_t	acc_y_l		= 0;		// low bits of acc x reading
int16_t acc_y		= 0;		// combined value of acc x reading
extern int16_t	acc_y_g;		// acc_y from main.c file

int8_t	acc_z_h		= 0;		// high bits of acc x reading
uint8_t	acc_z_l		= 0;		// low bits of acc x reading
int16_t acc_z		= 0;		// combined value of acc x reading
extern int16_t	acc_z_g;		// acc_z from main.c file

int8_t	mag_x_h		= 0;		// high bits of mag x reading
uint8_t	mag_x_l		= 0;		// low bits of mag x reading
int16_t mag_x		= 0;		// the value read on the x axis of the magnetometer
extern int16_t	mag_x_g;		// the geodetic reference frame value of x

int8_t	mag_y_h		= 0;		// high bits of mag y reading
uint8_t	mag_y_l		= 0;		// low bits of mag y reading
int16_t mag_y		= 0;		// the value read on the y axis of the magnetometer
extern int16_t	mag_y_g;		// the geodetic reference frame value of y

int8_t	mag_z_h		= 0;		// high bits of mag z reading
uint8_t	mag_z_l		= 0;		// low bits of mag z reading
int16_t mag_z	= 0;		// the value read on the z axis of the magnetometer
extern int16_t	mag_z_g;		// the geodetic reference frame value of y

/* ================================= */
/* BAROMETER VARIABLES				 */
/* ================================= */
uint8_t bar_h    = 0;    // high byte
uint8_t bar_l   = 0;    // middle byte
uint8_t bar_xl  = 0;    // lowest byte
extern uint32_t Bar_press;   // Barometric Pressure
/* ================================= */
/* GYRO FUNCTIONS					*/
/* ================================= */
void write_gyro_registry(uint8_t registry, uint8_t data)
{
    I2CM_I2CMasterSendStart(L3GD20H_ADDRESS_SA0_HIGH, WRITE);
	UART_1_UartPutString("GYR W Add Ok\r\n");
	I2CM_I2CMasterWriteByte(registry);
    UART_1_UartPutString("GYR W Reg Ok\r\n");
    I2CM_I2CMasterWriteByte(data);
    UART_1_UartPutString("GYR W Dat Ok\r\n");
    I2CM_I2C_MASTER_GENERATE_STOP;
    UART_1_UartPutString("GYR W Stop Ok\r\n");    
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
    UART_1_UartPutString("Gyro started\r\n");
}

// Gyro turn rate reading
void gyro_read(void)
{
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

/* ================================= */
/* ACC & MAG FUNCTIONS					*/
/* ================================= */

/*  ACCELEROMETER FUNCTIONS */

void write_acc_registry(char registry, char data)
{
	I2CM_I2CMasterSendStart(LSM303_ADDRESS, WRITE);
	UART_1_UartPutString("ACC W Add Ok");
	I2CM_I2CMasterWriteByte(registry);
    UART_1_UartPutString("ACC W Reg Ok");
    I2CM_I2CMasterWriteByte(data);
    UART_1_UartPutString("ACC W Dat Ok");
    I2CM_I2C_MASTER_GENERATE_STOP;
    UART_1_UartPutString("ACC W Stop Ok"); 
}
void acc_start(void)
{
	// CTRL REG 1
	write_acc_registry(LSM303_CTRL_REG1, 0x67);		// Enabling all axes read out and Power On -> 100 Hz output data rate
    //UART_1_UartPutNum(read_acc_registry(LSM303_CTRL_REG1));
    // CTRL REG 2
	
    //write_mag_registry(LSM303_CTRL_REG6, 0x20);		// Magnetometer FS +-4Gauss
    //UART_1_UartPutNum(read_acc_registry(LSM303_CTRL_REG2));
    UART_1_UartPutString("Acc started\r\n");
}

void acc_read(void)
{
	I2CM_I2CMasterSendStart(LSM303_ADDRESS, WRITE);
	I2CM_I2CMasterWriteByte(LSM303_ACC_OUT_X_L + 0b10000000); // add MSB to activate auto increment
	I2CM_I2CMasterSendRestart(LSM303_ADDRESS, READ);
	acc_x_l = I2CM_I2CMasterReadByte(ACK);
	acc_x_h = I2CM_I2CMasterReadByte(ACK);
    acc_y_l = I2CM_I2CMasterReadByte(ACK);
	acc_y_h = I2CM_I2CMasterReadByte(ACK);
	acc_z_l = I2CM_I2CMasterReadByte(ACK);
	acc_z_h = I2CM_I2CMasterReadByte(NACK);
    I2CM_I2C_MASTER_GENERATE_STOP;
    acc_x = (acc_x_h<<8) | (acc_x_l);
	acc_y = (acc_y_h<<8) | (acc_y_l);
	acc_z = (acc_z_h<<8) | (acc_z_l);
    acc_x_g = acc_x * 0.122;	// milli G										
	acc_y_g = acc_y * 0.122;	// milli G					// Linear Acceleration at 4G gives 0.122mg/bit
	acc_z_g = acc_z * 0.122;	// milli G					// see ACC datasheet page 10  
}

/*  MAGNETOMETER FUNCTIONS */

void write_mag_registry(char registry, char data)
{
	I2CM_I2CMasterSendStart(LSM303_ADDRESS, WRITE);
	UART_1_UartPutString("W Add Ok");
	I2CM_I2CMasterWriteByte(registry);
    UART_1_UartPutString("W Reg Ok");
    I2CM_I2CMasterWriteByte(data);
    UART_1_UartPutString("W Dat Ok");
    I2CM_I2C_MASTER_GENERATE_STOP;
    UART_1_UartPutString("W Stop Ok"); 
}

void mag_start(void)
{
	// CTRL REG 1
	write_mag_registry(LSM303_CTRL_REG6, 0x20);		// Magnetometer FS +-4Gauss
    //UART_1_UartPutNum(read_acc_registry(LSM303_CTRL_REG1));
    // CTRL REG 2
	write_mag_registry(LSM303_CTRL_REG7, 0x00);		// Putting Magnetometer into Continuous Conversion Mode
    //UART_1_UartPutNum(read_acc_registry(LSM303_CTRL_REG2));
    UART_1_UartPutString("Mag started\r\n");
}

void mag_read(void)
{
	I2CM_I2CMasterSendStart(LSM303_ADDRESS, WRITE);
	I2CM_I2CMasterWriteByte(LSM303_MAG_OUT_X_L + 0b10000000); // add MSB to activate auto increment
	I2CM_I2CMasterSendRestart(LSM303_ADDRESS, READ);
	mag_x_l = I2CM_I2CMasterReadByte(ACK);
	mag_x_h = I2CM_I2CMasterReadByte(ACK);
    mag_y_l = I2CM_I2CMasterReadByte(ACK);
	mag_y_h = I2CM_I2CMasterReadByte(ACK);
	mag_z_l = I2CM_I2CMasterReadByte(ACK);
	mag_z_h = I2CM_I2CMasterReadByte(NACK);
    I2CM_I2C_MASTER_GENERATE_STOP;
    mag_x = (mag_x_h<<8) | (mag_x_l);
	mag_y = (mag_y_h<<8) | (mag_y_l);
	mag_z = (mag_z_h<<8) | (mag_z_l);
    mag_x_g = mag_x * 0.16;	// milli Gauss		    // bla					
	mag_y_g = mag_y * 0.16;	// milli Gauss			// Magnetic sensitivity at 4Gauss gives 0.16 mgauss/bit
	mag_z_g = mag_z * 0.16;	// milli Gauss			// see Mag datasheet page 10  
}

/* ================================= */
/* BAROMETER FUNCTIONS				 */
/* ================================= */

void write_baro_registry(char registry, char data)
{
    I2CM_I2CMasterSendStart(LPS25H_ADDRESS, WRITE);
	//UART_1_UartPutString("B W Add Ok");
	I2CM_I2CMasterWriteByte(registry);
    //UART_1_UartPutString("B W Reg Ok");
    I2CM_I2CMasterWriteByte(data);
    //UART_1_UartPutString("B W Dat Ok");
    I2CM_I2C_MASTER_GENERATE_STOP;
    //UART_1_UartPutString("B W Stop Ok"); 
}

void baro_start(void)
{
    write_baro_registry(LPS25H_CTRL_REG1,0xC6);         // Enabling the Baro, 25Hz output, enable Block Data Update
    UART_1_UartPutString("Baro Started");
}

void baro_read(void)
{
    I2CM_I2CMasterSendStart(LPS25H_ADDRESS, WRITE);
	I2CM_I2CMasterWriteByte(LPS25H_P_OUT_XL + 0b10000000); // add MSB to activate auto increment
	I2CM_I2CMasterSendRestart(LSM303_ADDRESS, READ);
	bar_xl = I2CM_I2CMasterReadByte(ACK);
	bar_l = I2CM_I2CMasterReadByte(ACK);
    bar_h = I2CM_I2CMasterReadByte(NACK);
    I2CM_I2C_MASTER_GENERATE_STOP;
    uint32_t press_temp = (bar_l<<8) | (bar_xl);
    press_temp = (bar_h << 16) | press_temp;
    
    Bar_press = press_temp / 4096;      // 4096 bit / hPa = 4096 bit / mbar
    
}

/* [] END OF FILE */
