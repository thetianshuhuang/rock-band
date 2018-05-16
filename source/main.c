/*
 * ROCK BAND
 * EE319k Final Project
 *
 * By Quinn Buoy and Tianshu Huang
 * May 2018
 *
 * FEATURES
 * - 44.1kHz, 8 bit audio
 * - ST7735R display
 * - Audio and tracks via SD read
 * - inifinitely many songs supported, just by expanding the menu
 * - Full resolution (128x160) splash screens
 *
 * DEPENDENCIES
 * - tm4c123gh6p.h (tm4c hardware register definition file)
 * - PLL.h (tm4c PLL; used for 80mHz clock)
 * - FATFS; ST7735.h and diskio.h from Valvanoware (modified)
 *
 * LIBRARIES AND MODULES
 * - Network: token network implementation, modified from Serial Token Ring
 * - Audio: SD read and DAC out; 8 bit x 44.1kHz (44.1kBps bitrate)
 * - Controller: Four digital and one analog, and derivative routines for the
 *      strummer
 * - Game: Core game control
 * - Display: SD drivers and display routines
 * - Menu: Generalized menu library using function pointers
 * - Graphics: Display routines for the guitar, splash screen, and misc utilities
 *
 * FILE TYPES
 * - Packed Image (.pi): packed 5-6-5 GBR 16-bit image, uncompressed, scanning
 *      starting from bottom left, across, then up
 * - Byte wave file (.bw): raw audio file, bit-depth of 8, 44.1kHz
 * - Rock Band Track (.rb): 16-bit array.
 *      | R | Y | B | G | Reserved | Reserved | -- (10) Tick -- |
 *      R, Y, B, G indicated whether each drum should be hit (1) at that note
 *      or not (0).
 *      Tick indicates the number of updates (441 updates/s or 100 audio ticks/update)
 *      before the next note.
 */

// Library Includes
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "PLL.h"

// Module Includes
#include "audio/driver.h"
#include "controller/controller.h"
#include "game/core.h"
#include "menu/menu_defs.h"
#include "display/ST7735.h"
#include "graphics/splash.h"
#include "network/uart.h"


//
// GAME HARDWARE SETTINGS
//
void gameInit(void)
{
    // Initializations (audioInit must go before ST7735_InitR)
    PLL_Init(Bus80MHz);
    audioInit();
    ST7735_InitR(INITR_REDTAB);
    controllerInit();
    uartInit();

    // Set rotation (180 degrees)
    ST7735_SetRotation(2);
}


//
// MAIN LOOP
//
int main()
{
    // Initialize hardware
    gameInit();

    // Show splash screen
    menuSplash();

    // Enter main loop
    while(1){
        showMenuByIndex(MAIN_MENU);
        mainLoop();
    }
}

