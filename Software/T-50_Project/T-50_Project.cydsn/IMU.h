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

#ifdef ALTIMU    
    
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
void gyro_read(void);
void gyro_calibration(void);

// #################################
// LSM303 D Accelerometer & Magnetometer
// 7 bit Address is
#define LSM303_ADDRESS              0b0011101   // as per Datasheet o 22 - SA0 is High by default

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
// LSM303 Functions

// Function prototypes
void write_acc_registry(char registry, char data);
void acc_start(void);
void acc_read(void);

void write_mag_registry(char registry, char data);
void mag_start(void);
void mag_read(void);

// #################################
// Barometer Addresses
#define LPS25H_ADDRESS				0b1011101	// as per LPS25H Datasheet

// Barometer Registers
#define LPS25H_WHO_AM_I				0x0F
#define LPS25H_RES_CONF				0x10
#define LPS25H_CTRL_REG1			0x20
#define LPS25H_CTRL_REG2			0x21
#define LPS25H_CTRL_REG3			0x22
#define LPS25H_CTRL_REG4			0x23
#define LPS25H_STATUS				0x27

#define LPS25H_P_OUT_XL				0x28
#define LPS25H_P_OUT_L				0x29
#define LPS25H_P_OUT_H				0x2A
#define LPS25H_T_OUT_L				0x2B
#define LPS25H_T_OUT_H				0x2C


// Function prototypes
void write_baro_registry(char registry, char data);
void baro_start(void);
int32_t baro_read(void);
void baro_calibration(void);

#endif  /* ALTIMU */

//#ifdef MPU6050    // How To add a "symbol" for the precompiler?
/*===========================*/
/*      MPU6050              */
/*===========================*/
#define MPU6050_ADDRESS         0x68 // 7Bit I2C address -> Read & Write is set when communicating
                                //0x69  // This is AD0 to VCC
#define MPU6050_WHO_AM_I        0x75
#define MPU6050_CONFIG          0x1A
#define MPU6050_GYRO_CONFIG     0x1B
#define MPU6050_ACC_CONFIG      0x1C

#define MPU6050_ACC_XOUT_H      0x3B
#define MPU6050_ACC_XOUT_L      0x3C
#define MPU6050_ACC_YOUT_H      0x3D
#define MPU6050_ACC_YOUT_L      0x3E
#define MPU6050_ACC_ZOUT_H      0x3F
#define MPU6050_ACC_ZOUT_L      0x40

#define MPU6050_GYRO_XOUT_H      0x43
#define MPU6050_GYRO_XOUT_L      0x44
#define MPU6050_GYRO_YOUT_H      0x45
#define MPU6050_GYRO_YOUT_L      0x46
#define MPU6050_GYRO_ZOUT_H      0x47
#define MPU6050_GYRO_ZOUT_L      0x48

#define MPU6050_PWR_MGMT_1       0x6B
#define MPU6050_PWR_MGMT_2       0x6C

void MPU6050_Init(void);
void MPU6050_acc_read(void);
void MPU6050_gyro_read(void);
void MPU6050_data_read(void);

/*===========================*/
/*      HMC5883L           */
/*===========================*/

#define HMC_ADDRESS             0x1E    // as per datasheet page 11

#define HMC_CONFIG_A            0x00
#define HMC_CONFIG_B            0x01
#define HMC_MODE                0x02
#define HMC_OUT_X_H             0x03
#define HMC_OUT_X_L             0x04
#define HMC_OUT_Z_H             0x05
#define HMC_OUT_Z_L             0x06
#define HMC_OUT_Y_H             0x07
#define HMC_OUT_Y_L             0x08
#define HMC_STATUS              0x09
#define HMC_ID_A                0x0A
#define HMC_ID_B                0x0B
#define HMC_ID_C                0x0C

void HMC_Init(void);
void HMC_data_read(void);

#endif  // endif IMU_H
/* [] END OF FILE */
