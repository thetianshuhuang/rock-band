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
#include "../PLL.h"
#include "../display/ST7735.h"
#include "../display/splash.h"
#include "songs.h"

GAME_STATE playerStates[4];


// ----------selectInstrument----------
// Set the player's current instrument
// Parameters:
//      enum instrument_t instrument: instrument to choose; GUITAR, BASS, or DRUMS
void selectInstrument(enum instrument_t instrument) {
    playerStates[0].instrument = instrument;
}


// Storage array for the current song
uint16_t currentTrack[1500];

// ----------initGame----------
// initialize game (start song)
// Parameters
//      SONG song: song to play
void initGame(SONG *song) {
    for(uint8_t i = 0; i < 4; i++) {
        playerStates[i].tick = song->length;
        playerStates[i].score = 10000;
        playerStates[i].currentOffset = 0;
        playerStates[i].note = 0;
    }
    // Load song from SD card
    /*
    if(playerStates[0].instrument == GUITAR) {
        something something load(song->guitarTrack);
    }
    else if(playerStates[0].instrument == BASS) {
        something something load(song->bassTrack);
    }
    else if(playerStates[0].instrument == DRUMS) {
        something something load(song->drumsTrack);
    }
    // Null track
    else {
        don't load any track
    }
    */
    
    // Start song
    startSong(song->byteWav, &(playerStates[0].tick));
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


Note testRed;
Note testYellow;
Note testBlue;
Note testGreen;
// ----------mainLoop----------
// Main game loop
void mainLoop(void) {
    drawGuitar();

    // Play until tick overflows
    while(playerStates[0].tick < 0x8FFFFFFF) {
        initRedNote(&testRed);
        initYellowNote(&testYellow);
        initBlueNote(&testBlue);
        initGreenNote(&testGreen);
        for(int i = 0; i < resolution; i++)
        { 
            animateNote(&testRed);
            animateNote(&testYellow);
            animateNote(&testBlue);
            animateNote(&testGreen);
            updatePickups(controllerRead());
            Delayms(12);
        }    
    }
    
    // End song
    endSong();
    
    showSplash("back.pi");
    ST7735_SetTextColor(0xFFFF);
    ST7735_SetCursor(3, 2);
    ST7735_OutString("Your Score:");
    ST7735_SetCursor(3, 3);
    ST7735_OutUDec(playerStates[0].score);
    // Wait for input
    while((controllerRead() & 0xF000) == 0){};


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
    // Read sector
    readSector();
    
    GPIO_PORTF_DATA_R ^= 0x08;
}
