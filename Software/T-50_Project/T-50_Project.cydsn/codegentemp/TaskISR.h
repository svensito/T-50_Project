/*******************************************************************************
* File Name: TaskISR.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_TaskISR_H)
#define CY_ISR_TaskISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void TaskISR_Start(void);
void TaskISR_StartEx(cyisraddress address);
void TaskISR_Stop(void);

CY_ISR_PROTO(TaskISR_Interrupt);

void TaskISR_SetVector(cyisraddress address);
cyisraddress TaskISR_GetVector(void);

void TaskISR_SetPriority(uint8 priority);
uint8 TaskISR_GetPriority(void);

void TaskISR_Enable(void);
uint8 TaskISR_GetState(void);
void TaskISR_Disable(void);

void TaskISR_SetPending(void);
void TaskISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the TaskISR ISR. */
#define TaskISR_INTC_VECTOR            ((reg32 *) TaskISR__INTC_VECT)

/* Address of the TaskISR ISR priority. */
#define TaskISR_INTC_PRIOR             ((reg32 *) TaskISR__INTC_PRIOR_REG)

/* Priority of the TaskISR interrupt. */
#define TaskISR_INTC_PRIOR_NUMBER      TaskISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable TaskISR interrupt. */
#define TaskISR_INTC_SET_EN            ((reg32 *) TaskISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the TaskISR interrupt. */
#define TaskISR_INTC_CLR_EN            ((reg32 *) TaskISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the TaskISR interrupt state to pending. */
#define TaskISR_INTC_SET_PD            ((reg32 *) TaskISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the TaskISR interrupt. */
#define TaskISR_INTC_CLR_PD            ((reg32 *) TaskISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_TaskISR_H */


/* [] END OF FILE */
