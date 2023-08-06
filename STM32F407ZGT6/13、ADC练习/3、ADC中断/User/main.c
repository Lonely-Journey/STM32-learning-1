#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"

int main(void)
{
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    SysTick_Init();                         /* ��ʱ��ʼ�� */
    USART1_Init(115200);                    /* ����1��ʼ�� 115200 */
    ADC3_In5_Init();                        /* ADC3ͨ��6��ʼ�� */

    while(1)
    {
        /* ÿ�յ�����1�����ݾ�ת��һ��ADC���� */
        USART1_Receive_Byte();
        /* ��������ͨ��ת������ */
        ADC3->CR2 |= (1<<22);
    }
}




