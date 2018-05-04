/*
 * menu_defs.c
 *
 * Menu definitions for Rock Band
 */

#include "menu_defs.h"
#include "menu.h"
#include "../graphics/util.h"
#include "../game/core.h"
#include "../game/songs.h"
#include "../graphics/splash.h"
#include "../display/ST7735.h"
#include "../controller/controller.h"
#include "../network/uart.h"


MENU_SCREEN mainMenu;
MENU_SCREEN songSelect1;
MENU_SCREEN songSelect2;
MENU_SCREEN instrumentSelect;

void song1(void) {
    initGame(0);
}
void song2(void) {
    initGame(1);
}
void song3(void) {
    initGame(2);
}
void song4(void) {
    initGame(3);
}
void song5(void) {
    initGame(4);
}
void song6(void) {
    initGame(5);
}
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
void selectNull(void) {
    selectInstrument(NULL);
    selectBack();
}
void songSelectMain(void) {displayMenu(&songSelect1);}
void instrumentSelectMenu(void) {displayMenu(&instrumentSelect);}
void showMainMenu(void) {displayMenu(&mainMenu);}
void startMultiplayer(void) {
    // set flag
    songSelectMain();
}
uint8_t data;
void joinMultiplayer(void) {
    // Show splash screen
    multiSplash();
    while(1) {
        // Check for back button
        if(controllerRead() & 0x2000) {
            showMainMenu();
            break;
        }
        // Wait for sync byte
        if((uartRead(&data) != 0) && ((data & 0xF0) == 0xA0)) {
            uartWrite(data);
            initGame(data & 0x0F);
            break;
        }
    }
}
void setDemo(void) {
    playerState.runMode = DEMO;
    showMainMenu();
}

MENU_SCREEN mainMenu = {
    "MAIN MENU", 5, 1,
    {
        {"Single Player", "", "", &songSelectMain},
        {"Multiplayer", "", "", &joinMultiplayer},
        {"Start Lobby", "", "", &startMultiplayer},
        {"Select Instrument", "", "", &instrumentSelectMenu},
        {"Enable Full Mode", "", "", &setDemo},
    },
    0
};


MENU_SCREEN instrumentSelect = {
    "SELECT INSTRUMENT", 4, 1,
    {
        {"No instrument", "", "", &selectNull},
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
    "SONG SELECT", 4, 3,
    {
        {"DROELOE", "zZz", "", &song4},
        {"Yeah Yeah Yeahs", "Heads Will Roll", "", &song5},
        {"Band of Horses", "The Funeral", "Y2KxHonest Remix", &song6},
        {"Previous", "", "", &lambda1},
    },
    &showMainMenu
};

