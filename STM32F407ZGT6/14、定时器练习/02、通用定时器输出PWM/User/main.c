#include "sys.h"
#include "delay.h"
#include "key.h"
#include "pwm.h"

int main(void)
{
    uint8_t key;

    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    SysTick_Init();                         /* ��ʱ��ʼ�� */
    KEY_Init();                             /* ������ʼ�� */
    TIM14_PWM_Init(1000, 72, 500);          /* 50%ռ�ձ� */

    while(1)
    {
        key = KEY_Scan();
        if(key == 1)
        {
            if(TIM14->CCR1 == 0) TIM14->CCR1 = 0;
            else                TIM14->CCR1 -= 100;
        }
        else if(key == 2)
        {
            if(TIM14->CCR1 == 1000) TIM14->CCR1 = 1000;
            else                   TIM14->CCR1 += 100;
        }
    }
}




