/*
 * menu.h
 * Menu display routines for the TM4C / ST7735R
 */

#ifndef MENU_H
#define MENU_H

#include <stdint.h>


#define CHAR_WIDTH 30
#define CHAR_HEIGHT 4

// Menu item
typedef struct menu_item_t {
    char name[CHAR_WIDTH];
    void (*function)(void);
} MENU_ITEM;

// Menu screen
typedef struct menu_screen_t {
    char title[CHAR_WIDTH];
    uint8_t number;
    MENU_ITEM options[CHAR_HEIGHT];
} MENU_SCREEN;


// ----------displayMenu----------
// Interactively display a menu
// Parameters:
//      MENU_SCREEN *menu: menu to display
void displayMenu(MENU_SCREEN *menu);


#endif
