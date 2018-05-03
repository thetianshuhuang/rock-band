/*
 * guitar.h
 *
 * Graphics for the onscreen guitar
 */

#include "guitar.h"
#include "../display/ST7735.h"
#include "../tm4c123gh6pm.h"
#include "../controller/controller.h"
#include "../controller/dsp.h"
#include "../game/core.h"
#include "guitar_data.h"


// Note states
uint32_t noteStates[4];


// --------drawGuitar--------
// Draw the main guitar
#define COLOR_WHITE 0xFFFF
#define PICKUP_Y 157
const uint8_t pickupCoords[4] = {102, 71, 42, 11};
void drawGuitar(void){
	ST7735_FillScreen(0);
    // Draw score
	ST7735_DrawString(0, 0, "Score", COLOR_WHITE);
	ST7735_DrawString(0, 1, ">9000", COLOR_WHITE);
    // Draw Pickups
    for(uint8_t i = 0; i < 4; i++) {
        ST7735_DrawBitmap(
            pickupCoords[i], PICKUP_Y, noteProfiles[i].pickupSprite, 16, 14);
    }
    // Draw lines
	ST7735_DrawLine(35, 0, 0, 160, COLOR_WHITE);
	ST7735_DrawLine(49, 0, 34, 160, COLOR_WHITE);
	ST7735_DrawFastVLine(64, 0, 160, COLOR_WHITE);
	ST7735_DrawLine(79, 0, 94, 160, COLOR_WHITE);
	ST7735_DrawLine(93, 0, 128, 160, COLOR_WHITE);
    // Clear note States
    for(uint8_t i = 0; i < 4; i++) {
        noteStates[i] = 0;
    }
}


// --------updatePickups--------
// Updates the pickup graphic to show if button is pressed or not
void updatePickups(uint16_t controller){
    for(uint8_t i = 0; i < 4; i++) {
        // First four bits show which buttons are pressed
        // Red = [13], Yellow = [14], Blue = [15], Green = [16], 
        // Pickup pressed
        if(controller & (0x1000 << i)) {
            ST7735_DrawBitmap(
                pickupCoords[i], PICKUP_Y, noteProfiles[i].pickupPressed, 16, 14);
        }
        // Pickup not pressed
        else {
            ST7735_DrawBitmap(
                pickupCoords[i], PICKUP_Y, noteProfiles[i].pickupSprite, 16, 14);
        }
    }
}


// --------createNotes--------
// Create note sprites.
// Parameters:
//      uint16_t inputState: Input string, as specified by the song track
//          filetype. The first four bits are used to determine what notes
//          to create.
void createNotes(uint16_t controller){
    for(uint8_t i = 0; i < 4; i++){
        if(controller & (0x1000 << i)){
            noteStates[i] |= 0x0001;
        }
    }
}


// --------moveNotes--------
// Move all notes by one position.
void moveNotes(void) {
    for(uint8_t i = 0; i < 4; i++) {
        noteStates[i] = noteStates[i] << 1;
    }
}


// lenience in seconds = (19 - LENIENCE) * 60  / 441
#define LENIENCE 18
// Minimum strum velocity
#define MIN_STRUM 0x0200

// --------updateNotes--------
// Draw notes on the screen.
// Parameters:
//      uint16_t strumChange: change in strummer
// Returns:
//      int16_t: change in score due to this update
int16_t updateNote(uint16_t strumChange)
{
    int16_t score = 0;
    // Cycle through possible positions
    for(uint8_t i = 0; i < 20; i++) {
        // Cycle through the four notes
        for(uint8_t j = 0; j < 4; j++) {
            // Check if note is present
            if((noteStates[j] && (0x0001 << i)) != 0) {
                // Clear previous note, except for position 0
                if(i != 0) {
                    ST7735_DrawCircle(
                        noteProfiles[j].xPath[i - 1],
                        noteProfiles[j].yPath[i - 1], 0);
                }
                // If the note is being played:
                if(strumChange > MIN_STRUM &&
                   ((controllerRead() & (0x0001 << i)) != 0) &&
                   i > LENIENCE) {
                    // Increment score by 100
                    score += 100;
                    // Erase note
                    noteStates[j] &= ~(0x0001 << i);
                }
                // Draw new note
                ST7735_DrawCircle(
                    noteProfiles[j].xPath[i],
                    noteProfiles[j].yPath[i],
                    noteProfiles[j].color);
                // Subtract points for missed note
                if(i == 20) {
                    score -= 20;
                    noteStates[j] &= ~(0x0001 << i);
                }
            }
        }
    }
    return(score);
}

void updateScore(uint16_t score){
	ST7735_DrawString(0, 0, "Score", COLOR_WHITE);
	ST7735_FillRect(0, 8, 29, 9, 0);
	ST7735_SetCursor(0, 1);
	ST7735_OutUDec(score);
}
