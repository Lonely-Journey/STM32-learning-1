#include "sys.h"

/*****************************************************
*��������  ����DMA1��ͨ��4���г�ʼ������
*������    ��DMA1_Channels4_Init
*��������  ��void
*��������ֵ��u16 ndtr,u8 *data 
*����      ��
*           DMA���洢�������ݰ��˵�����1����
********************************************************/
void DMA1_Channels4_Init(u16 ndtr,u8 *data)
{
  //DMA1ʱ��ʹ��
  RCC->AHBENR |= 1<<0;
  //DMAͨ��x���üĴ���
  DMA1_Channel4->CCR &= ~(1<<14);    //�Ǵ洢�����洢��ģʽ
  DMA1_Channel4->CCR &= ~(3<<12);    //ͨ�����ȼ�   ��
  DMA1_Channel4->CCR &= ~(3<<10);    //�洢�����ݿ��  8λ
  DMA1_Channel4->CCR &= ~(3<<8);     //�������ݿ��    8λ
  DMA1_Channel4->CCR |= (1<<7);      //ִ�д洢����ַ��������
  DMA1_Channel4->CCR &= ~(1<<0);     //��ִ�������ַ����ģʽ 
  DMA1_Channel4->CCR |= (1<<4);      //���ݴ��䷽�� 
  //DMAͨ��x���������Ĵ���
  DMA1_Channel4->CNDTR = 0;
  DMA1_Channel4->CNDTR = ndtr;            //���ô�������
  //DMAͨ��x�����ַ�Ĵ���
  DMA1_Channel4->CPAR = 0;
  DMA1_Channel4->CPAR = (u32)&USART1->DR;  //���������ַ
  //DMAͨ��x�����ַ�Ĵ���
  DMA1_Channel4->CMAR = 0;
  DMA1_Channel4->CMAR = (u32)data;         //���ô洢��ַ
  //ʹ�ܴ���DMA����
  USART1->CR3 |= 1<<7;            
  //ʹ��DMA1
  DMA1_Channel4->CCR |= 1<<0;              //ͨ������
}

















