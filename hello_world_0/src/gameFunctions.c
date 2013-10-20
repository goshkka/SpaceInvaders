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
static const int _RED = 0x00FF0000;
static const int _GREEN = 0x0000FF00;
static const int _WHITE = 0xFFFFFFFF;
static const int _BLACK = 0x00000000;
static const int _640 = 640;
int COLUMNS = ALIEN_BLOCK_COLUMNS;
int ROWS = ALIEN_BLOCK_ROWS;

//?????
void drawSprite(unsigned int * framePointer, int x, int y, int width,
		int height, unsigned int color) {
	int row, col;
	for (row = 0; row < (TANK_BULLET_HEIGHT); row++) {
		for (col = 0; col < (TANK_BULLET_WIDTH); col++) {
			if ((tankBulletSymbol[row] & (1 << (TANK_BULLET_WIDTH - 1 - col)))) {
				if (getTankBulletPositionY() > 0) {
					framePointer[(row + y) * _640 + col + x] = _WHITE;
				} else {
					framePointer[(row + y) * _640 + col + x] = _BLACK;
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
int aliveRandomCol() {
	int filler[COLUMNS];
	int *alien_roll = takeRoll(filler);

	int i = 0;
	int j = 0;
	//get census of alive aliens
	for (i = 0; i < COLUMNS; i++) {
		if (alien_roll[i] == ALIVE) {

			j++;
		}
	}
	//generates a random number out of the set j is how many are alive
	int rand = generateRandomNumber(j);
	int bullet = 0;
	//finds the alive column in the alien columns
	for (j = 0, i = 0; i < COLUMNS; i++) {

		if (alien_roll[i] == ALIVE) {

			if (j == rand) {
				bullet = i;
			}
			j++;
		}

	}

	return bullet;
}

//	alienColumnState();
//generateRandomNumber(10)+ 1


//Returns the lowest alien in a column
int getLowestAlien(int column) {
	int c = 0;
	int j;
	int row = 0;
	for (j = NUMBER_ALIEN_ROWS - 1; j > -1; j--) {
		if (getAlienLifeState(j * NUMBER_ALIEN_COLUMNS + column) == DEAD) {
			c++;
		} else {
			row = c;
		}
	}
	//xil_printf("getLowest:%d\r\n",row);
	return row;
}

//determines which alien columns are present
int* takeRoll(int* array) {
	int c, k, j;
	//This for loop initializes alien_roll
	for (k = 0; k < NUMBER_ALIEN_COLUMNS; k++) {
		c = 0;
		for (j = 0; j < NUMBER_ALIEN_ROWS; j++) {
			if (getAlienLifeState(j * NUMBER_ALIEN_COLUMNS + k) == DEAD) {
				c++;
			}

		}
		if (c == NUMBER_ALIEN_ROWS) {
			//ALIEN ROW IS DEAD
			array[k] = DEAD;
		} else {
			//ALIEN ROW IS Alive
			array[k] = ALIVE;
		}

		//dead column
	}
	return array;
}

int isEven(int n) {
	if (n % 2 == 0)
		return 1;
	else
		return 0;
}

void score(int n, unsigned int * framePointer) {
	//xil_printf("alienTimer: %d",getAlienTimer());

	int score = 0;
	if (n >= 00 && n < 11) {
		score = 40;
	}
	if (n >= 11 && n < 33) {
		score = 20;
	}
	if (n >= 33 && n < 55) {
		score = 10;
	}
	if (n >= 55) {
		score = n;
	}
	setGlobalScore(score + getGlobalScore());
}
// Draw the alien explosion at (x,y)
void drawAlienExplosion(unsigned int * framePointer, int x, int y) {

	int row, col;
	for (row = 0; row < (ALIEN_HEIGHT); row++) {
		for (col = 0; col < WORD_WIDTH; col++) {
			if (alienExplosionSymbol[row] & (1 << (WORD_WIDTH - 1 - col))) {
				framePointer[(row + y) * _640 + col + x] = _WHITE;

			} else {
				framePointer[(row + y) * _640 + col + x] = _BLACK;
			}
		}
	}
}

// Draw the tank explosion at (x,y) and frame
void drawTankExplosion(unsigned int * framePointer, int x, int y, int z) {
	int row, col;
	for (row = 0; row < (TANK_HEIGHT); row++) {
		for (col = 0; col < WORD_WIDTH; col++) {
			if (tankKilledSymbols[z][row] & (1 << (WORD_WIDTH - 1 - col))) {
				//((tankSymbol[row] & (1<<(WORD_WIDTH-1-col)))
				framePointer[(row + y) * _640 + col + x] = _GREEN;
				;
			} else {
				framePointer[(row + y) * _640 + col + x] = _BLACK;
			}
		}
	}
}
void drawShipExplosion(unsigned int * framePointer, int x, int y, int z) {
	//xil_printf("\r\nXPOS%d",x);
	//update global score
	setGlobalScore(getGlobalScore() + z);
	int score = z;
	int count = 0;
	do {
		//draw right most first, then shift to the left 10*count
		drawSpaceShipNumber(framePointer, x - count * 12 + 24, score % 10);
		score /= 10;
		count++;
	} while (score);
}

// top left alien is 00, bottom right alien is 54
void killAlien(int n, unsigned int * framePointer, int x, int y) {
	if (n > -1 && n < 55) {
		//Only give score on the first Killed Alien
		if (getAlienLifeState(n) == ALIVE) {
			score(n, framePointer);
			if (n >= 00 && n < 11) {

				drawAlienExplosion(framePointer,
						alienBlockX + WORD_WIDTH * (n % 11),
						alienBlockY + (ALIEN_HEIGHT+ROW_SEPERATOR_HEIGHT) * (0));
			}
			if (n >= 11 && n < 22) {
				drawAlienExplosion(framePointer,
						alienBlockX + WORD_WIDTH * (n % 11),
						alienBlockY + (ALIEN_HEIGHT+ROW_SEPERATOR_HEIGHT) * (1));
			}
			if (n >= 22 && n < 33) {
				drawAlienExplosion(framePointer,
						alienBlockX + WORD_WIDTH * (n % 11),
						alienBlockY + (ALIEN_HEIGHT+ROW_SEPERATOR_HEIGHT) * (2));
			}
			if (n >= 33 && n < 44) {
				drawAlienExplosion(framePointer,
						alienBlockX + WORD_WIDTH * (n % 11),
						alienBlockY + (ALIEN_HEIGHT+ROW_SEPERATOR_HEIGHT) * (3));
			}

			if (n >= 44 && n < 55) {
				drawAlienExplosion(framePointer,alienBlockX + WORD_WIDTH * (n%11),
						alienBlockY + (ALIEN_HEIGHT+ROW_SEPERATOR_HEIGHT) * (4));
			}

		}
		setAlienLifeState(n);
		//quick and dirty check
	}
	//find out which columns are dead
	int filler[COLUMNS];
	int *alien_roll = takeRoll(filler);
	//REMOVES DEAD ALIEN COLUMNS FROM BLOCK
	int i = 0;
	while (alien_roll[i] == DEAD) {
		i++;
	}
	//set left offset(Neg)
	setAlienOffset(-i);
	i = 0;
	while (alien_roll[COLUMNS - i - 1] == DEAD) {
		i++;
	}
	//set right offset(Pos)
	setAlienOffset(i);
}

void drawAlien(int x, int y, int alienType, unsigned int * framePointer) {
	int row, col;
	int cadence = isEven(x + y);

	for (row = 0; row < (ALIEN_HEIGHT); row++) {
		for (col = 0; col < (WORD_WIDTH); col++) {
			//			if (framePointer[(row+y-ALIEN_BULLET_HEIGHT)*640 + col+x] == 0x0000FF00) {
			//							framePointer[(row+y-ALIEN_BULLET_HEIGHT)*640 + col+x] = 0x0000FF00;
			//						} else {
			//							framePointer[(row+y-ALIEN_BULLET_HEIGHT)*640 + col+x] = 0x00000000;
			//						}
			switch (alienType + cadence) {
			case 1:
				if ((topOutAlienSymbol[row] & (1 << (WORD_WIDTH - 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _WHITE;
				} else {
					if (framePointer[(row + y) * _640 + col + x] == _GREEN) {
						framePointer[(row + y) * _640 + col + x] = _GREEN;
					} else {
						framePointer[(row + y) * _640 + col + x] = _BLACK;
					}
				}
				break;
			case 2:

				if ((topInAlienSymbol[row] & (1 << (WORD_WIDTH - 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _WHITE;
				} else {
					if (framePointer[(row + y) * _640 + col + x] == _GREEN) {
						framePointer[(row + y) * _640 + col + x] = _GREEN;
					} else {
						framePointer[(row + y) * _640 + col + x] = _BLACK;
					}
				}
				break;
			case 3:

				if ((middleOutAlienSymbol[row] & (1 << (WORD_WIDTH - 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _WHITE;
				} else {
					if (framePointer[(row + y) * _640 + col + x] == _GREEN) {
						framePointer[(row + y) * _640 + col + x] = _GREEN;
					} else {

						framePointer[(row + y) * _640 + col + x] = _BLACK;
					}

				}
				break;
			case 4:
				if ((middleInAlienSymbol[row] & (1 << (WORD_WIDTH - 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _WHITE;
				} else {
					if (framePointer[(row + y) * _640 + col + x] == _GREEN) {
						framePointer[(row + y) * _640 + col + x] = _GREEN;
					} else {
						framePointer[(row + y) * _640 + col + x] = _BLACK;
					}
				}
				break;
			case 5:

				if ((bottomOutAlienSymbol[row] & (1 << (WORD_WIDTH - 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _WHITE;
				} else {
					if (framePointer[(row + y) * _640 + col + x] == _GREEN) {
						framePointer[(row + y) * _640 + col + x] = _GREEN;
					} else {
						framePointer[(row + y) * _640 + col + x] = _BLACK;
					}
				}
				break;
			case 6:
				if ((bottomInAlienSymbol[row] & (1 << (WORD_WIDTH - 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _WHITE;
				} else {
					if (framePointer[(row + y) * _640 + col + x] == _GREEN) {
						framePointer[(row + y) * _640 + col + x] = _GREEN;
					} else {

						framePointer[(row + y) * _640 + col + x] = _BLACK;
					}

				}
				break;
			case 7:
			case 8:
				if ((deadAlienSymbol[row] & (1 << (WORD_WIDTH - 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _WHITE;
				} else {
					if (framePointer[(row + y) * _640 + col + x] == _GREEN) {
						framePointer[(row + y) * _640 + col + x] = _GREEN;
					} else {

						framePointer[(row + y) * _640 + col + x] = _BLACK;
					}

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
			if (framePointer[(row + y) * _640 + col + x] == _GREEN) {
				framePointer[(row + y) * _640 + col + x] = _GREEN;
			} else {

				framePointer[(row + y) * _640 + col + x] = _BLACK;
			}
		}
	}
}
void drawAlienBlock(unsigned int * framePointer, int positionChange) {

	//removes the previous parts of the frame
	removeRedraw(framePointer, positionChange);

	//DRAWS ALIEN BLOCK
	int i;
	for (i = 0; i < COLUMNS; i++) {

		//DRAWS AN ENTIRE COLUMN OF ALIENS

		//ADD ADDITIONAL ROW SEPERATOR BLOCKS TO ERASE BLOCK WHEN MOVING LEFT TO RIGHT
		drawRowSeparator(alienBlockX - WORD_WIDTH * i,
				alienBlockY + ALIEN_HEIGHT, framePointer);
		if (getAlienLifeState(i) == ALIVE) {
			drawAlien(alienBlockX + WORD_WIDTH * i, alienBlockY, 1,
					framePointer);
		} else {
			drawAlien(alienBlockX + WORD_WIDTH * i, alienBlockY, 7,
					framePointer);
		}
		drawRowSeparator(alienBlockX + WORD_WIDTH * i,
				alienBlockY + ALIEN_HEIGHT * 1, framePointer);
		if (getAlienLifeState(COLUMNS + i) == ALIVE) {
			drawAlien(alienBlockX + WORD_WIDTH * i,
					alienBlockY + ALIEN_HEIGHT * 1 + ROW_SEPERATOR_HEIGHT * 1,
					3, framePointer);
		} else {
			drawAlien(alienBlockX + WORD_WIDTH * i,
					alienBlockY + ALIEN_HEIGHT * 1 + ROW_SEPERATOR_HEIGHT * 1,
					7, framePointer);
		}
		drawRowSeparator(alienBlockX + WORD_WIDTH * i,
				alienBlockY + ALIEN_HEIGHT * 2 + ROW_SEPERATOR_HEIGHT * 1,
				framePointer);
		if (getAlienLifeState(COLUMNS * 2 + i) == ALIVE) {
			drawAlien(alienBlockX + WORD_WIDTH * i,
					alienBlockY + ALIEN_HEIGHT * 2 + ROW_SEPERATOR_HEIGHT * 2,
					3, framePointer);
		} else {
			drawAlien(alienBlockX + WORD_WIDTH * i,
					alienBlockY + ALIEN_HEIGHT * 2 + ROW_SEPERATOR_HEIGHT * 2,
					7, framePointer);
		}
		drawRowSeparator(alienBlockX + WORD_WIDTH * i,
				alienBlockY + ALIEN_HEIGHT * 3 + ROW_SEPERATOR_HEIGHT * 2,
				framePointer);
		if (getAlienLifeState(COLUMNS * 3 + i) == ALIVE) {
			drawAlien(alienBlockX + WORD_WIDTH * i,
					alienBlockY + ALIEN_HEIGHT * 3 + ROW_SEPERATOR_HEIGHT * 3,
					5, framePointer);
		} else {
			drawAlien(alienBlockX + WORD_WIDTH * i,
					alienBlockY + ALIEN_HEIGHT * 3 + ROW_SEPERATOR_HEIGHT * 3,
					7, framePointer);
		}
		drawRowSeparator(alienBlockX + WORD_WIDTH * i,
				alienBlockY + ALIEN_HEIGHT * 4 + ROW_SEPERATOR_HEIGHT * 3,
				framePointer);
		if (getAlienLifeState(COLUMNS * 4 + i) == ALIVE) {

			drawAlien(alienBlockX + WORD_WIDTH * i,
					alienBlockY + ALIEN_HEIGHT * 4 + ROW_SEPERATOR_HEIGHT * 4,
					5, framePointer);
		} else {
			drawAlien(alienBlockX + WORD_WIDTH * i,
					alienBlockY + ALIEN_HEIGHT * 4 + ROW_SEPERATOR_HEIGHT * 4,
					7, framePointer);
		}

	}
}
//cleans aliens mess after move
void removeRedraw(unsigned int * framePointer, int positionChange) {
	int row, col;
	//removes left side redraw needs to be put in a method
	for (row = 0; row < ALIEN_BLOCK_HEIGHT + 5 * ROW_SEPERATOR_HEIGHT; row++) {
		for (col = -positionChange; col < 0; col++) {
			if (framePointer[(row + alienBlockY) * _640 + col + alienBlockX]
			                 == _GREEN) {
				framePointer[(row + alienBlockY) * _640 + col + alienBlockX]
				             = _GREEN;
			} else {
				framePointer[(row + alienBlockY) * _640 + col + alienBlockX]
				             = _BLACK;
			}
			if (framePointer[(row + alienBlockY) * _640 + col + alienBlockX
			                 + ALIEN_BLOCK_WIDTH + positionChange] == _GREEN) {
				framePointer[(row + alienBlockY) * _640 + col + alienBlockX
				             + ALIEN_BLOCK_WIDTH + positionChange] = _GREEN;
			} else {
				framePointer[(row + alienBlockY) * _640 + col + alienBlockX
				             + ALIEN_BLOCK_WIDTH + positionChange] = _BLACK;
			}

		}
	}
	//Removes top side redraw needs to be put in a method

	for (row = -(positionChange); row < 0; row++) {

		for (col = -(WORD_WIDTH); col < ALIEN_BLOCK_WIDTH; col++) {
			if (framePointer[(row + alienBlockY) * _640 + col + alienBlockX
			                 + ALIEN_BLOCK_WIDTH + positionChange] == _GREEN) {
				framePointer[(row + alienBlockY) * _640 + col + alienBlockX
				             + ALIEN_BLOCK_WIDTH + positionChange] = _GREEN;
			} else {
				framePointer[(row + alienBlockY) * _640 + col + alienBlockX]
				             = _BLACK;
			}
		}
	}
}

void drawSpaceShipNumber(unsigned int * framePointer, int x, int z) {
	int row, col;
	for (row = 0; row < (LETTER_HEIGHT); row++) {
		for (col = 0; col < NUMBER_WIDTH; col++) {
			if ((numbers[z][row] & (1 << (NUMBER_WIDTH - 1 - col)))) {
				framePointer[(row + SPACESHIP_Y) * _640 + col + x] = _GREEN;
			} else {
				framePointer[(row + SPACESHIP_Y) * _640 + col + x] = _BLACK;
			}
		}
	}
}
// Loop through each alien and redraw
// Added a blank row between each alien row


//Redraws the tank when it moves
void drawTank(unsigned int * framePointer) {
	int row, col;
	for (row = 0; row < (TANK_HEIGHT); row++) {
		for (col = 0 - tankMovementDistance; col < (WORD_WIDTH+ tankMovementDistance); col++) {
			if (col < 0 || col >= WORD_WIDTH) {
				framePointer[(row + TANK_Y_POSITION) * _640 + col
				             + getTankPositionGlobal()] = _BLACK;
			} else {
				if ((tankSymbol[row] & (1 << (WORD_WIDTH - 1 - col)))) {
					framePointer[(row + TANK_Y_POSITION) * _640 + col
					             + getTankPositionGlobal()] = _GREEN;
				}
				else {
					framePointer[(row + TANK_Y_POSITION) * _640 + col
					             + getTankPositionGlobal()] = _BLACK;
				}
			}
		}
	}
	framePointer[(row + TANK_Y_POSITION) * _640 + col
	             + getTankPositionGlobal() - WORD_WIDTH] = _BLACK;
	framePointer[(row + TANK_Y_POSITION) * _640 + col
	             + getTankPositionGlobal() + WORD_WIDTH] = _BLACK;
}

// Draw top of each bunker by taking sections of the master array of bunker state and dividing it like so
// 0 1 2 3
// Y position is constant defined here
// 4 parts equal 4 parts of bunker
// @param x position
// @param ints
// @param framepointer
void drawTopLevelBunker(int x, int leftState, int middleLeftState,
		int middleRightState, int rightState, unsigned int * framePointer) {
	int y = 350;
	int row, col;
	for (row = 0; row < (BUNKER_HEIGHT); row++) {
		for (col = 0; col < (HALF_WORD_WIDTH * 4); col++) {
			// top left
			if (col < HALF_WORD_WIDTH) {
				if ((topLeftBunkerSymbol[leftState][row] & (1
						<< (HALF_WORD_WIDTH - 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _GREEN;
				} else {
					framePointer[(row + y) * _640 + col + x] = _BLACK;
				}
				// top middle left
			} else if (col >= HALF_WORD_WIDTH && col < HALF_WORD_WIDTH * 2) {
				if ((solidBunkerSymbol[middleLeftState][row] & (1
						<< (HALF_WORD_WIDTH * 2 - 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _GREEN;
				} else {
					framePointer[(row + y) * _640 + col + x] = _BLACK;
				}
				// top middle right
			} else if (col >= HALF_WORD_WIDTH * 2 && col < HALF_WORD_WIDTH * 3) {
				if ((solidBunkerSymbol[middleRightState][row] & (1
						<< (HALF_WORD_WIDTH - 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _GREEN;
				} else {
					framePointer[(row + y) * _640 + col + x] = _BLACK;
				}
				// top right
			} else {
				if ((topRightBunkerSymbol[rightState][row] & (1
						<< (HALF_WORD_WIDTH * 2 - 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _GREEN;
				} else {
					framePointer[(row + y) * _640 + col + x] = _BLACK;
				}
			}
		}
	}
}

// 0 1 2 3
void drawMiddleLevelBunker(int x, int leftState, int middleLeftState,
		int middleRightState, int rightState, unsigned int * framePointer) {
	int y = 362;
	int row, col;
	for (row = 0; row < (BUNKER_HEIGHT); row++) {
		for (col = 0; col < (HALF_WORD_WIDTH * 4); col++) {
			// middle left
			if (col < HALF_WORD_WIDTH) {
				if ((solidBunkerSymbol[leftState][row] & (1 << (HALF_WORD_WIDTH
						- 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _GREEN;
				} else {
					framePointer[(row + y) * _640 + col + x] = _BLACK;
				}
				//  middle center left
			} else if (col >= HALF_WORD_WIDTH && col < HALF_WORD_WIDTH * 2) {
				if ((middleLeftBunkerSymbol[middleLeftState][row] & (1
						<< (HALF_WORD_WIDTH * 2 - 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _GREEN;
				} else {
					framePointer[(row + y) * _640 + col + x] = _BLACK;
				}
				//  middle center right
			} else if (col >= HALF_WORD_WIDTH * 2 && col < HALF_WORD_WIDTH * 3) {
				if ((middleRightBunkerSymbol[middleRightState][row] & (1
						<< (HALF_WORD_WIDTH - 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _GREEN;
				} else {
					framePointer[(row + y) * _640 + col + x] = _BLACK;
				}
				// middle right
			} else {
				if ((solidBunkerSymbol[rightState][row] & (1
						<< (HALF_WORD_WIDTH * 2 - 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _GREEN;
				} else {
					framePointer[(row + y) * _640 + col + x] = _BLACK;
				}
			}
		}
	}
}

void drawBottomLevelBunker(int x, int leftState, int rightState,
		unsigned int * framePointer) {
	int y = 374;
	int row, col;
	for (row = 0; row < (BUNKER_HEIGHT); row++) {
		for (col = 0; col < (HALF_WORD_WIDTH * 4); col++) {
			if (col < HALF_WORD_WIDTH) {
				if ((solidBunkerSymbol[leftState][row] & (1 << (HALF_WORD_WIDTH
						- 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _GREEN;
				} else {
					framePointer[(row + y) * _640 + col + x] = _BLACK;
				}
			} else if (col > HALF_WORD_WIDTH * 3) {
				if ((solidBunkerSymbol[rightState][row] & (1
						<< (HALF_WORD_WIDTH * 2 - 1 - col)))) {
					framePointer[(row + y) * _640 + col + x] = _GREEN;
				} else {
					framePointer[(row + y) * _640 + col + x] = _BLACK;
				}
			}
		}
	}
}

//Start by just redrawing all the bunkers based on hit/not hit
//This potentially can be optimized later to just redraw the part that has changed
void drawBunkerBlock(unsigned int * framePointer) {
	//Draw bunker 1
	drawTopLevelBunker(48, bunkerErosionState[0], bunkerErosionState[1],
			bunkerErosionState[2], bunkerErosionState[3], framePointer);
	drawMiddleLevelBunker(48, bunkerErosionState[16], bunkerErosionState[17],
			bunkerErosionState[18], bunkerErosionState[19], framePointer);
	drawBottomLevelBunker(48, bunkerErosionState[32], bunkerErosionState[33],
			framePointer);

	//Draw bunker 2
	drawTopLevelBunker(208, bunkerErosionState[4], bunkerErosionState[5],
			bunkerErosionState[6], bunkerErosionState[7], framePointer);
	drawMiddleLevelBunker(208, bunkerErosionState[20], bunkerErosionState[21],
			bunkerErosionState[22], bunkerErosionState[23], framePointer);
	drawBottomLevelBunker(208, bunkerErosionState[34], bunkerErosionState[35],
			framePointer);

	//Draw bunker 3
	drawTopLevelBunker(368, bunkerErosionState[8], bunkerErosionState[9],
			bunkerErosionState[10], bunkerErosionState[11], framePointer);
	drawMiddleLevelBunker(368, bunkerErosionState[24], bunkerErosionState[25],
			bunkerErosionState[26], bunkerErosionState[27], framePointer);
	drawBottomLevelBunker(368, bunkerErosionState[36], bunkerErosionState[37],
			framePointer);

	//Draw bunker 4
	drawTopLevelBunker(528, bunkerErosionState[12], bunkerErosionState[13],
			bunkerErosionState[14], bunkerErosionState[15], framePointer);
	drawMiddleLevelBunker(528, bunkerErosionState[28], bunkerErosionState[29],
			bunkerErosionState[30], bunkerErosionState[31], framePointer);
	drawBottomLevelBunker(528, bunkerErosionState[38], bunkerErosionState[39],
			framePointer);
}
void drawBlankTankBullet(unsigned int * framePointer, int x, int y) {
	//xil_printf("drawBlank(%d,%d)",x,y);
	int row, col;
	for (row = 0; row < 2 * (TANK_BULLET_HEIGHT + TANK_BULLET_TRAVEL_DISTANCE); row++) {
		for (col = 0; col < (TANK_BULLET_WIDTH); col++) {
			if (framePointer[(row + y - TANK_BULLET_HEIGHT) * _640 + col + x]
			                 == _WHITE) {
				framePointer[(row + y - TANK_BULLET_HEIGHT) * _640 + col + x]
				             = _WHITE;
			}
			if (framePointer[(row + y - TANK_BULLET_HEIGHT) * _640 + col + x]
			                 == _RED) {
				framePointer[(row + y - TANK_BULLET_HEIGHT) * _640 + col + x]
				             = _RED;
			}
			if (framePointer[(row + y - TANK_BULLET_HEIGHT) * _640 + col + x]
			                 == _GREEN) {
				framePointer[(row + y - TANK_BULLET_HEIGHT) * _640 + col + x]
				             = _GREEN;
			} else {
				framePointer[(row + y - TANK_BULLET_HEIGHT) * _640 + col + x]
				             = _BLACK;
			}

		}
	}
}

//If it's a fresh bullet just draw it, but if it is moving then need to clean up redering
void drawTankBullet(unsigned int * framePointer) {
	int row, col;
	int hit, index;
	hit = 0;

	//xil_printf("DrawTankBullet\r\n");
	for (row = 0; row < (TANK_BULLET_HEIGHT); row++) {
		//xil_printf("X: %d, Y: %d \r\n", getTankBulletPositionX(), getTankBulletPositionY());
		for (col = 0; col < (TANK_BULLET_WIDTH); col++) {
			//			if (getTankBulletPositionY() > (TANK_BULLET_HEIGHT)) {
			//				 ((tankBulletSymbol[row] & (1<<(TANK_BULLET_WIDTH-1-col)))) {
			//				TANK_BULLET_TRAVEL_DISTANCE
			if ((tankBulletSymbol[row] & (1 << (TANK_BULLET_WIDTH - 1 - col)))) {
				//If bullet in range to impact
				//if hits green
				if (framePointer[(row + getTankBulletPositionY()) * _640 + col
				                 + getTankBulletPositionX()] == _GREEN) {
					//determine which bunker was hit and update the state array

					index = determineBunkerHit(getTankBulletPositionX(),
							getTankBulletPositionY());
					int value = bunkerErosionState[index];
					//xil_printf("index=%d ,value=%d\r\n",index, value);
					if (value == 4) {
						value = 0;
					} else if (value == 3) {
						value = 3;
					} else {
						value = value + 1;
					}
					//xil_printf("\r\nIndex = %d, Value = %d",index, value);
					bunkerErosionState[index] = value;
					hit = 1;
					setHaveTankBullet(0);
					break;

				}
				//if it encounters white
				if (framePointer[(row + getTankBulletPositionY()) * _640 + col
				                 + getTankBulletPositionX() - 2] == _WHITE) {

					//get Location. Determine and kill the correct alien
					point_t location = getAlienXYGlobal();

					point_t deadAlien;
					deadAlien.y = getTankBulletPositionY() - location.y;
					deadAlien.x = getTankBulletPositionX() - location.x;
					int dA_row = deadAlien.y / (ALIEN_HEIGHT
							+ ROW_SEPERATOR_HEIGHT);
					int dA_col = deadAlien.x / (WORD_WIDTH);

					killAlien(dA_row * COLUMNS + dA_col, framePointer,
							deadAlien.x, deadAlien.y);

					//Destroy bullet/Reset Bullet


					//Reset Tank and Don't update bullet anymore
					setHaveTankBullet(0);
					hit = 1;

				}
				//if it encounters RED
				if (framePointer[(row + getTankBulletPositionY()) * _640 + col
				                 + getTankBulletPositionX()] == _RED) {
					setHaveSpaceShip(0);
					setSpaceShipExplosionTimer(0);
					//eraseShip
					drawBlankSpaceShip(framePointer);
					setSpaceShipScoreX(getSpaceShipPositionGlobal());

					drawShipExplosion(framePointer,
							getSpaceShipPositionGlobal(), SPACESHIP_Y,
							spaceShipPoints[generateRandomNumber(5)]);

				}

				//This draws the actual bullet and erases the contrails

				if (getTankBulletPositionY() > 24 ) {
					framePointer[(row + getTankBulletPositionY()) * _640 + col
					             + getTankBulletPositionX()] = _WHITE;

					if(	((row + getTankBulletPositionY() + TANK_BULLET_TRAVEL_DISTANCE + 5)) < TANK_Y_POSITION ){
						framePointer[(row + getTankBulletPositionY()
								+ TANK_BULLET_TRAVEL_DISTANCE + 5) * _640 + col
								+ getTankBulletPositionX()] = _BLACK;
					}
				}
				if (getTankBulletPositionY() <= 24) {
					setHaveTankBullet(0);

					drawBlankTankBullet(framePointer, getTankBulletPositionX(), 24);
				}

			}
			//Erases Screen

		}
		if (hit == 1) {
			drawBlankTankBullet(framePointer, getTankBulletPositionX(),
					getTankBulletPositionY());
			//setHaveTankBullet(0);
			break;
		}
	}
	//drawBlankTankBullet(framePointer, getTankBulletPositionX(), 27);
}

void drawBlankAlienBullet(unsigned int * framePointer, int x, int y) {
	int row, col;
	xil_printf("blank(%d,%d)\r\n",x,y);
	for (row = 0; row < (ALIEN_BULLET_HEIGHT + ALIEN_BULLET_TRAVEL_DISTANCE); row++) {
		for (col = 0; col < (ALIEN_BULLET_WIDTH); col++) {
			if (framePointer[(row + y - ALIEN_BULLET_HEIGHT) * _640 + col + x] == _GREEN) {
				framePointer[(row + y - ALIEN_BULLET_HEIGHT) * _640 + col + x] = _GREEN;
			} else {
				framePointer[(row + y - ALIEN_BULLET_HEIGHT) * _640 + col + x]= _BLACK;
			}
		}
	}
}

void drawAlienBullets(unsigned int * framePointer) {

	int row, col, bullet, index;
	// this variable is a boolean to help break the second for loop when hit
	int hit = 0;
	for (bullet = 0; bullet < NUMBER_ALIEN_BULLETS; bullet++) {
		hit = 0;
//		drawBlankAlienBullet(framePointer, alienBullets[bullet].x,
//				alienBullets[bullet].y);
		// only draw if bullet is there
		if (alienBullets[bullet].isAvailable == ALIVE) {
			//xil_printf("BUNGHOLIO");

			for (row = 0; row < (ALIEN_BULLET_HEIGHT); row++) {
				for (col = 0; col < (ALIEN_BULLET_WIDTH); col++) {
					if ((alienBulletSymbol[alienBullets[bullet].bulletSymbol][row] & (1 << (ALIEN_BULLET_WIDTH - 1 - col)))) {
						// If bullet hits something green (bunker or tank)
						// draw blank bullet
						// Determine if it is bunker or tank
						// If bunker determine which one and change the state at that bunker
						// Else blow up tank, decrement lives, redraw tank
						// remove bullet and break loop


						if (alienBullets[bullet].y > TANK_Y_POSITION +10) {
							drawBlankAlienBullet(framePointer, alienBullets[bullet].x,
									alienBullets[bullet].y);

						}
						if (framePointer[(row + alienBullets[bullet].y) * _640
						                 + col + alienBullets[bullet].x] == _GREEN) {
							hit = 1;
							//drawBlankAlienBullet(framePointer, getTankBulletPositionX(), getTankBulletPositionY());
							// HIT a bunker
							if (alienBullets[bullet].y < TANK_Y_POSITION - 10) {
								//draw blank bullet

								//determine which bunker was hit and update the state array
								index = determineBunkerHit(
										alienBullets[bullet].x,
										alienBullets[bullet].y);
								int value = bunkerErosionState[index];
								if (value == 4) {
									value = 0;
								} else if (value == 3) {
									value = 3;
								} else {
									value = value + 1;
								}
								//xil_printf("\r\nIndex = %d, Value = %d",index, value);
								bunkerErosionState[index] = value;
								// Else hit the tank
							} else if (alienBullets[bullet].y
									>= TANK_Y_POSITION - 10
									&& alienBullets[bullet].y < TANK_Y_POSITION
									+ TANK_HEIGHT) {
								xil_printf("\r\nDELETED!");
								//blow up tank --> handled by fit. Just need to set the boolean to pause game action and blow up tank
								//redraw tank --> handled by fit so it can alternate between the bitmaps and give it a slight animation
								setGameInAction(1);
								//decrement lives

								drawLives(framePointer);
							} else {

							}
							alienBullets[bullet].isAvailable = 0;
							break;
						}
						if (alienBullets[bullet].y > 0) {
							framePointer[(row + alienBullets[bullet].y) * _640 + col + alienBullets[bullet].x]= _WHITE;
						} else {
							framePointer[(row + alienBullets[bullet].y) * _640 + col + alienBullets[bullet].x]= _BLACK;
						}
					}
					framePointer[(row + alienBullets[bullet].y - ALIEN_BULLET_HEIGHT) * _640 + col+ alienBullets[bullet].x] = _BLACK;
				}
				if (hit == 1) {
					break;
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
			if ((scoreSymbol[0][row] & (1 << (WORD_WIDTH - 1 - col)))) {
				framePointer[(row + BANNER_Y) * _640 + col] = _WHITE;
			} else {
				framePointer[(row + BANNER_Y) * _640 + col] = _BLACK;
			}
		}
	}
	for (row = 0; row < (LETTER_HEIGHT); row++) {
		for (col = 0; col < WORD_WIDTH; col++) {
			if ((scoreSymbol[1][row] & (1 << (WORD_WIDTH - 1 - col)))) {
				framePointer[(row + BANNER_Y) * _640 + col + WORD_WIDTH - 2] = _WHITE;
			} else {
				framePointer[(row + BANNER_Y) * _640 + col + WORD_WIDTH - 2] = _BLACK;
			}
		}
	}
}

void drawLivesBanner(unsigned int * framePointer) {
	int st = 350;
	int row, col;
	for (row = 0; row < (LETTER_HEIGHT); row++) {
		for (col = 0; col < WORD_WIDTH; col++) {
			if ((livesSymbol[0][row] & (1 << (WORD_WIDTH - 1 - col)))) {
				framePointer[(row + BANNER_Y) * _640 + st + col] = _WHITE;
			} else {
				framePointer[(row + BANNER_Y) * _640 + st + col] = _BLACK;
			}
		}
	}
	for (row = 0; row < (LETTER_HEIGHT); row++) {
		for (col = 0; col < WORD_WIDTH; col++) {
			if ((livesSymbol[1][row] & (1 << (WORD_WIDTH - 1 - col)))) {
				framePointer[(row + BANNER_Y) * _640 + st + col + WORD_WIDTH - 6]
				             = _WHITE;
			} else {
				framePointer[(row + BANNER_Y) * _640 + st + col + WORD_WIDTH - 6]
				             = _BLACK;
			}
		}
	}
}

void drawLives(unsigned int * framePointer) {
	int row, col, i;
	int xPos = 400;
	// Need to clear the screen of left overs
	for (i = 0; i < getNumberLives() + 1; i++) {
		for (row = 0; row < (TANK_HEIGHT); row++) {
			for (col = 0; col < (WORD_WIDTH); col++) {
				framePointer[(row) * _640 + col + xPos + i * WORD_WIDTH + i * 5] = _BLACK;
			}
		}
	}
	for (i = 0; i < getNumberLives(); i++) {
		for (row = 0; row < (TANK_HEIGHT); row++) {
			for (col = 0; col < (WORD_WIDTH); col++) {
				if ((tankSymbol[row] & (1 << (WORD_WIDTH - 1 - col)))) {
					framePointer[(row) * _640 + col + xPos + i * WORD_WIDTH + i
					             * 5] = _GREEN;
				} else {
					framePointer[(row) * _640 + col + xPos + i * WORD_WIDTH + i* 5] = _BLACK;
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
			if ((numbers[number][row] & (1 << (NUMBER_WIDTH - 1 - col)))) {
				framePointer[(row + BANNER_Y) * _640 + col + xPos] = _GREEN;
			} else {
				framePointer[(row + BANNER_Y) * _640 + col + xPos] = _BLACK;
			}
		}
	}
}

void drawBlankTank(unsigned int * framePointer) {
	int row, col;
	for (row = 0; row < (TANK_HEIGHT); row++) {
		for (col = 0; col < (WORD_WIDTH); col++) {
			framePointer[(row + TANK_Y_POSITION) * _640 + col
			             + getTankPositionGlobal()] = _BLACK;
		}
	}
}

void drawBlankSpaceShip(unsigned int * framePointer) {
	int row, col;
	for (row = 0; row < (SPACESHIP_HEIGHT); row++) {
		for (col = 0; col < (WORD_WIDTH); col++) {
			framePointer[(row + SPACESHIP_Y) * _640 + col + getSpaceShipPositionGlobal()] = _BLACK;
			framePointer[(row + SPACESHIP_Y) * _640 + col+ getSpaceShipPositionGlobal() - WORD_WIDTH] = _BLACK;
			framePointer[(row + SPACESHIP_Y) * _640 + col+ getSpaceShipPositionGlobal() + WORD_WIDTH] = _BLACK;
		}
	}
}

void drawScore(unsigned int * framePointer, int value) {
	int score = value;
	int count = 0;
	do {
		//draw right most first, then shift to the left 10*count
		drawNumber(framePointer, score % 10, RIGHT_NUMBER - count * 12);
		score /= 10;
		count++;
	} while (score);
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
	//int bunkerWidth = HALF_WORD_WIDTH*4;

	for (i = 0; i < 4; i++) {
		//xil_printf("\r\nFirst: %d, Second: %d", first + i*HALF_WORD_WIDTH, first + HALF_WORD_WIDTH * (i+1));
		if (x >= first + i * HALF_WORD_WIDTH && x < first + HALF_WORD_WIDTH
				* (i + 1)) {
			returnValue = i;
			break;
		}
	}
	// only need to calculate if value hasn't been found
	if (returnValue == -1) {
		for (i = 0; i < 4; i++) {
			if (x >= second + i * HALF_WORD_WIDTH && x < second
					+ HALF_WORD_WIDTH * (i + 1)) {
				returnValue = i + 4;
				break;
			}
		}
	}
	if (returnValue == -1) {
		for (i = 0; i < 4; i++) {
			if (x >= third + i * HALF_WORD_WIDTH && x < third + HALF_WORD_WIDTH
					* (i + 1)) {
				returnValue = i + 8;
				break;
			}
		}
	}
	if (returnValue == -1) {
		for (i = 0; i < 4; i++) {
			if (x >= fourth + i * HALF_WORD_WIDTH && x < fourth
					+ HALF_WORD_WIDTH * (i + 1)) {
				returnValue = i + 12;
				break;
			}
		}
	}

	//top row
	if (y >= 350 && y < 362) {
		//return value is the same - leave
	}
	// second row
	else if (y >= 362 && y < 374) {
		returnValue = returnValue + 16;
	}
	// third row
	else if (y >= 374 && y < 386) {
		//potential bug because of how i did bottom row - may need to redo
		returnValue = returnValue + 32;
	}
	//32 33 34 35				36 37 38 39			40 41 42 43		44 45 46 47
	// 32       33			34       35			36       37		38       39
	switch (returnValue) {
	case 35:
		returnValue = 33;
		break;
	case 36:
		returnValue = 34;
		break;
	case 39:
		returnValue = 35;
		break;
	case 40:
		returnValue = 36;
		break;
	case 43:
		returnValue = 37;
		break;
	case 44:
		returnValue = 38;
		break;
	case 47:
		returnValue = 39;
		break;
	}
	//xil_printf("\r\nx=%d, y=%d : return=%d", x, y,returnValue);
	return returnValue;
}

void drawSpaceShip(unsigned int * framePointer) {
	int row, col;

	//removeRedraw(framePointer, positionChange);
	for (row = 0; row < (SPACESHIP_HEIGHT); row++) {
		for (col = 0; col < (WORD_WIDTH); col++) {
			if (getSpaceShipPositionGlobal() + WORD_WIDTH <= 0
					|| getSpaceShipPositionGlobal() - WORD_WIDTH >= _640) {
				setHaveSpaceShip(0);
				//off = 1;
			}

			//Erase Ends
			framePointer[(row + SPACESHIP_Y) * _640 + col
			             + getSpaceShipPositionGlobal() - WORD_WIDTH] = _BLACK;
			framePointer[(row + SPACESHIP_Y) * _640 + col
			             + getSpaceShipPositionGlobal() + WORD_WIDTH] = _BLACK;

			//Draw Ship
			if ((spaceShipSymbol[row] & (1 << (WORD_WIDTH - 1 - col)))
					&& getSpaceShipPositionGlobal() + WORD_WIDTH <= _640
					&& getSpaceShipPositionGlobal() >= 0) {
				framePointer[(row + SPACESHIP_Y) * _640 + col
				             + getSpaceShipPositionGlobal()] = _RED;
			} else {
				framePointer[(row + SPACESHIP_Y) * _640 + col
				             + getSpaceShipPositionGlobal()] = _BLACK;
			}
		}
	}
}

void eraseTankBullet(unsigned int * framePointer) {
	xil_printf("FUGLY MOMMA");
	int row, col;
	//TANK_BULLET_HEIGHT+TANK_BULLET_TRAVEL_DISTANCE
	for (row = 0; row < 10; row++) {
		for (col = 0; col < (TANK_BULLET_WIDTH); col++) {
			framePointer[(row)*640 + col+getTankBulletPositionX()] = 0x00000000;

			//if ((tankBulletSymbol[row] & (1<<(TANK_BULLET_WIDTH-1-col)))) {
			//framePointer[(row+getTankBulletPositionY())*640 + col+getTankBulletPositionX()] = 0x000000FF;
			//}
		}
	}
}

