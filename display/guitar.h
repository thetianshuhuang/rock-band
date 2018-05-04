/*
 * guitar.h
 *
 * Graphics for the onscreen guitar
 */
 
#ifndef GUITAR_H
#define GUITAR_H

#include <stdint.h>
#include "../game/core.h"

#define COLOR_NORMAL 0xFFFF
#define COLOR_STARPOWER 0x0618

#define resolution 19
#define red 0x001F
#define yellow 0x07FF
#define blue 0xF800
#define green 0x07E0


extern uint32_t noteStates[4];


typedef struct {
    const uint8_t *x_path;
	const uint8_t *y_path;
    uint16_t stage;
    uint16_t color;
	uint8_t playCheck;
	uint16_t button;
} Note;

// --------drawGuitar--------
// Draw the main guitar
void drawGuitar(void);


// --------updatePickups--------
// Updates the pickup graphic to show if button is pressed or not
void updatePickups(uint16_t controller);

    
// --------createNotes--------
// Create note sprites.
// Parameters
//      uint16_t inputState: Input string, as specified by the song track
//          filetype. The first four bits are used to determine what notes
//          to create.
void createNotes(uint16_t controller);


// --------moveNotes--------
// Move all notes by one position.
void moveNotes(void);


// --------updateNotes--------
// Draw notes on the screen.
// Parameters:
//      uint16_t strumChange: change in strummer
//      enum guitarState: current state. Currently, NORMAL and STARPOWER only
// Returns:
//      int16_t: change in score due to this update
int16_t updateNote(uint16_t strumChange, enum guitar_state_t currentState);


// --------updateScore--------
// Display the score on the screen
// Parameters:
//      uint16_t score: score to display
void updateScore(uint16_t score);

#endif
