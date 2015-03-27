/*******************************************************************************
* File Name: NavLightPWM.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the NavLightPWM
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

#include "NavLightPWM.h"

uint8 NavLightPWM_initVar = 0u;


/*******************************************************************************
* Function Name: NavLightPWM_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default NavLightPWM configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (NavLightPWM__QUAD == NavLightPWM_CONFIG)
        NavLightPWM_CONTROL_REG = NavLightPWM_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        NavLightPWM_TRIG_CONTROL1_REG  = NavLightPWM_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        NavLightPWM_SetInterruptMode(NavLightPWM_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        NavLightPWM_SetCounterMode(NavLightPWM_COUNT_DOWN);
        NavLightPWM_WritePeriod(NavLightPWM_QUAD_PERIOD_INIT_VALUE);
        NavLightPWM_WriteCounter(NavLightPWM_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (NavLightPWM__QUAD == NavLightPWM_CONFIG) */

    #if (NavLightPWM__TIMER == NavLightPWM_CONFIG)
        NavLightPWM_CONTROL_REG = NavLightPWM_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        NavLightPWM_TRIG_CONTROL1_REG  = NavLightPWM_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        NavLightPWM_SetInterruptMode(NavLightPWM_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        NavLightPWM_WritePeriod(NavLightPWM_TC_PERIOD_VALUE );

        #if (NavLightPWM__COMPARE == NavLightPWM_TC_COMP_CAP_MODE)
            NavLightPWM_WriteCompare(NavLightPWM_TC_COMPARE_VALUE);

            #if (1u == NavLightPWM_TC_COMPARE_SWAP)
                NavLightPWM_SetCompareSwap(1u);
                NavLightPWM_WriteCompareBuf(NavLightPWM_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == NavLightPWM_TC_COMPARE_SWAP) */
        #endif  /* (NavLightPWM__COMPARE == NavLightPWM_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (NavLightPWM_CY_TCPWM_V2 && NavLightPWM_TIMER_UPDOWN_CNT_USED && !NavLightPWM_CY_TCPWM_4000)
            NavLightPWM_WriteCounter(1u);
        #elif(NavLightPWM__COUNT_DOWN == NavLightPWM_TC_COUNTER_MODE)
            NavLightPWM_WriteCounter(NavLightPWM_TC_PERIOD_VALUE);
        #else
            NavLightPWM_WriteCounter(0u);
        #endif /* (NavLightPWM_CY_TCPWM_V2 && NavLightPWM_TIMER_UPDOWN_CNT_USED && !NavLightPWM_CY_TCPWM_4000) */
    #endif  /* (NavLightPWM__TIMER == NavLightPWM_CONFIG) */

    #if (NavLightPWM__PWM_SEL == NavLightPWM_CONFIG)
        NavLightPWM_CONTROL_REG = NavLightPWM_CTRL_PWM_BASE_CONFIG;

        #if (NavLightPWM__PWM_PR == NavLightPWM_PWM_MODE)
            NavLightPWM_CONTROL_REG |= NavLightPWM_CTRL_PWM_RUN_MODE;
            NavLightPWM_WriteCounter(NavLightPWM_PWM_PR_INIT_VALUE);
        #else
            NavLightPWM_CONTROL_REG |= NavLightPWM_CTRL_PWM_ALIGN | NavLightPWM_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (NavLightPWM_CY_TCPWM_V2 && NavLightPWM_PWM_UPDOWN_CNT_USED && !NavLightPWM_CY_TCPWM_4000)
                NavLightPWM_WriteCounter(1u);
            #elif (NavLightPWM__RIGHT == NavLightPWM_PWM_ALIGN)
                NavLightPWM_WriteCounter(NavLightPWM_PWM_PERIOD_VALUE);
            #else 
                NavLightPWM_WriteCounter(0u);
            #endif  /* (NavLightPWM_CY_TCPWM_V2 && NavLightPWM_PWM_UPDOWN_CNT_USED && !NavLightPWM_CY_TCPWM_4000) */
        #endif  /* (NavLightPWM__PWM_PR == NavLightPWM_PWM_MODE) */

        #if (NavLightPWM__PWM_DT == NavLightPWM_PWM_MODE)
            NavLightPWM_CONTROL_REG |= NavLightPWM_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (NavLightPWM__PWM_DT == NavLightPWM_PWM_MODE) */

        #if (NavLightPWM__PWM == NavLightPWM_PWM_MODE)
            NavLightPWM_CONTROL_REG |= NavLightPWM_CTRL_PWM_PRESCALER;
        #endif  /* (NavLightPWM__PWM == NavLightPWM_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        NavLightPWM_TRIG_CONTROL1_REG  = NavLightPWM_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        NavLightPWM_SetInterruptMode(NavLightPWM_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (NavLightPWM__PWM_PR == NavLightPWM_PWM_MODE)
            NavLightPWM_TRIG_CONTROL2_REG =
                    (NavLightPWM_CC_MATCH_NO_CHANGE    |
                    NavLightPWM_OVERLOW_NO_CHANGE      |
                    NavLightPWM_UNDERFLOW_NO_CHANGE);
        #else
            #if (NavLightPWM__LEFT == NavLightPWM_PWM_ALIGN)
                NavLightPWM_TRIG_CONTROL2_REG = NavLightPWM_PWM_MODE_LEFT;
            #endif  /* ( NavLightPWM_PWM_LEFT == NavLightPWM_PWM_ALIGN) */

            #if (NavLightPWM__RIGHT == NavLightPWM_PWM_ALIGN)
                NavLightPWM_TRIG_CONTROL2_REG = NavLightPWM_PWM_MODE_RIGHT;
            #endif  /* ( NavLightPWM_PWM_RIGHT == NavLightPWM_PWM_ALIGN) */

            #if (NavLightPWM__CENTER == NavLightPWM_PWM_ALIGN)
                NavLightPWM_TRIG_CONTROL2_REG = NavLightPWM_PWM_MODE_CENTER;
            #endif  /* ( NavLightPWM_PWM_CENTER == NavLightPWM_PWM_ALIGN) */

            #if (NavLightPWM__ASYMMETRIC == NavLightPWM_PWM_ALIGN)
                NavLightPWM_TRIG_CONTROL2_REG = NavLightPWM_PWM_MODE_ASYM;
            #endif  /* (NavLightPWM__ASYMMETRIC == NavLightPWM_PWM_ALIGN) */
        #endif  /* (NavLightPWM__PWM_PR == NavLightPWM_PWM_MODE) */

        /* Set other values from customizer */
        NavLightPWM_WritePeriod(NavLightPWM_PWM_PERIOD_VALUE );
        NavLightPWM_WriteCompare(NavLightPWM_PWM_COMPARE_VALUE);

        #if (1u == NavLightPWM_PWM_COMPARE_SWAP)
            NavLightPWM_SetCompareSwap(1u);
            NavLightPWM_WriteCompareBuf(NavLightPWM_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == NavLightPWM_PWM_COMPARE_SWAP) */

        #if (1u == NavLightPWM_PWM_PERIOD_SWAP)
            NavLightPWM_SetPeriodSwap(1u);
            NavLightPWM_WritePeriodBuf(NavLightPWM_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == NavLightPWM_PWM_PERIOD_SWAP) */
    #endif  /* (NavLightPWM__PWM_SEL == NavLightPWM_CONFIG) */
    
}


/*******************************************************************************
* Function Name: NavLightPWM_Enable
********************************************************************************
*
* Summary:
*  Enables the NavLightPWM.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    NavLightPWM_BLOCK_CONTROL_REG |= NavLightPWM_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (NavLightPWM__PWM_SEL == NavLightPWM_CONFIG)
        #if (0u == NavLightPWM_PWM_START_SIGNAL_PRESENT)
            NavLightPWM_TriggerCommand(NavLightPWM_MASK, NavLightPWM_CMD_START);
        #endif /* (0u == NavLightPWM_PWM_START_SIGNAL_PRESENT) */
    #endif /* (NavLightPWM__PWM_SEL == NavLightPWM_CONFIG) */

    #if (NavLightPWM__TIMER == NavLightPWM_CONFIG)
        #if (0u == NavLightPWM_TC_START_SIGNAL_PRESENT)
            NavLightPWM_TriggerCommand(NavLightPWM_MASK, NavLightPWM_CMD_START);
        #endif /* (0u == NavLightPWM_TC_START_SIGNAL_PRESENT) */
    #endif /* (NavLightPWM__TIMER == NavLightPWM_CONFIG) */
}


/*******************************************************************************
* Function Name: NavLightPWM_Start
********************************************************************************
*
* Summary:
*  Initializes the NavLightPWM with default customizer
*  values when called the first time and enables the NavLightPWM.
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
*  NavLightPWM_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time NavLightPWM_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the NavLightPWM_Start() routine.
*
*******************************************************************************/
void NavLightPWM_Start(void)
{
    if (0u == NavLightPWM_initVar)
    {
        NavLightPWM_Init();
        NavLightPWM_initVar = 1u;
    }

    NavLightPWM_Enable();
}


/*******************************************************************************
* Function Name: NavLightPWM_Stop
********************************************************************************
*
* Summary:
*  Disables the NavLightPWM.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_BLOCK_CONTROL_REG &= (uint32)~NavLightPWM_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the NavLightPWM. This function is used when
*  configured as a generic NavLightPWM and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the NavLightPWM to operate in
*   Values:
*   - NavLightPWM_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - NavLightPWM_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - NavLightPWM_MODE_QUAD - Quadrature decoder
*         - NavLightPWM_MODE_PWM - PWM
*         - NavLightPWM_MODE_PWM_DT - PWM with dead time
*         - NavLightPWM_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_CONTROL_REG &= (uint32)~NavLightPWM_MODE_MASK;
    NavLightPWM_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - NavLightPWM_MODE_X1 - Counts on phi 1 rising
*         - NavLightPWM_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - NavLightPWM_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_CONTROL_REG &= (uint32)~NavLightPWM_QUAD_MODE_MASK;
    NavLightPWM_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - NavLightPWM_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - NavLightPWM_PRESCALE_DIVBY2    - Divide by 2
*         - NavLightPWM_PRESCALE_DIVBY4    - Divide by 4
*         - NavLightPWM_PRESCALE_DIVBY8    - Divide by 8
*         - NavLightPWM_PRESCALE_DIVBY16   - Divide by 16
*         - NavLightPWM_PRESCALE_DIVBY32   - Divide by 32
*         - NavLightPWM_PRESCALE_DIVBY64   - Divide by 64
*         - NavLightPWM_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_CONTROL_REG &= (uint32)~NavLightPWM_PRESCALER_MASK;
    NavLightPWM_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the NavLightPWM runs
*  continuously or stops when terminal count is reached.  By default the
*  NavLightPWM operates in the continuous mode.
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
void NavLightPWM_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_CONTROL_REG &= (uint32)~NavLightPWM_ONESHOT_MASK;
    NavLightPWM_CONTROL_REG |= ((uint32)((oneShotEnable & NavLightPWM_1BIT_MASK) <<
                                                               NavLightPWM_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_SetPWMMode
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
void NavLightPWM_SetPWMMode(uint32 modeMask)
{
    NavLightPWM_TRIG_CONTROL2_REG = (modeMask & NavLightPWM_6BIT_MASK);
}



/*******************************************************************************
* Function Name: NavLightPWM_SetPWMSyncKill
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
void NavLightPWM_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_CONTROL_REG &= (uint32)~NavLightPWM_PWM_SYNC_KILL_MASK;
    NavLightPWM_CONTROL_REG |= ((uint32)((syncKillEnable & NavLightPWM_1BIT_MASK)  <<
                                               NavLightPWM_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_SetPWMStopOnKill
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
void NavLightPWM_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_CONTROL_REG &= (uint32)~NavLightPWM_PWM_STOP_KILL_MASK;
    NavLightPWM_CONTROL_REG |= ((uint32)((stopOnKillEnable & NavLightPWM_1BIT_MASK)  <<
                                                         NavLightPWM_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_SetPWMDeadTime
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
void NavLightPWM_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_CONTROL_REG &= (uint32)~NavLightPWM_PRESCALER_MASK;
    NavLightPWM_CONTROL_REG |= ((uint32)((deadTime & NavLightPWM_8BIT_MASK) <<
                                                          NavLightPWM_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_SetPWMInvert
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
*         - NavLightPWM_INVERT_LINE   - Inverts the line output
*         - NavLightPWM_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_CONTROL_REG &= (uint32)~NavLightPWM_INV_OUT_MASK;
    NavLightPWM_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: NavLightPWM_WriteCounter
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
void NavLightPWM_WriteCounter(uint32 count)
{
    NavLightPWM_COUNTER_REG = (count & NavLightPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: NavLightPWM_ReadCounter
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
uint32 NavLightPWM_ReadCounter(void)
{
    return (NavLightPWM_COUNTER_REG & NavLightPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: NavLightPWM_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - NavLightPWM_COUNT_UP       - Counts up
*     - NavLightPWM_COUNT_DOWN     - Counts down
*     - NavLightPWM_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - NavLightPWM_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_CONTROL_REG &= (uint32)~NavLightPWM_UPDOWN_MASK;
    NavLightPWM_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_WritePeriod
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
void NavLightPWM_WritePeriod(uint32 period)
{
    NavLightPWM_PERIOD_REG = (period & NavLightPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: NavLightPWM_ReadPeriod
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
uint32 NavLightPWM_ReadPeriod(void)
{
    return (NavLightPWM_PERIOD_REG & NavLightPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: NavLightPWM_SetCompareSwap
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
void NavLightPWM_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_CONTROL_REG &= (uint32)~NavLightPWM_RELOAD_CC_MASK;
    NavLightPWM_CONTROL_REG |= (swapEnable & NavLightPWM_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_WritePeriodBuf
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
void NavLightPWM_WritePeriodBuf(uint32 periodBuf)
{
    NavLightPWM_PERIOD_BUF_REG = (periodBuf & NavLightPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: NavLightPWM_ReadPeriodBuf
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
uint32 NavLightPWM_ReadPeriodBuf(void)
{
    return (NavLightPWM_PERIOD_BUF_REG & NavLightPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: NavLightPWM_SetPeriodSwap
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
void NavLightPWM_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_CONTROL_REG &= (uint32)~NavLightPWM_RELOAD_PERIOD_MASK;
    NavLightPWM_CONTROL_REG |= ((uint32)((swapEnable & NavLightPWM_1BIT_MASK) <<
                                                            NavLightPWM_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_WriteCompare
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
void NavLightPWM_WriteCompare(uint32 compare)
{
    #if (NavLightPWM_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (NavLightPWM_CY_TCPWM_4000) */

    #if (NavLightPWM_CY_TCPWM_4000)
        currentMode = ((NavLightPWM_CONTROL_REG & NavLightPWM_UPDOWN_MASK) >> NavLightPWM_UPDOWN_SHIFT);

        if (((uint32)NavLightPWM__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)NavLightPWM__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (NavLightPWM_CY_TCPWM_4000) */
    
    NavLightPWM_COMP_CAP_REG = (compare & NavLightPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: NavLightPWM_ReadCompare
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
uint32 NavLightPWM_ReadCompare(void)
{
    #if (NavLightPWM_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (NavLightPWM_CY_TCPWM_4000) */

    #if (NavLightPWM_CY_TCPWM_4000)
        currentMode = ((NavLightPWM_CONTROL_REG & NavLightPWM_UPDOWN_MASK) >> NavLightPWM_UPDOWN_SHIFT);
        
        regVal = NavLightPWM_COMP_CAP_REG;
        
        if (((uint32)NavLightPWM__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)NavLightPWM__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & NavLightPWM_16BIT_MASK);
    #else
        return (NavLightPWM_COMP_CAP_REG & NavLightPWM_16BIT_MASK);
    #endif /* (NavLightPWM_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: NavLightPWM_WriteCompareBuf
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
void NavLightPWM_WriteCompareBuf(uint32 compareBuf)
{
    #if (NavLightPWM_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (NavLightPWM_CY_TCPWM_4000) */

    #if (NavLightPWM_CY_TCPWM_4000)
        currentMode = ((NavLightPWM_CONTROL_REG & NavLightPWM_UPDOWN_MASK) >> NavLightPWM_UPDOWN_SHIFT);

        if (((uint32)NavLightPWM__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)NavLightPWM__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (NavLightPWM_CY_TCPWM_4000) */
    
    NavLightPWM_COMP_CAP_BUF_REG = (compareBuf & NavLightPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: NavLightPWM_ReadCompareBuf
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
uint32 NavLightPWM_ReadCompareBuf(void)
{
    #if (NavLightPWM_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (NavLightPWM_CY_TCPWM_4000) */

    #if (NavLightPWM_CY_TCPWM_4000)
        currentMode = ((NavLightPWM_CONTROL_REG & NavLightPWM_UPDOWN_MASK) >> NavLightPWM_UPDOWN_SHIFT);

        regVal = NavLightPWM_COMP_CAP_BUF_REG;
        
        if (((uint32)NavLightPWM__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)NavLightPWM__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & NavLightPWM_16BIT_MASK);
    #else
        return (NavLightPWM_COMP_CAP_BUF_REG & NavLightPWM_16BIT_MASK);
    #endif /* (NavLightPWM_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: NavLightPWM_ReadCapture
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
uint32 NavLightPWM_ReadCapture(void)
{
    return (NavLightPWM_COMP_CAP_REG & NavLightPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: NavLightPWM_ReadCaptureBuf
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
uint32 NavLightPWM_ReadCaptureBuf(void)
{
    return (NavLightPWM_COMP_CAP_BUF_REG & NavLightPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: NavLightPWM_SetCaptureMode
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
*     - NavLightPWM_TRIG_LEVEL     - Level
*     - NavLightPWM_TRIG_RISING    - Rising edge
*     - NavLightPWM_TRIG_FALLING   - Falling edge
*     - NavLightPWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_TRIG_CONTROL1_REG &= (uint32)~NavLightPWM_CAPTURE_MASK;
    NavLightPWM_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - NavLightPWM_TRIG_LEVEL     - Level
*     - NavLightPWM_TRIG_RISING    - Rising edge
*     - NavLightPWM_TRIG_FALLING   - Falling edge
*     - NavLightPWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_TRIG_CONTROL1_REG &= (uint32)~NavLightPWM_RELOAD_MASK;
    NavLightPWM_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << NavLightPWM_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - NavLightPWM_TRIG_LEVEL     - Level
*     - NavLightPWM_TRIG_RISING    - Rising edge
*     - NavLightPWM_TRIG_FALLING   - Falling edge
*     - NavLightPWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_TRIG_CONTROL1_REG &= (uint32)~NavLightPWM_START_MASK;
    NavLightPWM_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << NavLightPWM_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - NavLightPWM_TRIG_LEVEL     - Level
*     - NavLightPWM_TRIG_RISING    - Rising edge
*     - NavLightPWM_TRIG_FALLING   - Falling edge
*     - NavLightPWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_TRIG_CONTROL1_REG &= (uint32)~NavLightPWM_STOP_MASK;
    NavLightPWM_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << NavLightPWM_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - NavLightPWM_TRIG_LEVEL     - Level
*     - NavLightPWM_TRIG_RISING    - Rising edge
*     - NavLightPWM_TRIG_FALLING   - Falling edge
*     - NavLightPWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_TRIG_CONTROL1_REG &= (uint32)~NavLightPWM_COUNT_MASK;
    NavLightPWM_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << NavLightPWM_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_TriggerCommand
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
*     - NavLightPWM_CMD_CAPTURE    - Trigger Capture command
*     - NavLightPWM_CMD_RELOAD     - Trigger Reload command
*     - NavLightPWM_CMD_STOP       - Trigger Stop command
*     - NavLightPWM_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    NavLightPWM_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: NavLightPWM_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the NavLightPWM.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - NavLightPWM_STATUS_DOWN    - Set if counting down
*     - NavLightPWM_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 NavLightPWM_ReadStatus(void)
{
    return ((NavLightPWM_STATUS_REG >> NavLightPWM_RUNNING_STATUS_SHIFT) |
            (NavLightPWM_STATUS_REG & NavLightPWM_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: NavLightPWM_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - NavLightPWM_INTR_MASK_TC       - Terminal count mask
*     - NavLightPWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_SetInterruptMode(uint32 interruptMask)
{
    NavLightPWM_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: NavLightPWM_GetInterruptSourceMasked
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
*     - NavLightPWM_INTR_MASK_TC       - Terminal count mask
*     - NavLightPWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 NavLightPWM_GetInterruptSourceMasked(void)
{
    return (NavLightPWM_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: NavLightPWM_GetInterruptSource
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
*     - NavLightPWM_INTR_MASK_TC       - Terminal count mask
*     - NavLightPWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 NavLightPWM_GetInterruptSource(void)
{
    return (NavLightPWM_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: NavLightPWM_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - NavLightPWM_INTR_MASK_TC       - Terminal count mask
*     - NavLightPWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_ClearInterrupt(uint32 interruptMask)
{
    NavLightPWM_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: NavLightPWM_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - NavLightPWM_INTR_MASK_TC       - Terminal count mask
*     - NavLightPWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void NavLightPWM_SetInterrupt(uint32 interruptMask)
{
    NavLightPWM_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
