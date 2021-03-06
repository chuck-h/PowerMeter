/*******************************************************************************
* File Name: PumpDrive.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "PumpDrive.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        PumpDrive_PC =   (PumpDrive_PC & \
                                (uint32)(~(uint32)(PumpDrive_DRIVE_MODE_IND_MASK << (PumpDrive_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (PumpDrive_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: PumpDrive_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void PumpDrive_Write(uint8 value) 
{
    uint8 drVal = (uint8)(PumpDrive_DR & (uint8)(~PumpDrive_MASK));
    drVal = (drVal | ((uint8)(value << PumpDrive_SHIFT) & PumpDrive_MASK));
    PumpDrive_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: PumpDrive_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  PumpDrive_DM_STRONG     Strong Drive 
*  PumpDrive_DM_OD_HI      Open Drain, Drives High 
*  PumpDrive_DM_OD_LO      Open Drain, Drives Low 
*  PumpDrive_DM_RES_UP     Resistive Pull Up 
*  PumpDrive_DM_RES_DWN    Resistive Pull Down 
*  PumpDrive_DM_RES_UPDWN  Resistive Pull Up/Down 
*  PumpDrive_DM_DIG_HIZ    High Impedance Digital 
*  PumpDrive_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void PumpDrive_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(PumpDrive__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: PumpDrive_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro PumpDrive_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PumpDrive_Read(void) 
{
    return (uint8)((PumpDrive_PS & PumpDrive_MASK) >> PumpDrive_SHIFT);
}


/*******************************************************************************
* Function Name: PumpDrive_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 PumpDrive_ReadDataReg(void) 
{
    return (uint8)((PumpDrive_DR & PumpDrive_MASK) >> PumpDrive_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PumpDrive_INTSTAT) 

    /*******************************************************************************
    * Function Name: PumpDrive_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 PumpDrive_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(PumpDrive_INTSTAT & PumpDrive_MASK);
		PumpDrive_INTSTAT = maskedStatus;
        return maskedStatus >> PumpDrive_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
