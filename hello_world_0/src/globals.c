/*/*
 * globals.c
 *
 *  Created on: Sep 28, 2013
 *      Author: superman
 */

#include "globals.h"
#include <time.h>
#include <stdlib.h>

// Here are the globals.
int tankMovementDistance = 5;
int alienMovementDistance = 5;
int totalAlienMovement = 0;
int spaceShipPosition = 0;

short alienDirection = 1;
short shipDirection = 1;
int alienTimerCnt = 65;
int globalScore = 0;
//Set Alien Start Position
int alienBlockX = ALIEN_BLOCK_X_START;
int alienBlockY = ALIEN_BLOCK_Y_START;

int global_block_x_end = ALIEN_BLOCK_X_END;
int global_block_x_start = ALIEN_BLOCK_X_START;
int global_block_y_end = ALIEN_BLOCK_Y_END;

//Alien Offset Variables
int alienRightOffset= 0;
int alienLeftOffset = 0;

//Set Aliens to alive/dead 1/0
int alienLifeState[55] = { [0 ... 54] = 1 };
int alienColumnState[NUMBER_ALIEN_COLUMNS] = { [0 ... NUMBER_ALIEN_COLUMNS  -1] = 1};
int haveSpaceShip = 0;
int spaceShipPoints[4] = { 50, 100, 150, 300 };

// boolean to pause the game while the tank dies
// 1 = true, 0 = false;
// when tank dies pause everything else from incrementing and when death cinema is done then set this back
int gameInAction = 0;

short tankPosition = 30;
point_t tankBulletPosition;
point_t alienBlockPosition;
int numberLives = 3;
// Here are the accessors.
//

int getGameInAction() {
  return gameInAction;
}
void setGameInAction(int x) {
  gameInAction = x;
}

int getNumberLives() {
	//xil_printf("%d",numberLives);
  return numberLives;
}
void setNumberLives(int x) {
  numberLives = x;
}
void setAlienTimer(int time){
	alienTimerCnt = time;
}
int getAlienTimer(){
	return alienTimerCnt;

}

int getGlobalScore() {
  return globalScore;
}
void setGlobalScore(int x) {


  globalScore = x;
  xil_printf("score: %d",globalScore);
}
// 0 is no space ship
// 1 is have ship
int isHaveSpaceShip() {
	return haveSpaceShip;
}
void setHaveSpaceShip(int x) {
	haveSpaceShip = x;
}

int getSpaceShipPositionGlobal(){
	return spaceShipPosition;
}


void setSpaceShipPositionGlobal(int x) {
	spaceShipPosition = x;
}

void setTankPositionGlobal(short val) {
  tankPosition = val;
  if (tankPosition < 0) {
	  tankPosition = 0;
  } else if (tankPosition > SCREEN_WIDTH-WORD_WIDTH) {
	  tankPosition = SCREEN_WIDTH-WORD_WIDTH;
  }
}
short getTankPositionGlobal() {
  return tankPosition;
}

void reverseAlienDirection(){
	alienDirection = (-1)*alienDirection;
}
short getAlienDirection(){
	return alienDirection;
}

void setAlienOffset(int offset){
	//xil_printf("Call->setAlienOffset:%d\r\n",offset);
	//Positive numbers Right offset
	if(offset > 0){

		alienRightOffset=offset;
	}//Negative numbers Left offset
	if(offset < 0){

		alienLeftOffset= offset;
	}//Zero resets both
//	if(offset == 0){
//		alienRightOffset=offset;
//		alienLeftOffset=offset;
//	}

}
int getRightOffset(){
	return alienRightOffset;
}
int getLeftOffset(){
	return alienLeftOffset;
}

void setAlienPositionGlobal(unsigned short val){
	//For tracking score and length of game
	alienMovementDistance = val;

	if( alienBlockX >= (ALIEN_BLOCK_X_END+ getRightOffset()*WORD_WIDTH) && getAlienDirection() == 1 ){
		//xil_printf("set alien Case 1:Rightoffset:%d\r\n",getRightOffset());
		alienBlockY = alienBlockY + val;
		alienBlockX = ALIEN_BLOCK_X_END + getRightOffset()*WORD_WIDTH;

		//begin decrementing alienBlockX
		if(getAlienDirection() == 1)
			reverseAlienDirection();

	}
	else if( alienBlockX <= (ALIEN_BLOCK_X_START + getLeftOffset()*WORD_WIDTH) && getAlienDirection() == -1){
		//xil_printf("set alien Case 2:Letoffset:%d\r\n",getLeftOffset());
		alienBlockY = alienBlockY + val;
		alienBlockX = ALIEN_BLOCK_X_START + getLeftOffset()*WORD_WIDTH;

		reverseAlienDirection();

	}else{
		//xil_printf("set alien Case 3:Leftoffset:%d\r\n",getLeftOffset());
				alienBlockX = alienBlockX + val*getAlienDirection();
				//Code prevents remainder of value from causing screen off.
			if(alienBlockX > (ALIEN_BLOCK_X_END+getRightOffset()*WORD_WIDTH)){
					alienBlockX = (ALIEN_BLOCK_X_END + getRightOffset()*WORD_WIDTH);
			}
			if(alienBlockX < ALIEN_BLOCK_X_START+getLeftOffset()*WORD_WIDTH){
				alienBlockX = ALIEN_BLOCK_X_START+getLeftOffset()*WORD_WIDTH;
			}
	}




}
unsigned int getAlienPositionGlobal() {
	return alienBlockY*640 + alienBlockX;

}
point_t getAlienXYGlobal(){
		alienBlockPosition.x = alienBlockX;
		alienBlockPosition.y = alienBlockY;
	return alienBlockPosition;

}
int getAlienMovementGlobal(){
	return alienMovementDistance;

}

void setAlienLifeState(int alien){
	//1 is alive and 0 is dead
	//Function Defaults to dead
	if((alien < 55) && (alien > -1) )
		alienLifeState[alien] = DEAD;
	else
		xil_printf("ERROR: ALIEN OUT OF BOUNDS!!!");
}
int getAlienLifeState(int alien){
return alienLifeState[alien];
}
void setTankBulletPosition(point_t val) {
  tankBulletPosition.x = val.x;
  tankBulletPosition.y = val.y;
}

point_t getTankBulletPosition() {
  return tankBulletPosition;
}

//////////////// Another way to do this without structs ////////////////
unsigned short tankBulletPositionX;
unsigned short tankBulletPositionY;

void setTankBulletPositionX(short val) {tankBulletPositionX = val;}
void setTankBulletPositionY(short val) {tankBulletPositionY = val;}

short getTankBulletPositionX(){return tankBulletPositionX;}
short getTankBulletPositionY(){return tankBulletPositionY;}

// 0 -> no bullet; 1 -> bullet
int haveTankBullet = ALIVE;
void setHaveTankBullet(int x) {
	haveTankBullet = x;
}

int isHaveTankBullet() {
	return haveTankBullet;
}

int generateRandomNumber(int number) {
	int tmp = (rand()%(number));
	//xil_printf("POO: %d, %d)\r\n", number, tmp);
	return tmp;
  //  int x= (double)rand()/RAND_MAX;
    //xil_printf("RANDOMGEN: %d, %d", number,(number+1)*x);
    //return (number+1)/x;
}
int generateRandomNumberInterval(int number0, int number1) {
  return ( rand() % ( number1 - number0 ) ) + number0;
}

point_t generateRandomAlienBulletPosition() {
	 point_t alienPoint;
  double a = (double) rand()/RAND_MAX;
  int b = (NUMBER_ALIEN_COLUMNS + 1)*a;
  if (alienColumnState[b]== 1) {
    //check val+row looop and return when meets
    int i;
    for (i = NUMBER_ALIEN_ROWS; i > 0; i--) {
      if (alienLifeState[b+11*i] == 1) {
      //NEED x and y of alien block point to add
        alienPoint.x = b*WORD_WIDTH + getAlienXYGlobal().x + WORD_WIDTH*3/2;
        alienPoint.y = i*ALIEN_HEIGHT + getAlienXYGlobal().y+ALIEN_HEIGHT;
        break;
      }
    }
  } else {
    alienPoint = generateRandomAlienBulletPosition();
  }
  return alienPoint;
}

void initGameDefaults() {
	int i = 0;
	//int bunkerErosionState[38];
	for (i = 0; i < NUMBER_BUNKER_ELEMENTS+1; i++) {
		bunkerErosionState[i] = 4;
	}
	for (i = 0; i < NUMBER_ALIEN_BULLETS; i++) {
		alienBullets[i].isAvailable = 0;
		alienBullets[i].x = 0;
		alienBullets[i].y = 0;
		alienBullets[i].bulletSymbol = 0;
	}
	setHaveTankBullet(0);
//  setAlienSpaceShipPosition(0-SPACESHIP_WIDTH);
}

void setBunkerErosionState(int x) {
	int i = 0;
	for (i = 0; i < NUMBER_BUNKER_ELEMENTS; i++) {
		bunkerErosionState[i] = x;
	}
}


