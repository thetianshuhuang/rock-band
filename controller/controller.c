/*
 * controller.c
 *
 * I/O interfacing for the game controller
 * Analog: PE2
 * Digital: PE1, PD1-D3
 */

#include "controller.h"
#include "../tm4c123gh6pm.h"


#define ADC_SAMPLE_RATE 1000000

// ----------controllerInit----------
// Initialize controller
void controllerInit(void) {
    // Turn on clocks for port A, E
    SYSCTL_RCGCGPIO_R |= 0x11;
    __asm{
			NOP
			NOP
			NOP
			NOP
		};
    // PE0, PE1, PD1-D3 digital
    GPIO_PORTD_AMSEL_R &= ~0x0E;
    GPIO_PORTD_DIR_R &= ~0x0E;
    GPIO_PORTD_AFSEL_R &= ~0x0E;
    GPIO_PORTD_DEN_R |= 0x0E;
    
    GPIO_PORTE_AMSEL_R &= ~0x03;
    GPIO_PORTE_DIR_R &= ~0x03;
    GPIO_PORTE_AFSEL_R &= ~0x03;
		GPIO_PORTE_AFSEL_R &= ~0x01;          // disable alt funct on PE0
    GPIO_PORTE_DR4R_R |= 0x01;            // 4mA drive on PE0
    GPIO_PORTE_PUR_R |= 0x01;             // enable weak pullup on PE0
    GPIO_PORTE_DEN_R |= 0x03;
    
    // PE2 analog
    GPIO_PORTE_DIR_R |= 0x04;
    GPIO_PORTE_AFSEL_R |= 0x04;
    GPIO_PORTE_DEN_R &= ~0x04;
    GPIO_PORTE_AMSEL_R |= 0x04;
    
    // Configure ADC0
    SYSCTL_RCGCADC_R |= 0x01;   // Activate ADC0
		__asm{
			NOP
			NOP
			NOP
			NOP
		};
    ADC0_PC_R = 0x07;           // 1M (80 clocks) conversion speed
    ADC0_SSPRI_R = 0x0123;      // set priorities
    ADC0_ACTSS_R &= ~0x08;      // disable sample sequencer 3
    ADC0_EMUX_R &= ~0xF000;     // seq3 is set to software trigger
    ADC0_SSMUX3_R &= ~0x0F;     // Clear SS3 field
    ADC0_SSMUX3_R = 0x05;       // set channel to Ain5 (PE2)
    ADC0_SSCTL3_R = 0x06;
    ADC0_SAC_R = 0x03;
    ADC0_IM_R &= ~0x08;         // disable ss3 interrupts
    ADC0_ACTSS_R |= 0x08;       // enable ss3
    
    // Configure timer0
    SYSCTL_RCGCTIMER_R |= 0x01;
    TIMER0_CTL_R = 0x00000000;          // Disable timer
    TIMER0_CFG_R = 0x00000000;          // 32-bit mode
    TIMER0_TAMR_R = 0x000000002;        // Periodic mode
    TIMER0_TAILR_R = ADC_SAMPLE_RATE;   // Set reload value
    TIMER0_TAPR_R = 0;                  // Use bus clock
    TIMER0_ICR_R = 0x000000001;         // Clear timeout flag
    TIMER0_IMR_R = 0x000000001;         // Enable interrupt
    NVIC_PRI4_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x40000000;
                                        // Set priority to the same as the main timer
    NVIC_EN0_R = 1<<19;                 // Enable IRQ 19 in NVIC
    TIMER0_CTL_R = 0x00000001;          // Enable timer
}


// Analog mailbox
uint16_t adcMailbox;

// ----------Timer0A_Handler----------
// Timer handler for ADC sampling
void Timer0A_Handler(void) {
    // Clear interrupt
    TIMER0_ICR_R = TIMER_ICR_TATOCINT;
    // Start sample
    ADC0_PSSI_R = 0x08;
    // Wait for conversion (~80 clocks)
    while((ADC0_RIS_R & 0x08) == 0){};
    // Set mailbox
    adcMailbox = ADC0_SSFIFO3_R & 0xFFF;
    // Clear sample complete flag
    ADC0_ISC_R = 0x08;    
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
