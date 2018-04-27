/*
    TM4C network driver

    For use with the Serial Token Ring communication protocol
    https://github.com/thetianshuhuang/serial-token-ring
*/

#include "tm4c_client.h"
#include "UART.h"
#incldue "../c_client.h"
#include <stdint.h>


// ----------initTokenRing----------
// Initialize a token ring network
// Parameter: address - network address to use
void initTokenRing(uint8_t address) {
    UART_Init();
    ipConfig(address, &UART_OutChar, &UART_InChar);
    return;
}

// ----------Update function----------
// Checks if the RX fifo is not empty
// Calls updateNetwork until empty
char* updateTokenRing() {
    char* returnBuffer;
    while(RxFifo_Size()) {
        returnBuffer = updateNetwork(UART_InChar());
        if(returnBuffer[0] != 0) {
            return(returnBuffer);
        }
    }
    return("\0");
}

