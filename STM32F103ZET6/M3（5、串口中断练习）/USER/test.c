#include "sys.h"
#include "delay.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "usart.h"
#include "stdio.h" 
#include "nvic.h"

int main(void)
{				 
	Stm32_Clock_Init(9);//ϵͳʱ������
  NVIC_SetPriorityGrouping(5);  //7 - ��ռ���ȼ�������λ��
	delay_init(72);	  	//��ʱ��ʼ��
  LED_Init();
  BEEP_Init();
  KEY_Init();
  USART1_Init(9600);
  
	while(1)
	{
    LED_Flash1();                                                                                                                                                                                                        
	}	 
}




