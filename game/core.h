/*
 * core.h
 *
 * Core game mechanics for Rock Band
 */
 
#ifndef CORE_H
#define CORE_H

#include <stdint.h>
#include "songs.h"


enum instrument_t {NULL, GUITAR, BASS, DRUMS};

// Game state type
typedef struct game_state_t {
    uint8_t id;
    uint16_t score;
    uint16_t currentOffset;
    uint32_t tick;
    uint16_t note;
    enum instrument_t instrument;
} GAME_STATE;

// ----------selectInstrument----------
// Set the player's current instrument
// Parameters:
//      enum instrument_t instrument: instrument to choose; GUITAR, BASS, or DRUMS
void selectInstrument(enum instrument_t instrument);


// ----------initGame----------
// initialize game (start song)
// Parameters
//      SONG song: song to play
void initGame(SONG *song);


// ----------mainLoop----------
// Main game loop
void mainLoop(void);


// ----------updateGame----------
// Update game state over network
// Parameters:
//      uint8_t* packet: byte string packet
void updateGame(uint8_t* packet);


#endif
