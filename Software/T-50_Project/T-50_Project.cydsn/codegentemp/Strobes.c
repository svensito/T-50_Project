/*******************************************************************************
* File Name: Strobes.c  
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
#include "Strobes.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Strobes_PC =   (Strobes_PC & \
                                (uint32)(~(uint32)(Strobes_DRIVE_MODE_IND_MASK << (Strobes_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Strobes_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Strobes_Write
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
void Strobes_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Strobes_DR & (uint8)(~Strobes_MASK));
    drVal = (drVal | ((uint8)(value << Strobes_SHIFT) & Strobes_MASK));
    Strobes_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Strobes_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Strobes_DM_STRONG     Strong Drive 
*  Strobes_DM_OD_HI      Open Drain, Drives High 
*  Strobes_DM_OD_LO      Open Drain, Drives Low 
*  Strobes_DM_RES_UP     Resistive Pull Up 
*  Strobes_DM_RES_DWN    Resistive Pull Down 
*  Strobes_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Strobes_DM_DIG_HIZ    High Impedance Digital 
*  Strobes_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Strobes_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Strobes__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Strobes_Read
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
*  Macro Strobes_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Strobes_Read(void) 
{
    return (uint8)((Strobes_PS & Strobes_MASK) >> Strobes_SHIFT);
}


/*******************************************************************************
* Function Name: Strobes_ReadDataReg
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
uint8 Strobes_ReadDataReg(void) 
{
    return (uint8)((Strobes_DR & Strobes_MASK) >> Strobes_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Strobes_INTSTAT) 

    /*******************************************************************************
    * Function Name: Strobes_ClearInterrupt
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
    uint8 Strobes_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Strobes_INTSTAT & Strobes_MASK);
		Strobes_INTSTAT = maskedStatus;
        return maskedStatus >> Strobes_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
