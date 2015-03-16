/*******************************************************************************
* File Name: Collis.c  
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
#include "Collis.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Collis_PC =   (Collis_PC & \
                                (uint32)(~(uint32)(Collis_DRIVE_MODE_IND_MASK << (Collis_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Collis_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Collis_Write
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
void Collis_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Collis_DR & (uint8)(~Collis_MASK));
    drVal = (drVal | ((uint8)(value << Collis_SHIFT) & Collis_MASK));
    Collis_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Collis_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Collis_DM_STRONG     Strong Drive 
*  Collis_DM_OD_HI      Open Drain, Drives High 
*  Collis_DM_OD_LO      Open Drain, Drives Low 
*  Collis_DM_RES_UP     Resistive Pull Up 
*  Collis_DM_RES_DWN    Resistive Pull Down 
*  Collis_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Collis_DM_DIG_HIZ    High Impedance Digital 
*  Collis_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Collis_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Collis__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Collis_Read
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
*  Macro Collis_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Collis_Read(void) 
{
    return (uint8)((Collis_PS & Collis_MASK) >> Collis_SHIFT);
}


/*******************************************************************************
* Function Name: Collis_ReadDataReg
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
uint8 Collis_ReadDataReg(void) 
{
    return (uint8)((Collis_DR & Collis_MASK) >> Collis_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Collis_INTSTAT) 

    /*******************************************************************************
    * Function Name: Collis_ClearInterrupt
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
    uint8 Collis_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Collis_INTSTAT & Collis_MASK);
		Collis_INTSTAT = maskedStatus;
        return maskedStatus >> Collis_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
