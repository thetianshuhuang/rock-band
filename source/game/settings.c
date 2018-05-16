/*
 * settings.c
 *
 * Routines for modifying game settings
 */

#include "core.h"

// ----------selectInstrument----------
// Set the player's current instrument
//      uint8_t instrument: instrument to choose; GUITAR, BASS, or DRUMS
//          (matches enum instrument_t)
void selectInstrument(uint8_t instrument) {
    playerState.instrument = (enum instrument_t) instrument;
}


// ----------toggleDemo----------
// Toggle Demo Mode
void toggleDemo(void) {
    if(playerState.runMode == DEMO) {
        playerState.runMode = FULL;
    }
    else {
        playerState.runMode = DEMO;
    }
}
