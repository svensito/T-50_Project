/*******************************************************************************
* File Name: In_Speed.h  
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

#if !defined(CY_PINS_In_Speed_H) /* Pins In_Speed_H */
#define CY_PINS_In_Speed_H

#include "cytypes.h"
#include "cyfitter.h"
#include "In_Speed_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    In_Speed_Write(uint8 value) ;
void    In_Speed_SetDriveMode(uint8 mode) ;
uint8   In_Speed_ReadDataReg(void) ;
uint8   In_Speed_Read(void) ;
uint8   In_Speed_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define In_Speed_DRIVE_MODE_BITS        (3)
#define In_Speed_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - In_Speed_DRIVE_MODE_BITS))

#define In_Speed_DM_ALG_HIZ         (0x00u)
#define In_Speed_DM_DIG_HIZ         (0x01u)
#define In_Speed_DM_RES_UP          (0x02u)
#define In_Speed_DM_RES_DWN         (0x03u)
#define In_Speed_DM_OD_LO           (0x04u)
#define In_Speed_DM_OD_HI           (0x05u)
#define In_Speed_DM_STRONG          (0x06u)
#define In_Speed_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define In_Speed_MASK               In_Speed__MASK
#define In_Speed_SHIFT              In_Speed__SHIFT
#define In_Speed_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define In_Speed_PS                     (* (reg32 *) In_Speed__PS)
/* Port Configuration */
#define In_Speed_PC                     (* (reg32 *) In_Speed__PC)
/* Data Register */
#define In_Speed_DR                     (* (reg32 *) In_Speed__DR)
/* Input Buffer Disable Override */
#define In_Speed_INP_DIS                (* (reg32 *) In_Speed__PC2)


#if defined(In_Speed__INTSTAT)  /* Interrupt Registers */

    #define In_Speed_INTSTAT                (* (reg32 *) In_Speed__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define In_Speed_DRIVE_MODE_SHIFT       (0x00u)
#define In_Speed_DRIVE_MODE_MASK        (0x07u << In_Speed_DRIVE_MODE_SHIFT)


#endif /* End Pins In_Speed_H */


/* [] END OF FILE */
