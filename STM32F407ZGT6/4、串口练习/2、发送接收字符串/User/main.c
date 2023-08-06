#include "sys.h"
#include "delay.h"
#include "usart.h"

int main(void)
{
    uint8_t str[20];

    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    SysTick_Init();                         /* ��ʱ��ʼ�� */
    USART1_Init(115200);                    /* ����1��ʼ��   115200 */

    while(1)
    {
        USART1_Receive_Str(str);
        USART1_Send_Str(str);
        printf("\r\n");
        printf("%s\r\n",str);
    }
}




