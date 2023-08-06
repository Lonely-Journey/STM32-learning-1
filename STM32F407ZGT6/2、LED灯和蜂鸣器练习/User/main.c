#include "sys.h"
#include "delay.h"
#include "led.h"
#include "beep.h"

int main(void)
{
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    SysTick_Init();                         /* ��ʱ��ʼ�� */
    LED_Init();                             /* LED������ʼ�� */
    BEEP_Init();                            /* BEEP������ʼ�� */

    while(1)
    {
    }
}




