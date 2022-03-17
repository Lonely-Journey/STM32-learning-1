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
  u8 as[] = "885qwertyuiopasd123456789";
  u8 bs[40] ;
  u8 err1,err2;
  
  SysTick_Init();
  NVIC_SetPriorityGrouping(5);       //���ȼ����� 
  USART1_Init(115200);
  AT24CXX_Init();  
  err1 = AT24CXXaddr_Write_Addr(AT24C02,AT24CXX_WRITE,16,sizeof(as),as);
  err2 = AT24CXXaddr_Read_Addr(AT24C02,AT24CXX_WRITE,16,sizeof(as),bs);
  
  while(1)
  {
    printf("err1 : %d    err2 = %d\r\n",err1,err2);
    printf("bs : %s\r\n",bs);
    delay_ms(1000);
  }
  
}











