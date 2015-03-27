/*******************************************************************************
* File Name: Collis.h  
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

#if !defined(CY_PINS_Collis_H) /* Pins Collis_H */
#define CY_PINS_Collis_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Collis_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Collis_Write(uint8 value) ;
void    Collis_SetDriveMode(uint8 mode) ;
uint8   Collis_ReadDataReg(void) ;
uint8   Collis_Read(void) ;
uint8   Collis_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Collis_DRIVE_MODE_BITS        (3)
#define Collis_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Collis_DRIVE_MODE_BITS))

#define Collis_DM_ALG_HIZ         (0x00u)
#define Collis_DM_DIG_HIZ         (0x01u)
#define Collis_DM_RES_UP          (0x02u)
#define Collis_DM_RES_DWN         (0x03u)
#define Collis_DM_OD_LO           (0x04u)
#define Collis_DM_OD_HI           (0x05u)
#define Collis_DM_STRONG          (0x06u)
#define Collis_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Collis_MASK               Collis__MASK
#define Collis_SHIFT              Collis__SHIFT
#define Collis_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Collis_PS                     (* (reg32 *) Collis__PS)
/* Port Configuration */
#define Collis_PC                     (* (reg32 *) Collis__PC)
/* Data Register */
#define Collis_DR                     (* (reg32 *) Collis__DR)
/* Input Buffer Disable Override */
#define Collis_INP_DIS                (* (reg32 *) Collis__PC2)


#if defined(Collis__INTSTAT)  /* Interrupt Registers */

    #define Collis_INTSTAT                (* (reg32 *) Collis__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Collis_DRIVE_MODE_SHIFT       (0x00u)
#define Collis_DRIVE_MODE_MASK        (0x07u << Collis_DRIVE_MODE_SHIFT)


#endif /* End Pins Collis_H */


/* [] END OF FILE */
