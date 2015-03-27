/*******************************************************************************
* File Name: Out_Ele2_Pin.c  
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
#include "Out_Ele2_Pin.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Out_Ele2_Pin_PC =   (Out_Ele2_Pin_PC & \
                                (uint32)(~(uint32)(Out_Ele2_Pin_DRIVE_MODE_IND_MASK << (Out_Ele2_Pin_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Out_Ele2_Pin_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Out_Ele2_Pin_Write
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
void Out_Ele2_Pin_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Out_Ele2_Pin_DR & (uint8)(~Out_Ele2_Pin_MASK));
    drVal = (drVal | ((uint8)(value << Out_Ele2_Pin_SHIFT) & Out_Ele2_Pin_MASK));
    Out_Ele2_Pin_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Out_Ele2_Pin_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Out_Ele2_Pin_DM_STRONG     Strong Drive 
*  Out_Ele2_Pin_DM_OD_HI      Open Drain, Drives High 
*  Out_Ele2_Pin_DM_OD_LO      Open Drain, Drives Low 
*  Out_Ele2_Pin_DM_RES_UP     Resistive Pull Up 
*  Out_Ele2_Pin_DM_RES_DWN    Resistive Pull Down 
*  Out_Ele2_Pin_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Out_Ele2_Pin_DM_DIG_HIZ    High Impedance Digital 
*  Out_Ele2_Pin_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Out_Ele2_Pin_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Out_Ele2_Pin__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Out_Ele2_Pin_Read
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
*  Macro Out_Ele2_Pin_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Out_Ele2_Pin_Read(void) 
{
    return (uint8)((Out_Ele2_Pin_PS & Out_Ele2_Pin_MASK) >> Out_Ele2_Pin_SHIFT);
}


/*******************************************************************************
* Function Name: Out_Ele2_Pin_ReadDataReg
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
uint8 Out_Ele2_Pin_ReadDataReg(void) 
{
    return (uint8)((Out_Ele2_Pin_DR & Out_Ele2_Pin_MASK) >> Out_Ele2_Pin_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Out_Ele2_Pin_INTSTAT) 

    /*******************************************************************************
    * Function Name: Out_Ele2_Pin_ClearInterrupt
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
    uint8 Out_Ele2_Pin_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Out_Ele2_Pin_INTSTAT & Out_Ele2_Pin_MASK);
		Out_Ele2_Pin_INTSTAT = maskedStatus;
        return maskedStatus >> Out_Ele2_Pin_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
