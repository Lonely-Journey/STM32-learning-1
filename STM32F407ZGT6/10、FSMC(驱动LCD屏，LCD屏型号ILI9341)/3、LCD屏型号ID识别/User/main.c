#include "sys.h"
#include "delay.h"
#include "lcd.h"

int main(void)
{
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    SysTick_Init();                         /* ��ʱ��ʼ�� */
    LCD_ILI9341_Init();       /* ILI9341��LCD����ʼ�� */

    delay_ms(50);

    /* ��ʶ����ͺţ�ST7789��ILI9341��NT35310��NT35510��SSD1963 */
    LCD_Recognition_Id();

    while(1)
    {
    }
}




