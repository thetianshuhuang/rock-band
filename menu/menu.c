/*
 * menu.c
 * Menu display routines for the TM4C / ST7735R
 */

#include "menu.h"
#include "../controller/controller.h"
#include "../display/ST7735.h"
#include "../game/core.h"
#include "../graphics/splash.h"
#include "../graphics/util.h"

#define TEXT_WHITE  0xFFFF
#define TEXT_GREEN  0x07E0
#define TEXT_BLUE   0xF800
#define TEXT_YELLOW 0x07FF
#define TEXT_RED    0x001F


// ----------showInstructions----------
void showInstructions(void) {
    // Show instructions
    ST7735_SetCursor(2, 12);
    ST7735_OutString("Up");
    drawSpecialChar(0, 120, 1, TEXT_GREEN, 0x00);
    ST7735_SetCursor(2, 13);
    ST7735_OutString("Down");
    drawSpecialChar(0, 130, 2, TEXT_BLUE, 0x00);
    ST7735_SetCursor(2, 14);
    ST7735_OutString("Back");
    drawSpecialChar(0, 140, 3, TEXT_YELLOW, 0x00);
    ST7735_SetCursor(2, 15);
    ST7735_OutString("Select");
    drawSpecialChar(0, 150, 0, TEXT_RED, 0x00);
}


// ----------displayMenu----------
// Interactively display a menu
// Parameters:
//      MENU_SCREEN *menu: menu to display
void displayMenu(MENU_SCREEN *menu) {
    
    if(playerState.instrument == DRUMS) {
        showSplash("menu_d.pi");
    }
    else if(playerState.instrument == GUITAR || playerState.instrument == BASS) {
        showSplash("menu_g.pi");
    }
    else {
        ST7735_FillScreen(0);
    }
    
    // Title text
    ST7735_SetTextColor(TEXT_WHITE);
    ST7735_SetCursor(0, 0);
    ST7735_OutString(menu->title);
    // Options
    for(uint8_t i = 0; i < menu->number; i++) {
        ST7735_SetCursor(2, menu->height*i + 1);
        ST7735_OutString(menu->options[i].name);
        if(i + 1 < menu->number) {
            if(menu->height > 1) {
                ST7735_SetCursor(3, menu->height * i + 2);
                ST7735_OutString(menu->options[i].description1);
            }
            if(menu->height > 2) {
                ST7735_SetCursor(3, menu->height * i + 3);
                ST7735_OutString(menu->options[i].description2);
            }
            vLine(13, menu->height * 10 * i + 20, menu->height * 10 * i + (menu->height) * 10 + 8, TEXT_WHITE);
        }
    }    
    showInstructions();
    
    // Show arrow
    uint8_t inputLine = 0;
    drawSpecialChar(2, 10 * inputLine + 10, 0, TEXT_RED, 0x00);
    
    // Check for button press    
    uint16_t previousState;
    uint16_t currentState;
    uint32_t ghettoDebouncer = 100;
    while(1) {
        currentState = controllerRead();
        if((currentState & 0xF000 & ~previousState) && (ghettoDebouncer > 500000)) {
            ghettoDebouncer = 0;
            drawSpecialChar(2, menu->height * 10 * inputLine + 10, 5, TEXT_RED, 0x00);
            // Down
            if(currentState & 0x4000) {
                if(inputLine + 1 < menu->number) {
                    inputLine += 1;
                }
            }
            // Up
            else if(currentState & 0x8000) {
                if(inputLine > 0) {
                    inputLine -= 1;
                }
            }
            // Back (no back if null pointer passed)
            else if(currentState & 0x2000) {
                if(menu->backFunction != 0) {
                    menu->backFunction();
                    break;
                }
            }
            // Select
            else {
                (menu->options)[inputLine].function();
                break;
            }
            // Draw new arrow
            drawSpecialChar(2, menu->height * 10 * inputLine + 10, 0, TEXT_RED, 0x00);
        }
        previousState = currentState;
        ghettoDebouncer += 1;
    }
}
