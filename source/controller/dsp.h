/*
 * dsp.h
 *
 * Basic strummer signal processing
 */

#ifndef DSP_H
#define DSP_H

#include <stdint.h>


// --------derivative--------
// Take derivative of an input signal
// Parameters:
//      uint16_t input: input datapoint
// Returns;
//      uint16_t: output change
uint16_t derivative(uint16_t input);

#endif
