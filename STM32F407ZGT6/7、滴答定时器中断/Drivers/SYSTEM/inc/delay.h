#ifndef _DELAY_H
#define _DELAY_H

    /****************   外部头文件声明   ****************/
    #include "sys.h"



    /****************    函数外部声明   *****************/
    void SysTick_Init(void);          /* 滴答定时器初始化 */
    void SysTick1_Init(uint16_t ms);  /* 滴答定时器初始化(带滴答定时器中断) */
    void delay_us(uint32_t us);       /* 微妙延时 */
    void delay1_ms(uint16_t ms);      /* 毫秒延时 */
    void delay_ms(uint16_t ms);       /* 毫秒延时 */

#endif











