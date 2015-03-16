/*******************************************************************************
* File Name: I2CM.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the SCB Component.
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

#if(I2CM_SCB_MODE_I2C_INC)
    #include "I2CM_I2C_PVT.h"
#endif /* (I2CM_SCB_MODE_I2C_INC) */

#if(I2CM_SCB_MODE_EZI2C_INC)
    #include "I2CM_EZI2C_PVT.h"
#endif /* (I2CM_SCB_MODE_EZI2C_INC) */

#if(I2CM_SCB_MODE_SPI_INC || I2CM_SCB_MODE_UART_INC)
    #include "I2CM_SPI_UART_PVT.h"
#endif /* (I2CM_SCB_MODE_SPI_INC || I2CM_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for unconfigured mode */
#if(I2CM_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common config vars */
    uint8 I2CM_scbMode = I2CM_SCB_MODE_UNCONFIG;
    uint8 I2CM_scbEnableWake;
    uint8 I2CM_scbEnableIntr;

    /* I2C config vars */
    uint8 I2CM_mode;
    uint8 I2CM_acceptAddr;

    /* SPI/UART config vars */
    volatile uint8 * I2CM_rxBuffer;
    uint8  I2CM_rxDataBits;
    uint32 I2CM_rxBufferSize;

    volatile uint8 * I2CM_txBuffer;
    uint8  I2CM_txDataBits;
    uint32 I2CM_txBufferSize;

    /* EZI2C config vars */
    uint8 I2CM_numberOfAddr;
    uint8 I2CM_subAddrSize;
#endif /* (I2CM_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 I2CM_initVar = 0u;

#if !defined (CY_REMOVE_I2CM_CUSTOM_INTR_HANDLER)
    cyisraddress I2CM_customIntrHandler = NULL;
#endif /* !defined (CY_REMOVE_I2CM_CUSTOM_INTR_HANDLER) */


/***************************************
*    Private Function Prototypes
***************************************/

static void I2CM_ScbEnableIntr(void);
static void I2CM_ScbModeStop(void);


/*******************************************************************************
* Function Name: I2CM_Init
********************************************************************************
*
* Summary:
*  Initializes the SCB component to operate in one of the selected configurations:
*  I2C, SPI, UART or EZ I2C.
*  When the configuration is set to �Unconfigured SCB�, this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SCB_I2CInit, SCB_SpiInit, SCB_UartInit or SCB_EzI2CInit.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void I2CM_Init(void)
{
#if(I2CM_SCB_MODE_UNCONFIG_CONST_CFG)
    if(I2CM_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        I2CM_initVar = 0u; /* Clear init var */
    }
    else
    {
        /* Initialization was done before call */
    }

#elif(I2CM_SCB_MODE_I2C_CONST_CFG)
    I2CM_I2CInit();

#elif(I2CM_SCB_MODE_SPI_CONST_CFG)
    I2CM_SpiInit();

#elif(I2CM_SCB_MODE_UART_CONST_CFG)
    I2CM_UartInit();

#elif(I2CM_SCB_MODE_EZI2C_CONST_CFG)
    I2CM_EzI2CInit();

#endif /* (I2CM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: I2CM_Enable
********************************************************************************
*
* Summary:
*  Enables the SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void I2CM_Enable(void)
{
#if(I2CM_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if(!I2CM_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        I2CM_CTRL_REG |= I2CM_CTRL_ENABLED;

        I2CM_ScbEnableIntr();
    }
#else
    I2CM_CTRL_REG |= I2CM_CTRL_ENABLED;

    I2CM_ScbEnableIntr();
#endif /* (I2CM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: I2CM_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to �Unconfigured SCB�, the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZ I2C. Otherwise this function does not enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  I2CM_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void I2CM_Start(void)
{
    if(0u == I2CM_initVar)
    {
        I2CM_Init();
        I2CM_initVar = 1u; /* Component was initialized */
    }

    I2CM_Enable();
}


/*******************************************************************************
* Function Name: I2CM_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component and its interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void I2CM_Stop(void)
{
#if(I2CM_SCB_IRQ_INTERNAL)
    I2CM_DisableInt();
#endif /* (I2CM_SCB_IRQ_INTERNAL) */

    I2CM_CTRL_REG &= (uint32) ~I2CM_CTRL_ENABLED;  /* Disable SCB block */

#if(I2CM_SCB_IRQ_INTERNAL)
    I2CM_ClearPendingInt();
#endif /* (I2CM_SCB_IRQ_INTERNAL) */

    I2CM_ScbModeStop(); /* Calls scbMode specific Stop function */
}


/*******************************************************************************
* Function Name: I2CM_SetCustomInterruptHandler
********************************************************************************
*
* Summary:
*  Registers a function to be called by the internal interrupt handler.
*  First the function that is registered is called, then the internal interrupt
*  handler performs any operations such as software buffer management functions
*  before the interrupt returns.  It is the user's responsibility not to break the
*  software buffer operations. Only one custom handler is supported, which is
*  the function provided by the most recent call.
*  At initialization time no custom handler is registered.
*
* Parameters:
*  func: Pointer to the function to register.
*        The value NULL indicates to remove the current custom interrupt
*        handler.
*
* Return:
*  None
*
*******************************************************************************/
void I2CM_SetCustomInterruptHandler(cyisraddress func)
{
#if !defined (CY_REMOVE_I2CM_CUSTOM_INTR_HANDLER)
    I2CM_customIntrHandler = func; /* Register interrupt handler */
#else
    if(NULL != func)
    {
        /* Suppress compiler warning */
    }
#endif /* !defined (CY_REMOVE_I2CM_CUSTOM_INTR_HANDLER) */
}


/*******************************************************************************
* Function Name: I2CM_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables an interrupt for a specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void I2CM_ScbEnableIntr(void)
{
#if(I2CM_SCB_IRQ_INTERNAL)
    #if(I2CM_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Enable interrupt in the NVIC */
        if(0u != I2CM_scbEnableIntr)
        {
            I2CM_EnableInt();
        }
    #else
        I2CM_EnableInt();

    #endif /* (I2CM_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (I2CM_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: I2CM_ScbModeStop
********************************************************************************
*
* Summary:
*  Calls the Stop function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void I2CM_ScbModeStop(void)
{
#if(I2CM_SCB_MODE_UNCONFIG_CONST_CFG)
    if(I2CM_SCB_MODE_I2C_RUNTM_CFG)
    {
        I2CM_I2CStop();
    }
    else if(I2CM_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        I2CM_EzI2CStop();
    }
    else
    {
        /* Do nohing for other modes */
    }
#elif(I2CM_SCB_MODE_I2C_CONST_CFG)
    I2CM_I2CStop();

#elif(I2CM_SCB_MODE_EZI2C_CONST_CFG)
    I2CM_EzI2CStop();

#endif /* (I2CM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if(I2CM_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: I2CM_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartTxRx:  Direction for UART.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void I2CM_SetPins(uint32 mode, uint32 subMode, uint32 uartTxRx)
    {
        uint32 hsiomSel [I2CM_SCB_PINS_NUMBER];
        uint32 pinsDm   [I2CM_SCB_PINS_NUMBER];
        uint32 pinsInBuf = 0u;

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for(i = 0u; i < I2CM_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = I2CM_HSIOM_DEF_SEL;
            pinsDm[i]    = I2CM_PIN_DM_ALG_HIZ;
        }

        if((I2CM_SCB_MODE_I2C   == mode) ||
           (I2CM_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[I2CM_MOSI_SCL_RX_PIN_INDEX] = I2CM_HSIOM_I2C_SEL;
            hsiomSel[I2CM_MISO_SDA_TX_PIN_INDEX] = I2CM_HSIOM_I2C_SEL;

            pinsDm[I2CM_MOSI_SCL_RX_PIN_INDEX] = I2CM_PIN_DM_OD_LO;
            pinsDm[I2CM_MISO_SDA_TX_PIN_INDEX] = I2CM_PIN_DM_OD_LO;
        }
    #if(!I2CM_CY_SCBIP_V1_I2C_ONLY)
        else if(I2CM_SCB_MODE_SPI == mode)
        {
            hsiomSel[I2CM_MOSI_SCL_RX_PIN_INDEX] = I2CM_HSIOM_SPI_SEL;
            hsiomSel[I2CM_MISO_SDA_TX_PIN_INDEX] = I2CM_HSIOM_SPI_SEL;
            hsiomSel[I2CM_SCLK_PIN_INDEX]        = I2CM_HSIOM_SPI_SEL;

            if(I2CM_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[I2CM_MOSI_SCL_RX_PIN_INDEX] = I2CM_PIN_DM_DIG_HIZ;
                pinsDm[I2CM_MISO_SDA_TX_PIN_INDEX] = I2CM_PIN_DM_STRONG;
                pinsDm[I2CM_SCLK_PIN_INDEX]        = I2CM_PIN_DM_DIG_HIZ;

            #if(I2CM_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[I2CM_SS0_PIN_INDEX] = I2CM_HSIOM_SPI_SEL;
                pinsDm  [I2CM_SS0_PIN_INDEX] = I2CM_PIN_DM_DIG_HIZ;
            #endif /* (I2CM_SS1_PIN) */

            #if(I2CM_MISO_SDA_TX_PIN)
                /* Disable input buffer */
                 pinsInBuf |= I2CM_MISO_SDA_TX_PIN_MASK;
            #endif /* (I2CM_MISO_SDA_TX_PIN_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[I2CM_MOSI_SCL_RX_PIN_INDEX] = I2CM_PIN_DM_STRONG;
                pinsDm[I2CM_MISO_SDA_TX_PIN_INDEX] = I2CM_PIN_DM_DIG_HIZ;
                pinsDm[I2CM_SCLK_PIN_INDEX]        = I2CM_PIN_DM_STRONG;

            #if(I2CM_SS0_PIN)
                hsiomSel [I2CM_SS0_PIN_INDEX] = I2CM_HSIOM_SPI_SEL;
                pinsDm   [I2CM_SS0_PIN_INDEX] = I2CM_PIN_DM_STRONG;
                pinsInBuf                                |= I2CM_SS0_PIN_MASK;
            #endif /* (I2CM_SS0_PIN) */

            #if(I2CM_SS1_PIN)
                hsiomSel [I2CM_SS1_PIN_INDEX] = I2CM_HSIOM_SPI_SEL;
                pinsDm   [I2CM_SS1_PIN_INDEX] = I2CM_PIN_DM_STRONG;
                pinsInBuf                                |= I2CM_SS1_PIN_MASK;
            #endif /* (I2CM_SS1_PIN) */

            #if(I2CM_SS2_PIN)
                hsiomSel [I2CM_SS2_PIN_INDEX] = I2CM_HSIOM_SPI_SEL;
                pinsDm   [I2CM_SS2_PIN_INDEX] = I2CM_PIN_DM_STRONG;
                pinsInBuf                                |= I2CM_SS2_PIN_MASK;
            #endif /* (I2CM_SS2_PIN) */

            #if(I2CM_SS3_PIN)
                hsiomSel [I2CM_SS3_PIN_INDEX] = I2CM_HSIOM_SPI_SEL;
                pinsDm   [I2CM_SS3_PIN_INDEX] = I2CM_PIN_DM_STRONG;
                pinsInBuf                                |= I2CM_SS3_PIN_MASK;
            #endif /* (I2CM_SS2_PIN) */

                /* Disable input buffers */
            #if(I2CM_MOSI_SCL_RX_PIN)
                pinsInBuf |= I2CM_MOSI_SCL_RX_PIN_MASK;
            #endif /* (I2CM_MOSI_SCL_RX_PIN) */

             #if(I2CM_MOSI_SCL_RX_WAKE_PIN)
                pinsInBuf |= I2CM_MOSI_SCL_RX_WAKE_PIN_MASK;
            #endif /* (I2CM_MOSI_SCL_RX_WAKE_PIN) */

            #if(I2CM_SCLK_PIN)
                pinsInBuf |= I2CM_SCLK_PIN_MASK;
            #endif /* (I2CM_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if(I2CM_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[I2CM_MISO_SDA_TX_PIN_INDEX] = I2CM_HSIOM_UART_SEL;
                pinsDm  [I2CM_MISO_SDA_TX_PIN_INDEX] = I2CM_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if(0u != (I2CM_UART_RX & uartTxRx))
                {
                    hsiomSel[I2CM_MOSI_SCL_RX_PIN_INDEX] = I2CM_HSIOM_UART_SEL;
                    pinsDm  [I2CM_MOSI_SCL_RX_PIN_INDEX] = I2CM_PIN_DM_DIG_HIZ;
                }

                if(0u != (I2CM_UART_TX & uartTxRx))
                {
                    hsiomSel[I2CM_MISO_SDA_TX_PIN_INDEX] = I2CM_HSIOM_UART_SEL;
                    pinsDm  [I2CM_MISO_SDA_TX_PIN_INDEX] = I2CM_PIN_DM_STRONG;

                #if(I2CM_MISO_SDA_TX_PIN)
                     pinsInBuf |= I2CM_MISO_SDA_TX_PIN_MASK;
                #endif /* (I2CM_MISO_SDA_TX_PIN_PIN) */
                }
            }
        }
    #endif /* (!I2CM_CY_SCBIP_V1_I2C_ONLY) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settigns do not effect the pin output if HSIOM is other than GPIO */

    #if(I2CM_MOSI_SCL_RX_PIN)
        I2CM_SET_HSIOM_SEL(I2CM_MOSI_SCL_RX_HSIOM_REG,
                                       I2CM_MOSI_SCL_RX_HSIOM_MASK,
                                       I2CM_MOSI_SCL_RX_HSIOM_POS,
                                       hsiomSel[I2CM_MOSI_SCL_RX_PIN_INDEX]);

        I2CM_spi_mosi_i2c_scl_uart_rx_SetDriveMode((uint8) pinsDm[I2CM_MOSI_SCL_RX_PIN_INDEX]);

        I2CM_SET_INP_DIS(I2CM_spi_mosi_i2c_scl_uart_rx_INP_DIS,
                                     I2CM_spi_mosi_i2c_scl_uart_rx_MASK,
                                     (0u != (pinsInBuf & I2CM_MOSI_SCL_RX_PIN_MASK)));
    #endif /* (I2CM_MOSI_SCL_RX_PIN) */

    #if(I2CM_MOSI_SCL_RX_WAKE_PIN)
        I2CM_SET_HSIOM_SEL(I2CM_MOSI_SCL_RX_WAKE_HSIOM_REG,
                                       I2CM_MOSI_SCL_RX_WAKE_HSIOM_MASK,
                                       I2CM_MOSI_SCL_RX_WAKE_HSIOM_POS,
                                       hsiomSel[I2CM_MOSI_SCL_RX_WAKE_PIN_INDEX]);

        I2CM_spi_mosi_i2c_scl_uart_rx_wake_SetDriveMode((uint8)
                                                               pinsDm[I2CM_MOSI_SCL_RX_WAKE_PIN_INDEX]);

        I2CM_SET_INP_DIS(I2CM_spi_mosi_i2c_scl_uart_rx_wake_INP_DIS,
                                     I2CM_spi_mosi_i2c_scl_uart_rx_wake_MASK,
                                     (0u != (pinsInBuf & I2CM_MOSI_SCL_RX_WAKE_PIN_MASK)));

         /* Set interrupt on falling edge */
        I2CM_SET_INCFG_TYPE(I2CM_MOSI_SCL_RX_WAKE_INTCFG_REG,
                                        I2CM_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK,
                                        I2CM_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS,
                                        I2CM_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (I2CM_MOSI_SCL_RX_WAKE_PIN) */

    #if(I2CM_MISO_SDA_TX_PIN)
        I2CM_SET_HSIOM_SEL(I2CM_MISO_SDA_TX_HSIOM_REG,
                                       I2CM_MISO_SDA_TX_HSIOM_MASK,
                                       I2CM_MISO_SDA_TX_HSIOM_POS,
                                       hsiomSel[I2CM_MISO_SDA_TX_PIN_INDEX]);

        I2CM_spi_miso_i2c_sda_uart_tx_SetDriveMode((uint8) pinsDm[I2CM_MISO_SDA_TX_PIN_INDEX]);

        I2CM_SET_INP_DIS(I2CM_spi_miso_i2c_sda_uart_tx_INP_DIS,
                                     I2CM_spi_miso_i2c_sda_uart_tx_MASK,
                                    (0u != (pinsInBuf & I2CM_MISO_SDA_TX_PIN_MASK)));
    #endif /* (I2CM_MOSI_SCL_RX_PIN) */

    #if(I2CM_SCLK_PIN)
        I2CM_SET_HSIOM_SEL(I2CM_SCLK_HSIOM_REG, I2CM_SCLK_HSIOM_MASK,
                                       I2CM_SCLK_HSIOM_POS, hsiomSel[I2CM_SCLK_PIN_INDEX]);

        I2CM_spi_sclk_SetDriveMode((uint8) pinsDm[I2CM_SCLK_PIN_INDEX]);

        I2CM_SET_INP_DIS(I2CM_spi_sclk_INP_DIS,
                             I2CM_spi_sclk_MASK,
                            (0u != (pinsInBuf & I2CM_SCLK_PIN_MASK)));
    #endif /* (I2CM_SCLK_PIN) */

    #if(I2CM_SS0_PIN)
        I2CM_SET_HSIOM_SEL(I2CM_SS0_HSIOM_REG, I2CM_SS0_HSIOM_MASK,
                                       I2CM_SS0_HSIOM_POS, hsiomSel[I2CM_SS0_PIN_INDEX]);

        I2CM_spi_ss0_SetDriveMode((uint8) pinsDm[I2CM_SS0_PIN_INDEX]);

        I2CM_SET_INP_DIS(I2CM_spi_ss0_INP_DIS,
                                     I2CM_spi_ss0_MASK,
                                     (0u != (pinsInBuf & I2CM_SS0_PIN_MASK)));
    #endif /* (I2CM_SS1_PIN) */

    #if(I2CM_SS1_PIN)
        I2CM_SET_HSIOM_SEL(I2CM_SS1_HSIOM_REG, I2CM_SS1_HSIOM_MASK,
                                       I2CM_SS1_HSIOM_POS, hsiomSel[I2CM_SS1_PIN_INDEX]);

        I2CM_spi_ss1_SetDriveMode((uint8) pinsDm[I2CM_SS1_PIN_INDEX]);

        I2CM_SET_INP_DIS(I2CM_spi_ss1_INP_DIS,
                                     I2CM_spi_ss1_MASK,
                                     (0u != (pinsInBuf & I2CM_SS1_PIN_MASK)));
    #endif /* (I2CM_SS1_PIN) */

    #if(I2CM_SS2_PIN)
        I2CM_SET_HSIOM_SEL(I2CM_SS2_HSIOM_REG, I2CM_SS2_HSIOM_MASK,
                                       I2CM_SS2_HSIOM_POS, hsiomSel[I2CM_SS2_PIN_INDEX]);

        I2CM_spi_ss2_SetDriveMode((uint8) pinsDm[I2CM_SS2_PIN_INDEX]);

        I2CM_SET_INP_DIS(I2CM_spi_ss2_INP_DIS,
                                     I2CM_spi_ss2_MASK,
                                     (0u != (pinsInBuf & I2CM_SS2_PIN_MASK)));
    #endif /* (I2CM_SS2_PIN) */

    #if(I2CM_SS3_PIN)
        I2CM_SET_HSIOM_SEL(I2CM_SS3_HSIOM_REG,  I2CM_SS3_HSIOM_MASK,
                                       I2CM_SS3_HSIOM_POS, hsiomSel[I2CM_SS3_PIN_INDEX]);

        I2CM_spi_ss3_SetDriveMode((uint8) pinsDm[I2CM_SS3_PIN_INDEX]);

        I2CM_SET_INP_DIS(I2CM_spi_ss3_INP_DIS,
                                     I2CM_spi_ss3_MASK,
                                     (0u != (pinsInBuf & I2CM_SS3_PIN_MASK)));
    #endif /* (I2CM_SS3_PIN) */
    }

#endif /* (I2CM_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
