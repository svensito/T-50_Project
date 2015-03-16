/*******************************************************************************
* File Name: SpareLight.h  
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

#if !defined(CY_PINS_SpareLight_H) /* Pins SpareLight_H */
#define CY_PINS_SpareLight_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SpareLight_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SpareLight_Write(uint8 value) ;
void    SpareLight_SetDriveMode(uint8 mode) ;
uint8   SpareLight_ReadDataReg(void) ;
uint8   SpareLight_Read(void) ;
uint8   SpareLight_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SpareLight_DRIVE_MODE_BITS        (3)
#define SpareLight_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SpareLight_DRIVE_MODE_BITS))
#define SpareLight_DRIVE_MODE_SHIFT       (0x00u)
#define SpareLight_DRIVE_MODE_MASK        (0x07u << SpareLight_DRIVE_MODE_SHIFT)

#define SpareLight_DM_ALG_HIZ         (0x00u << SpareLight_DRIVE_MODE_SHIFT)
#define SpareLight_DM_DIG_HIZ         (0x01u << SpareLight_DRIVE_MODE_SHIFT)
#define SpareLight_DM_RES_UP          (0x02u << SpareLight_DRIVE_MODE_SHIFT)
#define SpareLight_DM_RES_DWN         (0x03u << SpareLight_DRIVE_MODE_SHIFT)
#define SpareLight_DM_OD_LO           (0x04u << SpareLight_DRIVE_MODE_SHIFT)
#define SpareLight_DM_OD_HI           (0x05u << SpareLight_DRIVE_MODE_SHIFT)
#define SpareLight_DM_STRONG          (0x06u << SpareLight_DRIVE_MODE_SHIFT)
#define SpareLight_DM_RES_UPDWN       (0x07u << SpareLight_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define SpareLight_MASK               SpareLight__MASK
#define SpareLight_SHIFT              SpareLight__SHIFT
#define SpareLight_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SpareLight_PS                     (* (reg32 *) SpareLight__PS)
/* Port Configuration */
#define SpareLight_PC                     (* (reg32 *) SpareLight__PC)
/* Data Register */
#define SpareLight_DR                     (* (reg32 *) SpareLight__DR)
/* Input Buffer Disable Override */
#define SpareLight_INP_DIS                (* (reg32 *) SpareLight__PC2)


#if defined(SpareLight__INTSTAT)  /* Interrupt Registers */

    #define SpareLight_INTSTAT                (* (reg32 *) SpareLight__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins SpareLight_H */


/* [] END OF FILE */
