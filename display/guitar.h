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

typedef struct {
    uint8_t pos_x;
	  uint8_t pos_y;
	  uint8_t size_x;
	  uint8_t size_y;
		uint16_t *bmp;
} Pickup;

typedef struct {
    uint8_t *x_path;
	  uint8_t *y_path;
    uint16_t stage;
		uint16_t color;
	  Pickup *pickup;
} Note;

// ----------drawGuitar----------
// initialize guitar graphics
// Parameters
//      none
void drawGuitar(void);

void updatePickups(uint16_t controller);

void initRedPickup(Pickup *pickup);
void initYellowPickup(Pickup *pickup);
void initBluePickup(Pickup *pickup);
void initGreenPickup(Pickup *pickup);

void initRedNote(Note *note);
void initYellowNote(Note *note);
void initBlueNote(Note *note);
void initGreenNote(Note *note); 

uint32_t animateNote(Note *note);


#endif
