/*******************************************************************************
* File Name: OnBoardLED.h  
* Version 2.5
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_OnBoardLED_H) /* Pins OnBoardLED_H */
#define CY_PINS_OnBoardLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "OnBoardLED_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    OnBoardLED_Write(uint8 value) ;
void    OnBoardLED_SetDriveMode(uint8 mode) ;
uint8   OnBoardLED_ReadDataReg(void) ;
uint8   OnBoardLED_Read(void) ;
uint8   OnBoardLED_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define OnBoardLED_DRIVE_MODE_BITS        (3)
#define OnBoardLED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - OnBoardLED_DRIVE_MODE_BITS))
#define OnBoardLED_DRIVE_MODE_SHIFT       (0x00u)
#define OnBoardLED_DRIVE_MODE_MASK        (0x07u << OnBoardLED_DRIVE_MODE_SHIFT)

#define OnBoardLED_DM_ALG_HIZ         (0x00u << OnBoardLED_DRIVE_MODE_SHIFT)
#define OnBoardLED_DM_DIG_HIZ         (0x01u << OnBoardLED_DRIVE_MODE_SHIFT)
#define OnBoardLED_DM_RES_UP          (0x02u << OnBoardLED_DRIVE_MODE_SHIFT)
#define OnBoardLED_DM_RES_DWN         (0x03u << OnBoardLED_DRIVE_MODE_SHIFT)
#define OnBoardLED_DM_OD_LO           (0x04u << OnBoardLED_DRIVE_MODE_SHIFT)
#define OnBoardLED_DM_OD_HI           (0x05u << OnBoardLED_DRIVE_MODE_SHIFT)
#define OnBoardLED_DM_STRONG          (0x06u << OnBoardLED_DRIVE_MODE_SHIFT)
#define OnBoardLED_DM_RES_UPDWN       (0x07u << OnBoardLED_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define OnBoardLED_MASK               OnBoardLED__MASK
#define OnBoardLED_SHIFT              OnBoardLED__SHIFT
#define OnBoardLED_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define OnBoardLED_PS                     (* (reg32 *) OnBoardLED__PS)
/* Port Configuration */
#define OnBoardLED_PC                     (* (reg32 *) OnBoardLED__PC)
/* Data Register */
#define OnBoardLED_DR                     (* (reg32 *) OnBoardLED__DR)
/* Input Buffer Disable Override */
#define OnBoardLED_INP_DIS                (* (reg32 *) OnBoardLED__PC2)


#if defined(OnBoardLED__INTSTAT)  /* Interrupt Registers */

    #define OnBoardLED_INTSTAT                (* (reg32 *) OnBoardLED__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins OnBoardLED_H */


/* [] END OF FILE */
