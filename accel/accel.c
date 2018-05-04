// I2C0SCL connected to PE4 
// I2C0SDA connected to PE5
// SCL and SDA lines pulled to +3.3 V with 10 k resistors (part of breakout module)
#include <stdint.h>
#include "I2C0.h"
#include "../PLL.h"

int8_t address = 0x18;
//int8_t address = 0x0C;

// For debug purposes, this program may peek at the I2C0 Master
// Control/Status Register to try to provide a more meaningful
// diagnostic message in the event of an error.  The rest of the
// interface with the I2C hardware occurs through the functions
// in I2C0.c.
#define I2C0_MASTER_MCS_R       (*((volatile unsigned long *)0x40020004))
	
void initAccel(void){
	I2C_Init();
  I2C_Send1(address, 1);                  // use command 1 to set pointer to config (Figure 7.XX chapter7-10-1.ulb)
  if(I2C_Recv2(address) == 0x60A0){          // expected 0x60A0 as power-on default (Figure 7.XX chapter7-10-2.ulb)
    ;
		
	 uint8_t deviceid = readRegister8(LIS3DH_REG_WHOAMI);
  if (deviceid != 0x33)
  {
    /* No LIS3DH detected ... return false */
    //Serial.println(deviceid, HEX);
    return false;
  }
	
	
/*
    UART_OutString("\r\nTest Passed\r\n");
  }
  else{
    if(I2C0_MASTER_MCS_R&0x02){
      UART_OutString("\r\nNo Acknowledge\r\n");
    }
    else{
      UART_OutString("\r\nTest Failed\r\n");
    }
	*/
	}
}

int main(void){
	
	I2C_Init();
                                          // write commands to 0x48 (ADDR to ground)
  I2C_Send1(address, 1);                  // use command 1 to set pointer to config (Figure 7.XX chapter7-10-1.ulb)
                                          // read from 0x48 to get data
  if(I2C_Recv2(address) == 0x60A0){          // expected 0x60A0 as power-on default (Figure 7.XX chapter7-10-2.ulb)
    //UART_OutString("\r\nTest Passed\r\n");
  }
  else{
    if(I2C0_MASTER_MCS_R&0x02){
      UART_OutString("\r\nNo Acknowledge\r\n");
    }
    else{
      UART_OutString("\r\nTest Failed\r\n");
    }
	
	
	
	
	
	
	
}