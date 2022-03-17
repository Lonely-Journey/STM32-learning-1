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

/**************************************************************
*��ע���
*         1��W25Q64��0x0b0000~0x1F1F58���ڴ洢�ֿ�
*            ��ʼ���飺0b   ��11��      ������0    ��0������
*                  ҳ��0    ��0ҳ       �ֽڣ�0    ��0���ֽ�
*            �������飺1F   ��31��      ������1    ��1������
*                  ҳ��F    ��15ҳ      �ֽڣ�58   ��88���ֽ�
*         2��AT24C02��0~16���ڴ洢LCD�봥����֮���У׼ϵ��
***************************************************************/

u8 data = 0;
u8 flay = 0;

int main(void)
{   
  SysTick_Init();
  NVIC_SetPriorityGrouping(5);       //���ȼ����� 
  USART1_Init(115200);
  W25Q64_Init();
  LED_Init();
  
  printf("��ʼ����\r\n");
  W25Q64_Blocks_Erase(0x0b0000,21);
  printf("�������\r\n");
  
  while(1)
  {
    
  }
}











