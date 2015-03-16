/*******************************************************************************
* File Name: PPMRstISR.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <PPMRstISR.h>

#if !defined(PPMRstISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START PPMRstISR_intc` */
#include <project.h>
extern uint8_t PPM_channel;     // input channel variable
extern uint16_t ctrl_in[];      // input control vector

uint8_t overflow = 0;
/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: PPMRstISR_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void PPMRstISR_Start(void)
{
    /* For all we know the interrupt is active. */
    PPMRstISR_Disable();

    /* Set the ISR to point to the PPMRstISR Interrupt. */
    PPMRstISR_SetVector(&PPMRstISR_Interrupt);

    /* Set the priority. */
    PPMRstISR_SetPriority((uint8)PPMRstISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    PPMRstISR_Enable();
}


/*******************************************************************************
* Function Name: PPMRstISR_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void PPMRstISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    PPMRstISR_Disable();

    /* Set the ISR to point to the PPMRstISR Interrupt. */
    PPMRstISR_SetVector(address);

    /* Set the priority. */
    PPMRstISR_SetPriority((uint8)PPMRstISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    PPMRstISR_Enable();
}


/*******************************************************************************
* Function Name: PPMRstISR_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
void PPMRstISR_Stop(void)
{
    /* Disable this interrupt. */
    PPMRstISR_Disable();

    /* Set the ISR to point to the passive one. */
    PPMRstISR_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: PPMRstISR_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for PPMRstISR.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(PPMRstISR_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START PPMRstISR_Interrupt` */
    PPMCounter_ClearInterrupt(PPMCounter_INTR_MASK_CC_MATCH); // clears interrupt
    overflow = 1;
    PPM_channel = 0;
    /* `#END` */
}


/*******************************************************************************
* Function Name: PPMRstISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling PPMRstISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use PPMRstISR_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void PPMRstISR_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + PPMRstISR__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: PPMRstISR_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress PPMRstISR_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + PPMRstISR__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: PPMRstISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling PPMRstISR_Start
*   or PPMRstISR_StartEx will override any effect this method would 
*   have had. This method should only be called after PPMRstISR_Start or 
*   PPMRstISR_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void PPMRstISR_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((PPMRstISR__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *PPMRstISR_INTC_PRIOR = (*PPMRstISR_INTC_PRIOR & (uint32)(~PPMRstISR__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: PPMRstISR_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 3, 0 being the highest.
*
*******************************************************************************/
uint8 PPMRstISR_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((PPMRstISR__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*PPMRstISR_INTC_PRIOR & PPMRstISR__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: PPMRstISR_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void PPMRstISR_Enable(void)
{
    /* Enable the general interrupt. */
    *PPMRstISR_INTC_SET_EN = PPMRstISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: PPMRstISR_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 PPMRstISR_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*PPMRstISR_INTC_SET_EN & (uint32)PPMRstISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: PPMRstISR_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void PPMRstISR_Disable(void)
{
    /* Disable the general interrupt. */
    *PPMRstISR_INTC_CLR_EN = PPMRstISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: PPMRstISR_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void PPMRstISR_SetPending(void)
{
    *PPMRstISR_INTC_SET_PD = PPMRstISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: PPMRstISR_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void PPMRstISR_ClearPending(void)
{
    *PPMRstISR_INTC_CLR_PD = PPMRstISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
