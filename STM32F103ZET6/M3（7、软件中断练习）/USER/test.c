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
  u8 key_flay;
	Stm32_Clock_Init(9);//ϵͳʱ������
  NVIC_SetPriorityGrouping(5);  //7 - ��ռ���ȼ�������λ��
	delay_init(72);	  	//��ʱ��ʼ��
  LED_Init();
  KEY_Init();
  EXTI5_Swier_Init();
  
	while(1)
	{
    key_flay = KEY_Scan();
    if(key_flay == 2)
    {
      EXTI->SWIER |= (1<<5);
    }
  }
}




