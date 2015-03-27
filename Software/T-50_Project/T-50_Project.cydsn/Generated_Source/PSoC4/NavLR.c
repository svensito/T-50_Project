/*******************************************************************************
* File Name: NavLR.c  
* Version 2.10
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
#include "NavLR.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        NavLR_PC =   (NavLR_PC & \
                                (uint32)(~(uint32)(NavLR_DRIVE_MODE_IND_MASK << (NavLR_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (NavLR_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: NavLR_Write
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
void NavLR_Write(uint8 value) 
{
    uint8 drVal = (uint8)(NavLR_DR & (uint8)(~NavLR_MASK));
    drVal = (drVal | ((uint8)(value << NavLR_SHIFT) & NavLR_MASK));
    NavLR_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: NavLR_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  NavLR_DM_STRONG     Strong Drive 
*  NavLR_DM_OD_HI      Open Drain, Drives High 
*  NavLR_DM_OD_LO      Open Drain, Drives Low 
*  NavLR_DM_RES_UP     Resistive Pull Up 
*  NavLR_DM_RES_DWN    Resistive Pull Down 
*  NavLR_DM_RES_UPDWN  Resistive Pull Up/Down 
*  NavLR_DM_DIG_HIZ    High Impedance Digital 
*  NavLR_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void NavLR_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(NavLR__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: NavLR_Read
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
*  Macro NavLR_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 NavLR_Read(void) 
{
    return (uint8)((NavLR_PS & NavLR_MASK) >> NavLR_SHIFT);
}


/*******************************************************************************
* Function Name: NavLR_ReadDataReg
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
uint8 NavLR_ReadDataReg(void) 
{
    return (uint8)((NavLR_DR & NavLR_MASK) >> NavLR_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(NavLR_INTSTAT) 

    /*******************************************************************************
    * Function Name: NavLR_ClearInterrupt
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
    uint8 NavLR_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(NavLR_INTSTAT & NavLR_MASK);
		NavLR_INTSTAT = maskedStatus;
        return maskedStatus >> NavLR_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
