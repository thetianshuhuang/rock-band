/*
 * network.h
 *
 * TM4C network driver
 * For use by the Serial Token Ring protocol
 *
 * Written by Tianshu Huang, April 2018 
 */
 
#ifndef NETWORK_H
#define NETWORK_H
 
#include "../serial-token-ring/C/c_client.h"
#include "../tm4c123gh6pm.h"
#include "fifo.h"
#include "uart.h"

#define GAME_ID 0x42


// ----------networkInit----------
// Initialize the network
// Gets the network address from PC6, PC7, PD6, PD7
void networkInit(void);


uint8_t peers[16];
// ----------discoverPeers----------
// Run peer discovery
void discoverPeers(void);


#endif
 