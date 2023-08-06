#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"
#include "capture.h"

int main(void)
{
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    SysTick_Init();                         /* ��ʱ��ʼ�� */
    USART1_Init(115200);                    /* ����1��ʼ�� 115200 */
    TIM14_PWM_Init(1000, 72, 500);          /* ���PWM��50%ռ�ձ� */
    TIM4_Capture_Init(0xffff, 72);          /* �����ʼ�� */
    /***
    * ע�⣺��Ϊ�����ж������ظ��������жϣ�
    * ����TIM4_Capture_Init�������TIM3_PWM_Init֮��
    */

    while(1)
    {
    }
}




