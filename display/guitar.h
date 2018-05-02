/*
 * guitar.h
 *
 * Graphics for the onscreen guitar
 */
 
#ifndef GUITAR_H
#define GUITAR_H

#include <stdint.h>
#include "../game/core.h"

#define resolution 19
#define red 0x001F
#define yellow 0x07FF
#define blue 0xF800
#define green 0x07E0

typedef struct {
    const uint8_t *x_path;
	const uint8_t *y_path;
    uint16_t stage;
    uint16_t color;
	uint8_t playCheck;
	uint16_t button;
} Note;

// ----------drawGuitar----------
// initialize guitar graphics
// Parameters:
//      none
void drawGuitar(void);

void updatePickups(uint16_t controller);

void initRedNote(Note *note);
void initYellowNote(Note *note);
void initBlueNote(Note *note);
void initGreenNote(Note *note); 

uint32_t animateNote(Note *note, GAME_STATE *playerState, uint16_t strumVelocity);

void updateScore(uint16_t score);

#endif
