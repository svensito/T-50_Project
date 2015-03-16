/*******************************************************************************
* File Name: ServoTimer.h
* Version 1.10
*
* Description:
*  This file provides constants and parameter values for the ServoTimer
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

#if !defined(CY_TCPWM_ServoTimer_H)
#define CY_TCPWM_ServoTimer_H

#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} ServoTimer_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  ServoTimer_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define ServoTimer_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)

/* TCPWM Configuration */
#define ServoTimer_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define ServoTimer_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define ServoTimer_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define ServoTimer_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define ServoTimer_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define ServoTimer_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define ServoTimer_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define ServoTimer_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define ServoTimer_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define ServoTimer_TC_RUN_MODE                    (0lu)
#define ServoTimer_TC_COUNTER_MODE                (0lu)
#define ServoTimer_TC_COMP_CAP_MODE               (0lu)
#define ServoTimer_TC_PRESCALER                   (0lu)

/* Signal modes */
#define ServoTimer_TC_RELOAD_SIGNAL_MODE          (0lu)
#define ServoTimer_TC_COUNT_SIGNAL_MODE           (3lu)
#define ServoTimer_TC_START_SIGNAL_MODE           (0lu)
#define ServoTimer_TC_STOP_SIGNAL_MODE            (0lu)
#define ServoTimer_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define ServoTimer_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define ServoTimer_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define ServoTimer_TC_START_SIGNAL_PRESENT        (0lu)
#define ServoTimer_TC_STOP_SIGNAL_PRESENT         (0lu)
#define ServoTimer_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define ServoTimer_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define ServoTimer_PWM_KILL_EVENT                 (0lu)
#define ServoTimer_PWM_STOP_EVENT                 (0lu)
#define ServoTimer_PWM_MODE                       (4lu)
#define ServoTimer_PWM_OUT_N_INVERT               (0lu)
#define ServoTimer_PWM_OUT_INVERT                 (0lu)
#define ServoTimer_PWM_ALIGN                      (0lu)
#define ServoTimer_PWM_RUN_MODE                   (0lu)
#define ServoTimer_PWM_DEAD_TIME_CYCLE            (0lu)
#define ServoTimer_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define ServoTimer_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define ServoTimer_PWM_COUNT_SIGNAL_MODE          (3lu)
#define ServoTimer_PWM_START_SIGNAL_MODE          (0lu)
#define ServoTimer_PWM_STOP_SIGNAL_MODE           (0lu)
#define ServoTimer_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define ServoTimer_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define ServoTimer_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define ServoTimer_PWM_START_SIGNAL_PRESENT       (0lu)
#define ServoTimer_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define ServoTimer_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define ServoTimer_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define ServoTimer_TC_PERIOD_VALUE                (65535lu)
#define ServoTimer_TC_COMPARE_VALUE               (65535lu)
#define ServoTimer_TC_COMPARE_BUF_VALUE           (65535lu)
#define ServoTimer_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define ServoTimer_PWM_PERIOD_VALUE               (65535lu)
#define ServoTimer_PWM_PERIOD_BUF_VALUE           (65535lu)
#define ServoTimer_PWM_PERIOD_SWAP                (0lu)
#define ServoTimer_PWM_COMPARE_VALUE              (65535lu)
#define ServoTimer_PWM_COMPARE_BUF_VALUE          (65535lu)
#define ServoTimer_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define ServoTimer__LEFT 0
#define ServoTimer__RIGHT 1
#define ServoTimer__CENTER 2
#define ServoTimer__ASYMMETRIC 3

#define ServoTimer__X1 0
#define ServoTimer__X2 1
#define ServoTimer__X4 2

#define ServoTimer__PWM 4
#define ServoTimer__PWM_DT 5
#define ServoTimer__PWM_PR 6

#define ServoTimer__INVERSE 1
#define ServoTimer__DIRECT 0

#define ServoTimer__CAPTURE 2
#define ServoTimer__COMPARE 0

#define ServoTimer__TRIG_LEVEL 3
#define ServoTimer__TRIG_RISING 0
#define ServoTimer__TRIG_FALLING 1
#define ServoTimer__TRIG_BOTH 2

#define ServoTimer__INTR_MASK_TC 1
#define ServoTimer__INTR_MASK_CC_MATCH 2
#define ServoTimer__INTR_MASK_NONE 0
#define ServoTimer__INTR_MASK_TC_CC 3

#define ServoTimer__UNCONFIG 8
#define ServoTimer__TIMER 1
#define ServoTimer__QUAD 3
#define ServoTimer__PWM_SEL 7

#define ServoTimer__COUNT_UP 0
#define ServoTimer__COUNT_DOWN 1
#define ServoTimer__COUNT_UPDOWN0 2
#define ServoTimer__COUNT_UPDOWN1 3


/* Prescaler */
#define ServoTimer_PRESCALE_DIVBY1                ((uint32)(0u << ServoTimer_PRESCALER_SHIFT))
#define ServoTimer_PRESCALE_DIVBY2                ((uint32)(1u << ServoTimer_PRESCALER_SHIFT))
#define ServoTimer_PRESCALE_DIVBY4                ((uint32)(2u << ServoTimer_PRESCALER_SHIFT))
#define ServoTimer_PRESCALE_DIVBY8                ((uint32)(3u << ServoTimer_PRESCALER_SHIFT))
#define ServoTimer_PRESCALE_DIVBY16               ((uint32)(4u << ServoTimer_PRESCALER_SHIFT))
#define ServoTimer_PRESCALE_DIVBY32               ((uint32)(5u << ServoTimer_PRESCALER_SHIFT))
#define ServoTimer_PRESCALE_DIVBY64               ((uint32)(6u << ServoTimer_PRESCALER_SHIFT))
#define ServoTimer_PRESCALE_DIVBY128              ((uint32)(7u << ServoTimer_PRESCALER_SHIFT))

/* TCPWM set modes */
#define ServoTimer_MODE_TIMER_COMPARE             ((uint32)(ServoTimer__COMPARE         <<  \
                                                                  ServoTimer_MODE_SHIFT))
#define ServoTimer_MODE_TIMER_CAPTURE             ((uint32)(ServoTimer__CAPTURE         <<  \
                                                                  ServoTimer_MODE_SHIFT))
#define ServoTimer_MODE_QUAD                      ((uint32)(ServoTimer__QUAD            <<  \
                                                                  ServoTimer_MODE_SHIFT))
#define ServoTimer_MODE_PWM                       ((uint32)(ServoTimer__PWM             <<  \
                                                                  ServoTimer_MODE_SHIFT))
#define ServoTimer_MODE_PWM_DT                    ((uint32)(ServoTimer__PWM_DT          <<  \
                                                                  ServoTimer_MODE_SHIFT))
#define ServoTimer_MODE_PWM_PR                    ((uint32)(ServoTimer__PWM_PR          <<  \
                                                                  ServoTimer_MODE_SHIFT))

/* Quad Modes */
#define ServoTimer_MODE_X1                        ((uint32)(ServoTimer__X1              <<  \
                                                                  ServoTimer_QUAD_MODE_SHIFT))
#define ServoTimer_MODE_X2                        ((uint32)(ServoTimer__X2              <<  \
                                                                  ServoTimer_QUAD_MODE_SHIFT))
#define ServoTimer_MODE_X4                        ((uint32)(ServoTimer__X4              <<  \
                                                                  ServoTimer_QUAD_MODE_SHIFT))

/* Counter modes */
#define ServoTimer_COUNT_UP                       ((uint32)(ServoTimer__COUNT_UP        <<  \
                                                                  ServoTimer_UPDOWN_SHIFT))
#define ServoTimer_COUNT_DOWN                     ((uint32)(ServoTimer__COUNT_DOWN      <<  \
                                                                  ServoTimer_UPDOWN_SHIFT))
#define ServoTimer_COUNT_UPDOWN0                  ((uint32)(ServoTimer__COUNT_UPDOWN0   <<  \
                                                                  ServoTimer_UPDOWN_SHIFT))
#define ServoTimer_COUNT_UPDOWN1                  ((uint32)(ServoTimer__COUNT_UPDOWN1   <<  \
                                                                  ServoTimer_UPDOWN_SHIFT))

/* PWM output invert */
#define ServoTimer_INVERT_LINE                    ((uint32)(ServoTimer__INVERSE         <<  \
                                                                  ServoTimer_INV_OUT_SHIFT))
#define ServoTimer_INVERT_LINE_N                  ((uint32)(ServoTimer__INVERSE         <<  \
                                                                  ServoTimer_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define ServoTimer_TRIG_RISING                    ((uint32)ServoTimer__TRIG_RISING)
#define ServoTimer_TRIG_FALLING                   ((uint32)ServoTimer__TRIG_FALLING)
#define ServoTimer_TRIG_BOTH                      ((uint32)ServoTimer__TRIG_BOTH)
#define ServoTimer_TRIG_LEVEL                     ((uint32)ServoTimer__TRIG_LEVEL)

/* Interrupt mask */
#define ServoTimer_INTR_MASK_TC                   ((uint32)ServoTimer__INTR_MASK_TC)
#define ServoTimer_INTR_MASK_CC_MATCH             ((uint32)ServoTimer__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define ServoTimer_CC_MATCH_SET                   (0x00u)
#define ServoTimer_CC_MATCH_CLEAR                 (0x01u)
#define ServoTimer_CC_MATCH_INVERT                (0x02u)
#define ServoTimer_CC_MATCH_NO_CHANGE             (0x03u)
#define ServoTimer_OVERLOW_SET                    (0x00u)
#define ServoTimer_OVERLOW_CLEAR                  (0x04u)
#define ServoTimer_OVERLOW_INVERT                 (0x08u)
#define ServoTimer_OVERLOW_NO_CHANGE              (0x0Cu)
#define ServoTimer_UNDERFLOW_SET                  (0x00u)
#define ServoTimer_UNDERFLOW_CLEAR                (0x10u)
#define ServoTimer_UNDERFLOW_INVERT               (0x20u)
#define ServoTimer_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define ServoTimer_PWM_MODE_LEFT                  (ServoTimer_CC_MATCH_CLEAR        |   \
                                                         ServoTimer_OVERLOW_SET           |   \
                                                         ServoTimer_UNDERFLOW_NO_CHANGE)
#define ServoTimer_PWM_MODE_RIGHT                 (ServoTimer_CC_MATCH_SET          |   \
                                                         ServoTimer_OVERLOW_NO_CHANGE     |   \
                                                         ServoTimer_UNDERFLOW_CLEAR)
#define ServoTimer_PWM_MODE_CENTER                (ServoTimer_CC_MATCH_INVERT       |   \
                                                         ServoTimer_OVERLOW_NO_CHANGE     |   \
                                                         ServoTimer_UNDERFLOW_CLEAR)
#define ServoTimer_PWM_MODE_ASYM                  (ServoTimer_CC_MATCH_NO_CHANGE    |   \
                                                         ServoTimer_OVERLOW_SET           |   \
                                                         ServoTimer_UNDERFLOW_CLEAR )

/* Command operations without condition */
#define ServoTimer_CMD_CAPTURE                    (0u)
#define ServoTimer_CMD_RELOAD                     (8u)
#define ServoTimer_CMD_STOP                       (16u)
#define ServoTimer_CMD_START                      (24u)

/* Status */
#define ServoTimer_STATUS_DOWN                    (1u)
#define ServoTimer_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   ServoTimer_Init(void);
void   ServoTimer_Enable(void);
void   ServoTimer_Start(void);
void   ServoTimer_Stop(void);

void   ServoTimer_SetMode(uint32 mode);
void   ServoTimer_SetCounterMode(uint32 counterMode);
void   ServoTimer_SetPWMMode(uint32 modeMask);
void   ServoTimer_SetQDMode(uint32 qdMode);

void   ServoTimer_SetPrescaler(uint32 prescaler);
void   ServoTimer_TriggerCommand(uint32 mask, uint32 command);
void   ServoTimer_SetOneShot(uint32 oneShotEnable);
uint32 ServoTimer_ReadStatus(void);

void   ServoTimer_SetPWMSyncKill(uint32 syncKillEnable);
void   ServoTimer_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   ServoTimer_SetPWMDeadTime(uint32 deadTime);
void   ServoTimer_SetPWMInvert(uint32 mask);

void   ServoTimer_SetInterruptMode(uint32 interruptMask);
uint32 ServoTimer_GetInterruptSourceMasked(void);
uint32 ServoTimer_GetInterruptSource(void);
void   ServoTimer_ClearInterrupt(uint32 interruptMask);
void   ServoTimer_SetInterrupt(uint32 interruptMask);

void   ServoTimer_WriteCounter(uint32 count);
uint32 ServoTimer_ReadCounter(void);

uint32 ServoTimer_ReadCapture(void);
uint32 ServoTimer_ReadCaptureBuf(void);

void   ServoTimer_WritePeriod(uint32 period);
uint32 ServoTimer_ReadPeriod(void);
void   ServoTimer_WritePeriodBuf(uint32 periodBuf);
uint32 ServoTimer_ReadPeriodBuf(void);

void   ServoTimer_WriteCompare(uint32 compare);
uint32 ServoTimer_ReadCompare(void);
void   ServoTimer_WriteCompareBuf(uint32 compareBuf);
uint32 ServoTimer_ReadCompareBuf(void);

void   ServoTimer_SetPeriodSwap(uint32 swapEnable);
void   ServoTimer_SetCompareSwap(uint32 swapEnable);

void   ServoTimer_SetCaptureMode(uint32 triggerMode);
void   ServoTimer_SetReloadMode(uint32 triggerMode);
void   ServoTimer_SetStartMode(uint32 triggerMode);
void   ServoTimer_SetStopMode(uint32 triggerMode);
void   ServoTimer_SetCountMode(uint32 triggerMode);

void   ServoTimer_SaveConfig(void);
void   ServoTimer_RestoreConfig(void);
void   ServoTimer_Sleep(void);
void   ServoTimer_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define ServoTimer_BLOCK_CONTROL_REG              (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define ServoTimer_BLOCK_CONTROL_PTR              ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define ServoTimer_COMMAND_REG                    (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define ServoTimer_COMMAND_PTR                    ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define ServoTimer_INTRRUPT_CAUSE_REG             (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define ServoTimer_INTRRUPT_CAUSE_PTR             ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define ServoTimer_CONTROL_REG                    (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__CTRL )
#define ServoTimer_CONTROL_PTR                    ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__CTRL )
#define ServoTimer_STATUS_REG                     (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__STATUS )
#define ServoTimer_STATUS_PTR                     ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__STATUS )
#define ServoTimer_COUNTER_REG                    (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__COUNTER )
#define ServoTimer_COUNTER_PTR                    ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__COUNTER )
#define ServoTimer_COMP_CAP_REG                   (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__CC )
#define ServoTimer_COMP_CAP_PTR                   ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__CC )
#define ServoTimer_COMP_CAP_BUF_REG               (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define ServoTimer_COMP_CAP_BUF_PTR               ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define ServoTimer_PERIOD_REG                     (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__PERIOD )
#define ServoTimer_PERIOD_PTR                     ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__PERIOD )
#define ServoTimer_PERIOD_BUF_REG                 (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define ServoTimer_PERIOD_BUF_PTR                 ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define ServoTimer_TRIG_CONTROL0_REG              (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define ServoTimer_TRIG_CONTROL0_PTR              ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define ServoTimer_TRIG_CONTROL1_REG              (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define ServoTimer_TRIG_CONTROL1_PTR              ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define ServoTimer_TRIG_CONTROL2_REG              (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define ServoTimer_TRIG_CONTROL2_PTR              ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define ServoTimer_INTERRUPT_REQ_REG              (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__INTR )
#define ServoTimer_INTERRUPT_REQ_PTR              ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__INTR )
#define ServoTimer_INTERRUPT_SET_REG              (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define ServoTimer_INTERRUPT_SET_PTR              ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define ServoTimer_INTERRUPT_MASK_REG             (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define ServoTimer_INTERRUPT_MASK_PTR             ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define ServoTimer_INTERRUPT_MASKED_REG           (*(reg32 *) ServoTimer_cy_m0s8_tcpwm_1__INTR_MASKED )
#define ServoTimer_INTERRUPT_MASKED_PTR           ( (reg32 *) ServoTimer_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define ServoTimer_MASK                           ((uint32)ServoTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define ServoTimer_RELOAD_CC_SHIFT                (0u)
#define ServoTimer_RELOAD_PERIOD_SHIFT            (1u)
#define ServoTimer_PWM_SYNC_KILL_SHIFT            (2u)
#define ServoTimer_PWM_STOP_KILL_SHIFT            (3u)
#define ServoTimer_PRESCALER_SHIFT                (8u)
#define ServoTimer_UPDOWN_SHIFT                   (16u)
#define ServoTimer_ONESHOT_SHIFT                  (18u)
#define ServoTimer_QUAD_MODE_SHIFT                (20u)
#define ServoTimer_INV_OUT_SHIFT                  (20u)
#define ServoTimer_INV_COMPL_OUT_SHIFT            (21u)
#define ServoTimer_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define ServoTimer_RELOAD_CC_MASK                 ((uint32)(ServoTimer_1BIT_MASK        <<  \
                                                                            ServoTimer_RELOAD_CC_SHIFT))
#define ServoTimer_RELOAD_PERIOD_MASK             ((uint32)(ServoTimer_1BIT_MASK        <<  \
                                                                            ServoTimer_RELOAD_PERIOD_SHIFT))
#define ServoTimer_PWM_SYNC_KILL_MASK             ((uint32)(ServoTimer_1BIT_MASK        <<  \
                                                                            ServoTimer_PWM_SYNC_KILL_SHIFT))
#define ServoTimer_PWM_STOP_KILL_MASK             ((uint32)(ServoTimer_1BIT_MASK        <<  \
                                                                            ServoTimer_PWM_STOP_KILL_SHIFT))
#define ServoTimer_PRESCALER_MASK                 ((uint32)(ServoTimer_8BIT_MASK        <<  \
                                                                            ServoTimer_PRESCALER_SHIFT))
#define ServoTimer_UPDOWN_MASK                    ((uint32)(ServoTimer_2BIT_MASK        <<  \
                                                                            ServoTimer_UPDOWN_SHIFT))
#define ServoTimer_ONESHOT_MASK                   ((uint32)(ServoTimer_1BIT_MASK        <<  \
                                                                            ServoTimer_ONESHOT_SHIFT))
#define ServoTimer_QUAD_MODE_MASK                 ((uint32)(ServoTimer_3BIT_MASK        <<  \
                                                                            ServoTimer_QUAD_MODE_SHIFT))
#define ServoTimer_INV_OUT_MASK                   ((uint32)(ServoTimer_2BIT_MASK        <<  \
                                                                            ServoTimer_INV_OUT_SHIFT))
#define ServoTimer_MODE_MASK                      ((uint32)(ServoTimer_3BIT_MASK        <<  \
                                                                            ServoTimer_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define ServoTimer_CAPTURE_SHIFT                  (0u)
#define ServoTimer_COUNT_SHIFT                    (2u)
#define ServoTimer_RELOAD_SHIFT                   (4u)
#define ServoTimer_STOP_SHIFT                     (6u)
#define ServoTimer_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define ServoTimer_CAPTURE_MASK                   ((uint32)(ServoTimer_2BIT_MASK        <<  \
                                                                  ServoTimer_CAPTURE_SHIFT))
#define ServoTimer_COUNT_MASK                     ((uint32)(ServoTimer_2BIT_MASK        <<  \
                                                                  ServoTimer_COUNT_SHIFT))
#define ServoTimer_RELOAD_MASK                    ((uint32)(ServoTimer_2BIT_MASK        <<  \
                                                                  ServoTimer_RELOAD_SHIFT))
#define ServoTimer_STOP_MASK                      ((uint32)(ServoTimer_2BIT_MASK        <<  \
                                                                  ServoTimer_STOP_SHIFT))
#define ServoTimer_START_MASK                     ((uint32)(ServoTimer_2BIT_MASK        <<  \
                                                                  ServoTimer_START_SHIFT))

/* MASK */
#define ServoTimer_1BIT_MASK                      ((uint32)0x01u)
#define ServoTimer_2BIT_MASK                      ((uint32)0x03u)
#define ServoTimer_3BIT_MASK                      ((uint32)0x07u)
#define ServoTimer_6BIT_MASK                      ((uint32)0x3Fu)
#define ServoTimer_8BIT_MASK                      ((uint32)0xFFu)
#define ServoTimer_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define ServoTimer_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define ServoTimer_PWM_PR_INIT_VALUE              (1u)

#endif /* End CY_TCPWM_ServoTimer_H */

/* [] END OF FILE */
