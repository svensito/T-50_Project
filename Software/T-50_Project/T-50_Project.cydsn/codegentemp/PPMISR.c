/*******************************************************************************
* File Name: PPMISR.c  
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
#include <PPMISR.h>

#if !defined(PPMISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START PPMISR_intc` */
#include <project.h>
    
extern uint8_t PPM_channel;     // input channel variable
extern uint16_t ctrl_in[];      // input control vector
extern uint8_t overflow;        // overflow from the PPMRstISR    
/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: PPMISR_Start
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
void PPMISR_Start(void)
{
    /* For all we know the interrupt is active. */
    PPMISR_Disable();

    /* Set the ISR to point to the PPMISR Interrupt. */
    PPMISR_SetVector(&PPMISR_Interrupt);

    /* Set the priority. */
    PPMISR_SetPriority((uint8)PPMISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    PPMISR_Enable();
}


/*******************************************************************************
* Function Name: PPMISR_StartEx
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
void PPMISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    PPMISR_Disable();

    /* Set the ISR to point to the PPMISR Interrupt. */
    PPMISR_SetVector(address);

    /* Set the priority. */
    PPMISR_SetPriority((uint8)PPMISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    PPMISR_Enable();
}


/*******************************************************************************
* Function Name: PPMISR_Stop
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
void PPMISR_Stop(void)
{
    /* Disable this interrupt. */
    PPMISR_Disable();

    /* Set the ISR to point to the passive one. */
    PPMISR_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: PPMISR_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for PPMISR.
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
CY_ISR(PPMISR_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START PPMISR_Interrupt` */
    PPMCounter_ClearInterrupt(PPMCounter_INTR_MASK_CC_MATCH); // clears the interrupt
    
    if(overflow == 1) 
    {
        overflow = 0;
        PPM_channel = 0;
    }
    else
    {
        ctrl_in[PPM_channel] =  PPMCounter_ReadCounter();       // Reading the current counter value
        PPM_channel++;
    }
    PPMCounter_WriteCounter(0);     // Resetting the counter
    /* `#END` */
}


/*******************************************************************************
* Function Name: PPMISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling PPMISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use PPMISR_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void PPMISR_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + PPMISR__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: PPMISR_GetVector
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
cyisraddress PPMISR_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + PPMISR__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: PPMISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling PPMISR_Start
*   or PPMISR_StartEx will override any effect this method would 
*   have had. This method should only be called after PPMISR_Start or 
*   PPMISR_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void PPMISR_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((PPMISR__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *PPMISR_INTC_PRIOR = (*PPMISR_INTC_PRIOR & (uint32)(~PPMISR__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: PPMISR_GetPriority
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
uint8 PPMISR_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((PPMISR__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*PPMISR_INTC_PRIOR & PPMISR__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: PPMISR_Enable
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
void PPMISR_Enable(void)
{
    /* Enable the general interrupt. */
    *PPMISR_INTC_SET_EN = PPMISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: PPMISR_GetState
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
uint8 PPMISR_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*PPMISR_INTC_SET_EN & (uint32)PPMISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: PPMISR_Disable
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
void PPMISR_Disable(void)
{
    /* Disable the general interrupt. */
    *PPMISR_INTC_CLR_EN = PPMISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: PPMISR_SetPending
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
void PPMISR_SetPending(void)
{
    *PPMISR_INTC_SET_PD = PPMISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: PPMISR_ClearPending
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
void PPMISR_ClearPending(void)
{
    *PPMISR_INTC_CLR_PD = PPMISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
