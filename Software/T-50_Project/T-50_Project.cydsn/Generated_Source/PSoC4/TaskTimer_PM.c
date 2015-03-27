/*******************************************************************************
* File Name: TaskTimer_PM.c
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

#include "TaskTimer.h"

static TaskTimer_BACKUP_STRUCT TaskTimer_backup;


/*******************************************************************************
* Function Name: TaskTimer_SaveConfig
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
void TaskTimer_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: TaskTimer_Sleep
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
void TaskTimer_Sleep(void)
{
    if(0u != (TaskTimer_BLOCK_CONTROL_REG & TaskTimer_MASK))
    {
        TaskTimer_backup.enableState = 1u;
    }
    else
    {
        TaskTimer_backup.enableState = 0u;
    }

    TaskTimer_Stop();
    TaskTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: TaskTimer_RestoreConfig
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
void TaskTimer_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: TaskTimer_Wakeup
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
void TaskTimer_Wakeup(void)
{
    TaskTimer_RestoreConfig();

    if(0u != TaskTimer_backup.enableState)
    {
        TaskTimer_Enable();
    }
}


/* [] END OF FILE */
