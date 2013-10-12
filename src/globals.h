/*
 * globals.h
 *
 *  Created on: Sep 28, 2013
 *      Author: superman
 */
#include <stdio.h>

#ifndef GLOBALS_H_
#define GLOBALS_H_

#define ALIEN_BLOCK_COLUMNS 11
#define ALIEN_BLOCK_ROWS 5
#define ALIEN_BLOCK_X_START 0
#define ALIEN_BLOCK_Y_START 0
#define ALIEN_BLOCK_X_END 640-ALIEN_BLOCK_WIDTH
#define ALIEN_BLOCK_Y_END ALIEN_BLOCK_HEIGHT+5*ROW_SEPERATOR_HEIGHT
#define ALIEN_HEIGHT 16
#define ROW_SEPERATOR_HEIGHT 6
#define WORD_WIDTH 32
#define HALF_WORD_WIDTH 16
#define ALIEN_BLOCK_HEIGHT ALIEN_HEIGHT*5
#define ALIEN_BLOCK_WIDTH WORD_WIDTH*ALIEN_BLOCK_COLUMNS
#define RIGHT 1
#define LEFT -1
#define ALIVE 1
#define DEAD  0

//BUTTON MAPPING
//       16
//  8   1   2
//       4
#define LEFT_BUTTON   8 //0x00001000
#define MIDDLE_BUTTON 1 //0x00000001
#define RIGHT_BUTTON 2 //0x00000010
#define TOP_BUTTON     16 //0x00010000
#define BOTTOM_BUTTON   4 //0x00000100
#define TRUE 1
#define FALSE 0



#define TANK_HEIGHT 16
#define TANK_Y_POSITION 415
#define TANK_BULLET_HEIGHT 8
#define TANK_BULLET_WIDTH 2
#define TANK_BULLET_TRAVEL_DISTANCE 4

#define NUMBER_ALIEN_COLUMNS 11
#define NUMBER_ALIEN_ROWS 5
#define ALIEN_BULLET_HEIGHT 10
#define NUMBER_ALIEN_BULLETS 4
#define ALIEN_BULLET_WIDTH 6
#define ALIEN_BULLET_TRAVEL_DISTANCE 8

#define BUNKER_HEIGHT 12
#define NUMBER_BUNKER_ELEMENTS 39
#define LETTER_HEIGHT 10

#define SPACESHIP_HEIGHT 16
#define SPACESHIP_WIDTH 32

// Packs each horizontal line of the figures into a single 2 bit word.
#define packWord2(b1,b0) 											  \
((b1  << 1 ) | (b0  << 0 ))

// Packs each horizontal line of the figures into a single 16 bit word.
#define packWord6(b5,b4,b3,b2,b1,b0) 											  \
((b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )


// Packs each horizontal line of the figures into a single 16 bit word.
#define packWord16(b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) 											  \
((b15 << 15) | (b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |	  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

// Packs each horizontal line of the figures into a single 32 bit word.
#define packWord32(b31,b30,b29,b28,b27,b26,b25,b24,b23,b22,b21,b20,b19,b18,b17,b16,b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) \
((b31 << 31) | (b30 << 30) | (b29 << 29) | (b28 << 28) | (b27 << 27) | (b26 << 26) | (b25 << 25) | (b24 << 24) |						  \
 (b23 << 23) | (b22 << 22) | (b21 << 21) | (b20 << 20) | (b19 << 19) | (b18 << 18) | (b17 << 17) | (b16 << 16) |						  \
 (b15 << 15) | (b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )


// Packs each horizontal line of the figures into a single 32 bit word.
#define packWord64(b63, b62, b61, b60, b59, b58, b57, b56, b55, b54, b53, b52, b51, b50, b49, b48, b47, b46, b45, b44, b43, b42, b41, b40, b39, b38, b37, b36, b35, b34, b33, b32, b31,b30,b29,b28,b27,b26,b25,b24,b23,b22,b21,b20,b19,b18,b17,b16,b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) \
((b63 << 63) | (b62 << 62) | (b61 << 61) | (b60 << 60) | (b59 << 59) | (b58 << 58) | (b57 << 57) | (b56 << 56) |						  \
 (b55 << 55) | (b54 << 54) | (b53 << 53) | (b52 << 52) | (b51 << 51) | (b50 << 50) | (b49 << 49) | (b48 << 48) |						  \
 (b47 << 47) | (b46 << 46) | (b45 << 45) | (b44 << 44) | (b43 << 43) | (b42 << 42) | (b41 << 41) | (b40 << 40) |						  \
 (b39 << 39) | (b38 << 38) | (b37 << 37) | (b36 << 36) | (b35 << 35) | (b34 << 34) | (b33 << 33) | (b32 << 32) |						  \
 (b31 << 31) | (b30 << 30) | (b29 << 29) | (b28 << 28) | (b27 << 27) | (b26 << 26) | (b25 << 25) | (b24 << 24) |						  \
 (b23 << 23) | (b22 << 22) | (b21 << 21) | (b20 << 20) | (b19 << 19) | (b18 << 18) | (b17 << 17) | (b16 << 16) |						  \
 (b15 << 15) | (b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )


#define alienBottomPoint 10
#define alienMiddlePoint 20
#define alienTopPoint 40

int globalScore;

typedef struct {unsigned short x; unsigned short y;} point_t;
typedef struct {
	int isAvailable;
	short x;
	short y;
	int bulletSymbol;
} alienBullet;

alienBullet alienBullets[NUMBER_ALIEN_BULLETS];


int getSpaceShipPositionGlobal();
void setSpaceShipPositionGlobal(int x);

void reverseAlienDirection();
short getAlienDirection();

void setAlienPositionGlobal(unsigned short val);
unsigned int getAlienPositionGlobal();
point_t getAlienXYGlobal();
int getAlienMovementGlobal();



void setTankPositionGlobal(unsigned short val);
unsigned short getTankPositionGlobal();

void setTankBulletPosition(point_t val);
point_t getTankBulletPosition();
point_t generateRandomAlienBulletPosition();

//////////// Another way to do it without structs. //////////////
void setTankBulletPositionX(short val);
void setTankBulletPositionY(short val);

short getTankBulletPositionX();
short getTankBulletPositionY();

int alienLifeState[55];

void setAlienLifeState(int alien);
int getAlienLifeState(int alien);
int alienBlockX;
int alienBlockY;
int tankMovementDistance;


// erosion state of bunkers will be a single array that looks like the following
// 0  1  2  3			4  5  6  7			8  9  10 11			12 13 14 15
// 16 17 18 19			19 20 21 22			23 24 25 26			27 28 29 30
// 31       32			33       34			35       36			37       38
// The values stored in here will be from 0 - 3 for the erosion. 0 = 1 hit and 3 = gone
// this will be initialized to -1 : which means they are to be drawn complete
int bunkerErosionState[NUMBER_BUNKER_ELEMENTS];

void setBunkerErosionState(int x);
int haveTankBullet;
void setHaveTankBullet(int x);
int isHaveTankBullet();

int generateRandomNumber(int number);
int alienColumnState[NUMBER_ALIEN_COLUMNS];

void initGameDefaults();
void drawTank(unsigned int *framePointer);

#endif /* GLOBALS_H_ */
