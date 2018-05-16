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
    char name[CHAR_WIDTH];              // Item name
    char description1[CHAR_WIDTH];      // Item description
    char description2[CHAR_WIDTH];
    void (*function)(uint8_t);          // Function to execte
    uint8_t argument;                   // Argument to pass to function
} MENU_ITEM;


// Menu screen
typedef struct menu_screen_t {
    char title[CHAR_WIDTH];             // Menu screen title
    uint8_t number;                     // Number of options
    uint8_t height;                     // Height of each option
    MENU_ITEM options[CHAR_HEIGHT];     // List of options
    void (*backFunction)(uint8_t);      // Function to execute on "back"
    uint8_t argument;                   // Arg to pass to function
} MENU_SCREEN;


// ----------displayMenu----------
// Interactively display a menu
// Parameters:
//      MENU_SCREEN *menu: menu to display
void displayMenu(MENU_SCREEN *menu);


#endif
