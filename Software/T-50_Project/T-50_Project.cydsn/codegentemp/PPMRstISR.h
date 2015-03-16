/*******************************************************************************
* File Name: PPMRstISR.h
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
#if !defined(CY_ISR_PPMRstISR_H)
#define CY_ISR_PPMRstISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void PPMRstISR_Start(void);
void PPMRstISR_StartEx(cyisraddress address);
void PPMRstISR_Stop(void);

CY_ISR_PROTO(PPMRstISR_Interrupt);

void PPMRstISR_SetVector(cyisraddress address);
cyisraddress PPMRstISR_GetVector(void);

void PPMRstISR_SetPriority(uint8 priority);
uint8 PPMRstISR_GetPriority(void);

void PPMRstISR_Enable(void);
uint8 PPMRstISR_GetState(void);
void PPMRstISR_Disable(void);

void PPMRstISR_SetPending(void);
void PPMRstISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the PPMRstISR ISR. */
#define PPMRstISR_INTC_VECTOR            ((reg32 *) PPMRstISR__INTC_VECT)

/* Address of the PPMRstISR ISR priority. */
#define PPMRstISR_INTC_PRIOR             ((reg32 *) PPMRstISR__INTC_PRIOR_REG)

/* Priority of the PPMRstISR interrupt. */
#define PPMRstISR_INTC_PRIOR_NUMBER      PPMRstISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable PPMRstISR interrupt. */
#define PPMRstISR_INTC_SET_EN            ((reg32 *) PPMRstISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the PPMRstISR interrupt. */
#define PPMRstISR_INTC_CLR_EN            ((reg32 *) PPMRstISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the PPMRstISR interrupt state to pending. */
#define PPMRstISR_INTC_SET_PD            ((reg32 *) PPMRstISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the PPMRstISR interrupt. */
#define PPMRstISR_INTC_CLR_PD            ((reg32 *) PPMRstISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_PPMRstISR_H */


/* [] END OF FILE */
