#include "stm32f4xx.h"  
#include "touch.h"
#include "delay.h"
#include "stdio.h"

//200ns��ʱ����
static void delay_200ns(void)
{
  u8 i = 20;
  while(i) i--;
}

/*****************************************************
*��������  ���Դ�����оƬ��Ӧ��GPIO�ڽ��г�ʼ������
*������    ��Touch_Init
*��������  ��void
*��������ֵ��void
*����      ��
*            CS     PC13 ͨ�����
*            SCK    PB0  ͨ�����
*            PEN    PB1  ͨ������
*            MISO   PB2  ͨ������
*            MOSI   PF11 ͨ�����
********************************************************/
void Touch_Init(void)
{
  //PB
  //GPIOxʱ��ʹ��
  RCC->AHB1ENR |= 1<<1;
  //�˿�ģʽ�Ĵ���
  GPIOB->MODER &= ~((3<<(2*0))|(3<<(2*1))|(3<<(2*2)));
  GPIOB->MODER |= 1<<(2*0);
  //�˿�������ͼĴ���
  GPIOB->OTYPER &= ~(1<<0);
  //�˿�����ٶȼĴ���
  GPIOB->OSPEEDR &= ~(3<<(2*0));
  GPIOB->OSPEEDR |= (2<<(2*0));
  //�˿�����/�����Ĵ���
  GPIOB->PUPDR &= ~((3<<(2*1))|(3<<(2*2)));
  
  //PC
  //GPIOxʱ��ʹ��
  RCC->AHB1ENR |= (1<<2);
  //�˿�ģʽ�Ĵ���
  GPIOC->MODER &= ~(3<<(2*13));
  GPIOC->MODER |= (1<<(2*13));
  //�˿�������ͼĴ���
  GPIOC->OTYPER &= ~(1<<13);
  //�˿�����ٶȼĴ���
  GPIOC->OSPEEDR &= ~(3<<(2*13));
  GPIOC->OSPEEDR |= (2<<(2*13));
  
  //PF
  //GPIOxʱ��ʹ��
  RCC->AHB1ENR |= (1<<5);
  //�˿�ģʽ�Ĵ���
  GPIOF->MODER &= ~(3<<(2*11));
  GPIOF->MODER |= (1<<(2*11));
  //�˿�������ͼĴ���
  GPIOF->OTYPER &= ~(1<<11);
  //�˿�����ٶȼĴ���
  GPIOF->OSPEEDR &= ~(3<<(2*11));
  GPIOF->OSPEEDR |= (2<<(2*11));
  
  //��ʼ״̬����
  T_CS_H;
  T_SCK_L;
  T_MOSI_L;
}

/*****************************************************
*��������  ��ͨ��������оƬ��ȡ��������������
*������    ��Touch_Data
*��������  ��u16
*��������ֵ��u8 command 
*����      ��
*       Ƭѡ��        T_CS_H       T_CS_L  
*       ʱ����        T_SCK_H      T_SCK_L  
*       ���������    T_MOSI_H     T_MOSI_L
*       ����������    T_MISO 
*       �ʽӴ���      T_PEN    
********************************************************/
u16 Touch_Data(u8 command)
{
  u16 data = 0;
  u8 i;
  
  //�������������
  T_MOSI_L;
  //����Ƭѡ
  T_CS_L;
  //ѭ��8�η���ָ��
  for(i=0;i<8;i++)
  {
    //ʱ��������
    T_SCK_L;
    //�ж�ָ��λ��ƽ
    if(command & 0x80)T_MOSI_H;
    else T_MOSI_L;
    //��ʱ200ns���������ݽ���
    delay_200ns();
    //ʱ��������
    T_SCK_H;
    //��ʱ200ns���������ݶ�ȡ
    delay_200ns();
    //ָ����������
    command <<= 1;
  }
  //�������������
  T_MOSI_L;
  //����ʱ����
  T_SCK_L;
  //��ʱ120us�����ڵȴ�ADCת������
  delay_us(120);
  //�ճ�һ��������
  T_SCK_L;
  delay_200ns();
  T_SCK_H;
  delay_200ns();
  //ѭ��12�ν�������
  for(i=0;i<12;i++)
  {
    //ָ����������
    data <<= 1;
    //ʱ��������
    T_SCK_L;
    //��ʱ200ns���������ݽ���
    delay_200ns();
    //ʱ��������
    T_SCK_H;
    //��ȡ����λ��ƽ
    if(T_MISO) 
    {
      data |= 0x1;
    }
    //��ʱ200ns���������ݶ�ȡ
    delay_200ns();
  }
  //Ƭѡ����
  T_CS_H;
  //ʱ��������
  T_SCK_L;
  
  return data;
}




