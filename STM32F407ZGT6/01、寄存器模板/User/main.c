#include "sys.h"
#include "delay.h"
#include "led.h"

int main(void)
{
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    SysTick_Init();                         /* ��ʱ��ʼ�� */
    LED_Init();                             /* LED��ʼ�� */

    while(1)
    {
    }
}




