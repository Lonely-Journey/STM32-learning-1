#include "sys.h"
#include "delay.h"
#include "usart.h"

int main(void)
{
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    NVIC_SetPriorityGrouping(5);            /* 5--101  2�ŷ��鷽�� 2 λ��ռ���ȼ��� 2 λ��Ӧ���ȼ� */
    SysTick_Init();                         /* ��ʱ��ʼ�� */
    USART1_Init(115200);                    /* ����1��ʼ��   115200 */

    while(1)
    {
    }
}




