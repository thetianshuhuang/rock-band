/*
 * guitar.h
 *
 * Graphics for the onscreen guitar
 */
 
#ifndef GUITAR_H
#define GUITAR_H

#include <stdint.h>

#define resolution 10
#define red 0x001F
#define yellow 0x07FF
#define blue 0xF800
#define green 0x07E0

typedef struct red_note_struct {
    uint8_t x_path[resolution];
	  uint8_t y_path[resolution];
    uint16_t stage;
		uint16_t color;
} RedNote;

typedef struct yellow_note_struct {
    uint8_t x_path[resolution];
	  uint8_t y_path[resolution];
    uint16_t stage;
	  uint16_t color;
} YellowNote;

typedef struct blue_note_struct {
    uint8_t x_path[resolution];
	  uint8_t y_path[resolution];
    uint16_t stage;
	  uint16_t color;
} BlueNote;

typedef struct green_note_struct {
    uint8_t x_path[resolution];
	  uint8_t y_path[resolution];
    uint16_t stage;
	  uint16_t color;
} GreenNote;


// ----------drawGuitar----------
// initialize guitar graphics
// Parameters
//      none
void drawGuitar(void);

void updatePickups(uint16_t controller);


#endif
