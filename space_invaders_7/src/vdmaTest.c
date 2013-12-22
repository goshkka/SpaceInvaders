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
#include "sounds.h"
#include "pitDrive.h"


#define DEBUG
void print(char *str);

#define FRAME_BUFFER_0_ADDR 0xC1000000  // Starting location in DDR where we will store the images that we display.
#define MAX_SILLY_TIMER 10000000;
#define VOL_ATTN_MIN 0x0
#define VOL_ATTN_MAX 0x1f

XGpio gpLED;  // This is a handle for the LED GPIO block.
XGpio gpPB;   // This is a handle for the push-button GPIO block.
XGpio gpPS2;  // This is a handle for the PS2 GPIO block

Xuint32 vol_attn = 0x10;

void increaseVolume() {
  if((int)vol_attn > VOL_ATTN_MIN) {
    vol_attn = vol_attn - 0x1;
    XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MasterVol, vol_attn | (vol_attn << 8));
    XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_AuxOutVol, vol_attn | (vol_attn << 8));
  }
}
void decreaseVolume() {
  if((int)vol_attn < VOL_ATTN_MAX) {
    vol_attn = vol_attn + 0x1;
    XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MasterVol, vol_attn | (vol_attn << 8));
    XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_AuxOutVol, vol_attn | (vol_attn << 8));
  }
}

unsigned int * framePointer0;

int tankExplosionTimer = 0;

int alienTimer = 0;
int tankBulletTimer = 0;
int alienBulletTimer = 0;
int alienBulletGeneratorTimer = 0;
int alienBulletGeneratorResult = 300;
int alienSpaceShipTimer = 0;
int alienSpaceShipGeneratorTimer = 0;
int currentButtonState = 0;
int alienSpaceShipGeneratorResult = 4000;
int spaceShipTravelDistance = 20;
int randomNumber = 0;
int buttonTimer = 0;
int buttonThreshold = 20;

//Game In Action States
//0 game is moving
//1 tank is blowing up
//2 game over freeze all
void timer_interrupt_handler() {
	if (getGameInAction() == 0) {
				alienTimer++;
			tankBulletTimer++;
				alienBulletTimer++;
				alienBulletGeneratorTimer++;
				alienSpaceShipTimer++;
				alienSpaceShipGeneratorTimer++;
	}
	else if (getGameInAction() == 1){
			tankExplosionTimer++;
		} else if (getGameInAction() == 2) {
			return;
		}
		if (currentButtonState != 0) {
			buttonTimer++;
			if (buttonTimer > buttonThreshold) {
				if (currentButtonState & LEFT_BUTTON) {
					setTankPositionGlobal(getTankPositionGlobal() - 5);
					drawTank(framePointer0);
				}
				if (currentButtonState & RIGHT_BUTTON) {
					setTankPositionGlobal(getTankPositionGlobal() + 5);
					drawTank(framePointer0);
				}
				if (currentButtonState & MIDDLE_BUTTON) {
					if (!isHaveTankBullet()) {
						setHaveTankBullet(1);
						setTankBulletPositionX(getTankPositionGlobal() + 15);
						setTankBulletPositionY(TANK_Y_POSITION - 2*TANK_BULLET_HEIGHT);
					}
				}
				buttonTimer = buttonThreshold;

			}
		} else {
			buttonTimer = 0;
		}
		//gameOver
		if(getAlienPositionGlobal() >= GAME_OVER){
			setGameInAction(2);
		}
	//	//how fast the aliens move across the screen

		if (alienTimer >= 50) {
			incrementAlienSoundCadence();
			alienTimer = 0;
			setAlienPositionGlobal(9);
			//drawBunkerBlock(framePointer0);
			drawAlienBlock(framePointer0,getAlienMovementGlobal());
			drawBunkerBlock(framePointer0);
			//incrementAlienSoundCadence();
//			  int buttonValue = XGpio_ReadReg(XPAR_PS2_KEYBOARD_0_BASEADDR, 0x0);
//				xil_printf("\nValue=%d",buttonValue);

		}

	//
	//	//how fast tank bullet travels across screen
		if (tankBulletTimer == 1) {

			tankBulletTimer =0;
			if (isHaveTankBullet()){

				setTankBulletPositionY(getTankBulletPositionY()- TANK_BULLET_TRAVEL_DISTANCE);
				if (getTankBulletPositionY() <= 20) {
				//stop bullet at banner
							setHaveTankBullet(0);

					//eraseTankBullet(framePointer0);
				}
				drawTankBullet(framePointer0);
			}
			drawScore(framePointer0, getGlobalScore());
		}
	//	//how fast alien bullet travels across screen
		if (alienBulletTimer == 10) {
			alienBulletTimer = 0;
			int i;
			for (i = 0; i < NUMBER_ALIEN_BULLETS; i++) {
				if (alienBullets[i].isAvailable == ALIVE) {
					alienBullets[i].y += ALIEN_BULLET_TRAVEL_DISTANCE;
					if (alienBullets[i].y >= 480) {
						alienBullets[i].isAvailable = DEAD;
					}
					drawAlienBullets(framePointer0);
				}
			}




		}
	//	//how fast space ship travels across screen
	if (alienSpaceShipTimer == 30) {
		alienSpaceShipTimer = 0;
		if (isHaveSpaceShip() == 1) {
			//set alien spaceship position by moving left or right?
			//Add Logic for change in direction here
			setSpaceShipPositionGlobal(getSpaceShipPositionGlobal() + spaceShipTravelDistance);
			drawSpaceShip(framePointer0);
		}else{
			drawBlankSpaceShip(framePointer0);
		}
	}
	//	//when to generate an alien spaceship to fly across the screen
		if (alienSpaceShipGeneratorTimer >= alienSpaceShipGeneratorResult) {
			if (isHaveSpaceShip() == 0) {
				setHaveSpaceShip(1);

				// random true/false
	      // true from left
	      // false from right
	      randomNumber = generateRandomNumber(1);
	      if (randomNumber == 1) {
	        setSpaceShipPositionGlobal(1);
	        spaceShipTravelDistance = 10;
	      } else {
	        setSpaceShipPositionGlobal(640);
	        spaceShipTravelDistance = -10;
	      }
			}
			alienSpaceShipGeneratorTimer = 0;

			// Randomly generate a new result that will be long enough for the spaceship to go across the screen
			// create spaceship that moves left or right and has a certain value of points {50,100, 150, 200, 300}
		  // Maybe when the spaceship is hit we determine which point value to get in the drawTankBullet Method
	  }
		//when to generate alien bullet
		if (alienBulletGeneratorTimer ==alienBulletGeneratorResult) {
			alienBulletGeneratorTimer =0;
			int i;
			for (i = 0; i < NUMBER_ALIEN_BULLETS; i++) {
	      if (alienBullets[i].isAvailable == DEAD ) {
	        alienBullets[i].isAvailable = ALIVE;
	        // Position
	        //point_t bullet = generateRandomAlienBulletPosition();
	        int bulletColumn = aliveRandomCol();
	        //You do the random junk WORD_WIDTH*i is where it determines the alien
	        alienBullets[i].x = (HALF_WORD_WIDTH/2)  + (WORD_WIDTH*bulletColumn) + getAlienXYGlobal().x;
	        alienBullets[i].y = ALIEN_BLOCK_Y_END + ALIEN_BULLET_HEIGHT/5 -(ALIEN_HEIGHT*getLowestAlien(bulletColumn)) + getAlienXYGlobal().y;
	        //point_t tmp = generateRandomAlienBulletPosition();
	        //alienBullets[i].x = tmp.x;
	        //alienBullets[i].y = tmp.y;
	        alienBullets[i].bulletSymbol = generateRandomNumber(NUMBER_ALIEN_BULLETS);
	        break;
	      }

	    }
		}
	//

		//draw first explosion
		if (tankExplosionTimer % 10 == 1) {
			drawTankExplosion(framePointer0, getTankPositionGlobal(), TANK_Y_POSITION,1);
		}
		//draw alternate explosion
		if (tankExplosionTimer % 20 == 1) {
			drawTankExplosion(framePointer0, getTankPositionGlobal(), TANK_Y_POSITION,2);
		}
		if (tankExplosionTimer == 170) {
			setGameInAction(0);
			tankExplosionTimer = 0;
			drawBlankTank(framePointer0);

			setNumberLives(getNumberLives() - 1);
			if (getNumberLives() == 0) {
				xil_printf("GAME OVER");
				setGameInAction(2);
			} else {
				setTankPositionGlobal(50);
			}
			drawLives(framePointer0);
			//draw blank tank
			//draw new tank if there is a new game
		}
}


void pb_interrupt_handler() {
	//xil_printf("pb-interrupt\r\n");
	//Clear the GPIO interrupt.
	XGpio_InterruptGlobalDisable(&gpPB);                // Turn off all PB interrupts for now.
	currentButtonState = XGpio_DiscreteRead(&gpPB, 1);  // Get the current state of the buttons.
	if (getGameInAction() == 0) {
		switch (currentButtonState) {
				case LEFT_BUTTON:
					setTankPositionGlobal(getTankPositionGlobal() - 5);
					drawTank(framePointer0);
					break;
				case MIDDLE_BUTTON:
					if (!isHaveTankBullet()) {
						setHaveTankBullet(1);
						setHaveTankBulletSound(1);
						setTankBulletPositionX(getTankPositionGlobal() + 15);
						setTankBulletPositionY(TANK_Y_POSITION - 2*TANK_BULLET_HEIGHT);
						drawTankBullet(framePointer0);
					}
					break;
				case RIGHT_BUTTON:
					setTankPositionGlobal(getTankPositionGlobal() + 5);
					drawTank(framePointer0);
					break;
        case TOP_BUTTON:
          increaseVolume();
          break;
        case BOTTOM_BUTTON:
          decreaseVolume();
          break;
				}

	}
	// You need to do something here.
	XGpio_InterruptClear(&gpPB, 0xFFFFFFFF);            // Ack the PB interrupt.
	XGpio_InterruptGlobalEnable(&gpPB);                 // Re-enable PB interrupts.

}


void ps2_interrupt_handler() {
  int buttonValue = XGpio_ReadReg(XPAR_PS2_KEYBOARD_0_BASEADDR, 0x0);
  xil_printf("\r\nValue0=%d",buttonValue);

  if (getGameInAction() == 0) {
		switch (buttonValue) {
				// left button
        		case 28:
					setTankPositionGlobal(getTankPositionGlobal() - 5);
					drawTank(framePointer0);
					break;
				case 27:
					if (!isHaveTankBullet()) {
						setHaveTankBullet(1);
						setHaveTankBulletSound(1);
						setTankBulletPositionX(getTankPositionGlobal() + 15);
						setTankBulletPositionY(TANK_Y_POSITION - 2*TANK_BULLET_HEIGHT);
						drawTankBullet(framePointer0);
					}
					break;
				case 35:
					setTankPositionGlobal(getTankPositionGlobal() + 5);
					drawTank(framePointer0);
					break;
    }
  }
}

// Main interrupt handler, queries the interrupt controller to see what peripheral
// fired the interrupt and then dispatches the corresponding interrupt handler.
// This routine acks the interrupt at the controller level but the peripheral
// interrupt must be ack'd by the dispatched interrupt handler.
void interrupt_handler_dispatcher(void* ptr) {
	int intc_status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);

  // Check the AC97. Just one method - no need for a separate handler
  if (intc_status & XPAR_AXI_AC97_0_INTERRUPT_MASK) {
	  XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_AXI_AC97_0_INTERRUPT_MASK);
	  fillSound();

  }

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
  if (intc_status & XPAR_PS2_KEYBOARD_0_MYINTERRUPT_MASK) {
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_PS2_KEYBOARD_0_MYINTERRUPT_MASK);
		ps2_interrupt_handler();
  }
}




int main()
{
	// Necessary for all programs.
		init_platform();

		// set up regs for pit

		//Setup AC97
    XAC97_HardReset(XPAR_AXI_AC97_0_BASEADDR);  //Reset XAC97
    XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MasterVol, AC97_VOL_ATTN_23_5_DB);  // Set default volume

    XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_ExtendedAudioStat, 1);
    XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR,AC97_PCM_DAC_Rate,AC97_PCM_RATE_11025_HZ);
    //XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR,AC97_PCM_DAC_Rate0,AC97_PCM_RATE_11025_HZ);
    //XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR,AC97_PCM_DAC_Rate1,AC97_PCM_RATE_11025_HZ);

    XAC97_mSetControl(XPAR_AXI_AC97_0_BASEADDR, AC97_ENABLE_IN_FIFO_INTERRUPT);   //Enable AC97 Interrupts



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
		XIntc_EnableIntr(XPAR_INTC_0_BASEADDR, (XPAR_FIT_TIMER_0_INTERRUPT_MASK | XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK  | XPAR_PS2_KEYBOARD_0_MYINTERRUPT_MASK | XPAR_AXI_AC97_0_INTERRUPT_MASK ));
		XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);
		microblaze_enable_interrupts();
		int Status;
		// Keep track of success/failure of system function calls.
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
		myFrameConfig.WriteFrameCount = 2;
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
		myFrameBuffer.VertSizeInput = 480; // 480 vertical pixels.
		myFrameBuffer.HoriSizeInput = 640 * 4; // 640 horizontal (32-bit pixels).
		myFrameBuffer.Stride = 640 * 4; // Dont' worry about the rest of the values.
		myFrameBuffer.FrameDelay = 0;
		myFrameBuffer.EnableCircularBuf = 1;
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
		// Now, let's get ready to start displaying some stuff on the screen.
		// The variables framePointer and framePointer1 are just pointers to the base address
		// of frame 0 and frame 1.
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
		// Print a sanity message if you get this far.
		xil_printf("Woohoo! I made it through initialization.\n\r");
	//_setupHardware(gpPB);
	//initGameDefaults();
	int tmpTankPosition = getTankPositionGlobal();
	int tmpAlienPosition = getAlienPositionGlobal();
	int tmpSpaceShipPosition = getSpaceShipPositionGlobal();
	int tmpScore = getGlobalScore();
	int tmpBunkerState[NUMBER_BUNKER_ELEMENTS];
	int tmpNumberLives = getNumberLives();

	alienBullet tmpAlienBullets[NUMBER_ALIEN_BULLETS];

	int i = 0;
	for (i=0; i < NUMBER_ALIEN_BULLETS; i++) {
		tmpAlienBullets[i] = alienBullets[i];
	}
	for (i=0; i < NUMBER_BUNKER_ELEMENTS; i++){
		tmpBunkerState[i] = bunkerErosionState[i];
	}
	int tmpTankBulletPositionY = getTankBulletPositionY();

	setBunkerErosionState(4);

	framePointer0 = (unsigned int *) FRAME_BUFFER_0_ADDR;
	//unsigned int * framePointer1 = ((unsigned int *) FRAME_BUFFER_0_ADDR) + 640*480;


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
	drawBannerBlock(framePointer0);



	// Let's print out the alien as ASCII characters on the screen.
	// Each line of the alien is a 32-bit integer. We just need to strip the bits out and send
	// them to stdout.
	// MSB is the left-most pixel for the alien, so start from the MSB as we print from left to right.




	while (1) {
//		//This is a hack for stopping the alien bullets from sticking to the bottom of the screen
				for( row=448; row< 453; row++) {
					for(col=0; col<640; col++) {
						if (row > 450 && row < 453) {
							framePointer0[row*640 + col] = 0x0000FF00;
						} else {
							framePointer0[row*640 + col] = 0x00000000;
						}
					}
				}


		//xil_printf("HERE ENTER");
//		char c = getchar();
//		    	char D1;
//		    	char D2;
//		    	char D3;
//		    	char D4;
//		    	char D5;
//		    	char D6;
//		    	char D7;
//
//		    	if(c == ALPHA_q){
//		    		xil_printf("\n Disable/Enable Timer\r\n");
//		    		int reg = XGpio_ReadReg(XPAR_PIT_0_BASEADDR, 0x0);
//		    		if(reg << 31 == 0)
//		    			XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0x0, reg+1);
//		    		else
//		    			XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0x0, reg-1);
//		    	}
//		    	if(c == ALPHA_w){
//		    		xil_printf("\n Disable/Enable Interrupts\r\n");
//		    		int reg = XGpio_ReadReg(XPAR_PIT_0_BASEADDR, 0x0);
//		    		reg = reg ^2;
//		    		XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0x0, reg);
//		    		//    		else
//		    		//    			XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0x0, reg-1);
//
//
//		    	}
//
//		    	if(c == ALPHA_a){
//		    		xil_printf("\r\nReload Counter\r\n");
//		    		int reg = XGpio_ReadReg(XPAR_PIT_0_BASEADDR, 0x0);
//		    		reg = reg ^4;
//		    		XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0x0, reg);
//		    	}
//
//		    	if(c == ALPHA_c){
//		    		xil_printf("\r\nReset To initial\r\n");
//		    		XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0, 0x000000007); // control
//		    		XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0x4, 0x000000FF); //delay value
//		    	}
//
//
//		    	if(c == ALPHA_r){ //Keyboard r
//		    		xil_printf("\r\nDisable Timer\r\n");
//		    		XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0x0, 0x00000006);
//		    		//int eState;
//		    		xil_printf("\r\nPlease pick a value between 000000 and 1000000 to change timer\r\n");
//
//		    		D7 = getchar() - NUM_0;
//		    		xil_printf("%d",D7);
//		    		D6 = getchar() - NUM_0;
//		    		xil_printf("%d",D6);
//		    		D5 = getchar() - NUM_0;
//		    		xil_printf("%d",D5);
//		    		D4 = getchar() - NUM_0;
//		    		xil_printf("%d",D4);
//		    		D3 = getchar() - NUM_0;
//		    		xil_printf("%d",D3);
//		    		D2 = getchar() - NUM_0;
//		    		xil_printf("%d",D2);
//		    		D1 = getchar() - NUM_0;
//		    		xil_printf("%d",D1);
//		    		int out = D1+D2*10+D3*100+D4*1000+D5*10000+D6*100000+D7*1000000;
////		    		if (out == 1000000) {
////		    			out =1000;
////		    			xil_printf("You picked: One Million");
////		    		}else{
////						out = out/1000;
////						xil_printf("You picked: %d",out);
////		    		}
//		    		XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0x4, out);
//		    		xil_printf("\r\nWriting\r\n");
//
//		    		xil_printf("\r\nEnable All\r\n");
//		    		XGpio_WriteReg(XPAR_PIT_0_BASEADDR, 0x0, 0x00000007);
//		    	}


//		char c = getchar();
//		int eState;
//		switch(c) {
//		//Keyboard button 1
//
//		case 49:
//			if (isHaveSpaceShip() == 0) {
//				setHaveSpaceShip(1);
//				// random true/false
//				// true from left
//				// false from right
//				randomNumber = generateRandomNumber(2);
//				if (randomNumber == 1) {
//					xil_printf("1\r\n");
//					setSpaceShipPositionGlobal(1);
//					spaceShipTravelDistance = 10;
//				} else {
//					xil_printf("0\r\n");
//					setSpaceShipPositionGlobal(640);
//					spaceShipTravelDistance = -10;
//				}
//			}
//			break;
//			//Keyboard button 2
//		case 50:
//			xil_printf("\r\nPlease pick a value between 00 and 54 to kill alien\r\n");
//			char key0 = getchar() - 48;
//			char key1 = getchar() - 48;
//
//			int value = key0*10 + key1;
//			xil_printf("\rAlien is Dead: %d\r\n", value);
//			//	killAlien(value);
//			break;
//			//Keyboard button 3
//		case 51:
//			//Add Alien bullet
//			for (i = 0; i < NUMBER_ALIEN_BULLETS; i++) {
//				if (alienBullets[i].isAvailable == DEAD ) {
//					alienBullets[i].isAvailable = ALIVE;
//					// Position
//					//point_t bullet = generateRandomAlienBulletPosition();
//					int bulletColumn = aliveRandomCol();
//					//You do the random junk WORD_WIDTH*i is where it determines the alien
//					alienBullets[i].x = (HALF_WORD_WIDTH/2)  + (WORD_WIDTH*bulletColumn) + getAlienXYGlobal().x;
//					alienBullets[i].y = ALIEN_BLOCK_Y_END + ALIEN_BULLET_HEIGHT/5 -(ALIEN_HEIGHT*getLowestAlien(bulletColumn)) + getAlienXYGlobal().y;
//					//point_t tmp = generateRandomAlienBulletPosition();
//					//alienBullets[i].x = tmp.x;
//					//alienBullets[i].y = tmp.y;
//					alienBullets[i].bulletSymbol = generateRandomNumber(NUMBER_ALIEN_BULLETS);
//					break;
//				}
//			}
//
//			break;
//			//Keyboard button 4
//		case 52:
//			setTankPositionGlobal(getTankPositionGlobal() - 5);
//			break;
//			//Keyboard button 5
//		case 53:
//			setAlienPositionGlobal(5);
//			break;
//			//Keyboard button 6
//		case 54:
//			setTankPositionGlobal(getTankPositionGlobal() + 5);
//			break;
//			//Keyboard button 7
//		case 55:
//			// we can add a way of making all states -1 if we want to restore bunkers
//
//			xil_printf("\r\nPlease pick a value between 0 and 4 for erosion state of all bunkers\r\n");
//			char cs = getchar();
//			if (cs == 48)
//				eState = 0;
//			else if (cs == 49)
//				eState = 1;
//			else if (cs == 50)
//				eState = 2;
//			else if (cs == 51)
//				eState = 3;
//			else if (cs == 52)
//				eState = 4;
//			xil_printf("\rYou picked : %d\r\n", eState);
//			setBunkerErosionState(eState);
//			break;
//			//Keyboard button 8
//		case 56:
//			if (isHaveTankBullet() == DEAD) {
//				setHaveTankBullet(ALIVE);
//				setTankBulletPositionX(getTankPositionGlobal() + 15);
//				setTankBulletPositionY(TANK_Y_POSITION - TANK_BULLET_HEIGHT);
//			}
//			break;
//			//Keyboard button 9
//		case 57:
//			if (isHaveTankBullet()==ALIVE){
//				setTankBulletPositionY(getTankBulletPositionY()- TANK_BULLET_TRAVEL_DISTANCE);
//			}
//			for (i = 0; i < NUMBER_ALIEN_BULLETS; i++) {
//				if (alienBullets[i].isAvailable == ALIVE) {
//					alienBullets[i].y += ALIEN_BULLET_TRAVEL_DISTANCE;
//					if (alienBullets[i].y >= 480) {
//						alienBullets[i].isAvailable = DEAD;
//					}
//				}
//			}
//			if (isHaveSpaceShip() == 1) {
//				//set alien spaceship position by moving left or right?
//				//Add Logic for change in direction here
//				setSpaceShipPositionGlobal(getSpaceShipPositionGlobal() + spaceShipTravelDistance);
				//				//setSpaceShipPositionGlobal(getSpaceShipPositionGlobal() - 10);
				//			}
				//			break;
				//		}
				for (i = 0; i < NUMBER_BUNKER_ELEMENTS; i++) {
					if (tmpBunkerState[i] != bunkerErosionState[i]) {
						//xil_printf("HERE");
						tmpBunkerState[i] = bunkerErosionState[i];
						//  drawBunkerBlock(framePointer0);
					}
				}
				if (tmpAlienPosition != getAlienPositionGlobal()){

					tmpAlienPosition = getAlienPositionGlobal();
					drawAlienBlock(framePointer0,getAlienMovementGlobal());
				}

				if(tmpTankPosition != getTankPositionGlobal()){
					tmpTankPosition = getTankPositionGlobal();
					drawTank(framePointer0);
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
			if (isHaveSpaceShip() == 1) {
				drawSpaceShip(framePointer0);
			}
		}
		if (tmpScore != getGlobalScore()) {
			tmpScore = getGlobalScore();
			drawScore(framePointer0, getGlobalScore());
		}
		if (tmpNumberLives != getNumberLives()) {
			tmpNumberLives = getNumberLives();
			drawLives(framePointer0);
		}

	}
	cleanup_platform();

	return 0;
}
