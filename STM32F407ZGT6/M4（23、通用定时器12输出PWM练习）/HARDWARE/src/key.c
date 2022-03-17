#include "stm32f4xx.h"   

static void delay_ms(u32 ms)
{
	u32 i = 168 / 4 * 1000 * ms;
	while(i)
	{
		i--;
	}
}

/*****************************************************
*��������  ����KEY��Ӧ��GPIO�ڽ��г�ʼ������
*������    ��KEY_Init
*��������  ��void
*��������ֵ��void
*����      ��
            KEY1  PA0    �ߵ�ƽ����
            KEY2  PE2    �͵�ƽ����
            KEY3  PE3    �͵�ƽ����
            KEY4  PE4    �͵�ƽ����
                   ����ģʽ
********************************************************/
void KEY_Init(void)
{
  //GPIOxʱ��ʹ��
  RCC->AHB1ENR |= (1<<0);
  RCC->AHB1ENR |= (1<<4);
  
  //�˿�ģʽ�Ĵ���
  GPIOA->MODER &= ~(3<<0);
  GPIOE->MODER &= ~((3<<2*2)|(3<<2*3)|(3<<2*4));
  
  //�˿�����/�����Ĵ���
  GPIOA->PUPDR &= ~(3<<0);
  GPIOE->PUPDR &= ~((3<<2*2)|(3<<2*3)|(3<<2*4));
}

/*****************************************************
*��������  ������ɨ�躯��
*������    ��KEY_Scan
*��������  ��void
*��������ֵ��u8
*����      ��
            KEY1  PA0    �ߵ�ƽ����
            KEY2  PE2    �͵�ƽ����
            KEY3  PE3    �͵�ƽ����
            KEY4  PE4    �͵�ƽ����
                   ����ģʽ
********************************************************/
u8 KEY_Scan(void)
{
  u8 temp = 0;
  static u8 key_flay = 1;
  
  if(((GPIOA->IDR & (1<<0))||!(GPIOE->IDR & (1<<2))||!(GPIOE->IDR & (1<<3))||!(GPIOE->IDR & (1<<4)))&& key_flay)
  {
    delay_ms(10);
    if((GPIOA->IDR & (1<<0))||!(GPIOE->IDR & (1<<2))||!(GPIOE->IDR & (1<<3))||!(GPIOE->IDR & (1<<4)))
    {
      key_flay = 0;
      if(GPIOA->IDR & (1<<0)) temp = 1;
      else if(!(GPIOE->IDR & (1<<2))) temp = 2;
      else if(!(GPIOE->IDR & (1<<3))) temp = 3;
      else if(!(GPIOE->IDR & (1<<4))) temp = 4;
    }
  }
  if(!key_flay && !(GPIOA->IDR & (1<<0))&&(GPIOE->IDR & (1<<2))&&(GPIOE->IDR & (1<<3))&&(GPIOE->IDR & (1<<4)))
  {
    key_flay = 1;
  }
  
  return temp;
}


