/*******************************************************************************
* File Name: TelemUART.h
* Version 2.30
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_TelemUART_H)
#define CY_UART_TelemUART_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define TelemUART_RX_ENABLED                     (0u)
#define TelemUART_TX_ENABLED                     (1u)
#define TelemUART_HD_ENABLED                     (0u)
#define TelemUART_RX_INTERRUPT_ENABLED           (0u)
#define TelemUART_TX_INTERRUPT_ENABLED           (0u)
#define TelemUART_INTERNAL_CLOCK_USED            (1u)
#define TelemUART_RXHW_ADDRESS_ENABLED           (0u)
#define TelemUART_OVER_SAMPLE_COUNT              (8u)
#define TelemUART_PARITY_TYPE                    (0u)
#define TelemUART_PARITY_TYPE_SW                 (0u)
#define TelemUART_BREAK_DETECT                   (0u)
#define TelemUART_BREAK_BITS_TX                  (13u)
#define TelemUART_BREAK_BITS_RX                  (13u)
#define TelemUART_TXCLKGEN_DP                    (1u)
#define TelemUART_USE23POLLING                   (1u)
#define TelemUART_FLOW_CONTROL                   (0u)
#define TelemUART_CLK_FREQ                       (0u)
#define TelemUART_TXBUFFERSIZE                   (4u)
#define TelemUART_RXBUFFERSIZE                   (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_30 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#ifdef TelemUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define TelemUART_CONTROL_REG_REMOVED            (0u)
#else
    #define TelemUART_CONTROL_REG_REMOVED            (1u)
#endif /* End TelemUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct TelemUART_backupStruct_
{
    uint8 enableState;

    #if(TelemUART_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End TelemUART_CONTROL_REG_REMOVED */
    #if( (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED) )
        uint8 rx_period;
        #if (CY_UDB_V0)
            uint8 rx_mask;
            #if (TelemUART_RXHW_ADDRESS_ENABLED)
                uint8 rx_addr1;
                uint8 rx_addr2;
            #endif /* End TelemUART_RXHW_ADDRESS_ENABLED */
        #endif /* End CY_UDB_V0 */
    #endif  /* End (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED)*/

    #if(TelemUART_TX_ENABLED)
        #if(TelemUART_TXCLKGEN_DP)
            uint8 tx_clk_ctr;
            #if (CY_UDB_V0)
                uint8 tx_clk_compl;
            #endif  /* End CY_UDB_V0 */
        #else
            uint8 tx_period;
        #endif /*End TelemUART_TXCLKGEN_DP */
        #if (CY_UDB_V0)
            uint8 tx_mask;
        #endif  /* End CY_UDB_V0 */
    #endif /*End TelemUART_TX_ENABLED */
} TelemUART_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void TelemUART_Start(void) ;
void TelemUART_Stop(void) ;
uint8 TelemUART_ReadControlRegister(void) ;
void TelemUART_WriteControlRegister(uint8 control) ;

void TelemUART_Init(void) ;
void TelemUART_Enable(void) ;
void TelemUART_SaveConfig(void) ;
void TelemUART_RestoreConfig(void) ;
void TelemUART_Sleep(void) ;
void TelemUART_Wakeup(void) ;

/* Only if RX is enabled */
#if( (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED) )

    #if(TelemUART_RX_INTERRUPT_ENABLED)
        void  TelemUART_EnableRxInt(void) ;
        void  TelemUART_DisableRxInt(void) ;
        CY_ISR_PROTO(TelemUART_RXISR);
    #endif /* TelemUART_RX_INTERRUPT_ENABLED */

    void TelemUART_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void TelemUART_SetRxAddress1(uint8 address) ;
    void TelemUART_SetRxAddress2(uint8 address) ;

    void  TelemUART_SetRxInterruptMode(uint8 intSrc) ;
    uint8 TelemUART_ReadRxData(void) ;
    uint8 TelemUART_ReadRxStatus(void) ;
    uint8 TelemUART_GetChar(void) ;
    uint16 TelemUART_GetByte(void) ;
    uint8 TelemUART_GetRxBufferSize(void)
                                                            ;
    void TelemUART_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define TelemUART_GetRxInterruptSource   TelemUART_ReadRxStatus

#endif /* End (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED) */

/* Only if TX is enabled */
#if(TelemUART_TX_ENABLED || TelemUART_HD_ENABLED)

    #if(TelemUART_TX_INTERRUPT_ENABLED)
        void TelemUART_EnableTxInt(void) ;
        void TelemUART_DisableTxInt(void) ;
        CY_ISR_PROTO(TelemUART_TXISR);
    #endif /* TelemUART_TX_INTERRUPT_ENABLED */

    void TelemUART_SetTxInterruptMode(uint8 intSrc) ;
    void TelemUART_WriteTxData(uint8 txDataByte) ;
    uint8 TelemUART_ReadTxStatus(void) ;
    void TelemUART_PutChar(uint8 txDataByte) ;
    void TelemUART_PutString(const char8 string[]) ;
    void TelemUART_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void TelemUART_PutCRLF(uint8 txDataByte) ;
    void TelemUART_ClearTxBuffer(void) ;
    void TelemUART_SetTxAddressMode(uint8 addressMode) ;
    void TelemUART_SendBreak(uint8 retMode) ;
    uint8 TelemUART_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define TelemUART_PutStringConst         TelemUART_PutString
    #define TelemUART_PutArrayConst          TelemUART_PutArray
    #define TelemUART_GetTxInterruptSource   TelemUART_ReadTxStatus

#endif /* End TelemUART_TX_ENABLED || TelemUART_HD_ENABLED */

#if(TelemUART_HD_ENABLED)
    void TelemUART_LoadRxConfig(void) ;
    void TelemUART_LoadTxConfig(void) ;
#endif /* End TelemUART_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_TelemUART) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    TelemUART_CyBtldrCommStart(void) CYSMALL ;
    void    TelemUART_CyBtldrCommStop(void) CYSMALL ;
    void    TelemUART_CyBtldrCommReset(void) CYSMALL ;
    cystatus TelemUART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus TelemUART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_TelemUART)
        #define CyBtldrCommStart    TelemUART_CyBtldrCommStart
        #define CyBtldrCommStop     TelemUART_CyBtldrCommStop
        #define CyBtldrCommReset    TelemUART_CyBtldrCommReset
        #define CyBtldrCommWrite    TelemUART_CyBtldrCommWrite
        #define CyBtldrCommRead     TelemUART_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_TelemUART) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define TelemUART_BYTE2BYTE_TIME_OUT (25u)

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define TelemUART_SET_SPACE                              (0x00u)
#define TelemUART_SET_MARK                               (0x01u)

/* Status Register definitions */
#if( (TelemUART_TX_ENABLED) || (TelemUART_HD_ENABLED) )
    #if(TelemUART_TX_INTERRUPT_ENABLED)
        #define TelemUART_TX_VECT_NUM            (uint8)TelemUART_TXInternalInterrupt__INTC_NUMBER
        #define TelemUART_TX_PRIOR_NUM           (uint8)TelemUART_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* TelemUART_TX_INTERRUPT_ENABLED */
    #if(TelemUART_TX_ENABLED)
        #define TelemUART_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define TelemUART_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define TelemUART_TX_STS_FIFO_FULL_SHIFT         (0x02u)
        #define TelemUART_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* TelemUART_TX_ENABLED */
    #if(TelemUART_HD_ENABLED)
        #define TelemUART_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define TelemUART_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define TelemUART_TX_STS_FIFO_FULL_SHIFT         (0x05u)  /*needs MD=0*/
        #define TelemUART_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* TelemUART_HD_ENABLED */
    #define TelemUART_TX_STS_COMPLETE            (uint8)(0x01u << TelemUART_TX_STS_COMPLETE_SHIFT)
    #define TelemUART_TX_STS_FIFO_EMPTY          (uint8)(0x01u << TelemUART_TX_STS_FIFO_EMPTY_SHIFT)
    #define TelemUART_TX_STS_FIFO_FULL           (uint8)(0x01u << TelemUART_TX_STS_FIFO_FULL_SHIFT)
    #define TelemUART_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << TelemUART_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (TelemUART_TX_ENABLED) || (TelemUART_HD_ENABLED)*/

#if( (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED) )
    #if(TelemUART_RX_INTERRUPT_ENABLED)
        #define TelemUART_RX_VECT_NUM            (uint8)TelemUART_RXInternalInterrupt__INTC_NUMBER
        #define TelemUART_RX_PRIOR_NUM           (uint8)TelemUART_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* TelemUART_RX_INTERRUPT_ENABLED */
    #define TelemUART_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define TelemUART_RX_STS_BREAK_SHIFT             (0x01u)
    #define TelemUART_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define TelemUART_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define TelemUART_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define TelemUART_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define TelemUART_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define TelemUART_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define TelemUART_RX_STS_MRKSPC           (uint8)(0x01u << TelemUART_RX_STS_MRKSPC_SHIFT)
    #define TelemUART_RX_STS_BREAK            (uint8)(0x01u << TelemUART_RX_STS_BREAK_SHIFT)
    #define TelemUART_RX_STS_PAR_ERROR        (uint8)(0x01u << TelemUART_RX_STS_PAR_ERROR_SHIFT)
    #define TelemUART_RX_STS_STOP_ERROR       (uint8)(0x01u << TelemUART_RX_STS_STOP_ERROR_SHIFT)
    #define TelemUART_RX_STS_OVERRUN          (uint8)(0x01u << TelemUART_RX_STS_OVERRUN_SHIFT)
    #define TelemUART_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << TelemUART_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define TelemUART_RX_STS_ADDR_MATCH       (uint8)(0x01u << TelemUART_RX_STS_ADDR_MATCH_SHIFT)
    #define TelemUART_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << TelemUART_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define TelemUART_RX_HW_MASK                     (0x7Fu)
#endif /* End (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED) */

/* Control Register definitions */
#define TelemUART_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define TelemUART_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define TelemUART_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define TelemUART_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define TelemUART_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define TelemUART_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define TelemUART_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define TelemUART_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define TelemUART_CTRL_HD_SEND               (uint8)(0x01u << TelemUART_CTRL_HD_SEND_SHIFT)
#define TelemUART_CTRL_HD_SEND_BREAK         (uint8)(0x01u << TelemUART_CTRL_HD_SEND_BREAK_SHIFT)
#define TelemUART_CTRL_MARK                  (uint8)(0x01u << TelemUART_CTRL_MARK_SHIFT)
#define TelemUART_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << TelemUART_CTRL_PARITY_TYPE0_SHIFT)
#define TelemUART_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << TelemUART_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define TelemUART_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define TelemUART_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define TelemUART_SEND_BREAK                         (0x00u)
#define TelemUART_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define TelemUART_REINIT                             (0x02u)
#define TelemUART_SEND_WAIT_REINIT                   (0x03u)

#define TelemUART_OVER_SAMPLE_8                      (8u)
#define TelemUART_OVER_SAMPLE_16                     (16u)

#define TelemUART_BIT_CENTER                         (TelemUART_OVER_SAMPLE_COUNT - 1u)

#define TelemUART_FIFO_LENGTH                        (4u)
#define TelemUART_NUMBER_OF_START_BIT                (1u)
#define TelemUART_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation*/
#define TelemUART_TXBITCTR_BREAKBITS8X   ((TelemUART_BREAK_BITS_TX * TelemUART_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation*/
#define TelemUART_TXBITCTR_BREAKBITS ((TelemUART_BREAK_BITS_TX * TelemUART_OVER_SAMPLE_COUNT) - 1u)

#define TelemUART_HALF_BIT_COUNT   \
                            (((TelemUART_OVER_SAMPLE_COUNT / 2u) + (TelemUART_USE23POLLING * 1u)) - 2u)
#if (TelemUART_OVER_SAMPLE_COUNT == TelemUART_OVER_SAMPLE_8)
    #define TelemUART_HD_TXBITCTR_INIT   (((TelemUART_BREAK_BITS_TX + \
                            TelemUART_NUMBER_OF_START_BIT) * TelemUART_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define TelemUART_RXBITCTR_INIT  ((((TelemUART_BREAK_BITS_RX + TelemUART_NUMBER_OF_START_BIT) \
                            * TelemUART_OVER_SAMPLE_COUNT) + TelemUART_HALF_BIT_COUNT) - 1u)


#else /* TelemUART_OVER_SAMPLE_COUNT == TelemUART_OVER_SAMPLE_16 */
    #define TelemUART_HD_TXBITCTR_INIT   ((8u * TelemUART_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount=16 */
    #define TelemUART_RXBITCTR_INIT      (((7u * TelemUART_OVER_SAMPLE_COUNT) - 1u) + \
                                                      TelemUART_HALF_BIT_COUNT)
#endif /* End TelemUART_OVER_SAMPLE_COUNT */
#define TelemUART_HD_RXBITCTR_INIT                   TelemUART_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 TelemUART_initVar;
#if( TelemUART_TX_ENABLED && (TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH))
    extern volatile uint8 TelemUART_txBuffer[TelemUART_TXBUFFERSIZE];
    extern volatile uint8 TelemUART_txBufferRead;
    extern uint8 TelemUART_txBufferWrite;
#endif /* End TelemUART_TX_ENABLED */
#if( ( TelemUART_RX_ENABLED || TelemUART_HD_ENABLED ) && \
     (TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH) )
    extern volatile uint8 TelemUART_rxBuffer[TelemUART_RXBUFFERSIZE];
    extern volatile uint8 TelemUART_rxBufferRead;
    extern volatile uint8 TelemUART_rxBufferWrite;
    extern volatile uint8 TelemUART_rxBufferLoopDetect;
    extern volatile uint8 TelemUART_rxBufferOverflow;
    #if (TelemUART_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 TelemUART_rxAddressMode;
        extern volatile uint8 TelemUART_rxAddressDetected;
    #endif /* End EnableHWAddress */
#endif /* End TelemUART_RX_ENABLED */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define TelemUART__B_UART__AM_SW_BYTE_BYTE 1
#define TelemUART__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define TelemUART__B_UART__AM_HW_BYTE_BY_BYTE 3
#define TelemUART__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define TelemUART__B_UART__AM_NONE 0

#define TelemUART__B_UART__NONE_REVB 0
#define TelemUART__B_UART__EVEN_REVB 1
#define TelemUART__B_UART__ODD_REVB 2
#define TelemUART__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define TelemUART_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define TelemUART_NUMBER_OF_STOP_BITS    (1u)

#if (TelemUART_RXHW_ADDRESS_ENABLED)
    #define TelemUART_RXADDRESSMODE      (0u)
    #define TelemUART_RXHWADDRESS1       (0u)
    #define TelemUART_RXHWADDRESS2       (0u)
    /* Backward compatible define */
    #define TelemUART_RXAddressMode      TelemUART_RXADDRESSMODE
#endif /* End EnableHWAddress */

#define TelemUART_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((0 << TelemUART_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << TelemUART_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << TelemUART_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << TelemUART_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << TelemUART_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << TelemUART_RX_STS_BREAK_SHIFT) \
                                        | (0 << TelemUART_RX_STS_OVERRUN_SHIFT))

#define TelemUART_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << TelemUART_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << TelemUART_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << TelemUART_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << TelemUART_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef TelemUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define TelemUART_CONTROL_REG \
                            (* (reg8 *) TelemUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define TelemUART_CONTROL_PTR \
                            (  (reg8 *) TelemUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End TelemUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(TelemUART_TX_ENABLED)
    #define TelemUART_TXDATA_REG          (* (reg8 *) TelemUART_BUART_sTX_TxShifter_u0__F0_REG)
    #define TelemUART_TXDATA_PTR          (  (reg8 *) TelemUART_BUART_sTX_TxShifter_u0__F0_REG)
    #define TelemUART_TXDATA_AUX_CTL_REG  (* (reg8 *) TelemUART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define TelemUART_TXDATA_AUX_CTL_PTR  (  (reg8 *) TelemUART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define TelemUART_TXSTATUS_REG        (* (reg8 *) TelemUART_BUART_sTX_TxSts__STATUS_REG)
    #define TelemUART_TXSTATUS_PTR        (  (reg8 *) TelemUART_BUART_sTX_TxSts__STATUS_REG)
    #define TelemUART_TXSTATUS_MASK_REG   (* (reg8 *) TelemUART_BUART_sTX_TxSts__MASK_REG)
    #define TelemUART_TXSTATUS_MASK_PTR   (  (reg8 *) TelemUART_BUART_sTX_TxSts__MASK_REG)
    #define TelemUART_TXSTATUS_ACTL_REG   (* (reg8 *) TelemUART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define TelemUART_TXSTATUS_ACTL_PTR   (  (reg8 *) TelemUART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(TelemUART_TXCLKGEN_DP)
        #define TelemUART_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) TelemUART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define TelemUART_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) TelemUART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define TelemUART_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) TelemUART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define TelemUART_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) TelemUART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define TelemUART_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) TelemUART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define TelemUART_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) TelemUART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define TelemUART_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) TelemUART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define TelemUART_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) TelemUART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define TelemUART_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) TelemUART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define TelemUART_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) TelemUART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* TelemUART_TXCLKGEN_DP */

#endif /* End TelemUART_TX_ENABLED */

#if(TelemUART_HD_ENABLED)

    #define TelemUART_TXDATA_REG             (* (reg8 *) TelemUART_BUART_sRX_RxShifter_u0__F1_REG )
    #define TelemUART_TXDATA_PTR             (  (reg8 *) TelemUART_BUART_sRX_RxShifter_u0__F1_REG )
    #define TelemUART_TXDATA_AUX_CTL_REG     (* (reg8 *) TelemUART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define TelemUART_TXDATA_AUX_CTL_PTR     (  (reg8 *) TelemUART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define TelemUART_TXSTATUS_REG           (* (reg8 *) TelemUART_BUART_sRX_RxSts__STATUS_REG )
    #define TelemUART_TXSTATUS_PTR           (  (reg8 *) TelemUART_BUART_sRX_RxSts__STATUS_REG )
    #define TelemUART_TXSTATUS_MASK_REG      (* (reg8 *) TelemUART_BUART_sRX_RxSts__MASK_REG )
    #define TelemUART_TXSTATUS_MASK_PTR      (  (reg8 *) TelemUART_BUART_sRX_RxSts__MASK_REG )
    #define TelemUART_TXSTATUS_ACTL_REG      (* (reg8 *) TelemUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define TelemUART_TXSTATUS_ACTL_PTR      (  (reg8 *) TelemUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End TelemUART_HD_ENABLED */

#if( (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED) )
    #define TelemUART_RXDATA_REG             (* (reg8 *) TelemUART_BUART_sRX_RxShifter_u0__F0_REG )
    #define TelemUART_RXDATA_PTR             (  (reg8 *) TelemUART_BUART_sRX_RxShifter_u0__F0_REG )
    #define TelemUART_RXADDRESS1_REG         (* (reg8 *) TelemUART_BUART_sRX_RxShifter_u0__D0_REG )
    #define TelemUART_RXADDRESS1_PTR         (  (reg8 *) TelemUART_BUART_sRX_RxShifter_u0__D0_REG )
    #define TelemUART_RXADDRESS2_REG         (* (reg8 *) TelemUART_BUART_sRX_RxShifter_u0__D1_REG )
    #define TelemUART_RXADDRESS2_PTR         (  (reg8 *) TelemUART_BUART_sRX_RxShifter_u0__D1_REG )
    #define TelemUART_RXDATA_AUX_CTL_REG     (* (reg8 *) TelemUART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define TelemUART_RXBITCTR_PERIOD_REG    (* (reg8 *) TelemUART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define TelemUART_RXBITCTR_PERIOD_PTR    (  (reg8 *) TelemUART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define TelemUART_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) TelemUART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define TelemUART_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) TelemUART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define TelemUART_RXBITCTR_COUNTER_REG   (* (reg8 *) TelemUART_BUART_sRX_RxBitCounter__COUNT_REG )
    #define TelemUART_RXBITCTR_COUNTER_PTR   (  (reg8 *) TelemUART_BUART_sRX_RxBitCounter__COUNT_REG )

    #define TelemUART_RXSTATUS_REG           (* (reg8 *) TelemUART_BUART_sRX_RxSts__STATUS_REG )
    #define TelemUART_RXSTATUS_PTR           (  (reg8 *) TelemUART_BUART_sRX_RxSts__STATUS_REG )
    #define TelemUART_RXSTATUS_MASK_REG      (* (reg8 *) TelemUART_BUART_sRX_RxSts__MASK_REG )
    #define TelemUART_RXSTATUS_MASK_PTR      (  (reg8 *) TelemUART_BUART_sRX_RxSts__MASK_REG )
    #define TelemUART_RXSTATUS_ACTL_REG      (* (reg8 *) TelemUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define TelemUART_RXSTATUS_ACTL_PTR      (  (reg8 *) TelemUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED) */

#if(TelemUART_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define TelemUART_INTCLOCK_CLKEN_REG     (* (reg8 *) TelemUART_IntClock__PM_ACT_CFG)
    #define TelemUART_INTCLOCK_CLKEN_PTR     (  (reg8 *) TelemUART_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define TelemUART_INTCLOCK_CLKEN_MASK    TelemUART_IntClock__PM_ACT_MSK
#endif /* End TelemUART_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(TelemUART_TX_ENABLED)
    #define TelemUART_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End TelemUART_TX_ENABLED */

#if(TelemUART_HD_ENABLED)
    #define TelemUART_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End TelemUART_HD_ENABLED */

#if( (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED) )
    #define TelemUART_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED) */


/***************************************
* Renamed global variables or defines
* for backward compatible
***************************************/

#define TelemUART_initvar                    TelemUART_initVar

#define TelemUART_RX_Enabled                 TelemUART_RX_ENABLED
#define TelemUART_TX_Enabled                 TelemUART_TX_ENABLED
#define TelemUART_HD_Enabled                 TelemUART_HD_ENABLED
#define TelemUART_RX_IntInterruptEnabled     TelemUART_RX_INTERRUPT_ENABLED
#define TelemUART_TX_IntInterruptEnabled     TelemUART_TX_INTERRUPT_ENABLED
#define TelemUART_InternalClockUsed          TelemUART_INTERNAL_CLOCK_USED
#define TelemUART_RXHW_Address_Enabled       TelemUART_RXHW_ADDRESS_ENABLED
#define TelemUART_OverSampleCount            TelemUART_OVER_SAMPLE_COUNT
#define TelemUART_ParityType                 TelemUART_PARITY_TYPE

#if( TelemUART_TX_ENABLED && (TelemUART_TXBUFFERSIZE > TelemUART_FIFO_LENGTH))
    #define TelemUART_TXBUFFER               TelemUART_txBuffer
    #define TelemUART_TXBUFFERREAD           TelemUART_txBufferRead
    #define TelemUART_TXBUFFERWRITE          TelemUART_txBufferWrite
#endif /* End TelemUART_TX_ENABLED */
#if( ( TelemUART_RX_ENABLED || TelemUART_HD_ENABLED ) && \
     (TelemUART_RXBUFFERSIZE > TelemUART_FIFO_LENGTH) )
    #define TelemUART_RXBUFFER               TelemUART_rxBuffer
    #define TelemUART_RXBUFFERREAD           TelemUART_rxBufferRead
    #define TelemUART_RXBUFFERWRITE          TelemUART_rxBufferWrite
    #define TelemUART_RXBUFFERLOOPDETECT     TelemUART_rxBufferLoopDetect
    #define TelemUART_RXBUFFER_OVERFLOW      TelemUART_rxBufferOverflow
#endif /* End TelemUART_RX_ENABLED */

#ifdef TelemUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define TelemUART_CONTROL                TelemUART_CONTROL_REG
#endif /* End TelemUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(TelemUART_TX_ENABLED)
    #define TelemUART_TXDATA                 TelemUART_TXDATA_REG
    #define TelemUART_TXSTATUS               TelemUART_TXSTATUS_REG
    #define TelemUART_TXSTATUS_MASK          TelemUART_TXSTATUS_MASK_REG
    #define TelemUART_TXSTATUS_ACTL          TelemUART_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(TelemUART_TXCLKGEN_DP)
        #define TelemUART_TXBITCLKGEN_CTR        TelemUART_TXBITCLKGEN_CTR_REG
        #define TelemUART_TXBITCLKTX_COMPLETE    TelemUART_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define TelemUART_TXBITCTR_PERIOD        TelemUART_TXBITCTR_PERIOD_REG
        #define TelemUART_TXBITCTR_CONTROL       TelemUART_TXBITCTR_CONTROL_REG
        #define TelemUART_TXBITCTR_COUNTER       TelemUART_TXBITCTR_COUNTER_REG
    #endif /* TelemUART_TXCLKGEN_DP */
#endif /* End TelemUART_TX_ENABLED */

#if(TelemUART_HD_ENABLED)
    #define TelemUART_TXDATA                 TelemUART_TXDATA_REG
    #define TelemUART_TXSTATUS               TelemUART_TXSTATUS_REG
    #define TelemUART_TXSTATUS_MASK          TelemUART_TXSTATUS_MASK_REG
    #define TelemUART_TXSTATUS_ACTL          TelemUART_TXSTATUS_ACTL_REG
#endif /* End TelemUART_HD_ENABLED */

#if( (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED) )
    #define TelemUART_RXDATA                 TelemUART_RXDATA_REG
    #define TelemUART_RXADDRESS1             TelemUART_RXADDRESS1_REG
    #define TelemUART_RXADDRESS2             TelemUART_RXADDRESS2_REG
    #define TelemUART_RXBITCTR_PERIOD        TelemUART_RXBITCTR_PERIOD_REG
    #define TelemUART_RXBITCTR_CONTROL       TelemUART_RXBITCTR_CONTROL_REG
    #define TelemUART_RXBITCTR_COUNTER       TelemUART_RXBITCTR_COUNTER_REG
    #define TelemUART_RXSTATUS               TelemUART_RXSTATUS_REG
    #define TelemUART_RXSTATUS_MASK          TelemUART_RXSTATUS_MASK_REG
    #define TelemUART_RXSTATUS_ACTL          TelemUART_RXSTATUS_ACTL_REG
#endif /* End  (TelemUART_RX_ENABLED) || (TelemUART_HD_ENABLED) */

#if(TelemUART_INTERNAL_CLOCK_USED)
    #define TelemUART_INTCLOCK_CLKEN         TelemUART_INTCLOCK_CLKEN_REG
#endif /* End TelemUART_INTERNAL_CLOCK_USED */

#define TelemUART_WAIT_FOR_COMLETE_REINIT    TelemUART_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_TelemUART_H */


/* [] END OF FILE */
