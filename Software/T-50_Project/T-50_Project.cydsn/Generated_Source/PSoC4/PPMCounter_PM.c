/*******************************************************************************
* File Name: PPMCounter_PM.c
* Version 1.10
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

#include "PPMCounter.h"

static PPMCounter_BACKUP_STRUCT PPMCounter_backup;


/*******************************************************************************
* Function Name: PPMCounter_SaveConfig
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
void PPMCounter_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: PPMCounter_Sleep
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
void PPMCounter_Sleep(void)
{
    if(0u != (PPMCounter_BLOCK_CONTROL_REG & PPMCounter_MASK))
    {
        PPMCounter_backup.enableState = 1u;
    }
    else
    {
        PPMCounter_backup.enableState = 0u;
    }

    PPMCounter_Stop();
    PPMCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: PPMCounter_RestoreConfig
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
void PPMCounter_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: PPMCounter_Wakeup
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
void PPMCounter_Wakeup(void)
{
    PPMCounter_RestoreConfig();

    if(0u != PPMCounter_backup.enableState)
    {
        PPMCounter_Enable();
    }
}


/* [] END OF FILE */
