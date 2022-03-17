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
	u8 str[] = "momoû����";
  u8 str2[30]; 
	
  SysTick_Init();
  NVIC_SetPriorityGrouping(5);       //���ȼ����� 
  USART1_Init(115200);
  W25Q64_Init();
  W25Q64_Sector_Erase(0x7);
  W25Q64_Page_Write(0x1,sizeof(str),str);
  W25Q64_Read_Bytes(0x1,sizeof(str),str2);
  
  while(1)
  {
    printf("str2 : %s\r\n",str2);
    delay1_ms(500);
  }
}











