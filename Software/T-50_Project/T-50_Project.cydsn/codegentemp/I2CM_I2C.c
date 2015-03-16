/*******************************************************************************
* File Name: I2CM_I2C.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "I2CM_PVT.h"
#include "I2CM_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 I2CM_state;  /* Current state of I2C FSM */


#if(I2CM_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Config Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const I2CM_I2C_INIT_STRUCT I2CM_configI2C =
    {
        I2CM_I2C_MODE,
        I2CM_I2C_OVS_FACTOR_LOW,
        I2CM_I2C_OVS_FACTOR_HIGH,
        I2CM_I2C_MEDIAN_FILTER_ENABLE,
        I2CM_I2C_SLAVE_ADDRESS,
        I2CM_I2C_SLAVE_ADDRESS_MASK,
        I2CM_I2C_ACCEPT_ADDRESS,
        I2CM_I2C_WAKE_ENABLE
    };

    /*******************************************************************************
    * Function Name: I2CM_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for I2C operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void I2CM_I2CInit(const I2CM_I2C_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due bad function parameter */
        }
        else
        {
            /* Configure pins */
            I2CM_SetPins(I2CM_SCB_MODE_I2C, I2CM_DUMMY_PARAM,
                                                                    I2CM_DUMMY_PARAM);

            /* Store internal configuration */
            I2CM_scbMode       = (uint8) I2CM_SCB_MODE_I2C;
            I2CM_scbEnableWake = (uint8) config->enableWake;
            I2CM_scbEnableIntr = (uint8) I2CM_SCB_IRQ_INTERNAL;

            I2CM_mode          = (uint8) config->mode;
            I2CM_acceptAddr    = (uint8) config->acceptAddr;

            /* Configure I2C interface */
            I2CM_CTRL_REG     = I2CM_GET_CTRL_ADDR_ACCEPT(config->acceptAddr) |
                                            I2CM_GET_CTRL_EC_AM_MODE (config->enableWake);

            I2CM_I2C_CTRL_REG = I2CM_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                                            I2CM_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)  |
                                            I2CM_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode)           |
                                            I2CM_I2C_CTRL;

        #if(I2CM_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            I2CM_SET_I2C_CFG_SDA_FILT_TRIM(I2CM_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (I2CM_CY_SCBIP_V0) */

            /* Configure RX direction */
            I2CM_RX_CTRL_REG      = I2CM_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                I2CM_I2C_RX_CTRL;
            I2CM_RX_FIFO_CTRL_REG = I2CM_CLEAR_REG;

            /* Set default address and mask */
            I2CM_RX_MATCH_REG    = ((I2CM_I2C_SLAVE) ?
                                                (I2CM_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 I2CM_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (I2CM_CLEAR_REG));


            /* Configure TX direction */
            I2CM_TX_CTRL_REG      = I2CM_I2C_TX_CTRL;
            I2CM_TX_FIFO_CTRL_REG = I2CM_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (I2CM_ISR_NUMBER);
            CyIntSetPriority(I2CM_ISR_NUMBER, I2CM_ISR_PRIORITY);
            (void) CyIntSetVector(I2CM_ISR_NUMBER, &I2CM_I2C_ISR);

            /* Configure interrupt sources */
        #if(!I2CM_CY_SCBIP_V1_I2C_ONLY)
            I2CM_INTR_SPI_EC_MASK_REG = I2CM_NO_INTR_SOURCES;
        #endif /* (!I2CM_CY_SCBIP_V1_I2C_ONLY) */

            I2CM_INTR_I2C_EC_MASK_REG = I2CM_NO_INTR_SOURCES;
            I2CM_INTR_RX_MASK_REG     = I2CM_NO_INTR_SOURCES;
            I2CM_INTR_TX_MASK_REG     = I2CM_NO_INTR_SOURCES;

            I2CM_INTR_SLAVE_MASK_REG  = ((I2CM_I2C_SLAVE) ?
                                                     (I2CM_I2C_INTR_SLAVE_MASK) :
                                                     (I2CM_CLEAR_REG));

            I2CM_INTR_MASTER_MASK_REG = ((I2CM_I2C_MASTER) ?
                                                     (I2CM_I2C_INTR_MASTER_MASK) :
                                                     (I2CM_CLEAR_REG));

            /* Configure global variables */
            I2CM_state = I2CM_I2C_FSM_IDLE;

            /* Internal slave variables */
            I2CM_slStatus        = 0u;
            I2CM_slRdBufIndex    = 0u;
            I2CM_slWrBufIndex    = 0u;
            I2CM_slOverFlowCount = 0u;

            /* Internal master variables */
            I2CM_mstrStatus     = 0u;
            I2CM_mstrRdBufIndex = 0u;
            I2CM_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: I2CM_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the I2C operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void I2CM_I2CInit(void)
    {
        /* Configure I2C interface */
        I2CM_CTRL_REG     = I2CM_I2C_DEFAULT_CTRL;
        I2CM_I2C_CTRL_REG = I2CM_I2C_DEFAULT_I2C_CTRL;

    #if(I2CM_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        I2CM_SET_I2C_CFG_SDA_FILT_TRIM(I2CM_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (I2CM_CY_SCBIP_V0) */

        /* Configure RX direction */
        I2CM_RX_CTRL_REG      = I2CM_I2C_DEFAULT_RX_CTRL;
        I2CM_RX_FIFO_CTRL_REG = I2CM_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        I2CM_RX_MATCH_REG     = I2CM_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        I2CM_TX_CTRL_REG      = I2CM_I2C_DEFAULT_TX_CTRL;
        I2CM_TX_FIFO_CTRL_REG = I2CM_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (I2CM_ISR_NUMBER);
        CyIntSetPriority(I2CM_ISR_NUMBER, I2CM_ISR_PRIORITY);
    #if(!I2CM_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(I2CM_ISR_NUMBER, &I2CM_I2C_ISR);
    #endif /* (I2CM_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!I2CM_CY_SCBIP_V1_I2C_ONLY)
        I2CM_INTR_SPI_EC_MASK_REG = I2CM_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!I2CM_CY_SCBIP_V1_I2C_ONLY) */

        I2CM_INTR_I2C_EC_MASK_REG = I2CM_I2C_DEFAULT_INTR_I2C_EC_MASK;
        I2CM_INTR_SLAVE_MASK_REG  = I2CM_I2C_DEFAULT_INTR_SLAVE_MASK;
        I2CM_INTR_MASTER_MASK_REG = I2CM_I2C_DEFAULT_INTR_MASTER_MASK;
        I2CM_INTR_RX_MASK_REG     = I2CM_I2C_DEFAULT_INTR_RX_MASK;
        I2CM_INTR_TX_MASK_REG     = I2CM_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        I2CM_state = I2CM_I2C_FSM_IDLE;

    #if(I2CM_I2C_SLAVE)
        /* Internal slave variable */
        I2CM_slStatus        = 0u;
        I2CM_slRdBufIndex    = 0u;
        I2CM_slWrBufIndex    = 0u;
        I2CM_slOverFlowCount = 0u;
    #endif /* (I2CM_I2C_SLAVE) */

    #if(I2CM_I2C_MASTER)
    /* Internal master variable */
        I2CM_mstrStatus     = 0u;
        I2CM_mstrRdBufIndex = 0u;
        I2CM_mstrWrBufIndex = 0u;
    #endif /* (I2CM_I2C_MASTER) */
    }
#endif /* (I2CM_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: I2CM_I2CStop
********************************************************************************
*
* Summary:
*  Resets the I2C FSM into the default state and disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*
*
*******************************************************************************/
void I2CM_I2CStop(void)
{
    /* Disable TX interrupt sources in order not to cause a false trigger.
    * The incoming transaction will enable an appropriate TX interrupt.
    */
    I2CM_SetTxInterruptMode(I2CM_NO_INTR_SOURCES);

#if(I2CM_CY_SCBIP_V0)
    /* Clear pending interrupt as TX FIFO becomes empty and block does not gate interrupt trigger when disabled */
    I2CM_ClearPendingInt();
#endif /* (I2CM_CY_SCBIP_V0) */

    I2CM_state = I2CM_I2C_FSM_IDLE;
}


#if(I2CM_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: I2CM_I2CSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Enables I2CM_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void I2CM_I2CSaveConfig(void)
    {
        I2CM_SetI2CExtClkInterruptMode(I2CM_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: I2CM_I2CRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Added for compatibility.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void I2CM_I2CRestoreConfig(void)
    {
        /* I2CM_INTR_I2C_EC_WAKE_UP is masked-off in the interrupt */
    }
#endif /* (I2CM_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
