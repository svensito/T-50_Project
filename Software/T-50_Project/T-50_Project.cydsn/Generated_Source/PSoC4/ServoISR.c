/*******************************************************************************
* File Name: ServoISR.c  
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
#include <ServoISR.h>

#if !defined(ServoISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START ServoISR_intc` */
#include <project.h>
extern uint16_t ctrl_in[];
extern uint16_t ctrl_out[];
uint8_t PWM_channel = 0;    // the PWM output channel

/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: ServoISR_Start
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
void ServoISR_Start(void)
{
    /* For all we know the interrupt is active. */
    ServoISR_Disable();

    /* Set the ISR to point to the ServoISR Interrupt. */
    ServoISR_SetVector(&ServoISR_Interrupt);

    /* Set the priority. */
    ServoISR_SetPriority((uint8)ServoISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ServoISR_Enable();
}


/*******************************************************************************
* Function Name: ServoISR_StartEx
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
void ServoISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    ServoISR_Disable();

    /* Set the ISR to point to the ServoISR Interrupt. */
    ServoISR_SetVector(address);

    /* Set the priority. */
    ServoISR_SetPriority((uint8)ServoISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ServoISR_Enable();
}


/*******************************************************************************
* Function Name: ServoISR_Stop
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
void ServoISR_Stop(void)
{
    /* Disable this interrupt. */
    ServoISR_Disable();

    /* Set the ISR to point to the passive one. */
    ServoISR_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: ServoISR_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for ServoISR.
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
CY_ISR(ServoISR_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START ServoISR_Interrupt` */
    ServoTimer_ClearInterrupt(ServoTimer_INTR_MASK_TC);
    switch (PWM_channel)
    {
        case 0:
            // Set the Pin of output 12 to low
            Out_Sp2_Pin_Write(0x00);
            // Set the Pin of output 0 to high
            Out_Mot_Pin_Write(0xFF);
            
            ServoTimer_WritePeriod(ctrl_out[PWM_channel]);    // mot
        break;
        
        case 1:
            // Set the Pin of output 0 to low
            Out_Mot_Pin_Write(0x00);
            // Set the Pin of output 1 to high
            Out_Ail1_Pin_Write(0xFF);                         // ail1
            ServoTimer_WritePeriod(ctrl_out[PWM_channel]);    
        break;
            
        case 2:
            // Set the Pin of output 1 to low
            Out_Ail1_Pin_Write(0x00);
            // Set the Pin of output 2 to high
            Out_Ail2_Pin_Write(0xFF);                          // ail2
            ServoTimer_WritePeriod(ctrl_out[PWM_channel]);    
        break;    
       
        case 3:
            // Set the Pin of output 2 to low
            Out_Ail2_Pin_Write(0x00);
            // Set the Pin of output 3 to high
            Out_Ele1_Pin_Write(0xFF);
            // Set Timer Value to next output
            ServoTimer_WritePeriod(ctrl_out[PWM_channel]);    
        break; 
        
        case 4:
            // Set the Pin of output 3 to low
            Out_Ele1_Pin_Write(0x00);
            // Set the Pin of output 4 to high
            Out_Ele2_Pin_Write(0xFF);
            ServoTimer_WritePeriod(ctrl_out[PWM_channel]);    
        break; 
        
        case 5:
            // Set the Pin of output 4 to low
            Out_Ele2_Pin_Write(0x00);
            // Set the Pin of output 5 to high
            Out_Rud_Pin_Write(0xFF);
            ServoTimer_WritePeriod(ctrl_out[PWM_channel]);    
        break; 
        
        case 6:
            // Set the Pin of output 5 to low
            Out_Rud_Pin_Write(0x00);
            // Set the Pin of output 6 to high
            Out_Fl1_Pin_Write(0xFF);
            ServoTimer_WritePeriod(ctrl_out[PWM_channel]); 
        break; 
        
        case 7:
            // Set the Pin of output 6 to low
            Out_Fl1_Pin_Write(0x00);
            // Set the Pin of output 7 to high
            Out_Fl2_Pin_Write(0xFF);
            ServoTimer_WritePeriod(ctrl_out[PWM_channel]);
        break; 
        
        case 8:
            // Set the Pin of output 7 to low
            Out_Fl2_Pin_Write(0x00);
            // Set the Pin of output 8 to high
            Out_Ge1_Pin_Write(0xFF);
            ServoTimer_WritePeriod(ctrl_out[PWM_channel]);
        break; 
        
        case 9:
            // Set the Pin of output 8 to low
            Out_Ge1_Pin_Write(0x00);
            // Set the Pin of output 9 to high
            Out_Ge2_Pin_Write(0xFF);
            ServoTimer_WritePeriod(ctrl_out[PWM_channel]);
        break; 
        
        case 10:
            // Set the Pin of output 9 to low
            Out_Ge2_Pin_Write(0x00);
            // Set the Pin of output 10 to high
            Out_Ge3_Pin_Write(0xFF);
            ServoTimer_WritePeriod(ctrl_out[PWM_channel]);
        break; 
        
        case 11:
            // Set the Pin of output 10 to low
            Out_Ge3_Pin_Write(0x00);
            // Set the Pin of output 11 to high
            Out_Sp1_Pin_Write(0xFF);
            ServoTimer_WritePeriod(ctrl_out[PWM_channel]);
        break; 
        
        case 12:
            // Set the Pin of output 11 to low
            Out_Sp1_Pin_Write(0x00);
            // Set the Pin of output 0 to high
            Out_Sp2_Pin_Write(0xFF);
            ServoTimer_WritePeriod(ctrl_out[PWM_channel]);
        break; 
        
    }
    
    ServoTimer_WriteCounter(0); // Reset the counter
    PWM_channel++;
    if(PWM_channel == 13) PWM_channel = 0;
    /* `#END` */
}


/*******************************************************************************
* Function Name: ServoISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling ServoISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use ServoISR_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void ServoISR_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + ServoISR__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: ServoISR_GetVector
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
cyisraddress ServoISR_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + ServoISR__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: ServoISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling ServoISR_Start
*   or ServoISR_StartEx will override any effect this method would 
*   have had. This method should only be called after ServoISR_Start or 
*   ServoISR_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void ServoISR_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((ServoISR__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *ServoISR_INTC_PRIOR = (*ServoISR_INTC_PRIOR & (uint32)(~ServoISR__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: ServoISR_GetPriority
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
uint8 ServoISR_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((ServoISR__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*ServoISR_INTC_PRIOR & ServoISR__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: ServoISR_Enable
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
void ServoISR_Enable(void)
{
    /* Enable the general interrupt. */
    *ServoISR_INTC_SET_EN = ServoISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: ServoISR_GetState
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
uint8 ServoISR_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*ServoISR_INTC_SET_EN & (uint32)ServoISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: ServoISR_Disable
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
void ServoISR_Disable(void)
{
    /* Disable the general interrupt. */
    *ServoISR_INTC_CLR_EN = ServoISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: ServoISR_SetPending
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
void ServoISR_SetPending(void)
{
    *ServoISR_INTC_SET_PD = ServoISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: ServoISR_ClearPending
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
void ServoISR_ClearPending(void)
{
    *ServoISR_INTC_CLR_PD = ServoISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
