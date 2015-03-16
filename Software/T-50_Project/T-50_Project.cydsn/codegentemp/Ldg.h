/*******************************************************************************
* File Name: Ldg.h  
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

#if !defined(CY_PINS_Ldg_H) /* Pins Ldg_H */
#define CY_PINS_Ldg_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Ldg_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Ldg_Write(uint8 value) ;
void    Ldg_SetDriveMode(uint8 mode) ;
uint8   Ldg_ReadDataReg(void) ;
uint8   Ldg_Read(void) ;
uint8   Ldg_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Ldg_DRIVE_MODE_BITS        (3)
#define Ldg_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Ldg_DRIVE_MODE_BITS))
#define Ldg_DRIVE_MODE_SHIFT       (0x00u)
#define Ldg_DRIVE_MODE_MASK        (0x07u << Ldg_DRIVE_MODE_SHIFT)

#define Ldg_DM_ALG_HIZ         (0x00u << Ldg_DRIVE_MODE_SHIFT)
#define Ldg_DM_DIG_HIZ         (0x01u << Ldg_DRIVE_MODE_SHIFT)
#define Ldg_DM_RES_UP          (0x02u << Ldg_DRIVE_MODE_SHIFT)
#define Ldg_DM_RES_DWN         (0x03u << Ldg_DRIVE_MODE_SHIFT)
#define Ldg_DM_OD_LO           (0x04u << Ldg_DRIVE_MODE_SHIFT)
#define Ldg_DM_OD_HI           (0x05u << Ldg_DRIVE_MODE_SHIFT)
#define Ldg_DM_STRONG          (0x06u << Ldg_DRIVE_MODE_SHIFT)
#define Ldg_DM_RES_UPDWN       (0x07u << Ldg_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Ldg_MASK               Ldg__MASK
#define Ldg_SHIFT              Ldg__SHIFT
#define Ldg_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Ldg_PS                     (* (reg32 *) Ldg__PS)
/* Port Configuration */
#define Ldg_PC                     (* (reg32 *) Ldg__PC)
/* Data Register */
#define Ldg_DR                     (* (reg32 *) Ldg__DR)
/* Input Buffer Disable Override */
#define Ldg_INP_DIS                (* (reg32 *) Ldg__PC2)


#if defined(Ldg__INTSTAT)  /* Interrupt Registers */

    #define Ldg_INTSTAT                (* (reg32 *) Ldg__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Ldg_H */


/* [] END OF FILE */
