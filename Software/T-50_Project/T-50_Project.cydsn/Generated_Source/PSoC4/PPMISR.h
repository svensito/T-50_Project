/*******************************************************************************
* File Name: PPMISR.h
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
#if !defined(CY_ISR_PPMISR_H)
#define CY_ISR_PPMISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void PPMISR_Start(void);
void PPMISR_StartEx(cyisraddress address);
void PPMISR_Stop(void);

CY_ISR_PROTO(PPMISR_Interrupt);

void PPMISR_SetVector(cyisraddress address);
cyisraddress PPMISR_GetVector(void);

void PPMISR_SetPriority(uint8 priority);
uint8 PPMISR_GetPriority(void);

void PPMISR_Enable(void);
uint8 PPMISR_GetState(void);
void PPMISR_Disable(void);

void PPMISR_SetPending(void);
void PPMISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the PPMISR ISR. */
#define PPMISR_INTC_VECTOR            ((reg32 *) PPMISR__INTC_VECT)

/* Address of the PPMISR ISR priority. */
#define PPMISR_INTC_PRIOR             ((reg32 *) PPMISR__INTC_PRIOR_REG)

/* Priority of the PPMISR interrupt. */
#define PPMISR_INTC_PRIOR_NUMBER      PPMISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable PPMISR interrupt. */
#define PPMISR_INTC_SET_EN            ((reg32 *) PPMISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the PPMISR interrupt. */
#define PPMISR_INTC_CLR_EN            ((reg32 *) PPMISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the PPMISR interrupt state to pending. */
#define PPMISR_INTC_SET_PD            ((reg32 *) PPMISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the PPMISR interrupt. */
#define PPMISR_INTC_CLR_PD            ((reg32 *) PPMISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_PPMISR_H */


/* [] END OF FILE */
