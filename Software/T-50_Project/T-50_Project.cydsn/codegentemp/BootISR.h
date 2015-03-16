/*******************************************************************************
* File Name: BootISR.h
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
#if !defined(CY_ISR_BootISR_H)
#define CY_ISR_BootISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void BootISR_Start(void);
void BootISR_StartEx(cyisraddress address);
void BootISR_Stop(void);

CY_ISR_PROTO(BootISR_Interrupt);

void BootISR_SetVector(cyisraddress address);
cyisraddress BootISR_GetVector(void);

void BootISR_SetPriority(uint8 priority);
uint8 BootISR_GetPriority(void);

void BootISR_Enable(void);
uint8 BootISR_GetState(void);
void BootISR_Disable(void);

void BootISR_SetPending(void);
void BootISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the BootISR ISR. */
#define BootISR_INTC_VECTOR            ((reg32 *) BootISR__INTC_VECT)

/* Address of the BootISR ISR priority. */
#define BootISR_INTC_PRIOR             ((reg32 *) BootISR__INTC_PRIOR_REG)

/* Priority of the BootISR interrupt. */
#define BootISR_INTC_PRIOR_NUMBER      BootISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable BootISR interrupt. */
#define BootISR_INTC_SET_EN            ((reg32 *) BootISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the BootISR interrupt. */
#define BootISR_INTC_CLR_EN            ((reg32 *) BootISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the BootISR interrupt state to pending. */
#define BootISR_INTC_SET_PD            ((reg32 *) BootISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the BootISR interrupt. */
#define BootISR_INTC_CLR_PD            ((reg32 *) BootISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_BootISR_H */


/* [] END OF FILE */
