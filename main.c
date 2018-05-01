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

Note testRed;
Note testYellow;
Note testBlue;
Note testGreen;

uint32_t a;
//
uint16_t controller;
int main() {
    PLL_Init(Bus80MHz);
    audioInit();
    ST7735_InitR(INITR_REDTAB);
    controllerInit();
    showSplash();
    while(1){};
    //displayMenu(&mainMenu);
	  //initGame("miab.bw");
	  //startSong("zzz.bw", &a);
	 
    drawGuitar();
    while(1){
			initRedNote(&testRed);
	    initYellowNote(&testYellow);
	    initBlueNote(&testBlue);
	    initGreenNote(&testGreen);
			for(int i = 0; i < resolution; i++)
	    { 
		    animateNote(&testRed);
			  animateNote(&testYellow);
			  animateNote(&testBlue);
			  animateNote(&testGreen);
				updatePickups(controllerRead());
			  Delayms(12);
	    }
    }
}

// ----------systick_Handler----------
void SysTick_Handler(void) {
    updateSong();
}
