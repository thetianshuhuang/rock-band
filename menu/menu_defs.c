/*
 * menu_defs.c
 *
 * Menu definitions for Rock Band
 */

#include "menu_defs.h"
#include "menu.h"
#include "../game/core.h"


MENU_SCREEN mainMenu = {
    "MAIN MENU", 2,
    {
        {"Single Player", "placeholder", "placeholder", 0},
        {"Multiplayer", "placeholder", "placeholder", 0},
    }
};


void song1(void) {
    initGame("song.bw");
}

MENU_SCREEN songSelect = {
    "SONG SELECT", 3,
    {
        {"The Scorpions", "Rock You Like A", "Hurricane", &song1},
        {"The Police", "Message in a", "bottle", 0},
        {"Talking Heads", "Wild Wild Life", "", 0},
    }
};
