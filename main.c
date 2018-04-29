/*
 *Insert a header here
 *
 */

/************************************/
#define AUDIO_TEST
#define FOURTY
//#define TWENY
//#define ELEVEN
/************************************/

#define UART_H
#define NETWORK_H
#define FIFO_H
#define CONTROLLER_H

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "TExaS.h"
#include "display/diskio.h"
#include "display/ff.h"
#include "PLL.h"
#include "display/ST7735.h"

#ifdef AUDIO_TEST
#include "audio/dac.h"
uint32_t i;
static FATFS g_sFatFs;
FIL Handle,Handle2;
FRESULT MountFresult;
FRESULT Fresult;
unsigned char buffer[512];
#define MAXBLOCKS 100
uint8_t c;
UINT successfulreads;
const char inFilename[] = "song.txt";   // 8 characters or fewer
#endif

// Game ID ifndef for testing
#ifndef GAME_ID
#define GAME_ID 0x42
#endif
	
#ifndef AUDIO_TEST
int main() {
	
    
    
}
#endif

/************************************/
//MAKE SURE TO INIT CONTROLLER BEFORE SD!!!!!
/************************************/

#ifdef AUDIO_TEST
int main() {
	 TExaS_Init();    // bus clock at 80 MHz
   DACInit();
	 NVIC_ST_CTRL_R=0; // during the setup disable SysTick
	 #ifdef FOURTY
		NVIC_ST_RELOAD_R=0x00000716;
	 #endif
	 #ifdef TWENTY
		NVIC_ST_RELOAD_R=0x00000E2C;
	 #endif
	 #ifdef ELEVEN
		NVIC_ST_RELOAD_R=0x00001C58;
	 #endif
	 NVIC_ST_CURRENT_R=0; // any write to current clears it
	 NVIC_SYS_PRI3_R=(NVIC_SYS_PRI3_R & 0X00FFFFFF) | 0X20000000; // priority 1
	 NVIC_ST_CTRL_R = 0X0007; // enable systick with clock and interrups
   void EnableInterrupts(void);
	 MountFresult = f_mount(&g_sFatFs, "", 0);
   while(1)
		 ;
}
#endif

void SysTick_Handler(void){
		if(i < 5654016){
			Fresult = f_open(&Handle, inFilename, FA_READ);
			Fresult = f_read(&Handle, &c, 2, &successfulreads);
      Fresult = f_close(&Handle);
			DACOut(c);
			#ifdef FOURTY
			i++;
			#endif
			#ifdef TWENTY
			i+=2;
			#endif
			#ifdef ELEVEN
			i+=4;
			#endif
	  }
		else
			i=0;
	}
