#include "stm32f4xx.h"  
#include "stdio.h"
#include "nvic.h"
#include "string.h"
#include "led.h"
#include "w25q64.h"

static void delay_ms(u32 ms)
{
	u32 i = 168 / 4 * 1000 * ms;
	while(i)
	{
		i--;
	}
}

u32 temp = 1;

/******************************************************************
*��������  ������1���жϷ�����
*������    ��USART1_IRQHandler
*��������  ��void
*��������ֵ��void
*����      ��
*******************************************************************/
void USART1_IRQHandler(void)
{
  u8 data;
  static u32 addr = 0x0b0000;
  
  //�ж�����ʲô��ʽ�����ж�
  if(USART1->SR & (1<<5))
  {
    //ִ���ж�����
    data = USART1->DR;
    W25Q64_Page_Write(addr,1,&data);
    addr++;
    LED1_ON;
  }
  if(USART1->SR & (1<<4))
  {
    USART1->SR;
    USART1->DR;
    LED1_OFF;
  }
}

/******************************************************************
*��������  ������2���жϷ�����
*������    ��USART2_IRQHandler
*��������  ��void
*��������ֵ��void
*����      ��
*******************************************************************/
void USART2_IRQHandler(void)
{
  
  //�ж�����ʲô��ʽ�����ж�
  if(USART2->SR & (1<<5))
  {
    //ִ���ж�����
    data = USART2->DR;
    flay = 1;
  }
}

/******************************************************************
*��������  ���ⲿ�ж�1������
*������    ��EXTI0_IRQHandler
*��������  ��void
*��������ֵ��void
*����      ��
*******************************************************************/
void EXTI0_IRQHandler(void)
{
  if(EXTI->PR & (1<<0))
  {
    delay_ms(10);
    if((GPIOA->IDR & (1<<0)))
    {
      EXTI->PR |= (1<<0);
      GPIOF->ODR ^= (1<<6);
      GPIOF->ODR ^= (1<<9);
      GPIOF->ODR ^= (1<<10);
      GPIOC->ODR ^= (1<<0);
    }
  }
}

void SysTick_Handler(void)
{
  if(SysTick->CTRL & (1<<16))
  {
    //����ǰֵ�Ĵ�������   //���дһ�����ݽ���
    SysTick->VAL = 0xff;
    GPIOF->ODR ^= (1<<6);
  }
}
