/*
 * menu_defs.c
 *
 * Menu definitions for Rock Band
 */

#include "menu_defs.h"
#include "menu.h"


MENU_SCREEN mainMenu = {
    "Main Menu", 2,
    {
        {"Single Player", 0, 0},
        {"Multiplayer", 0, 0},
    }
};

MENU_SCREEN songSelect = {
    "Song Select", 3,
    {
        {"Placeholder 1", 0, 0},
        {"Placeholder 2", 0, 1},
        {"Placeholder 3", 0, 2}
    }
};
