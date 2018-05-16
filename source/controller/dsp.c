/*
 * dsp.c
 *
 * Basic strummer signal processing
 */


#include <stdint.h>
#include <stdlib.h>


uint16_t previousValue;
// --------derivative--------
// Take derivative of an input signal
// Parameters:
//      uint16_t input: input datapoint
// Returns;
//      uint16_t: output change
uint16_t derivative(uint16_t input) {
    uint16_t output = abs(input - previousValue);
    previousValue = input;
    return(output);
}
