/*
 * driver.h
 *
 * Audio driver
 * Plays raw hex-string audio files from an SD card
 */
 
#ifndef DRIVER_H
#define DRIVER_H
#include "../network/fifo.h" 

// ----------audioInit----------
// Initialize audio driver
void audioInit(void);


// ----------startSong----------
// Start a song from the SD card
// Parameters:
//      char* songName: name of file to open
//      uint32_t* songCounter: pointer to current song index
void startSong(const char* songName, uint32_t* songCounter);


// ----------endSong----------
// End the current song
void endSong(void);


// ----------updateSong----------
// Execute a song update
void updateSong(void);

void sdRead(void);

#endif
