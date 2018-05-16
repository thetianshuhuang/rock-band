/*
 * settings.h
 *
 * Routines for modifying game settings
 */
 
#ifndef SETTINGS_H
#define SETTINGS_H

// ----------selectInstrument----------
// Set the player's current instrument
// Parameters:
//      uint8_t instrument: instrument to choose; GUITAR, BASS, or DRUMS
//          (matches enum instrument_t)
void selectInstrument(uint8_t instrument);


// ----------toggleDemo----------
// Toggle Demo Mode
void toggleDemo(void);

#endif
