#include "sys.h"
#include "stdio.h"

void USART1_IRQHandler(void)
{
  u8 data;
  //�ж��жϴ�������ʽ
  if(USART1->SR & (1<<5))
  {
    //�ж�Ҫִ�е�����
    data = USART1->DR;
    printf("�㷢�͵����ݣ�%c\r\n",data);
  }
}









