#include "sys.h"
#include "delay.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "usart.h"
#include "stdio.h" 
#include "nvic.h"
#include "string.h"
#include "exti.h"

u8 cor_flay = 0;
u8 str[200];
u8 data = 0;
u8 flay = 0;

int main(void)
{		 
	Stm32_Clock_Init(9);//ϵͳʱ������
  NVIC_SetPriorityGrouping(5);  //7 - ��ռ���ȼ�������λ��
	SysTick_Init();	 	//��ʱ��ʼ��
  LED_Init();
  
	while(1)
	{
    LED_ON();
    delay_ms(10000);
    LED_OFF();
    delay_ms(10000);
  }
}




