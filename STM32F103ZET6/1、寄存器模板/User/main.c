#include "sys.h"
#include "delay.h"
#include "led.h"

int main(void)
{
    sys_stm32_clock_init(9);  /* ϵͳʱ�ӳ�ʼ��*/
    SysTick_Init();           /* ��ʱ��ʼ�� */
    LED_Init();               /* LED��ʼ�� */

    while(1)
    {
        LED0_ON;
        LED1_OFF;
        delay_ms(500);
        LED0_OFF;
        LED1_ON;
        delay_ms(500);
    }
}




