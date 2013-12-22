#include "xac97_l.h"
#include "xparameters.h"
/*
 * Do not use XAC97_WriteFifo. Use the macro that it uses instead: XAC97_mSetInFifoData.
 * This is because it uses a buggy macro XAC97_isInFIFOFull
 * (which you may need to use when polling but don't use it when you do the interrupts).
 * If you use XAC97_isInFIFOFull please know that it is buggy and is not always right.
 * When writing your interrupt handler for the AC97 it is better to write a set number of samples into the AC97 FIFO than to write samples until XAC97_isInFIFOFull.
 * Otherwise your game may hang/freeze randomly.
 * If your sounds are very static-y, it is probably because you are writing too much to the FIFO. Do not use XAC97_WriteFifo.
 * Even though it does 'wait' until the FIFO is not empty before writing (ensuring the sound does not get static-y), it messes up A LOT and will lead to you either overrunning your FIFO or underrunning your FIFO.
 * To avoid the 'static-y' sounds, have your interrupt handler output up to 256 entries (use a for-loop) each time it is called.
 * To be safe, choose a smaller number (100).
 * If your sounds are still very static-y, make sure you have your headphones plugged into the right jack.
 * Remember that .wav files are binary files. You must use the “b” character when opening the file with fopen().
*/

//# Constrain the AC97 clock frequency NET AC97_BIT_CLK PERIOD = 81380 ps;
Xuint32 soundData[] = {1, 2, 3, 4};
int main(){

int BaseAddress = 0;//XPAR_AXI_AC97_0_BASEADDR;
	XAC97_HardReset(XPAR_AXI_AC97_0_BASEADDR);
	Xuint32 test;
	 //XAC97_mSetInFifoData;
	XAC97_PlayAudio(BaseAddress,soundData,
			     soundData+50);

	 /** Reset audio codec **/
	  XAC97_SoftReset(BaseAddress);

	  /** Wait until we receive the ready signal **/
	  XAC97_AwaitCodecReady(BaseAddress);
	    XAC97_WriteReg(BaseAddress, AC97_GeneralPurpose, AC97_GP_ADC_DAC_LOOPBACK);



	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, 0, 20);

	 XAC97_mSetInFifoData(XPAR_AXI_AC97_0_BASEADDR,5);
	test = XAC97_ReadReg(XPAR_AXI_AC97_0_BASEADDR,XAC97_mGetStatus(XPAR_AXI_AC97_0_BASEADDR));
	xil_printf("test,%p\r\n",test);
	xil_printf("test,%d\r\n",test);
//10 0000 0001
	//XAC97_PlayAudio(Xuint32 BaseAddress, Xuint32 StartAddress, Xuint32 EndAddress);

test = XAC97_isInFIFOFull(XPAR_AXI_AC97_0_BASEADDR);
xil_printf("isInFIFOFull,%d\r\n",test);
test = XAC97_isInFIFOEmpty(XPAR_AXI_AC97_0_BASEADDR);
xil_printf("isInFIFOEmpty,%d\r\n",test);
test = XAC97_isOutFIFOEmpty(XPAR_AXI_AC97_0_BASEADDR);
xil_printf("isOutFIFOEmpty,%d\r\n",test);

	//Xuint32 XAC97_ReadReg(Xuint32 BaseAddress, Xuint32 RegAddress);
//	XAC97_HardReset
//	 XAC97_mSetControl(BaseAddress, AC97_ENABLE_RESET_AC97);
//	  XAC97_Delay(100000);
//	  XAC97_mSetControl(BaseAddress, AC97_DISABLE_RESET_AC97);
//	  XAC97_Delay(100000);
//	  XAC97_SoftReset(BaseAddress);

	return 0;
}





