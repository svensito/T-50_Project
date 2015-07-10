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
#include <mavlink.h>
#include <mavlink_types.h>

#define FALSE   0
#define TRUE    1

#define PI			3.1415926535897932384626433832795

volatile uint8_t task_flag = FALSE;     // The Task Flag is set in TaskISR Interrupt Routine
volatile uint8_t blink_cnt = 0;
float sample_time = 0.01;               // 10 ms Sample time

/*=============================*/
/*Remote Input variables*/
/*=============================*/
uint8_t PPM_channel = 0;                    // input channel variable
uint16_t ctrl_in[8] = {0};                  // input control vector
uint16_t ctrl_out[13] = {1500,
                         1500,
                         1500,
                         1500,
                         1500,
                         1500,
                         1500,
                         1500,
                         1500,
                         1500,
                         1500,
                         1500,
                         1500};                // output control vector

enum e_in{   // Input Control Enum - 8 Channels
    in_mot = 0,
    in_ail,
    in_ele,
    in_rud,
    in_gear,
    in_can,
    in_mod,
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
/* State Machine for mode control*/
/*=============================*/
uint8_t Ctrl_Mode = 0;
enum ctrl_mode
{
    manual = 0,
    damped,
    tune,
    autonom
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
/*Strobe Light*/
uint8_t cnt_StrobeLight     = 0;


/*=============================*/
/*IMU variables*/
/*=============================*/
#define GYRO_TASK   FALSE
#define ACC_TASK    FALSE
#define MAG_TASK    FALSE
#define BARO_TASK   FALSE

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
float Theta, Theta_Mav, Theta_acc = 0;   // Theta => estimated angle after Kalman, Theta_acc => Theta from accelerometer
float Phi, Phi_Mav, Phi_acc = 0;       // Phi => estimated angle after Kalman, Phi_acc => Theta from accelerometer
float Psi, Psi_acc = 0;       // Psi , Psi_acc => Psi from accelerometer

/* Magnetic Heading*/
int32_t Mag_Heading = 0;
float Mag_x, Mag_y = 0;    

/* Barometer Reading*/
int32_t Bar_press = 0;
uint8_t cnt_baro  = 0;

/*=============================*/
/* Speed reading       		*/
/*=============================*/
#define SPEED_TASK  TRUE
uint16_t speed_offset = 172;
int16_t speed = 0;
uint8_t cal_cnt = 0;
uint8_t speed_cal_compl = 0;

/*=============================*/
/* Kalman Filter Data			*/
/*=============================*/
// weighing matrices ???
float Q_angle = 0.005;
float Q_gyro = 0.005;
float R_angle = 0.02;
// Estimation of Theta (Kalman)
float q_bias = 0;
//int8_t P_00_Theta, P_01_Theta, P_10_Theta, P_11_Theta = 0;
float P_Theta[2][2] = {0,0,0,0};
float Theta_temp, S_Theta, K_0_Theta, K_1_Theta = 0;
// Estimation of Phi (Kalman)
float p_bias = 0;
//int8_t P_00_Phi, P_01_Phi, P_10_Phi, P_11_Phi = 0;
float P_Phi[2][2] = {0,0,0,0};
float Phi_temp, S_Phi, K_0_Phi, K_1_Phi = 0;

/*============================*/
/* Control variables	*/
/*=============================*/
uint8_t K_d_p = 2;
uint8_t K_d_q = 2;
uint8_t K_d_r = 3;

/*============================*/
/* Tune variables	            */
/*=============================*/
uint8_t tune_cnt = 0;


/*============================*/
/* UART Rx Tx variables		*/
/*=============================*/
#define DATA_LOG        TRUE
uint8_t Rx_char = 0;
char Rx_String[10] = {0,0,0,0,0,0,0,0,0,0};
uint8_t Rx_index = 0;
uint8_t Rx_flag = 0;

/*=============================*/
/* MAVLINK			*/
/*=============================*/
#define MAVLINK_TASK    FALSE

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

// Read speed
int16_t ADC_read_speed(void)
{
    ADC_StartConvert();
    int16_t speed = ADC_GetResult16(0); // channel 0 is the first channel
    ADC_StopConvert();
    return(speed);
}

// Speed calibration
void ADC_calibrate_speed(void)
{
    speed_offset = 0;
    cal_cnt = 0;
    while(cal_cnt < 254)
        {
            speed = ADC_read_speed();
            speed_offset+=speed;
            cal_cnt++;
        }
    speed_offset /= cal_cnt;
    //cal_cnt = 0;
    UART_1_UartPutNum(speed_offset);
    UART_1_UartPutString("Cal Compl\r\n");    
}

/*##########################*/
/* main */
int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    CyDelay(500); // Wait before initialization happens. -> gives time for receiver to send PPM signal
    CyGlobalIntEnable; 
    UART_1_Start();     /* Enabling the UART */
    I2CM_Start();
    ADC_Start();
    // Setup the watchdog
    CySysWdtWriteMode(CY_SYS_WDT_COUNTER0, CY_SYS_WDT_MODE_RESET);  // Generate RESET
    CySysWdtWriteMatch(CY_SYS_WDT_COUNTER0, 16000);                 // Every 16000 cycles // 500ms
    //CySysWdtLock(); // Lock WDT settings
    
   
    // End Watchdog setup
    
    
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
    
    if(GYRO_TASK == TRUE) gyro_start();
    if(ACC_TASK == TRUE) acc_start();
    if(MAG_TASK == TRUE) mag_start();
    if(BARO_TASK == TRUE) baro_start();
    if(SPEED_TASK == TRUE) ;//ADC_calibrate_speed();
    UART_1_UartPutString("Started OK\r\n");
    //CyDelay(500);
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    
    // Enable Watchdog
    CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK);
    
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
                // Strobe Light Control
                if(cnt_StrobeLight == 200) Strobes_Write(0xFF); // Setting Output High
                if(cnt_StrobeLight == 205)  // (205 - 200) *10 ms = 5 * 10 ms = 50 ms Strobe
                {
                    cnt_StrobeLight = 0;
                    Strobes_Write(0x00);    // Setting output Low
                }
                cnt_StrobeLight++;
                // Landing Light Control
                if(ctrl_in[in_gear] < 1100)
                {
                    Ldg_Write(0xFF);
                }
                else Ldg_Write(0x00);
            }
            else
            {
                /* Lights disabled*/
                NavLightPWM_WriteCompare(0);    // Nav Lights set to 0
                Strobes_Write(0x00);    // Setting output Low
                Ldg_Write(0x00);
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
            if(BARO_TASK == TRUE)
            {
                cnt_baro++;
                if(cnt_baro == 10)
                {
                    cnt_baro = 0;
                    Bar_press = baro_read();
                }
            }
            if(SPEED_TASK == TRUE)
            {
                
                /*
                     - - - -         - - - -
                    |       |       |       |
                    |       |       |       |
                    |       |       |       |
                    |X      |       |X      |
                     - - - -         - - - -
                */
                
                if((ctrl_in[in_mot]<1200) &&        
                   (ctrl_in[in_rud]<1200) && 
                   (ctrl_in[in_ail]<1200) &&
                   (ctrl_in[in_ele]>1800) &&
                    speed_cal_compl == FALSE)
                {
                    speed_cal_compl = TRUE;
                    ADC_calibrate_speed();
                    UART_1_UartPutString("ADC Calibrated\r\n");
                }
                else if((ctrl_in[in_rud]>1200) && 
                   (ctrl_in[in_ail]>1200) &&
                   (ctrl_in[in_ele]<1800) &&
                    speed_cal_compl == TRUE)
                {
                    speed_cal_compl = FALSE;
                }
                speed = ADC_read_speed() - speed_offset;
            }
            
            /* Theta and Phi out of acceleration data*/
            Theta_acc = (atan2(acc_x_g,-acc_z_g))*180/PI;
		    Phi_acc = (atan2(-acc_y_g,-acc_z_g))*180/PI;
            //Psi_acc = (atan2(-acc_y_g,-acc_x_g))*180/PI;
			/*=========================================================*/
			/* Calculating the attitude by using Kalman Filtering START*/
			
//            Theta += sample_time * (turn_rate_q-q_bias);
//            
//			//P_00_Theta +=  - sample_time * ((P_10_Theta + P_01_Theta) - Q_angle);
//            P_Theta[0][0] +=  - sample_time * ((P_Theta[1][0] + P_Theta[0][1]) - Q_angle);
////			P_01_Theta +=  - sample_time * P_11_Theta;
//            P_Theta[0][1] +=  - sample_time * P_Theta[1][1];
//			//P_10_Theta = P_01_Theta;
//            P_Theta[1][0] = P_Theta[0][1];
//			//P_11_Theta +=  + Q_gyro * sample_time;
//            P_Theta[1][1] +=  + Q_gyro * sample_time;
//			
//			
//			Phi += sample_time * (turn_rate_p-p_bias);
//			P_Phi[0][0] +=  - sample_time * ((P_Phi[1][0] + P_Phi[0][1]) - Q_angle);
//			P_Phi[0][1] +=  - sample_time * P_Phi[1][1];
//			P_Phi[1][0] = P_Phi[0][1];
//			P_Phi[1][1] +=  + Q_gyro * sample_time;
//			
//		
//			/*
//			Psi += sample_time * (r_filt-r_bias);
//			P_00_Psi +=  - sample_time * (P_10_Psi + P_01_Psi) + Q_angle * sample_time;
//			P_01_Psi +=  - sample_time * P_11_Psi;
//			P_10_Psi +=  - sample_time * P_11_Psi;
//			P_11_Psi +=  + Q_gyro * sample_time;
//			*/
//			Theta_temp = Theta_acc - Theta;
//			S_Theta = P_Theta[0][0] + R_angle;
//			K_0_Theta = P_Theta[0][0] / S_Theta;
//			K_1_Theta = P_Theta[1][0] / S_Theta;
//			
//			Phi_temp = Phi_acc - Phi;
//			S_Phi = P_Phi[0][0] + R_angle;
//			K_0_Phi = P_Phi[0][0] / S_Phi;
//			K_1_Phi = P_Phi[1][0] / S_Phi;
//			/*
//			Psi_temp = mag - Psi;
//			S_Psi = P_00_Psi + R_angle;
//			K_0_Psi = P_00_Psi / S_Psi;
//			K_1_Psi = P_10_Psi / S_Psi;
//			*/
//			Theta +=  K_0_Theta * Theta_temp;
//			q_bias  +=  K_1_Theta * Theta_temp;
//			P_Theta[0][0] -= K_0_Theta * P_Theta[0][0];
//			P_Theta[0][1] -= K_0_Theta * P_Theta[0][1];
//			P_Theta[1][0] -= K_1_Theta * P_Theta[0][0];
//			P_Theta[1][1] -= K_1_Theta * P_Theta[0][1];
//			
//			Phi +=  K_0_Phi * Phi_temp;
//			p_bias  +=  K_1_Phi * Phi_temp;
//			P_Phi[0][0] -= K_0_Phi * P_Phi[0][0];
//			P_Phi[0][1] -= K_0_Phi * P_Phi[0][1];
//			P_Phi[1][0] -= K_1_Phi * P_Phi[0][0];
//			P_Phi[1][1] -= K_1_Phi * P_Phi[0][1];
		
			//angle = 0.98 *(angle+gyro*dt) + 0.02*acc
            // Complementary filter. Substitute for Kalman filter.
            // it is not clear why the 8 in the end is required, but it gives useable results
            Theta = (0.90* (Theta + turn_rate_q*sample_time) + 0.10*Theta_acc);
            Theta_Mav = Theta*PI/180*8;
            Phi = (0.90 * (Phi + turn_rate_p*sample_time) + 0.10*Phi_acc);
            Phi_Mav = Phi*PI/180*8;
            
             // Tilt compensated Magnetic filed X:
            //  MAG_X = c_magnetom_x*cos_pitch+c_magnetom_y*sin_roll*sin_pitch+c_magnetom_z*cos_roll*sin_pitch;
            //  // Tilt compensated Magnetic filed Y:
            //  MAG_Y = c_magnetom_y*cos_roll-c_magnetom_z*sin_roll;
            //  // Magnetic Heading
            //  MAG_Heading = atan2(-MAG_Y,MAG_X);
            
            // cos of radian angles
//            Mag_x = mag_x_g*cos(Theta) + mag_y_g*sin(Phi)*sin(Theta) + mag_z_g*cos(Phi)*sin(Theta);
//            Mag_y = mag_y_g*cos(Phi) - mag_z_g*sin(Phi);
//
            //Mag_x = mag_x_g*cos(Theta);//+ mag_y_g*sin(Phi)*sin(Theta)+ mag_z_g*cos(Phi)*sin(Theta);
            //Mag_y = mag_y_g*cos(Phi);// - mag_z_g*sin(Phi);
            //Mag_Heading = atan2(-(mag_y_g),(mag_x_g))*180/PI;
            //UART_1_UartPutNum(Mag_Heading);
            //UART_1_UartPutNum(Bar_press);   //Print Baro Press
            //UART_1_UartPutString(";\r\n");
            
			/* Calculating the attitude by using Kalman Filtering END*/
			/*=======================================================*/
            /* MAVLINK
            /*=======================================================*/
            
		    if(MAVLINK_TASK == TRUE)
            {
                if((cnt_ML_HEARTBEAT_send % 20) == 0)  // 20*10ms = 200ms
                {
                    mavlink_msg_attitude_pack(mavlink_system.sysid, mavlink_system.compid, &msg, 0, Phi_Mav, Theta_Mav, 0, 0,0,0);
                    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
                    UART_1_UartSendMavlink(buf, len);
                    
                    // GLOBAL_POSITION_INT
                    //mavlink_msg_global_position_int_pack(mavlink_system.sysid, mavlink_system.compid, &msg, 0,0,0,10,0,0,0,0,Mag_Heading);
                    //uint16_t len2 = mavlink_msg_to_send_buffer(buf, &msg);
                    //UART_1_UartSendMavlink(buf, len);
                    
                }               
                if((cnt_ML_HEARTBEAT_send % 100) == 0)  // 100*10ms = 1000ms
                {
                    cnt_ML_HEARTBEAT_send = 0;
                    mavlink_msg_heartbeat_pack(mavlink_system.sysid, mavlink_system.compid, &msg, system_type, autopilot_type, system_mode, custom_mode, system_state);

                    // Copy the message to the send buffer
                    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
                      
                      UART_1_UartSendMavlink(buf, len);
                }
                cnt_ML_HEARTBEAT_send++;
            }
            /*=======================================
                Airplane Control
              =======================================*/
        uint8_t debug = 0;
            
           
            if(debug == 0)
            {                     
                if (ctrl_in[in_mod]<1250) Ctrl_Mode = damped;       // up:      damped mode
                else if (ctrl_in[in_mod]>1750) Ctrl_Mode = tune;    // down:    tune mode
                else Ctrl_Mode = manual;                            // mid:     manual mode
                            
                uint16_t flap_offset = 0;
                // Flap Control
                if(ctrl_in[in_sp2]>1750)
                {
                    flap_offset = 300;
                }
                
                switch (Ctrl_Mode)
                {
                    case manual:
                        tune_cnt= 0;    // Reset in case tune cnt was used before...
                        ctrl_out[out_mot] = ctrl_in[in_mot];//ctrl_in[in_mot];            // motor:   low: 1000   high: 2000
                        //ctrl_out[out_mot] = 800;
                        ctrl_out[out_ail1] = ctrl_in[in_ail]+flap_offset;           // ail:     left: 1000  right: 2000
                        ctrl_out[out_ail2] = ctrl_in[in_ail]-flap_offset;
                        ctrl_out[out_ele1] = ctrl_in[in_ele];           // ele:     low: 2000   high: 1000
                        ctrl_out[out_ele2] = ctrl_in[in_ele];
                        ctrl_out[out_rud] = ctrl_in[in_rud];            // rud:     left: 1000  right: 2000
                        ctrl_out[out_ge1] = ctrl_in[in_gear];           // gear:    down: 1000  retracted: 2000
                        ctrl_out[out_ge2] = ctrl_in[in_gear];
                        ctrl_out[out_ge3] = ctrl_in[in_gear];             
                        ctrl_out[out_fl1] = ctrl_in[in_can];            // canopy:  open: 1000  closed: 2000
                        ctrl_out[out_fl2] = ctrl_in[in_can];
                        ctrl_out[out_sp1] = ctrl_in[in_mot];            // mode:    down: 2000 mid: 1500 up: 1000
                        ctrl_out[out_sp2] = ctrl_in[in_mot];
 
                        
                    break;
                    
                    case damped:
                        ctrl_out[out_mot] = ctrl_in[in_mot];            // motor:   low: 1000   high: 2000
                        //ctrl_out[out_mot] = 800;
                        ctrl_out[out_ail1] = ctrl_in[in_ail]-(K_d_p*turn_rate_p);           // ail:     left: 1000  right: 2000
                        ctrl_out[out_ail2] = ctrl_in[in_ail]-(K_d_p*turn_rate_p);
                        ctrl_out[out_ele1] = ctrl_in[in_ele]-(K_d_q*turn_rate_q);           // ele:     low: 2000   high: 1000
                        ctrl_out[out_ele2] = ctrl_in[in_ele]-(K_d_q*turn_rate_q);
                        ctrl_out[out_rud] = ctrl_in[in_rud]-(K_d_r*turn_rate_r);            // rud:     left: 1000  right: 2000
                        ctrl_out[out_ge1] = ctrl_in[in_mot];           // gear:    down: 1000  retracted: 2000
                        ctrl_out[out_ge2] = ctrl_in[in_gear];
                        ctrl_out[out_ge3] = ctrl_in[in_gear];             
                        ctrl_out[out_fl1] = ctrl_in[in_can];            // canopy:  front: 1000  back: 2000
                        ctrl_out[out_fl2] = ctrl_in[in_can];
                        ctrl_out[out_sp1] = ctrl_in[in_mot];            // mode:    down: 2000 mid: 1500 up: 1000
                        ctrl_out[out_sp2] = ctrl_in[in_mot];
                    break;
                        
                    case tune:
                        if(tune_cnt == 0)
                        {
                            ctrl_out[out_mot] = ctrl_in[in_mot];            // motor:   low: 1000   high: 2000
                            ctrl_out[out_ail1] = ctrl_in[in_ail];           // ail:     left: 1000  right: 2000
                            ctrl_out[out_ail2] = ctrl_in[in_ail];
                            ctrl_out[out_ele1] = ctrl_in[in_ele];           // ele:     low: 2000   high: 1000
                            ctrl_out[out_ele2] = ctrl_in[in_ele];
                            ctrl_out[out_rud] = ctrl_in[in_rud];
                        }
                        if(ctrl_in[in_can] < 1500 && (tune_cnt == 100))
                        {
                            // step Aileron
                            ctrl_out[out_ail1]+= 150;
                            ctrl_out[out_ail2]-= 150;
                        }
                        else if (ctrl_in[in_can] > 1500 && (tune_cnt == 100))
                        {
                            // step Elevator
                            ctrl_out[out_ele1]+= 150;   // positive step -> Up
                        }
                        
                        if(tune_cnt < 250) tune_cnt++;
                        
                    break;
                    
                }
            }
            else    // for debug use only (no receiver connected)
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
            if(DATA_LOG == TRUE)
            {
                UART_1_UartPutNum(ctrl_out[out_mot]);
                UART_1_UartPutString(";");
                UART_1_UartPutNum(ctrl_out[out_ail1]);
                UART_1_UartPutString(";");
                UART_1_UartPutNum(ctrl_out[out_ele1]);
                UART_1_UartPutString(";");
                UART_1_UartPutNum(ctrl_out[out_rud]);
                UART_1_UartPutString(";");
                UART_1_UartPutNum(ctrl_out[out_ge2]);
                UART_1_UartPutString(";");
                UART_1_UartPutNum(ctrl_out[out_fl1]);
                UART_1_UartPutString(";");
                //UART_1_UartPutNum(ctrl_in[7]);
                //UART_1_UartPutString("\r\n");
                UART_1_UartPutNum(Phi);
                UART_1_UartPutString(";");
                UART_1_UartPutNum(Theta);
                UART_1_UartPutString(";");
                UART_1_UartPutNum(speed);
                UART_1_UartPutString(";");
                UART_1_UartPutNum(Ctrl_Mode);
                UART_1_UartPutString(";\r\n");
            }
                //UART_1_UartPutNum(Phi);
                //UART_1_UartPutString(";");
                //UART_1_UartPutNum(Theta);
                //UART_1_UartPutString(";");
                //UART_1_UartPutNum(speed);
                //UART_1_UartPutString(";\r\n");
            if(Rx_flag == 1)
            {
                Rx_flag = 0;
                UART_1_UartPutString(Rx_String);
                UART_1_UartPutString("\r\n");
                // In case "Boot" is received -> Bootloader gets enabled
                if(strcmp(Rx_String,"Boot")==0)
                {
                    CySysWdtUnlock();   // Stop The Watchdog...?
                    CySysWdtDisable(CY_SYS_WDT_COUNTER0_MASK);
                    UART_1_UartPutString("BootEnabl\r\n");
                    CyDelay(100);
                    Bootloadable_1_Load(); 
                }
            }
            // Feed the Watchdog
            //CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0);
            //CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_MASK);
            //CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_INT);
            //CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_);
            CySysWdtResetCounters(CY_SYS_WDT_COUNTER0_RESET);
        }
        // Reading the serial data and putting it to a string
        Rx_char = UART_1_UartGetChar(); // Poll for Characters
        if(Rx_char > 0u)  
            {
                if(Rx_char == '\r')
                {
                    Rx_String[Rx_index] = '\0';
                    Rx_flag = 1;
                    Rx_index = 0;
                }
                else
                {
                    Rx_String[Rx_index] = Rx_char;
                    Rx_index++;
                }
            }
    }
}

/* [] END OF FILE */
