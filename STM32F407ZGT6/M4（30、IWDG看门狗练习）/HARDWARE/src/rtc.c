#include "stm32f4xx.h" 
#include "rtc.h"
#include "stdio.h"

/*****************************************
*��������  ��BCD����תʮ��������
*������    ��BCD_DEC_Transition 
*��������  ��u8 bcd
*��������ֵ��u8
*����      ��
*******************************************/
u8 BCD_DEC_Transition(u8 bcd)
{
  return  (bcd >> 4) * 10 + (bcd & 0x0f);
}

/*****************************************
*��������  ��ʮ��������תBCD����
*������    ��DEC_BCD_Transition
*��������  ��u8 dec
*��������ֵ��u8
*����      ��
*******************************************/
u8 DEC_BCD_Transition(u8 dec)
{
  return  (dec / 10) << 4 | (dec % 10);
}

/************************************
*��������  ����RTC���г�ʼ������
*������    ��RTC_Init
*��������  ��RTC_DATES rtc
*��������ֵ��void
*����      ��
*************************************/
void RTC_Init(RTC_DATES rtc)
{
  /*��Դ������*/
  //ʹ�ܵ�Դ������ʱ��
  RCC->APB1ENR |= 1<<28;
  //��Դ���ƼĴ���
  PWR->CR |= 1<<8;  //ʹ�ܶ�RTC��д����
  
  if(RTC->BKP0R != 0xff)  //���ڱ��⸴λ��������ʱ��ֵ(ֻ�Ը�λ���ã��ϵ���λ�����㣬��Ȼ��������ʱ��ֵ)
  {
    /*ʱ��Դѡ��*/
    //��������ƼĴ���
    RCC->BDCR &= ~(3<<8);
    RCC->BDCR |= (1<<8);             //ѡ���ⲿ����ʱ����Ϊʱ��Դ
    RCC->BDCR |= 1<<0;               //�����ⲿ��������(LSE)
    while(!(RCC->BDCR & (1<<1)));    //�ⲿ������������
    RCC->BDCR |= (1<<15);            //RTCʱ��ʹ��
    RCC->BDCR &= ~(1<<16);
    
    /*RTC����*/
    //���RTC�ڲ��ķ��ʱ���
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    //RTC���ƼĴ���
    RTC->CR &= ~(1 << 6);   //ѡ���ʽ 24
    RTC->CR &= ~(1 << 5);   //ʹ��Ӱ�ӼĴ��� 
    //�ָ�д����
    RTC->WPR = 0xFF;
    /*ʱ������*/
    //����ʱ��
    RTC_Set_Time(rtc.hour,rtc.min,rtc.sec,rtc.pm);
    //��������������
    RTC_Set_date(rtc.year,rtc.month,rtc.day,rtc.week);
    //���⸴λ��������ʱ��ֵ�����ϵ�������λ���Զ����㡣
    RTC->BKP0R = 0xff;   
  }
}

/*****************************************
*��������  ������RTC��ʱ���֡��롢����
*������    ��RTC_Set_Time
*��������  ��u8 hour,u8 min,u8 sec,u8 pm
*��������ֵ��void
*����      ��
*******************************************/
void RTC_Set_Time(u8 hour,u8 min,u8 sec,u8 pm)
{
  u32 data;
  
  //���RTC�ڲ��ķ��ʱ���
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;
  
  //�����ʼ��״̬
  RTC->ISR |= 1<<7;             //�����ʼ��
  while(!(RTC->ISR & (1<<6)));  //�ȴ��������
  //��ʼ����ʱ��
  data = (u32)(DEC_BCD_Transition(pm)<<22)  |
         (u32)(DEC_BCD_Transition(hour)<<16)|
         (u32)(DEC_BCD_Transition(min)<<8)  |
         (u32)(DEC_BCD_Transition(sec));
  RTC->TR = data;
  //�˳���ʼ��ģʽ
  RTC->ISR &= ~(1<<7);
  //�ָ�д����
  RTC->WPR = 0xFF;
}

/**********************************************
*��������  ������RTC���ꡢ���ڡ��¡���
*������    ��RTC_Set_date
*��������  ��u16 year,u8 week,u8 month,u8 day
*��������ֵ��void
*����      ��
************************************************/
void RTC_Set_date(u8 year,u8 month,u8 day,u8 week)
{
    u32 data;
  
  //���RTC�ڲ��ķ��ʱ���
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;
  
  //�����ʼ��״̬
  RTC->ISR |= 1<<7;             //�����ʼ��
  while(!(RTC->ISR & (1<<6)));  //�ȴ��������
  //��ʼ����ʱ��
  data = (u32)(DEC_BCD_Transition(year)<<16)|
         (u32)(DEC_BCD_Transition(week)<<13)|
         (u32)(DEC_BCD_Transition(month)<<8)|
         (u32)(DEC_BCD_Transition(day));
  RTC->DR = data;
  //�˳���ʼ��ģʽ
  RTC->ISR &= ~(1<<7);
  //�ָ�д����
  RTC->WPR = 0xFF;
}

/************************************
*��������  ����ȡRTC��ʱ���֡���
*������    ��RTC_Read_Time
*��������  ��RTC_DATES *rtc
*��������ֵ��void
*����      ��
*************************************/
void RTC_Read_Time(RTC_DATES *rtc)
{
  u32 data;
  
  //���RTC�ڲ��ķ��ʱ���
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;
  
  RTC->ISR &=~(1 << 5);  //��ͬ��  ����
  //�ȴ�����Ӱ�ӼĴ���ͬ��
  while(!(RTC->ISR & (1<<5)));
  //��ȡ��ȡʱ������
  data = RTC->TR;
  //ʱ������ת��Ϊʮ��������
  rtc->hour = BCD_DEC_Transition((data>>16)&0x3f); 
  rtc->min = BCD_DEC_Transition((data>>8)&0x7f);
  rtc->sec = BCD_DEC_Transition(data&0x7f);
  //�ָ�д����
  RTC->WPR = 0xFF;
}

/************************************
*��������  ����ȡRTC��ʱ���֡���
*������    ��RTC_Read_Time
*��������  ��RTC_DATES *rtc
*��������ֵ��void
*����      ��
*************************************/
void RTC_Read_date(RTC_DATES *rtc)
{
  u32 data;
  
  //���RTC�ڲ��ķ��ʱ���
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;
  
  RTC->ISR &=~(1 << 5);  //��ͬ��  ����
  //�ȴ�����Ӱ�ӼĴ���ͬ��
  while(!(RTC->ISR & (1<<5)));
  //��ȡ��ȡʱ������
  data = RTC->DR;
  //ʱ������ת��Ϊʮ��������
  rtc->year  = BCD_DEC_Transition((data>>16)&0xff); 
  rtc->week  = BCD_DEC_Transition((data>>13)&0x7);
  rtc->month = BCD_DEC_Transition((data>>8)&0x1f);
  rtc->day   = BCD_DEC_Transition(data&0x3f);
  //�ָ�д����
  RTC->WPR = 0xFF;
}














