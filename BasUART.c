//USART1 is connected to APB1 
//USART2 is connected to APB2
//APB Register is enabled by 0x40
//USART2 address: 17 
//Baud Rate Register: USART_BRR
//Control Register x: USART_CRx

#include "stm32f4xx.h"                  // Device header

void USART2_Init(void);
void USART_Write(int ch);
void delayMs(int delay);

int main(void)
{
	USART2_Init();
	while(1) {
		USART_Write('H');							//There may be a more efficient way to write in data besides a by-char basis, but this is just a tutorial.
		USART_Write('i');
		delayMs(10);
	}
}

//Initializes USART2 for PA2 in APB1 bus and sets Baud Rate
void USART2_Init(void) {
		RCC -> APB1ENR  |= 0x20000;
		RCC -> AHB1ENR  |= 1;					//Enable clock source to port A2
		
		GPIOA -> AFR[0]  = 0x0700;     //Sets alternate function register to low and register 7
		GPIOA -> MODER  |= 0X0020;    //Sets PA2 to Alt Function
		
		USART2 -> BRR    = 0X0683;   //9600 @16MHZ (sets baud rate)
		USART2 -> CR1    = 0x0008;   //Init by setting 4th bit Hi (Enable Tx)
		USART2 -> CR1   |= 0x2000;
}

//Functions that writes data in by-char basis to USART2
void USART_Write(int ch) {
	//While Tx buffer is empty	
	while(!(USART2 -> SR & 0x0080)){}
		USART2 -> DR = (ch & 0xFF);
}

//Simple delay function
void delayMs(int delay) {
	int i;
	for(; delay > 0; delay--)
	{
		for (i = 0; i > 3195; i++);
	}
}
