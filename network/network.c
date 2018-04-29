/*
 * network.c
 *
 * TM4C network driver
 * For use by the Serial Token Ring protocol
 *
 * Written by Tianshu Huang, April 2018 
 */
 
#include "network.h"
#include "uart.h"
#include "c_client.h"
#include "../tm4c123gh6pm.h"
#include "fifo.h"


// ----------getAddress----------
// Initialize the network
// Read the network address from PC6, PC7, PD6, PD7
// Returns:
//      uint8_t: address |0000|PC6|PC7|PD6|PD7|
uint8_t getAddress(void) {

    // Enable ports C and D
    SYSCTL_RCGCGPIO_R |= 0x0C;
    __asm{NOP};
    __asm{NOP};

    // PC6, PC7, PD6, PD7 digital in
    GPIO_PORTC_AMSEL_R &= ~0xC0;
    GPIO_PORTD_AMSEL_R &= ~0xC0;
    GPIO_PORTC_PUR_R &= 0xC0;
    GPIO_PORTD_PUR_R &= 0xC0;
    GPIO_PORTC_DIR_R &= ~0xC0;
    GPIO_PORTD_DIR_R &= ~0xC0;
    GPIO_PORTC_AFSEL_R &= ~0xC0;
    GPIO_PORTD_AFSEL_R &= ~0xC0;
    GPIO_PORTC_DEN_R |= 0xC0;
    GPIO_PORTC_DEN_R |= 0xC0;
    
    // Read address
    return(
        (GPIO_PORTC_DATA_R & 0xC0) >> 4 |
        (GPIO_PORTD_DATA_R & 0xC0) >> 6);
}


// ----------networkInit----------
// Initialize the network
// Gets the network address from PC6, PC7, PD6, PD7
void networkInit(void) {
    ipConfig(getAddress(), &uartWrite);
}


// ----------discoverPeers----------
// Run peer discovery
void discoverPeers(void) {
    uint8_t message[1];
    message[0] = GAME_ID;
    sendMessage(0x00, message, 1);
}
