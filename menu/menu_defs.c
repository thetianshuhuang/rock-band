/*
 * menu_defs.c
 *
 * Menu definitions for Rock Band
 */

#include "menu_defs.h"
#include "menu.h"
#include "../game/core.h"


// ----------showMenuByIndex----------
// Shortcut for showing menus by index
// Parameters
//      uint8_t menuIndex: index of menu to show (pass as menus_t)
void showMenuByIndex(uint8_t menuIndex) {
    displayMenu(&menus[menuIndex]);
}


// Macros to return to main menu after changing settings
void demoScreen(uint8_t foo) {
    toggleDemo();
    showMenuByIndex(MAIN_MENU);
}
void instrumentScreen(uint8_t instrument) {
    selectInstrument(instrument);
    showMenuByIndex(MAIN_MENU);
}


// Menus
MENU_SCREEN menus[4] = {
    {
        "MAIN MENU", 5, 1,
        {
            {"Single Player", "", "", &showMenuByIndex, SONG_1},
            {"Multiplayer", "", "", &joinMultiplayer, 0},
            {"Start Lobby", "", "", &showMenuByIndex, SONG_1},
            {"Select Instrument", "", "", &showMenuByIndex, INSTRUMENT},
            {"Enable Full Mode", "", "", &demoScreen, 0},
        },
        0, 0
    }, 
    {
        "SELECT INSTRUMENT", 4, 1,
        {
            {"No instrument", "", "", &instrumentScreen, NULL},
            {"Guitar", "", "", &instrumentScreen, GUITAR},
            {"Bass", "", "", &instrumentScreen, BASS},
            {"Drums", "", "", &instrumentScreen, DRUMS},
        },
        &showMenuByIndex, MAIN_MENU
    },
    {
        "SONG SELECT", 4, 3,
        {
            {"The Scorpions", "Rock You Like A", "Hurricane", &initGame, RYLAH},
            {"The Police", "Message in a", "bottle", &initGame, MIAB},
            {"Talking Heads", "Wild Wild Life", "", &initGame, WWL},
            {"Next", "", "", &showMenuByIndex, SONG_2},
        },
        &showMenuByIndex, MAIN_MENU
    },
    {
        "SONG SELECT", 4, 3,
        {
            {"DROELOE", "zZz", "", &initGame, ZZZ},
            {"Yeah Yeah Yeahs", "Heads Will Roll", "", &initGame, HWR},
            {"Band of Horses", "The Funeral", "Y2KxHonest Remix", &initGame, TF},
            {"Previous", "", "", &showMenuByIndex, SONG_1},
        },
        &showMenuByIndex, MAIN_MENU
    }
};
