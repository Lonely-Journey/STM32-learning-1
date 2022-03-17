#include "stm32f4xx.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "usart.h"
#include "stdio.h"
#include "nvic.h"
#include "exit.h"
#include "delay.h"
#include "at24cxx.h"
#include "lcd.h"
#include "w25q64.h"
#include "touch.h"
#include "adc.h"
#include "time.h"
#include "pwm.h"
#include "dma.h"
#include "rtc.h"

/**************************************************************
*��ע���
*         1��W25Q64��0x0b0000~0x1F1F58���ڴ洢�ֿ�
*            ��ʼ���飺0b   ��11��      ������0    ��0������
*                  ҳ��0    ��0ҳ       �ֽڣ�0    ��0���ֽ�
*            �������飺1F   ��31��      ������1    ��1������
*                  ҳ��F    ��15ҳ      �ֽڣ�58   ��88���ֽ�
*         2��AT24C02��0~16���ڴ洢LCD�봥����֮���У׼ϵ��
***************************************************************/ 

int main(void)
{   
  RTC_DATES time = {19,10,10,6,12,20,20,0};
  RTC_DATES rtc;
  SysTick_Init();
  USART1_Init(115200);
  NVIC_SetPriorityGrouping(5);  //7 - ��ռ���ȼ�������λ��
  RTC_Init(time);
  while(1)
  {
    RTC_Read_Time(&rtc);
    RTC_Read_date(&rtc);
    printf("20%d��%d��%d�� ����%d\r\n",rtc.year,rtc.month,rtc.day,rtc.week);
    printf("%d : %d : %d\r\n",rtc.hour,rtc.min,rtc.sec);
    
    delay_ms(1000);
  }
}



















