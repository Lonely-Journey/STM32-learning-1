#include "stm32f4xx.h"  
#include "stdio.h"

/*****************************************************
*��������  ����ͨ�ö�ʱ��5���г�ʼ�����ò����������ź�
*������    ��TIM5_Capture_Init
*��������  ��void
*��������ֵ��u16 arr,u16 psc,u16 ccr2
*����      ��ͨ�����������������㰴��ʱ��
*            ��������� �� PA0   TIM5_CH1  ����ͨ��1
********************************************************/
void TIM5_Capture_Init(u16 arr,u16 psc)
{
  u32 pri;
  
  /*GPIOx�Ĵ�������*/
  //GPIOxʱ��ʹ��
  RCC->AHB1ENR |= (1<<0);
  //�˿�ģʽ�Ĵ���
  GPIOA->MODER &= ~(3<<0);
  GPIOA->MODER |= (2<<0);
  //���������Ĵ���
  GPIOA->PUPDR &= ~(3<<0);
  //���ù��ܼĴ���
  GPIOA->AFR[0] &= ~(0xf<<0);
  GPIOA->AFR[0] |= (2<<0);
  
  /*TIMx�Ĵ�������*/
  //TIMxʱ��ʹ��
  RCC->APB1ENR |= (1<<3);
  //���ƼĴ���1  CR1
  TIM5->CR1 &= ~(0xffff);
  TIM5->CR1 |= (2<<8);
  TIM5->CR1 |= (1<<7);
  //��ģʽ���ƼĴ���
  TIM5->SMCR &= ~(0xffff);
  //����Ƚ�ģʽ�Ĵ���1
  TIM5->CCMR1 &= ~(0xff<<0);
  TIM5->CCMR1 |= (1<<0);   //��ͨ��1����Ϊ����
	TIM5->CCMR1 |= (0xf<<4); //8�β���������Ƶ�����
  //Ԥ��Ƶ��
  TIM5->PSC = psc;
  //�Զ���װ�ؼĴ���
  TIM5->ARR = arr;
  //����Ƚ�ʹ�ܼĴ���
  TIM5->CCER &= ~(0x7<<0);
  TIM5->CCER |= (0x1<<0);
  //�жϻ��ܼĴ���
  TIM5->DIER |= 1<<1;   //�����ش���
  TIM5->DIER |= 1<<0;   //�����¼�����
  
  //�¼����ɼĴ���
  TIM5->EGR |= 1<<0;
  //����¼����ɱ�־
  TIM5->SR &= ~(1<0);
  
  /*NVIC����*/
  //�жϷ��飨����������
  //�����ж����ȼ������ж�
  pri = NVIC_EncodePriority (5, 1, 2);  //5�ŷ�����ʽ����ռ1������Ӧ2��
  //������д���ж�Դ
  NVIC_SetPriority(TIM5_IRQn,pri);
  //ʹ��NVICͨ��
  NVIC_EnableIRQ(TIM5_IRQn);
  
  //TIMxʹ��
  TIM5->CR1 |= (1<<0);
}

/******************************************
*��������  ����ʱ��5���жϷ�����
*������    ��TIM5_IRQHandler
*��������  ����
*��������ֵ����
*��������  ��
*********************************************/
void TIM5_IRQHandler(void)
{
  static u16 update_num;
  static u8 update_flay = 0;
  static u16 rising_edge; 
  u16 falling_edge;
  u16 cont; 
  u16 t;
	//�����ж�
	if(TIM5->SR & (1<<0))
	{
		//���жϱ�־λ
		TIM5->SR &= ~(1<<0);
		//�����¼�
    if(update_flay)
    {
      update_num++;
    }
	}
  //���ش����ж�
  if(TIM5->SR & (1<<1))
  {
    //�ж��ǲ��������ش���
    if(!(TIM5->CCER & (1<<1)))
    {
      //�������������־λ
      update_flay = 1;
      //��ȡ�����ؼ���
      rising_edge = TIM5->CCR1;
      //�ѱ��ش�����ʽ��Ϊ�½���
      TIM5->CCER |= (1<<1);	
    }
    else if(TIM5->CCER & (1<<1))
    {
      //��ȡ�����ؼ���
      falling_edge = TIM5->CCR1;
      //����������
			cont = 65535 * update_num - rising_edge + falling_edge;
      t = cont / 10;
      
      printf("�����ȣ�%d\r\n",t);
      
      update_num = 0;
      update_flay = 0;
      
      //�л���������
			TIM5->CCER &= ~(1<<1);
    }
  }
}









