/*
 * pitDrive.c
 *
 *  Created on: Nov 7, 2013
 *      Author: superman
 */
#include "xgpio.h"          // Provides access to PB GPIO driver.
#include <stdio.h>          // xil_printf and so forth.
#include "platform.h"       // Enables caching and other system stuff.
#include "mb_interface.h"   // provides the microblaze interrupt enables, etc.
#include "xintc_l.h"        // Provides handy macros for the interrupt controller.


void reloadcounter(){
	int reg = XGpio_ReadReg(XPAR_PIT_0_BASEADDR, 0x0);
	reg = reg ^4;
	XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0x0, reg);
}
void changeInterrupt(){

	int reg = XGpio_ReadReg(XPAR_PIT_0_BASEADDR, 0x0);
	reg = reg ^2;
	XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0x0, reg);
}
void changeCounter(){
	int reg = XGpio_ReadReg(XPAR_PIT_0_BASEADDR, 0x0);
	if(reg << 31 == 0)
		XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0x0, reg+1);
	else
		XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0x0, reg-1);
}
void freqency(int enter){

	XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0x0, 0x00000006);
	XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0x4, enter);
	XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0x0, 0x00000007);

}
