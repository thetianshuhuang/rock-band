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
/*
uint8_t red_x_path[] = {};
uint8_t red_y_path[] = {0, 10, 30, 48, 65, 82, 98, 114, 130, 146};
uint8_t yellow_x_path[] = {53, 52, 51, 50, 49, 48, 48, 47, 46, 45};
uint8_t yellow_y_path[] = {0, 10, 30, 48, 65, 82, 98, 114, 130, 146};
uint8_t blue_x_path[] = {53, 52, 51, 50, 49, 48, 48, 47, 46, 45};
uint8_t blue_y_path[] = {0, 10, 30, 48, 65, 82, 98, 114, 130, 146};
uint8_t green_x_path[] = {};
uint8_t green_y_path[] = {0, 10, 30, 48, 65, 82, 98, 114, 130, 146};
*/

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
