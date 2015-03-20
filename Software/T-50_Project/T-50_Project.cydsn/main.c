/* ========================================
 *
 * Copyright SNFU
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * T-50_Project
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <IMU.h>
#include <common/mavlink.h>
#include <mavlink_types.h>

#define FALSE   0
#define TRUE    1

#define PI			3.1415926535897932384626433832795

volatile uint8_t task_flag = FALSE;     // The Task Flag is set in TaskISR Interrupt Routine
volatile uint8_t blink_cnt = 0;
float sample_time = 0.01;               // 10 ms Sample time

/*=============================*/
/* TASK Flags*/
/*=============================*/



/*=============================*/
/*Remote Input variables*/
/*=============================*/
uint8_t PPM_channel = 0;                    // input channel variable
uint16_t ctrl_in[8] = {0};                  // input control vector
uint16_t ctrl_out[13] = {0};                // output control vector

enum e_in{   // Input Control Enum - 8 Channels
    in_mot = 0,
    in_ail,
    in_ele,
    in_rud,
    in_fl,
    in_ge,
    in_sp1,
    in_sp2
};

enum e_out{   // Output Control Enum - 13 Signals
    out_mot = 0,
    out_ail1,
    out_ail2,
    out_ele1,
    out_ele2,
    out_rud,
    out_fl1,
    out_fl2,
    out_ge1,
    out_ge2,
    out_ge3,
    out_sp1,
    out_sp2
};

/*=============================*/
/*Light control variables*/
/*=============================*/
uint8_t flag_LightsEnabled = TRUE;

/*Nav Light Control START -> Pulsing of the Navigation Lights*/
uint8_t flag_NavLightPulse  = FALSE;    // Nav Light Pulse flag (to count up or down)
uint16_t NavLightBright     = 100;  // Upper value for the brightness 100 = 100%
uint16_t NavLightDim        = 0;    // Lower value for the brightness 0 = 0%
uint16_t NavLightStep       = 1;    // Nav Light Pulse Stepwidth => brightness change per 10ms
uint16_t NavLightCompare    = 0;    // Nav Light PWM Compare Value
/*Nav Light Control END*/

/*=============================*/
/*IMU variables*/
/*=============================*/
#define GYRO_TASK   TRUE
#define ACC_TASK    TRUE
#define MAG_TASK    FALSE

/* turn rates */
int16_t turn_rate_p = 0;
int16_t turn_rate_q = 0;
int16_t turn_rate_r = 0;
/* accelerations*/
int16_t acc_x_g = 0;
int16_t acc_y_g = 0;
int16_t acc_z_g = 0;
/* magnetic out*/
int16_t mag_x_g = 0;
int16_t mag_y_g = 0;
int16_t mag_z_g = 0;

/* Euler Angles */
int16_t Theta, Theta_acc = 0;   // Theta => estimated angle after Kalman, Theta_acc => Theta from accelerometer
int16_t Phi, Phi_acc = 0;       // Phi => estimated angle after Kalman, Phi_acc => Theta from accelerometer



/*=============================*/
/* Kalman Filter Data			*/
/*=============================*/
// weighing matrices ???
float Q_angle = 0.005;
float Q_gyro = 0.005;
float R_angle = 0.02;
// Estimation of Theta (Kalman)
float q_bias = 0;
float P_00_Theta, P_01_Theta, P_10_Theta, P_11_Theta = 0;
float Theta_temp, S_Theta, K_0_Theta, K_1_Theta = 0;
// Estimation of Phi (Kalman)
float p_bias = 0;
float P_00_Phi, P_01_Phi, P_10_Phi, P_11_Phi = 0;
float Phi_temp, S_Phi, K_0_Phi, K_1_Phi = 0;

/*=============================*/
/* MAVLINK			*/
/*=============================*/
mavlink_system_t mavlink_system;
// Define the system type, in this case an airplane
uint8_t system_type = MAV_TYPE_FIXED_WING;        //MAV_TYPE_FIXED_WING;
uint8_t autopilot_type = MAV_AUTOPILOT_GENERIC;     //MAV_AUTOPILOT_GENERIC;

uint8_t system_mode = MAV_MODE_PREFLIGHT;       ///< Booting up //
uint32_t custom_mode = 0;                       ///< Custom mode, can be defined by user/adopter
uint8_t system_state = MAV_STATE_STANDBY;       ///< System ready for flight

// Initialize the required buffers
mavlink_message_t msg;
uint8_t buf[MAVLINK_MAX_PACKET_LEN];

uint8_t cnt_ML_HEARTBEAT_send = 0;          // used for timing of the HEARTBEAT message sending
uint8_t cnt_ML_ATTITUDE_send = 0;           // used for timing of the ATTITUDE message sending

/*=============================*/
/* General Functions */
/*=============================*/
// UART Put Num to write serial number data
void UART_1_UartPutNum(int32_t num)
{
    char k[31];
    sprintf(k,"%d",num);
    UART_1_UartPutString(k);   
}

// UART Put Num to write serial number data
void UART_1_UartSendMavlink(uint8_t buf[], uint16_t len)
{
    uint16_t i = 0;
    UART_1_UartPutChar(0xFE);   // message header    
    while(i<(len+1))
	{
        i++;
        UART_1_UartPutChar(buf[i]);
	}  
}

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CyGlobalIntEnable; 

    UART_1_Start();     /* Enabling the UART */
    I2CM_Start();
    CyDelay(500);
    TaskTimer_Start();
    NavLightPWM_Start();
    PPMCounter_Start();
    ServoTimer_Start();
    PPMISR_Start();
    PPMRstISR_Start();
    ServoISR_Start();
    TaskISR_Start();
    BootISR_Start();
       
    // Mavlink Initialization
    mavlink_system.sysid = 58;     ///< ID 25 for this airplane
    mavlink_system.compid = 58;     ///< The component ID
    
    UART_1_UartPutString("UART OK\r\n");
    
    //if(GYRO_TASK == TRUE) gyro_start();
    //if(ACC_TASK == TRUE) acc_start();
    //if(MAG_TASK == TRUE) mag_start();
    uint8_t test = read_gyro_registry(L3GD20H_CTRL_REG1);
    //UART_1_UartPutNum(test);
    UART_1_UartPutString("Started OK\r\n");
    //CyDelay(500);
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        
        if(task_flag == TRUE)
        {
            /*=======================================
                Main Task that is executed every 10ms
              =======================================*/
            task_flag = FALSE;
            
//            blink_cnt++;
//            if(blink_cnt == 10)
//            {
//                blink_cnt = 0;   
//       
//            }
//            if(blink_cnt == 100)
//            {
//                //Pin_2_Write(0xFF);
//                
//            }
//            if(blink_cnt == 110)
//            {
//                blink_cnt = 0;
//                //Pin_2_Write(0x00);    
//            }
//            //NavLightCompare++;
//            //NavLightPWM_WriteCompare(NavLightCompare);      
            
            /*=======================================
                Light Control
              =======================================*/
            
            if(flag_LightsEnabled == TRUE)
            {
                /* Lights enabled */
                // START PWM FOR NAV LIGHTS HERE??
                if(NavLightCompare == NavLightBright)
                {
                    flag_NavLightPulse = TRUE;
                }
                else if (NavLightCompare == NavLightDim)
                {
                    flag_NavLightPulse = FALSE;
                }
                if(flag_NavLightPulse == 0)
                {
                    NavLightCompare+=NavLightStep;
                    NavLightPWM_WriteCompare(NavLightCompare);
                }
                else
                {
                    NavLightCompare-=NavLightStep;
                    NavLightPWM_WriteCompare(NavLightCompare);
                }
            }
            else
            {
                /* Lights disabled*/
            }
            
            /*=======================================
                Sensor Reading
              =======================================*/
            //turn_rate_p = gyro_read_p();
            //UART_1_UartPutNum(turn_rate_p);
            if(GYRO_TASK == TRUE)
            {
                gyro_read();
            }
            if(ACC_TASK == TRUE)
            {
                acc_read();
            }
            if(MAG_TASK == TRUE)
            {
                mag_read();
            }
            
            /* Theta and Phi out of acceleration data*/
            Theta_acc = (atan2(acc_x_g,-acc_z_g))*180/PI;
		    Phi_acc = (atan2(-acc_y_g,-acc_z_g))*180/PI;
        
			/*=========================================================*/
			/* Calculating the attitude by using Kalman Filtering START*/
			Theta += sample_time * (turn_rate_q-q_bias);
			
			P_00_Theta +=  - sample_time * ((P_10_Theta + P_01_Theta) - Q_angle);
			P_01_Theta +=  - sample_time * P_11_Theta;
			P_10_Theta = P_01_Theta;
			P_11_Theta +=  + Q_gyro * sample_time;
			
			
			Phi += sample_time * (turn_rate_p-p_bias);
			P_00_Phi +=  - sample_time * ((P_10_Phi + P_01_Phi) - Q_angle);
			P_01_Phi +=  - sample_time * P_11_Phi;
			P_10_Phi = P_01_Phi;
			P_11_Phi +=  + Q_gyro * sample_time;
			
		
			/*
			Psi += sample_time * (r_filt-r_bias);
			P_00_Psi +=  - sample_time * (P_10_Psi + P_01_Psi) + Q_angle * sample_time;
			P_01_Psi +=  - sample_time * P_11_Psi;
			P_10_Psi +=  - sample_time * P_11_Psi;
			P_11_Psi +=  + Q_gyro * sample_time;
			*/
			Theta_temp = Theta_acc - Theta;
			S_Theta = P_00_Theta + R_angle;
			K_0_Theta = P_00_Theta / S_Theta;
			K_1_Theta = P_10_Theta / S_Theta;
			
			Phi_temp = Phi_acc - Phi;
			S_Phi = P_00_Phi + R_angle;
			K_0_Phi = P_00_Phi / S_Phi;
			K_1_Phi = P_10_Phi / S_Phi;
			/*
			Psi_temp = mag - Psi;
			S_Psi = P_00_Psi + R_angle;
			K_0_Psi = P_00_Psi / S_Psi;
			K_1_Psi = P_10_Psi / S_Psi;
			*/
			Theta +=  K_0_Theta * Theta_temp;
			q_bias  +=  K_1_Theta * Theta_temp;
			P_00_Theta -= K_0_Theta * P_00_Theta;
			P_01_Theta -= K_0_Theta * P_01_Theta;
			P_10_Theta -= K_1_Theta * P_00_Theta;
			P_11_Theta -= K_1_Theta * P_01_Theta;
			
			Phi +=  K_0_Phi * Phi_temp;
			p_bias  +=  K_1_Phi * Phi_temp;
			P_00_Phi -= K_0_Phi * P_00_Phi;
			P_01_Phi -= K_0_Phi * P_01_Phi;
			P_10_Phi -= K_1_Phi * P_00_Phi;
			P_11_Phi -= K_1_Phi * P_01_Phi;
		
			
			/* Calculating the attitude by using Kalman Filtering END*/
			/*=======================================================*/
		
//            UART_1_UartPutNum(Theta);
//            UART_1_UartPutString(" ");
//            UART_1_UartPutNum(Phi);
//            UART_1_UartPutString(" \r\n");
                
                
            /*=======================================
                Output Control
              =======================================*/
        uint8_t debug = 1;
            if(debug == 0)
            {
                ctrl_out[out_mot] = ctrl_in[in_mot];    
                ctrl_out[out_ail1] = ctrl_in[in_ail];    
                ctrl_out[out_ail2] = ctrl_in[in_ail];
                ctrl_out[out_ele1] = ctrl_in[in_ele];
                ctrl_out[out_ele2] = ctrl_in[in_ele];
                ctrl_out[out_rud] = ctrl_in[in_rud];
                ctrl_out[out_fl1] = ctrl_in[in_fl];
                ctrl_out[out_fl2] = ctrl_in[in_fl];
                ctrl_out[out_ge1] = ctrl_in[in_ge];
                ctrl_out[out_ge2] = ctrl_in[in_ge];
                ctrl_out[out_ge3] = ctrl_in[in_ge];
                ctrl_out[out_sp1] = ctrl_in[in_sp1];
                ctrl_out[out_sp2] = ctrl_in[in_sp2];
            }
            else
            {
                ctrl_in[in_mot] = 1000;
                ctrl_out[out_mot] = ctrl_in[in_mot];    
                ctrl_out[out_ail1] = ctrl_in[in_mot];    
                ctrl_out[out_ail2] = ctrl_in[in_mot];
                ctrl_out[out_ele1] = ctrl_in[in_mot];
                ctrl_out[out_ele2] = ctrl_in[in_mot];
                ctrl_out[out_rud] = ctrl_in[in_mot];
                ctrl_out[out_fl1] = ctrl_in[in_mot];
                ctrl_out[out_fl2] = ctrl_in[in_mot];
                ctrl_out[out_ge1] = ctrl_in[in_mot];
                ctrl_out[out_ge2] = ctrl_in[in_mot];
                ctrl_out[out_ge3] = ctrl_in[in_mot];
                ctrl_out[out_sp1] = ctrl_in[in_mot];
                ctrl_out[out_sp2] = ctrl_in[in_mot];
            }
            
            /*=======================================
                Data Logging
              =======================================*/
            // Pack the message
            if((cnt_ML_HEARTBEAT_send % 20) == 0)  // 20*10ms = 200ms
            {
                mavlink_msg_attitude_pack(mavlink_system.sysid, mavlink_system.compid, &msg, 0, Phi, Theta, 0, 0,0,0);
                uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
                UART_1_UartSendMavlink(buf, len);
            }
            
            if((cnt_ML_HEARTBEAT_send % 100) == 0)  // 100*10ms = 1000ms
            {
                  cnt_ML_HEARTBEAT_send = 0;
                
                  mavlink_msg_heartbeat_pack(mavlink_system.sysid, mavlink_system.compid, &msg, system_type, autopilot_type, system_mode, custom_mode, system_state);
//     
//                // Copy the message to the send buffer
                  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
                  
                  UART_1_UartSendMavlink(buf, len);
                
//                UART_1_UartPutChar(0xFE);   // message header
//                UART_1_UartPutChar(0x09);   // message length
//                UART_1_UartPutChar(cnt_Mavlink_seq);   // Sequence number (0 to 255 counting)
//                UART_1_UartPutChar(mavlink_system.sysid);
//                UART_1_UartPutChar(mavlink_system.compid);
//                UART_1_UartPutChar(0);      // 0 = Heartbeat Message
//                UART_1_UartPutChar(0);      // 0 = Heartbeat Message // Byte 6
//                UART_1_UartPutChar(0);      // 0 = Heartbeat Message // Byte 7
//                UART_1_UartPutChar(0);      // 0 = Heartbeat Message // Byte 8
//                UART_1_UartPutChar(0);      // 0 = Heartbeat Message // Byte 9
//                UART_1_UartPutChar(0x01);      // 0 = Heartbeat Message // Byte 10
//                UART_1_UartPutChar(0x00);      // 0 = Heartbeat Message // Byte 11
//                UART_1_UartPutChar(0x00);      // 0 = Heartbeat Message // Byte 12
//                UART_1_UartPutChar(0x03);      // 0 = Heartbeat Message // Byte 13
//                UART_1_UartPutChar(0x03);      // 0 = Heartbeat Message // Byte 14
                
                
                //cnt_Mavlink_seq++;
            }
            cnt_ML_HEARTBEAT_send++;
            /*    
            UART_1_UartPutNum(ctrl_out[out_mot]);
                UART_1_UartPutString(";");
                UART_1_UartPutNum(ctrl_out[out_ail1]);
                UART_1_UartPutString(";");
                UART_1_UartPutNum(ctrl_in[2]);
                UART_1_UartPutString(";");
                UART_1_UartPutNum(ctrl_in[3]);
                UART_1_UartPutString(";");
                UART_1_UartPutNum(ctrl_in[4]);
                UART_1_UartPutString(";");
                UART_1_UartPutNum(ctrl_in[5]);
                UART_1_UartPutString(";");
                UART_1_UartPutNum(ctrl_in[6]);
                UART_1_UartPutString(";");
                UART_1_UartPutNum(ctrl_in[7]);
                UART_1_UartPutString("\r\n");
            */
        }

    }
}

/* [] END OF FILE */
