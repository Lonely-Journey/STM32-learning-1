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
#include "at24cxx.h"
#include "stdio.h"
#include "lcd.h"

u8 cor_flay = 0;
u8 str[200];
u8 data = 0;
u8 flay = 0;

int main(void)
{		  
	Stm32_Clock_Init(9);//ϵͳʱ������
  NVIC_SetPriorityGrouping(5);  //7 - ��ռ���ȼ�������λ��
	SysTick_Init();	 	//��ʱ��ʼ��
  USART1_Init(9600);
  LCD_Init();
  LCD_Characters_String32(100,100,"��˼��",RED);
  
  
	while(1)
	{
  }
}




