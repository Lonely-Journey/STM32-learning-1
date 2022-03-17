#include "sys.h"
#include "delay.h"
#include "led.h"

/************************************************************
*��������  ����ʼ��LED�ƶ�Ӧ��GPIO��
*������    ��KEY_Init
*��������  ��void
*��������ֵ��void
*����      ��
            KEY0 PE3
            KEY1 PE4
***************************************************************/
void KEY_Init(void)
{
  //�˿�ʱ��ʹ��
  RCC->APB2ENR |= (1<<6);
  //�˿�ģʽ����(����)
  //�˿�������
  GPIOE->CRL &= ~((0xf<<4*3)|(0xf<<4*4));
  GPIOE->CRL |= ((0x8<<4*3)|(0x8<<4*4));
  GPIOE->ODR |= (3<<3); 
}

/************************************************************
*��������  ����ʼ��LED�ƶ�Ӧ��GPIO��
*������    ��KEY_Init
*��������  ��void
*��������ֵ��void
*����      ��
            KEY0 PE3
            KEY1 PE4
***************************************************************/
u8 KEY_Scan(void)
{
  static u8 temp=0;
  static u8 key_flay = 1;
  if((key_flay)||(!(GPIOE->IDR&(1<<3)))||(!(GPIOE->IDR&(1<<4))))
  {
    delay_ms(10);
    if(!(GPIOE->IDR&(1<<3))||!(GPIOE->IDR&(1<<4)))
    {
      if(!(GPIOE->IDR&(1<<3)))
      {
       // LED1_ON;
        LED0=1;
        temp=1;
      }
      else if(!(GPIOE->IDR&(1<<4)))
      {
        temp = 2;
//        LED1_OFF;
        LED0=0;
      }
      key_flay = 0;
    }
  }
  if(GPIOE->IDR&(1<<3)&&(GPIOE->IDR&(1<<4)))
  {
    key_flay = 1;
  }
  return temp;
}






