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
        splashStatus = f_open(&splashHandle, "spl.pi", FA_READ);
    } while(splashStatus != 0);
    
    uint16_t readPixel;
    for(uint8_t i = 0; i < 160; i++) {
        for(uint8_t j = 0; j < 100; j++) {
            splashStatus = f_read(&splashHandle, &readPixel, 2, &splashSuccess);
            ST7735_DrawPixel(j, i, readPixel);
            // ST7735_DrawPixel(j, i, 0x001F);
        }
    }
    
    splashStatus = f_close(&splashHandle);
}
