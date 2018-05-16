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
enum guitar_state_t {NORMAL, STARPOWER};
enum run_mode_t {DEMO, FULL};

// Game state type
typedef struct game_state_t {
    uint8_t id;
    uint16_t score;
    uint32_t tick;
    int32_t head;
    int32_t headPtr;
    int32_t tail;
    int32_t tailPtr;
    uint32_t percent;
    enum instrument_t instrument;
    enum guitar_state_t guitarState;
    enum run_mode_t runMode;
} GAME_STATE;

extern GAME_STATE playerState;


// ----------selectInstrument----------
// Set the player's current instrument
// Parameters:
//      uint8_t instrument: instrument to choose; GUITAR, BASS, or DRUMS
//          (matches enum instrument_t)
void selectInstrument(uint8_t instrument);


// ----------toggleDemo----------
// Toggle Demo Mode
void toggleDemo(void);


// ----------initGame----------
// initialize game (start song)
// Parameters
//      uint8_t song: index of song to play
void initGame(uint8_t song);


// ----------joinMultiplayer----------
// Join multiplayer game via serial
// Parameters
//      uint8_t foo: argument to match function definition in Menu library
void joinMultiplayer(uint8_t foo);


// ----------mainLoop----------
// Main game loop
void mainLoop(void);


// ----------updateGame----------
// Update game state over network
// Parameters:
//      uint8_t* packet: byte string packet
void updateGame(uint8_t* packet);


#endif
