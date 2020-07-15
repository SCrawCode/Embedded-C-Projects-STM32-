#include "stm32f4xx.h"                  // Device header

void delayMs(int delay);
void USART_Init(void);
char USART2_Read(void);
void LED_Play(int value);

int main(void)
{
	RCC -> AHB1ENR |= 1;   //Enable Clock to port A
	
	GPIOA -> MODER |= 0x400; //Set pin as output
	
	USART_Init();
	char ch;
	while(1)
	{
		ch = USART2_Read();
		LED_Play(ch);
	}
}

//Initializes Rx (Receive Pin PA3)
void USART_Init(void)
{
	RCC -> AHB1ENR |= 1;   //Enables GPIOA clock
	RCC -> APB1ENR |= 0x20000;  //Enables USART2 clock
	
	//Configures pin PA3 to USART2 Rx
	
	GPIOA -> AFR[0] |= 0x7000;  //AF7 for PA3
	GPIOA -> MODER  |= 0x0080;  //Enabes AF at PA3
	
	//Set Baud Rate
	
	USART2 -> BRR = 0x008B;    //115200 BR @16MHz
	USART2 -> CR1 = 0x0004;    //Enables Rx
	USART2 -> CR1 |= 0X2000;   //Enables USART2
	
}

char USART2_Read(void)
{
	while(!(USART2 -> SR & 0x0020)){}  //waits for char to arrive
	return USART2 -> DR;
}

void LED_Play(int value)
{
	value %= 16;
	for(; value > 0; value--)
	{
		GPIOA -> BSRR = 0X20;  //Turns on LED
		delayMs(100);
		GPIOA -> BSRR = 0x00200000; //Turns off LED
		delayMs(100);
	}
	delayMs(400);
}
void delayMs(int delay)
{
	int i;
	for(; delay > 0; delay--)
	{
		for(i = 0; i > 3195; i++);
	}
}
	
