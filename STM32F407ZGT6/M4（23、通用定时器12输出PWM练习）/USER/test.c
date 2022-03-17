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
  u8 key;
  
  SysTick_Init();
  USART1_Init(115200);
  NVIC_SetPriorityGrouping(5);  //7 - ��ռ���ȼ�������λ��
  KEY_Init();
  LCD_Init();
  TIM12_PWM_Init(1000,84,500);
  
  while(1)
  {
    key = KEY_Scan();
    if(key == 3)
    {
      if(TIM12->CCR2 == 0)
      {
        TIM12->CCR2 = 0;
      }
      else 
      TIM12->CCR2 -= 100;
    }
    else if(key == 4)
    {
      if(TIM12->CCR2 == 1000)
      {
        TIM12->CCR2 = 1000;
      }
      else 
      TIM12->CCR2 += 100;
    }
  }
}



















