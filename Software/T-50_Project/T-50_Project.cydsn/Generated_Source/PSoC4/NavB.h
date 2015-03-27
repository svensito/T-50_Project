/*******************************************************************************
* File Name: NavB.h  
* Version 2.10
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

#if !defined(CY_PINS_NavB_H) /* Pins NavB_H */
#define CY_PINS_NavB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "NavB_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    NavB_Write(uint8 value) ;
void    NavB_SetDriveMode(uint8 mode) ;
uint8   NavB_ReadDataReg(void) ;
uint8   NavB_Read(void) ;
uint8   NavB_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define NavB_DRIVE_MODE_BITS        (3)
#define NavB_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - NavB_DRIVE_MODE_BITS))

#define NavB_DM_ALG_HIZ         (0x00u)
#define NavB_DM_DIG_HIZ         (0x01u)
#define NavB_DM_RES_UP          (0x02u)
#define NavB_DM_RES_DWN         (0x03u)
#define NavB_DM_OD_LO           (0x04u)
#define NavB_DM_OD_HI           (0x05u)
#define NavB_DM_STRONG          (0x06u)
#define NavB_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define NavB_MASK               NavB__MASK
#define NavB_SHIFT              NavB__SHIFT
#define NavB_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define NavB_PS                     (* (reg32 *) NavB__PS)
/* Port Configuration */
#define NavB_PC                     (* (reg32 *) NavB__PC)
/* Data Register */
#define NavB_DR                     (* (reg32 *) NavB__DR)
/* Input Buffer Disable Override */
#define NavB_INP_DIS                (* (reg32 *) NavB__PC2)


#if defined(NavB__INTSTAT)  /* Interrupt Registers */

    #define NavB_INTSTAT                (* (reg32 *) NavB__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define NavB_DRIVE_MODE_SHIFT       (0x00u)
#define NavB_DRIVE_MODE_MASK        (0x07u << NavB_DRIVE_MODE_SHIFT)


#endif /* End Pins NavB_H */


/* [] END OF FILE */
