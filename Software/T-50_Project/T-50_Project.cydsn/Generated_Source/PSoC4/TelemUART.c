/*******************************************************************************
* File Name: TelemUART.c
* Version 2.30
*
* Description:
*  This file provides all API functionality of the UART component
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
#include "CyLib.h"
#if(TelemUART_INTERNAL_CLOCK_USED)
    #include "TelemUART_IntClock.h"
#endif /* End TelemUART_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 TelemUART_initVar = 0u;
#if( TelemUART_TX_ENABLED && (TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH))
    volatile uint8 TelemUART_txBuffer[TelemUART_TXBUFFERSIZE];
    volatile uint8 TelemUART_txBufferRead = 0u;
    uint8 TelemUART_txBufferWrite = 0u;
#endif /* End TelemUART_TX_ENABLED */
#if( ( TelemUART_RX_ENABLED || TelemUART_HD_ENABLED ) && \
     (TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH) )
    volatile uint8 TelemUART_rxBuffer[TelemUART_RXBUFFERSIZE];
    volatile uint8 TelemUART_rxBufferRead = 0u;
    volatile uint8 TelemUART_rxBufferWrite = 0u;
    volatile uint8 TelemUART_rxBufferLoopDetect = 0u;
    volatile uint8 TelemUART_rxBufferOverflow = 0u;
    #if (TelemUART_RXHW_ADDRESS_ENABLED)
        volatile uint8 TelemUART_rxAddressMode = TelemUART_RXADDRESSMODE;
        volatile uint8 TelemUART_rxAddressDetected = 0u;
    #endif /* End EnableHWAddress */
#endif /* End TelemUART_RX_ENABLED */


/*******************************************************************************
* Function Name: TelemUART_Start
********************************************************************************
*
* Summary:
*  Initialize and Enable the UART component.
*  Enable the clock input to enable operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The TelemUART_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time UART_Start() is called. This allows for
*  component initialization without re-initialization in all subsequent calls
*  to the TelemUART_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TelemUART_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(TelemUART_initVar == 0u)
    {
        TelemUART_Init();
        TelemUART_initVar = 1u;
    }
    TelemUART_Enable();
}


/*******************************************************************************
* Function Name: TelemUART_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  TelemUART_Start().
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void TelemUART_Init(void) 
{
    #if(TelemUART_RX_ENABLED || TelemUART_HD_ENABLED)

        #if(TelemUART_RX_INTERRUPT_ENABLED && (TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH))
            /* Set the RX Interrupt. */
            (void)CyIntSetVector(TelemUART_RX_VECT_NUM, &TelemUART_RXISR);
            CyIntSetPriority(TelemUART_RX_VECT_NUM, TelemUART_RX_PRIOR_NUM);
        #endif /* End TelemUART_RX_INTERRUPT_ENABLED */

        #if (TelemUART_RXHW_ADDRESS_ENABLED)
            TelemUART_SetRxAddressMode(TelemUART_RXAddressMode);
            TelemUART_SetRxAddress1(TelemUART_RXHWADDRESS1);
            TelemUART_SetRxAddress2(TelemUART_RXHWADDRESS2);
        #endif /* End TelemUART_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        TelemUART_RXBITCTR_PERIOD_REG = TelemUART_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        TelemUART_RXSTATUS_MASK_REG  = TelemUART_INIT_RX_INTERRUPTS_MASK;
    #endif /* End TelemUART_RX_ENABLED || TelemUART_HD_ENABLED*/

    #if(TelemUART_TX_ENABLED)
        #if(TelemUART_TX_INTERRUPT_ENABLED && (TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH))
            /* Set the TX Interrupt. */
            (void)CyIntSetVector(TelemUART_TX_VECT_NUM, &TelemUART_TXISR);
            CyIntSetPriority(TelemUART_TX_VECT_NUM, TelemUART_TX_PRIOR_NUM);
        #endif /* End TelemUART_TX_INTERRUPT_ENABLED */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if(TelemUART_TXCLKGEN_DP)
            TelemUART_TXBITCLKGEN_CTR_REG = TelemUART_BIT_CENTER;
            TelemUART_TXBITCLKTX_COMPLETE_REG = (TelemUART_NUMBER_OF_DATA_BITS +
                        TelemUART_NUMBER_OF_START_BIT) * TelemUART_OVER_SAMPLE_COUNT;
        #else
            TelemUART_TXBITCTR_PERIOD_REG = ((TelemUART_NUMBER_OF_DATA_BITS +
                        TelemUART_NUMBER_OF_START_BIT) * TelemUART_OVER_SAMPLE_8) - 1u;
        #endif /* End TelemUART_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if(TelemUART_TX_INTERRUPT_ENABLED && (TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH))
            TelemUART_TXSTATUS_MASK_REG = TelemUART_TX_STS_FIFO_EMPTY;
        #else
            TelemUART_TXSTATUS_MASK_REG = TelemUART_INIT_TX_INTERRUPTS_MASK;
        #endif /*End TelemUART_TX_INTERRUPT_ENABLED*/

    #endif /* End TelemUART_TX_ENABLED */

    #if(TelemUART_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        TelemUART_WriteControlRegister( \
            (TelemUART_ReadControlRegister() & (uint8)~TelemUART_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(TelemUART_PARITY_TYPE << TelemUART_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End TelemUART_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: TelemUART_Enable
********************************************************************************
*
* Summary:
*  Enables the UART block operation
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TelemUART_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void TelemUART_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if(TelemUART_RX_ENABLED || TelemUART_HD_ENABLED)
        /*RX Counter (Count7) Enable */
        TelemUART_RXBITCTR_CONTROL_REG |= TelemUART_CNTR_ENABLE;
        /* Enable the RX Interrupt. */
        TelemUART_RXSTATUS_ACTL_REG  |= TelemUART_INT_ENABLE;
        #if(TelemUART_RX_INTERRUPT_ENABLED && (TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH))
            CyIntEnable(TelemUART_RX_VECT_NUM);
            #if (TelemUART_RXHW_ADDRESS_ENABLED)
                TelemUART_rxAddressDetected = 0u;
            #endif /* End TelemUART_RXHW_ADDRESS_ENABLED */
        #endif /* End TelemUART_RX_INTERRUPT_ENABLED */
    #endif /* End TelemUART_RX_ENABLED || TelemUART_HD_ENABLED*/

    #if(TelemUART_TX_ENABLED)
        /*TX Counter (DP/Count7) Enable */
        #if(!TelemUART_TXCLKGEN_DP)
            TelemUART_TXBITCTR_CONTROL_REG |= TelemUART_CNTR_ENABLE;
        #endif /* End TelemUART_TXCLKGEN_DP */
        /* Enable the TX Interrupt. */
        TelemUART_TXSTATUS_ACTL_REG |= TelemUART_INT_ENABLE;
        #if(TelemUART_TX_INTERRUPT_ENABLED && (TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH))
            CyIntEnable(TelemUART_TX_VECT_NUM);
        #endif /* End TelemUART_TX_INTERRUPT_ENABLED*/
     #endif /* End TelemUART_TX_ENABLED */

    #if(TelemUART_INTERNAL_CLOCK_USED)
        /* Enable the clock. */
        TelemUART_IntClock_Start();
    #endif /* End TelemUART_INTERNAL_CLOCK_USED */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TelemUART_Stop
********************************************************************************
*
* Summary:
*  Disable the UART component
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void TelemUART_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if(TelemUART_RX_ENABLED || TelemUART_HD_ENABLED)
        TelemUART_RXBITCTR_CONTROL_REG &= (uint8)~TelemUART_CNTR_ENABLE;
    #endif /* End TelemUART_RX_ENABLED */

    #if(TelemUART_TX_ENABLED)
        #if(!TelemUART_TXCLKGEN_DP)
            TelemUART_TXBITCTR_CONTROL_REG &= (uint8)~TelemUART_CNTR_ENABLE;
        #endif /* End TelemUART_TXCLKGEN_DP */
    #endif /* TelemUART_TX_ENABLED */

    #if(TelemUART_INTERNAL_CLOCK_USED)
        /* Disable the clock. */
        TelemUART_IntClock_Stop();
    #endif /* End TelemUART_INTERNAL_CLOCK_USED */

    /* Disable internal interrupt component */
    #if(TelemUART_RX_ENABLED || TelemUART_HD_ENABLED)
        TelemUART_RXSTATUS_ACTL_REG  &= (uint8)~TelemUART_INT_ENABLE;
        #if(TelemUART_RX_INTERRUPT_ENABLED && (TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH))
            TelemUART_DisableRxInt();
        #endif /* End TelemUART_RX_INTERRUPT_ENABLED */
    #endif /* End TelemUART_RX_ENABLED */

    #if(TelemUART_TX_ENABLED)
        TelemUART_TXSTATUS_ACTL_REG &= (uint8)~TelemUART_INT_ENABLE;
        #if(TelemUART_TX_INTERRUPT_ENABLED && (TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH))
            TelemUART_DisableTxInt();
        #endif /* End TelemUART_TX_INTERRUPT_ENABLED */
    #endif /* End TelemUART_TX_ENABLED */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TelemUART_ReadControlRegister
********************************************************************************
*
* Summary:
*  Read the current state of the control register
*
* Parameters:
*  None.
*
* Return:
*  Current state of the control register.
*
*******************************************************************************/
uint8 TelemUART_ReadControlRegister(void) 
{
    #if( TelemUART_CONTROL_REG_REMOVED )
        return(0u);
    #else
        return(TelemUART_CONTROL_REG);
    #endif /* End TelemUART_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: TelemUART_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  TelemUART_WriteControlRegister(uint8 control) 
{
    #if( TelemUART_CONTROL_REG_REMOVED )
        if(control != 0u) { }      /* release compiler warning */
    #else
       TelemUART_CONTROL_REG = control;
    #endif /* End TelemUART_CONTROL_REG_REMOVED */
}


#if(TelemUART_RX_ENABLED || TelemUART_HD_ENABLED)

    #if(TelemUART_RX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: TelemUART_EnableRxInt
        ********************************************************************************
        *
        * Summary:
        *  Enable RX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Enable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void TelemUART_EnableRxInt(void) 
        {
            CyIntEnable(TelemUART_RX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: TelemUART_DisableRxInt
        ********************************************************************************
        *
        * Summary:
        *  Disable RX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Disable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void TelemUART_DisableRxInt(void) 
        {
            CyIntDisable(TelemUART_RX_VECT_NUM);
        }

    #endif /* TelemUART_RX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: TelemUART_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *  IntSrc:  An or'd combination of the desired status bit masks (defined in
    *           the header file)
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void TelemUART_SetRxInterruptMode(uint8 intSrc) 
    {
        TelemUART_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: TelemUART_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns data in RX Data register without checking status register to
    *  determine if data is valid
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  TelemUART_rxBuffer - RAM buffer pointer for save received data.
    *  TelemUART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  TelemUART_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  TelemUART_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 TelemUART_ReadRxData(void) 
    {
        uint8 rxData;

        #if(TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH)
            uint8 loc_rxBufferRead;
            uint8 loc_rxBufferWrite;
            /* Protect variables that could change on interrupt. */
            /* Disable Rx interrupt. */
            #if(TelemUART_RX_INTERRUPT_ENABLED)
                TelemUART_DisableRxInt();
            #endif /* TelemUART_RX_INTERRUPT_ENABLED */
            loc_rxBufferRead = TelemUART_rxBufferRead;
            loc_rxBufferWrite = TelemUART_rxBufferWrite;

            if( (TelemUART_rxBufferLoopDetect != 0u) || (loc_rxBufferRead != loc_rxBufferWrite) )
            {
                rxData = TelemUART_rxBuffer[loc_rxBufferRead];
                loc_rxBufferRead++;

                if(loc_rxBufferRead >= TelemUART_RXBUFFERSIZE)
                {
                    loc_rxBufferRead = 0u;
                }
                /* Update the real pointer */
                TelemUART_rxBufferRead = loc_rxBufferRead;

                if(TelemUART_rxBufferLoopDetect != 0u )
                {
                    TelemUART_rxBufferLoopDetect = 0u;
                    #if( (TelemUART_RX_INTERRUPT_ENABLED) && (TelemUART_FLOW_CONTROL != 0u) && \
                         (TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH) )
                        /* When Hardware Flow Control selected - return RX mask */
                        #if( TelemUART_HD_ENABLED )
                            if((TelemUART_CONTROL_REG & TelemUART_CTRL_HD_SEND) == 0u)
                            {   /* In Half duplex mode return RX mask only in RX
                                *  configuration set, otherwise
                                *  mask will be returned in LoadRxConfig() API.
                                */
                                TelemUART_RXSTATUS_MASK_REG  |= TelemUART_RX_STS_FIFO_NOTEMPTY;
                            }
                        #else
                            TelemUART_RXSTATUS_MASK_REG  |= TelemUART_RX_STS_FIFO_NOTEMPTY;
                        #endif /* end TelemUART_HD_ENABLED */
                    #endif /* TelemUART_RX_INTERRUPT_ENABLED and Hardware flow control*/
                }
            }
            else
            {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
                rxData = TelemUART_RXDATA_REG;
            }

            /* Enable Rx interrupt. */
            #if(TelemUART_RX_INTERRUPT_ENABLED)
                TelemUART_EnableRxInt();
            #endif /* End TelemUART_RX_INTERRUPT_ENABLED */

        #else /* TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH */

            /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
            rxData = TelemUART_RXDATA_REG;

        #endif /* TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: TelemUART_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Read the current state of the status register
    *  And detect software buffer overflow.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Global Variables:
    *  TelemUART_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn?t free space in
    *   TelemUART_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   TelemUART_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 TelemUART_ReadRxStatus(void) 
    {
        uint8 status;

        status = TelemUART_RXSTATUS_REG & TelemUART_RX_HW_MASK;

        #if(TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH)
            if( TelemUART_rxBufferOverflow != 0u )
            {
                status |= TelemUART_RX_STS_SOFT_BUFF_OVER;
                TelemUART_rxBufferOverflow = 0u;
            }
        #endif /* TelemUART_RXBUFFERSIZE */

        return(status);
    }


    /*******************************************************************************
    * Function Name: TelemUART_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, if data is not available or an error
    *  condition exists, zero is returned; otherwise, character is read and
    *  returned.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  TelemUART_rxBuffer - RAM buffer pointer for save received data.
    *  TelemUART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  TelemUART_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  TelemUART_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 TelemUART_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

        #if(TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH)
            uint8 loc_rxBufferRead;
            uint8 loc_rxBufferWrite;
            /* Protect variables that could change on interrupt. */
            /* Disable Rx interrupt. */
            #if(TelemUART_RX_INTERRUPT_ENABLED)
                TelemUART_DisableRxInt();
            #endif /* TelemUART_RX_INTERRUPT_ENABLED */
            loc_rxBufferRead = TelemUART_rxBufferRead;
            loc_rxBufferWrite = TelemUART_rxBufferWrite;

            if( (TelemUART_rxBufferLoopDetect != 0u) || (loc_rxBufferRead != loc_rxBufferWrite) )
            {
                rxData = TelemUART_rxBuffer[loc_rxBufferRead];
                loc_rxBufferRead++;
                if(loc_rxBufferRead >= TelemUART_RXBUFFERSIZE)
                {
                    loc_rxBufferRead = 0u;
                }
                /* Update the real pointer */
                TelemUART_rxBufferRead = loc_rxBufferRead;

                if(TelemUART_rxBufferLoopDetect > 0u )
                {
                    TelemUART_rxBufferLoopDetect = 0u;
                    #if( (TelemUART_RX_INTERRUPT_ENABLED) && (TelemUART_FLOW_CONTROL != 0u) )
                        /* When Hardware Flow Control selected - return RX mask */
                        #if( TelemUART_HD_ENABLED )
                            if((TelemUART_CONTROL_REG & TelemUART_CTRL_HD_SEND) == 0u)
                            {   /* In Half duplex mode return RX mask only if
                                *  RX configuration set, otherwise
                                *  mask will be returned in LoadRxConfig() API.
                                */
                                TelemUART_RXSTATUS_MASK_REG  |= TelemUART_RX_STS_FIFO_NOTEMPTY;
                            }
                        #else
                            TelemUART_RXSTATUS_MASK_REG  |= TelemUART_RX_STS_FIFO_NOTEMPTY;
                        #endif /* end TelemUART_HD_ENABLED */
                    #endif /* TelemUART_RX_INTERRUPT_ENABLED and Hardware flow control*/
                }

            }
            else
            {   rxStatus = TelemUART_RXSTATUS_REG;
                if((rxStatus & TelemUART_RX_STS_FIFO_NOTEMPTY) != 0u)
                {   /* Read received data from FIFO*/
                    rxData = TelemUART_RXDATA_REG;
                    /*Check status on error*/
                    if((rxStatus & (TelemUART_RX_STS_BREAK | TelemUART_RX_STS_PAR_ERROR |
                                   TelemUART_RX_STS_STOP_ERROR | TelemUART_RX_STS_OVERRUN)) != 0u)
                    {
                        rxData = 0u;
                    }
                }
            }

            /* Enable Rx interrupt. */
            #if(TelemUART_RX_INTERRUPT_ENABLED)
                TelemUART_EnableRxInt();
            #endif /* TelemUART_RX_INTERRUPT_ENABLED */

        #else /* TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH */

            rxStatus =TelemUART_RXSTATUS_REG;
            if((rxStatus & TelemUART_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO*/
                rxData = TelemUART_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (TelemUART_RX_STS_BREAK | TelemUART_RX_STS_PAR_ERROR |
                               TelemUART_RX_STS_STOP_ERROR | TelemUART_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        #endif /* TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: TelemUART_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Grab the next available byte of data from the recieve FIFO
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains Status Register and LSB contains UART RX data
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 TelemUART_GetByte(void) 
    {
        return ( ((uint16)TelemUART_ReadRxStatus() << 8u) | TelemUART_ReadRxData() );
    }


    /*******************************************************************************
    * Function Name: TelemUART_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Determine the amount of bytes left in the RX buffer and return the count in
    *  bytes
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Integer count of the number of bytes left
    *  in the RX buffer
    *
    * Global Variables:
    *  TelemUART_rxBufferWrite - used to calculate left bytes.
    *  TelemUART_rxBufferRead - used to calculate left bytes.
    *  TelemUART_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 TelemUART_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

        #if(TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(TelemUART_RX_INTERRUPT_ENABLED)
                TelemUART_DisableRxInt();
            #endif /* TelemUART_RX_INTERRUPT_ENABLED */

            if(TelemUART_rxBufferRead == TelemUART_rxBufferWrite)
            {
                if(TelemUART_rxBufferLoopDetect > 0u)
                {
                    size = TelemUART_RXBUFFERSIZE;
                }
                else
                {
                    size = 0u;
                }
            }
            else if(TelemUART_rxBufferRead < TelemUART_rxBufferWrite)
            {
                size = (TelemUART_rxBufferWrite - TelemUART_rxBufferRead);
            }
            else
            {
                size = (TelemUART_RXBUFFERSIZE - TelemUART_rxBufferRead) + TelemUART_rxBufferWrite;
            }

            /* Enable Rx interrupt. */
            #if(TelemUART_RX_INTERRUPT_ENABLED)
                TelemUART_EnableRxInt();
            #endif /* End TelemUART_RX_INTERRUPT_ENABLED */

        #else /* TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH */

            /* We can only know if there is data in the fifo. */
            size = ((TelemUART_RXSTATUS_REG & TelemUART_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

        #endif /* End TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: TelemUART_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the RX RAM buffer by setting the read and write pointers both to zero.
    *  Clears hardware RX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  TelemUART_rxBufferWrite - cleared to zero.
    *  TelemUART_rxBufferRead - cleared to zero.
    *  TelemUART_rxBufferLoopDetect - cleared to zero.
    *  TelemUART_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *******************************************************************************/
    void TelemUART_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* clear the HW FIFO */
        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();
        TelemUART_RXDATA_AUX_CTL_REG |=  TelemUART_RX_FIFO_CLR;
        TelemUART_RXDATA_AUX_CTL_REG &= (uint8)~TelemUART_RX_FIFO_CLR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);

        #if(TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH)
            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(TelemUART_RX_INTERRUPT_ENABLED)
                TelemUART_DisableRxInt();
            #endif /* End TelemUART_RX_INTERRUPT_ENABLED */

            TelemUART_rxBufferRead = 0u;
            TelemUART_rxBufferWrite = 0u;
            TelemUART_rxBufferLoopDetect = 0u;
            TelemUART_rxBufferOverflow = 0u;

            /* Enable Rx interrupt. */
            #if(TelemUART_RX_INTERRUPT_ENABLED)
                TelemUART_EnableRxInt();
            #endif /* End TelemUART_RX_INTERRUPT_ENABLED */
        #endif /* End TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH */

    }


    /*******************************************************************************
    * Function Name: TelemUART_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the receive addressing mode
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  TelemUART__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  TelemUART__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  TelemUART__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  TelemUART__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  TelemUART__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  TelemUART_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  TelemUART_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void TelemUART_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(TelemUART_RXHW_ADDRESS_ENABLED)
            #if(TelemUART_CONTROL_REG_REMOVED)
                if(addressMode != 0u) { }     /* release compiler warning */
            #else /* TelemUART_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = TelemUART_CONTROL_REG & (uint8)~TelemUART_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << TelemUART_CTRL_RXADDR_MODE0_SHIFT);
                TelemUART_CONTROL_REG = tmpCtrl;
                #if(TelemUART_RX_INTERRUPT_ENABLED && \
                   (TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH) )
                    TelemUART_rxAddressMode = addressMode;
                    TelemUART_rxAddressDetected = 0u;
                #endif /* End TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH*/
            #endif /* End TelemUART_CONTROL_REG_REMOVED */
        #else /* TelemUART_RXHW_ADDRESS_ENABLED */
            if(addressMode != 0u) { }     /* release compiler warning */
        #endif /* End TelemUART_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: TelemUART_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Set the first hardware address compare value
    *
    * Parameters:
    *  address
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void TelemUART_SetRxAddress1(uint8 address) 

    {
        TelemUART_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: TelemUART_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Set the second hardware address compare value
    *
    * Parameters:
    *  address
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void TelemUART_SetRxAddress2(uint8 address) 
    {
        TelemUART_RXADDRESS2_REG = address;
    }

#endif  /* TelemUART_RX_ENABLED || TelemUART_HD_ENABLED*/


#if( (TelemUART_TX_ENABLED) || (TelemUART_HD_ENABLED) )

    #if(TelemUART_TX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: TelemUART_EnableTxInt
        ********************************************************************************
        *
        * Summary:
        *  Enable TX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Enable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void TelemUART_EnableTxInt(void) 
        {
            CyIntEnable(TelemUART_TX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: TelemUART_DisableTxInt
        ********************************************************************************
        *
        * Summary:
        *  Disable TX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Disable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void TelemUART_DisableTxInt(void) 
        {
            CyIntDisable(TelemUART_TX_VECT_NUM);
        }

    #endif /* TelemUART_TX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: TelemUART_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *  intSrc: An or'd combination of the desired status bit masks (defined in
    *          the header file)
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void TelemUART_SetTxInterruptMode(uint8 intSrc) 
    {
        TelemUART_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: TelemUART_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Write a byte of data to the Transmit FIFO or TX buffer to be sent when the
    *  bus is available. WriteTxData sends a byte without checking for buffer room
    *  or status. It is up to the user to separately check status.
    *
    * Parameters:
    *  TXDataByte: byte of data to place in the transmit FIFO
    *
    * Return:
    * void
    *
    * Global Variables:
    *  TelemUART_txBuffer - RAM buffer pointer for save data for transmission
    *  TelemUART_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  TelemUART_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  TelemUART_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void TelemUART_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(TelemUART_initVar != 0u)
        {
            #if(TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH)

                /* Disable Tx interrupt. */
                /* Protect variables that could change on interrupt. */
                #if(TelemUART_TX_INTERRUPT_ENABLED)
                    TelemUART_DisableTxInt();
                #endif /* End TelemUART_TX_INTERRUPT_ENABLED */

                if( (TelemUART_txBufferRead == TelemUART_txBufferWrite) &&
                    ((TelemUART_TXSTATUS_REG & TelemUART_TX_STS_FIFO_FULL) == 0u) )
                {
                    /* Add directly to the FIFO. */
                    TelemUART_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(TelemUART_txBufferWrite >= TelemUART_TXBUFFERSIZE)
                    {
                        TelemUART_txBufferWrite = 0u;
                    }

                    TelemUART_txBuffer[TelemUART_txBufferWrite] = txDataByte;

                    /* Add to the software buffer. */
                    TelemUART_txBufferWrite++;

                }

                /* Enable Tx interrupt. */
                #if(TelemUART_TX_INTERRUPT_ENABLED)
                    TelemUART_EnableTxInt();
                #endif /* End TelemUART_TX_INTERRUPT_ENABLED */

            #else /* TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH */

                /* Add directly to the FIFO. */
                TelemUART_TXDATA_REG = txDataByte;

            #endif /* End TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH */
        }
    }


    /*******************************************************************************
    * Function Name: TelemUART_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Read the status register for the component
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the status register which is clear on read. It is up to
    *  the user to handle all bits in this return value accordingly, even if the bit
    *  was not enabled as an interrupt source the event happened and must be handled
    *  accordingly.
    *
    *******************************************************************************/
    uint8 TelemUART_ReadTxStatus(void) 
    {
        return(TelemUART_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: TelemUART_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Wait to send byte until TX register or buffer has room.
    *
    * Parameters:
    *  txDataByte: The 8-bit data value to send across the UART.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  TelemUART_txBuffer - RAM buffer pointer for save data for transmission
    *  TelemUART_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  TelemUART_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  TelemUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void TelemUART_PutChar(uint8 txDataByte) 
    {
            #if(TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH)
                /* The temporary output pointer is used since it takes two instructions
                *  to increment with a wrap, and we can't risk doing that with the real
                *  pointer and getting an interrupt in between instructions.
                */
                uint8 loc_txBufferWrite;
                uint8 loc_txBufferRead;

                do{
                    /* Block if software buffer is full, so we don't overwrite. */
                    #if ((TelemUART_TXBUFFERSIZE > TelemUART_MAX_BYTE_VALUE) && (CY_PSOC3))
                        /* Disable TX interrupt to protect variables that could change on interrupt */
                        CyIntDisable(TelemUART_TX_VECT_NUM);
                    #endif /* End TXBUFFERSIZE > 255 */
                    loc_txBufferWrite = TelemUART_txBufferWrite;
                    loc_txBufferRead = TelemUART_txBufferRead;
                    #if ((TelemUART_TXBUFFERSIZE > TelemUART_MAX_BYTE_VALUE) && (CY_PSOC3))
                        /* Enable interrupt to continue transmission */
                        CyIntEnable(TelemUART_TX_VECT_NUM);
                    #endif /* End TXBUFFERSIZE > 255 */
                }while( (loc_txBufferWrite < loc_txBufferRead) ? (loc_txBufferWrite == (loc_txBufferRead - 1u)) :
                                        ((loc_txBufferWrite - loc_txBufferRead) ==
                                        (uint8)(TelemUART_TXBUFFERSIZE - 1u)) );

                if( (loc_txBufferRead == loc_txBufferWrite) &&
                    ((TelemUART_TXSTATUS_REG & TelemUART_TX_STS_FIFO_FULL) == 0u) )
                {
                    /* Add directly to the FIFO. */
                    TelemUART_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(loc_txBufferWrite >= TelemUART_TXBUFFERSIZE)
                    {
                        loc_txBufferWrite = 0u;
                    }
                    /* Add to the software buffer. */
                    TelemUART_txBuffer[loc_txBufferWrite] = txDataByte;
                    loc_txBufferWrite++;

                    /* Finally, update the real output pointer */
                    #if ((TelemUART_TXBUFFERSIZE > TelemUART_MAX_BYTE_VALUE) && (CY_PSOC3))
                        CyIntDisable(TelemUART_TX_VECT_NUM);
                    #endif /* End TXBUFFERSIZE > 255 */
                    TelemUART_txBufferWrite = loc_txBufferWrite;
                    #if ((TelemUART_TXBUFFERSIZE > TelemUART_MAX_BYTE_VALUE) && (CY_PSOC3))
                        CyIntEnable(TelemUART_TX_VECT_NUM);
                    #endif /* End TXBUFFERSIZE > 255 */
                }

            #else /* TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH */

                while((TelemUART_TXSTATUS_REG & TelemUART_TX_STS_FIFO_FULL) != 0u)
                {
                    ; /* Wait for room in the FIFO. */
                }

                /* Add directly to the FIFO. */
                TelemUART_TXDATA_REG = txDataByte;

            #endif /* End TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: TelemUART_PutString
    ********************************************************************************
    *
    * Summary:
    *  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
    *
    * Parameters:
    *  string: char pointer to character string of Data to Send.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  TelemUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  This function will block if there is not enough memory to place the whole
    *  string, it will block until the entire string has been written to the
    *  transmit buffer.
    *
    *******************************************************************************/
    void TelemUART_PutString(const char8 string[]) 
    {
        uint16 buf_index = 0u;
        /* If not Initialized then skip this function*/
        if(TelemUART_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent*/
            while(string[buf_index] != (char8)0)
            {
                TelemUART_PutChar((uint8)string[buf_index]);
                buf_index++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: TelemUART_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
    *
    * Parameters:
    *  string: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of Bytes to be transmitted.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  TelemUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void TelemUART_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 buf_index = 0u;
        /* If not Initialized then skip this function*/
        if(TelemUART_initVar != 0u)
        {
            do
            {
                TelemUART_PutChar(string[buf_index]);
                buf_index++;
            }while(buf_index < byteCount);
        }
    }


    /*******************************************************************************
    * Function Name: TelemUART_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Write a character and then carriage return and line feed.
    *
    * Parameters:
    *  txDataByte: uint8 Character to send.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  TelemUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void TelemUART_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(TelemUART_initVar != 0u)
        {
            TelemUART_PutChar(txDataByte);
            TelemUART_PutChar(0x0Du);
            TelemUART_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: TelemUART_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Determine the amount of space left in the TX buffer and return the count in
    *  bytes
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Integer count of the number of bytes left in the TX buffer
    *
    * Global Variables:
    *  TelemUART_txBufferWrite - used to calculate left space.
    *  TelemUART_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 TelemUART_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

        #if(TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(TelemUART_TX_INTERRUPT_ENABLED)
                TelemUART_DisableTxInt();
            #endif /* End TelemUART_TX_INTERRUPT_ENABLED */

            if(TelemUART_txBufferRead == TelemUART_txBufferWrite)
            {
                size = 0u;
            }
            else if(TelemUART_txBufferRead < TelemUART_txBufferWrite)
            {
                size = (TelemUART_txBufferWrite - TelemUART_txBufferRead);
            }
            else
            {
                size = (TelemUART_TXBUFFERSIZE - TelemUART_txBufferRead) + TelemUART_txBufferWrite;
            }

            /* Enable Tx interrupt. */
            #if(TelemUART_TX_INTERRUPT_ENABLED)
                TelemUART_EnableTxInt();
            #endif /* End TelemUART_TX_INTERRUPT_ENABLED */

        #else /* TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH */

            size = TelemUART_TXSTATUS_REG;

            /* Is the fifo is full. */
            if((size & TelemUART_TX_STS_FIFO_FULL) != 0u)
            {
                size = TelemUART_FIFO_LENGTH;
            }
            else if((size & TelemUART_TX_STS_FIFO_EMPTY) != 0u)
            {
                size = 0u;
            }
            else
            {
                /* We only know there is data in the fifo. */
                size = 1u;
            }

        #endif /* End TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: TelemUART_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the TX RAM buffer by setting the read and write pointers both to zero.
    *  Clears the hardware TX FIFO.  Any data present in the FIFO will not be sent.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  TelemUART_txBufferWrite - cleared to zero.
    *  TelemUART_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM buffer will be lost when overwritten.
    *
    *******************************************************************************/
    void TelemUART_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();
        /* clear the HW FIFO */
        TelemUART_TXDATA_AUX_CTL_REG |=  TelemUART_TX_FIFO_CLR;
        TelemUART_TXDATA_AUX_CTL_REG &= (uint8)~TelemUART_TX_FIFO_CLR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);

        #if(TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(TelemUART_TX_INTERRUPT_ENABLED)
                TelemUART_DisableTxInt();
            #endif /* End TelemUART_TX_INTERRUPT_ENABLED */

            TelemUART_txBufferRead = 0u;
            TelemUART_txBufferWrite = 0u;

            /* Enable Tx interrupt. */
            #if(TelemUART_TX_INTERRUPT_ENABLED)
                TelemUART_EnableTxInt();
            #endif /* End TelemUART_TX_INTERRUPT_ENABLED */

        #endif /* End TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: TelemUART_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Write a Break command to the UART
    *
    * Parameters:
    *  uint8 retMode:  Wait mode,
    *   0 - Initialize registers for Break, sends the Break signal and return
    *       imediately.
    *   1 - Wait until Break sending is complete, reinitialize registers to normal
    *       transmission mode then return.
    *   2 - Reinitialize registers to normal transmission mode then return.
    *   3 - both steps: 0 and 1
    *       init registers for Break, send Break signal
    *       wait until Break sending is complete, reinit registers to normal
    *       transmission mode then return.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  TelemUART_initVar - checked to identify that the component has been
    *     initialized.
    *  tx_period - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  Trere are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Funcition will block CPU untill transmition
    *     complete.
    *  2) User may want to use bloking time if UART configured to the low speed
    *     operation
    *     Emample for this case:
    *     SendBreak(0);     - init Break signal transmition
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to init and use the interrupt for complete
    *     break operation.
    *     Example for this case:
    *     Init TX interrupt whith "TX - On TX Complete" parameter
    *     SendBreak(0);     - init Break signal transmition
    *         Add your code here to use CPU time
    *     When interrupt appear with UART_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *   Uses static variable to keep registers configuration.
    *
    *******************************************************************************/
    void TelemUART_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(TelemUART_initVar != 0u)
        {
            /*Set the Counter to 13-bits and transmit a 00 byte*/
            /*When that is done then reset the counter value back*/
            uint8 tmpStat;

            #if(TelemUART_HD_ENABLED) /* Half Duplex mode*/

                if( (retMode == TelemUART_SEND_BREAK) ||
                    (retMode == TelemUART_SEND_WAIT_REINIT ) )
                {
                    /* CTRL_HD_SEND_BREAK - sends break bits in HD mode*/
                    TelemUART_WriteControlRegister(TelemUART_ReadControlRegister() |
                                                          TelemUART_CTRL_HD_SEND_BREAK);
                    /* Send zeros*/
                    TelemUART_TXDATA_REG = 0u;

                    do /*wait until transmit starts*/
                    {
                        tmpStat = TelemUART_TXSTATUS_REG;
                    }while((tmpStat & TelemUART_TX_STS_FIFO_EMPTY) != 0u);
                }

                if( (retMode == TelemUART_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == TelemUART_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = TelemUART_TXSTATUS_REG;
                    }while(((uint8)~tmpStat & TelemUART_TX_STS_COMPLETE) != 0u);
                }

                if( (retMode == TelemUART_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == TelemUART_REINIT) ||
                    (retMode == TelemUART_SEND_WAIT_REINIT) )
                {
                    TelemUART_WriteControlRegister(TelemUART_ReadControlRegister() &
                                                  (uint8)~TelemUART_CTRL_HD_SEND_BREAK);
                }

            #else /* TelemUART_HD_ENABLED Full Duplex mode */

                static uint8 tx_period;

                if( (retMode == TelemUART_SEND_BREAK) ||
                    (retMode == TelemUART_SEND_WAIT_REINIT) )
                {
                    /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode*/
                    #if( (TelemUART_PARITY_TYPE != TelemUART__B_UART__NONE_REVB) || \
                                        (TelemUART_PARITY_TYPE_SW != 0u) )
                        TelemUART_WriteControlRegister(TelemUART_ReadControlRegister() |
                                                              TelemUART_CTRL_HD_SEND_BREAK);
                    #endif /* End TelemUART_PARITY_TYPE != TelemUART__B_UART__NONE_REVB  */

                    #if(TelemUART_TXCLKGEN_DP)
                        tx_period = TelemUART_TXBITCLKTX_COMPLETE_REG;
                        TelemUART_TXBITCLKTX_COMPLETE_REG = TelemUART_TXBITCTR_BREAKBITS;
                    #else
                        tx_period = TelemUART_TXBITCTR_PERIOD_REG;
                        TelemUART_TXBITCTR_PERIOD_REG = TelemUART_TXBITCTR_BREAKBITS8X;
                    #endif /* End TelemUART_TXCLKGEN_DP */

                    /* Send zeros*/
                    TelemUART_TXDATA_REG = 0u;

                    do /* wait until transmit starts */
                    {
                        tmpStat = TelemUART_TXSTATUS_REG;
                    }while((tmpStat & TelemUART_TX_STS_FIFO_EMPTY) != 0u);
                }

                if( (retMode == TelemUART_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == TelemUART_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = TelemUART_TXSTATUS_REG;
                    }while(((uint8)~tmpStat & TelemUART_TX_STS_COMPLETE) != 0u);
                }

                if( (retMode == TelemUART_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == TelemUART_REINIT) ||
                    (retMode == TelemUART_SEND_WAIT_REINIT) )
                {

                    #if(TelemUART_TXCLKGEN_DP)
                        TelemUART_TXBITCLKTX_COMPLETE_REG = tx_period;
                    #else
                        TelemUART_TXBITCTR_PERIOD_REG = tx_period;
                    #endif /* End TelemUART_TXCLKGEN_DP */

                    #if( (TelemUART_PARITY_TYPE != TelemUART__B_UART__NONE_REVB) || \
                         (TelemUART_PARITY_TYPE_SW != 0u) )
                        TelemUART_WriteControlRegister(TelemUART_ReadControlRegister() &
                                                      (uint8)~TelemUART_CTRL_HD_SEND_BREAK);
                    #endif /* End TelemUART_PARITY_TYPE != NONE */
                }
            #endif    /* End TelemUART_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: TelemUART_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the transmit addressing mode
    *
    * Parameters:
    *  addressMode: 0 -> Space
    *               1 -> Mark
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void TelemUART_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable*/
        if(addressMode != 0u)
        {
            #if( TelemUART_CONTROL_REG_REMOVED == 0u )
                TelemUART_WriteControlRegister(TelemUART_ReadControlRegister() |
                                                      TelemUART_CTRL_MARK);
            #endif /* End TelemUART_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
            #if( TelemUART_CONTROL_REG_REMOVED == 0u )
                TelemUART_WriteControlRegister(TelemUART_ReadControlRegister() &
                                                    (uint8)~TelemUART_CTRL_MARK);
            #endif /* End TelemUART_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndTelemUART_TX_ENABLED */

#if(TelemUART_HD_ENABLED)


    /*******************************************************************************
    * Function Name: TelemUART_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Unloads the Rx configuration if required and loads the
    *  Tx configuration. It is the users responsibility to ensure that any
    *  transaction is complete and it is safe to unload the Tx
    *  configuration.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Valid only for half duplex UART.
    *
    * Side Effects:
    *  Disable RX interrupt mask, when software buffer has been used.
    *
    *******************************************************************************/
    void TelemUART_LoadTxConfig(void) 
    {
        #if((TelemUART_RX_INTERRUPT_ENABLED) && (TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH))
            /* Disable RX interrupts before set TX configuration */
            TelemUART_SetRxInterruptMode(0u);
        #endif /* TelemUART_RX_INTERRUPT_ENABLED */

        TelemUART_WriteControlRegister(TelemUART_ReadControlRegister() | TelemUART_CTRL_HD_SEND);
        TelemUART_RXBITCTR_PERIOD_REG = TelemUART_HD_TXBITCTR_INIT;
        #if(CY_UDB_V0) /* Manually clear status register when mode has been changed */
            /* Clear status register */
            CY_GET_REG8(TelemUART_RXSTATUS_PTR);
        #endif /* CY_UDB_V0 */
    }


    /*******************************************************************************
    * Function Name: TelemUART_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Unloads the Tx configuration if required and loads the
    *  Rx configuration. It is the users responsibility to ensure that any
    *  transaction is complete and it is safe to unload the Rx
    *  configuration.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Valid only for half duplex UART
    *
    * Side Effects:
    *  Set RX interrupt mask based on customizer settings, when software buffer
    *  has been used.
    *
    *******************************************************************************/
    void TelemUART_LoadRxConfig(void) 
    {
        TelemUART_WriteControlRegister(TelemUART_ReadControlRegister() &
                                                (uint8)~TelemUART_CTRL_HD_SEND);
        TelemUART_RXBITCTR_PERIOD_REG = TelemUART_HD_RXBITCTR_INIT;
        #if(CY_UDB_V0) /* Manually clear status register when mode has been changed */
            /* Clear status register */
            CY_GET_REG8(TelemUART_RXSTATUS_PTR);
        #endif /* CY_UDB_V0 */

        #if((TelemUART_RX_INTERRUPT_ENABLED) && (TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH))
            /* Enable RX interrupt after set RX configuration */
            TelemUART_SetRxInterruptMode(TelemUART_INIT_RX_INTERRUPTS_MASK);
        #endif /* TelemUART_RX_INTERRUPT_ENABLED */
    }

#endif  /* TelemUART_HD_ENABLED */


/* [] END OF FILE */
