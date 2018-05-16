/*
 * mechanics.c
 *
 * Game mechanics routines (scoring, etc)
 */

#include <stdint.h>
#include "core.h"
#include "../graphics/guitar.h"
#include "../controller/controller.h"
#include "../controller/dsp.h"
#include "../accel/accel.h"


// ----------getScoreChange----------
// Get the score change during this loop
// Returns:
//      int16_t: scoreChange
int16_t getScoreChange(void) {
    // Exempt drums from strumming
    if(playerState.instrument == DRUMS) {
        return updateNote(0x1000, playerState.guitarState);
    }
    else {
        uint16_t change = derivative(controllerRead() & 0x0FFF);
        return updateNote(change, playerState.guitarState);
    }
}


// ----------updateScore----------
// Update the player score
// Parameters:
//      int16_t scoreChange: change in score
void updateScore(int16_t scoreChange) {

    // Track previous score, only update on change
    static uint16_t previousScore;
    
    // Update score
    if(playerState.score > 60000) {
        playerState.score = 0;
    }
    if(playerState.score != previousScore) {
        showScore(playerState.score);
    }
    previousScore = playerState.score;
}


// ----------updateStarPower----------
// Update current star power state
// Parameters:
//      int32_t starCounter: current star power counter
//      int16_t scoreChange: change in score this loop
// Returns:
//      int32_t: new starCounter
int32_t updateStarPower(int32_t starCounter, int16_t scoreChange) {
    // Check for normal->starpower transition
    if(playerState.guitarState == NORMAL) {
        starCounter += scoreChange;
        if(starCounter > 5000 && isStarpower()) {
            starCounter = 800;
            playerState.guitarState = STARPOWER;
            // Draw starpower
            drawGuitarLines(COLOR_STARPOWER);
        }
        playerState.score += scoreChange;
    }
    // Check for starpower->normal transistion
    if(playerState.guitarState == STARPOWER) {
        // Decrease star counter each cycle
        starCounter --;
        // Hits will extend the star counter; misses will decrease it
        if(scoreChange < 0) {
            starCounter += scoreChange;
        }
        else {
            starCounter += scoreChange / 20;
        }
        if(starCounter < 0) {
            playerState.guitarState = NORMAL;
            // Clear guitar
            drawGuitarLines(COLOR_NORMAL);
        }
        playerState.score += 2 * scoreChange;
    }
    
    return(starCounter);
}
