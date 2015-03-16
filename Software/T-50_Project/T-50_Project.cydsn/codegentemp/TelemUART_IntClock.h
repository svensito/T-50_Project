/*******************************************************************************
* File Name: TelemUART_IntClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_TelemUART_IntClock_H)
#define CY_CLOCK_TelemUART_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void TelemUART_IntClock_StartEx(uint32 alignClkDiv);
#define TelemUART_IntClock_Start() \
    TelemUART_IntClock_StartEx(TelemUART_IntClock__PA_DIV_ID)

#else

void TelemUART_IntClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void TelemUART_IntClock_Stop(void);

void TelemUART_IntClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 TelemUART_IntClock_GetDividerRegister(void);
uint8  TelemUART_IntClock_GetFractionalDividerRegister(void);

#define TelemUART_IntClock_Enable()                         TelemUART_IntClock_Start()
#define TelemUART_IntClock_Disable()                        TelemUART_IntClock_Stop()
#define TelemUART_IntClock_SetDividerRegister(clkDivider, reset)  \
    TelemUART_IntClock_SetFractionalDividerRegister((clkDivider), 0u)
#define TelemUART_IntClock_SetDivider(clkDivider)           TelemUART_IntClock_SetDividerRegister((clkDivider), 1u)
#define TelemUART_IntClock_SetDividerValue(clkDivider)      TelemUART_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define TelemUART_IntClock_DIV_ID     TelemUART_IntClock__DIV_ID

#define TelemUART_IntClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define TelemUART_IntClock_CTRL_REG   (*(reg32 *)TelemUART_IntClock__CTRL_REGISTER)
#define TelemUART_IntClock_DIV_REG    (*(reg32 *)TelemUART_IntClock__DIV_REGISTER)

#define TelemUART_IntClock_CMD_DIV_SHIFT          (0u)
#define TelemUART_IntClock_CMD_PA_DIV_SHIFT       (8u)
#define TelemUART_IntClock_CMD_DISABLE_SHIFT      (30u)
#define TelemUART_IntClock_CMD_ENABLE_SHIFT       (31u)

#define TelemUART_IntClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << TelemUART_IntClock_CMD_DISABLE_SHIFT))
#define TelemUART_IntClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << TelemUART_IntClock_CMD_ENABLE_SHIFT))

#define TelemUART_IntClock_DIV_FRAC_MASK  (0x000000F8u)
#define TelemUART_IntClock_DIV_FRAC_SHIFT (3u)
#define TelemUART_IntClock_DIV_INT_MASK   (0xFFFFFF00u)
#define TelemUART_IntClock_DIV_INT_SHIFT  (8u)

#else 

#define TelemUART_IntClock_DIV_REG        (*(reg32 *)TelemUART_IntClock__REGISTER)
#define TelemUART_IntClock_ENABLE_REG     TelemUART_IntClock_DIV_REG
#define TelemUART_IntClock_DIV_FRAC_MASK  TelemUART_IntClock__FRAC_MASK
#define TelemUART_IntClock_DIV_FRAC_SHIFT (16u)
#define TelemUART_IntClock_DIV_INT_MASK   TelemUART_IntClock__DIVIDER_MASK
#define TelemUART_IntClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_TelemUART_IntClock_H) */

/* [] END OF FILE */
