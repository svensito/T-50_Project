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

#include <Stabilizer.h>

extern int16_t turn_rate_p;		// from main.c file
extern int16_t turn_rate_q;		// from main.c file
extern int16_t turn_rate_r;		// from main.c file

extern uint16_t ctrl_out[13];
extern uint16_t ctrl_in[8];
uint16_t ctrl_in_ent[8]={0};    /* Used as ctrl_in when Prog Mode Entered */

extern int8_t K_d_p;
extern int8_t K_d_q;
extern int8_t K_d_r;

extern uint8_t imu_conn;        /* From main.c file */
uint8_t receiver_connected;     /* From main.c file */

uint8_t K_d_p_conv = 0;


extern void UART_1_UartPutNum();

uint16_t ProgMode_Timer = 0;
uint16_t ExitProgMode_Timer = 0;
extern uint8_t Ctrl_Mode;       /* Ctrl Mode from main.c */
uint8_t ProgModeReq = FALSE;            // Programming Mode Request
uint8_t Mode_Changed = FALSE;
uint8_t EleAilNeutral = FALSE;
uint8_t RudNeutral = FALSE;

enum ctrl_mode
{
    manual = 0,
    damped,
    tune,
    autonom,
    prog
};

enum e_in{   // Input Control Enum - 8 Channels
    in_mot = 0, // Channel 1
    in_ail,     // Channel 2
    in_ele,     // Channel 3
    in_rud,     // Channel 4
    in_gear,    // Channel 5
    in_can,     // Channel 6
    in_mod,     // Channel 7
    in_sp2      // Channel 8
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

//extern uint8_t Stab_Val_Stor[3];    /* Stabi Values */
//extern uint8_t Stab_Val_Use[3];    /* Stabi Values */

/**********************************************************************
***
*** TO DO:  - save Kdp, Kdq, Kdr in EEprom -> Additional Bootloader required 
            - == OK == limit Kdp, Kdq, Kdr to +- 10 == OK ==
            - == OK == make stick movements to "normal" TX config == OK ==
            - make Stab robust to missing Rx and missing IMU
            - Allow PWM input of diff channels
**********************************************************************/
void Stabi_Task(void)
{
    /* TEST ONLY */
    //CySysFlashWriteRow()
    //CysysFl
    
    /* State Machine for the Modes */
    switch (Ctrl_Mode)
    {
        case damped:
            
            if(Mode_Changed == TRUE)
            {
                Mode_Changed = FALSE;
                UART_1_UartPutString("Stab Mode Entered\r\n");
            }
        
            //UART_1_UartPutString("Stab Norm ");
            
            //UART_1_UartPutNum(ctrl_in[in_ail]);
            //UART_1_UartPutString(" ");
            //UART_1_UartPutNum(ctrl_in[in_ele]);
            //UART_1_UartPutString(" ");
            //UART_1_UartPutNum(ctrl_in[in_rud]);
            //UART_1_UartPutString("\r\n");
            
            /* Normal Stabilization Mode */
            if((imu_conn == 1) && (receiver_connected == 1)) /* if IMU is detected */
            {
                MPU6050_data_read();    /* All MPU Data is read at once */
                ctrl_out[out_ail1] = ctrl_in[in_ail]+(K_d_p*(turn_rate_p));           // ail:     left: 1000  right: 2000
                ctrl_out[out_ail2] = ctrl_in[in_ail]+(K_d_p*(turn_rate_p));
                ctrl_out[out_ele1] = ctrl_in[in_ele]+(K_d_q*(turn_rate_q));           // ele:     low: 2000   high: 1000
                ctrl_out[out_ele2] = ctrl_in[in_ele]+(K_d_q*(turn_rate_q));
                ctrl_out[out_rud] = ctrl_in[in_rud]+((K_d_r*turn_rate_r));            // rud:     left: 1000  right: 2000
            }
            else if(receiver_connected == 1)/* No IMU detected*/
            {
                ctrl_out[out_ail1] = ctrl_in[in_ail];           // ail:     left: 1000  right: 2000
                ctrl_out[out_ail2] = ctrl_in[in_ail];
                ctrl_out[out_ele1] = ctrl_in[in_ele];           // ele:     low: 2000   high: 1000
                ctrl_out[out_ele2] = ctrl_in[in_ele];
                ctrl_out[out_rud] = ctrl_in[in_rud];            // rud:     left: 1000  right: 2000
            }
            else /* In case no receiver connected -> keep them safe */
            {
                /* Do not modify the outputs */
            }
        break;
        
        case prog:
            
            ProgModeReq = FALSE;
            if(Mode_Changed == TRUE)
            {
                UART_1_UartPutString("Prog Mode Entered\r\n");
                /* This is called only when Prog Mode entered */
                Mode_Changed = FALSE;   
                ctrl_in_ent[in_ail] = ctrl_in[in_ail];
                ctrl_in_ent[in_ele] = ctrl_in[in_ele];
                ctrl_in_ent[in_rud] = ctrl_in[in_rud];
            }
            /* Indicate that in Prog Mode */
            OnBoardLED_Write(0xFF);       
            
            /* EXIT Programming Mode Timer -> Reset when any stick is moved */
            ExitProgMode_Timer++;
            if(ExitProgMode_Timer >= 1000) /* 10 second timeout */
            {
                /* Store new Stabi Data */
                EEPROM_write(EEPROM_K_D_P_ADD, (uint8_t)K_d_p);
                CyDelay(100);
                EEPROM_write(EEPROM_K_D_Q_ADD, (uint8_t)K_d_q);
                CyDelay(100);
                EEPROM_write(EEPROM_K_D_R_ADD, (uint8_t)K_d_r);
                UART_1_UartPutString("EEPROM Stored\r\n");
                //Stab_Val_Use[0]=K_d_p;
                //Stab_Val_Use[1]=K_d_q;
                //Stab_Val_Use[2]=K_d_r;
                //Em_EEPROM_1_Write(Stab_Val_Use, Stab_Val_Stor,3);
                /* Leave Programming Mode */
                Ctrl_Mode = damped;
                Mode_Changed = TRUE;  
            }
            /* EXIT END*/
            
            /* Show current Damping Values by movement*/
            MPU6050_data_read();    /* All MPU Data is read at once */
        
            ctrl_out[out_ail1]  = ctrl_in_ent[in_ail]+(K_d_p*(turn_rate_p));           // ail:     left: 1000  right: 2000
            ctrl_out[out_ail2]  = ctrl_in_ent[in_ail]+(K_d_p*(turn_rate_p));
            ctrl_out[out_ele1]  = ctrl_in_ent[in_ele]+(K_d_q*(turn_rate_q));           // ele:     low: 2000   high: 1000
            ctrl_out[out_ele2]  = ctrl_in_ent[in_ele]+(K_d_q*(turn_rate_q));
            ctrl_out[out_rud]   = ctrl_in_ent[in_rud]+((K_d_r*turn_rate_r));            // rud:     left: 1000  right: 2000
            
            /****************************************/
            /* MODIFY K_d_p value with Aileron Stick */
            static uint8_t ail_cmd = FALSE;
            if((ctrl_in[in_ail] > 1700) && (ail_cmd== FALSE))
            {
                ExitProgMode_Timer = 0; /* Reset exit timer on stick movement */
                ail_cmd = TRUE;
                
                /* Limit Values for Aileron Damping + - 10 */
                if(K_d_p < 10) K_d_p++;
                UART_1_UartPutString("K_d_p: ");
                UART_1_UartPutNum(K_d_p);
                UART_1_UartPutString("\r\n");
            }
            else if((ctrl_in[in_ail] < 1300)&& (ail_cmd == FALSE))
            {
                ExitProgMode_Timer = 0; /* Reset exit timer on stick movement */
                ail_cmd = TRUE;
                /* Limit Values for Aileron Damping + - 10 */
                if(K_d_p > -10) K_d_p--;
                UART_1_UartPutString("K_d_p: ");
                UART_1_UartPutNum(K_d_p);
                UART_1_UartPutString("\r\n");
            }
            else if(EleAilNeutral)
            {
                /* Reset the command */
                ail_cmd = FALSE;
            }

            /****************************************/
            /* MODIFY K_d_q value with Elevator Stick */
            static uint8_t ele_cmd = FALSE;

            if((ctrl_in[in_ele] > 1800) && (ele_cmd== FALSE))
            {
                ExitProgMode_Timer = 0; /* Reset exit timer on stick movement */
                ele_cmd = TRUE;
                /* Limit Values for Elevator Damping + - 10 */
                if(K_d_q < 10) K_d_q++;
                UART_1_UartPutString("K_d_q: ");
                UART_1_UartPutNum(K_d_q);
                UART_1_UartPutString("\r\n");
            }
            else if((ctrl_in[in_ele] < 1200)&& (ele_cmd == FALSE))
            {
                ExitProgMode_Timer = 0; /* Reset exit timer on stick movement */
                ele_cmd = TRUE;
                /* Limit Values for Elevator Damping + - 10 */
                if(K_d_q > -10) K_d_q--;
                UART_1_UartPutString("K_d_q: ");
                UART_1_UartPutNum(K_d_q);
                UART_1_UartPutString("\r\n");
            }
            else if(EleAilNeutral)
            {
                /* Reset the command */
                ele_cmd = FALSE;
            }
            
             /****************************************/
            /* MODIFY K_d_r value with Rudder Stick */
            static uint8_t rud_cmd = FALSE;

            if((ctrl_in[in_rud] > 1800) && (rud_cmd== FALSE))
            {
                ExitProgMode_Timer = 0; /* Reset exit timer on stick movement */
                rud_cmd = TRUE;
                /* Limit Values for Rudder Damping + - 10 */
                if(K_d_r < 10) K_d_r++;                
                UART_1_UartPutString("K_d_r: ");
                UART_1_UartPutNum(K_d_r);
                UART_1_UartPutString("\r\n");
            }
            else if((ctrl_in[in_rud] < 1200)&& (rud_cmd == FALSE))
            {
                ExitProgMode_Timer = 0; /* Reset exit timer on stick movement */
                rud_cmd = TRUE;
                /* Limit Values for Rudder Damping + - 10 */
                if(K_d_r > -10) K_d_r--;                
                UART_1_UartPutString("K_d_r: ");
                UART_1_UartPutNum(K_d_r);
                UART_1_UartPutString("\r\n");
            }
            else if(RudNeutral)
            {
                /* Reset the command */
                rud_cmd = FALSE;
            }
        break;
    }
    
    
    if((ctrl_in[in_ail] < 1350) && (ctrl_in[in_ele] < 1300) && (Ctrl_Mode == damped) && (ProgModeReq == FALSE))
    {
        if(ProgMode_Timer >= 1000) /* base 10msec => 10000msec = 10 sec */
        {
            ProgModeReq = TRUE;     /* Request to enter Prog Mode */
            /* Prog Mode Timer Reset */    
            ExitProgMode_Timer = 0;
            UART_1_UartPutString("Release Stick to Switch\r\n");
            OnBoardLED_Write(0xFF);
        }
        ProgMode_Timer++;
    }
    else 
    {
        ProgMode_Timer = 0;
    }
    
    if((ctrl_in[in_ail] > 1400) && (ctrl_in[in_ail] < 1600)&&   // Aileron Neutral
       (ctrl_in[in_ele] > 1400) && (ctrl_in[in_ele] < 1600))    // Elevator Neutral
    {
        EleAilNeutral = TRUE;
    }
    else EleAilNeutral = FALSE;
    
    if((ctrl_in[in_rud] > 1400) && (ctrl_in[in_rud] < 1600))   // Rudder Neutral
    {
         RudNeutral = TRUE;
    }
    else RudNeutral = FALSE;
    
    if((ProgModeReq == TRUE) && (EleAilNeutral == TRUE) && (Ctrl_Mode == damped))// && (ctrl_in[in_ail] > 1800) && (ctrl_in[in_ele] > 1300))
    {
        /* Programming Mode ENTERED */
        Ctrl_Mode = prog;   
        Mode_Changed = TRUE;
    }
    
}




/* [] END OF FILE */
