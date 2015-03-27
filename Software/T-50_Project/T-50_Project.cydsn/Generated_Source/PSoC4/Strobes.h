/*******************************************************************************
* File Name: Strobes.h  
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

#if !defined(CY_PINS_Strobes_H) /* Pins Strobes_H */
#define CY_PINS_Strobes_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Strobes_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Strobes_Write(uint8 value) ;
void    Strobes_SetDriveMode(uint8 mode) ;
uint8   Strobes_ReadDataReg(void) ;
uint8   Strobes_Read(void) ;
uint8   Strobes_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Strobes_DRIVE_MODE_BITS        (3)
#define Strobes_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Strobes_DRIVE_MODE_BITS))

#define Strobes_DM_ALG_HIZ         (0x00u)
#define Strobes_DM_DIG_HIZ         (0x01u)
#define Strobes_DM_RES_UP          (0x02u)
#define Strobes_DM_RES_DWN         (0x03u)
#define Strobes_DM_OD_LO           (0x04u)
#define Strobes_DM_OD_HI           (0x05u)
#define Strobes_DM_STRONG          (0x06u)
#define Strobes_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Strobes_MASK               Strobes__MASK
#define Strobes_SHIFT              Strobes__SHIFT
#define Strobes_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Strobes_PS                     (* (reg32 *) Strobes__PS)
/* Port Configuration */
#define Strobes_PC                     (* (reg32 *) Strobes__PC)
/* Data Register */
#define Strobes_DR                     (* (reg32 *) Strobes__DR)
/* Input Buffer Disable Override */
#define Strobes_INP_DIS                (* (reg32 *) Strobes__PC2)


#if defined(Strobes__INTSTAT)  /* Interrupt Registers */

    #define Strobes_INTSTAT                (* (reg32 *) Strobes__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Strobes_DRIVE_MODE_SHIFT       (0x00u)
#define Strobes_DRIVE_MODE_MASK        (0x07u << Strobes_DRIVE_MODE_SHIFT)


#endif /* End Pins Strobes_H */


/* [] END OF FILE */
