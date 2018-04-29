/*
 * uart.h
 *
 * UART driver for the TM4C
 */

#include "uart.h"
#include "../tm4c123gh6pm.h"
 
// FIFO queues
FIFO_QUEUE rxFifo;
FIFO_QUEUE txFifo;
 
 
// ----------uartInit----------
// Initialize UART
 void uartInit(void) {

    // Turn on UART1
    SYSCTL_RCGCUART_R |= 0x0002;    // UART 1
    SYSCTL_RCGCGPIO_R |= 0x0004;    // Port C
    
    // Create fifo queues
    fifoInit(&rxFifo);
    fifoInit(&txFifo);
     
    // Disable UART during init
    UART1_CTL_R &= ~0x0001;
    
    // 115200 Baud, 8 bit word length
    UART1_IBRD_R = 43;
    UART1_FBRD_R = 26;
    // 8 bit length
    UART1_LCRH_R = 0x70;

    // Enable UART1 (RXE[9], TXE[8], UARTEN[0])
    UART1_CTL_R |= 0x0301;
   
    // Set up interrupts
    UART1_IM_R |= 0x10; // <---------------- add tx interrupt here
    // Interrupts at 1/2 full ([5,4,3] = 010)
    UART1_IFLS_R |= 0x10;
    UART1_IFLS_R &= ~0x28;
    // Priority
    NVIC_PRI1_R = (NVIC_PRI1_R & 0xFFFF00FF) | 0x00004000;
    NVIC_EN0_R = NVIC_EN0_INT6;
   
    // Enable alternate function
    GPIO_PORTC_AFSEL_R |= 0x30;     // PC4,5
    GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & 0xFF00FFFF) + 0x00220000; // ???
    GPIO_PORTC_DEN_R |= 0x30;       // Enable digital
    GPIO_PORTC_AMSEL_R &= ~0x30;    // Disable analog
}
 

// uartWrite

// uartRead

// ----------UART1_Handler----------
// Handler for UART1 interrupt
void UART1_Handler(void) {
    
    // Acknowledge RX interrupt
    UART1_ICR_R = 0x10;
    while((UART1_FR_R & 0x10) == 0) {
        // Empty RX hardware fifo
        fifoPut(&rxFifo, UART1_DR_R);
    }
    
    // Acknowledge TX interrupt
    // < add this block>
        
    // Update networking
    // < add this block>
    // - call updateClient
    // - write data to core game
}
