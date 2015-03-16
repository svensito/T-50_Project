/*******************************************************************************
* File Name: PPMCounter.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the PPMCounter
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

#include "PPMCounter.h"
#include "CyLib.h"

uint8 PPMCounter_initVar = 0u;


/*******************************************************************************
* Function Name: PPMCounter_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default PPMCounter configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (PPMCounter__QUAD == PPMCounter_CONFIG)
        PPMCounter_CONTROL_REG =
        (((uint32)(PPMCounter_QUAD_ENCODING_MODES     << PPMCounter_QUAD_MODE_SHIFT))       |
         ((uint32)(PPMCounter_CONFIG                  << PPMCounter_MODE_SHIFT)));
    #endif  /* (PPMCounter__QUAD == PPMCounter_CONFIG) */

    #if (PPMCounter__PWM_SEL == PPMCounter_CONFIG)
        PPMCounter_CONTROL_REG =
        (((uint32)(PPMCounter_PWM_STOP_EVENT          << PPMCounter_PWM_STOP_KILL_SHIFT))    |
         ((uint32)(PPMCounter_PWM_OUT_INVERT          << PPMCounter_INV_OUT_SHIFT))         |
         ((uint32)(PPMCounter_PWM_OUT_N_INVERT        << PPMCounter_INV_COMPL_OUT_SHIFT))     |
         ((uint32)(PPMCounter_PWM_MODE                << PPMCounter_MODE_SHIFT)));

        #if (PPMCounter__PWM_PR == PPMCounter_PWM_MODE)
            PPMCounter_CONTROL_REG |=
            ((uint32)(PPMCounter_PWM_RUN_MODE         << PPMCounter_ONESHOT_SHIFT));

            PPMCounter_WriteCounter(PPMCounter_PWM_PR_INIT_VALUE);
        #else
            PPMCounter_CONTROL_REG |=
            (((uint32)(PPMCounter_PWM_ALIGN           << PPMCounter_UPDOWN_SHIFT))          |
             ((uint32)(PPMCounter_PWM_KILL_EVENT      << PPMCounter_PWM_SYNC_KILL_SHIFT)));
        #endif  /* (PPMCounter__PWM_PR == PPMCounter_PWM_MODE) */

        #if (PPMCounter__PWM_DT == PPMCounter_PWM_MODE)
            PPMCounter_CONTROL_REG |=
            ((uint32)(PPMCounter_PWM_DEAD_TIME_CYCLE  << PPMCounter_PRESCALER_SHIFT));
        #endif  /* (PPMCounter__PWM_DT == PPMCounter_PWM_MODE) */

        #if (PPMCounter__PWM == PPMCounter_PWM_MODE)
            PPMCounter_CONTROL_REG |=
            ((uint32)PPMCounter_PWM_PRESCALER         << PPMCounter_PRESCALER_SHIFT);
        #endif  /* (PPMCounter__PWM == PPMCounter_PWM_MODE) */
    #endif  /* (PPMCounter__PWM_SEL == PPMCounter_CONFIG) */

    #if (PPMCounter__TIMER == PPMCounter_CONFIG)
        PPMCounter_CONTROL_REG =
        (((uint32)(PPMCounter_TC_PRESCALER            << PPMCounter_PRESCALER_SHIFT))   |
         ((uint32)(PPMCounter_TC_COUNTER_MODE         << PPMCounter_UPDOWN_SHIFT))      |
         ((uint32)(PPMCounter_TC_RUN_MODE             << PPMCounter_ONESHOT_SHIFT))     |
         ((uint32)(PPMCounter_TC_COMP_CAP_MODE        << PPMCounter_MODE_SHIFT)));
    #endif  /* (PPMCounter__TIMER == PPMCounter_CONFIG) */

    /* Set values from customizer to CTRL1 */
    #if (PPMCounter__QUAD == PPMCounter_CONFIG)
        PPMCounter_TRIG_CONTROL1_REG  =
        (((uint32)(PPMCounter_QUAD_PHIA_SIGNAL_MODE   << PPMCounter_COUNT_SHIFT))       |
         ((uint32)(PPMCounter_QUAD_INDEX_SIGNAL_MODE  << PPMCounter_RELOAD_SHIFT))      |
         ((uint32)(PPMCounter_QUAD_STOP_SIGNAL_MODE   << PPMCounter_STOP_SHIFT))        |
         ((uint32)(PPMCounter_QUAD_PHIB_SIGNAL_MODE   << PPMCounter_START_SHIFT)));
    #endif  /* (PPMCounter__QUAD == PPMCounter_CONFIG) */

    #if (PPMCounter__PWM_SEL == PPMCounter_CONFIG)
        PPMCounter_TRIG_CONTROL1_REG  =
        (((uint32)(PPMCounter_PWM_SWITCH_SIGNAL_MODE  << PPMCounter_CAPTURE_SHIFT))     |
         ((uint32)(PPMCounter_PWM_COUNT_SIGNAL_MODE   << PPMCounter_COUNT_SHIFT))       |
         ((uint32)(PPMCounter_PWM_RELOAD_SIGNAL_MODE  << PPMCounter_RELOAD_SHIFT))      |
         ((uint32)(PPMCounter_PWM_STOP_SIGNAL_MODE    << PPMCounter_STOP_SHIFT))        |
         ((uint32)(PPMCounter_PWM_START_SIGNAL_MODE   << PPMCounter_START_SHIFT)));
    #endif  /* (PPMCounter__PWM_SEL == PPMCounter_CONFIG) */

    #if (PPMCounter__TIMER == PPMCounter_CONFIG)
        PPMCounter_TRIG_CONTROL1_REG  =
        (((uint32)(PPMCounter_TC_CAPTURE_SIGNAL_MODE  << PPMCounter_CAPTURE_SHIFT))     |
         ((uint32)(PPMCounter_TC_COUNT_SIGNAL_MODE    << PPMCounter_COUNT_SHIFT))       |
         ((uint32)(PPMCounter_TC_RELOAD_SIGNAL_MODE   << PPMCounter_RELOAD_SHIFT))      |
         ((uint32)(PPMCounter_TC_STOP_SIGNAL_MODE     << PPMCounter_STOP_SHIFT))        |
         ((uint32)(PPMCounter_TC_START_SIGNAL_MODE    << PPMCounter_START_SHIFT)));
    #endif  /* (PPMCounter__TIMER == PPMCounter_CONFIG) */

    /* Set values from customizer to INTR */
    #if (PPMCounter__QUAD == PPMCounter_CONFIG)
        PPMCounter_SetInterruptMode(PPMCounter_QUAD_INTERRUPT_MASK);
    #endif  /* (PPMCounter__QUAD == PPMCounter_CONFIG) */

    #if (PPMCounter__PWM_SEL == PPMCounter_CONFIG)
        PPMCounter_SetInterruptMode(PPMCounter_PWM_INTERRUPT_MASK);
    #endif  /* (PPMCounter__PWM_SEL == PPMCounter_CONFIG) */

    #if (PPMCounter__TIMER == PPMCounter_CONFIG)
        PPMCounter_SetInterruptMode(PPMCounter_TC_INTERRUPT_MASK);
    #endif  /* (PPMCounter__TIMER == PPMCounter_CONFIG) */

    /* Set other values from customizer */
    #if (PPMCounter__TIMER == PPMCounter_CONFIG)
        PPMCounter_WritePeriod(PPMCounter_TC_PERIOD_VALUE );

        #if (PPMCounter__COUNT_DOWN == PPMCounter_TC_COUNTER_MODE)
            PPMCounter_WriteCounter(PPMCounter_TC_PERIOD_VALUE );
        #endif  /* (PPMCounter__COUNT_DOWN == PPMCounter_TC_COUNTER_MODE) */

        #if (PPMCounter__COMPARE == PPMCounter_TC_COMP_CAP_MODE)
            PPMCounter_WriteCompare(PPMCounter_TC_COMPARE_VALUE);

            #if (1u == PPMCounter_TC_COMPARE_SWAP)
                PPMCounter_SetCompareSwap(1u);
                PPMCounter_WriteCompareBuf(PPMCounter_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == PPMCounter_TC_COMPARE_SWAP) */
        #endif  /* (PPMCounter__COMPARE == PPMCounter_TC_COMP_CAP_MODE) */
    #endif  /* (PPMCounter__TIMER == PPMCounter_CONFIG) */

    #if (PPMCounter__PWM_SEL == PPMCounter_CONFIG)
        PPMCounter_WritePeriod(PPMCounter_PWM_PERIOD_VALUE );
        PPMCounter_WriteCompare(PPMCounter_PWM_COMPARE_VALUE);

        #if (1u == PPMCounter_PWM_COMPARE_SWAP)
            PPMCounter_SetCompareSwap(1u);
            PPMCounter_WriteCompareBuf(PPMCounter_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == PPMCounter_PWM_COMPARE_SWAP) */

        #if (1u == PPMCounter_PWM_PERIOD_SWAP)
            PPMCounter_SetPeriodSwap(1u);
            PPMCounter_WritePeriodBuf(PPMCounter_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == PPMCounter_PWM_PERIOD_SWAP) */

        /* Set values from customizer to CTRL2 */
        #if (PPMCounter__PWM_PR == PPMCounter_PWM_MODE)
            PPMCounter_TRIG_CONTROL2_REG =
                    (PPMCounter_CC_MATCH_NO_CHANGE    |
                    PPMCounter_OVERLOW_NO_CHANGE      |
                    PPMCounter_UNDERFLOW_NO_CHANGE);
        #else
            #if (PPMCounter__LEFT == PPMCounter_PWM_ALIGN)
                PPMCounter_TRIG_CONTROL2_REG = PPMCounter_PWM_MODE_LEFT;
            #endif  /* ( PPMCounter_PWM_LEFT == PPMCounter_PWM_ALIGN) */

            #if (PPMCounter__RIGHT == PPMCounter_PWM_ALIGN)
                PPMCounter_WriteCounter(PPMCounter_PWM_PERIOD_VALUE);
                PPMCounter_TRIG_CONTROL2_REG = PPMCounter_PWM_MODE_RIGHT;
            #endif  /* ( PPMCounter_PWM_RIGHT == PPMCounter_PWM_ALIGN) */

            #if (PPMCounter__CENTER == PPMCounter_PWM_ALIGN)
                PPMCounter_TRIG_CONTROL2_REG = PPMCounter_PWM_MODE_CENTER;
            #endif  /* ( PPMCounter_PWM_CENTER == PPMCounter_PWM_ALIGN) */

            #if (PPMCounter__ASYMMETRIC == PPMCounter_PWM_ALIGN)
                PPMCounter_TRIG_CONTROL2_REG = PPMCounter_PWM_MODE_ASYM;
            #endif  /* (PPMCounter__ASYMMETRIC == PPMCounter_PWM_ALIGN) */
        #endif  /* (PPMCounter__PWM_PR == PPMCounter_PWM_MODE) */
    #endif  /* (PPMCounter__PWM_SEL == PPMCounter_CONFIG) */
}


/*******************************************************************************
* Function Name: PPMCounter_Enable
********************************************************************************
*
* Summary:
*  Enables the PPMCounter.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    PPMCounter_BLOCK_CONTROL_REG |= PPMCounter_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (PPMCounter__PWM_SEL == PPMCounter_CONFIG)
        #if (0u == PPMCounter_PWM_START_SIGNAL_PRESENT)
            PPMCounter_TriggerCommand(PPMCounter_MASK, PPMCounter_CMD_START);
        #endif /* (0u == PPMCounter_PWM_START_SIGNAL_PRESENT) */
    #endif /* (PPMCounter__PWM_SEL == PPMCounter_CONFIG) */

    #if (PPMCounter__TIMER == PPMCounter_CONFIG)
        #if (0u == PPMCounter_TC_START_SIGNAL_PRESENT)
            PPMCounter_TriggerCommand(PPMCounter_MASK, PPMCounter_CMD_START);
        #endif /* (0u == PPMCounter_TC_START_SIGNAL_PRESENT) */
    #endif /* (PPMCounter__TIMER == PPMCounter_CONFIG) */
}


/*******************************************************************************
* Function Name: PPMCounter_Start
********************************************************************************
*
* Summary:
*  Initializes the PPMCounter with default customizer
*  values when called the first time and enables the PPMCounter.
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
*  PPMCounter_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time PPMCounter_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the PPMCounter_Start() routine.
*
*******************************************************************************/
void PPMCounter_Start(void)
{
    if (0u == PPMCounter_initVar)
    {
        PPMCounter_Init();
        PPMCounter_initVar = 1u;
    }

    PPMCounter_Enable();
}


/*******************************************************************************
* Function Name: PPMCounter_Stop
********************************************************************************
*
* Summary:
*  Disables the PPMCounter.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_BLOCK_CONTROL_REG &= (uint32)~PPMCounter_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the PPMCounter. This function is used when
*  configured as a generic PPMCounter and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the PPMCounter to operate in
*   Values:
*   - PPMCounter_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - PPMCounter_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - PPMCounter_MODE_QUAD - Quadrature decoder
*         - PPMCounter_MODE_PWM - PWM
*         - PPMCounter_MODE_PWM_DT - PWM with dead time
*         - PPMCounter_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_CONTROL_REG &= (uint32)~PPMCounter_MODE_MASK;
    PPMCounter_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - PPMCounter_MODE_X1 - Counts on phi 1 rising
*         - PPMCounter_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - PPMCounter_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_CONTROL_REG &= (uint32)~PPMCounter_QUAD_MODE_MASK;
    PPMCounter_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - PPMCounter_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - PPMCounter_PRESCALE_DIVBY2    - Divide by 2
*         - PPMCounter_PRESCALE_DIVBY4    - Divide by 4
*         - PPMCounter_PRESCALE_DIVBY8    - Divide by 8
*         - PPMCounter_PRESCALE_DIVBY16   - Divide by 16
*         - PPMCounter_PRESCALE_DIVBY32   - Divide by 32
*         - PPMCounter_PRESCALE_DIVBY64   - Divide by 64
*         - PPMCounter_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_CONTROL_REG &= (uint32)~PPMCounter_PRESCALER_MASK;
    PPMCounter_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PPMCounter runs
*  continuously or stops when terminal count is reached.  By default the
*  PPMCounter operates in the continuous mode.
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
void PPMCounter_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_CONTROL_REG &= (uint32)~PPMCounter_ONESHOT_MASK;
    PPMCounter_CONTROL_REG |= ((uint32)((oneShotEnable & PPMCounter_1BIT_MASK) <<
                                                               PPMCounter_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_SetPWMMode
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
void PPMCounter_SetPWMMode(uint32 modeMask)
{
    PPMCounter_TRIG_CONTROL2_REG = (modeMask & PPMCounter_6BIT_MASK);
}



/*******************************************************************************
* Function Name: PPMCounter_SetPWMSyncKill
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
void PPMCounter_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_CONTROL_REG &= (uint32)~PPMCounter_PWM_SYNC_KILL_MASK;
    PPMCounter_CONTROL_REG |= ((uint32)((syncKillEnable & PPMCounter_1BIT_MASK)  <<
                                               PPMCounter_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_SetPWMStopOnKill
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
void PPMCounter_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_CONTROL_REG &= (uint32)~PPMCounter_PWM_STOP_KILL_MASK;
    PPMCounter_CONTROL_REG |= ((uint32)((stopOnKillEnable & PPMCounter_1BIT_MASK)  <<
                                                         PPMCounter_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_SetPWMDeadTime
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
void PPMCounter_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_CONTROL_REG &= (uint32)~PPMCounter_PRESCALER_MASK;
    PPMCounter_CONTROL_REG |= ((uint32)((deadTime & PPMCounter_8BIT_MASK) <<
                                                          PPMCounter_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_SetPWMInvert
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
*         - PPMCounter_INVERT_LINE   - Inverts the line output
*         - PPMCounter_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_CONTROL_REG &= (uint32)~PPMCounter_INV_OUT_MASK;
    PPMCounter_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: PPMCounter_WriteCounter
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
void PPMCounter_WriteCounter(uint32 count)
{
    PPMCounter_COUNTER_REG = (count & PPMCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PPMCounter_ReadCounter
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
uint32 PPMCounter_ReadCounter(void)
{
    return (PPMCounter_COUNTER_REG & PPMCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PPMCounter_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - PPMCounter_COUNT_UP       - Counts up
*     - PPMCounter_COUNT_DOWN     - Counts down
*     - PPMCounter_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - PPMCounter_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_CONTROL_REG &= (uint32)~PPMCounter_UPDOWN_MASK;
    PPMCounter_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_WritePeriod
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
void PPMCounter_WritePeriod(uint32 period)
{
    PPMCounter_PERIOD_REG = (period & PPMCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PPMCounter_ReadPeriod
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
uint32 PPMCounter_ReadPeriod(void)
{
    return (PPMCounter_PERIOD_REG & PPMCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PPMCounter_SetCompareSwap
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
void PPMCounter_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_CONTROL_REG &= (uint32)~PPMCounter_RELOAD_CC_MASK;
    PPMCounter_CONTROL_REG |= (swapEnable & PPMCounter_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_WritePeriodBuf
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
void PPMCounter_WritePeriodBuf(uint32 periodBuf)
{
    PPMCounter_PERIOD_BUF_REG = (periodBuf & PPMCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PPMCounter_ReadPeriodBuf
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
uint32 PPMCounter_ReadPeriodBuf(void)
{
    return (PPMCounter_PERIOD_BUF_REG & PPMCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PPMCounter_SetPeriodSwap
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
void PPMCounter_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_CONTROL_REG &= (uint32)~PPMCounter_RELOAD_PERIOD_MASK;
    PPMCounter_CONTROL_REG |= ((uint32)((swapEnable & PPMCounter_1BIT_MASK) <<
                                                            PPMCounter_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_WriteCompare
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
void PPMCounter_WriteCompare(uint32 compare)
{
    #if (PPMCounter_CY_TCPWM_V2)
        uint32 currentMode;
    #endif /* (PPMCounter_CY_TCPWM_V2) */

    #if (PPMCounter_CY_TCPWM_V2)
        currentMode = ((PPMCounter_CONTROL_REG & PPMCounter_UPDOWN_MASK) >> PPMCounter_UPDOWN_SHIFT);

        if (PPMCounter__COUNT_DOWN == currentMode)
        {
            PPMCounter_COMP_CAP_REG = ((compare + 1u) & PPMCounter_16BIT_MASK);
        }
        else if (PPMCounter__COUNT_UP == currentMode)
        {
            PPMCounter_COMP_CAP_REG = ((compare - 1u) & PPMCounter_16BIT_MASK);
        }
        else
        {
            PPMCounter_COMP_CAP_REG = (compare & PPMCounter_16BIT_MASK);
        }
    #else
        PPMCounter_COMP_CAP_REG = (compare & PPMCounter_16BIT_MASK);
    #endif /* (PPMCounter_CY_TCPWM_V2) */
}


/*******************************************************************************
* Function Name: PPMCounter_ReadCompare
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
uint32 PPMCounter_ReadCompare(void)
{
    #if (PPMCounter_CY_TCPWM_V2)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (PPMCounter_CY_TCPWM_V2) */

    #if (PPMCounter_CY_TCPWM_V2)
        currentMode = ((PPMCounter_CONTROL_REG & PPMCounter_UPDOWN_MASK) >> PPMCounter_UPDOWN_SHIFT);

        if (PPMCounter__COUNT_DOWN == currentMode)
        {
            regVal = ((PPMCounter_COMP_CAP_REG - 1u) & PPMCounter_16BIT_MASK);
        }
        else if (PPMCounter__COUNT_UP == currentMode)
        {
            regVal = ((PPMCounter_COMP_CAP_REG + 1u) & PPMCounter_16BIT_MASK);
        }
        else
        {
            regVal = (PPMCounter_COMP_CAP_REG & PPMCounter_16BIT_MASK);
        }
        return (regVal);
    #else
        return (PPMCounter_COMP_CAP_REG & PPMCounter_16BIT_MASK);
    #endif /* (PPMCounter_CY_TCPWM_V2) */
}


/*******************************************************************************
* Function Name: PPMCounter_WriteCompareBuf
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
void PPMCounter_WriteCompareBuf(uint32 compareBuf)
{
    #if (PPMCounter_CY_TCPWM_V2)
        uint32 currentMode;
    #endif /* (PPMCounter_CY_TCPWM_V2) */

    #if (PPMCounter_CY_TCPWM_V2)
        currentMode = ((PPMCounter_CONTROL_REG & PPMCounter_UPDOWN_MASK) >> PPMCounter_UPDOWN_SHIFT);

        if (PPMCounter__COUNT_DOWN == currentMode)
        {
            PPMCounter_COMP_CAP_BUF_REG = ((compareBuf + 1u) & PPMCounter_16BIT_MASK);
        }
        else if (PPMCounter__COUNT_UP == currentMode)
        {
            PPMCounter_COMP_CAP_BUF_REG = ((compareBuf - 1u) & PPMCounter_16BIT_MASK);
        }
        else
        {
            PPMCounter_COMP_CAP_BUF_REG = (compareBuf & PPMCounter_16BIT_MASK);
        }
    #else
        PPMCounter_COMP_CAP_BUF_REG = (compareBuf & PPMCounter_16BIT_MASK);
    #endif /* (PPMCounter_CY_TCPWM_V2) */
}


/*******************************************************************************
* Function Name: PPMCounter_ReadCompareBuf
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
uint32 PPMCounter_ReadCompareBuf(void)
{
    #if (PPMCounter_CY_TCPWM_V2)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (PPMCounter_CY_TCPWM_V2) */

    #if (PPMCounter_CY_TCPWM_V2)
        currentMode = ((PPMCounter_CONTROL_REG & PPMCounter_UPDOWN_MASK) >> PPMCounter_UPDOWN_SHIFT);

        if (PPMCounter__COUNT_DOWN == currentMode)
        {
            regVal = ((PPMCounter_COMP_CAP_BUF_REG - 1u) & PPMCounter_16BIT_MASK);
        }
        else if (PPMCounter__COUNT_UP == currentMode)
        {
            regVal = ((PPMCounter_COMP_CAP_BUF_REG + 1u) & PPMCounter_16BIT_MASK);
        }
        else
        {
            regVal = (PPMCounter_COMP_CAP_BUF_REG & PPMCounter_16BIT_MASK);
        }
        return (regVal);
    #else
        return (PPMCounter_COMP_CAP_BUF_REG & PPMCounter_16BIT_MASK);
    #endif /* (PPMCounter_CY_TCPWM_V2) */
}


/*******************************************************************************
* Function Name: PPMCounter_ReadCapture
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
uint32 PPMCounter_ReadCapture(void)
{
    return (PPMCounter_COMP_CAP_REG & PPMCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PPMCounter_ReadCaptureBuf
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
uint32 PPMCounter_ReadCaptureBuf(void)
{
    return (PPMCounter_COMP_CAP_BUF_REG & PPMCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PPMCounter_SetCaptureMode
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
*     - PPMCounter_TRIG_LEVEL     - Level
*     - PPMCounter_TRIG_RISING    - Rising edge
*     - PPMCounter_TRIG_FALLING   - Falling edge
*     - PPMCounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_TRIG_CONTROL1_REG &= (uint32)~PPMCounter_CAPTURE_MASK;
    PPMCounter_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PPMCounter_TRIG_LEVEL     - Level
*     - PPMCounter_TRIG_RISING    - Rising edge
*     - PPMCounter_TRIG_FALLING   - Falling edge
*     - PPMCounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_TRIG_CONTROL1_REG &= (uint32)~PPMCounter_RELOAD_MASK;
    PPMCounter_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PPMCounter_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PPMCounter_TRIG_LEVEL     - Level
*     - PPMCounter_TRIG_RISING    - Rising edge
*     - PPMCounter_TRIG_FALLING   - Falling edge
*     - PPMCounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_TRIG_CONTROL1_REG &= (uint32)~PPMCounter_START_MASK;
    PPMCounter_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PPMCounter_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PPMCounter_TRIG_LEVEL     - Level
*     - PPMCounter_TRIG_RISING    - Rising edge
*     - PPMCounter_TRIG_FALLING   - Falling edge
*     - PPMCounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_TRIG_CONTROL1_REG &= (uint32)~PPMCounter_STOP_MASK;
    PPMCounter_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PPMCounter_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PPMCounter_TRIG_LEVEL     - Level
*     - PPMCounter_TRIG_RISING    - Rising edge
*     - PPMCounter_TRIG_FALLING   - Falling edge
*     - PPMCounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_TRIG_CONTROL1_REG &= (uint32)~PPMCounter_COUNT_MASK;
    PPMCounter_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PPMCounter_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_TriggerCommand
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
*     - PPMCounter_CMD_CAPTURE    - Trigger Capture command
*     - PPMCounter_CMD_RELOAD     - Trigger Reload command
*     - PPMCounter_CMD_STOP       - Trigger Stop command
*     - PPMCounter_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PPMCounter_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PPMCounter_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the PPMCounter.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - PPMCounter_STATUS_DOWN    - Set if counting down
*     - PPMCounter_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 PPMCounter_ReadStatus(void)
{
    return ((PPMCounter_STATUS_REG >> PPMCounter_RUNNING_STATUS_SHIFT) |
            (PPMCounter_STATUS_REG & PPMCounter_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: PPMCounter_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - PPMCounter_INTR_MASK_TC       - Terminal count mask
*     - PPMCounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_SetInterruptMode(uint32 interruptMask)
{
    PPMCounter_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: PPMCounter_GetInterruptSourceMasked
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
*     - PPMCounter_INTR_MASK_TC       - Terminal count mask
*     - PPMCounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 PPMCounter_GetInterruptSourceMasked(void)
{
    return (PPMCounter_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: PPMCounter_GetInterruptSource
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
*     - PPMCounter_INTR_MASK_TC       - Terminal count mask
*     - PPMCounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 PPMCounter_GetInterruptSource(void)
{
    return (PPMCounter_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: PPMCounter_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - PPMCounter_INTR_MASK_TC       - Terminal count mask
*     - PPMCounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_ClearInterrupt(uint32 interruptMask)
{
    PPMCounter_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: PPMCounter_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - PPMCounter_INTR_MASK_TC       - Terminal count mask
*     - PPMCounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PPMCounter_SetInterrupt(uint32 interruptMask)
{
    PPMCounter_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
