/*
 * util.h
 *
 * Graphics utility routines
 */

#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>


// ----------drawSpecialChar----------
// Draw a special character on the screen.
// Parameters:
//      int16_t x: x coord
//      int16_t y: y coord
//      char c: character to draw
//      int16_t textColor: color to use
//      int16_t bgColor: background color for erasing
void drawSpecialChar(
    int16_t x, int16_t y,
    char c, int16_t textColor, int16_t bgColor);


// ----------vLine--------
// Draw vertical line
void vLine(uint8_t x, uint8_t y_1, uint8_t y_2, uint16_t color);


#endif
