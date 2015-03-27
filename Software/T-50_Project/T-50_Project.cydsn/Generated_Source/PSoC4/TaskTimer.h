/*******************************************************************************
* File Name: TaskTimer.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the TaskTimer
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

#if !defined(CY_TCPWM_TaskTimer_H)
#define CY_TCPWM_TaskTimer_H


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
} TaskTimer_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  TaskTimer_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define TaskTimer_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define TaskTimer_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define TaskTimer_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define TaskTimer_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define TaskTimer_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define TaskTimer_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define TaskTimer_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define TaskTimer_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define TaskTimer_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define TaskTimer_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define TaskTimer_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define TaskTimer_TC_RUN_MODE                    (0lu)
#define TaskTimer_TC_COUNTER_MODE                (0lu)
#define TaskTimer_TC_COMP_CAP_MODE               (0lu)
#define TaskTimer_TC_PRESCALER                   (0lu)

/* Signal modes */
#define TaskTimer_TC_RELOAD_SIGNAL_MODE          (0lu)
#define TaskTimer_TC_COUNT_SIGNAL_MODE           (3lu)
#define TaskTimer_TC_START_SIGNAL_MODE           (0lu)
#define TaskTimer_TC_STOP_SIGNAL_MODE            (0lu)
#define TaskTimer_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define TaskTimer_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define TaskTimer_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define TaskTimer_TC_START_SIGNAL_PRESENT        (0lu)
#define TaskTimer_TC_STOP_SIGNAL_PRESENT         (0lu)
#define TaskTimer_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define TaskTimer_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define TaskTimer_PWM_KILL_EVENT                 (0lu)
#define TaskTimer_PWM_STOP_EVENT                 (0lu)
#define TaskTimer_PWM_MODE                       (4lu)
#define TaskTimer_PWM_OUT_N_INVERT               (0lu)
#define TaskTimer_PWM_OUT_INVERT                 (0lu)
#define TaskTimer_PWM_ALIGN                      (0lu)
#define TaskTimer_PWM_RUN_MODE                   (0lu)
#define TaskTimer_PWM_DEAD_TIME_CYCLE            (0lu)
#define TaskTimer_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define TaskTimer_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define TaskTimer_PWM_COUNT_SIGNAL_MODE          (3lu)
#define TaskTimer_PWM_START_SIGNAL_MODE          (0lu)
#define TaskTimer_PWM_STOP_SIGNAL_MODE           (0lu)
#define TaskTimer_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define TaskTimer_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define TaskTimer_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define TaskTimer_PWM_START_SIGNAL_PRESENT       (0lu)
#define TaskTimer_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define TaskTimer_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define TaskTimer_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define TaskTimer_TC_PERIOD_VALUE                (10000lu)
#define TaskTimer_TC_COMPARE_VALUE               (10000lu)
#define TaskTimer_TC_COMPARE_BUF_VALUE           (0lu)
#define TaskTimer_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define TaskTimer_PWM_PERIOD_VALUE               (65535lu)
#define TaskTimer_PWM_PERIOD_BUF_VALUE           (65535lu)
#define TaskTimer_PWM_PERIOD_SWAP                (0lu)
#define TaskTimer_PWM_COMPARE_VALUE              (65535lu)
#define TaskTimer_PWM_COMPARE_BUF_VALUE          (65535lu)
#define TaskTimer_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define TaskTimer__LEFT 0
#define TaskTimer__RIGHT 1
#define TaskTimer__CENTER 2
#define TaskTimer__ASYMMETRIC 3

#define TaskTimer__X1 0
#define TaskTimer__X2 1
#define TaskTimer__X4 2

#define TaskTimer__PWM 4
#define TaskTimer__PWM_DT 5
#define TaskTimer__PWM_PR 6

#define TaskTimer__INVERSE 1
#define TaskTimer__DIRECT 0

#define TaskTimer__CAPTURE 2
#define TaskTimer__COMPARE 0

#define TaskTimer__TRIG_LEVEL 3
#define TaskTimer__TRIG_RISING 0
#define TaskTimer__TRIG_FALLING 1
#define TaskTimer__TRIG_BOTH 2

#define TaskTimer__INTR_MASK_TC 1
#define TaskTimer__INTR_MASK_CC_MATCH 2
#define TaskTimer__INTR_MASK_NONE 0
#define TaskTimer__INTR_MASK_TC_CC 3

#define TaskTimer__UNCONFIG 8
#define TaskTimer__TIMER 1
#define TaskTimer__QUAD 3
#define TaskTimer__PWM_SEL 7

#define TaskTimer__COUNT_UP 0
#define TaskTimer__COUNT_DOWN 1
#define TaskTimer__COUNT_UPDOWN0 2
#define TaskTimer__COUNT_UPDOWN1 3


/* Prescaler */
#define TaskTimer_PRESCALE_DIVBY1                ((uint32)(0u << TaskTimer_PRESCALER_SHIFT))
#define TaskTimer_PRESCALE_DIVBY2                ((uint32)(1u << TaskTimer_PRESCALER_SHIFT))
#define TaskTimer_PRESCALE_DIVBY4                ((uint32)(2u << TaskTimer_PRESCALER_SHIFT))
#define TaskTimer_PRESCALE_DIVBY8                ((uint32)(3u << TaskTimer_PRESCALER_SHIFT))
#define TaskTimer_PRESCALE_DIVBY16               ((uint32)(4u << TaskTimer_PRESCALER_SHIFT))
#define TaskTimer_PRESCALE_DIVBY32               ((uint32)(5u << TaskTimer_PRESCALER_SHIFT))
#define TaskTimer_PRESCALE_DIVBY64               ((uint32)(6u << TaskTimer_PRESCALER_SHIFT))
#define TaskTimer_PRESCALE_DIVBY128              ((uint32)(7u << TaskTimer_PRESCALER_SHIFT))

/* TCPWM set modes */
#define TaskTimer_MODE_TIMER_COMPARE             ((uint32)(TaskTimer__COMPARE         <<  \
                                                                  TaskTimer_MODE_SHIFT))
#define TaskTimer_MODE_TIMER_CAPTURE             ((uint32)(TaskTimer__CAPTURE         <<  \
                                                                  TaskTimer_MODE_SHIFT))
#define TaskTimer_MODE_QUAD                      ((uint32)(TaskTimer__QUAD            <<  \
                                                                  TaskTimer_MODE_SHIFT))
#define TaskTimer_MODE_PWM                       ((uint32)(TaskTimer__PWM             <<  \
                                                                  TaskTimer_MODE_SHIFT))
#define TaskTimer_MODE_PWM_DT                    ((uint32)(TaskTimer__PWM_DT          <<  \
                                                                  TaskTimer_MODE_SHIFT))
#define TaskTimer_MODE_PWM_PR                    ((uint32)(TaskTimer__PWM_PR          <<  \
                                                                  TaskTimer_MODE_SHIFT))

/* Quad Modes */
#define TaskTimer_MODE_X1                        ((uint32)(TaskTimer__X1              <<  \
                                                                  TaskTimer_QUAD_MODE_SHIFT))
#define TaskTimer_MODE_X2                        ((uint32)(TaskTimer__X2              <<  \
                                                                  TaskTimer_QUAD_MODE_SHIFT))
#define TaskTimer_MODE_X4                        ((uint32)(TaskTimer__X4              <<  \
                                                                  TaskTimer_QUAD_MODE_SHIFT))

/* Counter modes */
#define TaskTimer_COUNT_UP                       ((uint32)(TaskTimer__COUNT_UP        <<  \
                                                                  TaskTimer_UPDOWN_SHIFT))
#define TaskTimer_COUNT_DOWN                     ((uint32)(TaskTimer__COUNT_DOWN      <<  \
                                                                  TaskTimer_UPDOWN_SHIFT))
#define TaskTimer_COUNT_UPDOWN0                  ((uint32)(TaskTimer__COUNT_UPDOWN0   <<  \
                                                                  TaskTimer_UPDOWN_SHIFT))
#define TaskTimer_COUNT_UPDOWN1                  ((uint32)(TaskTimer__COUNT_UPDOWN1   <<  \
                                                                  TaskTimer_UPDOWN_SHIFT))

/* PWM output invert */
#define TaskTimer_INVERT_LINE                    ((uint32)(TaskTimer__INVERSE         <<  \
                                                                  TaskTimer_INV_OUT_SHIFT))
#define TaskTimer_INVERT_LINE_N                  ((uint32)(TaskTimer__INVERSE         <<  \
                                                                  TaskTimer_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define TaskTimer_TRIG_RISING                    ((uint32)TaskTimer__TRIG_RISING)
#define TaskTimer_TRIG_FALLING                   ((uint32)TaskTimer__TRIG_FALLING)
#define TaskTimer_TRIG_BOTH                      ((uint32)TaskTimer__TRIG_BOTH)
#define TaskTimer_TRIG_LEVEL                     ((uint32)TaskTimer__TRIG_LEVEL)

/* Interrupt mask */
#define TaskTimer_INTR_MASK_TC                   ((uint32)TaskTimer__INTR_MASK_TC)
#define TaskTimer_INTR_MASK_CC_MATCH             ((uint32)TaskTimer__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define TaskTimer_CC_MATCH_SET                   (0x00u)
#define TaskTimer_CC_MATCH_CLEAR                 (0x01u)
#define TaskTimer_CC_MATCH_INVERT                (0x02u)
#define TaskTimer_CC_MATCH_NO_CHANGE             (0x03u)
#define TaskTimer_OVERLOW_SET                    (0x00u)
#define TaskTimer_OVERLOW_CLEAR                  (0x04u)
#define TaskTimer_OVERLOW_INVERT                 (0x08u)
#define TaskTimer_OVERLOW_NO_CHANGE              (0x0Cu)
#define TaskTimer_UNDERFLOW_SET                  (0x00u)
#define TaskTimer_UNDERFLOW_CLEAR                (0x10u)
#define TaskTimer_UNDERFLOW_INVERT               (0x20u)
#define TaskTimer_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define TaskTimer_PWM_MODE_LEFT                  (TaskTimer_CC_MATCH_CLEAR        |   \
                                                         TaskTimer_OVERLOW_SET           |   \
                                                         TaskTimer_UNDERFLOW_NO_CHANGE)
#define TaskTimer_PWM_MODE_RIGHT                 (TaskTimer_CC_MATCH_SET          |   \
                                                         TaskTimer_OVERLOW_NO_CHANGE     |   \
                                                         TaskTimer_UNDERFLOW_CLEAR)
#define TaskTimer_PWM_MODE_ASYM                  (TaskTimer_CC_MATCH_INVERT       |   \
                                                         TaskTimer_OVERLOW_SET           |   \
                                                         TaskTimer_UNDERFLOW_CLEAR)

#if (TaskTimer_CY_TCPWM_V2)
    #if(TaskTimer_CY_TCPWM_4000)
        #define TaskTimer_PWM_MODE_CENTER                (TaskTimer_CC_MATCH_INVERT       |   \
                                                                 TaskTimer_OVERLOW_NO_CHANGE     |   \
                                                                 TaskTimer_UNDERFLOW_CLEAR)
    #else
        #define TaskTimer_PWM_MODE_CENTER                (TaskTimer_CC_MATCH_INVERT       |   \
                                                                 TaskTimer_OVERLOW_SET           |   \
                                                                 TaskTimer_UNDERFLOW_CLEAR)
    #endif /* (TaskTimer_CY_TCPWM_4000) */
#else
    #define TaskTimer_PWM_MODE_CENTER                (TaskTimer_CC_MATCH_INVERT       |   \
                                                             TaskTimer_OVERLOW_NO_CHANGE     |   \
                                                             TaskTimer_UNDERFLOW_CLEAR)
#endif /* (TaskTimer_CY_TCPWM_NEW) */

/* Command operations without condition */
#define TaskTimer_CMD_CAPTURE                    (0u)
#define TaskTimer_CMD_RELOAD                     (8u)
#define TaskTimer_CMD_STOP                       (16u)
#define TaskTimer_CMD_START                      (24u)

/* Status */
#define TaskTimer_STATUS_DOWN                    (1u)
#define TaskTimer_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   TaskTimer_Init(void);
void   TaskTimer_Enable(void);
void   TaskTimer_Start(void);
void   TaskTimer_Stop(void);

void   TaskTimer_SetMode(uint32 mode);
void   TaskTimer_SetCounterMode(uint32 counterMode);
void   TaskTimer_SetPWMMode(uint32 modeMask);
void   TaskTimer_SetQDMode(uint32 qdMode);

void   TaskTimer_SetPrescaler(uint32 prescaler);
void   TaskTimer_TriggerCommand(uint32 mask, uint32 command);
void   TaskTimer_SetOneShot(uint32 oneShotEnable);
uint32 TaskTimer_ReadStatus(void);

void   TaskTimer_SetPWMSyncKill(uint32 syncKillEnable);
void   TaskTimer_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   TaskTimer_SetPWMDeadTime(uint32 deadTime);
void   TaskTimer_SetPWMInvert(uint32 mask);

void   TaskTimer_SetInterruptMode(uint32 interruptMask);
uint32 TaskTimer_GetInterruptSourceMasked(void);
uint32 TaskTimer_GetInterruptSource(void);
void   TaskTimer_ClearInterrupt(uint32 interruptMask);
void   TaskTimer_SetInterrupt(uint32 interruptMask);

void   TaskTimer_WriteCounter(uint32 count);
uint32 TaskTimer_ReadCounter(void);

uint32 TaskTimer_ReadCapture(void);
uint32 TaskTimer_ReadCaptureBuf(void);

void   TaskTimer_WritePeriod(uint32 period);
uint32 TaskTimer_ReadPeriod(void);
void   TaskTimer_WritePeriodBuf(uint32 periodBuf);
uint32 TaskTimer_ReadPeriodBuf(void);

void   TaskTimer_WriteCompare(uint32 compare);
uint32 TaskTimer_ReadCompare(void);
void   TaskTimer_WriteCompareBuf(uint32 compareBuf);
uint32 TaskTimer_ReadCompareBuf(void);

void   TaskTimer_SetPeriodSwap(uint32 swapEnable);
void   TaskTimer_SetCompareSwap(uint32 swapEnable);

void   TaskTimer_SetCaptureMode(uint32 triggerMode);
void   TaskTimer_SetReloadMode(uint32 triggerMode);
void   TaskTimer_SetStartMode(uint32 triggerMode);
void   TaskTimer_SetStopMode(uint32 triggerMode);
void   TaskTimer_SetCountMode(uint32 triggerMode);

void   TaskTimer_SaveConfig(void);
void   TaskTimer_RestoreConfig(void);
void   TaskTimer_Sleep(void);
void   TaskTimer_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define TaskTimer_BLOCK_CONTROL_REG              (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define TaskTimer_BLOCK_CONTROL_PTR              ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define TaskTimer_COMMAND_REG                    (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define TaskTimer_COMMAND_PTR                    ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define TaskTimer_INTRRUPT_CAUSE_REG             (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define TaskTimer_INTRRUPT_CAUSE_PTR             ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define TaskTimer_CONTROL_REG                    (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__CTRL )
#define TaskTimer_CONTROL_PTR                    ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__CTRL )
#define TaskTimer_STATUS_REG                     (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__STATUS )
#define TaskTimer_STATUS_PTR                     ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__STATUS )
#define TaskTimer_COUNTER_REG                    (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__COUNTER )
#define TaskTimer_COUNTER_PTR                    ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__COUNTER )
#define TaskTimer_COMP_CAP_REG                   (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__CC )
#define TaskTimer_COMP_CAP_PTR                   ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__CC )
#define TaskTimer_COMP_CAP_BUF_REG               (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define TaskTimer_COMP_CAP_BUF_PTR               ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define TaskTimer_PERIOD_REG                     (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__PERIOD )
#define TaskTimer_PERIOD_PTR                     ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__PERIOD )
#define TaskTimer_PERIOD_BUF_REG                 (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define TaskTimer_PERIOD_BUF_PTR                 ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define TaskTimer_TRIG_CONTROL0_REG              (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define TaskTimer_TRIG_CONTROL0_PTR              ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define TaskTimer_TRIG_CONTROL1_REG              (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define TaskTimer_TRIG_CONTROL1_PTR              ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define TaskTimer_TRIG_CONTROL2_REG              (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define TaskTimer_TRIG_CONTROL2_PTR              ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define TaskTimer_INTERRUPT_REQ_REG              (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__INTR )
#define TaskTimer_INTERRUPT_REQ_PTR              ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__INTR )
#define TaskTimer_INTERRUPT_SET_REG              (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define TaskTimer_INTERRUPT_SET_PTR              ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define TaskTimer_INTERRUPT_MASK_REG             (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define TaskTimer_INTERRUPT_MASK_PTR             ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define TaskTimer_INTERRUPT_MASKED_REG           (*(reg32 *) TaskTimer_cy_m0s8_tcpwm_1__INTR_MASKED )
#define TaskTimer_INTERRUPT_MASKED_PTR           ( (reg32 *) TaskTimer_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define TaskTimer_MASK                           ((uint32)TaskTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define TaskTimer_RELOAD_CC_SHIFT                (0u)
#define TaskTimer_RELOAD_PERIOD_SHIFT            (1u)
#define TaskTimer_PWM_SYNC_KILL_SHIFT            (2u)
#define TaskTimer_PWM_STOP_KILL_SHIFT            (3u)
#define TaskTimer_PRESCALER_SHIFT                (8u)
#define TaskTimer_UPDOWN_SHIFT                   (16u)
#define TaskTimer_ONESHOT_SHIFT                  (18u)
#define TaskTimer_QUAD_MODE_SHIFT                (20u)
#define TaskTimer_INV_OUT_SHIFT                  (20u)
#define TaskTimer_INV_COMPL_OUT_SHIFT            (21u)
#define TaskTimer_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define TaskTimer_RELOAD_CC_MASK                 ((uint32)(TaskTimer_1BIT_MASK        <<  \
                                                                            TaskTimer_RELOAD_CC_SHIFT))
#define TaskTimer_RELOAD_PERIOD_MASK             ((uint32)(TaskTimer_1BIT_MASK        <<  \
                                                                            TaskTimer_RELOAD_PERIOD_SHIFT))
#define TaskTimer_PWM_SYNC_KILL_MASK             ((uint32)(TaskTimer_1BIT_MASK        <<  \
                                                                            TaskTimer_PWM_SYNC_KILL_SHIFT))
#define TaskTimer_PWM_STOP_KILL_MASK             ((uint32)(TaskTimer_1BIT_MASK        <<  \
                                                                            TaskTimer_PWM_STOP_KILL_SHIFT))
#define TaskTimer_PRESCALER_MASK                 ((uint32)(TaskTimer_8BIT_MASK        <<  \
                                                                            TaskTimer_PRESCALER_SHIFT))
#define TaskTimer_UPDOWN_MASK                    ((uint32)(TaskTimer_2BIT_MASK        <<  \
                                                                            TaskTimer_UPDOWN_SHIFT))
#define TaskTimer_ONESHOT_MASK                   ((uint32)(TaskTimer_1BIT_MASK        <<  \
                                                                            TaskTimer_ONESHOT_SHIFT))
#define TaskTimer_QUAD_MODE_MASK                 ((uint32)(TaskTimer_3BIT_MASK        <<  \
                                                                            TaskTimer_QUAD_MODE_SHIFT))
#define TaskTimer_INV_OUT_MASK                   ((uint32)(TaskTimer_2BIT_MASK        <<  \
                                                                            TaskTimer_INV_OUT_SHIFT))
#define TaskTimer_MODE_MASK                      ((uint32)(TaskTimer_3BIT_MASK        <<  \
                                                                            TaskTimer_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define TaskTimer_CAPTURE_SHIFT                  (0u)
#define TaskTimer_COUNT_SHIFT                    (2u)
#define TaskTimer_RELOAD_SHIFT                   (4u)
#define TaskTimer_STOP_SHIFT                     (6u)
#define TaskTimer_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define TaskTimer_CAPTURE_MASK                   ((uint32)(TaskTimer_2BIT_MASK        <<  \
                                                                  TaskTimer_CAPTURE_SHIFT))
#define TaskTimer_COUNT_MASK                     ((uint32)(TaskTimer_2BIT_MASK        <<  \
                                                                  TaskTimer_COUNT_SHIFT))
#define TaskTimer_RELOAD_MASK                    ((uint32)(TaskTimer_2BIT_MASK        <<  \
                                                                  TaskTimer_RELOAD_SHIFT))
#define TaskTimer_STOP_MASK                      ((uint32)(TaskTimer_2BIT_MASK        <<  \
                                                                  TaskTimer_STOP_SHIFT))
#define TaskTimer_START_MASK                     ((uint32)(TaskTimer_2BIT_MASK        <<  \
                                                                  TaskTimer_START_SHIFT))

/* MASK */
#define TaskTimer_1BIT_MASK                      ((uint32)0x01u)
#define TaskTimer_2BIT_MASK                      ((uint32)0x03u)
#define TaskTimer_3BIT_MASK                      ((uint32)0x07u)
#define TaskTimer_6BIT_MASK                      ((uint32)0x3Fu)
#define TaskTimer_8BIT_MASK                      ((uint32)0xFFu)
#define TaskTimer_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define TaskTimer_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define TaskTimer_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(TaskTimer_QUAD_ENCODING_MODES     << TaskTimer_QUAD_MODE_SHIFT))       |\
         ((uint32)(TaskTimer_CONFIG                  << TaskTimer_MODE_SHIFT)))

#define TaskTimer_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(TaskTimer_PWM_STOP_EVENT          << TaskTimer_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(TaskTimer_PWM_OUT_INVERT          << TaskTimer_INV_OUT_SHIFT))         |\
         ((uint32)(TaskTimer_PWM_OUT_N_INVERT        << TaskTimer_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(TaskTimer_PWM_MODE                << TaskTimer_MODE_SHIFT)))

#define TaskTimer_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(TaskTimer_PWM_RUN_MODE         << TaskTimer_ONESHOT_SHIFT))
            
#define TaskTimer_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(TaskTimer_PWM_ALIGN            << TaskTimer_UPDOWN_SHIFT))

#define TaskTimer_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(TaskTimer_PWM_KILL_EVENT      << TaskTimer_PWM_SYNC_KILL_SHIFT))

#define TaskTimer_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(TaskTimer_PWM_DEAD_TIME_CYCLE  << TaskTimer_PRESCALER_SHIFT))

#define TaskTimer_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(TaskTimer_PWM_PRESCALER        << TaskTimer_PRESCALER_SHIFT))

#define TaskTimer_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(TaskTimer_TC_PRESCALER            << TaskTimer_PRESCALER_SHIFT))       |\
         ((uint32)(TaskTimer_TC_COUNTER_MODE         << TaskTimer_UPDOWN_SHIFT))          |\
         ((uint32)(TaskTimer_TC_RUN_MODE             << TaskTimer_ONESHOT_SHIFT))         |\
         ((uint32)(TaskTimer_TC_COMP_CAP_MODE        << TaskTimer_MODE_SHIFT)))
        
#define TaskTimer_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(TaskTimer_QUAD_PHIA_SIGNAL_MODE   << TaskTimer_COUNT_SHIFT))           |\
         ((uint32)(TaskTimer_QUAD_INDEX_SIGNAL_MODE  << TaskTimer_RELOAD_SHIFT))          |\
         ((uint32)(TaskTimer_QUAD_STOP_SIGNAL_MODE   << TaskTimer_STOP_SHIFT))            |\
         ((uint32)(TaskTimer_QUAD_PHIB_SIGNAL_MODE   << TaskTimer_START_SHIFT)))

#define TaskTimer_PWM_SIGNALS_MODES                                                              \
        (((uint32)(TaskTimer_PWM_SWITCH_SIGNAL_MODE  << TaskTimer_CAPTURE_SHIFT))         |\
         ((uint32)(TaskTimer_PWM_COUNT_SIGNAL_MODE   << TaskTimer_COUNT_SHIFT))           |\
         ((uint32)(TaskTimer_PWM_RELOAD_SIGNAL_MODE  << TaskTimer_RELOAD_SHIFT))          |\
         ((uint32)(TaskTimer_PWM_STOP_SIGNAL_MODE    << TaskTimer_STOP_SHIFT))            |\
         ((uint32)(TaskTimer_PWM_START_SIGNAL_MODE   << TaskTimer_START_SHIFT)))

#define TaskTimer_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(TaskTimer_TC_CAPTURE_SIGNAL_MODE  << TaskTimer_CAPTURE_SHIFT))         |\
         ((uint32)(TaskTimer_TC_COUNT_SIGNAL_MODE    << TaskTimer_COUNT_SHIFT))           |\
         ((uint32)(TaskTimer_TC_RELOAD_SIGNAL_MODE   << TaskTimer_RELOAD_SHIFT))          |\
         ((uint32)(TaskTimer_TC_STOP_SIGNAL_MODE     << TaskTimer_STOP_SHIFT))            |\
         ((uint32)(TaskTimer_TC_START_SIGNAL_MODE    << TaskTimer_START_SHIFT)))
        
#define TaskTimer_TIMER_UPDOWN_CNT_USED                                                          \
                ((TaskTimer__COUNT_UPDOWN0 == TaskTimer_TC_COUNTER_MODE)                  ||\
                 (TaskTimer__COUNT_UPDOWN1 == TaskTimer_TC_COUNTER_MODE))

#define TaskTimer_PWM_UPDOWN_CNT_USED                                                            \
                ((TaskTimer__CENTER == TaskTimer_PWM_ALIGN)                               ||\
                 (TaskTimer__ASYMMETRIC == TaskTimer_PWM_ALIGN))               
        
#define TaskTimer_PWM_PR_INIT_VALUE              (1u)
#define TaskTimer_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_TaskTimer_H */

/* [] END OF FILE */
