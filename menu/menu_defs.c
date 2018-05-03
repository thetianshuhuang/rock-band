/*
 * menu_defs.c
 *
 * Menu definitions for Rock Band
 */

#include "menu_defs.h"
#include "menu.h"
#include "../game/core.h"
#include "../game/songs.h"
#include "../display/splash.h"
#include "../display/ST7735.h"
#include "../controller/controller.h"


MENU_SCREEN mainMenu;
MENU_SCREEN songSelect1;
MENU_SCREEN songSelect2;
MENU_SCREEN instrumentSelect;

void song1(void) {initGame(&rockYouLikeAHurricane);}
void song2(void) {initGame(&messageInABottle);}
void song3(void) {initGame(&wildWildLife);}
void song4(void) {initGame(&zZz);}
void song5(void) {initGame(&headsWillRoll);}
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
void joinMultiplayer(void) {
    showSplash("wait.pi");
    ST7735_SetCursor(3, 3);
    ST7735_SetTextColor(0x0000);
    ST7735_OutString("Waiting for Song");
    ST7735_SetCursor(3, 4);
    ST7735_OutString("   Selection    ");
    ST7735_SetTextColor(0xFFFF);
    drawSpecialChar(5, 151, 3, 0x07FF, 0);
    ST7735_SetCursor(3, 15);
    ST7735_OutString("back to main menu");
    ST7735_DrawFastHLine(14, 27, 101, 0x0000);
    ST7735_DrawFastHLine(14, 49, 101, 0x0000);
    ST7735_DrawFastVLine(14, 27, 22, 0x0000);
    ST7735_DrawFastVLine(115, 27, 22, 0x0000);
    while(1) {
        if(controllerRead() & 0x2000) {
            showMainMenu();
        }
        // Put UART RX here
        uint8_t uart_RX_flag = 0;
        if(uart_RX_flag != 0) {
            initGame(&rockYouLikeAHurricane);
        }
    };    
}

MENU_SCREEN mainMenu = {
    "MAIN MENU", 4, 1,
    {
        {"Single Player", "", "", &songSelectMain},
        {"Multiplayer", "", "", &joinMultiplayer},
        {"Start Lobby", "", "", &startMultiplayer},
        {"Select Instrument", "", "", &instrumentSelectMenu},
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
    "SONG SELECT", 3, 3,
    {
        {"DROELOE", "zZz", "", &song4},
        {"Yeah Yeah Yeahs", "Heads Will Roll", "", &song5},
        {"Previous", "", "", &lambda1},
    },
    &showMainMenu
};

