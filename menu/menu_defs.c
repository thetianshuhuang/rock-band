/*
 * menu_defs.c
 *
 * Menu definitions for Rock Band
 */

#include "menu_defs.h"
#include "menu.h"
#include "../game/core.h"


MENU_SCREEN mainMenu = {
    "Main Menu", 2,
    {
        {"Single Player", 0},
        {"Multiplayer", 0},
    }
};


void song1(void) {
    initGame("song.bw");
}

MENU_SCREEN songSelect = {
    "Song Select", 3,
    {
        {"Rock You Like[...]", &song1},
        {"Placeholder 2", 0},
        {"Placeholder 3", 0}
    }
};
