/*
 * splash.c
 *
 * Splash screen display routine
 */

#include "../controller/controller.h"
#include "../display/ST7735.h"
#include "../display/diskio.h"
#include "../display/ff.h"
#include "util.h"

// Status codes from the SD library
FRESULT splashStatus;
// FATFS object
static FATFS splashFS;
// not sure what this is
FIL splashHandle;
// not sure what this does either
UINT splashSuccess;

#include "../tm4c123gh6pm.h"


// --------showSplash--------
// Show the splash screen
void showSplash(char* image) {
    
    // Mount SD Card
    do {
        splashStatus = f_mount(&splashFS, "", 0);
    } while(splashStatus != 0);
    // Read file
    do {
        splashStatus = f_open(&splashHandle, image, FA_READ);
    } while(splashStatus != 0);
    // Show Image
    for(uint8_t i = 0; i < 160; i++) {
        uint16_t readPixels[128];
        do {
            splashStatus = f_read(&splashHandle, &readPixels, 256, &splashSuccess);
        } while(splashStatus != 0);
        for(uint8_t j = 0; j < 128; j++) {
            ST7735_DrawPixel(j, 159 - i, readPixels[j]);
        }
    }
    // Close file
    splashStatus = f_close(&splashHandle);
}


// --------menuSplash--------
// Show the main menu splash screen
void menuSplash(void) {
     // Show splash screen
    showSplash("splash.pi");
    // Write instructions
    ST7735_SetTextColor(0xFFFF);
    ST7735_SetCursor(3, 15);
    ST7735_OutString("Press Any Button");
    // Wait for input
    while((controllerRead() & 0xF000) == 0){};
}


// --------scoreSplash--------
// Show the song end score splash screen
void scoreSplash(uint16_t score) {
    // Show splash screen
    showSplash("back.pi");
    // Show display Text
    ST7735_SetTextColor(0xFFFF);
    ST7735_SetCursor(3, 2);
    ST7735_OutString("Your Score:");
    ST7735_SetCursor(3, 3);
    ST7735_OutUDec(score);
    ST7735_SetCursor(3, 4);
    // Wait for input
    while((controllerRead() & 0xF000) == 0){};
}


// --------multiplayerSplash--------
// Show the multiplayer splash screen
void multiSplash(void) {
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
}

