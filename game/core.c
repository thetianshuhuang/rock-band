/*
 * core.h
 *
 * Core game mechanics for Rock Band
 */

#include "core.h"
#include "../audio/driver.h"
#include "../tm4c123gh6pm.h"
#include "../controller/controller.h"
#include "../display/guitar.h"


GAME_STATE playerStates[4];


// ----------selectInstrument----------
// Set the player's current instrument
// Parameters:
//      enum instrument_t instrument: instrument to choose; GUITAR, BASS, or DRUMS
void selectInstrument(enum instrument_t instrument) {
    playerStates[0].instrument = instrument;
}


// ----------initGame----------
// initialize game (start song)
// Parameters
//      const char* songName: song name to play
void initGame(const char* songName) {
    for(uint8_t i = 0; i < 4; i++) {
        playerStates[i].tick = 0;
        playerStates[i].score = 10000;
        playerStates[i].currentOffset = 0;
    }
	// Start graphics
    //drawGuitar();
    // Start song
    startSong(songName, &(playerStates[0].tick));
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


// ----------Timer0A_Handler----------
// Timer handler for ADC sampling and SD read
void Timer0A_Handler(void) {

    GPIO_PORTF_DATA_R ^= 0x08;

    // Clear interrupt
    TIMER0_ICR_R = TIMER_ICR_TATOCINT;
    // Take ADC sample
    sampleAdc();
    
    GPIO_PORTF_DATA_R ^= 0x08;
}
