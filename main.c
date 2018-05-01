/*
 *Insert a header here
 *
 */

/************************************/
#define AUDIO_TEST
/************************************/

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

// Game ID ifndef for testing
#ifndef GAME_ID
#define GAME_ID 0x42
#endif

const char* testSongName = "song3.bw";
uint32_t songIndex = 0;


int main() {
	PLL_Init(Bus80MHz);
    ST7735_InitR(INITR_REDTAB);
    audioInit();
    controllerInit();
    // displayMenu(&songSelect);
    while(1){
        initGame("song.bw");
    };
}


void SysTick_Handler(void) {
    updateSong();
}
