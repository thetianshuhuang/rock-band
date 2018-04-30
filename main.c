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

// Game ID ifndef for testing
#ifndef GAME_ID
#define GAME_ID 0x42
#endif

const char* testSongName = "song.txt";
uint32_t songIndex = 0;


int main() {
	PLL_Init(Bus80MHz);
    audioInit();
    startSong(testSongName, &songIndex);
    while(1){
        sdRead();
    };
}


void SysTick_Handler(void) {
    updateSong();
}
