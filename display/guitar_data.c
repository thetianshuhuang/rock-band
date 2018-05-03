/*
 * guitar_data.c
 *
 * Graphics data for the guitar
 */

#include "guitar_data.h"

// Order:
// [0] Red
// [1] Yellow
// [2] Blue
// [3] Green
NOTE_PROFILE noteProfiles[4] = {
    //
    // Red note
    //
    {
        0x001F,
        {82, 82, 83, 85, 87, 88, 89, 90, 92, 94, 95, 96, 97, 98, 99, 100, 102, 104, 105},
        {0, 4, 10, 19, 30, 40, 48, 57, 65, 74, 82, 90, 98, 106, 114, 122, 130, 138, 146},
        {
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000,
            0x0000, 0x001F, 0x001F, 0x001F, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x001F, 0x001F, 0x001F, 0x0000,
            0x001F, 0x001F, 0x001F, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x001F, 0x001F, 0x001F,
            0x001F, 0x001F, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x001F, 0x001F,
            0x001F, 0x001F, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x001F, 0x001F,
            0x001F, 0x001F, 0x001F, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x001F, 0x001F, 0x001F,
            0x0000, 0x001F, 0x001F, 0x001F, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x001F, 0x001F, 0x001F, 0x0000,
            0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
        },
        {
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000,
            0x0000, 0x001F, 0x001F, 0x001F, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x001F, 0x001F, 0x001F, 0x0000,
            0x001F, 0x001F, 0x001F, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x001F, 0x001F, 0x001F,
            0x001F, 0x001F, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x001F, 0x001F,
            0x001F, 0x001F, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x001F, 0x001F,
            0x001F, 0x001F, 0x001F, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x001F, 0x001F, 0x001F,
            0x0000, 0x001F, 0x001F, 0x001F, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x001F, 0x001F, 0x001F, 0x0000,
            0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
        },
    },
    //
    // Yellow Note
    //
    {
        0x07FF,
        {66, 66, 67, 67, 68, 69, 69, 69, 70, 70, 71, 71, 71, 71, 72, 72, 73, 73, 74},
        {0, 4, 10, 19, 30, 40, 48, 57, 65, 74, 82, 90, 98, 106, 114, 122, 130, 138, 146},
        {
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x07FF, 0x07FF, 0x07FF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07FF, 0x07FF, 0x07FF, 0x0000, 0x0000,
            0x0000, 0x07FF, 0x07FF, 0x07FF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x07FF, 0x07FF, 0x07FF, 0x0000,
            0x07FF, 0x07FF, 0x07FF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x07FF, 0x07FF, 0x07FF,
            0x07FF, 0x07FF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x07FF, 0x07FF,
            0x07FF, 0x07FF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x07FF, 0x07FF,
            0x07FF, 0x07FF, 0x07FF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x07FF, 0x07FF, 0x07FF,
            0x0000, 0x07FF, 0x07FF, 0x07FF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x07FF, 0x07FF, 0x07FF, 0x0000,
            0x0000, 0x0000, 0x07FF, 0x07FF, 0x07FF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07FF, 0x07FF, 0x07FF, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
        },
        {
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x07FF, 0x07FF, 0x07FF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07FF, 0x07FF, 0x07FF, 0x0000, 0x0000,
            0x0000, 0x07FF, 0x07FF, 0x07FF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07FF, 0x07FF, 0x07FF, 0x0000,
            0x07FF, 0x07FF, 0x07FF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07FF, 0x07FF, 0x07FF,
            0x07FF, 0x07FF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07FF, 0x07FF,
            0x07FF, 0x07FF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07FF, 0x07FF,
            0x07FF, 0x07FF, 0x07FF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07FF, 0x07FF, 0x07FF,
            0x0000, 0x07FF, 0x07FF, 0x07FF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07FF, 0x07FF, 0x07FF, 0x0000,
            0x0000, 0x0000, 0x07FF, 0x07FF, 0x07FF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07FF, 0x07FF, 0x07FF, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
        },
    },
    //
    // Blue Note
    //
    {
        0xF800,
        {53, 53, 52, 52, 51, 50, 50, 50, 49, 49, 48, 48, 48, 48, 47, 47, 46, 46, 45},
        {0, 4, 10, 19, 30, 40, 48, 57, 65, 74, 82, 90, 98, 106, 114, 122, 130, 138, 146},
        {
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000,
            0x0000, 0xF800, 0xF800, 0xF800, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xF800, 0xF800, 0xF800, 0x0000,
            0xF800, 0xF800, 0xF800, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xF800, 0xF800, 0xF800,
            0xF800, 0xF800, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xF800, 0xF800,
            0xF800, 0xF800, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xF800, 0xF800,
            0xF800, 0xF800, 0xF800, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xF800, 0xF800, 0xF800,
            0x0000, 0xF800, 0xF800, 0xF800, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xF800, 0xF800, 0xF800, 0x0000,
            0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
        },
        {
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000,
            0x0000, 0xF800, 0xF800, 0xF800, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF800, 0xF800, 0xF800, 0x0000,
            0xF800, 0xF800, 0xF800, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF800, 0xF800, 0xF800,
            0xF800, 0xF800, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF800, 0xF800,
            0xF800, 0xF800, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF800, 0xF800,
            0xF800, 0xF800, 0xF800, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF800, 0xF800, 0xF800,
            0x0000, 0xF800, 0xF800, 0xF800, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF800, 0xF800, 0xF800, 0x0000,
            0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
        },
    },
    //
    // Green Note
    //
    {
        0x07E0,
        {37, 37, 36, 34, 32, 31, 30, 29, 27, 26, 24, 23, 22, 21, 20, 19, 17, 15, 14},
        {0, 4, 10, 19, 30, 40, 48, 57, 65, 74, 82, 90, 98, 106, 114, 122, 130, 138, 146},
        {
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000,
            0x0000, 0x07E0, 0x07E0, 0x07E0, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x07E0, 0x07E0, 0x07E0, 0x0000,
            0x07E0, 0x07E0, 0x07E0, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x07E0, 0x07E0, 0x07E0,
            0x07E0, 0x07E0, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x07E0, 0x07E0,
            0x07E0, 0x07E0, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x07E0, 0x07E0,
            0x07E0, 0x07E0, 0x07E0, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x07E0, 0x07E0, 0x07E0,
            0x0000, 0x07E0, 0x07E0, 0x07E0, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x07E0, 0x07E0, 0x07E0, 0x0000,
            0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
        },
        {
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000,
            0x0000, 0x07E0, 0x07E0, 0x07E0, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07E0, 0x07E0, 0x07E0, 0x0000,
            0x07E0, 0x07E0, 0x07E0, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07E0, 0x07E0, 0x07E0,
            0x07E0, 0x07E0, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07E0, 0x07E0,
            0x07E0, 0x07E0, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07E0, 0x07E0,
            0x07E0, 0x07E0, 0x07E0, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07E0, 0x07E0, 0x07E0,
            0x0000, 0x07E0, 0x07E0, 0x07E0, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07E0, 0x07E0, 0x07E0, 0x0000,
            0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
        }
    }
    
};
