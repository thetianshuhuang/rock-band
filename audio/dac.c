/*
 * dac.c
 *
 * Configure PB.0-7 as an 8 bit dac (bit 0 is the least significant bit)
 */

#include "dac.h"

// ----------dacInit----------
// Initialize 8-bit DAC ports
void DACInit(void) {
    // Turn on port A
    SYSCTL_RCGCGPIO_R |= 0x02;
    __asm{NOP};
    __asm{NOP};
    // All pins are digital outputs
    GPIO_PORTB_AMSEL_R = 0x00; 
    GPIO_PORTB_PCTL_R = 0x00;
    GPIO_PORTB_DIR_R = 0xFF;
    GPIO_PORTB_AFSEL_R = 0x00;
    GPIO_PORTB_DEN_R = 0xFF;
}

// ----------dacOut----------
// output an 8-bit value to the DAC
// Parameters:
//      uint8_t data: value to write to the DAC (8-bit, 0-3.3v)
void DACOut(uint8_t data) {
    GPIO_PORTB_DATA_R = data;
}
