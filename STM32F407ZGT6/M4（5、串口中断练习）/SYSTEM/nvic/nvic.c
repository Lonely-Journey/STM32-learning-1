#include "stm32f4xx.h"  
#include "stdio.h"
#include "nvic.h"


void USART1_IRQHandler(void)
{
  static u8 i = 0;
  static u8 str[200];
  
  //�ж�����ʲô��ʽ�����ж�
  if(USART1->SR & (1<<5))
  {
    //ִ���ж�����
    str[i] = USART1->DR;
    i++;
  }
  if(USART1->SR & (1<<4))
  {
    USART1->SR;
    USART1->DR;
    
    str[i] = '\0';
    printf("�㷢�͵������ǣ�%s\r\n",str);
    i = 0;
  }
}






