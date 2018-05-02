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
#include "load_song.h"
#include "../controller/dsp.h"

GAME_STATE playerState;

Note testRed;
Note testYellow;
Note testBlue;
Note testGreen;
Note notes[20];
uint32_t noteIndex;

void incrementNotePointer(void){
	noteIndex++;
	if(noteIndex >= 20)
		noteIndex = 0;
}

// ----------selectInstrument----------
// Set the player's current instrument
// Parameters:
//      enum instrument_t instrument: instrument to choose; GUITAR, BASS, or DRUMS
void selectInstrument(enum instrument_t instrument) {
    playerState.instrument = instrument;
}


// Storage array for the current song
uint16_t currentTrack[2048];

// ----------initGame----------
// initialize game (start song)
// Parameters
//      SONG song: song to play
void initGame(SONG *song) {
    
    playerState.tick = song->length;
    playerState.score = 0;
    playerState.head = 0;
    playerState.tail = 100;
    playerState.headPtr = 0;
    playerState.tailPtr = 0;

    // Zero out track
    for(int i = 0; i < 2048; i++) {
        currentTrack[i] = 0xF00F;
    }
    
    // Load song from SD card
    if(playerState.instrument == GUITAR) {
        loadSong(currentTrack, song->guitarTrack);
    }
    else if(playerState.instrument == BASS) {
        loadSong(currentTrack, song->bassTrack);
    }
    else if(playerState.instrument == DRUMS) {
        loadSong(currentTrack, song->drumsTrack);
    }
    // Null track
    else {}
    
    // Start song
    startSong(song->byteWav, &(playerState.tick));
}


// ----------findId----------
// Helper function to find the game state corresponding to an ID
// Parameters:
//      uint8_t id: id to find
// Returns:
//      uint8_t: index of found game states; 0xFF for error
uint8_t findId(uint8_t id) {
    for(uint8_t i = 0; i < 4; i++) {
        if(playerState.id == id) {
            return(i);
        }
    }
    return(0xFF);
}

// ----------mainLoop----------
// Main game loop
void mainLoop(void) {
    drawGuitar();

    // Play until tick overflows
    while(playerState.tick < 0x8FFFFFFF) {
        for(int j = 0; j < resolution; j++)
        { 
					  uint16_t controller = controllerRead();
            uint16_t change = derivative(controller);
					
					  for(int i = 0; i < 20; i++)
					    if(playerState.instrument == DRUMS)
						    animateNote(&notes[i], &playerState, (uint16_t)100000);
							else 
								animateNote(&notes[i], &playerState, change);
					
					  updateScore(playerState.score);
            updatePickups(controller);
					  Delayms(12);
            if(checkPause() != 0) {
                playerState.tick = 0xEFFFFFFF;
                break;
            }
        }                
    }
    
    // End song
    endSong();
    
    showSplash("back.pi");
    ST7735_SetTextColor(0xFFFF);
    ST7735_SetCursor(3, 2);
    ST7735_OutString("Your Score:");
    ST7735_SetCursor(3, 3);
    ST7735_OutUDec(playerState.score);
    // Wait for input
    while((controllerRead() & 0xF000) == 0){};
}


/*
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
*/


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


// ----------systick_Handler----------
void SysTick_Handler(void) {
    updateSong();
    // Increment note index when the next note is reached, and set remaining time
    if(playerState.head == 0) {
        playerState.head = currentTrack[playerState.headPtr];
        playerState.headPtr += 1;
        // Create Red note			
		    if(currentTrack[playerState.headPtr] & 0x8000){
					initRedNote(&notes[noteIndex]);
					incrementNotePointer();
				}
				// Create Yellow note
				if(currentTrack[playerState.headPtr] & 0x4000){
					initYellowNote(&notes[noteIndex]);
					incrementNotePointer();
				}
				// Create Blue note
				if(currentTrack[playerState.headPtr] & 0x2000){
					initBlueNote(&notes[noteIndex]);
					incrementNotePointer();
				}
				// Create Green note
				if(currentTrack[playerState.headPtr] & 0x1000){
					initGreenNote(&notes[noteIndex]);
					incrementNotePointer();
				}
                //
    }
    if(playerState.tail <= 10) {
        uint16_t controller = controllerRead();
        uint16_t change = derivative(controller);
        // Large change -> clear bits that are set in controller
        if(change > 0x0080) {
            currentTrack[playerState.tailPtr] &= ~(controller & 0xF000);
        }
    }
    /*
    if(playerState.tail <= -10) {
        playerState.tail = currentTrack[playerState.tailPtr];
        // Check if note bits have all been cleared
        if((playerState.tailPtr & 0xF000) != 0) {
            playerState.score -= 100;
        }
        else {
            playerState.score += 100;
        }
        playerState.tailPtr += 1;
    }
		*/
    playerState.head -= 1;
    playerState.tail -= 1;
}

