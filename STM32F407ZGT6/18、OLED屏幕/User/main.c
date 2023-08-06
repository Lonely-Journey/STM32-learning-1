#include "sys.h"
#include "delay.h"
#include "iic.h"
#include "oled.h"

int main(void)
{
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    SysTick_Init();                         /* ��ʱ��ʼ�� */
    OLED_Init();                            /* OLED����ʼ�� */

    OLED_ShowString16(0, 0, "123asdf");

    while(1)
    {
    }
}




