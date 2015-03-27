/*******************************************************************************
* File Name: ServoTimer.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the ServoTimer
*  component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ServoTimer.h"

uint8 ServoTimer_initVar = 0u;


/*******************************************************************************
* Function Name: ServoTimer_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default ServoTimer configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (ServoTimer__QUAD == ServoTimer_CONFIG)
        ServoTimer_CONTROL_REG = ServoTimer_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        ServoTimer_TRIG_CONTROL1_REG  = ServoTimer_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        ServoTimer_SetInterruptMode(ServoTimer_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        ServoTimer_SetCounterMode(ServoTimer_COUNT_DOWN);
        ServoTimer_WritePeriod(ServoTimer_QUAD_PERIOD_INIT_VALUE);
        ServoTimer_WriteCounter(ServoTimer_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (ServoTimer__QUAD == ServoTimer_CONFIG) */

    #if (ServoTimer__TIMER == ServoTimer_CONFIG)
        ServoTimer_CONTROL_REG = ServoTimer_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        ServoTimer_TRIG_CONTROL1_REG  = ServoTimer_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        ServoTimer_SetInterruptMode(ServoTimer_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        ServoTimer_WritePeriod(ServoTimer_TC_PERIOD_VALUE );

        #if (ServoTimer__COMPARE == ServoTimer_TC_COMP_CAP_MODE)
            ServoTimer_WriteCompare(ServoTimer_TC_COMPARE_VALUE);

            #if (1u == ServoTimer_TC_COMPARE_SWAP)
                ServoTimer_SetCompareSwap(1u);
                ServoTimer_WriteCompareBuf(ServoTimer_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == ServoTimer_TC_COMPARE_SWAP) */
        #endif  /* (ServoTimer__COMPARE == ServoTimer_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (ServoTimer_CY_TCPWM_V2 && ServoTimer_TIMER_UPDOWN_CNT_USED && !ServoTimer_CY_TCPWM_4000)
            ServoTimer_WriteCounter(1u);
        #elif(ServoTimer__COUNT_DOWN == ServoTimer_TC_COUNTER_MODE)
            ServoTimer_WriteCounter(ServoTimer_TC_PERIOD_VALUE);
        #else
            ServoTimer_WriteCounter(0u);
        #endif /* (ServoTimer_CY_TCPWM_V2 && ServoTimer_TIMER_UPDOWN_CNT_USED && !ServoTimer_CY_TCPWM_4000) */
    #endif  /* (ServoTimer__TIMER == ServoTimer_CONFIG) */

    #if (ServoTimer__PWM_SEL == ServoTimer_CONFIG)
        ServoTimer_CONTROL_REG = ServoTimer_CTRL_PWM_BASE_CONFIG;

        #if (ServoTimer__PWM_PR == ServoTimer_PWM_MODE)
            ServoTimer_CONTROL_REG |= ServoTimer_CTRL_PWM_RUN_MODE;
            ServoTimer_WriteCounter(ServoTimer_PWM_PR_INIT_VALUE);
        #else
            ServoTimer_CONTROL_REG |= ServoTimer_CTRL_PWM_ALIGN | ServoTimer_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (ServoTimer_CY_TCPWM_V2 && ServoTimer_PWM_UPDOWN_CNT_USED && !ServoTimer_CY_TCPWM_4000)
                ServoTimer_WriteCounter(1u);
            #elif (ServoTimer__RIGHT == ServoTimer_PWM_ALIGN)
                ServoTimer_WriteCounter(ServoTimer_PWM_PERIOD_VALUE);
            #else 
                ServoTimer_WriteCounter(0u);
            #endif  /* (ServoTimer_CY_TCPWM_V2 && ServoTimer_PWM_UPDOWN_CNT_USED && !ServoTimer_CY_TCPWM_4000) */
        #endif  /* (ServoTimer__PWM_PR == ServoTimer_PWM_MODE) */

        #if (ServoTimer__PWM_DT == ServoTimer_PWM_MODE)
            ServoTimer_CONTROL_REG |= ServoTimer_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (ServoTimer__PWM_DT == ServoTimer_PWM_MODE) */

        #if (ServoTimer__PWM == ServoTimer_PWM_MODE)
            ServoTimer_CONTROL_REG |= ServoTimer_CTRL_PWM_PRESCALER;
        #endif  /* (ServoTimer__PWM == ServoTimer_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        ServoTimer_TRIG_CONTROL1_REG  = ServoTimer_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        ServoTimer_SetInterruptMode(ServoTimer_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (ServoTimer__PWM_PR == ServoTimer_PWM_MODE)
            ServoTimer_TRIG_CONTROL2_REG =
                    (ServoTimer_CC_MATCH_NO_CHANGE    |
                    ServoTimer_OVERLOW_NO_CHANGE      |
                    ServoTimer_UNDERFLOW_NO_CHANGE);
        #else
            #if (ServoTimer__LEFT == ServoTimer_PWM_ALIGN)
                ServoTimer_TRIG_CONTROL2_REG = ServoTimer_PWM_MODE_LEFT;
            #endif  /* ( ServoTimer_PWM_LEFT == ServoTimer_PWM_ALIGN) */

            #if (ServoTimer__RIGHT == ServoTimer_PWM_ALIGN)
                ServoTimer_TRIG_CONTROL2_REG = ServoTimer_PWM_MODE_RIGHT;
            #endif  /* ( ServoTimer_PWM_RIGHT == ServoTimer_PWM_ALIGN) */

            #if (ServoTimer__CENTER == ServoTimer_PWM_ALIGN)
                ServoTimer_TRIG_CONTROL2_REG = ServoTimer_PWM_MODE_CENTER;
            #endif  /* ( ServoTimer_PWM_CENTER == ServoTimer_PWM_ALIGN) */

            #if (ServoTimer__ASYMMETRIC == ServoTimer_PWM_ALIGN)
                ServoTimer_TRIG_CONTROL2_REG = ServoTimer_PWM_MODE_ASYM;
            #endif  /* (ServoTimer__ASYMMETRIC == ServoTimer_PWM_ALIGN) */
        #endif  /* (ServoTimer__PWM_PR == ServoTimer_PWM_MODE) */

        /* Set other values from customizer */
        ServoTimer_WritePeriod(ServoTimer_PWM_PERIOD_VALUE );
        ServoTimer_WriteCompare(ServoTimer_PWM_COMPARE_VALUE);

        #if (1u == ServoTimer_PWM_COMPARE_SWAP)
            ServoTimer_SetCompareSwap(1u);
            ServoTimer_WriteCompareBuf(ServoTimer_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == ServoTimer_PWM_COMPARE_SWAP) */

        #if (1u == ServoTimer_PWM_PERIOD_SWAP)
            ServoTimer_SetPeriodSwap(1u);
            ServoTimer_WritePeriodBuf(ServoTimer_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == ServoTimer_PWM_PERIOD_SWAP) */
    #endif  /* (ServoTimer__PWM_SEL == ServoTimer_CONFIG) */
    
}


/*******************************************************************************
* Function Name: ServoTimer_Enable
********************************************************************************
*
* Summary:
*  Enables the ServoTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    ServoTimer_BLOCK_CONTROL_REG |= ServoTimer_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (ServoTimer__PWM_SEL == ServoTimer_CONFIG)
        #if (0u == ServoTimer_PWM_START_SIGNAL_PRESENT)
            ServoTimer_TriggerCommand(ServoTimer_MASK, ServoTimer_CMD_START);
        #endif /* (0u == ServoTimer_PWM_START_SIGNAL_PRESENT) */
    #endif /* (ServoTimer__PWM_SEL == ServoTimer_CONFIG) */

    #if (ServoTimer__TIMER == ServoTimer_CONFIG)
        #if (0u == ServoTimer_TC_START_SIGNAL_PRESENT)
            ServoTimer_TriggerCommand(ServoTimer_MASK, ServoTimer_CMD_START);
        #endif /* (0u == ServoTimer_TC_START_SIGNAL_PRESENT) */
    #endif /* (ServoTimer__TIMER == ServoTimer_CONFIG) */
}


/*******************************************************************************
* Function Name: ServoTimer_Start
********************************************************************************
*
* Summary:
*  Initializes the ServoTimer with default customizer
*  values when called the first time and enables the ServoTimer.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ServoTimer_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time ServoTimer_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the ServoTimer_Start() routine.
*
*******************************************************************************/
void ServoTimer_Start(void)
{
    if (0u == ServoTimer_initVar)
    {
        ServoTimer_Init();
        ServoTimer_initVar = 1u;
    }

    ServoTimer_Enable();
}


/*******************************************************************************
* Function Name: ServoTimer_Stop
********************************************************************************
*
* Summary:
*  Disables the ServoTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_BLOCK_CONTROL_REG &= (uint32)~ServoTimer_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the ServoTimer. This function is used when
*  configured as a generic ServoTimer and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the ServoTimer to operate in
*   Values:
*   - ServoTimer_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - ServoTimer_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - ServoTimer_MODE_QUAD - Quadrature decoder
*         - ServoTimer_MODE_PWM - PWM
*         - ServoTimer_MODE_PWM_DT - PWM with dead time
*         - ServoTimer_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_CONTROL_REG &= (uint32)~ServoTimer_MODE_MASK;
    ServoTimer_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - ServoTimer_MODE_X1 - Counts on phi 1 rising
*         - ServoTimer_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - ServoTimer_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_CONTROL_REG &= (uint32)~ServoTimer_QUAD_MODE_MASK;
    ServoTimer_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - ServoTimer_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - ServoTimer_PRESCALE_DIVBY2    - Divide by 2
*         - ServoTimer_PRESCALE_DIVBY4    - Divide by 4
*         - ServoTimer_PRESCALE_DIVBY8    - Divide by 8
*         - ServoTimer_PRESCALE_DIVBY16   - Divide by 16
*         - ServoTimer_PRESCALE_DIVBY32   - Divide by 32
*         - ServoTimer_PRESCALE_DIVBY64   - Divide by 64
*         - ServoTimer_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_CONTROL_REG &= (uint32)~ServoTimer_PRESCALER_MASK;
    ServoTimer_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the ServoTimer runs
*  continuously or stops when terminal count is reached.  By default the
*  ServoTimer operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_CONTROL_REG &= (uint32)~ServoTimer_ONESHOT_MASK;
    ServoTimer_CONTROL_REG |= ((uint32)((oneShotEnable & ServoTimer_1BIT_MASK) <<
                                                               ServoTimer_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetPWMMode(uint32 modeMask)
{
    ServoTimer_TRIG_CONTROL2_REG = (modeMask & ServoTimer_6BIT_MASK);
}



/*******************************************************************************
* Function Name: ServoTimer_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_CONTROL_REG &= (uint32)~ServoTimer_PWM_SYNC_KILL_MASK;
    ServoTimer_CONTROL_REG |= ((uint32)((syncKillEnable & ServoTimer_1BIT_MASK)  <<
                                               ServoTimer_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_CONTROL_REG &= (uint32)~ServoTimer_PWM_STOP_KILL_MASK;
    ServoTimer_CONTROL_REG |= ((uint32)((stopOnKillEnable & ServoTimer_1BIT_MASK)  <<
                                                         ServoTimer_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_CONTROL_REG &= (uint32)~ServoTimer_PRESCALER_MASK;
    ServoTimer_CONTROL_REG |= ((uint32)((deadTime & ServoTimer_8BIT_MASK) <<
                                                          ServoTimer_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - ServoTimer_INVERT_LINE   - Inverts the line output
*         - ServoTimer_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_CONTROL_REG &= (uint32)~ServoTimer_INV_OUT_MASK;
    ServoTimer_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: ServoTimer_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_WriteCounter(uint32 count)
{
    ServoTimer_COUNTER_REG = (count & ServoTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ServoTimer_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 ServoTimer_ReadCounter(void)
{
    return (ServoTimer_COUNTER_REG & ServoTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ServoTimer_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - ServoTimer_COUNT_UP       - Counts up
*     - ServoTimer_COUNT_DOWN     - Counts down
*     - ServoTimer_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - ServoTimer_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_CONTROL_REG &= (uint32)~ServoTimer_UPDOWN_MASK;
    ServoTimer_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_WritePeriod(uint32 period)
{
    ServoTimer_PERIOD_REG = (period & ServoTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ServoTimer_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 ServoTimer_ReadPeriod(void)
{
    return (ServoTimer_PERIOD_REG & ServoTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ServoTimer_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_CONTROL_REG &= (uint32)~ServoTimer_RELOAD_CC_MASK;
    ServoTimer_CONTROL_REG |= (swapEnable & ServoTimer_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_WritePeriodBuf(uint32 periodBuf)
{
    ServoTimer_PERIOD_BUF_REG = (periodBuf & ServoTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ServoTimer_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 ServoTimer_ReadPeriodBuf(void)
{
    return (ServoTimer_PERIOD_BUF_REG & ServoTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ServoTimer_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_CONTROL_REG &= (uint32)~ServoTimer_RELOAD_PERIOD_MASK;
    ServoTimer_CONTROL_REG |= ((uint32)((swapEnable & ServoTimer_1BIT_MASK) <<
                                                            ServoTimer_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_WriteCompare(uint32 compare)
{
    #if (ServoTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (ServoTimer_CY_TCPWM_4000) */

    #if (ServoTimer_CY_TCPWM_4000)
        currentMode = ((ServoTimer_CONTROL_REG & ServoTimer_UPDOWN_MASK) >> ServoTimer_UPDOWN_SHIFT);

        if (((uint32)ServoTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)ServoTimer__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (ServoTimer_CY_TCPWM_4000) */
    
    ServoTimer_COMP_CAP_REG = (compare & ServoTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ServoTimer_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
*******************************************************************************/
uint32 ServoTimer_ReadCompare(void)
{
    #if (ServoTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (ServoTimer_CY_TCPWM_4000) */

    #if (ServoTimer_CY_TCPWM_4000)
        currentMode = ((ServoTimer_CONTROL_REG & ServoTimer_UPDOWN_MASK) >> ServoTimer_UPDOWN_SHIFT);
        
        regVal = ServoTimer_COMP_CAP_REG;
        
        if (((uint32)ServoTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)ServoTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & ServoTimer_16BIT_MASK);
    #else
        return (ServoTimer_COMP_CAP_REG & ServoTimer_16BIT_MASK);
    #endif /* (ServoTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: ServoTimer_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_WriteCompareBuf(uint32 compareBuf)
{
    #if (ServoTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (ServoTimer_CY_TCPWM_4000) */

    #if (ServoTimer_CY_TCPWM_4000)
        currentMode = ((ServoTimer_CONTROL_REG & ServoTimer_UPDOWN_MASK) >> ServoTimer_UPDOWN_SHIFT);

        if (((uint32)ServoTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)ServoTimer__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (ServoTimer_CY_TCPWM_4000) */
    
    ServoTimer_COMP_CAP_BUF_REG = (compareBuf & ServoTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ServoTimer_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
*******************************************************************************/
uint32 ServoTimer_ReadCompareBuf(void)
{
    #if (ServoTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (ServoTimer_CY_TCPWM_4000) */

    #if (ServoTimer_CY_TCPWM_4000)
        currentMode = ((ServoTimer_CONTROL_REG & ServoTimer_UPDOWN_MASK) >> ServoTimer_UPDOWN_SHIFT);

        regVal = ServoTimer_COMP_CAP_BUF_REG;
        
        if (((uint32)ServoTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)ServoTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & ServoTimer_16BIT_MASK);
    #else
        return (ServoTimer_COMP_CAP_BUF_REG & ServoTimer_16BIT_MASK);
    #endif /* (ServoTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: ServoTimer_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 ServoTimer_ReadCapture(void)
{
    return (ServoTimer_COMP_CAP_REG & ServoTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ServoTimer_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 ServoTimer_ReadCaptureBuf(void)
{
    return (ServoTimer_COMP_CAP_BUF_REG & ServoTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ServoTimer_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - ServoTimer_TRIG_LEVEL     - Level
*     - ServoTimer_TRIG_RISING    - Rising edge
*     - ServoTimer_TRIG_FALLING   - Falling edge
*     - ServoTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_TRIG_CONTROL1_REG &= (uint32)~ServoTimer_CAPTURE_MASK;
    ServoTimer_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - ServoTimer_TRIG_LEVEL     - Level
*     - ServoTimer_TRIG_RISING    - Rising edge
*     - ServoTimer_TRIG_FALLING   - Falling edge
*     - ServoTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_TRIG_CONTROL1_REG &= (uint32)~ServoTimer_RELOAD_MASK;
    ServoTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << ServoTimer_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - ServoTimer_TRIG_LEVEL     - Level
*     - ServoTimer_TRIG_RISING    - Rising edge
*     - ServoTimer_TRIG_FALLING   - Falling edge
*     - ServoTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_TRIG_CONTROL1_REG &= (uint32)~ServoTimer_START_MASK;
    ServoTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << ServoTimer_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - ServoTimer_TRIG_LEVEL     - Level
*     - ServoTimer_TRIG_RISING    - Rising edge
*     - ServoTimer_TRIG_FALLING   - Falling edge
*     - ServoTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_TRIG_CONTROL1_REG &= (uint32)~ServoTimer_STOP_MASK;
    ServoTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << ServoTimer_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - ServoTimer_TRIG_LEVEL     - Level
*     - ServoTimer_TRIG_RISING    - Rising edge
*     - ServoTimer_TRIG_FALLING   - Falling edge
*     - ServoTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_TRIG_CONTROL1_REG &= (uint32)~ServoTimer_COUNT_MASK;
    ServoTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << ServoTimer_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - ServoTimer_CMD_CAPTURE    - Trigger Capture command
*     - ServoTimer_CMD_RELOAD     - Trigger Reload command
*     - ServoTimer_CMD_STOP       - Trigger Stop command
*     - ServoTimer_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ServoTimer_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ServoTimer_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the ServoTimer.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - ServoTimer_STATUS_DOWN    - Set if counting down
*     - ServoTimer_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 ServoTimer_ReadStatus(void)
{
    return ((ServoTimer_STATUS_REG >> ServoTimer_RUNNING_STATUS_SHIFT) |
            (ServoTimer_STATUS_REG & ServoTimer_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: ServoTimer_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - ServoTimer_INTR_MASK_TC       - Terminal count mask
*     - ServoTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetInterruptMode(uint32 interruptMask)
{
    ServoTimer_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: ServoTimer_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - ServoTimer_INTR_MASK_TC       - Terminal count mask
*     - ServoTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 ServoTimer_GetInterruptSourceMasked(void)
{
    return (ServoTimer_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: ServoTimer_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - ServoTimer_INTR_MASK_TC       - Terminal count mask
*     - ServoTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 ServoTimer_GetInterruptSource(void)
{
    return (ServoTimer_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: ServoTimer_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - ServoTimer_INTR_MASK_TC       - Terminal count mask
*     - ServoTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_ClearInterrupt(uint32 interruptMask)
{
    ServoTimer_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: ServoTimer_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - ServoTimer_INTR_MASK_TC       - Terminal count mask
*     - ServoTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SetInterrupt(uint32 interruptMask)
{
    ServoTimer_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
