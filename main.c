/*
 *Insert a header here
 *
 */

/************************************/
#define AUDIO_TEST
/************************************/

#define UART_H
#define NETWORK_H
#define FIFO_H
#define CONTROLLER_H

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "TExaS.h"
#include "PLL.h"
#include "audio/driver.h"

// Game ID ifndef for testing
#ifndef GAME_ID
#define GAME_ID 0x42
#endif

const char* testSongName = "song.txt";
uint32_t songIndex;


int main() {
	PLL_Init(Bus80MHz);
    audioInit();
    startSong(testSongName, &songIndex);
    while(1){};
}


void SysTick_Handler(void) {
    updateSong();
}
