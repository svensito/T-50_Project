/*******************************************************************************
* File Name: TelemUART_INT.c
* Version 2.30
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TelemUART.h"
#include "CyLib.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if( (TelemUART_RX_ENABLED || TelemUART_HD_ENABLED) && \
     (TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: TelemUART_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  TelemUART_rxBuffer - RAM buffer pointer for save received data.
    *  TelemUART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  TelemUART_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  TelemUART_rxBufferOverflow - software overflow flag. Set to one
    *     when TelemUART_rxBufferWrite index overtakes
    *     TelemUART_rxBufferRead index.
    *  TelemUART_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when TelemUART_rxBufferWrite is equal to
    *    TelemUART_rxBufferRead
    *  TelemUART_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  TelemUART_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(TelemUART_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;
        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START TelemUART_RXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        readData = TelemUART_RXSTATUS_REG;

        if((readData & (TelemUART_RX_STS_BREAK | TelemUART_RX_STS_PAR_ERROR |
                        TelemUART_RX_STS_STOP_ERROR | TelemUART_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            /* `#START TelemUART_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & TelemUART_RX_STS_FIFO_NOTEMPTY) != 0u)
        {

            #if (TelemUART_RXHW_ADDRESS_ENABLED)
                if(TelemUART_rxAddressMode == (uint8)TelemUART__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readData & TelemUART_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readData & TelemUART_RX_STS_ADDR_MATCH) != 0u)
                        {
                            TelemUART_rxAddressDetected = 1u;
                        }
                        else
                        {
                            TelemUART_rxAddressDetected = 0u;
                        }
                    }

                    readData = TelemUART_RXDATA_REG;
                    if(TelemUART_rxAddressDetected != 0u)
                    {   /* store only addressed data */
                        TelemUART_rxBuffer[TelemUART_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* without software addressing */
                {
                    TelemUART_rxBuffer[TelemUART_rxBufferWrite] = TelemUART_RXDATA_REG;
                    increment_pointer = 1u;
                }
            #else  /* without addressing */
                TelemUART_rxBuffer[TelemUART_rxBufferWrite] = TelemUART_RXDATA_REG;
                increment_pointer = 1u;
            #endif /* End SW_DETECT_TO_BUFFER */

            /* do not increment buffer pointer when skip not adderessed data */
            if( increment_pointer != 0u )
            {
                if(TelemUART_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    TelemUART_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                TelemUART_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(TelemUART_rxBufferWrite >= TelemUART_RXBUFFERSIZE)
                {
                    TelemUART_rxBufferWrite = 0u;
                }
                /* Detect pre-overload condition and set flag */
                if(TelemUART_rxBufferWrite == TelemUART_rxBufferRead)
                {
                    TelemUART_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if(TelemUART_FLOW_CONTROL != 0u)
                    /* Disable RX interrupt mask, it will be enabled when user read data from the buffer using APIs */
                        TelemUART_RXSTATUS_MASK_REG  &= (uint8)~TelemUART_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(TelemUART_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* End TelemUART_FLOW_CONTROL != 0 */
                }
            }

            /* Check again if there is data. */
            readData = TelemUART_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START TelemUART_RXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End TelemUART_RX_ENABLED && (TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH) */


#if(TelemUART_TX_ENABLED && (TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: TelemUART_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  TelemUART_txBuffer - RAM buffer pointer for transmit data from.
    *  TelemUART_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmited byte.
    *  TelemUART_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(TelemUART_TXISR)
    {

        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START TelemUART_TXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        while((TelemUART_txBufferRead != TelemUART_txBufferWrite) &&
             ((TelemUART_TXSTATUS_REG & TelemUART_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer. */
            if(TelemUART_txBufferRead >= TelemUART_TXBUFFERSIZE)
            {
                TelemUART_txBufferRead = 0u;
            }

            TelemUART_TXDATA_REG = TelemUART_txBuffer[TelemUART_txBufferRead];

            /* Set next pointer. */
            TelemUART_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START TelemUART_TXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End TelemUART_TX_ENABLED && (TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH) */


/* [] END OF FILE */
