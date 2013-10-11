/*
 * Copyright (c) 2009 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 */

#include "xgpio.h"
#include "mb_interface.h"
#include "xintc_l.h"

#include "xparameters.h"
#include "xbasic_types.h"
#include "xstatus.h"

#include "xuartlite.h"
#include "stdio.h"
#include "math.h"

#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xaxivdma.h"
#include "xio.h"
#include "time.h"
#include "unistd.h"
#include "aliens.h"
#include "globals.h"
#include "tank.h"
#include "gameFunctions.h"
#include "bunkers.h"
#include "bullets.h"
#include "banner.h"
#include "spaceShip.h"
//888888


#define DEBUG
void print(char *str);

#define FRAME_BUFFER_0_ADDR 0xC1000000  // Starting location in DDR where we will store the images that we display.
#define MAX_SILLY_TIMER 10000000;

XGpio gpLED;  // This is a handle for the LED GPIO block.
XGpio gpPB;   // This is a handle for the push-button GPIO block.
int alienTimer = 0;
int tankBulletTimer = 0;
int alienBulletTimer = 0;
int alienSpaceShipTimer = 0;
int alienSpaceShipGeneratorTimer = 0;
int currentButtonState = 0;
int alienSpaceShipGeneratorResult = 500;


void timer_interrupt_handler() {
  alienTimer++;
  tankBulletTimer++;
  alienBulletTimer++;
  alienSpaceShipTimer++;
  alienSpaceShipGeneratorTimer++;


  if (alienTimer == 40) {
    alienTimer = 0;
    setAlienPositionGlobal(9);
  }

  if (tankBulletTimer == 5) {
    if (!isHaveTankBullet()) {
    	setHaveTankBullet(1);
    	setTankBulletPositionX(getTankPositionGlobal() + 15);
    	setTankBulletPositionY(TANK_Y_POSITION - TANK_BULLET_HEIGHT);
    }
  }

  if (alienBulletTimer == 10) {
    alienBulletTimer = 0;
  }
  if (alienSpaceShipTimer == 80) {
    alienSpaceShipTimer = 0;
    //set alien spaceship position by moving left or right?
    setSpaceShipPositionGlobal(getSpaceShipPositionGlobal() + 10);
  }
  if (alienSpaceShipGeneratorTimer == alienSpaceShipGeneratorResult) {
    // Randomly generate a new result that will be long enough for the spaceship to go accross the screen
    // create spaceship that moves left or right and has a certain value of points {50,100, 150, 200, 300}
  }
}


void pb_interrupt_handler() {

  //Clear the GPIO interrupt.
  XGpio_InterruptGlobalDisable(&gpPB);                // Turn off all PB interrupts for now.
  currentButtonState = XGpio_DiscreteRead(&gpPB, 1);  // Get the current state of the buttons.
  // You need to do something here.
  XGpio_InterruptClear(&gpPB, 0xFFFFFFFF);            // Ack the PB interrupt.
  XGpio_InterruptGlobalEnable(&gpPB);                 // Re-enable PB interrupts.
}


// Main interrupt handler, queries the interrupt controller to see what peripheral
// fired the interrupt and then dispatches the corresponding interrupt handler.
// This routine acks the interrupt at the controller level but the peripheral
// interrupt must be ack'd by the dispatched interrupt handler.
void interrupt_handler_dispatcher(void* ptr) {
  int intc_status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);
  // Check the FIT interrupt first.
  if (intc_status & XPAR_FIT_TIMER_0_INTERRUPT_MASK){
    XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_FIT_TIMER_0_INTERRUPT_MASK);
    timer_interrupt_handler();
  }
  // Check the push buttons.
  if (intc_status & XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK){
    XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK);
    pb_interrupt_handler();
  }
}

int main()
{
	initGameDefaults();

	int tmpTankPosition = getTankPositionGlobal();
	int tmpAlienPosition = getAlienPositionGlobal();
	int tmpSpaceShipPosition = getSpaceShipPositionGlobal();

  int tmpBunkerState[NUMBER_BUNKER_ELEMENTS];

	alienBullet tmpAlienBullets[NUMBER_ALIEN_BULLETS];

	int i = 0;
	for (i=0; i < NUMBER_ALIEN_BULLETS; i++) {
		tmpAlienBullets[i] = alienBullets[i];
	}
	for (i=0; i < NUMBER_BUNKER_ELEMENTS; i++){
		tmpBunkerState[i] = bunkerErosionState[i];
	}
	int tmpTankBulletPositionY = getTankBulletPositionY();

	init_platform();                   // Necessary for all programs.

  //Initialize interrupts
  int success;
  success = XGpio_Initialize(&gpPB, XPAR_PUSH_BUTTONS_5BITS_DEVICE_ID);
  // Set the push button peripheral to be inputs.
  XGpio_SetDataDirection(&gpPB, 1, 0x0000001F);
  // Enable the global GPIO interrupt for push buttons.
  XGpio_InterruptGlobalEnable(&gpPB);
  // Enable all interrupts in the push button peripheral.
  XGpio_InterruptEnable(&gpPB, 0xFFFFFFFF);

  microblaze_register_handler(interrupt_handler_dispatcher, NULL);
  XIntc_EnableIntr(XPAR_INTC_0_BASEADDR, (XPAR_FIT_TIMER_0_INTERRUPT_MASK | XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK));
  XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);
  microblaze_enable_interrupts();





  int Status;                        // Keep track of success/failure of system function calls.
	XAxiVdma videoDMAController;
	// There are 3 steps to initializing the vdma driver and IP.
	// Step 1: lookup the memory structure that is used to access the vdma driver.
    XAxiVdma_Config * VideoDMAConfig = XAxiVdma_LookupConfig(XPAR_AXI_VDMA_0_DEVICE_ID);
    // Step 2: Initialize the memory structure and the hardware.
    if(XST_FAILURE == XAxiVdma_CfgInitialize(&videoDMAController, VideoDMAConfig,	XPAR_AXI_VDMA_0_BASEADDR)) {
    	xil_printf("VideoDMA Did not initialize.\r\n");
    }
    // Step 3: (optional) set the frame store number.
    if(XST_FAILURE ==  XAxiVdma_SetFrmStore(&videoDMAController, 2, XAXIVDMA_READ)) {
    	xil_printf("Set Frame Store Failed.");
    }
    // Initialization is complete at this point.

    // Setup the frame counter. We want two read frames. We don't need any write frames but the
    // function generates an error if you set the write frame count to 0. We set it to 2
    // but ignore it because we don't need a write channel at all.
    XAxiVdma_FrameCounter myFrameConfig;
    myFrameConfig.ReadFrameCount = 2;
    myFrameConfig.ReadDelayTimerCount = 10;
    myFrameConfig.WriteFrameCount =2;
    myFrameConfig.WriteDelayTimerCount = 10;
    Status = XAxiVdma_SetFrameCounter(&videoDMAController, &myFrameConfig);
    if (Status != XST_SUCCESS) {
	   xil_printf("Set frame counter failed %d\r\n", Status);
	   if(Status == XST_VDMA_MISMATCH_ERROR)
		   xil_printf("DMA Mismatch Error\r\n");
    }
    // Now we tell the driver about the geometry of our frame buffer and a few other things.
    // Our image is 480 x 640.
    XAxiVdma_DmaSetup myFrameBuffer;
    myFrameBuffer.VertSizeInput = 480;    // 480 vertical pixels.
    myFrameBuffer.HoriSizeInput = 640*4;  // 640 horizontal (32-bit pixels).
    myFrameBuffer.Stride = 640*4;         // Dont' worry about the rest of the values.
    myFrameBuffer.FrameDelay = 0;
    myFrameBuffer.EnableCircularBuf=1;
    myFrameBuffer.EnableSync = 0;
    myFrameBuffer.PointNum = 0;
    myFrameBuffer.EnableFrameCounter = 0;
    myFrameBuffer.FixedFrameStoreAddr = 0;
    if(XST_FAILURE == XAxiVdma_DmaConfig(&videoDMAController, XAXIVDMA_READ, &myFrameBuffer)) {
    	xil_printf("DMA Config Failed\r\n");
     }
    // We need to give the frame buffer pointers to the memory that it will use. This memory
    // is where you will write your video data. The vdma IP/driver then streams it to the HDMI
    // IP.
     myFrameBuffer.FrameStoreStartAddr[0] = FRAME_BUFFER_0_ADDR;
     myFrameBuffer.FrameStoreStartAddr[1] = FRAME_BUFFER_0_ADDR + 4*640*480;

     if(XST_FAILURE == XAxiVdma_DmaSetBufferAddr(&videoDMAController, XAXIVDMA_READ,
    		               myFrameBuffer.FrameStoreStartAddr)) {
    	 xil_printf("DMA Set Address Failed Failed\r\n");
     }
     // Print a sanity message if you get this far.
     xil_printf("Woohoo! I made it through initialization.\n\r");
     // Now, let's get ready to start displaying some stuff on the screen.
     // The variables framePointer and framePointer1 are just pointers to the base address
     // of frame 0 and frame 1.
     unsigned int * framePointer0 = (unsigned int *) FRAME_BUFFER_0_ADDR;
   //  unsigned int * framePointer1 = ((unsigned int *) FRAME_BUFFER_0_ADDR) + 640*480;


     // We will start by blacking out the screen and then drawing the block sections as appropriate
     // for the first printing
     int row=0;
     int col=0;
     for( row=0; row<480; row++) {
    	 for(col=0; col<640; col++) {
    		 if (row > 450 && row < 453) {
    			 framePointer0[row*640 + col] = 0x0000FF00;
    		 } else {
				 framePointer0[row*640 + col] = 0x00000000;
    		 }
    	 }
     }
     drawAlienBlock(framePointer0,0);
     drawTank(framePointer0);
     drawBunkerBlock(framePointer0);
     //drawBannerBlock(framePointer0);


  // Let's print out the alien as ASCII characters on the screen.
  // Each line of the alien is a 32-bit integer. We just need to strip the bits out and send
  // them to stdout.
  // MSB is the left-most pixel for the alien, so start from the MSB as we print from left to right.


     // This tells the HDMI controller the resolution of your display (there must be a better way to do this).
     XIo_Out32(XPAR_AXI_HDMI_0_BASEADDR, 640*480);

     // Start the DMA for the read channel only.
     if(XST_FAILURE == XAxiVdma_DmaStart(&videoDMAController, XAXIVDMA_READ)){
    	 xil_printf("DMA START FAILED\r\n");
     }
     int frameIndex = 0;
     // We have two frames, let's park on frame 0. Use frameIndex to index them.
     // Note that you have to start the DMA process before parking on a frame.
     if (XST_FAILURE == XAxiVdma_StartParking(&videoDMAController, frameIndex,  XAXIVDMA_READ)) {
    	 xil_printf("vdma parking failed\n\r");
     }
     // Oscillate between frame 0 and frame 1.
     //int sillyTimer = MAX_SILLY_TIMER;  // Just a cheap delay between frames.
     int j;
     for(j=0;j<5;j++){
     killAlien(j*11);
     killAlien(j*11+10);
     }
     while (1) {
////    	 char c = getchar();
////    	 int eState;
////    	 switch(c) {
////    	 	 //Keyboard button 6
////    	 	 case 54:
////    	 		 setTankPositionGlobal(getTankPositionGlobal() + 5);
////    	 		 break;
////    	 	 //Keyboard button 4
////    	 	 case 52:
////    	 		 setTankPositionGlobal(getTankPositionGlobal() - 5);
////    	 		 break;
////    	 	//Keyboard button 8
////    	 	case 56:
////
////
////    	 	    break;
////    	 	//Keyboard button 2
////    	 	case 50:
////    	 		xil_printf("\r\nPlease pick a value between 00 and 54 to kill alien\r\n");
////    	 		char key0 = getchar() - 48 ;
////    	 		char key1 = getchar() - 48;
////
////    	 		int value = key0*10 + key1;
////    	 		xil_printf("\rAlien is Dead: %d\r\n", value);
////    	 		killAlien(value);
////    	 	break;
////    	 	 //Keyboard button 5
////    	 	case 53:
////    	 		break;
////    	 	//Keyboard button 3
////    	 	case 51:
////    	 		//Add Alien bullet
////    	 		for (i = 0; i < NUMBER_ALIEN_BULLETS; i++) {
////    	 			if (alienBullets[i].isAvailable == DEAD ) {
////    	 				alienBullets[i].isAvailable = ALIVE;
////    	 				// Position
////
////    	 				int Offset = 8;
////    	 				//You do the random junk WORD_WIDTH*i is where it determines the alien
////    	 				alienBullets[i].x = (HALF_WORD_WIDTH- Offset)  + WORD_WIDTH*(generateRandomNumber(10)+ 1) + getAlienXYGlobal().x;
////    	 				alienBullets[i].y = ALIEN_BLOCK_Y_END + getAlienXYGlobal().y;
////    	 				//point_t tmp = generateRandomAlienBulletPosition();
////    	 				//alienBullets[i].x = tmp.x;
////    	 				//alienBullets[i].y = tmp.y;
////    	 				alienBullets[i].bulletSymbol = generateRandomNumber(NUMBER_ALIEN_BULLETS);
////    	 				break;
////    	 			}
////    	 		}
////
////    	 		break;
////    	 	//Keyboard button 9
////    	 	case 57:
////    	 		if (isHaveTankBullet()){
////    	 			setTankBulletPositionY(getTankBulletPositionY()- TANK_BULLET_TRAVEL_DISTANCE);
////    	 			if (getTankBulletPositionY() <= -1) {
////    	 				setHaveTankBullet(0);
////    	 				//eraseTankBullet(framePointer0);
////    	 			}
////    	 		}
////    	 		for (i = 0; i < NUMBER_ALIEN_BULLETS; i++) {
////    	 			if (alienBullets[i].isAvailable == ALIVE) {
////    	 				alienBullets[i].y += ALIEN_BULLET_TRAVEL_DISTANCE;
////    	 				if (alienBullets[i].y >= 480) {
////    	 					alienBullets[i].isAvailable = DEAD;
////    	 				}
////    	 			}
////    	 		}
////    	 		break;
////    	 	//Keyboard button 7
////    	 	case 55:
////    	 		// we can add a way of making all states -1 if we want to restore bunkers
////
////    	 		xil_printf("\r\nPlease pick a value between 0 and 4 for erosion state of all bunkers\r\n");
////    	 		char cs = getchar();
////    	 		if (cs == 48)
////    	 			eState = 0;
////    	 		else if (cs == 49)
////    	 			eState = 1;
////    	 		else if (cs == 50)
////    	 			eState = 2;
////    	 		else if (cs == 51)
////    	 			eState = 3;
////    	 		else if (cs == 52)
////    	 			eState = 4;
////    	 		xil_printf("\rYou picked : %d\r\n", eState);
////    	 		setBunkerErosionState(eState);
////    	 		break;
////
////
//
//
////    	 }
    	 if (tmpAlienPosition != getAlienPositionGlobal()){
    	     		 tmpAlienPosition = getAlienPositionGlobal();
    	     		 drawAlienBlock(framePointer0,getAlienMovementGlobal());
    	     	 }
    	 if (tmpTankPosition != getTankPositionGlobal()) {
    		 tmpTankPosition = getTankPositionGlobal();
    		 drawTank(framePointer0);
    	 }

    	 for (i = 0; i < NUMBER_BUNKER_ELEMENTS; i++) {
    		 if (tmpBunkerState[i] != bunkerErosionState[i]) {
    			 tmpBunkerState[i] = bunkerErosionState[i];
    			 drawBunkerBlock(framePointer0);
    		 }
    	 }
    	 for (i = 0; i < NUMBER_ALIEN_BULLETS; i++) {
    		 if (tmpAlienBullets[i].y != alienBullets[i].y || tmpAlienBullets[i].isAvailable != alienBullets[i].isAvailable){
    			 tmpAlienBullets[i] = alienBullets[i];
    			 drawAlienBullets(framePointer0);
    		 }
    	 }
    	 if (tmpTankBulletPositionY != getTankBulletPositionY()){
    		 tmpTankBulletPositionY = getTankBulletPositionY();
    		 drawTankBullet(framePointer0);
    	 }
       if (tmpSpaceShipPosition != getSpaceShipPositionGlobal()) {
         tmpSpaceShipPosition = getSpaceShipPositionGlobal();
         drawSpaceShip(framePointer0);
       }
    	 //while (sillyTimer) sillyTimer--;   // Decrement the timer.
    	 //sillyTimer = MAX_SILLY_TIMER;       // Reset the timer.
         //frameIndex = (frameIndex + 1) % 2;  // Alternate between frame 0 and frame 1.
         if (XST_FAILURE == XAxiVdma_StartParking(&videoDMAController, frameIndex,  XAXIVDMA_READ)) {
        	 xil_printf("vdma parking failed\n\r");
         }
     }
     cleanup_platform();

    return 0;
}
