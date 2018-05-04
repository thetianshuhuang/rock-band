/*
 * menu.h
 * Menu display routines for the TM4C / ST7735R
 */

#ifndef MENU_H
#define MENU_H

#include <stdint.h>


#define CHAR_WIDTH 18
#define CHAR_HEIGHT 5


// Menu item
typedef struct menu_item_t {
    char name[CHAR_WIDTH];
    char description1[CHAR_WIDTH];
    char description2[CHAR_WIDTH];
    void (*function)(void);
} MENU_ITEM;


// Menu screen
typedef struct menu_screen_t {
    char title[CHAR_WIDTH];
    uint8_t number;
    uint8_t height;
    MENU_ITEM options[CHAR_HEIGHT];
    void (*backFunction)(void);
} MENU_SCREEN;


// ----------displayMenu----------
// Interactively display a menu
// Parameters:
//      MENU_SCREEN *menu: menu to display
void displayMenu(MENU_SCREEN *menu);


#endif
