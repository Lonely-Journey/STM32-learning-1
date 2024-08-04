#include "sys.h"
#include "delay.h"
#include "timer.h"
#include "pwm.h"

int main(void)
{
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    NVIC_SetPriorityGrouping(5);            /* 5--101  2�ŷ��鷽�� 2 λ��ռ���ȼ��� 2 λ��Ӧ���ȼ� */
    SysTick_Init();                         /* ��ʱ��ʼ�� */
    TIM6_Init(500,7200);                    /* 500ms ��ʱ�ж� */
    TIM14_PWM_Init(1000, 72, 500);          /* 50%ռ�ձ� */

    while(1)
    {
    }
}




