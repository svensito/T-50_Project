/*******************************************************************************
* File Name: ServoTimer_PM.c
* Version 2.0
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ServoTimer.h"

static ServoTimer_BACKUP_STRUCT ServoTimer_backup;


/*******************************************************************************
* Function Name: ServoTimer_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: ServoTimer_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_Sleep(void)
{
    if(0u != (ServoTimer_BLOCK_CONTROL_REG & ServoTimer_MASK))
    {
        ServoTimer_backup.enableState = 1u;
    }
    else
    {
        ServoTimer_backup.enableState = 0u;
    }

    ServoTimer_Stop();
    ServoTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: ServoTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: ServoTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ServoTimer_Wakeup(void)
{
    ServoTimer_RestoreConfig();

    if(0u != ServoTimer_backup.enableState)
    {
        ServoTimer_Enable();
    }
}


/* [] END OF FILE */
