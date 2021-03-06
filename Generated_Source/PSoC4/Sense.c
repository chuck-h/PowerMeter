/*******************************************************************************
* File Name: Sense.c  
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
#include "Sense.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Sense_PC =   (Sense_PC & \
                                (uint32)(~(uint32)(Sense_DRIVE_MODE_IND_MASK << (Sense_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Sense_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Sense_Write
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
void Sense_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Sense_DR & (uint8)(~Sense_MASK));
    drVal = (drVal | ((uint8)(value << Sense_SHIFT) & Sense_MASK));
    Sense_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Sense_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Sense_DM_STRONG     Strong Drive 
*  Sense_DM_OD_HI      Open Drain, Drives High 
*  Sense_DM_OD_LO      Open Drain, Drives Low 
*  Sense_DM_RES_UP     Resistive Pull Up 
*  Sense_DM_RES_DWN    Resistive Pull Down 
*  Sense_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Sense_DM_DIG_HIZ    High Impedance Digital 
*  Sense_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Sense_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Sense__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Sense_Read
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
*  Macro Sense_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Sense_Read(void) 
{
    return (uint8)((Sense_PS & Sense_MASK) >> Sense_SHIFT);
}


/*******************************************************************************
* Function Name: Sense_ReadDataReg
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
uint8 Sense_ReadDataReg(void) 
{
    return (uint8)((Sense_DR & Sense_MASK) >> Sense_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Sense_INTSTAT) 

    /*******************************************************************************
    * Function Name: Sense_ClearInterrupt
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
    uint8 Sense_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Sense_INTSTAT & Sense_MASK);
		Sense_INTSTAT = maskedStatus;
        return maskedStatus >> Sense_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
