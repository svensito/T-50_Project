/*******************************************************************************
* File Name: Ldg.c  
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
#include "Ldg.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Ldg_PC =   (Ldg_PC & \
                                (uint32)(~(uint32)(Ldg_DRIVE_MODE_IND_MASK << (Ldg_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Ldg_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Ldg_Write
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
void Ldg_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Ldg_DR & (uint8)(~Ldg_MASK));
    drVal = (drVal | ((uint8)(value << Ldg_SHIFT) & Ldg_MASK));
    Ldg_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Ldg_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Ldg_DM_STRONG     Strong Drive 
*  Ldg_DM_OD_HI      Open Drain, Drives High 
*  Ldg_DM_OD_LO      Open Drain, Drives Low 
*  Ldg_DM_RES_UP     Resistive Pull Up 
*  Ldg_DM_RES_DWN    Resistive Pull Down 
*  Ldg_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Ldg_DM_DIG_HIZ    High Impedance Digital 
*  Ldg_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Ldg_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Ldg__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Ldg_Read
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
*  Macro Ldg_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Ldg_Read(void) 
{
    return (uint8)((Ldg_PS & Ldg_MASK) >> Ldg_SHIFT);
}


/*******************************************************************************
* Function Name: Ldg_ReadDataReg
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
uint8 Ldg_ReadDataReg(void) 
{
    return (uint8)((Ldg_DR & Ldg_MASK) >> Ldg_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Ldg_INTSTAT) 

    /*******************************************************************************
    * Function Name: Ldg_ClearInterrupt
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
    uint8 Ldg_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Ldg_INTSTAT & Ldg_MASK);
		Ldg_INTSTAT = maskedStatus;
        return maskedStatus >> Ldg_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
