/*******************************************************************************
* File Name: SpareLight.c  
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
#include "SpareLight.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        SpareLight_PC =   (SpareLight_PC & \
                                (uint32)(~(uint32)(SpareLight_DRIVE_MODE_IND_MASK << (SpareLight_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (SpareLight_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: SpareLight_Write
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
void SpareLight_Write(uint8 value) 
{
    uint8 drVal = (uint8)(SpareLight_DR & (uint8)(~SpareLight_MASK));
    drVal = (drVal | ((uint8)(value << SpareLight_SHIFT) & SpareLight_MASK));
    SpareLight_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: SpareLight_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  SpareLight_DM_STRONG     Strong Drive 
*  SpareLight_DM_OD_HI      Open Drain, Drives High 
*  SpareLight_DM_OD_LO      Open Drain, Drives Low 
*  SpareLight_DM_RES_UP     Resistive Pull Up 
*  SpareLight_DM_RES_DWN    Resistive Pull Down 
*  SpareLight_DM_RES_UPDWN  Resistive Pull Up/Down 
*  SpareLight_DM_DIG_HIZ    High Impedance Digital 
*  SpareLight_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void SpareLight_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(SpareLight__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: SpareLight_Read
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
*  Macro SpareLight_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SpareLight_Read(void) 
{
    return (uint8)((SpareLight_PS & SpareLight_MASK) >> SpareLight_SHIFT);
}


/*******************************************************************************
* Function Name: SpareLight_ReadDataReg
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
uint8 SpareLight_ReadDataReg(void) 
{
    return (uint8)((SpareLight_DR & SpareLight_MASK) >> SpareLight_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SpareLight_INTSTAT) 

    /*******************************************************************************
    * Function Name: SpareLight_ClearInterrupt
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
    uint8 SpareLight_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(SpareLight_INTSTAT & SpareLight_MASK);
		SpareLight_INTSTAT = maskedStatus;
        return maskedStatus >> SpareLight_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
