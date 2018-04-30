/*
 * menu.c
 * Menu display routines for the TM4C / ST7735R
 */

#include "menu.h"
#include "../controller/controller.h"
#include "../display/ST7735.h"

#define TEXT_WHITE  0xFFFF
#define TEXT_GREEN  0x07E0
#define TEXT_BLUE   0x001F
#define TEXT_YELLOW 0xFFE0
#define TEXT_RED    0xF800

const uint16_t menuColors[4] = {TEXT_GREEN, TEXT_BLUE, TEXT_YELLOW, TEXT_RED};

// ----------displayMenu----------
// Interactively display a menu
// Parameters:
//      MENU_SCREEN *menu: menu to display
void displayMenu(MENU_SCREEN *menu) {
    // Title text
    ST7735_SetTextColor(TEXT_WHITE);
    ST7735_FillScreen(0);
    ST7735_SetCursor(0, 0);
    ST7735_OutString(menu->title);
    // Options
    for(uint8_t i = 0; i < menu->number; i++) {
        ST7735_SetCursor(2, i + 1);
        ST7735_OutString(menu->options[i].name);
    }
    // Color select
    for(uint8_t i = 0; i < menu->number; i++) {
        ST7735_SetTextColor(menuColors[i]);
        ST7735_SetCursor(0, i + 1);
        ST7735_OutChar('>');
    }
    // Initialize null pointer
    void (*function)(void) = 0;
    // Check for button press    
    while(function == 0) {
        uint16_t input = controllerRead();
        for(uint8_t i = 0; i < menu->number; i++) {
            if((input & (0x1 << (16 - i))) != 0) {
                function = menu->options[i].function;
            }
        }
    }
    // Run function
    function();
}
