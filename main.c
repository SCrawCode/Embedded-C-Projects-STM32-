// LED = PA5(D13)
// Clock access of AHB1
// RCC -> ABH1ENR 
// GPIOx_MODRER = Direction Register
// GPIOx_ODR = Data Register

#include "stm32f4xx.h"      //Device Header


void delayMs(int delay);

int main(void)
{
	RCC -> AHB1ENR |= 1;         // enable GPIOA clock
	
	GPIOA -> MODER |= 0x400;   //Sets indexed pin (PA5) to 01 ( 0100 0000 0000 = 0x400h )
	
	while(1) {
		
		
		GPIOA -> ODR |= 0x20;    // 0x20 = 0010 0000 (Wrote to 5th bit of register)
		delayMs(1000);
		GPIOA -> ODR  &= ~0x20;
		delayMs(1000);
	}
}
//Taking into account 16MHz system lock

void delayMs(volatile int delay)
{
volatile int i;
	
	for (; delay > 0; delay--) {
			for(i = 0; i < 3195; i++);
	}
}

