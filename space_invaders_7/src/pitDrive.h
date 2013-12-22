/*
 * pitDrive.h
 *
 *  Created on: Nov 7, 2013
 *      Author: superman
 */

#ifndef PITDRIVE_H_
#define PITDRIVE_H_


/* Returns the int value of the control bit
 * 
 */
int getControlValue();

/*
 * Toggles the counter bit. 
 * Return 1 the bit is set to decrement
 * Return 0 the counter is stopped
 */
int toggleCounter();

/*
 * Toggles the interrupt
 * Return 1 the interrupt is enabled
 * Return 0 the interrupt is disabled
 */

/*
 * This allows the delayValue to be reset when count reaches zero
 * Return 1 the delayValue will be reset
 * Return 0 when counter finishes decrementing the value stays at 0
 */
int toggleRestoreValue();

/* 
 * Sets the delay value
 */
void setDelayValue(int value);

/*
 * return the delayValue
 */
int getDelayValue();

#endif /* PITDRIVE_H_ */
