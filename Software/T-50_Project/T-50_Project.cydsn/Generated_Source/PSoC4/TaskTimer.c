/*******************************************************************************
* File Name: TaskTimer.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the TaskTimer
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

#include "TaskTimer.h"

uint8 TaskTimer_initVar = 0u;


/*******************************************************************************
* Function Name: TaskTimer_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default TaskTimer configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (TaskTimer__QUAD == TaskTimer_CONFIG)
        TaskTimer_CONTROL_REG = TaskTimer_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        TaskTimer_TRIG_CONTROL1_REG  = TaskTimer_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        TaskTimer_SetInterruptMode(TaskTimer_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        TaskTimer_SetCounterMode(TaskTimer_COUNT_DOWN);
        TaskTimer_WritePeriod(TaskTimer_QUAD_PERIOD_INIT_VALUE);
        TaskTimer_WriteCounter(TaskTimer_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (TaskTimer__QUAD == TaskTimer_CONFIG) */

    #if (TaskTimer__TIMER == TaskTimer_CONFIG)
        TaskTimer_CONTROL_REG = TaskTimer_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        TaskTimer_TRIG_CONTROL1_REG  = TaskTimer_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        TaskTimer_SetInterruptMode(TaskTimer_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        TaskTimer_WritePeriod(TaskTimer_TC_PERIOD_VALUE );

        #if (TaskTimer__COMPARE == TaskTimer_TC_COMP_CAP_MODE)
            TaskTimer_WriteCompare(TaskTimer_TC_COMPARE_VALUE);

            #if (1u == TaskTimer_TC_COMPARE_SWAP)
                TaskTimer_SetCompareSwap(1u);
                TaskTimer_WriteCompareBuf(TaskTimer_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == TaskTimer_TC_COMPARE_SWAP) */
        #endif  /* (TaskTimer__COMPARE == TaskTimer_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (TaskTimer_CY_TCPWM_V2 && TaskTimer_TIMER_UPDOWN_CNT_USED && !TaskTimer_CY_TCPWM_4000)
            TaskTimer_WriteCounter(1u);
        #elif(TaskTimer__COUNT_DOWN == TaskTimer_TC_COUNTER_MODE)
            TaskTimer_WriteCounter(TaskTimer_TC_PERIOD_VALUE);
        #else
            TaskTimer_WriteCounter(0u);
        #endif /* (TaskTimer_CY_TCPWM_V2 && TaskTimer_TIMER_UPDOWN_CNT_USED && !TaskTimer_CY_TCPWM_4000) */
    #endif  /* (TaskTimer__TIMER == TaskTimer_CONFIG) */

    #if (TaskTimer__PWM_SEL == TaskTimer_CONFIG)
        TaskTimer_CONTROL_REG = TaskTimer_CTRL_PWM_BASE_CONFIG;

        #if (TaskTimer__PWM_PR == TaskTimer_PWM_MODE)
            TaskTimer_CONTROL_REG |= TaskTimer_CTRL_PWM_RUN_MODE;
            TaskTimer_WriteCounter(TaskTimer_PWM_PR_INIT_VALUE);
        #else
            TaskTimer_CONTROL_REG |= TaskTimer_CTRL_PWM_ALIGN | TaskTimer_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (TaskTimer_CY_TCPWM_V2 && TaskTimer_PWM_UPDOWN_CNT_USED && !TaskTimer_CY_TCPWM_4000)
                TaskTimer_WriteCounter(1u);
            #elif (TaskTimer__RIGHT == TaskTimer_PWM_ALIGN)
                TaskTimer_WriteCounter(TaskTimer_PWM_PERIOD_VALUE);
            #else 
                TaskTimer_WriteCounter(0u);
            #endif  /* (TaskTimer_CY_TCPWM_V2 && TaskTimer_PWM_UPDOWN_CNT_USED && !TaskTimer_CY_TCPWM_4000) */
        #endif  /* (TaskTimer__PWM_PR == TaskTimer_PWM_MODE) */

        #if (TaskTimer__PWM_DT == TaskTimer_PWM_MODE)
            TaskTimer_CONTROL_REG |= TaskTimer_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (TaskTimer__PWM_DT == TaskTimer_PWM_MODE) */

        #if (TaskTimer__PWM == TaskTimer_PWM_MODE)
            TaskTimer_CONTROL_REG |= TaskTimer_CTRL_PWM_PRESCALER;
        #endif  /* (TaskTimer__PWM == TaskTimer_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        TaskTimer_TRIG_CONTROL1_REG  = TaskTimer_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        TaskTimer_SetInterruptMode(TaskTimer_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (TaskTimer__PWM_PR == TaskTimer_PWM_MODE)
            TaskTimer_TRIG_CONTROL2_REG =
                    (TaskTimer_CC_MATCH_NO_CHANGE    |
                    TaskTimer_OVERLOW_NO_CHANGE      |
                    TaskTimer_UNDERFLOW_NO_CHANGE);
        #else
            #if (TaskTimer__LEFT == TaskTimer_PWM_ALIGN)
                TaskTimer_TRIG_CONTROL2_REG = TaskTimer_PWM_MODE_LEFT;
            #endif  /* ( TaskTimer_PWM_LEFT == TaskTimer_PWM_ALIGN) */

            #if (TaskTimer__RIGHT == TaskTimer_PWM_ALIGN)
                TaskTimer_TRIG_CONTROL2_REG = TaskTimer_PWM_MODE_RIGHT;
            #endif  /* ( TaskTimer_PWM_RIGHT == TaskTimer_PWM_ALIGN) */

            #if (TaskTimer__CENTER == TaskTimer_PWM_ALIGN)
                TaskTimer_TRIG_CONTROL2_REG = TaskTimer_PWM_MODE_CENTER;
            #endif  /* ( TaskTimer_PWM_CENTER == TaskTimer_PWM_ALIGN) */

            #if (TaskTimer__ASYMMETRIC == TaskTimer_PWM_ALIGN)
                TaskTimer_TRIG_CONTROL2_REG = TaskTimer_PWM_MODE_ASYM;
            #endif  /* (TaskTimer__ASYMMETRIC == TaskTimer_PWM_ALIGN) */
        #endif  /* (TaskTimer__PWM_PR == TaskTimer_PWM_MODE) */

        /* Set other values from customizer */
        TaskTimer_WritePeriod(TaskTimer_PWM_PERIOD_VALUE );
        TaskTimer_WriteCompare(TaskTimer_PWM_COMPARE_VALUE);

        #if (1u == TaskTimer_PWM_COMPARE_SWAP)
            TaskTimer_SetCompareSwap(1u);
            TaskTimer_WriteCompareBuf(TaskTimer_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == TaskTimer_PWM_COMPARE_SWAP) */

        #if (1u == TaskTimer_PWM_PERIOD_SWAP)
            TaskTimer_SetPeriodSwap(1u);
            TaskTimer_WritePeriodBuf(TaskTimer_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == TaskTimer_PWM_PERIOD_SWAP) */
    #endif  /* (TaskTimer__PWM_SEL == TaskTimer_CONFIG) */
    
}


/*******************************************************************************
* Function Name: TaskTimer_Enable
********************************************************************************
*
* Summary:
*  Enables the TaskTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    TaskTimer_BLOCK_CONTROL_REG |= TaskTimer_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (TaskTimer__PWM_SEL == TaskTimer_CONFIG)
        #if (0u == TaskTimer_PWM_START_SIGNAL_PRESENT)
            TaskTimer_TriggerCommand(TaskTimer_MASK, TaskTimer_CMD_START);
        #endif /* (0u == TaskTimer_PWM_START_SIGNAL_PRESENT) */
    #endif /* (TaskTimer__PWM_SEL == TaskTimer_CONFIG) */

    #if (TaskTimer__TIMER == TaskTimer_CONFIG)
        #if (0u == TaskTimer_TC_START_SIGNAL_PRESENT)
            TaskTimer_TriggerCommand(TaskTimer_MASK, TaskTimer_CMD_START);
        #endif /* (0u == TaskTimer_TC_START_SIGNAL_PRESENT) */
    #endif /* (TaskTimer__TIMER == TaskTimer_CONFIG) */
}


/*******************************************************************************
* Function Name: TaskTimer_Start
********************************************************************************
*
* Summary:
*  Initializes the TaskTimer with default customizer
*  values when called the first time and enables the TaskTimer.
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
*  TaskTimer_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time TaskTimer_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the TaskTimer_Start() routine.
*
*******************************************************************************/
void TaskTimer_Start(void)
{
    if (0u == TaskTimer_initVar)
    {
        TaskTimer_Init();
        TaskTimer_initVar = 1u;
    }

    TaskTimer_Enable();
}


/*******************************************************************************
* Function Name: TaskTimer_Stop
********************************************************************************
*
* Summary:
*  Disables the TaskTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_BLOCK_CONTROL_REG &= (uint32)~TaskTimer_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the TaskTimer. This function is used when
*  configured as a generic TaskTimer and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the TaskTimer to operate in
*   Values:
*   - TaskTimer_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - TaskTimer_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - TaskTimer_MODE_QUAD - Quadrature decoder
*         - TaskTimer_MODE_PWM - PWM
*         - TaskTimer_MODE_PWM_DT - PWM with dead time
*         - TaskTimer_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_CONTROL_REG &= (uint32)~TaskTimer_MODE_MASK;
    TaskTimer_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - TaskTimer_MODE_X1 - Counts on phi 1 rising
*         - TaskTimer_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - TaskTimer_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_CONTROL_REG &= (uint32)~TaskTimer_QUAD_MODE_MASK;
    TaskTimer_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - TaskTimer_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - TaskTimer_PRESCALE_DIVBY2    - Divide by 2
*         - TaskTimer_PRESCALE_DIVBY4    - Divide by 4
*         - TaskTimer_PRESCALE_DIVBY8    - Divide by 8
*         - TaskTimer_PRESCALE_DIVBY16   - Divide by 16
*         - TaskTimer_PRESCALE_DIVBY32   - Divide by 32
*         - TaskTimer_PRESCALE_DIVBY64   - Divide by 64
*         - TaskTimer_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_CONTROL_REG &= (uint32)~TaskTimer_PRESCALER_MASK;
    TaskTimer_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the TaskTimer runs
*  continuously or stops when terminal count is reached.  By default the
*  TaskTimer operates in the continuous mode.
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
void TaskTimer_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_CONTROL_REG &= (uint32)~TaskTimer_ONESHOT_MASK;
    TaskTimer_CONTROL_REG |= ((uint32)((oneShotEnable & TaskTimer_1BIT_MASK) <<
                                                               TaskTimer_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_SetPWMMode
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
void TaskTimer_SetPWMMode(uint32 modeMask)
{
    TaskTimer_TRIG_CONTROL2_REG = (modeMask & TaskTimer_6BIT_MASK);
}



/*******************************************************************************
* Function Name: TaskTimer_SetPWMSyncKill
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
void TaskTimer_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_CONTROL_REG &= (uint32)~TaskTimer_PWM_SYNC_KILL_MASK;
    TaskTimer_CONTROL_REG |= ((uint32)((syncKillEnable & TaskTimer_1BIT_MASK)  <<
                                               TaskTimer_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_SetPWMStopOnKill
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
void TaskTimer_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_CONTROL_REG &= (uint32)~TaskTimer_PWM_STOP_KILL_MASK;
    TaskTimer_CONTROL_REG |= ((uint32)((stopOnKillEnable & TaskTimer_1BIT_MASK)  <<
                                                         TaskTimer_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_SetPWMDeadTime
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
void TaskTimer_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_CONTROL_REG &= (uint32)~TaskTimer_PRESCALER_MASK;
    TaskTimer_CONTROL_REG |= ((uint32)((deadTime & TaskTimer_8BIT_MASK) <<
                                                          TaskTimer_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_SetPWMInvert
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
*         - TaskTimer_INVERT_LINE   - Inverts the line output
*         - TaskTimer_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_CONTROL_REG &= (uint32)~TaskTimer_INV_OUT_MASK;
    TaskTimer_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: TaskTimer_WriteCounter
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
void TaskTimer_WriteCounter(uint32 count)
{
    TaskTimer_COUNTER_REG = (count & TaskTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TaskTimer_ReadCounter
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
uint32 TaskTimer_ReadCounter(void)
{
    return (TaskTimer_COUNTER_REG & TaskTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TaskTimer_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - TaskTimer_COUNT_UP       - Counts up
*     - TaskTimer_COUNT_DOWN     - Counts down
*     - TaskTimer_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - TaskTimer_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_CONTROL_REG &= (uint32)~TaskTimer_UPDOWN_MASK;
    TaskTimer_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_WritePeriod
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
void TaskTimer_WritePeriod(uint32 period)
{
    TaskTimer_PERIOD_REG = (period & TaskTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TaskTimer_ReadPeriod
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
uint32 TaskTimer_ReadPeriod(void)
{
    return (TaskTimer_PERIOD_REG & TaskTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TaskTimer_SetCompareSwap
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
void TaskTimer_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_CONTROL_REG &= (uint32)~TaskTimer_RELOAD_CC_MASK;
    TaskTimer_CONTROL_REG |= (swapEnable & TaskTimer_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_WritePeriodBuf
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
void TaskTimer_WritePeriodBuf(uint32 periodBuf)
{
    TaskTimer_PERIOD_BUF_REG = (periodBuf & TaskTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TaskTimer_ReadPeriodBuf
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
uint32 TaskTimer_ReadPeriodBuf(void)
{
    return (TaskTimer_PERIOD_BUF_REG & TaskTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TaskTimer_SetPeriodSwap
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
void TaskTimer_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_CONTROL_REG &= (uint32)~TaskTimer_RELOAD_PERIOD_MASK;
    TaskTimer_CONTROL_REG |= ((uint32)((swapEnable & TaskTimer_1BIT_MASK) <<
                                                            TaskTimer_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_WriteCompare
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
void TaskTimer_WriteCompare(uint32 compare)
{
    #if (TaskTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (TaskTimer_CY_TCPWM_4000) */

    #if (TaskTimer_CY_TCPWM_4000)
        currentMode = ((TaskTimer_CONTROL_REG & TaskTimer_UPDOWN_MASK) >> TaskTimer_UPDOWN_SHIFT);

        if (((uint32)TaskTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)TaskTimer__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (TaskTimer_CY_TCPWM_4000) */
    
    TaskTimer_COMP_CAP_REG = (compare & TaskTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TaskTimer_ReadCompare
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
uint32 TaskTimer_ReadCompare(void)
{
    #if (TaskTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (TaskTimer_CY_TCPWM_4000) */

    #if (TaskTimer_CY_TCPWM_4000)
        currentMode = ((TaskTimer_CONTROL_REG & TaskTimer_UPDOWN_MASK) >> TaskTimer_UPDOWN_SHIFT);
        
        regVal = TaskTimer_COMP_CAP_REG;
        
        if (((uint32)TaskTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)TaskTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & TaskTimer_16BIT_MASK);
    #else
        return (TaskTimer_COMP_CAP_REG & TaskTimer_16BIT_MASK);
    #endif /* (TaskTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: TaskTimer_WriteCompareBuf
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
void TaskTimer_WriteCompareBuf(uint32 compareBuf)
{
    #if (TaskTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (TaskTimer_CY_TCPWM_4000) */

    #if (TaskTimer_CY_TCPWM_4000)
        currentMode = ((TaskTimer_CONTROL_REG & TaskTimer_UPDOWN_MASK) >> TaskTimer_UPDOWN_SHIFT);

        if (((uint32)TaskTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)TaskTimer__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (TaskTimer_CY_TCPWM_4000) */
    
    TaskTimer_COMP_CAP_BUF_REG = (compareBuf & TaskTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TaskTimer_ReadCompareBuf
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
uint32 TaskTimer_ReadCompareBuf(void)
{
    #if (TaskTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (TaskTimer_CY_TCPWM_4000) */

    #if (TaskTimer_CY_TCPWM_4000)
        currentMode = ((TaskTimer_CONTROL_REG & TaskTimer_UPDOWN_MASK) >> TaskTimer_UPDOWN_SHIFT);

        regVal = TaskTimer_COMP_CAP_BUF_REG;
        
        if (((uint32)TaskTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)TaskTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & TaskTimer_16BIT_MASK);
    #else
        return (TaskTimer_COMP_CAP_BUF_REG & TaskTimer_16BIT_MASK);
    #endif /* (TaskTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: TaskTimer_ReadCapture
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
uint32 TaskTimer_ReadCapture(void)
{
    return (TaskTimer_COMP_CAP_REG & TaskTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TaskTimer_ReadCaptureBuf
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
uint32 TaskTimer_ReadCaptureBuf(void)
{
    return (TaskTimer_COMP_CAP_BUF_REG & TaskTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TaskTimer_SetCaptureMode
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
*     - TaskTimer_TRIG_LEVEL     - Level
*     - TaskTimer_TRIG_RISING    - Rising edge
*     - TaskTimer_TRIG_FALLING   - Falling edge
*     - TaskTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_TRIG_CONTROL1_REG &= (uint32)~TaskTimer_CAPTURE_MASK;
    TaskTimer_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TaskTimer_TRIG_LEVEL     - Level
*     - TaskTimer_TRIG_RISING    - Rising edge
*     - TaskTimer_TRIG_FALLING   - Falling edge
*     - TaskTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_TRIG_CONTROL1_REG &= (uint32)~TaskTimer_RELOAD_MASK;
    TaskTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TaskTimer_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TaskTimer_TRIG_LEVEL     - Level
*     - TaskTimer_TRIG_RISING    - Rising edge
*     - TaskTimer_TRIG_FALLING   - Falling edge
*     - TaskTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_TRIG_CONTROL1_REG &= (uint32)~TaskTimer_START_MASK;
    TaskTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TaskTimer_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TaskTimer_TRIG_LEVEL     - Level
*     - TaskTimer_TRIG_RISING    - Rising edge
*     - TaskTimer_TRIG_FALLING   - Falling edge
*     - TaskTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_TRIG_CONTROL1_REG &= (uint32)~TaskTimer_STOP_MASK;
    TaskTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TaskTimer_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TaskTimer_TRIG_LEVEL     - Level
*     - TaskTimer_TRIG_RISING    - Rising edge
*     - TaskTimer_TRIG_FALLING   - Falling edge
*     - TaskTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_TRIG_CONTROL1_REG &= (uint32)~TaskTimer_COUNT_MASK;
    TaskTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TaskTimer_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_TriggerCommand
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
*     - TaskTimer_CMD_CAPTURE    - Trigger Capture command
*     - TaskTimer_CMD_RELOAD     - Trigger Reload command
*     - TaskTimer_CMD_STOP       - Trigger Stop command
*     - TaskTimer_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TaskTimer_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TaskTimer_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the TaskTimer.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - TaskTimer_STATUS_DOWN    - Set if counting down
*     - TaskTimer_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 TaskTimer_ReadStatus(void)
{
    return ((TaskTimer_STATUS_REG >> TaskTimer_RUNNING_STATUS_SHIFT) |
            (TaskTimer_STATUS_REG & TaskTimer_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: TaskTimer_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - TaskTimer_INTR_MASK_TC       - Terminal count mask
*     - TaskTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_SetInterruptMode(uint32 interruptMask)
{
    TaskTimer_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: TaskTimer_GetInterruptSourceMasked
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
*     - TaskTimer_INTR_MASK_TC       - Terminal count mask
*     - TaskTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 TaskTimer_GetInterruptSourceMasked(void)
{
    return (TaskTimer_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: TaskTimer_GetInterruptSource
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
*     - TaskTimer_INTR_MASK_TC       - Terminal count mask
*     - TaskTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 TaskTimer_GetInterruptSource(void)
{
    return (TaskTimer_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: TaskTimer_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - TaskTimer_INTR_MASK_TC       - Terminal count mask
*     - TaskTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_ClearInterrupt(uint32 interruptMask)
{
    TaskTimer_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: TaskTimer_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - TaskTimer_INTR_MASK_TC       - Terminal count mask
*     - TaskTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TaskTimer_SetInterrupt(uint32 interruptMask)
{
    TaskTimer_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
