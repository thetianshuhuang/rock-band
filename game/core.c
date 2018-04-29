/*
 * core.h
 *
 * Core game mechanics for Rock Band
 */

#include "core.h"


GAME_STATE playerStates[4];


// ----------initGame----------
// initialize game
void initGame(void) {
    for(uint8_t i = 0; i < 4; i++) {
        playerStates[i].tick = 0;
        playerStates[i].score = 10000;
        playerStates[i].currentOffset = 0;
    }
}


// ----------findId----------
// Helper function to find the game state corresponding to an ID
// Parameters:
//      uint8_t id: id to find
// Returns:
//      uint8_t: index of found game states; 0xFF for error
uint8_t findId(uint8_t id) {
    for(uint8_t i = 0; i < 4; i++) {
        if(playerStates[i].id == id) {
            return(i);
        }
    }
    return(0xFF);
}


// ----------updateGame----------
// Update game state over network
// Parameters:
//      uint8_t* packet: byte string packet
void updateGame(uint8_t* packet) {
    GAME_STATE *targetPlayer = &playerStates[findId(packet[2])];
    targetPlayer->score = ((uint16_t) packet[5] << 8) | packet[6];
    targetPlayer->currentOffset = ((uint16_t) packet[7] << 8) | packet[8];
    targetPlayer->tick = 
        (uint32_t) packet[9] << 24 |
        (uint32_t) packet[10] << 16 |
        (uint32_t) packet[11] << 8 |
        (uint32_t) packet[12];
}
