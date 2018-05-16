/*
 * controller.h
 *
 * I/O interfacing for the game controller
 * Analog: PE2
 * Digital: PE1, PD1-D3
 */
 

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>

 
// ----------controllerInit----------
// Initialize controller
void controllerInit(void);


// ----------sampleAdc--------
// Take ADC sample and store to mailbox
void sampleAdc(void);


// ----------checkPause--------
// Check whether the game should be paused
// Returns:
//      1 for pause; 0 if no pause
uint8_t checkPause(void);


// ----------controllerRead----------
// Read the controller state
// Returns:
//      uint16_t: packed controller state
//          | button1 | button2 | button3 | button4| --strummer (12 bit) --|
uint16_t controllerRead(void);

#endif
