//Accel lib header


#ifndef ACCEL_H
#define ACCEL_H

#include <stdint.h>

typedef struct{
	int16_t x;
	int16_t y;
	int16_t z;
  uint8_t enable;	
} Accel;

void initAccel(void);
void getSample(void);
uint8_t isStarpower(void);

#endif
