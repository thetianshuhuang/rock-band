// I2C0SCL connected to PE4 
// I2C0SDA connected to PE5
// SCL and SDA lines pulled to +3.3 V with 10 k resistors (part of breakout module)

#include "accel.h"
#include <stdint.h>
#include "I2C0.h"

int8_t address = 0x18;
//int8_t address = 0x0C;

// For debug purposes, this program may peek at the I2C0 Master
// Control/Status Register to try to provide a more meaningful
// diagnostic message in the event of an error.  The rest of the
// interface with the I2C hardware occurs through the functions
// in I2C0.c.
#define I2C0_MASTER_MCS_R       (*((volatile unsigned long *)0x40020004))
	
Accel *starpower;
uint16_t divider = 16380;

int16_t x;
int16_t y;
int16_t z;
	
void initAccel(void){
	I2C_Init();
  I2C_Send1(address, 0x0F);                 
  if(I2C_Recv(address) == 0x33){
    ;//USE ACCEL STAR POWER
		starpower->x = 0;
		starpower->y = 0;
		starpower->z = 0;
		starpower->enable = 1;
	}
	else
		starpower->enable = 0;
}

void getSample(void){
  I2C_Send1(address, 0x28|0x80);
	starpower->x = (int16_t)I2C_Recv2(address);
	starpower->x |= (I2C_Recv2(address) << 8);
	starpower->y = (int16_t)I2C_Recv2(address);
	starpower->y |= (I2C_Recv2(address) << 8);
	starpower->z = (int16_t)I2C_Recv2(address);
	starpower->z |= (I2C_Recv2(address) << 8);
}

uint8_t isStarpower(){
	if(starpower->enable == 0)
		return 1;
	uint8_t state;
	getSample();
	if(abs(starpower->x) > abs(starpower->y))
		state = 1;
	return state;
}
