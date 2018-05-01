/*
 * controller.c
 *
 * I/O interfacing for the game controller
 * Analog: PE2
 * Digital: PE1, PD1-D3
 */

#include "controller.h"
#include "../tm4c123gh6pm.h"


#define ADC_SAMPLE_RATE 200000
long StartCritical (void);
void EndCritical(long sr);

// ----------waitFourNops----------
// Helper function that just NOPs four times
void waitFourNops() {
    __asm{NOP};
    __asm{NOP};
    __asm{NOP};
    __asm{NOP};
}

// ----------controllerInit----------
// Initialize controller
void controllerInit(void) {
    // Turn on clocks for port D, E
    SYSCTL_RCGCGPIO_R |= 0x19;
    waitFourNops();
    // PE1, PD1-D3 digital
    GPIO_PORTD_AMSEL_R &= ~0x0E;
    GPIO_PORTD_DIR_R &= ~0x0E;
    GPIO_PORTD_AFSEL_R &= ~0x0E;
    GPIO_PORTD_DEN_R |= 0x0E;
    
    GPIO_PORTE_AMSEL_R &= ~0x02;
    GPIO_PORTE_DIR_R &= ~0x02;
    GPIO_PORTE_AFSEL_R &= ~0x02;
    GPIO_PORTE_DEN_R |= 0x02;
    
    // PE2 analog
    GPIO_PORTE_DIR_R |= 0x04;
    GPIO_PORTE_AFSEL_R |= 0x04;
    GPIO_PORTE_DEN_R &= ~0x04;
    GPIO_PORTE_AMSEL_R |= 0x04;
    
    // Configure ADC0
    SYSCTL_RCGCADC_R |= 0x01;   // Activate ADC0
    waitFourNops();
    waitFourNops();
    ADC0_PC_R = 0x07;           // 1M (80 clocks) conversion speed
    ADC0_SSPRI_R = 0x0123;      // set priorities
    ADC0_ACTSS_R &= ~0x08;      // disable sample sequencer 3
    ADC0_EMUX_R &= ~0xF000;     // seq3 is set to software trigger
    ADC0_SSMUX3_R &= ~0x0F;     // Clear SS3 field
    ADC0_SSMUX3_R = 0x01;       // set channel to Ain1 (PE2)
    ADC0_SSCTL3_R = 0x06;
    ADC0_SAC_R = 0x03;
    ADC0_IM_R &= ~0x08;         // disable ss3 interrupts
    ADC0_ACTSS_R |= 0x08;       // enable ss3
    
    // Configure timer0
    long sr = StartCritical();
    SYSCTL_RCGCTIMER_R |= 0x01;
    TIMER0_CTL_R = 0x00000000;          // Disable timer
    TIMER0_CFG_R = 0x00000000;          // 32-bit mode
    TIMER0_TAMR_R = 0x000000002;        // Periodic mode
    TIMER0_TAILR_R = ADC_SAMPLE_RATE;   // Set reload value
    TIMER0_TAPR_R = 0;                  // Use bus clock
    TIMER0_ICR_R = 0x000000001;         // Clear timeout flag
    TIMER0_IMR_R = 0x000000001;         // Enable interrupt
    NVIC_PRI4_R = (NVIC_PRI4_R & 0x00FFFFFF) | 0x80000000;
                                        // Set priority to the same as the main timer
    NVIC_EN0_R = 1<<19;                 // Enable IRQ 19 in NVIC
    EndCritical(sr);

    // PF0, PF4 inputs
    SYSCTL_RCGCGPIO_R |= 0x20;
    waitFourNops();
    GPIO_PORTF_DIR_R &= ~0x11;
    GPIO_PORTF_AFSEL_R &= ~0x11; 
    GPIO_PORTF_DEN_R |= 0x11;
    GPIO_PORTF_AMSEL_R &= ~0x11;
}


// Analog mailbox
uint16_t adcMailbox;
// ----------sampleAdc--------
// Take ADC sample and store to mailbox
void sampleAdc(void) {
    // Start sample
    ADC0_PSSI_R = 0x08;
    // Wait for conversion (~80 clocks)
    while((ADC0_RIS_R & 0x08) == 0){};
    // Set mailbox
    adcMailbox = ADC0_SSFIFO3_R & 0xFFF;
    // Clear sample complete flag
    ADC0_ISC_R = 0x08;
}


// ----------checkPause--------
// Check whether the game should be paused
// Returns:
//      1 for pause; 0 if no pause
uint8_t checkPause(void) {
    if((GPIO_PORTF_DATA_R & 0x11) != 0) {
        return(1);
    }
    return(0);
}


// ----------controllerRead----------
// Read the controller state
// Returns:
//      uint16_t: packed controller state
//          | button1 | button2 | button3 | button4| --strummer (12 bit) --|
uint16_t controllerRead(void) {

    return(
        ((GPIO_PORTD_DATA_R & 0x0E) << 11) |
        ((GPIO_PORTE_DATA_R & 0x02) << 14) |
        adcMailbox
    );
}
