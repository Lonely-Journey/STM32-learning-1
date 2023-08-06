#include "sys.h"
#include "delay.h"
#include "iic.h"
#include "oled.h"

int main(void)
{
    sys_stm32_clock_init(9);  /* 系统时钟初始化*/
    SysTick_Init();           /* 延时初始化 */
    OLED_Init();              /* OLED屏初始化 */

    OLED_ShowString16(0, 0, "123asdf");

    while(1)
    {
    }
}




