/*******************************************************************************
* File Name: TelemUART_PM.c
* Version 2.30
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TelemUART.h"


/***************************************
* Local data allocation
***************************************/

static TelemUART_BACKUP_STRUCT  TelemUART_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: TelemUART_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TelemUART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TelemUART_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(TelemUART_CONTROL_REG_REMOVED == 0u)
            TelemUART_backup.cr = TelemUART_CONTROL_REG;
        #endif /* End TelemUART_CONTROL_REG_REMOVED */

        #if( (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED) )
            TelemUART_backup.rx_period = TelemUART_RXBITCTR_PERIOD_REG;
            TelemUART_backup.rx_mask = TelemUART_RXSTATUS_MASK_REG;
            #if (TelemUART_RXHW_ADDRESS_ENABLED)
                TelemUART_backup.rx_addr1 = TelemUART_RXADDRESS1_REG;
                TelemUART_backup.rx_addr2 = TelemUART_RXADDRESS2_REG;
            #endif /* End TelemUART_RXHW_ADDRESS_ENABLED */
        #endif /* End TelemUART_RX_ENABLED | TelemUART_HD_ENABLED*/

        #if(TelemUART_TX_ENABLED)
            #if(TelemUART_TXCLKGEN_DP)
                TelemUART_backup.tx_clk_ctr = TelemUART_TXBITCLKGEN_CTR_REG;
                TelemUART_backup.tx_clk_compl = TelemUART_TXBITCLKTX_COMPLETE_REG;
            #else
                TelemUART_backup.tx_period = TelemUART_TXBITCTR_PERIOD_REG;
            #endif /*End TelemUART_TXCLKGEN_DP */
            TelemUART_backup.tx_mask = TelemUART_TXSTATUS_MASK_REG;
        #endif /*End TelemUART_TX_ENABLED */


    #else /* CY_UDB_V1 */

        #if(TelemUART_CONTROL_REG_REMOVED == 0u)
            TelemUART_backup.cr = TelemUART_CONTROL_REG;
        #endif /* End TelemUART_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: TelemUART_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TelemUART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TelemUART_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(TelemUART_CONTROL_REG_REMOVED == 0u)
            TelemUART_CONTROL_REG = TelemUART_backup.cr;
        #endif /* End TelemUART_CONTROL_REG_REMOVED */

        #if( (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED) )
            TelemUART_RXBITCTR_PERIOD_REG = TelemUART_backup.rx_period;
            TelemUART_RXSTATUS_MASK_REG = TelemUART_backup.rx_mask;
            #if (TelemUART_RXHW_ADDRESS_ENABLED)
                TelemUART_RXADDRESS1_REG = TelemUART_backup.rx_addr1;
                TelemUART_RXADDRESS2_REG = TelemUART_backup.rx_addr2;
            #endif /* End TelemUART_RXHW_ADDRESS_ENABLED */
        #endif  /* End (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED) */

        #if(TelemUART_TX_ENABLED)
            #if(TelemUART_TXCLKGEN_DP)
                TelemUART_TXBITCLKGEN_CTR_REG = TelemUART_backup.tx_clk_ctr;
                TelemUART_TXBITCLKTX_COMPLETE_REG = TelemUART_backup.tx_clk_compl;
            #else
                TelemUART_TXBITCTR_PERIOD_REG = TelemUART_backup.tx_period;
            #endif /*End TelemUART_TXCLKGEN_DP */
            TelemUART_TXSTATUS_MASK_REG = TelemUART_backup.tx_mask;
        #endif /*End TelemUART_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(TelemUART_CONTROL_REG_REMOVED == 0u)
            TelemUART_CONTROL_REG = TelemUART_backup.cr;
        #endif /* End TelemUART_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: TelemUART_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration. Should be called
*  just prior to entering sleep.
*
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TelemUART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TelemUART_Sleep(void)
{

    #if(TelemUART_RX_ENABLED || TelemUART_HD_ENABLED)
        if((TelemUART_RXSTATUS_ACTL_REG  & TelemUART_INT_ENABLE) != 0u)
        {
            TelemUART_backup.enableState = 1u;
        }
        else
        {
            TelemUART_backup.enableState = 0u;
        }
    #else
        if((TelemUART_TXSTATUS_ACTL_REG  & TelemUART_INT_ENABLE) !=0u)
        {
            TelemUART_backup.enableState = 1u;
        }
        else
        {
            TelemUART_backup.enableState = 0u;
        }
    #endif /* End TelemUART_RX_ENABLED || TelemUART_HD_ENABLED*/

    TelemUART_Stop();
    TelemUART_SaveConfig();
}


/*******************************************************************************
* Function Name: TelemUART_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TelemUART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TelemUART_Wakeup(void)
{
    TelemUART_RestoreConfig();
    #if( (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED) )
        TelemUART_ClearRxBuffer();
    #endif /* End (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED) */
    #if(TelemUART_TX_ENABLED || TelemUART_HD_ENABLED)
        TelemUART_ClearTxBuffer();
    #endif /* End TelemUART_TX_ENABLED || TelemUART_HD_ENABLED */

    if(TelemUART_backup.enableState != 0u)
    {
        TelemUART_Enable();
    }
}


/* [] END OF FILE */
