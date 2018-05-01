/*
 * guitar.h
 *
 * Graphics for the onscreen guitar
 */
 
#ifndef GUITAR_H
#define GUITAR_H

#include <stdint.h>

// ----------drawGuitar----------
// initialize guitar graphics
// Parameters
//      none
void drawGuitar(void);

void updatePickups(uint16_t controller);


#endif
