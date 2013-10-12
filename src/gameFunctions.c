/*
 * gameFunctions.c
 *
 *  Created on: Sep 28, 2013
 *      Author: superman
 */

#include "gameFunctions.h"
#include "globals.h"
#include "aliens.h"
#include "tank.h"
#include "bunkers.h"
#include "bullets.h"
#include "spaceship.h"
#include <stdio.h>
	int COLUMNS=ALIEN_BLOCK_COLUMNS;
	int ROWS=ALIEN_BLOCK_ROWS;


int isEven(int n){
	   if ( n%2 == 0 )
	      return 1;
	   else
	      return 0;
}

// n has to be in the range from 0 to 54
void killAlien(int n)
{
	if(n>-1 && n <55)
	{
		setAlienLifeState(n);
	}
}

void drawAlien(int x, int y, int alienType, unsigned int * framePointer) {
	int row, col;

	int cadence = isEven(x+y);

	for (row = 0; row < (ALIEN_HEIGHT); row++) {
		for (col = 0; col < (WORD_WIDTH); col++) {

			switch (alienType + cadence){
			case 1:

				if ((topOutAlienSymbol[row] & (1<<(WORD_WIDTH-1-col)))) {
					framePointer[(row+y)*640 + col+x] = 0xFFFFFFFF;
				} else {
					framePointer[(row+y)*640 + col+x] = 0x00000000;
				}
			break;
			case 2:

				if ((topInAlienSymbol[row] & (1<<(WORD_WIDTH-1-col)))) {
					framePointer[(row+y)*640 + col+x] = 0xFFFFFFFF;
				} else {
					framePointer[(row+y)*640 + col+x] = 0x00000000;
				}
			break;
			case 3:

				if ((middleOutAlienSymbol[row] & (1<<(WORD_WIDTH-1-col)))) {
					framePointer[(row+y)*640 + col+x] = 0xFFFFFFFF;
				} else {
					framePointer[(row+y)*640 + col+x] = 0x00000000;
				}
			break;
			case 4:
				if ((middleInAlienSymbol[row] & (1<<(WORD_WIDTH-1-col)))) {
					framePointer[(row+y)*640 + col+x] = 0xFFFFFFFF;
				} else {
					framePointer[(row+y)*640 + col+x] = 0x00000000;
				}
			break;
			case 5:

				if ((bottomOutAlienSymbol[row] & (1<<(WORD_WIDTH-1-col)))) {
					framePointer[(row+y)*640 + col+x] = 0xFFFFFFFF;
				} else {
					framePointer[(row+y)*640 + col+x] = 0x00000000;
				}
			break;
			case 6:
				if ((bottomInAlienSymbol[row] & (1<<(WORD_WIDTH-1-col)))) {
					framePointer[(row+y)*640 + col+x] = 0xFFFFFFFF;
				} else {
					framePointer[(row+y)*640 + col+x] = 0x00000000;
				}
			break;
			case 7:
			case 8:
			if ((deadAlienSymbol[row] & (1<<(WORD_WIDTH-1-col)))) {
									framePointer[(row+y)*640 + col+x] = 0xFFFFFFFF;
								} else {
									framePointer[(row+y)*640 + col+x] = 0x00000000;
								}
			break;
			default:
				xil_printf("ERROR: Entered default case in function");
			break;
			}

		}
	}
}

// draw a blank line or 2 between the alien rows
void drawRowSeparator(int x, int y, unsigned int * framePointer) {
	int row, col;
	for (row = 0; row < (ROW_SEPERATOR_HEIGHT); row++) {
		for (col = 0; col < (WORD_WIDTH); col++) {
			framePointer[(row+y)*640 + col+x] = 0x00000000;
		}
	}
}
void removeRedraw(unsigned int * framePointer, int positionChange){
	int row, col;
	//removes left side redraw needs to be put in a method
		for (row = 0; row < ALIEN_BLOCK_HEIGHT + 5*ROW_SEPERATOR_HEIGHT; row++) {
				for (col = -positionChange; col < 0; col++) {
					framePointer[(row+alienBlockY)*640 + col+alienBlockX] = 0x00000000;
					framePointer[(row+alienBlockY)*640 + col+alienBlockX+ALIEN_BLOCK_WIDTH + positionChange] = 0x00000000;

				}
			}
		//Removes top side redraw needs to be put in a method

		for (row = -(positionChange); row < 0; row++) {

					for (col = -(WORD_WIDTH); col < ALIEN_BLOCK_WIDTH; col++) {
						framePointer[(row+alienBlockY)*640 + col+alienBlockX] = 0x00000000;
					}
				}



}

int* takeRoll(int* arr){
	int c,k,j;
	//This for loop initializes alien_roll
	for(k=0;k<COLUMNS;k++){
			c=0;
			for(j=0;j<ROWS;j++){
		     if(getAlienLifeState(j*COLUMNS+k)==DEAD){
		    	c++;
		     }

			}
			if(c==ROWS){
				//ALIEN ROW IS DEAD
				arr[k]=DEAD;
			}else{
				//ALIEN ROW IS Alive
				arr[k]=ALIVE;
			}

			 //dead column
		}
	return arr;
}
// Loop through each alien and redraw
// Added a blank row between each alien row
void drawAlienBlock(unsigned int * framePointer, int positionChange)
{


	//removes the previous parts of the frame
	removeRedraw(framePointer, positionChange);

	//find out which columns are dead
	int filler[COLUMNS];
	int *alien_roll = takeRoll(filler);


//		if(getAlienLifeState(c) == DEAD for all columns
//		 DEAD_ALIEN_OFFSET += WORD_WIDTH;
		 //add DEAD_ALIEN_OFFSET to draw section.....
//	}



	//REMOVES DEAD ALIEN COLUMNS FROM BLOCK
	int i = 0;
	int start = 0;
	int end = COLUMNS;

	while(i< COLUMNS){
		if(alien_roll[i]==DEAD)
			start = i+1;
		else
			break;
		i++;
	}

	i=COLUMNS-1;
	while(i >-1){
		if(alien_roll[i]==DEAD)
			end = i;
		else
			break;
		i--;
	}

	//DRAWS ALIEN BLOCK
	for (i = start; i < end; i++) {



		//DRAWS AN ENTIRE COLUMN OF ALIENS

		//ADD ADDITIONAL ROW SEPERATOR BLOCKS TO ERASE BLOCK WHEN MOVING LEFT TO RIGHT
		drawRowSeparator(alienBlockX-WORD_WIDTH*i, alienBlockY+ALIEN_HEIGHT, framePointer);
		if(getAlienLifeState(i)==ALIVE){
			drawAlien(alienBlockX+WORD_WIDTH*i, alienBlockY, 1, framePointer);
		}else{drawAlien(alienBlockX+WORD_WIDTH*i, alienBlockY, 7, framePointer);}
		drawRowSeparator(alienBlockX+WORD_WIDTH*i, alienBlockY + ALIEN_HEIGHT*1, framePointer);
		if(getAlienLifeState(COLUMNS+i)==ALIVE){
			drawAlien(alienBlockX+WORD_WIDTH*i, alienBlockY + ALIEN_HEIGHT*1 + ROW_SEPERATOR_HEIGHT * 1, 3, framePointer);
		}else{drawAlien(alienBlockX+WORD_WIDTH*i, alienBlockY + ALIEN_HEIGHT*1 + ROW_SEPERATOR_HEIGHT * 1, 7, framePointer);}
		drawRowSeparator(alienBlockX+WORD_WIDTH*i, alienBlockY + ALIEN_HEIGHT *2 + ROW_SEPERATOR_HEIGHT * 1, framePointer);
		if(getAlienLifeState(COLUMNS*2+i)==ALIVE){
			drawAlien(alienBlockX+WORD_WIDTH*i, alienBlockY + ALIEN_HEIGHT*2 + ROW_SEPERATOR_HEIGHT * 2, 3, framePointer);
		}else{drawAlien(alienBlockX+WORD_WIDTH*i, alienBlockY + ALIEN_HEIGHT*2 + ROW_SEPERATOR_HEIGHT * 2, 7, framePointer);}
		drawRowSeparator(alienBlockX+WORD_WIDTH*i, alienBlockY + ALIEN_HEIGHT*3 + ROW_SEPERATOR_HEIGHT*2, framePointer);
		if(getAlienLifeState(COLUMNS*3+i)==ALIVE){
			drawAlien(alienBlockX+WORD_WIDTH*i, alienBlockY + ALIEN_HEIGHT*3 + ROW_SEPERATOR_HEIGHT * 3, 5, framePointer);
		}else{drawAlien(alienBlockX+WORD_WIDTH*i, alienBlockY + ALIEN_HEIGHT*3 + ROW_SEPERATOR_HEIGHT * 3, 7, framePointer);}
		drawRowSeparator(alienBlockX+WORD_WIDTH*i, alienBlockY + ALIEN_HEIGHT*4 + ROW_SEPERATOR_HEIGHT*3, framePointer);
		if(getAlienLifeState(COLUMNS*4+i)==ALIVE){
			drawAlien(alienBlockX+WORD_WIDTH*i, alienBlockY + ALIEN_HEIGHT*4 + ROW_SEPERATOR_HEIGHT * 4, 5, framePointer);
		}else{drawAlien(alienBlockX+WORD_WIDTH*i, alienBlockY + ALIEN_HEIGHT*4 + ROW_SEPERATOR_HEIGHT * 4, 7, framePointer);}

	}
}

//Draw block of bunkers

void drawTank(unsigned int * framePointer) {
	int row, col;
	for (row = 0; row < (TANK_HEIGHT); row++) {
		for (col = 0 - tankMovementDistance; col < (WORD_WIDTH+tankMovementDistance); col++) {
			if (col < 0 || col >= WORD_WIDTH) {
				framePointer[(row+TANK_Y_POSITION)*640 + col+getTankPositionGlobal()] = 0x00000000;
			} else {
				if ((tankSymbol[row] & (1<<(WORD_WIDTH-1-col)))) {
					framePointer[(row+TANK_Y_POSITION)*640 + col+getTankPositionGlobal()] = 0x0000FF00;
				} else {
					framePointer[(row+TANK_Y_POSITION)*640 + col+getTankPositionGlobal()] = 0x00000000;
				}
			}
		}
	}
}


// Draw top of each bunker by taking sections of the master array of bunker state and dividing it like so
// 0 1 2 3
// Y position is constant defined here
// 4 parts equal 4 parts of bunker
// @param x position
// @param ints
// @param framepointer
void drawTopLevelBunker(int x,int leftState, int middleLeftState, int middleRightState, int rightState, unsigned int * framePointer) {
	int y = 350;
	int row, col;
	for (row = 0; row < (BUNKER_HEIGHT); row++) {
		for (col = 0; col < (HALF_WORD_WIDTH*4); col++) {
			// top left
			if (col < HALF_WORD_WIDTH) {
				if ((topLeftBunkerSymbol[leftState][row] & (1<<(HALF_WORD_WIDTH-1-col)))) {
					framePointer[(row+y)*640 + col+x] = 0x0000FF00;
				} else {
					framePointer[(row+y)*640 + col+x] = 0x00000000;
				}
			// top middle left
			} else if (col >= HALF_WORD_WIDTH && col < HALF_WORD_WIDTH*2) {
				if ((solidBunkerSymbol[middleLeftState][row] & (1<<(HALF_WORD_WIDTH*2-1-col)))) {
					framePointer[(row+y)*640 + col+x] = 0x0000FF00;
				} else {
					framePointer[(row+y)*640 + col+x] = 0x00000000;
				}
			// top middle right
			} else if (col >= HALF_WORD_WIDTH*2 && col < HALF_WORD_WIDTH*3) {
				if ((solidBunkerSymbol[middleRightState][row] & (1<<(HALF_WORD_WIDTH-1-col)))) {
					framePointer[(row+y)*640 + col+x] = 0x0000FF00;
				} else {
					framePointer[(row+y)*640 + col+x] = 0x00000000;
				}
			// top right
			} else {
				if ((topRightBunkerSymbol[rightState][row] & (1<<(HALF_WORD_WIDTH*2-1-col)))) {
					framePointer[(row+y)*640 + col+x] = 0x0000FF00;
				} else {
					framePointer[(row+y)*640 + col+x] = 0x00000000;
				}
			}
		}
	}
}

// 0 1 2 3
void drawMiddleLevelBunker(int x, int leftState, int middleLeftState, int middleRightState, int rightState, unsigned int * framePointer) {
	int y = 362;
	int row, col;
	for (row = 0; row < (BUNKER_HEIGHT); row++) {
		for (col = 0; col < (HALF_WORD_WIDTH*4); col++) {
			// middle left
			if (col < HALF_WORD_WIDTH) {
				if ((solidBunkerSymbol[leftState][row] & (1<<(HALF_WORD_WIDTH-1-col)))) {
					framePointer[(row+y)*640 + col+x] = 0x0000FF00;
				} else {
					framePointer[(row+y)*640 + col+x] = 0x00000000;
				}
			//  middle center left
			} else if (col >= HALF_WORD_WIDTH && col < HALF_WORD_WIDTH*2) {
				if ((middleLeftBunkerSymbol[middleLeftState][row] & (1<<(HALF_WORD_WIDTH*2-1-col)))) {
					framePointer[(row+y)*640 + col+x] = 0x0000FF00;
				} else {
					framePointer[(row+y)*640 + col+x] = 0x00000000;
				}
			//  middle center right
			} else if (col >= HALF_WORD_WIDTH*2 && col < HALF_WORD_WIDTH*3) {
				if ((middleRightBunkerSymbol[middleRightState][row] & (1<<(HALF_WORD_WIDTH-1-col)))) {
					framePointer[(row+y
							)*640 + col+x] = 0x0000FF00;
				} else {
					framePointer[(row+y)*640 + col+x] = 0x00000000;
				}
			// middle right
			} else {
				if ((solidBunkerSymbol[rightState][row] & (1<<(HALF_WORD_WIDTH*2-1-col)))) {
					framePointer[(row+y)*640 + col+x] = 0x0000FF00;
				} else {
					framePointer[(row+y)*640 + col+x] = 0x00000000;
				}
			}
		}
	}
}

void drawBottomLevelBunker(int x, int leftState, int rightState, unsigned int * framePointer) {
	int y = 374;
	int row, col;
	for (row = 0; row < (BUNKER_HEIGHT); row++) {
		for (col = 0; col < (HALF_WORD_WIDTH*4); col++) {
			if (col < HALF_WORD_WIDTH) {
				if ((solidBunkerSymbol[leftState][row] & (1<<(HALF_WORD_WIDTH-1-col)))) {
					framePointer[(row+y)*640 + col+x] = 0x0000FF00;
				} else {
					framePointer[(row+y)*640 + col+x] = 0x00000000;
				}
			} else if (col > HALF_WORD_WIDTH*3){
				if ((solidBunkerSymbol[rightState][row] & (1<<(HALF_WORD_WIDTH*2-1-col)))) {
					framePointer[(row+y)*640 + col+x] = 0x0000FF00;
				} else {
					framePointer[(row+y)*640 + col+x] = 0x00000000;
				}
			}
		}
	}
}


//Start by just redrawing all the bunkers based on hit/not hit
//This potentially can be optimized later to just redraw the part that has changed
void drawBunkerBlock(unsigned int * framePointer) {
	//Draw bunker 1
	drawTopLevelBunker(48, bunkerErosionState[0], bunkerErosionState[1], bunkerErosionState[2], bunkerErosionState[3], framePointer);
	drawMiddleLevelBunker(48, bunkerErosionState[16], bunkerErosionState[17], bunkerErosionState[18], bunkerErosionState[19], framePointer);
	drawBottomLevelBunker(48, bunkerErosionState[31], bunkerErosionState[32], framePointer);

	//Draw bunker 2
	drawTopLevelBunker(208, bunkerErosionState[0], bunkerErosionState[1], bunkerErosionState[2], bunkerErosionState[3], framePointer);
	drawMiddleLevelBunker(208, bunkerErosionState[19], bunkerErosionState[20], bunkerErosionState[21], bunkerErosionState[22], framePointer);
	drawBottomLevelBunker(208, bunkerErosionState[33], bunkerErosionState[34], framePointer);

	//Draw bunker 3
	drawTopLevelBunker(368, bunkerErosionState[0], bunkerErosionState[1], bunkerErosionState[2], bunkerErosionState[3], framePointer);
	drawMiddleLevelBunker(368, bunkerErosionState[23], bunkerErosionState[24], bunkerErosionState[25], bunkerErosionState[26], framePointer);
	drawBottomLevelBunker(368, bunkerErosionState[35], bunkerErosionState[36], framePointer);

	//Draw bunker 4
	drawTopLevelBunker(528, bunkerErosionState[0], bunkerErosionState[1], bunkerErosionState[2], bunkerErosionState[3], framePointer);
	drawMiddleLevelBunker(528, bunkerErosionState[27], bunkerErosionState[28], bunkerErosionState[29], bunkerErosionState[30], framePointer);
	drawBottomLevelBunker(528, bunkerErosionState[37], bunkerErosionState[38], framePointer);
}

//If it's a fresh bullet just draw it, but if it is moving then need to clean up redering
void drawTankBullet(unsigned int * framePointer) {
	int row, col;

	for (row = 0; row < (TANK_BULLET_HEIGHT ); row++) {
			//xil_printf("X: %d, Y: %d \r\n", getTankBulletPositionX(), getTankBulletPositionY());
		for (col = 0; col < (TANK_BULLET_WIDTH); col++) {
//			if (getTankBulletPositionY() > (TANK_BULLET_HEIGHT)) {
//				 ((tankBulletSymbol[row] & (1<<(TANK_BULLET_WIDTH-1-col)))) {
//				TANK_BULLET_TRAVEL_DISTANCE

				if ((tankBulletSymbol[row] & (1<<(TANK_BULLET_WIDTH-1-col)))) {
					if (getTankBulletPositionY() > 0) {
						framePointer[(row+getTankBulletPositionY())*640 + col+getTankBulletPositionX()] = 0xFFFFFFFF;
					} else {
						framePointer[(row+getTankBulletPositionY())*640 + col+getTankBulletPositionX()] = 0x00000000;
					}
				}
					framePointer[(row+getTankBulletPositionY()+ TANK_BULLET_TRAVEL_DISTANCE)*640 + col+getTankBulletPositionX()] = 0x00000000;
		}
	}
}

void drawAlienBullets(unsigned int * framePointer) {
	int row, col, bullet;

	for (bullet = 0; bullet < NUMBER_ALIEN_BULLETS; bullet++) {
		// only draw if bullet is there
		if (alienBullets[bullet].isAvailable == ALIVE) {
			//xil_printf("BUNGHOLIO");
			for (row = 0; row < (ALIEN_BULLET_HEIGHT ); row++) {
				for (col = 0; col < (ALIEN_BULLET_WIDTH); col++) {
					if ((alienBulletSymbol[alienBullets[bullet].bulletSymbol][row] & (1<<(ALIEN_BULLET_WIDTH-1-col)))) {

						if (alienBullets[bullet].y > 0) {
							framePointer[(row+alienBullets[bullet].y)*640 + col+alienBullets[bullet].x] = 0xFFFFFFFF;
						} else {
							framePointer[(row+alienBullets[bullet].y)*640 + col+alienBullets[bullet].x] = 0x00000000;
						}
					}
						framePointer[(row+alienBullets[bullet].y- ALIEN_BULLET_HEIGHT)*640 + col+alienBullets[bullet].x] = 0x00000000;
				}
			}
		}
	}
}

void drawSpaceShip(unsigned int * framePointer) {
	int row, col, bullet;
	for (row = 0; row < (SPACESHIP_HEIGHT ); row++) {
	  for (col = 0; col < (SPACESHIP_WIDTH); col++) {
		  if ((spaceShipSymbol[row] & (1<<(SPACESHIP_WIDTH-1-col)))) {
						if (alienBullets[bullet].y > 0) {
						  framePointer[(row)*50 + col+getSpaceShipPositionGlobal()] = 0xFFFFFFFF;
						} else {
						  framePointer[(row)*50 + col+getSpaceShipPositionGlobal()] = 0x00000000;
						}
					}
					framePointer[(row)*50 + col+getSpaceShipPositionGlobal()] = 0x00000000;
				}
			}
}



void drawScoreBanner(unsigned int * framePointer) {

}


void drawScore(unsigned int * framePointer) {

}


void drawLivesBanner(unsigned int * framePointer) {

}


void drawLives(unsigned int * framePointer) {

}


void drawBannerBlock(unsigned int * framePointer) {


}





//void eraseTankBullet(unsigned int * framePointer) {
//	xil_printf("FUGLY MOMMA");
//	int row, col;
//	//TANK_BULLET_HEIGHT+TANK_BULLET_TRAVEL_DISTANCE
//	for (row = 0; row < 10; row++) {
//			for (col = 0; col < (TANK_BULLET_WIDTH); col++) {
//				framePointer[(row)*640 + col+getTankBulletPositionX()] = 0x00000000;
//
//				//if ((tankBulletSymbol[row] & (1<<(TANK_BULLET_WIDTH-1-col)))) {
//					//framePointer[(row+getTankBulletPositionY())*640 + col+getTankBulletPositionX()] = 0x000000FF;
//				//}
//			}
//	}
//}

