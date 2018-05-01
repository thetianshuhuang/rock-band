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

MENU_SCREEN songSelect1;
MENU_SCREEN songSelect2;

void song1(void) {initGame("rylah.bw");}
void song2(void) {initGame("miab.bw");}
void song3(void) {initGame("wwl.bw");}
void song4(void) {initGame("zzz.bw");}
void song5(void) {initGame("hwr.bw");}
void lambda2(void) {displayMenu(&songSelect2);}
void lambda1(void) {displayMenu(&songSelect1);}

MENU_SCREEN songSelect1 = {
    "SONG SELECT", 4,
    {
        {"The Scorpions", "Rock You Like A", "Hurricane", &song1},
        {"The Police", "Message in a", "bottle", &song2},
        {"Talking Heads", "Wild Wild Life", "", &song3},
        {"Next", "", "", &lambda2},
    }
};

MENU_SCREEN songSelect2 = {
    "SONG SELECT", 3,
    {
        {"DROELOE", "zZz", "", &song4},
        {"Yeah Yeah Yeahs", "Heads Will Roll", "", &song5},
        {"Previous", "", "", &lambda1},
    }
};
