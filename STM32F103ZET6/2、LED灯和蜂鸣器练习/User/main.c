#include "stm32f1xx.h"
#include "delay.h"
#include "led.h"
#include "beep.h"

int main(void)
{
    sys_stm32_clock_init(9);  /* ϵͳʱ�ӳ�ʼ��*/
    SysTick_Init();           /* ��ʱ��ʼ�� */
    LED_Init();               /* LED������ʼ�� */
    BEEP_Init();              /* BEEP������ʼ�� */

    while(1)
    {
        LED0_ON;
        LED1_ON;
        BEEP_ON;
        delay_ms(600);
        LED0_OFF;
        LED1_OFF;
        BEEP_OFF;
        delay_ms(600);
    }
}




