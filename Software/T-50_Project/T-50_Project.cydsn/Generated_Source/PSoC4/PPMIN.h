/*******************************************************************************
* File Name: PPMIN.h  
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

#if !defined(CY_PINS_PPMIN_H) /* Pins PPMIN_H */
#define CY_PINS_PPMIN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PPMIN_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PPMIN_Write(uint8 value) ;
void    PPMIN_SetDriveMode(uint8 mode) ;
uint8   PPMIN_ReadDataReg(void) ;
uint8   PPMIN_Read(void) ;
uint8   PPMIN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PPMIN_DRIVE_MODE_BITS        (3)
#define PPMIN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PPMIN_DRIVE_MODE_BITS))

#define PPMIN_DM_ALG_HIZ         (0x00u)
#define PPMIN_DM_DIG_HIZ         (0x01u)
#define PPMIN_DM_RES_UP          (0x02u)
#define PPMIN_DM_RES_DWN         (0x03u)
#define PPMIN_DM_OD_LO           (0x04u)
#define PPMIN_DM_OD_HI           (0x05u)
#define PPMIN_DM_STRONG          (0x06u)
#define PPMIN_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PPMIN_MASK               PPMIN__MASK
#define PPMIN_SHIFT              PPMIN__SHIFT
#define PPMIN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PPMIN_PS                     (* (reg32 *) PPMIN__PS)
/* Port Configuration */
#define PPMIN_PC                     (* (reg32 *) PPMIN__PC)
/* Data Register */
#define PPMIN_DR                     (* (reg32 *) PPMIN__DR)
/* Input Buffer Disable Override */
#define PPMIN_INP_DIS                (* (reg32 *) PPMIN__PC2)


#if defined(PPMIN__INTSTAT)  /* Interrupt Registers */

    #define PPMIN_INTSTAT                (* (reg32 *) PPMIN__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PPMIN_DRIVE_MODE_SHIFT       (0x00u)
#define PPMIN_DRIVE_MODE_MASK        (0x07u << PPMIN_DRIVE_MODE_SHIFT)


#endif /* End Pins PPMIN_H */


/* [] END OF FILE */
