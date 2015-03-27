/*******************************************************************************
* File Name: NavLightPWM_PM.c
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

#include "NavLightPWM.h"

static NavLightPWM_BACKUP_STRUCT NavLightPWM_backup;


/*******************************************************************************
* Function Name: NavLightPWM_SaveConfig
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
void NavLightPWM_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: NavLightPWM_Sleep
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
void NavLightPWM_Sleep(void)
{
    if(0u != (NavLightPWM_BLOCK_CONTROL_REG & NavLightPWM_MASK))
    {
        NavLightPWM_backup.enableState = 1u;
    }
    else
    {
        NavLightPWM_backup.enableState = 0u;
    }

    NavLightPWM_Stop();
    NavLightPWM_SaveConfig();
}


/*******************************************************************************
* Function Name: NavLightPWM_RestoreConfig
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
void NavLightPWM_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: NavLightPWM_Wakeup
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
void NavLightPWM_Wakeup(void)
{
    NavLightPWM_RestoreConfig();

    if(0u != NavLightPWM_backup.enableState)
    {
        NavLightPWM_Enable();
    }
}


/* [] END OF FILE */
