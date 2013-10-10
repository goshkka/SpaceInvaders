/*
 * gameFunctions.h
 *
 *  Created on: Sep 28, 2013
 *      Author: superman
 */

#ifndef GAMEFUNCTIONS_H_
#define GAMEFUNCTIONS_H_


#define R0W_SEP_HEIGHT 5

void removeRedraw(unsigned int * framePointer, int positionChange);
void drawAlienBlock(unsigned int * framePointer, int positionChange);
void drawAlien(int x, int y, int alienType, unsigned int * framePointer);

void drawBunkerBlock(unsigned int * framePointer);
void drawTankBullet(unsigned int * framePointer);
void drawAlienBullets(unsigned int * framePointer);
void drawSpaceShip(unsigned int * framePointer);

int isEven(int n);
void killAlien(int n);

#endif /* GAMEFUNCTIONS_H_ */
