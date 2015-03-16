/*******************************************************************************
* File Name: NavB.c  
* Version 2.5
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "NavB.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        NavB_PC =   (NavB_PC & \
                                (uint32)(~(uint32)(NavB_DRIVE_MODE_IND_MASK << (NavB_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (NavB_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: NavB_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void NavB_Write(uint8 value) 
{
    uint8 drVal = (uint8)(NavB_DR & (uint8)(~NavB_MASK));
    drVal = (drVal | ((uint8)(value << NavB_SHIFT) & NavB_MASK));
    NavB_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: NavB_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  NavB_DM_STRONG     Strong Drive 
*  NavB_DM_OD_HI      Open Drain, Drives High 
*  NavB_DM_OD_LO      Open Drain, Drives Low 
*  NavB_DM_RES_UP     Resistive Pull Up 
*  NavB_DM_RES_DWN    Resistive Pull Down 
*  NavB_DM_RES_UPDWN  Resistive Pull Up/Down 
*  NavB_DM_DIG_HIZ    High Impedance Digital 
*  NavB_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void NavB_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(NavB__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: NavB_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro NavB_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 NavB_Read(void) 
{
    return (uint8)((NavB_PS & NavB_MASK) >> NavB_SHIFT);
}


/*******************************************************************************
* Function Name: NavB_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 NavB_ReadDataReg(void) 
{
    return (uint8)((NavB_DR & NavB_MASK) >> NavB_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(NavB_INTSTAT) 

    /*******************************************************************************
    * Function Name: NavB_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 NavB_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(NavB_INTSTAT & NavB_MASK);
		NavB_INTSTAT = maskedStatus;
        return maskedStatus >> NavB_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
