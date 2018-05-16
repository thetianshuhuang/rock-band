/*
 * util.c
 *
 * Graphics utility routines
 */

#include <stdint.h>
#include "util.h"
#include "../display/ST7735.h"


const uint8_t specialChars[] = {
    0x3E, 0x3E, 0x1C, 0x1C, 0x08, // >
    0x30, 0x3C, 0x3E, 0x3C, 0x30, // ^
    0x0C, 0x3C, 0x7C, 0x3C, 0x0C, // v
    0x08, 0x1C, 0x1C, 0x3E, 0x3E, // <
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // []
    0x00, 0x00, 0x00, 0x00, 0x00, // ' '
};
// ----------drawSpecialChar----------
// Draw a special character on the screen.
// Parameters:
//      int16_t x: x coord
//      int16_t y: y coord
//      char c: character to draw
//      int16_t textColor: color to use
//      int16_t bgColor: background color for erasing
void drawSpecialChar(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor) {
    uint8_t line;
    for(uint8_t i = 0; i < 6; i++) {
        if(i == 5) {
            line = 0x0;
        }
        else {
            line = specialChars[(c * 5) + i];
        }
        for(uint8_t j = 0; j < 8; j++) {
            if(line & 0x1) {
                ST7735_DrawPixel(x + i, y + j, textColor);
            }
            else if (bgColor != textColor && c == 5) {
                ST7735_DrawPixel(x + i, y + j, bgColor);
            }
            line >>= 1;
        }
    }
}


// ----------vLine--------
// Draw vertical line
void vLine(uint8_t x, uint8_t y_1, uint8_t y_2, uint16_t color) {
    for(uint8_t coord = y_1; coord < y_2; coord++) {
        ST7735_DrawPixel(x, coord, color);
    }
}



