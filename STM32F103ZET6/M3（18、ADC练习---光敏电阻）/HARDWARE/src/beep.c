#include "sys.h"

/*****************************************************
*函数功能  ：对LED对应的GPIO口进行初始化设置
*函数名    ：BEEP_Init
*函数参数  ：void
*函数返回值：void
*描述      ：
             BEEP     PB8
             高电平响，低电平不响-----输出模式
********************************************************/
void BEEP_Init(void)
{
  //GPIOx时钟使能
  RCC->APB2ENR |= (1<<3);
  //端口配置寄存器
  GPIOB->CRH &= ~(0xf<<4*(8-8));
  GPIOB->CRH |= (3<<4*(8-8));
  //端口输出数据寄存器
  GPIOB->ODR &= ~(1<<8);
}





