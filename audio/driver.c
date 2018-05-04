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
#include "fifo.h"


// Set audio period
#define AUDIO_PERIOD 0x716;
#define DIVIDER 1;


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

    // Debug heartbeat init
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
    while(audioQueue.size < 18000) {
        readSector();
    }

    // Set silence at the beginning of the song
    silence = 114000;
    // Link current index
    currentIndex = songCounter;
    
    // Set up SysTick with priority 0, clock, and interrupts
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = AUDIO_PERIOD;
    NVIC_ST_CURRENT_R = 0;
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0X00FFFFFF) | 0x00000000;
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


// ----------readSector----------
// Read at most one sector from the SD card into the audio queue
void readSector(void) {
    uint8_t readByte;
    // Read until audioQueue is full, or at most two sectors, unless the queue is almost empty
    for(uint16_t i = 0; ((i < 1024) || audioQueue.size < 5000) && (audioQueue.size < 18000); i++) {
        readStatus = f_read(&handle, &readByte, 1, &successfulreads);
        if(readStatus == 0) {
            fifoPut(&audioQueue, readByte);
        }
    }
}


// ----------updateSong----------
// Execute a song update
void updateSong(void) {
    char data;
    if(silence == 0) {
        fifoGet(&audioQueue, &data);
        DACOut(data);
        *currentIndex -= DIVIDER;
    }
    else {
        silence --;
    }
}

