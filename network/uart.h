/*
 * uart.c
 *
 * UART driver for the TM4C
 */

#ifndef UART_C
#define UART_C


#include "../tm4c123gh6pm.h"

 
// ----------uartInit----------
// Initialize UART
 void uartInit(void);


//------------uartWrite------------
// Output 8-bit to serial port
// Parameters:
//      uint8_t data: data to write to serial port
void uartWrite(uint8_t data);


//------------uartRead---------
// Read 1 byte from the serial port
// Parameters:
//      uint8_t *data: pointer to char to fill
// Returns:
//      uint8_t: 1 for success, 0 for failure
uint8_t uartRead(uint8_t* data);


#endif
