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
<<<<<<< HEAD
#include "display/splash.h"
#include "display/guitar.h"
=======
>>>>>>> parent of 9c6da3c... Committed main

// Game ID ifndef for testing
#ifndef GAME_ID
#define GAME_ID 0x42
#endif

uint16_t controller;
int main() {
	PLL_Init(Bus80MHz);
    ST7735_InitR(INITR_REDTAB);
    controllerInit();
    audioInit();
<<<<<<< HEAD
    displayMenu(&mainMenu);
    while(1){
			//GPIO_PORTF_DATA_R ^= 0x04;
      controller = controllerRead();
			updatePickups(controller);
    };
=======
    displayMenu(&songSelect1);
    // controller = controllerRead();
    // initGame("song.bw");
    while(1){};
>>>>>>> parent of 9c6da3c... Committed main
}

// ----------systick_Handler----------
void SysTick_Handler(void) {
    updateSong();
}
