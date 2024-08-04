#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "exti.h"

int main(void)
{
    uint8_t key_flay;

    sys_stm32_clock_init(9);      /* ϵͳʱ�ӳ�ʼ��*/
    NVIC_SetPriorityGrouping(5);  /* 5--101  2�ŷ��鷽�� 2 λ��ռ���ȼ��� 2 λ��Ӧ���ȼ� */
    SysTick_Init();               /* ��ʱ��ʼ�� */
    LED_Init();                   /* LED��ʼ�� */
    KEY_Init();                   /* KEY��ʼ�� */
    EXTI5_Swier_Init();           /* ����ⲿ�жϳ�ʼ�� */

    while(1)
    {
        key_flay = KEY_Scan();
        if(key_flay == 2)
        {
            EXTI->SWIER |= (1<<5);     /* ��������ж� */
        }
    }
}




