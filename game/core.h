/*
 * core.h
 *
 * Core game mechanics for Rock Band
 */
 
#ifndef CORE_H
#define CORE_H

#include <stdint.h>


// Game state type
typedef struct game_state_t {
    uint8_t id;
    uint16_t score;
    uint16_t currentOffset;
    uint32_t tick;
} GAME_STATE;


// ----------initGame----------
// initialize game (start song)
// Parameters
//      const char* songName: song name to play
void initGame(const char* songName);


// ----------updateGame----------
// Update game state over network
// Parameters:
//      uint8_t* packet: byte string packet
void updateGame(uint8_t* packet);


#endif
