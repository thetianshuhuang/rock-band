/*
 * controller.h
 *
 * I/O interfacing for the game controller
 * Analog: PE2
 * Digital: PE1, PD1-D3
 */
 

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../tm4c123gh6pm.h"
 
// ----------controllerInit----------
// Initialize controller
void controllerInit(void);

// ----------controllerRead----------
// Read the controller state
// Returns:
//      uint16_t: packed controller state
//          | button1 | button2 | button3 | button4| --strummer (12 bit) --|
uint16_t controllerRead(void);

#endif
