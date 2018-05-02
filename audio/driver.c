/*
 * driver.c
 *
 * Audio driver
 * Plays raw hex-string audio files from an SD card
 */

#include "dac.h"
#include "driver.h"
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
// Current index
uint32_t *currentIndex;
// Audio buffer
FIFO_QUEUE audioQueue;


// ----------audioInit----------
// Initialize audio driver
void audioInit(void) {
    // Initialize DAC
    DACInit();
}


// ----------startSong----------
// Start a song from the SD card
// Parameters:
//      char* songName: name of file to open
//      uint32_t* songCounter: pointer to current song index
uint32_t silence;
void startSong(const char* songName, uint32_t* songCounter) {
    
    SYSCTL_RCGCGPIO_R |= 0x20;
    __asm{NOP};
    __asm{NOP};
    GPIO_PORTF_DEN_R |= 0x0C;
    GPIO_PORTF_DIR_R |= 0x0C;
    GPIO_PORTF_AFSEL_R &= ~0x0C;
    GPIO_PORTF_AMSEL_R &= ~0x0C;
    
    // Initialize SD card filesystem
    do {
        mountStatus = f_mount(&sdFileSystem, "", 0);
    } while(mountStatus != 0);

    // Open song and load the first sector
    do {
        openStatus = f_open(&handle, songName, FA_READ);
    } while(openStatus != 0);
    fifoInit(&audioQueue);
    while(audioQueue.size < 10000) {
        readSector();
    }
    
    silence = 70000;
    
    // Link current index
    currentIndex = songCounter;
    
    // Set up SysTick with priority 1, clock, and interrupts
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = AUDIO_PERIOD;
    NVIC_ST_CURRENT_R = 0;
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0X00FFFFFF) | 0x40000000;
    NVIC_ST_CTRL_R = 0x0007;
    // Start timer0 (ADC and SD)
    TIMER0_CTL_R = 0x00000001;
}


// ----------endSong----------
// End the current song
void endSong(void) {
    // Disable interrupts
    NVIC_ST_CTRL_R = 0;
    TIMER0_CTL_R = 0x00000000;
    // Close file
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


// ----------readSector----------
// Read at most one sector from the SD card into the audio queue
void readSector(void) {
    uint8_t readByte;
    for(uint16_t i = 0; (i < 512) && (audioQueue.size < 20000); i++) {
        readStatus = f_read(&handle, &readByte, 1, &successfulreads);
        if(readStatus == 0) {
            fifoPut(&audioQueue, readByte);
        }
    }
}


// ----------updateSong----------
// Execute a song update
void updateSong() {
    char data;
    if(silence == 0) {
        if(fifoGet(&audioQueue, &data)) {
            //GPIO_PORTF_DATA_R &= ~0x04;
            DACOut(data);
            *currentIndex -= DIVIDER;
        }
    }
    else {
        silence --;
    }
}

