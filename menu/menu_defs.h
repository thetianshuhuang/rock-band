/*
 * menu_defs.h
 *
 * Menu definitions for Rock Band
 */

#ifndef MENU_DEFS_H
#define MENU_DEFS_H

#include "menu.h"


// Menu screen definitions
enum menus_t {MAIN_MENU, INSTRUMENT, SONG_1, SONG_2};
extern MENU_SCREEN menus[4];


// ----------showMenuByIndex----------
// Shortcut for showing menus by index
// Parameters
//      uint8_t menuIndex: index of menu to show (pass as menus_t)
void showMenuByIndex(uint8_t menuIndex);


#endif
