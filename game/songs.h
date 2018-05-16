/*
 * songs.h
 *
 * Song datatype definitions
 */
 
#ifndef SONGS_H
#define SONGS_H

#include <stdint.h>


// Song struct
typedef struct song_t {
    const char* byteWav;        // File name (*.bw)
    const char* guitarTrack;    // Guitar track (*.rb)
    const char* bassTrack;      // Bass track (*.rb)
    const char* drumsTrack;     // Drum track (*.rb)
    const uint32_t length;      // Length of song, in samples
} SONG;


// Included songs
enum songs_t {RYLAH, MIAB, WWL, ZZZ, HWR, TF};
extern SONG songs[6];

#endif
