/*******************************************************************************
* File Name: PPMCounter.h
* Version 1.10
*
* Description:
*  This file provides constants and parameter values for the PPMCounter
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

#if !defined(CY_TCPWM_PPMCounter_H)
#define CY_TCPWM_PPMCounter_H

#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} PPMCounter_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  PPMCounter_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define PPMCounter_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)

/* TCPWM Configuration */
#define PPMCounter_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define PPMCounter_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define PPMCounter_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define PPMCounter_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define PPMCounter_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define PPMCounter_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define PPMCounter_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define PPMCounter_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define PPMCounter_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define PPMCounter_TC_RUN_MODE                    (0lu)
#define PPMCounter_TC_COUNTER_MODE                (0lu)
#define PPMCounter_TC_COMP_CAP_MODE               (2lu)
#define PPMCounter_TC_PRESCALER                   (0lu)

/* Signal modes */
#define PPMCounter_TC_RELOAD_SIGNAL_MODE          (0lu)
#define PPMCounter_TC_COUNT_SIGNAL_MODE           (3lu)
#define PPMCounter_TC_START_SIGNAL_MODE           (0lu)
#define PPMCounter_TC_STOP_SIGNAL_MODE            (0lu)
#define PPMCounter_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define PPMCounter_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define PPMCounter_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define PPMCounter_TC_START_SIGNAL_PRESENT        (0lu)
#define PPMCounter_TC_STOP_SIGNAL_PRESENT         (0lu)
#define PPMCounter_TC_CAPTURE_SIGNAL_PRESENT      (1lu)

/* Interrupt Mask */
#define PPMCounter_TC_INTERRUPT_MASK              (2lu)

/* PWM Mode */
/* Parameters */
#define PPMCounter_PWM_KILL_EVENT                 (0lu)
#define PPMCounter_PWM_STOP_EVENT                 (0lu)
#define PPMCounter_PWM_MODE                       (4lu)
#define PPMCounter_PWM_OUT_N_INVERT               (0lu)
#define PPMCounter_PWM_OUT_INVERT                 (0lu)
#define PPMCounter_PWM_ALIGN                      (0lu)
#define PPMCounter_PWM_RUN_MODE                   (0lu)
#define PPMCounter_PWM_DEAD_TIME_CYCLE            (0lu)
#define PPMCounter_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define PPMCounter_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define PPMCounter_PWM_COUNT_SIGNAL_MODE          (3lu)
#define PPMCounter_PWM_START_SIGNAL_MODE          (0lu)
#define PPMCounter_PWM_STOP_SIGNAL_MODE           (0lu)
#define PPMCounter_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define PPMCounter_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define PPMCounter_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define PPMCounter_PWM_START_SIGNAL_PRESENT       (0lu)
#define PPMCounter_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define PPMCounter_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PPMCounter_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define PPMCounter_TC_PERIOD_VALUE                (3600lu)
#define PPMCounter_TC_COMPARE_VALUE               (65535lu)
#define PPMCounter_TC_COMPARE_BUF_VALUE           (65535lu)
#define PPMCounter_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define PPMCounter_PWM_PERIOD_VALUE               (65535lu)
#define PPMCounter_PWM_PERIOD_BUF_VALUE           (65535lu)
#define PPMCounter_PWM_PERIOD_SWAP                (0lu)
#define PPMCounter_PWM_COMPARE_VALUE              (65535lu)
#define PPMCounter_PWM_COMPARE_BUF_VALUE          (65535lu)
#define PPMCounter_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define PPMCounter__LEFT 0
#define PPMCounter__RIGHT 1
#define PPMCounter__CENTER 2
#define PPMCounter__ASYMMETRIC 3

#define PPMCounter__X1 0
#define PPMCounter__X2 1
#define PPMCounter__X4 2

#define PPMCounter__PWM 4
#define PPMCounter__PWM_DT 5
#define PPMCounter__PWM_PR 6

#define PPMCounter__INVERSE 1
#define PPMCounter__DIRECT 0

#define PPMCounter__CAPTURE 2
#define PPMCounter__COMPARE 0

#define PPMCounter__TRIG_LEVEL 3
#define PPMCounter__TRIG_RISING 0
#define PPMCounter__TRIG_FALLING 1
#define PPMCounter__TRIG_BOTH 2

#define PPMCounter__INTR_MASK_TC 1
#define PPMCounter__INTR_MASK_CC_MATCH 2
#define PPMCounter__INTR_MASK_NONE 0
#define PPMCounter__INTR_MASK_TC_CC 3

#define PPMCounter__UNCONFIG 8
#define PPMCounter__TIMER 1
#define PPMCounter__QUAD 3
#define PPMCounter__PWM_SEL 7

#define PPMCounter__COUNT_UP 0
#define PPMCounter__COUNT_DOWN 1
#define PPMCounter__COUNT_UPDOWN0 2
#define PPMCounter__COUNT_UPDOWN1 3


/* Prescaler */
#define PPMCounter_PRESCALE_DIVBY1                ((uint32)(0u << PPMCounter_PRESCALER_SHIFT))
#define PPMCounter_PRESCALE_DIVBY2                ((uint32)(1u << PPMCounter_PRESCALER_SHIFT))
#define PPMCounter_PRESCALE_DIVBY4                ((uint32)(2u << PPMCounter_PRESCALER_SHIFT))
#define PPMCounter_PRESCALE_DIVBY8                ((uint32)(3u << PPMCounter_PRESCALER_SHIFT))
#define PPMCounter_PRESCALE_DIVBY16               ((uint32)(4u << PPMCounter_PRESCALER_SHIFT))
#define PPMCounter_PRESCALE_DIVBY32               ((uint32)(5u << PPMCounter_PRESCALER_SHIFT))
#define PPMCounter_PRESCALE_DIVBY64               ((uint32)(6u << PPMCounter_PRESCALER_SHIFT))
#define PPMCounter_PRESCALE_DIVBY128              ((uint32)(7u << PPMCounter_PRESCALER_SHIFT))

/* TCPWM set modes */
#define PPMCounter_MODE_TIMER_COMPARE             ((uint32)(PPMCounter__COMPARE         <<  \
                                                                  PPMCounter_MODE_SHIFT))
#define PPMCounter_MODE_TIMER_CAPTURE             ((uint32)(PPMCounter__CAPTURE         <<  \
                                                                  PPMCounter_MODE_SHIFT))
#define PPMCounter_MODE_QUAD                      ((uint32)(PPMCounter__QUAD            <<  \
                                                                  PPMCounter_MODE_SHIFT))
#define PPMCounter_MODE_PWM                       ((uint32)(PPMCounter__PWM             <<  \
                                                                  PPMCounter_MODE_SHIFT))
#define PPMCounter_MODE_PWM_DT                    ((uint32)(PPMCounter__PWM_DT          <<  \
                                                                  PPMCounter_MODE_SHIFT))
#define PPMCounter_MODE_PWM_PR                    ((uint32)(PPMCounter__PWM_PR          <<  \
                                                                  PPMCounter_MODE_SHIFT))

/* Quad Modes */
#define PPMCounter_MODE_X1                        ((uint32)(PPMCounter__X1              <<  \
                                                                  PPMCounter_QUAD_MODE_SHIFT))
#define PPMCounter_MODE_X2                        ((uint32)(PPMCounter__X2              <<  \
                                                                  PPMCounter_QUAD_MODE_SHIFT))
#define PPMCounter_MODE_X4                        ((uint32)(PPMCounter__X4              <<  \
                                                                  PPMCounter_QUAD_MODE_SHIFT))

/* Counter modes */
#define PPMCounter_COUNT_UP                       ((uint32)(PPMCounter__COUNT_UP        <<  \
                                                                  PPMCounter_UPDOWN_SHIFT))
#define PPMCounter_COUNT_DOWN                     ((uint32)(PPMCounter__COUNT_DOWN      <<  \
                                                                  PPMCounter_UPDOWN_SHIFT))
#define PPMCounter_COUNT_UPDOWN0                  ((uint32)(PPMCounter__COUNT_UPDOWN0   <<  \
                                                                  PPMCounter_UPDOWN_SHIFT))
#define PPMCounter_COUNT_UPDOWN1                  ((uint32)(PPMCounter__COUNT_UPDOWN1   <<  \
                                                                  PPMCounter_UPDOWN_SHIFT))

/* PWM output invert */
#define PPMCounter_INVERT_LINE                    ((uint32)(PPMCounter__INVERSE         <<  \
                                                                  PPMCounter_INV_OUT_SHIFT))
#define PPMCounter_INVERT_LINE_N                  ((uint32)(PPMCounter__INVERSE         <<  \
                                                                  PPMCounter_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define PPMCounter_TRIG_RISING                    ((uint32)PPMCounter__TRIG_RISING)
#define PPMCounter_TRIG_FALLING                   ((uint32)PPMCounter__TRIG_FALLING)
#define PPMCounter_TRIG_BOTH                      ((uint32)PPMCounter__TRIG_BOTH)
#define PPMCounter_TRIG_LEVEL                     ((uint32)PPMCounter__TRIG_LEVEL)

/* Interrupt mask */
#define PPMCounter_INTR_MASK_TC                   ((uint32)PPMCounter__INTR_MASK_TC)
#define PPMCounter_INTR_MASK_CC_MATCH             ((uint32)PPMCounter__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define PPMCounter_CC_MATCH_SET                   (0x00u)
#define PPMCounter_CC_MATCH_CLEAR                 (0x01u)
#define PPMCounter_CC_MATCH_INVERT                (0x02u)
#define PPMCounter_CC_MATCH_NO_CHANGE             (0x03u)
#define PPMCounter_OVERLOW_SET                    (0x00u)
#define PPMCounter_OVERLOW_CLEAR                  (0x04u)
#define PPMCounter_OVERLOW_INVERT                 (0x08u)
#define PPMCounter_OVERLOW_NO_CHANGE              (0x0Cu)
#define PPMCounter_UNDERFLOW_SET                  (0x00u)
#define PPMCounter_UNDERFLOW_CLEAR                (0x10u)
#define PPMCounter_UNDERFLOW_INVERT               (0x20u)
#define PPMCounter_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define PPMCounter_PWM_MODE_LEFT                  (PPMCounter_CC_MATCH_CLEAR        |   \
                                                         PPMCounter_OVERLOW_SET           |   \
                                                         PPMCounter_UNDERFLOW_NO_CHANGE)
#define PPMCounter_PWM_MODE_RIGHT                 (PPMCounter_CC_MATCH_SET          |   \
                                                         PPMCounter_OVERLOW_NO_CHANGE     |   \
                                                         PPMCounter_UNDERFLOW_CLEAR)
#define PPMCounter_PWM_MODE_CENTER                (PPMCounter_CC_MATCH_INVERT       |   \
                                                         PPMCounter_OVERLOW_NO_CHANGE     |   \
                                                         PPMCounter_UNDERFLOW_CLEAR)
#define PPMCounter_PWM_MODE_ASYM                  (PPMCounter_CC_MATCH_NO_CHANGE    |   \
                                                         PPMCounter_OVERLOW_SET           |   \
                                                         PPMCounter_UNDERFLOW_CLEAR )

/* Command operations without condition */
#define PPMCounter_CMD_CAPTURE                    (0u)
#define PPMCounter_CMD_RELOAD                     (8u)
#define PPMCounter_CMD_STOP                       (16u)
#define PPMCounter_CMD_START                      (24u)

/* Status */
#define PPMCounter_STATUS_DOWN                    (1u)
#define PPMCounter_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   PPMCounter_Init(void);
void   PPMCounter_Enable(void);
void   PPMCounter_Start(void);
void   PPMCounter_Stop(void);

void   PPMCounter_SetMode(uint32 mode);
void   PPMCounter_SetCounterMode(uint32 counterMode);
void   PPMCounter_SetPWMMode(uint32 modeMask);
void   PPMCounter_SetQDMode(uint32 qdMode);

void   PPMCounter_SetPrescaler(uint32 prescaler);
void   PPMCounter_TriggerCommand(uint32 mask, uint32 command);
void   PPMCounter_SetOneShot(uint32 oneShotEnable);
uint32 PPMCounter_ReadStatus(void);

void   PPMCounter_SetPWMSyncKill(uint32 syncKillEnable);
void   PPMCounter_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   PPMCounter_SetPWMDeadTime(uint32 deadTime);
void   PPMCounter_SetPWMInvert(uint32 mask);

void   PPMCounter_SetInterruptMode(uint32 interruptMask);
uint32 PPMCounter_GetInterruptSourceMasked(void);
uint32 PPMCounter_GetInterruptSource(void);
void   PPMCounter_ClearInterrupt(uint32 interruptMask);
void   PPMCounter_SetInterrupt(uint32 interruptMask);

void   PPMCounter_WriteCounter(uint32 count);
uint32 PPMCounter_ReadCounter(void);

uint32 PPMCounter_ReadCapture(void);
uint32 PPMCounter_ReadCaptureBuf(void);

void   PPMCounter_WritePeriod(uint32 period);
uint32 PPMCounter_ReadPeriod(void);
void   PPMCounter_WritePeriodBuf(uint32 periodBuf);
uint32 PPMCounter_ReadPeriodBuf(void);

void   PPMCounter_WriteCompare(uint32 compare);
uint32 PPMCounter_ReadCompare(void);
void   PPMCounter_WriteCompareBuf(uint32 compareBuf);
uint32 PPMCounter_ReadCompareBuf(void);

void   PPMCounter_SetPeriodSwap(uint32 swapEnable);
void   PPMCounter_SetCompareSwap(uint32 swapEnable);

void   PPMCounter_SetCaptureMode(uint32 triggerMode);
void   PPMCounter_SetReloadMode(uint32 triggerMode);
void   PPMCounter_SetStartMode(uint32 triggerMode);
void   PPMCounter_SetStopMode(uint32 triggerMode);
void   PPMCounter_SetCountMode(uint32 triggerMode);

void   PPMCounter_SaveConfig(void);
void   PPMCounter_RestoreConfig(void);
void   PPMCounter_Sleep(void);
void   PPMCounter_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define PPMCounter_BLOCK_CONTROL_REG              (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PPMCounter_BLOCK_CONTROL_PTR              ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PPMCounter_COMMAND_REG                    (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PPMCounter_COMMAND_PTR                    ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PPMCounter_INTRRUPT_CAUSE_REG             (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PPMCounter_INTRRUPT_CAUSE_PTR             ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PPMCounter_CONTROL_REG                    (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__CTRL )
#define PPMCounter_CONTROL_PTR                    ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__CTRL )
#define PPMCounter_STATUS_REG                     (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__STATUS )
#define PPMCounter_STATUS_PTR                     ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__STATUS )
#define PPMCounter_COUNTER_REG                    (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__COUNTER )
#define PPMCounter_COUNTER_PTR                    ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__COUNTER )
#define PPMCounter_COMP_CAP_REG                   (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__CC )
#define PPMCounter_COMP_CAP_PTR                   ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__CC )
#define PPMCounter_COMP_CAP_BUF_REG               (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__CC_BUFF )
#define PPMCounter_COMP_CAP_BUF_PTR               ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__CC_BUFF )
#define PPMCounter_PERIOD_REG                     (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__PERIOD )
#define PPMCounter_PERIOD_PTR                     ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__PERIOD )
#define PPMCounter_PERIOD_BUF_REG                 (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PPMCounter_PERIOD_BUF_PTR                 ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PPMCounter_TRIG_CONTROL0_REG              (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PPMCounter_TRIG_CONTROL0_PTR              ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PPMCounter_TRIG_CONTROL1_REG              (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PPMCounter_TRIG_CONTROL1_PTR              ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PPMCounter_TRIG_CONTROL2_REG              (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PPMCounter_TRIG_CONTROL2_PTR              ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PPMCounter_INTERRUPT_REQ_REG              (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__INTR )
#define PPMCounter_INTERRUPT_REQ_PTR              ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__INTR )
#define PPMCounter_INTERRUPT_SET_REG              (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__INTR_SET )
#define PPMCounter_INTERRUPT_SET_PTR              ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__INTR_SET )
#define PPMCounter_INTERRUPT_MASK_REG             (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__INTR_MASK )
#define PPMCounter_INTERRUPT_MASK_PTR             ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__INTR_MASK )
#define PPMCounter_INTERRUPT_MASKED_REG           (*(reg32 *) PPMCounter_cy_m0s8_tcpwm_1__INTR_MASKED )
#define PPMCounter_INTERRUPT_MASKED_PTR           ( (reg32 *) PPMCounter_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define PPMCounter_MASK                           ((uint32)PPMCounter_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define PPMCounter_RELOAD_CC_SHIFT                (0u)
#define PPMCounter_RELOAD_PERIOD_SHIFT            (1u)
#define PPMCounter_PWM_SYNC_KILL_SHIFT            (2u)
#define PPMCounter_PWM_STOP_KILL_SHIFT            (3u)
#define PPMCounter_PRESCALER_SHIFT                (8u)
#define PPMCounter_UPDOWN_SHIFT                   (16u)
#define PPMCounter_ONESHOT_SHIFT                  (18u)
#define PPMCounter_QUAD_MODE_SHIFT                (20u)
#define PPMCounter_INV_OUT_SHIFT                  (20u)
#define PPMCounter_INV_COMPL_OUT_SHIFT            (21u)
#define PPMCounter_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define PPMCounter_RELOAD_CC_MASK                 ((uint32)(PPMCounter_1BIT_MASK        <<  \
                                                                            PPMCounter_RELOAD_CC_SHIFT))
#define PPMCounter_RELOAD_PERIOD_MASK             ((uint32)(PPMCounter_1BIT_MASK        <<  \
                                                                            PPMCounter_RELOAD_PERIOD_SHIFT))
#define PPMCounter_PWM_SYNC_KILL_MASK             ((uint32)(PPMCounter_1BIT_MASK        <<  \
                                                                            PPMCounter_PWM_SYNC_KILL_SHIFT))
#define PPMCounter_PWM_STOP_KILL_MASK             ((uint32)(PPMCounter_1BIT_MASK        <<  \
                                                                            PPMCounter_PWM_STOP_KILL_SHIFT))
#define PPMCounter_PRESCALER_MASK                 ((uint32)(PPMCounter_8BIT_MASK        <<  \
                                                                            PPMCounter_PRESCALER_SHIFT))
#define PPMCounter_UPDOWN_MASK                    ((uint32)(PPMCounter_2BIT_MASK        <<  \
                                                                            PPMCounter_UPDOWN_SHIFT))
#define PPMCounter_ONESHOT_MASK                   ((uint32)(PPMCounter_1BIT_MASK        <<  \
                                                                            PPMCounter_ONESHOT_SHIFT))
#define PPMCounter_QUAD_MODE_MASK                 ((uint32)(PPMCounter_3BIT_MASK        <<  \
                                                                            PPMCounter_QUAD_MODE_SHIFT))
#define PPMCounter_INV_OUT_MASK                   ((uint32)(PPMCounter_2BIT_MASK        <<  \
                                                                            PPMCounter_INV_OUT_SHIFT))
#define PPMCounter_MODE_MASK                      ((uint32)(PPMCounter_3BIT_MASK        <<  \
                                                                            PPMCounter_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define PPMCounter_CAPTURE_SHIFT                  (0u)
#define PPMCounter_COUNT_SHIFT                    (2u)
#define PPMCounter_RELOAD_SHIFT                   (4u)
#define PPMCounter_STOP_SHIFT                     (6u)
#define PPMCounter_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define PPMCounter_CAPTURE_MASK                   ((uint32)(PPMCounter_2BIT_MASK        <<  \
                                                                  PPMCounter_CAPTURE_SHIFT))
#define PPMCounter_COUNT_MASK                     ((uint32)(PPMCounter_2BIT_MASK        <<  \
                                                                  PPMCounter_COUNT_SHIFT))
#define PPMCounter_RELOAD_MASK                    ((uint32)(PPMCounter_2BIT_MASK        <<  \
                                                                  PPMCounter_RELOAD_SHIFT))
#define PPMCounter_STOP_MASK                      ((uint32)(PPMCounter_2BIT_MASK        <<  \
                                                                  PPMCounter_STOP_SHIFT))
#define PPMCounter_START_MASK                     ((uint32)(PPMCounter_2BIT_MASK        <<  \
                                                                  PPMCounter_START_SHIFT))

/* MASK */
#define PPMCounter_1BIT_MASK                      ((uint32)0x01u)
#define PPMCounter_2BIT_MASK                      ((uint32)0x03u)
#define PPMCounter_3BIT_MASK                      ((uint32)0x07u)
#define PPMCounter_6BIT_MASK                      ((uint32)0x3Fu)
#define PPMCounter_8BIT_MASK                      ((uint32)0xFFu)
#define PPMCounter_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define PPMCounter_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define PPMCounter_PWM_PR_INIT_VALUE              (1u)

#endif /* End CY_TCPWM_PPMCounter_H */

/* [] END OF FILE */
