/*******************************************************************************
* File Name: PPMIN.c  
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
#include "PPMIN.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        PPMIN_PC =   (PPMIN_PC & \
                                (uint32)(~(uint32)(PPMIN_DRIVE_MODE_IND_MASK << (PPMIN_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (PPMIN_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: PPMIN_Write
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
void PPMIN_Write(uint8 value) 
{
    uint8 drVal = (uint8)(PPMIN_DR & (uint8)(~PPMIN_MASK));
    drVal = (drVal | ((uint8)(value << PPMIN_SHIFT) & PPMIN_MASK));
    PPMIN_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: PPMIN_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  PPMIN_DM_STRONG     Strong Drive 
*  PPMIN_DM_OD_HI      Open Drain, Drives High 
*  PPMIN_DM_OD_LO      Open Drain, Drives Low 
*  PPMIN_DM_RES_UP     Resistive Pull Up 
*  PPMIN_DM_RES_DWN    Resistive Pull Down 
*  PPMIN_DM_RES_UPDWN  Resistive Pull Up/Down 
*  PPMIN_DM_DIG_HIZ    High Impedance Digital 
*  PPMIN_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void PPMIN_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(PPMIN__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: PPMIN_Read
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
*  Macro PPMIN_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PPMIN_Read(void) 
{
    return (uint8)((PPMIN_PS & PPMIN_MASK) >> PPMIN_SHIFT);
}


/*******************************************************************************
* Function Name: PPMIN_ReadDataReg
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
uint8 PPMIN_ReadDataReg(void) 
{
    return (uint8)((PPMIN_DR & PPMIN_MASK) >> PPMIN_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PPMIN_INTSTAT) 

    /*******************************************************************************
    * Function Name: PPMIN_ClearInterrupt
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
    uint8 PPMIN_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(PPMIN_INTSTAT & PPMIN_MASK);
		PPMIN_INTSTAT = maskedStatus;
        return maskedStatus >> PPMIN_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
