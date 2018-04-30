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
#include "../network/fifo.h"


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
uint8_t readByte[1];
// Current index
uint32_t *currentIndex;

FIFO_QUEUE audioQueue;

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
    
    SYSCTL_RCGCGPIO_R |= 0x20;
    __asm{NOP};
    __asm{NOP};
    GPIO_PORTF_DEN_R |= 0x0C;
    GPIO_PORTF_DIR_R |= 0x0C;
    GPIO_PORTF_AFSEL_R &= ~0x0C;
    GPIO_PORTF_AMSEL_R &= ~0x0C;
    
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
    
    fifoInit(&audioQueue);
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

// ----------sdRead----------
void sdRead(void) {
    if((readStatus == 0) && (audioQueue.size < 2048)) {
        GPIO_PORTF_DATA_R ^= 0x08;
        readStatus = f_read(&handle, &readByte, 1, &successfulreads);

        fifoPut(&audioQueue, readByte[0]);
        GPIO_PORTF_DATA_R ^= 0x08;

    }
}

// ----------updateSong----------
// Execute a song update
void updateSong() {
    
    GPIO_PORTF_DATA_R ^= 0x04;
    char data;
    fifoGet(&audioQueue, &data);
    DACOut(data);
    // Increment counter
    *currentIndex += DIVIDER;
    GPIO_PORTF_DATA_R ^= 0x04;

}
