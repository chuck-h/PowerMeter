/*******************************************************************************
* File Name: Host_UART_rx.c  
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
#include "Host_UART_rx.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Host_UART_rx_PC =   (Host_UART_rx_PC & \
                                (uint32)(~(uint32)(Host_UART_rx_DRIVE_MODE_IND_MASK << (Host_UART_rx_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Host_UART_rx_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Host_UART_rx_Write
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
void Host_UART_rx_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Host_UART_rx_DR & (uint8)(~Host_UART_rx_MASK));
    drVal = (drVal | ((uint8)(value << Host_UART_rx_SHIFT) & Host_UART_rx_MASK));
    Host_UART_rx_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Host_UART_rx_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Host_UART_rx_DM_STRONG     Strong Drive 
*  Host_UART_rx_DM_OD_HI      Open Drain, Drives High 
*  Host_UART_rx_DM_OD_LO      Open Drain, Drives Low 
*  Host_UART_rx_DM_RES_UP     Resistive Pull Up 
*  Host_UART_rx_DM_RES_DWN    Resistive Pull Down 
*  Host_UART_rx_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Host_UART_rx_DM_DIG_HIZ    High Impedance Digital 
*  Host_UART_rx_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Host_UART_rx_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Host_UART_rx__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Host_UART_rx_Read
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
*  Macro Host_UART_rx_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Host_UART_rx_Read(void) 
{
    return (uint8)((Host_UART_rx_PS & Host_UART_rx_MASK) >> Host_UART_rx_SHIFT);
}


/*******************************************************************************
* Function Name: Host_UART_rx_ReadDataReg
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
uint8 Host_UART_rx_ReadDataReg(void) 
{
    return (uint8)((Host_UART_rx_DR & Host_UART_rx_MASK) >> Host_UART_rx_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Host_UART_rx_INTSTAT) 

    /*******************************************************************************
    * Function Name: Host_UART_rx_ClearInterrupt
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
    uint8 Host_UART_rx_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Host_UART_rx_INTSTAT & Host_UART_rx_MASK);
		Host_UART_rx_INTSTAT = maskedStatus;
        return maskedStatus >> Host_UART_rx_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
