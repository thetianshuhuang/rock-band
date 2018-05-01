/*
 * splash.c
 *
 * Splash screen display routine
 */
#include "ST7735.h"
#include "diskio.h"
#include "diskio.h"
#include "ff.h"

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
void showSplash(void) {
    do {
        splashStatus = f_mount(&splashFS, "", 0);
    } while(splashStatus != 0);
    do {
        splashStatus = f_open(&splashHandle, "splash.pi", FA_READ);
    } while(splashStatus != 0);
    
    for(uint8_t i = 0; i < 160; i++) {
        uint16_t readPixels[128];
        do {
            splashStatus = f_read(&splashHandle, &readPixels, 256, &splashSuccess);
        } while(splashStatus != 0);
        for(uint8_t j = 0; j < 128; j++) {
            ST7735_DrawPixel(j, 160 - i, readPixels[j]);
        }
    }
    
    splashStatus = f_close(&splashHandle);
}
