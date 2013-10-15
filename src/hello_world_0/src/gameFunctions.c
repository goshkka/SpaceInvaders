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
#include "banner.h"
#include "spaceship.h"
#include <stdio.h>
	int COLUMNS=ALIEN_BLOCK_COLUMNS;
	int ROWS=ALIEN_BLOCK_ROWS;

//?????
void drawSprite(unsigned int * framePointer, int x, int y, int width, int height, unsigned int color) {
	int row, col;
	for (row = 0; row < (TANK_BULLET_HEIGHT ); row++) {
		for (col = 0; col < (TANK_BULLET_WIDTH); col++) {
				if ((tankBulletSymbol[row] & (1<<(TANK_BULLET_WIDTH-1-col)))) {
					if (getTankBulletPositionY() > 0) {
						framePointer[(row+y)*640 + col+x] = 0xFFFFFFFF;
					} else {
						framePointer[(row+y)*640 + col+x] = 0x00000000;
					}
				}
//					framePointer[(row+y+ TANK_BULLET_TRAVEL_DISTANCE)*640 + col+x)] = 0x00000000;
		}
	}
}

//void drawAlienBullets(unsigned int * framePointer) {
//	int row, col, bullet;
//
//	for (bullet = 0; bullet < NUMBER_ALIEN_BULLETS; bullet++) {
//		// only draw if bullet is there
//		if (alienBullets[bullet].isAvailable == ALIVE) {
//			//xil_printf("BUNGHOLIO");
//		}
//	}
//
//}
//returns a valid bullet Column 0-11
int aliveRandomCol(){
	int filler[COLUMNS];
	int *alien_roll = takeRoll(filler);

	int i = 0;
	int j = 0;
	//get census of alive aliens
	for(i=0;i<COLUMNS;i++){
		if(alien_roll[i]==ALIVE){

			j++;
		}
	}
	//generates a random number out of the set j is how many are alive
	int rand = generateRandomNumber(j);
	int bullet=0;
	//finds the alive column in the alien columns
	for(j=0,i=0;i<COLUMNS;i++){

		if(alien_roll[i]==ALIVE){

			if(j==rand){
				bullet = i;
			}j++;
		}

	}

return bullet;
}

//	alienColumnState();
	//generateRandomNumber(10)+ 1


//Returns the lowest alien in a column
int getLowestAlien(int column){
	int c=0;
	int j;
	int row;
	for(j=NUMBER_ALIEN_ROWS-1;j>-1;j--){
		if(getAlienLifeState(j*NUMBER_ALIEN_COLUMNS+column)==DEAD){
			c++;
		}else{row = c;}
	}
	//xil_printf("getLowest:%d\r\n",row);
return row;
}

//determines which alien columns are present
int* takeRoll(int* array){
	int c,k,j;
	//This for loop initializes alien_roll
	for(k=0;k<NUMBER_ALIEN_COLUMNS;k++){
			c=0;
			for(j=0;j<NUMBER_ALIEN_ROWS;j++){
		     if(getAlienLifeState(j*NUMBER_ALIEN_COLUMNS+k)==DEAD){
		    	c++;
		     }

			}
			if(c==NUMBER_ALIEN_ROWS){
				//ALIEN ROW IS DEAD
				array[k]=DEAD;
			}else{
				//ALIEN ROW IS Alive
				array[k]=ALIVE;
			}

			 //dead column
		}
	return array;
}
int isEven(int n){
	   if ( n%2 == 0 )
	      return 1;
	   else
	      return 0;
}

// top left alien is 00, bottom right alien is 54
void killAlien(int n)
{
	if(n>-1 && n <55)
	{
		setAlienLifeState(n);
	}

	//find out which columns are dead
	int filler[COLUMNS];
	int *alien_roll = takeRoll(filler);
	//REMOVES DEAD ALIEN COLUMNS FROM BLOCK
	int i = 0;
	while(alien_roll[i]==DEAD){
			i++;
	}
	//set left offset(Neg)
	setAlienOffset(-i);
	i=0;
	while(alien_roll[COLUMNS-i-1]==DEAD){
		i++;
	}
	//set right offset(Pos)
	setAlienOffset(i);
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
//cleans aliens mess after move
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

// Draw the alien explosion at (x,y) 
void drawAlienExplosion(unsigned int * framePointer, int x, int y) {
//	int row, col;
//	for (row = 0; row < (ALIEN_HEIGHT); row++) {
//		for (col = 0; col < WORD_WIDTH; col++) {
//			if (alienExplosionSymbol([row] & (1<<(WORD_WIDTH-1-col)))) {
//				framePointer[(row+y)*640 + col+x] = 0xFFFFFFFF;;
//			} else {
//				framePointer[(row+y)*640 + col+x] = 0x00000000;
//			}
//		}
//	}
}


// Draw the tank explosion at (x,y) and frame
void drawTankExplosion(unsigned int * framePointer, int x, int y, int z) {
//	int row, col;
//	for (row = 0; row < (TANK_HEIGHT); row++) {
//		for (col = 0; col < WORD_WIDTH; col++) {
//			if (tankKilledSymbols[z][row] &   (1<<(WORD_WIDTH-1-col) ) {
//				framePointer[(row+y)*640 + col+x] = 0xFFFFFFFF;;
//			} else {
//				framePointer[(row+y)*640 + col+x] = 0x00000000;
//			}
//		}
//	}
}


// Loop through each alien and redraw
// Added a blank row between each alien row
void drawAlienBlock(unsigned int * framePointer, int positionChange)
{

	//removes the previous parts of the frame
	removeRedraw(framePointer, positionChange);

	//DRAWS ALIEN BLOCK
	int i;
	for (i = 0; i < COLUMNS; i++) {



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

//Redraws the tank when it moves
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

void drawBlankTankBullet(unsigned int * framePointer, int x, int y) {
	int row, col;
	for (row = 0; row < (TANK_BULLET_HEIGHT ); row++) {
		for (col = 0; col < (TANK_BULLET_WIDTH); col++) {
			framePointer[(row+y)*640 + col+x] = 0x00000000;
		}
	}
}
void drawBlankAlienBullet(unsigned int * framePointer, int x, int y) {
	int row, col;
	for (row = 0; row < (ALIEN_BULLET_HEIGHT ); row++) {
		for (col = 0; col < (ALIEN_BULLET_WIDTH); col++) {
			framePointer[(row+y)*640 + col+x] = 0x00000000;
		}
	}
}

void drawAlienBullets(unsigned int * framePointer) {
	int row, col, bullet, index;
  // this variable is a boolean to help break the second for loop when hit
	int hit = 0;
	for (bullet = 0; bullet < NUMBER_ALIEN_BULLETS; bullet++) {
		hit = 0;
		// only draw if bullet is there
		if (alienBullets[bullet].isAvailable == ALIVE) {
			//xil_printf("BUNGHOLIO");
			for (row = 0; row < (ALIEN_BULLET_HEIGHT ); row++) {
				for (col = 0; col < (ALIEN_BULLET_WIDTH); col++) {
					if ((alienBulletSymbol[alienBullets[bullet].bulletSymbol][row] & (1<<(ALIEN_BULLET_WIDTH-1-col)))) {
						// If bullet hits something green (bunker or tank)
						// draw blank bullet
						// Determine if it is bunker or tank
						// If bunker determine which one and change the state at that bunker
						// Else blow up tank, decrement lives, redraw tank
						// remove bullet and break loop
						if (framePointer[(row+alienBullets[bullet].y)*640 + col+alienBullets[bullet].x] == 0x0000FF00) {
							hit = 1;
							// HIT a bunker
							if (alienBullets[bullet].y < TANK_Y_POSITION-10) {
                //draw blank bullet

                //determine which bunker was hit and update the state array
                index = determineBunkerHit(alienBullets[bullet].x, alienBullets[bullet].y);
							  bunkerErosionState[index] = bunkerErosionState[index] + 1;
              // Else hit the tank
							} else {
								//blow up tank --> handled by fit. Just need to set the boolean to pause game action and blow up tank
								//redraw tank --> handled by fit so it can alternate between the bitmaps and give it a slight animation
                setGameInAction(0);
								//decrement lives
								setNumberLives(getNumberLives() - 1);
								if (getNumberLives() == 0) {
									xil_printf("GAME OVER");
								}
								drawLives(framePointer);
							}
							alienBullets[bullet].isAvailable = 0;
							break;
						}
						if (alienBullets[bullet].y > 0) {
							framePointer[(row+alienBullets[bullet].y)*640 + col+alienBullets[bullet].x] = 0xFFFFFFFF;
						} else {
							framePointer[(row+alienBullets[bullet].y)*640 + col+alienBullets[bullet].x] = 0x00000000;
						}
					}
					framePointer[(row+alienBullets[bullet].y- ALIEN_BULLET_HEIGHT)*640 + col+alienBullets[bullet].x] = 0x00000000;
				}
				if (hit == 1) {
					break;
				}
			}
		}
	}
}

void drawSpaceShip(unsigned int * framePointer) {
	int row, col;
	for (row = 0; row < (SPACESHIP_HEIGHT); row++) {
		for (col = 0 - SPACESHIP_TRAVEL_DISTANCE; col < (WORD_WIDTH+SPACESHIP_TRAVEL_DISTANCE); col++) {
			if (col < 0 || col >= WORD_WIDTH) {
				framePointer[(row+SPACESHIP_Y)*640 + col+getTankPositionGlobal()] = 0x00000000;
			} else {
				if ((spaceShipSymbol[row] & (1<<(WORD_WIDTH-1-col)))) {
					framePointer[(row+SPACESHIP_Y)*640 + col+getTankPositionGlobal()] = 0x00FF0000;
				} else {
					framePointer[(row+SPACESHIP_Y)*640 + col+getTankPositionGlobal()] = 0x00000000;
				}
			}
		}
	}
}


// Had to split score up into 2 32 bit words because lack of a 64 bit data type
void drawScoreBanner(unsigned int * framePointer) {
	int row, col;
	for (row = 0; row < (LETTER_HEIGHT); row++) {
		for (col = 0; col < WORD_WIDTH; col++) {
			if ((scoreSymbol[0][row] & (1<<(WORD_WIDTH-1-col)))) {
				framePointer[(row+BANNER_Y)*640 + col] = 0xFFFFFFFF;
			} else {
				framePointer[(row+BANNER_Y)*640 + col] = 0x00000000;
			}
		}
	}
	for (row = 0; row < (LETTER_HEIGHT); row++) {
		for (col = 0; col < WORD_WIDTH; col++) {
			if ((scoreSymbol[1][row] & (1<<(WORD_WIDTH-1-col)))) {
				framePointer[(row+BANNER_Y)*640 + col+WORD_WIDTH-2] = 0xFFFFFFFF;
			} else {
				framePointer[(row+BANNER_Y)*640 + col+WORD_WIDTH-2] = 0x00000000;
			}
		}
	}
}


//void drawScore(unsigned int * framePointer) {}


void drawLivesBanner(unsigned int * framePointer) {
	int st = 350;
	int row, col;
	for (row = 0; row < (LETTER_HEIGHT); row++) {
		for (col = 0; col < WORD_WIDTH; col++) {
			if ((livesSymbol[0][row] & (1<<(WORD_WIDTH-1-col)))) {
				framePointer[(row+BANNER_Y)*640 + st + col] = 0xFFFFFFFF;
			} else {
				framePointer[(row+BANNER_Y)*640 + st + col] = 0x00000000;
			}
		}
	}
	for (row = 0; row < (LETTER_HEIGHT); row++) {
		for (col = 0; col < WORD_WIDTH; col++) {
			if ((livesSymbol[1][row] & (1<<(WORD_WIDTH-1-col)))) {
				framePointer[(row+BANNER_Y)*640 +st+col+WORD_WIDTH-6] = 0xFFFFFFFF;
			} else {
				framePointer[(row+BANNER_Y)*640 +st+col+WORD_WIDTH-6] = 0x00000000;
			}
		}
	}
}


void drawLives(unsigned int * framePointer) {
	int row, col, i;
	int xPos = 400;
	// Need to clear the screen of left overs
	for (i = 0; i < getNumberLives()+1; i++) {
		for (row = 0; row < (TANK_HEIGHT); row++) {
			for (col = 0; col < (WORD_WIDTH); col++) {
				framePointer[(row)*640 + col+xPos+i*WORD_WIDTH+i*5] = 0x00000000;
			}
		}
	}
	for (i = 0; i < getNumberLives(); i++) {
		for (row = 0; row < (TANK_HEIGHT); row++) {
			for (col = 0; col < (WORD_WIDTH); col++) {
				if ((tankSymbol[row] & (1<<(WORD_WIDTH-1-col)))) {
					framePointer[(row)*640 + col+xPos+i*WORD_WIDTH+i*5] = 0x0000FF00;
				} else {
					framePointer[(row)*640 + col+xPos+i*WORD_WIDTH+i*5] = 0x00000000;
				}
			}
		}
	}
}


// Draws one number on the screen
void drawNumber(unsigned int * framePointer, int number, int xPos) {
	int row, col;
	for (row = 0; row < (LETTER_HEIGHT); row++) {
		for (col = 0; col < NUMBER_WIDTH; col++) {
			if ((numbers[number][row] & (1<<(NUMBER_WIDTH-1-col)))) {
				framePointer[(row+BANNER_Y)*640 + col+xPos] = 0x0000FF00;
			} else {
				framePointer[(row+BANNER_Y)*640 + col+xPos] = 0x00000000;
			}
		}
	}
}

void drawScore(unsigned int * framePointer, int value) {
  int score = value;
  int count = 0;
  do {
    //draw right most first, then shift to the left 10*count
    drawNumber(framePointer, score % 10, RIGHT_NUMBER - count*12);
    score /= 10;
    count++;
  } while(score);
}

void drawBannerBlock(unsigned int * framePointer) {
	drawScoreBanner(framePointer);
	drawScore(framePointer, getGlobalScore());
	drawLivesBanner(framePointer);
	drawLives(framePointer);
}


int determineBunkerHit(int x, int y) {
  int first = 48;
  int second = 208;
  int third = 368;
  int fourth = 528;
  
  int returnValue = -1;
  int i = 0;
  int bunkerWidth = HALF_WORD_WIDTH*4;

  for (i = 1; i < 5; i++ ) {
    if ( x >= first * i && < first + HALF_WORD_WIDTH * i) {
      returnValue = i - 1;
    }
  }
  // only need to calculate if value hasn't been found
  if ( returnValue == -1) {
    for (i = 1; i < 5; i++) {
      if ( x >= second * i && < second + HALF_WORD_WIDTH * i) {
        returnValue = i + 3;
      }
    }
  }
  if ( returnValue == -1) {
    for (i = 1; i < 5; i++) {
      if ( x >= third * i && < third + HALF_WORD_WIDTH * i) {
        returnValue = i + 7;
      }
    }
  } 
  if ( returnValue == -1) {
    for (i = 1; i < 5; i++) {
      if ( x >= fourth * i && < fourth + HALF_WORD_WIDTH * i) {
        returnValue = i + 11;
      }
    }
  } 




  //top row
  if (y >= 350 && y < 362) {
    //return value is the same - leave
  }
  // second row
  else if (y >= 362 && y < 374) {
    returnValue = returnValue + 15
  }
  // third row 
  else if (y >= 374 && y < 386) {
    //potential bug because of how i did bottom row - may need to redo
    returnValue = returnValue + 30;
  }
  return returnValue;
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

