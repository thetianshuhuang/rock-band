/*
 * songs.h
 *
 * Song datatype definitions
 */
 
#ifndef SONGS_H
#define SONGS_H

#include <stdint.h>

typedef struct song_t {
    const char* byteWav;
    const char* guitarTrack;
    const char* bassTrack;
    const char* drumsTrack;
    const uint32_t length;
} SONG;

extern SONG rockYouLikeAHurricane;
extern SONG messageInABottle;
extern SONG wildWildLife;
extern SONG zZz;
extern SONG headsWillRoll;
extern SONG theFuneral;

#endif
