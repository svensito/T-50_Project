/*******************************************************************************
* File Name: NavLR.h  
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

#if !defined(CY_PINS_NavLR_H) /* Pins NavLR_H */
#define CY_PINS_NavLR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "NavLR_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    NavLR_Write(uint8 value) ;
void    NavLR_SetDriveMode(uint8 mode) ;
uint8   NavLR_ReadDataReg(void) ;
uint8   NavLR_Read(void) ;
uint8   NavLR_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define NavLR_DRIVE_MODE_BITS        (3)
#define NavLR_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - NavLR_DRIVE_MODE_BITS))
#define NavLR_DRIVE_MODE_SHIFT       (0x00u)
#define NavLR_DRIVE_MODE_MASK        (0x07u << NavLR_DRIVE_MODE_SHIFT)

#define NavLR_DM_ALG_HIZ         (0x00u << NavLR_DRIVE_MODE_SHIFT)
#define NavLR_DM_DIG_HIZ         (0x01u << NavLR_DRIVE_MODE_SHIFT)
#define NavLR_DM_RES_UP          (0x02u << NavLR_DRIVE_MODE_SHIFT)
#define NavLR_DM_RES_DWN         (0x03u << NavLR_DRIVE_MODE_SHIFT)
#define NavLR_DM_OD_LO           (0x04u << NavLR_DRIVE_MODE_SHIFT)
#define NavLR_DM_OD_HI           (0x05u << NavLR_DRIVE_MODE_SHIFT)
#define NavLR_DM_STRONG          (0x06u << NavLR_DRIVE_MODE_SHIFT)
#define NavLR_DM_RES_UPDWN       (0x07u << NavLR_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define NavLR_MASK               NavLR__MASK
#define NavLR_SHIFT              NavLR__SHIFT
#define NavLR_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define NavLR_PS                     (* (reg32 *) NavLR__PS)
/* Port Configuration */
#define NavLR_PC                     (* (reg32 *) NavLR__PC)
/* Data Register */
#define NavLR_DR                     (* (reg32 *) NavLR__DR)
/* Input Buffer Disable Override */
#define NavLR_INP_DIS                (* (reg32 *) NavLR__PC2)


#if defined(NavLR__INTSTAT)  /* Interrupt Registers */

    #define NavLR_INTSTAT                (* (reg32 *) NavLR__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins NavLR_H */


/* [] END OF FILE */
