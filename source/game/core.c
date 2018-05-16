/*
 * core.h
 *
 * Core game mechanics for Rock Band
 */

#include "core.h"
#include "../audio/driver.h"
#include "../tm4c123gh6pm.h"
#include "../controller/controller.h"
#include "../graphics/guitar.h"
#include "../graphics/splash.h"
#include "songs.h"
#include "load_song.h"
#include "../network/uart.h"
#include "../menu/menu_defs.h"
#include "mechanics.h"


GAME_STATE playerState;

// Storage array for the current song
uint16_t currentTrack[2048];
// Tick tracker
uint16_t drawTicks;

// ----------initGame----------
// initialize game (start song)
// Parameters
//      uint8_t song: index of song to play
void initGame(uint8_t song) {
    
    // Forward UART
    uartWrite(0xA0 | song);

    // Demo mode: limit songs to 2:30
    if(playerState.runMode == FULL) {
        playerState.tick = songs[song].length + 112000;
    }
    // Default to demo mode
    else {
        playerState.tick = 6700000;
    }
    playerState.score = 0;
    playerState.head = 0;
    playerState.headPtr = 0;
    playerState.percent = 0;
    drawTicks = 3500;

    // Zero out track
    for(int i = 0; i < 3072; i++) {
        currentTrack[i] = 0x03FF;
    }
    
    // Load song from SD card
    if(playerState.instrument == GUITAR) {
        loadSong(currentTrack, songs[song].guitarTrack);
    }
    else if(playerState.instrument == BASS) {
        loadSong(currentTrack, songs[song].bassTrack);
    }
    else if(playerState.instrument == DRUMS) {
        loadSong(currentTrack, songs[song].drumsTrack);
    }
    // Null track
    else {}
    
    // Start song
    startSong(songs[song].byteWav, &(playerState.tick));
}


// ----------joinMultiplayer----------
// Join multiplayer game via serial
// Parameters
//      uint8_t foo: argument to match function definition in Menu library
void joinMultiplayer(uint8_t foo) {
    uint8_t data;
    // Show splash screen
    multiSplash();
    while(1) {
        // Check for back button
        if(controllerRead() & 0x2000) {
            showMenuByIndex(MAIN_MENU);
            break;
        }
        // Wait for sync byte
        if((uartRead(&data) != 0) && ((data & 0xF0) == 0xA0)) {
            uartWrite(data);
            initGame(data & 0x0F);
            break;
        }
    }
}


// ----------mainLoop----------
// Main game loop
void mainLoop(void) {
    drawGuitar();

    // Start at normal play
    int32_t starCounter = 0;
    playerState.guitarState = NORMAL;
    uint16_t drawCtr = 1000;
    showScore(0);
    
    // Clear note States
    for(uint8_t i = 0; i < 4; i++) {
        noteStates[i] = 0;
    }
    
    int16_t scoreChange;
    // Play until tick overflows
    while(playerState.tick < 0x8FFFFFFF) {
        
        // Clear artefacts periodically
        if(drawCtr == 0) {
            drawCtr = 1000;
            drawGuitar();
            showScore(playerState.score);
        }
        updatePickups(controllerRead());
        drawCtr --;
        
        // Get score change
        scoreChange = getScoreChange();
        updateScore(scoreChange);
        
        // Update star power
        starCounter = updateStarPower(starCounter, scoreChange);
    }
    
    // End song
    endSong();
    scoreSplash(playerState.score);
}


// ----------Timer0A_Handler----------
// Timer handler for ADC sampling and SD read
void Timer0A_Handler(void) {
    static uint8_t ADCCounter;

    // Clear interrupt
    TIMER0_ICR_R = TIMER_ICR_TATOCINT;
    // Take ADC sample
    if(ADCCounter > 40) {
        sampleAdc();
        ADCCounter = 0;
    }
    // Read sector
    readSector();

    ADCCounter += 1;
}


// ----------systick_Handler----------
void SysTick_Handler(void) {
    updateSong();
    // Increment note index when the next note is reached, and set remaining time
    if(playerState.head == 0) {
        do {
            playerState.head = 100 * (currentTrack[playerState.headPtr] & 0x03FF);
            playerState.headPtr += 1;
        } while(playerState.head == 0);
        // Create relevant notes
        createNotes(currentTrack[playerState.headPtr]);
    }
    if(drawTicks == 0) {
        drawTicks = 3500;
        moveNotes();
    }
    playerState.head -= 1;
    drawTicks -= 1;
}

