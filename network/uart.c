/*
 * uart.c
 *
 * UART driver for the TM4C
 */

#include "uart.h"
#include "../tm4c123gh6pm.h"
#include "../game/core.h"


// Register Bit Values
#define UART_TXFF   0x0020      // UART TX not full
#define UART_RXFF   0x0040      // UART RX not full
#define UART_TXRIS  0x0020      // UART TX interrupt flag
#define UART_RXRIS  0x0010      // UART RX interrupt flag
#define UART_TXIC   0x0020      // UART TX interrupt acknowledge
#define UART_RXIC   0x0010      // UART RX interrupt acknowledge
#define UART_TXIM   0x0020      // UART TX interrupt enable


// Game ID ifndef for testing
#ifndef GAME_ID
#define GAME_ID 0x42
#endif

 
// ----------uartInit----------
// Initialize UART
 void uartInit(void) {

    // Turn on UART1
    SYSCTL_RCGCUART_R |= 0x0002;    // UART 1
    SYSCTL_RCGCGPIO_R |= 0x0004;    // Port C
    __asm{
        NOP
        NOP
        NOP
        NOP
    };
     
    // Disable UART during init
    UART1_CTL_R &= ~0x0001;
    
    // 115200 Baud, 8 bit word length
    UART1_IBRD_R = 43;
    UART1_FBRD_R = 26;
    // 8 bit length
    UART1_LCRH_R = 0x70;

    // Enable UART1 (RXE[9], TXE[8], UARTEN[0])
    UART1_CTL_R |= 0x0301;
   
    // Enable alternate function
    GPIO_PORTC_AFSEL_R |= 0x30;     // PC4,5
    GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & 0xFF00FFFF) + 0x00220000; // ???
    GPIO_PORTC_DEN_R |= 0x30;       // Enable digital
    GPIO_PORTC_AMSEL_R &= ~0x30;    // Disable analog
}


//------------uartWrite------------
// Output 8-bit to serial port
// Parameters:
//      uint8_t data: data to write to serial port
void uartWrite(uint8_t data) {    
    while((UART1_FR_R & 0x20) != 0){};
    UART1_DR_R = data;
}


//------------uartRead---------
// Read 1 byte from the serial port
// Parameters:
//      uint8_t *data: pointer to char to fill
// Returns:
//      uint8_t: 1 for success, 0 for failure
uint8_t uartRead(uint8_t* data) {
    if((UART1_FR_R & 0x10) != 0) {
        return(0);
    }
    else {
        *data = UART1_DR_R;
        return(1);
    }
}
