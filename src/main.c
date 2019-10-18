/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>
#include <serial.h>

// for 100 MHz STM32F4
#define COUNTS_PER_MICROSECOND 33
void _delay_us(int d)
{
	unsigned int count = d * COUNTS_PER_MICROSECOND - 2;
	__asm volatile(" mov r0, %[count]  \n\t"
			"1: subs r0, #1            \n\t"
			"   bhi 1b                 \n\t"
			:
			: [count] "r" (count)
			  : "r0");
}

void _delay_ms(int d)
{
	while (d--) _delay_us(999);
}

volatile int32_t pos1;
volatile int32_t pos2;
volatile int32_t pos3;
volatile int32_t pos4;

void SysTick_Handler(void)
{
	int16_t tm3   = 0;
	int16_t tm3dif   = 0;
	static int16_t tm3_d = 0;

	int16_t tm4   = 0;
	int16_t tm4dif   = 0;
	static int16_t tm4_d = 0;

	pos1 = TIM2->CNT;
	pos2 = TIM5->CNT;

	tm3 = TIM3->CNT;
	tm3dif = tm3-tm3_d;
	pos3 += tm3dif;
	tm3_d = tm3;

	tm4 = TIM4->CNT;
	tm4dif = tm4-tm4_d;
	pos4 += tm4dif;
	tm4_d = tm4;

}

void timinit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5|RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM3, ENABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7	| GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_TIM3);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);



	TIM_SetAutoreload (TIM5, 0xffffffff);
	TIM_SetAutoreload (TIM2, 0xffffffff);
	TIM_SetAutoreload (TIM4, 0xffff);
	TIM_SetAutoreload (TIM3, 0xffff);

	/* Configure the timer */
	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);

	/* TIM2/5 counter enable */
	TIM_Cmd(TIM5, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}

int main(void)
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																													{
	uint8_t i;
	char str[128];

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

	serial_init();

	timinit();

    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 2000);

    while(1)
   	{
   		sprintf(str,"%d %d %d %d\r\n",pos1,pos2,pos3,pos4);
	    printString(str);
	    _delay_ms(100);
	}
}
