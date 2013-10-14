/*
 * bullets.c
 *
 *  Created on: Sep 29, 2013
 *      Author: superman
 */

#include "bullets.h"
#include "globals.h"


int tankBulletSymbol[TANK_BULLET_HEIGHT] =
{
		packWord2(1,1),
		packWord2(1,1),
		packWord2(1,1),
		packWord2(1,1),
		packWord2(1,1),
		packWord2(1,1),
		packWord2(1,1),
		packWord2(1,1),
};
//--------- CROSS BULLET 1
int alienBulletSymbol[NUMBER_ALIEN_BULLETS][ALIEN_BULLET_HEIGHT] =
{
		{
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(1,1,1,1,1,1),
			packWord6(1,1,1,1,1,1),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
		},
		{
		//	--------- CROSS BULLET 2
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(1,1,1,1,1,1),
			packWord6(1,1,1,1,1,1),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
		},
		{
				//--------- CROSS BULLET 3
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(1,1,1,1,1,1),
			packWord6(1,1,1,1,1,1),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
		},
		{
			//--------- SQUIGGLE BULLET 1
			packWord6(1,1,0,0,0,0),
			packWord6(1,1,0,0,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,0,0,1,1),
			packWord6(0,0,0,0,1,1),
			packWord6(0,0,1,1,0,0),
			packWord6(0,0,1,1,0,0),
			packWord6(1,1,0,0,0,0),
			packWord6(1,1,0,0,0,0),

		}, 
    {
//	--------- SQUIGGLE BULLET 2
      packWord6(0,0,1,1,0,0),
      packWord6(0,0,1,1,0,0),
      packWord6(1,1,0,0,0,0),
      packWord6(1,1,0,0,0,0),
      packWord6(0,0,1,1,0,0),
      packWord6(0,0,1,1,0,0),
      packWord6(0,0,0,0,1,1),
      packWord6(0,0,0,0,1,1),
      packWord6(0,0,1,1,0,0),
      packWord6(0,0,1,1,0,0)
    },
    {
//	--------- SQUIGGLE BULLET 4
      packWord6(0,0,0,0,1,1),
      packWord6(0,0,0,0,1,1),
      packWord6(0,0,1,1,0,0),
      packWord6(0,0,1,1,0,0),
      packWord6(1,1,0,0,0,0),
      packWord6(1,1,0,0,0,0),
      packWord6(0,0,1,1,0,0),
      packWord6(0,0,1,1,0,0),
      packWord6(0,0,0,0,1,1),
      packWord6(0,0,0,0,1,1)
    }

};


int blankTankBulletSymbol[TANK_BULLET_HEIGHT] =
{
		packWord2(0,0),
		packWord2(0,0),
		packWord2(0,0),
		packWord2(0,0),
		packWord2(0,0),
		packWord2(0,0),
		packWord2(0,0),
		packWord2(0,0),
};


int blankAlienBulletSymbol[ALIEN_BULLET_HEIGHT] =
{
      packWord6(0,0,0,0,0,0),
      packWord6(0,0,0,0,0,0),
      packWord6(0,0,0,0,0,0),
      packWord6(0,0,0,0,0,0),
      packWord6(0,0,0,0,0,0),
      packWord6(0,0,0,0,0,0),
      packWord6(0,0,0,0,0,0),
      packWord6(0,0,0,0,0,0),
      packWord6(0,0,0,0,0,0),
      packWord6(0,0,0,0,0,0)
};



//	--------- SQUIGGLE BULLET 3
//	packWord6(0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
//	packWord6(0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
//	packWord6(0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
//	packWord6(0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
//	packWord6(0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
//	packWord6(0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
//	packWord6(1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
//	packWord6(1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
//	packWord6(0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
//	packWord6(0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
//
//*/
