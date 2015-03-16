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
#include <IMU.h>

#define FALSE   0
#define TRUE    1

volatile uint8_t task_flag = FALSE;     // The Task Flag is set in TaskISR Interrupt Routine
volatile uint8_t blink_cnt = 0;

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
struct turn_rates_obj
{
	long p,q,r;
};  // used for getting the turnrates within one struct out of IMU.c

struct turn_rates_obj turn_rate;

int16_t turn_rate_p = 0;
int16_t turn_rate_q = 0;
int16_t turn_rate_r = 0;

void UART_1_UartPutNum(int32_t num)
{
    char k[31];
    sprintf(k,"%d",num);
    UART_1_UartPutString(k);   
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
    
    UART_1_UartPutString("UART OK\r\n");
    
    gyro_start();
    
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        
        if(task_flag == TRUE)
        {
            /*=======================================
                Main Task that is executed every 10ms
              =======================================*/
            task_flag = FALSE;
            
            blink_cnt++;
            if(blink_cnt == 10)
            {
                blink_cnt = 0;   
       
            }
            if(blink_cnt == 100)
            {
                //Pin_2_Write(0xFF);
                
            }
            if(blink_cnt == 110)
            {
                blink_cnt = 0;
                //Pin_2_Write(0x00);    
            }
            //NavLightCompare++;
            //NavLightPWM_WriteCompare(NavLightCompare);      
            
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
            turn_rate = gyro_read();
            UART_1_UartPutNum(turn_rate_p);
            UART_1_UartPutString(";\r\n");
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
