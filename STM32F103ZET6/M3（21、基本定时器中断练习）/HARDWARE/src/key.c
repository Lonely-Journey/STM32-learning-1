#include "sys.h"
#include "delay.h"

/*****************************************************
*��������  ����KEY��Ӧ��GPIO�ڽ��г�ʼ������
*������    ��KEY_Init
*��������  ��void
*��������ֵ��void
*����      ��
             KEY0     PE4
             KEY1     PE3
             KEY_UP   PA0
             KEY0��KEY1 �͵�ƽ���£��ߵ�ƽ̧��
             KEY_UP     �ߵ�ƽ���£��͵�ƽ̧��
                                  -------------���ģʽ
********************************************************/
void KEY_Init(void)
{
  //GPIOxʱ��ʹ��
  RCC->APB2ENR |= ((1<<2)|(1<<6));
  
  //�˿����üĴ���
  GPIOA->CRL &= ~(0xf<<4*0);
  GPIOA->CRL |= (8<<4*0);
  
  GPIOE->CRL &= ~((0xf<<4*3)|(0xf<<4*4));
  GPIOE->CRL |= ((8<<4*3)|(8<<4*4));
  
  //�˿�����Ĵ���  ���øߵ�ƽ����ʽ���� ���õ͵�ƽ����ʽ����
  GPIOA->ODR &= ~(1<<0);
  GPIOE->ODR |= ((1<<3)|(1<<4));
}

/*****************************************************
*��������  ������ɨ�躯��
*������    ��KEY_Scan
*��������  ��void
*��������ֵ��u8
*����      ��
             KEY0     PE4
             KEY1     PE3
             KEY_UP   PA0
             KEY0��KEY1 �͵�ƽ���£��ߵ�ƽ̧��
             KEY_UP     �ߵ�ƽ���£��͵�ƽ̧��
                                  -------------���ģʽ
********************************************************/
u8 KEY_Scan(void)
{
  u8 temp = 0;
  static u8 key_flay = 1;
  if(key_flay && ((GPIOA->IDR & (1<<0))||!(GPIOE->IDR & (1<<3))||!(GPIOE->IDR & (1<<4))))
  {
    delay_ms(10);
    if((GPIOA->IDR & (1<<0))||!(GPIOE->IDR & (1<<3))||!(GPIOE->IDR & (1<<4)))
    {
      key_flay = 0;
      if(!(GPIOE->IDR & (1<<4)))     temp = 1;
      else if(!(GPIOE->IDR & (1<<3))) temp = 2;
      else if(GPIOA->IDR & (1<<0))    temp = 3;
    }
  }
  if(!(GPIOA->IDR & (1<<0)) && (GPIOE->IDR & (1<<3)) && (GPIOE->IDR & (1<<4)))
  {
    key_flay = 1;
  }
  return temp;
}




