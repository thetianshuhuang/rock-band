/*
 * load_song.h
 *
 * Subroutine to load a song from SD
 */

#ifndef LOAD_SONG_H
#define LOAD_SONG_H

#include <stdint.h>


// --------loadSong--------
// Load a song into a specified buffer.
// Parameters:
//      const char* trackName: name of file to read
//      uint16_t* readBuffer: buffer to fill
void loadSong(uint16_t* readBuffer, const char* trackName);

#endif
