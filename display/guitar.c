/*
 * guitar.h
 *
 * Graphics for the onscreen guitar
 */

#include "guitar.h"
#include "../display/ST7735.h"
#include "../tm4c123gh6pm.h"
#include "../controller/controller.h"
#include "../game/core.h"
#include "guitar_data.h"



char *scorePrompt = "Score";

void drawGuitar(void){
	ST7735_FillScreen(0);
	ST7735_DrawString(0, 0, scorePrompt, 0xFFFF);
	ST7735_DrawString(0, 1, ">9000", 0xFFFF);
	ST7735_DrawBitmap(102, 157, RedPickup,16,14);
	ST7735_DrawBitmap(71, 157, YellowPickup,16,14);
	ST7735_DrawBitmap(42, 157, BluePickup,16,14);
	ST7735_DrawBitmap(11, 157, GreenPickup,16,14);
	ST7735_DrawLine(35, 0, 0, 160, 0xFFFF);
	ST7735_DrawLine(49, 0, 34, 160, 0xFFFF);
	ST7735_DrawFastVLine(64, 0, 160, 0xFFFF);
	ST7735_DrawLine(79, 0, 94, 160, 0xFFFF);
	ST7735_DrawLine(93, 0, 128, 160, 0xFFFF);
	
}

#define SDC_CS           (*((volatile uint32_t *)0x40024004))
#define SDC_CS_LOW       0           // CS controlled by software
#define SDC_CS_HIGH      0x01

// Updates the pickup graphic to show if button is pressed or not
void updatePickups(uint16_t controller)
{
  if(controller&0x8000)
		ST7735_DrawBitmap(11, 157, GreenPickupPressed,16,14);
	else
		ST7735_DrawBitmap(11, 157, GreenPickup,16,14);
	
	if(controller&0x4000)
		ST7735_DrawBitmap(42, 157, BluePickupPressed,16,14);
	else
		ST7735_DrawBitmap(42, 157, BluePickup,16,14);
	
	if(controller&0x2000)
		ST7735_DrawBitmap(71, 157, YellowPickupPressed,16,14);
	else
		ST7735_DrawBitmap(71, 157, YellowPickup,16,14);
	
	if(controller&0x1000)
		ST7735_DrawBitmap(102, 157, RedPickupPressed,16,14);
	else
		ST7735_DrawBitmap(102, 157, RedPickup,16,14);	
}

void initRedNote(Note *note)
{
	note->x_path = red_x_path; 
	note->y_path = red_y_path; 
    note->stage = 0;
    note->color = red;
	note->playCheck = 1;
	note->button = 0x1000;
}
void initYellowNote(Note *note)
{
	note->x_path = yellow_x_path; 
	note->y_path = yellow_y_path; 
    note->stage = 0;
    note->color = yellow;
	note->playCheck = 1;
	note->button = 0x2000;
}
void initBlueNote(Note *note)
{
	note->x_path = blue_x_path; 
	note->y_path = blue_y_path; 
    note->stage = 0;
    note->color = blue;
	note->playCheck = 1;
	note->button = 0x4000;
}
void initGreenNote(Note *note)
{
	note->x_path = green_x_path; 
	note->y_path = green_y_path; 
    note->stage = 0;
    note->color = green;
	note->playCheck = 1;
	note->button = 0x8000;
}

uint32_t animateNote(Note *note, GAME_STATE *playerState, uint16_t strumVelocity)
{
	if(note->stage >= resolution) {
		return 1;
    }
	if(note->stage != 0){
		ST7735_DrawCircle(note->x_path[note->stage - 1], note->y_path[note->stage - 1], 0);
	}
	if((note->stage >= 13) &&
       note->playCheck == 1 &&
       (controllerRead()&note->button) &&
       strumVelocity > 0x0200) {
		  note->playCheck = 0;
		  if(playerState->score < 50000)
			  playerState->score += 100;
	}
	ST7735_DrawCircle(note->x_path[note->stage], note->y_path[note->stage], note->color);
	note->stage++;
	return 0;
}

void updateScore(uint16_t score){
	ST7735_DrawString(0, 0, scorePrompt, 0xFFFF);
	ST7735_FillRect(0, 8, 29, 9, 0);
	ST7735_SetCursor(0, 1);
	ST7735_OutUDec(score);
}
