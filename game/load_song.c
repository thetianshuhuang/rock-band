/*
 * load_song.h
 *
 * Subroutine to load a song from SD
 */

#include "../display/diskio.h"
#include "../display/ff.h"
#include <stdint.h>


// Status codes from the SD library
FRESULT loadSongStatus;
// FATFS object
static FATFS loadSongFileSystem;
// not sure what this is
FIL songHandle;
// not sure what this does either
UINT songSuccessfulLoad;

// --------loadSong--------
// Load a song into a specified buffer.
// Parameters:
//      const char* trackName: name of file to read
//      uint16_t* readBuffer: buffer to fill
void loadSong(uint16_t* readBuffer, const char* trackName) {
    // Initialize filesystem
    do {
        loadSongStatus = f_mount(&loadSongFileSystem, "", 0);
    } while(loadSongStatus != 0);
    // Open file
    do {
        loadSongStatus = f_open(&songHandle, trackName, FA_READ);
    } while(loadSongStatus != 0);
    // Load buffer
    do {
        loadSongStatus = f_read(&songHandle, readBuffer, 3072, &songSuccessfulLoad);
    } while(loadSongStatus != 0);
}
