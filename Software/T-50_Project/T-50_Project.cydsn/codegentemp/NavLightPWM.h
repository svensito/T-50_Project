/*******************************************************************************
* File Name: NavLightPWM.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the NavLightPWM
*  component.
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

#if !defined(CY_TCPWM_NavLightPWM_H)
#define CY_TCPWM_NavLightPWM_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} NavLightPWM_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  NavLightPWM_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define NavLightPWM_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define NavLightPWM_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define NavLightPWM_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define NavLightPWM_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define NavLightPWM_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define NavLightPWM_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define NavLightPWM_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define NavLightPWM_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define NavLightPWM_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define NavLightPWM_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define NavLightPWM_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define NavLightPWM_TC_RUN_MODE                    (0lu)
#define NavLightPWM_TC_COUNTER_MODE                (0lu)
#define NavLightPWM_TC_COMP_CAP_MODE               (2lu)
#define NavLightPWM_TC_PRESCALER                   (0lu)

/* Signal modes */
#define NavLightPWM_TC_RELOAD_SIGNAL_MODE          (0lu)
#define NavLightPWM_TC_COUNT_SIGNAL_MODE           (3lu)
#define NavLightPWM_TC_START_SIGNAL_MODE           (0lu)
#define NavLightPWM_TC_STOP_SIGNAL_MODE            (0lu)
#define NavLightPWM_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define NavLightPWM_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define NavLightPWM_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define NavLightPWM_TC_START_SIGNAL_PRESENT        (0lu)
#define NavLightPWM_TC_STOP_SIGNAL_PRESENT         (0lu)
#define NavLightPWM_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define NavLightPWM_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define NavLightPWM_PWM_KILL_EVENT                 (0lu)
#define NavLightPWM_PWM_STOP_EVENT                 (0lu)
#define NavLightPWM_PWM_MODE                       (4lu)
#define NavLightPWM_PWM_OUT_N_INVERT               (0lu)
#define NavLightPWM_PWM_OUT_INVERT                 (0lu)
#define NavLightPWM_PWM_ALIGN                      (0lu)
#define NavLightPWM_PWM_RUN_MODE                   (0lu)
#define NavLightPWM_PWM_DEAD_TIME_CYCLE            (0lu)
#define NavLightPWM_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define NavLightPWM_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define NavLightPWM_PWM_COUNT_SIGNAL_MODE          (3lu)
#define NavLightPWM_PWM_START_SIGNAL_MODE          (0lu)
#define NavLightPWM_PWM_STOP_SIGNAL_MODE           (0lu)
#define NavLightPWM_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define NavLightPWM_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define NavLightPWM_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define NavLightPWM_PWM_START_SIGNAL_PRESENT       (0lu)
#define NavLightPWM_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define NavLightPWM_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define NavLightPWM_PWM_INTERRUPT_MASK             (0lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define NavLightPWM_TC_PERIOD_VALUE                (65535lu)
#define NavLightPWM_TC_COMPARE_VALUE               (65535lu)
#define NavLightPWM_TC_COMPARE_BUF_VALUE           (65535lu)
#define NavLightPWM_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define NavLightPWM_PWM_PERIOD_VALUE               (100lu)
#define NavLightPWM_PWM_PERIOD_BUF_VALUE           (65535lu)
#define NavLightPWM_PWM_PERIOD_SWAP                (0lu)
#define NavLightPWM_PWM_COMPARE_VALUE              (50lu)
#define NavLightPWM_PWM_COMPARE_BUF_VALUE          (65535lu)
#define NavLightPWM_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define NavLightPWM__LEFT 0
#define NavLightPWM__RIGHT 1
#define NavLightPWM__CENTER 2
#define NavLightPWM__ASYMMETRIC 3

#define NavLightPWM__X1 0
#define NavLightPWM__X2 1
#define NavLightPWM__X4 2

#define NavLightPWM__PWM 4
#define NavLightPWM__PWM_DT 5
#define NavLightPWM__PWM_PR 6

#define NavLightPWM__INVERSE 1
#define NavLightPWM__DIRECT 0

#define NavLightPWM__CAPTURE 2
#define NavLightPWM__COMPARE 0

#define NavLightPWM__TRIG_LEVEL 3
#define NavLightPWM__TRIG_RISING 0
#define NavLightPWM__TRIG_FALLING 1
#define NavLightPWM__TRIG_BOTH 2

#define NavLightPWM__INTR_MASK_TC 1
#define NavLightPWM__INTR_MASK_CC_MATCH 2
#define NavLightPWM__INTR_MASK_NONE 0
#define NavLightPWM__INTR_MASK_TC_CC 3

#define NavLightPWM__UNCONFIG 8
#define NavLightPWM__TIMER 1
#define NavLightPWM__QUAD 3
#define NavLightPWM__PWM_SEL 7

#define NavLightPWM__COUNT_UP 0
#define NavLightPWM__COUNT_DOWN 1
#define NavLightPWM__COUNT_UPDOWN0 2
#define NavLightPWM__COUNT_UPDOWN1 3


/* Prescaler */
#define NavLightPWM_PRESCALE_DIVBY1                ((uint32)(0u << NavLightPWM_PRESCALER_SHIFT))
#define NavLightPWM_PRESCALE_DIVBY2                ((uint32)(1u << NavLightPWM_PRESCALER_SHIFT))
#define NavLightPWM_PRESCALE_DIVBY4                ((uint32)(2u << NavLightPWM_PRESCALER_SHIFT))
#define NavLightPWM_PRESCALE_DIVBY8                ((uint32)(3u << NavLightPWM_PRESCALER_SHIFT))
#define NavLightPWM_PRESCALE_DIVBY16               ((uint32)(4u << NavLightPWM_PRESCALER_SHIFT))
#define NavLightPWM_PRESCALE_DIVBY32               ((uint32)(5u << NavLightPWM_PRESCALER_SHIFT))
#define NavLightPWM_PRESCALE_DIVBY64               ((uint32)(6u << NavLightPWM_PRESCALER_SHIFT))
#define NavLightPWM_PRESCALE_DIVBY128              ((uint32)(7u << NavLightPWM_PRESCALER_SHIFT))

/* TCPWM set modes */
#define NavLightPWM_MODE_TIMER_COMPARE             ((uint32)(NavLightPWM__COMPARE         <<  \
                                                                  NavLightPWM_MODE_SHIFT))
#define NavLightPWM_MODE_TIMER_CAPTURE             ((uint32)(NavLightPWM__CAPTURE         <<  \
                                                                  NavLightPWM_MODE_SHIFT))
#define NavLightPWM_MODE_QUAD                      ((uint32)(NavLightPWM__QUAD            <<  \
                                                                  NavLightPWM_MODE_SHIFT))
#define NavLightPWM_MODE_PWM                       ((uint32)(NavLightPWM__PWM             <<  \
                                                                  NavLightPWM_MODE_SHIFT))
#define NavLightPWM_MODE_PWM_DT                    ((uint32)(NavLightPWM__PWM_DT          <<  \
                                                                  NavLightPWM_MODE_SHIFT))
#define NavLightPWM_MODE_PWM_PR                    ((uint32)(NavLightPWM__PWM_PR          <<  \
                                                                  NavLightPWM_MODE_SHIFT))

/* Quad Modes */
#define NavLightPWM_MODE_X1                        ((uint32)(NavLightPWM__X1              <<  \
                                                                  NavLightPWM_QUAD_MODE_SHIFT))
#define NavLightPWM_MODE_X2                        ((uint32)(NavLightPWM__X2              <<  \
                                                                  NavLightPWM_QUAD_MODE_SHIFT))
#define NavLightPWM_MODE_X4                        ((uint32)(NavLightPWM__X4              <<  \
                                                                  NavLightPWM_QUAD_MODE_SHIFT))

/* Counter modes */
#define NavLightPWM_COUNT_UP                       ((uint32)(NavLightPWM__COUNT_UP        <<  \
                                                                  NavLightPWM_UPDOWN_SHIFT))
#define NavLightPWM_COUNT_DOWN                     ((uint32)(NavLightPWM__COUNT_DOWN      <<  \
                                                                  NavLightPWM_UPDOWN_SHIFT))
#define NavLightPWM_COUNT_UPDOWN0                  ((uint32)(NavLightPWM__COUNT_UPDOWN0   <<  \
                                                                  NavLightPWM_UPDOWN_SHIFT))
#define NavLightPWM_COUNT_UPDOWN1                  ((uint32)(NavLightPWM__COUNT_UPDOWN1   <<  \
                                                                  NavLightPWM_UPDOWN_SHIFT))

/* PWM output invert */
#define NavLightPWM_INVERT_LINE                    ((uint32)(NavLightPWM__INVERSE         <<  \
                                                                  NavLightPWM_INV_OUT_SHIFT))
#define NavLightPWM_INVERT_LINE_N                  ((uint32)(NavLightPWM__INVERSE         <<  \
                                                                  NavLightPWM_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define NavLightPWM_TRIG_RISING                    ((uint32)NavLightPWM__TRIG_RISING)
#define NavLightPWM_TRIG_FALLING                   ((uint32)NavLightPWM__TRIG_FALLING)
#define NavLightPWM_TRIG_BOTH                      ((uint32)NavLightPWM__TRIG_BOTH)
#define NavLightPWM_TRIG_LEVEL                     ((uint32)NavLightPWM__TRIG_LEVEL)

/* Interrupt mask */
#define NavLightPWM_INTR_MASK_TC                   ((uint32)NavLightPWM__INTR_MASK_TC)
#define NavLightPWM_INTR_MASK_CC_MATCH             ((uint32)NavLightPWM__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define NavLightPWM_CC_MATCH_SET                   (0x00u)
#define NavLightPWM_CC_MATCH_CLEAR                 (0x01u)
#define NavLightPWM_CC_MATCH_INVERT                (0x02u)
#define NavLightPWM_CC_MATCH_NO_CHANGE             (0x03u)
#define NavLightPWM_OVERLOW_SET                    (0x00u)
#define NavLightPWM_OVERLOW_CLEAR                  (0x04u)
#define NavLightPWM_OVERLOW_INVERT                 (0x08u)
#define NavLightPWM_OVERLOW_NO_CHANGE              (0x0Cu)
#define NavLightPWM_UNDERFLOW_SET                  (0x00u)
#define NavLightPWM_UNDERFLOW_CLEAR                (0x10u)
#define NavLightPWM_UNDERFLOW_INVERT               (0x20u)
#define NavLightPWM_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define NavLightPWM_PWM_MODE_LEFT                  (NavLightPWM_CC_MATCH_CLEAR        |   \
                                                         NavLightPWM_OVERLOW_SET           |   \
                                                         NavLightPWM_UNDERFLOW_NO_CHANGE)
#define NavLightPWM_PWM_MODE_RIGHT                 (NavLightPWM_CC_MATCH_SET          |   \
                                                         NavLightPWM_OVERLOW_NO_CHANGE     |   \
                                                         NavLightPWM_UNDERFLOW_CLEAR)
#define NavLightPWM_PWM_MODE_ASYM                  (NavLightPWM_CC_MATCH_INVERT       |   \
                                                         NavLightPWM_OVERLOW_SET           |   \
                                                         NavLightPWM_UNDERFLOW_CLEAR)

#if (NavLightPWM_CY_TCPWM_V2)
    #if(NavLightPWM_CY_TCPWM_4000)
        #define NavLightPWM_PWM_MODE_CENTER                (NavLightPWM_CC_MATCH_INVERT       |   \
                                                                 NavLightPWM_OVERLOW_NO_CHANGE     |   \
                                                                 NavLightPWM_UNDERFLOW_CLEAR)
    #else
        #define NavLightPWM_PWM_MODE_CENTER                (NavLightPWM_CC_MATCH_INVERT       |   \
                                                                 NavLightPWM_OVERLOW_SET           |   \
                                                                 NavLightPWM_UNDERFLOW_CLEAR)
    #endif /* (NavLightPWM_CY_TCPWM_4000) */
#else
    #define NavLightPWM_PWM_MODE_CENTER                (NavLightPWM_CC_MATCH_INVERT       |   \
                                                             NavLightPWM_OVERLOW_NO_CHANGE     |   \
                                                             NavLightPWM_UNDERFLOW_CLEAR)
#endif /* (NavLightPWM_CY_TCPWM_NEW) */

/* Command operations without condition */
#define NavLightPWM_CMD_CAPTURE                    (0u)
#define NavLightPWM_CMD_RELOAD                     (8u)
#define NavLightPWM_CMD_STOP                       (16u)
#define NavLightPWM_CMD_START                      (24u)

/* Status */
#define NavLightPWM_STATUS_DOWN                    (1u)
#define NavLightPWM_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   NavLightPWM_Init(void);
void   NavLightPWM_Enable(void);
void   NavLightPWM_Start(void);
void   NavLightPWM_Stop(void);

void   NavLightPWM_SetMode(uint32 mode);
void   NavLightPWM_SetCounterMode(uint32 counterMode);
void   NavLightPWM_SetPWMMode(uint32 modeMask);
void   NavLightPWM_SetQDMode(uint32 qdMode);

void   NavLightPWM_SetPrescaler(uint32 prescaler);
void   NavLightPWM_TriggerCommand(uint32 mask, uint32 command);
void   NavLightPWM_SetOneShot(uint32 oneShotEnable);
uint32 NavLightPWM_ReadStatus(void);

void   NavLightPWM_SetPWMSyncKill(uint32 syncKillEnable);
void   NavLightPWM_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   NavLightPWM_SetPWMDeadTime(uint32 deadTime);
void   NavLightPWM_SetPWMInvert(uint32 mask);

void   NavLightPWM_SetInterruptMode(uint32 interruptMask);
uint32 NavLightPWM_GetInterruptSourceMasked(void);
uint32 NavLightPWM_GetInterruptSource(void);
void   NavLightPWM_ClearInterrupt(uint32 interruptMask);
void   NavLightPWM_SetInterrupt(uint32 interruptMask);

void   NavLightPWM_WriteCounter(uint32 count);
uint32 NavLightPWM_ReadCounter(void);

uint32 NavLightPWM_ReadCapture(void);
uint32 NavLightPWM_ReadCaptureBuf(void);

void   NavLightPWM_WritePeriod(uint32 period);
uint32 NavLightPWM_ReadPeriod(void);
void   NavLightPWM_WritePeriodBuf(uint32 periodBuf);
uint32 NavLightPWM_ReadPeriodBuf(void);

void   NavLightPWM_WriteCompare(uint32 compare);
uint32 NavLightPWM_ReadCompare(void);
void   NavLightPWM_WriteCompareBuf(uint32 compareBuf);
uint32 NavLightPWM_ReadCompareBuf(void);

void   NavLightPWM_SetPeriodSwap(uint32 swapEnable);
void   NavLightPWM_SetCompareSwap(uint32 swapEnable);

void   NavLightPWM_SetCaptureMode(uint32 triggerMode);
void   NavLightPWM_SetReloadMode(uint32 triggerMode);
void   NavLightPWM_SetStartMode(uint32 triggerMode);
void   NavLightPWM_SetStopMode(uint32 triggerMode);
void   NavLightPWM_SetCountMode(uint32 triggerMode);

void   NavLightPWM_SaveConfig(void);
void   NavLightPWM_RestoreConfig(void);
void   NavLightPWM_Sleep(void);
void   NavLightPWM_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define NavLightPWM_BLOCK_CONTROL_REG              (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define NavLightPWM_BLOCK_CONTROL_PTR              ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define NavLightPWM_COMMAND_REG                    (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define NavLightPWM_COMMAND_PTR                    ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define NavLightPWM_INTRRUPT_CAUSE_REG             (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define NavLightPWM_INTRRUPT_CAUSE_PTR             ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define NavLightPWM_CONTROL_REG                    (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__CTRL )
#define NavLightPWM_CONTROL_PTR                    ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__CTRL )
#define NavLightPWM_STATUS_REG                     (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__STATUS )
#define NavLightPWM_STATUS_PTR                     ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__STATUS )
#define NavLightPWM_COUNTER_REG                    (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__COUNTER )
#define NavLightPWM_COUNTER_PTR                    ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__COUNTER )
#define NavLightPWM_COMP_CAP_REG                   (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__CC )
#define NavLightPWM_COMP_CAP_PTR                   ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__CC )
#define NavLightPWM_COMP_CAP_BUF_REG               (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__CC_BUFF )
#define NavLightPWM_COMP_CAP_BUF_PTR               ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__CC_BUFF )
#define NavLightPWM_PERIOD_REG                     (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__PERIOD )
#define NavLightPWM_PERIOD_PTR                     ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__PERIOD )
#define NavLightPWM_PERIOD_BUF_REG                 (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define NavLightPWM_PERIOD_BUF_PTR                 ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define NavLightPWM_TRIG_CONTROL0_REG              (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define NavLightPWM_TRIG_CONTROL0_PTR              ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define NavLightPWM_TRIG_CONTROL1_REG              (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define NavLightPWM_TRIG_CONTROL1_PTR              ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define NavLightPWM_TRIG_CONTROL2_REG              (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define NavLightPWM_TRIG_CONTROL2_PTR              ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define NavLightPWM_INTERRUPT_REQ_REG              (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__INTR )
#define NavLightPWM_INTERRUPT_REQ_PTR              ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__INTR )
#define NavLightPWM_INTERRUPT_SET_REG              (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__INTR_SET )
#define NavLightPWM_INTERRUPT_SET_PTR              ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__INTR_SET )
#define NavLightPWM_INTERRUPT_MASK_REG             (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__INTR_MASK )
#define NavLightPWM_INTERRUPT_MASK_PTR             ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__INTR_MASK )
#define NavLightPWM_INTERRUPT_MASKED_REG           (*(reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__INTR_MASKED )
#define NavLightPWM_INTERRUPT_MASKED_PTR           ( (reg32 *) NavLightPWM_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define NavLightPWM_MASK                           ((uint32)NavLightPWM_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define NavLightPWM_RELOAD_CC_SHIFT                (0u)
#define NavLightPWM_RELOAD_PERIOD_SHIFT            (1u)
#define NavLightPWM_PWM_SYNC_KILL_SHIFT            (2u)
#define NavLightPWM_PWM_STOP_KILL_SHIFT            (3u)
#define NavLightPWM_PRESCALER_SHIFT                (8u)
#define NavLightPWM_UPDOWN_SHIFT                   (16u)
#define NavLightPWM_ONESHOT_SHIFT                  (18u)
#define NavLightPWM_QUAD_MODE_SHIFT                (20u)
#define NavLightPWM_INV_OUT_SHIFT                  (20u)
#define NavLightPWM_INV_COMPL_OUT_SHIFT            (21u)
#define NavLightPWM_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define NavLightPWM_RELOAD_CC_MASK                 ((uint32)(NavLightPWM_1BIT_MASK        <<  \
                                                                            NavLightPWM_RELOAD_CC_SHIFT))
#define NavLightPWM_RELOAD_PERIOD_MASK             ((uint32)(NavLightPWM_1BIT_MASK        <<  \
                                                                            NavLightPWM_RELOAD_PERIOD_SHIFT))
#define NavLightPWM_PWM_SYNC_KILL_MASK             ((uint32)(NavLightPWM_1BIT_MASK        <<  \
                                                                            NavLightPWM_PWM_SYNC_KILL_SHIFT))
#define NavLightPWM_PWM_STOP_KILL_MASK             ((uint32)(NavLightPWM_1BIT_MASK        <<  \
                                                                            NavLightPWM_PWM_STOP_KILL_SHIFT))
#define NavLightPWM_PRESCALER_MASK                 ((uint32)(NavLightPWM_8BIT_MASK        <<  \
                                                                            NavLightPWM_PRESCALER_SHIFT))
#define NavLightPWM_UPDOWN_MASK                    ((uint32)(NavLightPWM_2BIT_MASK        <<  \
                                                                            NavLightPWM_UPDOWN_SHIFT))
#define NavLightPWM_ONESHOT_MASK                   ((uint32)(NavLightPWM_1BIT_MASK        <<  \
                                                                            NavLightPWM_ONESHOT_SHIFT))
#define NavLightPWM_QUAD_MODE_MASK                 ((uint32)(NavLightPWM_3BIT_MASK        <<  \
                                                                            NavLightPWM_QUAD_MODE_SHIFT))
#define NavLightPWM_INV_OUT_MASK                   ((uint32)(NavLightPWM_2BIT_MASK        <<  \
                                                                            NavLightPWM_INV_OUT_SHIFT))
#define NavLightPWM_MODE_MASK                      ((uint32)(NavLightPWM_3BIT_MASK        <<  \
                                                                            NavLightPWM_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define NavLightPWM_CAPTURE_SHIFT                  (0u)
#define NavLightPWM_COUNT_SHIFT                    (2u)
#define NavLightPWM_RELOAD_SHIFT                   (4u)
#define NavLightPWM_STOP_SHIFT                     (6u)
#define NavLightPWM_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define NavLightPWM_CAPTURE_MASK                   ((uint32)(NavLightPWM_2BIT_MASK        <<  \
                                                                  NavLightPWM_CAPTURE_SHIFT))
#define NavLightPWM_COUNT_MASK                     ((uint32)(NavLightPWM_2BIT_MASK        <<  \
                                                                  NavLightPWM_COUNT_SHIFT))
#define NavLightPWM_RELOAD_MASK                    ((uint32)(NavLightPWM_2BIT_MASK        <<  \
                                                                  NavLightPWM_RELOAD_SHIFT))
#define NavLightPWM_STOP_MASK                      ((uint32)(NavLightPWM_2BIT_MASK        <<  \
                                                                  NavLightPWM_STOP_SHIFT))
#define NavLightPWM_START_MASK                     ((uint32)(NavLightPWM_2BIT_MASK        <<  \
                                                                  NavLightPWM_START_SHIFT))

/* MASK */
#define NavLightPWM_1BIT_MASK                      ((uint32)0x01u)
#define NavLightPWM_2BIT_MASK                      ((uint32)0x03u)
#define NavLightPWM_3BIT_MASK                      ((uint32)0x07u)
#define NavLightPWM_6BIT_MASK                      ((uint32)0x3Fu)
#define NavLightPWM_8BIT_MASK                      ((uint32)0xFFu)
#define NavLightPWM_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define NavLightPWM_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define NavLightPWM_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(NavLightPWM_QUAD_ENCODING_MODES     << NavLightPWM_QUAD_MODE_SHIFT))       |\
         ((uint32)(NavLightPWM_CONFIG                  << NavLightPWM_MODE_SHIFT)))

#define NavLightPWM_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(NavLightPWM_PWM_STOP_EVENT          << NavLightPWM_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(NavLightPWM_PWM_OUT_INVERT          << NavLightPWM_INV_OUT_SHIFT))         |\
         ((uint32)(NavLightPWM_PWM_OUT_N_INVERT        << NavLightPWM_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(NavLightPWM_PWM_MODE                << NavLightPWM_MODE_SHIFT)))

#define NavLightPWM_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(NavLightPWM_PWM_RUN_MODE         << NavLightPWM_ONESHOT_SHIFT))
            
#define NavLightPWM_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(NavLightPWM_PWM_ALIGN            << NavLightPWM_UPDOWN_SHIFT))

#define NavLightPWM_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(NavLightPWM_PWM_KILL_EVENT      << NavLightPWM_PWM_SYNC_KILL_SHIFT))

#define NavLightPWM_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(NavLightPWM_PWM_DEAD_TIME_CYCLE  << NavLightPWM_PRESCALER_SHIFT))

#define NavLightPWM_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(NavLightPWM_PWM_PRESCALER        << NavLightPWM_PRESCALER_SHIFT))

#define NavLightPWM_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(NavLightPWM_TC_PRESCALER            << NavLightPWM_PRESCALER_SHIFT))       |\
         ((uint32)(NavLightPWM_TC_COUNTER_MODE         << NavLightPWM_UPDOWN_SHIFT))          |\
         ((uint32)(NavLightPWM_TC_RUN_MODE             << NavLightPWM_ONESHOT_SHIFT))         |\
         ((uint32)(NavLightPWM_TC_COMP_CAP_MODE        << NavLightPWM_MODE_SHIFT)))
        
#define NavLightPWM_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(NavLightPWM_QUAD_PHIA_SIGNAL_MODE   << NavLightPWM_COUNT_SHIFT))           |\
         ((uint32)(NavLightPWM_QUAD_INDEX_SIGNAL_MODE  << NavLightPWM_RELOAD_SHIFT))          |\
         ((uint32)(NavLightPWM_QUAD_STOP_SIGNAL_MODE   << NavLightPWM_STOP_SHIFT))            |\
         ((uint32)(NavLightPWM_QUAD_PHIB_SIGNAL_MODE   << NavLightPWM_START_SHIFT)))

#define NavLightPWM_PWM_SIGNALS_MODES                                                              \
        (((uint32)(NavLightPWM_PWM_SWITCH_SIGNAL_MODE  << NavLightPWM_CAPTURE_SHIFT))         |\
         ((uint32)(NavLightPWM_PWM_COUNT_SIGNAL_MODE   << NavLightPWM_COUNT_SHIFT))           |\
         ((uint32)(NavLightPWM_PWM_RELOAD_SIGNAL_MODE  << NavLightPWM_RELOAD_SHIFT))          |\
         ((uint32)(NavLightPWM_PWM_STOP_SIGNAL_MODE    << NavLightPWM_STOP_SHIFT))            |\
         ((uint32)(NavLightPWM_PWM_START_SIGNAL_MODE   << NavLightPWM_START_SHIFT)))

#define NavLightPWM_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(NavLightPWM_TC_CAPTURE_SIGNAL_MODE  << NavLightPWM_CAPTURE_SHIFT))         |\
         ((uint32)(NavLightPWM_TC_COUNT_SIGNAL_MODE    << NavLightPWM_COUNT_SHIFT))           |\
         ((uint32)(NavLightPWM_TC_RELOAD_SIGNAL_MODE   << NavLightPWM_RELOAD_SHIFT))          |\
         ((uint32)(NavLightPWM_TC_STOP_SIGNAL_MODE     << NavLightPWM_STOP_SHIFT))            |\
         ((uint32)(NavLightPWM_TC_START_SIGNAL_MODE    << NavLightPWM_START_SHIFT)))
        
#define NavLightPWM_TIMER_UPDOWN_CNT_USED                                                          \
                ((NavLightPWM__COUNT_UPDOWN0 == NavLightPWM_TC_COUNTER_MODE)                  ||\
                 (NavLightPWM__COUNT_UPDOWN1 == NavLightPWM_TC_COUNTER_MODE))

#define NavLightPWM_PWM_UPDOWN_CNT_USED                                                            \
                ((NavLightPWM__CENTER == NavLightPWM_PWM_ALIGN)                               ||\
                 (NavLightPWM__ASYMMETRIC == NavLightPWM_PWM_ALIGN))               
        
#define NavLightPWM_PWM_PR_INIT_VALUE              (1u)
#define NavLightPWM_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_NavLightPWM_H */

/* [] END OF FILE */
