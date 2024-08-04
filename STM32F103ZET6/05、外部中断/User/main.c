#include "sys.h"
#include "delay.h"
#include "led.h"
#include "exti.h"

int main(void)
{
    sys_stm32_clock_init(9);      /* ϵͳʱ�ӳ�ʼ��*/
    NVIC_SetPriorityGrouping(5);  /* 5--101  2�ŷ��鷽�� 2 λ��ռ���ȼ��� 2 λ��Ӧ���ȼ� */
    SysTick_Init();               /* ��ʱ��ʼ�� */
    LED_Init();                   /* LED��ʼ�� */
    EXTI4_Init();                 /* �ⲿ�ж�4��ʼ�� */

    while(1)
    {
    }
}




