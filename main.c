/*
 *Insert a header here
 *
 */


#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "PLL.h"

#include "audio/driver.h"
#include "network/fifo.h"
#include "display/ff.h"
#include "controller/controller.h"
#include "game/core.h"
#include "menu/menu.h"
#include "menu/menu_defs.h"
#include "display/ST7735.h"
#include "display/splash.h"
#include "display/guitar.h"

// Game ID ifndef for testing
#ifndef GAME_ID
#define GAME_ID 0x42
#endif


int main() {
    
    // Initializations (audioInit must go before ST7735_InitR)
    PLL_Init(Bus80MHz);
    audioInit();
    ST7735_InitR(INITR_REDTAB);
    controllerInit();
    
    // Set rotation
    ST7735_SetRotation(2);

    // Show splash screen
    showSplash("splash.pi");
    // Write instructions
    ST7735_SetTextColor(0xFFFF);
    ST7735_SetCursor(3, 15);
    ST7735_OutString("Press Any Button");
    // Wait for input
    while((controllerRead() & 0xF000) == 0){};
    
    // Enter main loop
    while(1){
        displayMenu(&mainMenu);	 
        mainLoop();
    }
}

// ----------systick_Handler----------
void SysTick_Handler(void) {
    updateSong();
}
