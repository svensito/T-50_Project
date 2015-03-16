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

#if !defined(IMU_H)
#define IMU_H

#include <project.h>
    
// #################################
// Gyro addresses                   
#define L3GD20H_ADDRESS_SA0_LOW  (0b1101010)      // as per Datasheet of L3GD20H p 28
#define L3GD20H_ADDRESS_SA0_HIGH (0b1101011)
// as per Default the SA0 Bit is set high!!!
// the 7 bit address is extended with the 8th bit for read / write access
#define L3GD20H_ADDRESS_READ		0b11010111		//  11010111	for reading
#define L3GD20H_ADDRESS_WRITE	    0b11010110		//  11010110    for writing

// Gyro registers
#define L3GD20H_WHO_AM_I		0x0F
#define L3GD20H_CTRL_REG1		0x20
#define L3GD20H_CTRL_REG2		0x21
#define L3GD20H_CTRL_REG3		0x22
#define L3GD20H_CTRL_REG4		0x23
#define L3GD20H_CTRL_REG5		0x24
#define L3GD20H_OUT_TEMP		0x26
#define L3GD20H_STATUS_REG		0x27
#define L3GD20H_OUT_X_L			0x28
#define L3GD20H_OUT_X_H			0x29
#define L3GD20H_OUT_Y_L			0x2A
#define L3GD20H_OUT_Y_H			0x2B
#define L3GD20H_OUT_Z_L			0x2C
#define L3GD20H_OUT_Z_H			0x2D

//###################################
// Gyro Functions
/* Gyro reading*/

void gyro_start(void);
void temp_read(void);
int8_t read_gyro_registry(uint8_t registry);
void write_gyro_registry(uint8_t registry, uint8_t data);

volatile struct turn_rates_s
{
    long p,q,r;
};

void gyro_read(void);
int16_t gyro_read_p(void);
//struct turn_rates_obj gyro_read(void);
void gyro_calibration(void);

// #################################
// LSM303 D Accelerometer & Magnetometer
// 7 bit Address is
#define LSM303_ADDRESS              0b0011101   // as per Datasheet o 22 - SA0 is High by default
#define LSM303_ACC_ADDRESS_READ		0x33	// 0011 0011
#define LSM303_ACC_ADDRESS_WRITE	0x32	// 0011 0010

// Control Registers LSM303
#define LSM303_MAG_WHO_AM_I			0x0F
#define LSM303_MAG_CRA_REG			0x00
#define LSM303_MAG_CRB_REG			0x01
#define LSM303_MAG_MR_REG			0x02
#define LSM303_CTRL_REG0		    0x1F
#define LSM303_CTRL_REG1		    0x20
#define LSM303_CTRL_REG2		    0x21
#define LSM303_CTRL_REG3		    0x22
#define LSM303_CTRL_REG4		    0x23
#define LSM303_CTRL_REG5		    0x24
#define LSM303_CTRL_REG6		    0x25
#define LSM303_CTRL_REG7		    0x26

//Accelerometer registers
#define LSM303_ACC_REF				0x26
#define LSM303_ACC_STAT_REG			0x27
#define LSM303_ACC_OUT_X_L			0x28
#define LSM303_ACC_OUT_X_H			0x29
#define LSM303_ACC_OUT_Y_L			0x2A
#define LSM303_ACC_OUT_Y_H			0x2B
#define LSM303_ACC_OUT_Z_L			0x2C
#define LSM303_ACC_OUT_Z_H			0x2D

// Magnetometer registers
#define LSM303_MAG_STAT_REG			0x07
#define LSM303_MAG_OUT_X_L			0x08
#define LSM303_MAG_OUT_X_H			0x09
#define LSM303_MAG_OUT_Z_L			0x0A
#define LSM303_MAG_OUT_Z_H			0x0B
#define LSM303_MAG_OUT_Y_L			0x0C
#define LSM303_MAG_OUT_Y_H			0x0D

// Temp Sensor register
#define LSM303_MAG_TEMP_L			0x05
#define LSM303_MAG_TEMP_H			0x06

//###################################
// ACC Functions
/* ACC reading*/

// Function prototypes
void write_acc_registry(char registry, char data);
void acc_start(void);
struct acc_readings_obj acc_reading(void);

void write_mag_registry(char registry, char data);
void mag_start(void);

// #################################
// Magnetometer address
#define LSM303_MAG_ADDRESS_READ		0x3D	// 0011 1101	as per Pololu website and Datasheet
#define LSM303_MAG_ADDRESS_WRITE	0x3C	// 0011 1100

// Magnetometer Registers




// Function prototypes


// #################################
// Barometer Addresses
#define MPL3115A2_ADDRESS_READ		0xC1	// 1100 0001
#define MPL3115A2_ADDRESS_WRITE		0xC0	// 1100 0000

// Barometer Registers
#define MPL3115A2_STATUS			0x00
#define MPL3115A2_OUT_P_MSB			0x01
#define MPL3115A2_OUT_P_CSB			0x02
#define MPL3115A2_OUT_P_LSB			0x03
#define MPL3115A2_OUT_T_MSB			0x04
#define MPL3115A2_OUT_T_LSB			0x05
#define MPL3115A2_STATUS_DR			0x06
#define MPL3115A2_OUT_P_DELTA_MSB	0x07
#define MPL3115A2_OUT_P_DELTA_CSB	0x08
#define MPL3115A2_OUT_P_DELTA_LSB	0x09
#define MPL3115A2_OUT_T_DELTA_MSB	0x0A
#define MPL3115A2_OUT_T_DELTA_LSB	0x0B
#define MPL3115A2_WHO_AM_I			0x0C
#define MPL3115A2_INT_SOURCE		0x12
#define MPL3115A2_PT_DATA_CFG		0x13
#define MPL3115A2_BAR_IN_MSB		0x14
#define MPL3115A2_BAR_IN_LSB		0x15
#define MPL3115A2_P_TGT_MSB			0x16
#define MPL3115A2_P_TGT_LSB			0x17
#define MPL3115A2_T_TGT				0x18
#define MPL3115A2_P_WND_MSB			0x19
#define MPL3115A2_P_WND_LSB			0x1A
#define MPL3115A2_T_WND				0x1B
#define MPL3115A2_CTRL_REG1			0x26
#define MPL3115A2_CTRL_REG2			0x27
#define MPL3115A2_CTRL_REG3			0x28
#define MPL3115A2_CTRL_REG4			0x29
#define MPL3115A2_CTRL_REG5			0x2A

// Function prototypes
void write_baro_registry(char registry, char data);
void baro_start(void);
void baro_read(void);
void baro_calibration(void);


#endif  // endif IMU_H
/* [] END OF FILE */
