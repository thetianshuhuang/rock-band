/*
 * mechanics.h
 *
 * Game mechanics routines (scoring, etc)
 */
 
#ifndef MECHANICS_H
#define MECHANICS_H

#include <stdint.h>


// ----------getScoreChange----------
// Get the score change during this loop
// Returns:
//      int16_t: scoreChange
int16_t getScoreChange(void);


// ----------updateScore----------
// Update the player score
// Parameters:
//      int16_t scoreChange: change in score
void updateScore(int16_t scoreChange);


// ----------updateStarPower----------
// Update current star power state
// Parameters:
//      int32_t starCounter: current star power counter
//      int16_t scoreChange: change in score this loop
// Returns:
//      int32_t: new starCounter
int32_t updateStarPower(int32_t starCounter, int16_t scoreChange);


#endif
