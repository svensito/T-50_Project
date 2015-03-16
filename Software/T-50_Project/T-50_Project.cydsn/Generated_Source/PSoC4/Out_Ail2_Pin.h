/*******************************************************************************
* File Name: Out_Ail2_Pin.h  
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

#if !defined(CY_PINS_Out_Ail2_Pin_H) /* Pins Out_Ail2_Pin_H */
#define CY_PINS_Out_Ail2_Pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Out_Ail2_Pin_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Out_Ail2_Pin_Write(uint8 value) ;
void    Out_Ail2_Pin_SetDriveMode(uint8 mode) ;
uint8   Out_Ail2_Pin_ReadDataReg(void) ;
uint8   Out_Ail2_Pin_Read(void) ;
uint8   Out_Ail2_Pin_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Out_Ail2_Pin_DRIVE_MODE_BITS        (3)
#define Out_Ail2_Pin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Out_Ail2_Pin_DRIVE_MODE_BITS))
#define Out_Ail2_Pin_DRIVE_MODE_SHIFT       (0x00u)
#define Out_Ail2_Pin_DRIVE_MODE_MASK        (0x07u << Out_Ail2_Pin_DRIVE_MODE_SHIFT)

#define Out_Ail2_Pin_DM_ALG_HIZ         (0x00u << Out_Ail2_Pin_DRIVE_MODE_SHIFT)
#define Out_Ail2_Pin_DM_DIG_HIZ         (0x01u << Out_Ail2_Pin_DRIVE_MODE_SHIFT)
#define Out_Ail2_Pin_DM_RES_UP          (0x02u << Out_Ail2_Pin_DRIVE_MODE_SHIFT)
#define Out_Ail2_Pin_DM_RES_DWN         (0x03u << Out_Ail2_Pin_DRIVE_MODE_SHIFT)
#define Out_Ail2_Pin_DM_OD_LO           (0x04u << Out_Ail2_Pin_DRIVE_MODE_SHIFT)
#define Out_Ail2_Pin_DM_OD_HI           (0x05u << Out_Ail2_Pin_DRIVE_MODE_SHIFT)
#define Out_Ail2_Pin_DM_STRONG          (0x06u << Out_Ail2_Pin_DRIVE_MODE_SHIFT)
#define Out_Ail2_Pin_DM_RES_UPDWN       (0x07u << Out_Ail2_Pin_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Out_Ail2_Pin_MASK               Out_Ail2_Pin__MASK
#define Out_Ail2_Pin_SHIFT              Out_Ail2_Pin__SHIFT
#define Out_Ail2_Pin_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Out_Ail2_Pin_PS                     (* (reg32 *) Out_Ail2_Pin__PS)
/* Port Configuration */
#define Out_Ail2_Pin_PC                     (* (reg32 *) Out_Ail2_Pin__PC)
/* Data Register */
#define Out_Ail2_Pin_DR                     (* (reg32 *) Out_Ail2_Pin__DR)
/* Input Buffer Disable Override */
#define Out_Ail2_Pin_INP_DIS                (* (reg32 *) Out_Ail2_Pin__PC2)


#if defined(Out_Ail2_Pin__INTSTAT)  /* Interrupt Registers */

    #define Out_Ail2_Pin_INTSTAT                (* (reg32 *) Out_Ail2_Pin__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Out_Ail2_Pin_H */


/* [] END OF FILE */
