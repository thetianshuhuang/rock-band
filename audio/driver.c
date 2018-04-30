/*
 * driver.c
 *
 * Audio driver
 * Plays raw hex-string audio files from an SD card
 */

#include "dac.h"
#include "../display/ff.h"
#include "../display/diskio.h"
#include "../display/ST7735.h"


// Set audio period
// Divider specifies the audio refresh rate as a fraction of 44.1kHz
#if DIVIDER == 4
#define AUDIO_PERIOD 0x1C58;
#elif DIVIDER == 2
#define AUDIO_PERIOD 0xE2C;
#elif DIVIDER == 1
#define AUDIO_PERIOD 0x716;
#else
#define DIVIDER 1
#define AUDIO_PERIOD 0x716;
#endif


// Status codes from the SD library
FRESULT mountStatus, openStatus, readStatus;
// FATFS object
static FATFS sdFileSystem;
// not sure what this is
FIL handle;
// not sure what this does either
UINT successfulreads;
// Data to be read from the SD card
uint8_t readBytes[2];
// Current index
uint32_t *currentIndex;


// ----------audioInit----------
// Initialize audio driver
void audioInit(void) {
    // Initialize DAC
    DACInit();
    // Initialize SD card filesystem
    mountStatus = f_mount(&sdFileSystem, "", 0);
}


// ----------startSong----------
// Start a song from the SD card
// Parameters:
//      char* songName: name of file to open
//      uint32_t* songCounter: pointer to current song index
void startSong(const char* songName, uint32_t* songCounter) {
    
    // Set up SysTick with priority 1, clock, and interrupts
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = AUDIO_PERIOD;
    NVIC_ST_CURRENT_R = 0;
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0X00FFFFFF) | 0X20000000;
    NVIC_ST_CTRL_R = 0x0007;
    
    // Open song
    openStatus = f_open(&handle, songName, FA_READ);
    // Link current index
    currentIndex = songCounter;
}


// ----------endSong----------
// End the current song
void endSong(void) {
    openStatus = f_close(&handle);
}


// ----------charToHex----------
// The the hex value of an ASCII character
// Parameters:
//      uint8_t input: character to look up
// Returns:
//      uint8_t: 1-byte hex int output
uint8_t charToHex(uint8_t input) {
    if('0' <= input && '9' >= input) {
        return(input - 48);
    }
    else {
        return(input - 55);
    }
}


// ----------updateSong----------
// Execute a song update
void updateSong() {
    readStatus = f_read(&handle, &readBytes, 2, &successfulreads);
    if(readStatus == 0) {
        DACOut(charToHex(readBytes[0]) << 4 | charToHex(readBytes[1]));
    }
    // Increment counter
    *currentIndex += DIVIDER;
}
