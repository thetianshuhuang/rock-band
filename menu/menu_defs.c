/*
 * menu_defs.c
 *
 * Menu definitions for Rock Band
 */

#include "menu_defs.h"
#include "menu.h"
#include "../game/core.h"


MENU_SCREEN mainMenu;
MENU_SCREEN songSelect1;
MENU_SCREEN songSelect2;
MENU_SCREEN instrumentSelect;

void song1(void) {initGame("rylah.bw");}
void song2(void) {initGame("miab.bw");}
void song3(void) {initGame("wwl.bw");}
void song4(void) {initGame("zzz.bw");}
void song5(void) {initGame("hwr.bw");}
void lambda2(void) {displayMenu(&songSelect2);}
void lambda1(void) {displayMenu(&songSelect1);}
void selectBack(void) {displayMenu(&mainMenu);}
void selectGuitar(void) {
    selectInstrument(GUITAR);
    selectBack();
}
void selectBass(void) {
    selectInstrument(BASS);
    selectBack();
}
void selectDrums(void) {
    selectInstrument(DRUMS);
    selectBack();
}
void songSelectMain(void) {displayMenu(&songSelect1);}
void instrumentSelectMenu(void) {displayMenu(&instrumentSelect);}
void showMainMenu(void) {displayMenu(&mainMenu);}


MENU_SCREEN mainMenu = {
    "MAIN MENU", 3, 1,
    {
        {"Single Player", "", "", &songSelectMain},
        {"Multiplayer", "", "", &songSelectMain},
        {"Select Instrument", "", "", &instrumentSelectMenu},
    },
    0
};


MENU_SCREEN instrumentSelect = {
    "SELECT INSTRUMENT", 3, 1,
    {
        {"Guitar", "", "", &selectGuitar},
        {"Bass", "", "", &selectBass},
        {"Drums", "", "", &selectDrums},
    },
    &showMainMenu
};


MENU_SCREEN songSelect1 = {
    "SONG SELECT", 4, 3,
    {
        {"The Scorpions", "Rock You Like A", "Hurricane", &song1},
        {"The Police", "Message in a", "bottle", &song2},
        {"Talking Heads", "Wild Wild Life", "", &song3},
        {"Next", "", "", &lambda2},
    },
    &showMainMenu
};

MENU_SCREEN songSelect2 = {
    "SONG SELECT", 3, 3,
    {
        {"DROELOE", "zZz", "", &song4},
        {"Yeah Yeah Yeahs", "Heads Will Roll", "", &song5},
        {"Previous", "", "", &lambda1},
    },
    &showMainMenu
};

