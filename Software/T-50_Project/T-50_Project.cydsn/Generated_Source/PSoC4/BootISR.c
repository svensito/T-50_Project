/*******************************************************************************
* File Name: BootISR.c  
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
#include <BootISR.h>

#if !defined(BootISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START BootISR_intc` */
#include <project.h>
/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: BootISR_Start
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
void BootISR_Start(void)
{
    /* For all we know the interrupt is active. */
    BootISR_Disable();

    /* Set the ISR to point to the BootISR Interrupt. */
    BootISR_SetVector(&BootISR_Interrupt);

    /* Set the priority. */
    BootISR_SetPriority((uint8)BootISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    BootISR_Enable();
}


/*******************************************************************************
* Function Name: BootISR_StartEx
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
void BootISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    BootISR_Disable();

    /* Set the ISR to point to the BootISR Interrupt. */
    BootISR_SetVector(address);

    /* Set the priority. */
    BootISR_SetPriority((uint8)BootISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    BootISR_Enable();
}


/*******************************************************************************
* Function Name: BootISR_Stop
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
void BootISR_Stop(void)
{
    /* Disable this interrupt. */
    BootISR_Disable();

    /* Set the ISR to point to the passive one. */
    BootISR_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: BootISR_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for BootISR.
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
CY_ISR(BootISR_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START BootISR_Interrupt` */
    SW1_ClearInterrupt();
    UART_1_UartPutString("Boot\r\n");
    CyDelay(100);    
    Bootloadable_1_Load();
    /* `#END` */
}


/*******************************************************************************
* Function Name: BootISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling BootISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use BootISR_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void BootISR_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + BootISR__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: BootISR_GetVector
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
cyisraddress BootISR_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + BootISR__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: BootISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling BootISR_Start
*   or BootISR_StartEx will override any effect this method would 
*   have had. This method should only be called after BootISR_Start or 
*   BootISR_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void BootISR_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((BootISR__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *BootISR_INTC_PRIOR = (*BootISR_INTC_PRIOR & (uint32)(~BootISR__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: BootISR_GetPriority
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
uint8 BootISR_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((BootISR__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*BootISR_INTC_PRIOR & BootISR__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: BootISR_Enable
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
void BootISR_Enable(void)
{
    /* Enable the general interrupt. */
    *BootISR_INTC_SET_EN = BootISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: BootISR_GetState
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
uint8 BootISR_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*BootISR_INTC_SET_EN & (uint32)BootISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: BootISR_Disable
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
void BootISR_Disable(void)
{
    /* Disable the general interrupt. */
    *BootISR_INTC_CLR_EN = BootISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: BootISR_SetPending
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
void BootISR_SetPending(void)
{
    *BootISR_INTC_SET_PD = BootISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: BootISR_ClearPending
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
void BootISR_ClearPending(void)
{
    *BootISR_INTC_CLR_PD = BootISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
