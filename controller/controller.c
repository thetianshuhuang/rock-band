/*
 * controller.c
 *
 * I/O interfacing for the game controller
 * Analog: PE2
 * Digital: PE1, PD1-D3
 */
 
 #include "controller.h"


// ----------controllerInit----------
// Initialize controller
void controllerInit(void) {
    // Turn on clocks for port A, E
    SYSCTL_RCGCGPIO_R |= 0x11;
    __asm{NOP};
    __asm{NOP};
    // PE1, PD1-D3 digital
    GPIO_PORTD_PCTL_R = ???
    GPIO_PORTD_AMSEL_R &= ~0x0E;
    GPIO_PORTD_DIR_R &= ~0x0E;
    GPIO_PORTD_AFSEL_R &= ~0x0E;
    GPIO_PORTD_DEN_R |= 0x0E;
    
    GPIO_PORTE_PCTL_R = ???
    GPIO_PORTE_AMSEL_R &= ~0x02;
    GPIO_PORTE_DIR_R &= ~0x02;
    GPIO_PORTE_AFSEL_R &= ~0x02;
    GPIO_PORTE_DEN_R |= 0x02;
    
    // PE2 analog
    GPIO_PORTE_DIR_R |= 0x04;
    GPIO_PORTE_AFSEL_R |= 0x04;
    GPIO_PORTE_DEN_R &= ~0x04;
    GPIO_PORTE_AMSEL_R |= 0x04;
    
    // IDK WHAT ANY OF THIS DOES
    ADC0_PC_R = 0x01;               // configure 125kHz ADC conversion speed
    ADC0_SSPRI_R = 0x0123;          // set priorities
    ADC0_ACTSS_R &= ~0x08;        // disable sample sequencer 3
    ADC0_EMUX_R &= ~0xF000;         // seq3 is set to software trigger
    ADC0_SSMUX3_R &= ~0x0F;
    ADC0_SSMUX3_R |= 0x05;          // set channel to Ain5 (PD2)
    ADC0_SSCTL3_R = 0x06;
    ADC0_SAC_R = 0x03;
    ADC0_IM_R &= ~0x08;             // disable ss3 interrupts
    ADC0_ACTSS_R |= 0x08;           // enable ss3
}


// ----------controllerRead----------
// Read the controller state
// Returns:
//      uint16_t: packed controller state
//          | button1 | button2 | button3 | button4| --strummer (12 bit) --|
uint16_t controllerRead(void) {
    uint16_t output;
    output = (GPIO_PORTD_DATA_R & 0x0E) << 11;
    output |= (GPIO_PORTE_DATA_R & 0x02) << 14;
    output |= < some sort of ADC read, idk how interrupts should be structured yet>
    return(output)
}
