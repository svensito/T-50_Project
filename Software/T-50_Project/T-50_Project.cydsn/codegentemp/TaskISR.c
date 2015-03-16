/*******************************************************************************
* File Name: TaskISR.c  
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
#include <TaskISR.h>

#if !defined(TaskISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START TaskISR_intc` */

    #include <project.h>
    extern uint8_t task_flag;
/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: TaskISR_Start
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
void TaskISR_Start(void)
{
    /* For all we know the interrupt is active. */
    TaskISR_Disable();

    /* Set the ISR to point to the TaskISR Interrupt. */
    TaskISR_SetVector(&TaskISR_Interrupt);

    /* Set the priority. */
    TaskISR_SetPriority((uint8)TaskISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    TaskISR_Enable();
}


/*******************************************************************************
* Function Name: TaskISR_StartEx
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
void TaskISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    TaskISR_Disable();

    /* Set the ISR to point to the TaskISR Interrupt. */
    TaskISR_SetVector(address);

    /* Set the priority. */
    TaskISR_SetPriority((uint8)TaskISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    TaskISR_Enable();
}


/*******************************************************************************
* Function Name: TaskISR_Stop
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
void TaskISR_Stop(void)
{
    /* Disable this interrupt. */
    TaskISR_Disable();

    /* Set the ISR to point to the passive one. */
    TaskISR_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: TaskISR_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for TaskISR.
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
CY_ISR(TaskISR_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START TaskISR_Interrupt` */
    TaskTimer_ClearInterrupt(TaskTimer__INTR_MASK_TC);
    task_flag = 1;
    /* `#END` */
}


/*******************************************************************************
* Function Name: TaskISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling TaskISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use TaskISR_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void TaskISR_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + TaskISR__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: TaskISR_GetVector
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
cyisraddress TaskISR_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + TaskISR__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: TaskISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling TaskISR_Start
*   or TaskISR_StartEx will override any effect this method would 
*   have had. This method should only be called after TaskISR_Start or 
*   TaskISR_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void TaskISR_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((TaskISR__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *TaskISR_INTC_PRIOR = (*TaskISR_INTC_PRIOR & (uint32)(~TaskISR__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: TaskISR_GetPriority
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
uint8 TaskISR_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((TaskISR__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*TaskISR_INTC_PRIOR & TaskISR__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: TaskISR_Enable
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
void TaskISR_Enable(void)
{
    /* Enable the general interrupt. */
    *TaskISR_INTC_SET_EN = TaskISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: TaskISR_GetState
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
uint8 TaskISR_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*TaskISR_INTC_SET_EN & (uint32)TaskISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: TaskISR_Disable
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
void TaskISR_Disable(void)
{
    /* Disable the general interrupt. */
    *TaskISR_INTC_CLR_EN = TaskISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: TaskISR_SetPending
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
void TaskISR_SetPending(void)
{
    *TaskISR_INTC_SET_PD = TaskISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: TaskISR_ClearPending
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
void TaskISR_ClearPending(void)
{
    *TaskISR_INTC_CLR_PD = TaskISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
