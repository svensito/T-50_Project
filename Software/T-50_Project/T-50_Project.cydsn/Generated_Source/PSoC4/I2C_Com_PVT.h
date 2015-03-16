/*******************************************************************************
* File Name: .h
* Version 1.20
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_I2C_Com_H)
#define CY_SCB_PVT_I2C_Com_H

#include "I2C_Com.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define I2C_Com_SetI2CExtClkInterruptMode(interruptMask) I2C_Com_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define I2C_Com_ClearI2CExtClkInterruptSource(interruptMask) I2C_Com_CLEAR_INTR_I2C_EC(interruptMask)
#define I2C_Com_GetI2CExtClkInterruptSource()                (I2C_Com_INTR_I2C_EC_REG)
#define I2C_Com_GetI2CExtClkInterruptMode()                  (I2C_Com_INTR_I2C_EC_MASK_REG)
#define I2C_Com_GetI2CExtClkInterruptSourceMasked()          (I2C_Com_INTR_I2C_EC_MASKED_REG)

#if(!I2C_Com_CY_SCBIP_V1_I2C_ONLY)
/* APIs to service INTR_SPI_EC register */
#define I2C_Com_SetSpiExtClkInterruptMode(interruptMask) I2C_Com_WRITE_INTR_SPI_EC_MASK(interruptMask)
#define I2C_Com_ClearSpiExtClkInterruptSource(interruptMask) I2C_Com_CLEAR_INTR_SPI_EC(interruptMask)
#define I2C_Com_GetExtSpiClkInterruptSource()                 (I2C_Com_INTR_SPI_EC_REG)
#define I2C_Com_GetExtSpiClkInterruptMode()                   (I2C_Com_INTR_SPI_EC_MASK_REG)
#define I2C_Com_GetExtSpiClkInterruptSourceMasked()           (I2C_Com_INTR_SPI_EC_MASKED_REG)
#endif /* (!I2C_Com_CY_SCBIP_V1_I2C_ONLY) */

#if(I2C_Com_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void I2C_Com_SetPins(uint32 mode, uint32 subMode, uint32 uartTxRx);
#endif /* (I2C_Com_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if !defined (CY_REMOVE_I2C_Com_CUSTOM_INTR_HANDLER)
    extern cyisraddress I2C_Com_customIntrHandler;
#endif /* !defined (CY_REMOVE_I2C_Com_CUSTOM_INTR_HANDLER) */

extern I2C_Com_BACKUP_STRUCT I2C_Com_backup;

#if(I2C_Com_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common config vars */
    extern uint8 I2C_Com_scbMode;
    extern uint8 I2C_Com_scbEnableWake;
    extern uint8 I2C_Com_scbEnableIntr;

    /* I2C config vars */
    extern uint8 I2C_Com_mode;
    extern uint8 I2C_Com_acceptAddr;

    /* SPI/UART config vars */
    extern volatile uint8 * I2C_Com_rxBuffer;
    extern uint8   I2C_Com_rxDataBits;
    extern uint32  I2C_Com_rxBufferSize;

    extern volatile uint8 * I2C_Com_txBuffer;
    extern uint8   I2C_Com_txDataBits;
    extern uint32  I2C_Com_txBufferSize;

    /* EZI2C config vars */
    extern uint8 I2C_Com_numberOfAddr;
    extern uint8 I2C_Com_subAddrSize;
#endif /* (I2C_Com_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*  Conditional Macro
****************************************/

#if(I2C_Com_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Define run time operation mode */
    #define I2C_Com_SCB_MODE_I2C_RUNTM_CFG     (I2C_Com_SCB_MODE_I2C      == I2C_Com_scbMode)
    #define I2C_Com_SCB_MODE_SPI_RUNTM_CFG     (I2C_Com_SCB_MODE_SPI      == I2C_Com_scbMode)
    #define I2C_Com_SCB_MODE_UART_RUNTM_CFG    (I2C_Com_SCB_MODE_UART     == I2C_Com_scbMode)
    #define I2C_Com_SCB_MODE_EZI2C_RUNTM_CFG   (I2C_Com_SCB_MODE_EZI2C    == I2C_Com_scbMode)
    #define I2C_Com_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (I2C_Com_SCB_MODE_UNCONFIG == I2C_Com_scbMode)

    /* Define wakeup enable */
    #define I2C_Com_SCB_WAKE_ENABLE_CHECK        (0u != I2C_Com_scbEnableWake)
#endif /* (I2C_Com_SCB_MODE_UNCONFIG_CONST_CFG) */

#endif /* (CY_SCB_PVT_I2C_Com_H) */


/* [] END OF FILE */
