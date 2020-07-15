#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
//Program is meant to send and receive data to specified pins via UART protocols

void USART2_Init(void);



int main(void)
{
	int n;
	char str[100];
	USART2_Init();
	printf("Hello World\n");
	fprintf(stdout," stdout test\r\n");
	fprintf(stderr," stderr test\r\n");
	
	while(1)
	{
		printf("Enter Age: ");
		scanf("%d", &n);
		printf("Your age is: %d\r\n", n);
		printf("Enter first name: ");
		gets(str);
		printf("What's up ");
		puts(str);
		printf("\r\n");
	}
}

void USART2_Init(void)
{
	RCC -> AHB1ENR |= 1;
	RCC -> APB1ENR |= 0x200000;
	
	
	GPIOA -> AFR[0] |= 0x7000;
	GPIOA -> MODER |= 0x00A0;   //Enable Alt function for PA2, PA3
	
	USART2 -> BRR = 0x0683;    //BR = 9600 @16MHz
	USART2 -> CR1 = 0x000C;    //Enable Tx & Rx
	USART2 -> CR1 |= 0x2000;
}

int USART2_Write(int ch)
{
	while(!(USART2 -> SR & 0x0080)){}  //Check Tx buffer state
	USART2 -> DR = (ch & 0xFF);
		return ch;
}

int USART2_Read(void)
{
	while(!(USART2 -> SR & 0x0020)){}
		return USART2 -> DR;		
}

struct _FILE{int handle;};
 FILE __stdin = {0};
 FILE __stdout = {1};
 FILE __stderr = {2};	

 
 int fgetc(FILE *f)
 {
	int c;
		c = USART2_Read();
	 if( c == '\r' ) {
		 USART2_Write(c);
		 c = '\n';
	 }
	 USART2_Write(c);
	 
	 return c;
	 
 }
 
 int fputc(int c, FILE *f)
 {
	return USART2_Write(c); 
 }
 