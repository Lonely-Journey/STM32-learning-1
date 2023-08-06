#include "sys.h"
#include "delay.h"
#include "led.h"
#include "timer.h"

int main(void)
{
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    NVIC_SetPriorityGrouping(5);            /* 5--101  2�ŷ��鷽�� 2 λ��ռ���ȼ��� 2 λ��Ӧ���ȼ� */
    SysTick_Init();                         /* ��ʱ��ʼ�� */
    LED_Init();                             /* LED��ʼ�� */
    TIM6_Init(4999, 8400);                  /* ��ʱ��6��ʼ��  500ms��ʱ */

    while(1)
    {
        LED0_ON;
        delay_ms(500);
        LED0_OFF;
        delay_ms(500);
    }
}




