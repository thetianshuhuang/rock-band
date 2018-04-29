/*
 * dac.h
 *
 * Configure PB.0-7 as an 8 bit dac (bit 0 is the least significant bit)
 */

#ifndef DAC_H
#define DAC_H

#include <stdint.h>
#include "../tm4c123gh6pm.h"

// ----------dacInit----------
// Initialize 8-bit DAC ports
void DACInit(void);

// ----------dacOut----------
// output an 8-bit value to the DAC
// Parameters:
//      uint8_t data: value to write to the DAC (8-bit, 0-3.3v)
void DACOut(uint8_t data);

#endif
