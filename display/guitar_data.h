/*
 * guitar_data.h
 *
 * Graphics data for the guitar
 */

#ifndef GUITAR_DATA_H
#define GUITAR_DATA_H

#include <stdint.h>

typedef struct note_profile_t {
    // Color
    const uint16_t color;
    // Path
    const uint8_t xPath[19];
    const uint8_t yPath[19];
    // Pickup Sprite (16x14)
    const uint16_t pickupSprite[224];
    const uint16_t pickupPressed[224];
} NOTE_PROFILE;

extern NOTE_PROFILE noteProfiles[4];

#endif
