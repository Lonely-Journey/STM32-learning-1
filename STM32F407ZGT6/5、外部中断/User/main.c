#include "sys.h"
#include "delay.h"
#include "led.h"
#include "exti.h"

int main(void)
{
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    SysTick_Init();                         /* ��ʱ��ʼ�� */
    LED_Init();                             /* LED��ʼ�� */
    EXTI0_Init();                           /* �ⲿ�ж�0��ʼ�� */

    while(1)
    {
    }
}




