#include "usart.h"

/**********************************************************
* @funcName ：USART1_Init
* @brief    ：对USART1对应的GPIO口进行初始化设置
* @param    ：uint32_t baud (波特率)
* @retval   ：void
* @details  ：
*             PA9     TX     ---------输出
*             PA10    RX     ---------输入
* @fn       ：
************************************************************/
void USART1_Init(uint32_t baud)
{
    uint32_t pri;

    /* GPIOx配置部分 */
    /* GPIOx时钟使能 */
    RCC->AHB1ENR |= (1<<0);

    /* 端口模式寄存器 */
    GPIOA->MODER &= ~((3<<2*9)|(3<<2*10));
    GPIOA->MODER |= ((2<<2*9)|(2<<2*10));

    /* 端口输出类型寄存器 */
    GPIOA->OTYPER &= ~(1<<9); 

    /* 端口输出速率寄存器 */
    GPIOA->OSPEEDR &= ~(3<<2*9);
    GPIOA->OSPEEDR |= (2<<2*9);

    /* 端口输入上拉/下拉寄存器 */
    GPIOA->PUPDR &= ~(3<<2*10);

    /* 端口复用功能寄存器 */
    GPIOA->AFR[1] &= ~((0xf<<4*(9-8))|(0xf<<4*(10-8)));
    GPIOA->AFR[1] |= (7<<4*(9-8)|(7<<4*(10-8)));

    /* 串口配置部分 */
    /* 串口时钟使能 */
    RCC->APB2ENR |= (1<<4);

    /* 控制寄存器CR1 */
    USART1->CR1 &= ~((1<<15)|(1<<12));
    USART1->CR1 |= ((1<<3)|(1<<2));

    /* 使能中断形式（CR1）*/
    USART1->CR1 |= (1<<5);      /* 接收完成中断使能 */
    USART1->CR1 |= (1<<4);      /* 空闲中断使能 */

    /* 控制寄存器CR2 */
    USART1->CR2 &= ~(3<<12);

    //波特率寄存器
    USART1->BRR = 84*1000000/baud;

    /* NVIC配置 */
    /* 优先级分组(在主函数里写) */
    /* 计算优先级编码值 */
    /* 5--101  2号分组方案 2 位抢占优先级， 2 位响应优先级 */
    pri = NVIC_EncodePriority (5, 1, 1);  /* 该中断抢占优先为1，子优先级为1 */
    /* 将编码值写入具体中断源 */
    NVIC_SetPriority(USART1_IRQn,pri);
    /* 使能NVIC响应通道 */
    NVIC_EnableIRQ(USART1_IRQn);

    /* 串口使能 */
    USART1->CR1 |= (1<<13);
}



/**********************************************************
* @funcName ：USART1_Send_Byte
* @brief    ：串口1发送一个字节的数据（uint8_t）
* @param    ：uint8_t data
* @retval   ：void
* @details  ：
* @fn       ：
************************************************************/
void USART1_Send_Byte(uint8_t data)
{
    while(!(USART1->SR & (1<<6)));
    USART1->DR = data;
}



/**********************************************************
* @funcName ：USART1_Send_Str
* @brief    ：串口1发送一个字符串
* @param    ：uint8_t *str
* @retval   ：void
* @details  ：
* @fn       ：
************************************************************/
void USART1_Send_Str(uint8_t *str)
{
    while(*str != '\0')
    {
        while(!(USART1->SR & (1<<6)));
        USART1->DR = *str;
        str++;
    }
}



/**********************************************************
* @funcName ：USART1_Receive_Byte
* @brief    ：串口1接收一个字节的数据（uint8_t）
* @param    ：void
* @retval   ：uint8_t
* @details  ：
* @fn       ：
************************************************************/
uint8_t USART1_Receive_Byte(void)
{
    uint8_t data;

    while(!(USART1->SR & (1<<5)));
    data = USART1->DR;

    return data;
}



/**********************************************************
* @funcName ：USART1_Receive_Str
* @brief    ：串口1接收一个字符串
* @param    ：uint8_t *str
* @retval   ：void
* @details  ：
* @fn       ：
************************************************************/
void USART1_Receive_Str(uint8_t *str)
{
    while(1)
    {
        while(!(USART1->SR & (1<<5)));
        *str = USART1->DR;
        if(*str == '\r')
        {
            while(!(USART1->SR & (1<<5)));
            *str = USART1->DR;
            if(*str == '\n') break;
        }
        str++;
    }
    *str = '\0';
}



uint8_t str[200]={0};
uint8_t strSize=0;
/**********************************************************
* @funcName ：USART1_IRQHandler
* @brief    ：串口1中断
* @param    ：void
* @retval   ：void
* @details  ：
* @fn       ：
************************************************************/
void USART1_IRQHandler(void)
{
    /* 判断中断触发的形式 */
    /* 接收完成中断 */
    if(USART1->SR & (1<<5))
    {
        /* 中断要执行的任务 */
        str[strSize++] = USART1->DR;
        
        /* 先读USART1->SR，再改USART1->DR，可以清除中断标志 */
        /* 或者直接修改USART1->SR，从而清除中断标志 */
        /* 我这里两种方式都用 */
        USART1->SR &= ~(1<<5);
    }
    if(USART1->SR & (1<<4))
    {
        printf("%s", str);
        strSize=0;
        
        /* 先读USART1->SR，再改USART1->DR，可以清除中断标志 */
        /* 或者直接修改USART1->SR，从而清除中断标志 */
        /* 我这里两种方式都用 */
        USART1->SR &= ~(1<<4);
        USART1->DR;
    }
}





























/******************************************************************************************/
/* 加入以下代码, 支持printf函数, 而不需要选择use MicroLIB */

#if 1
#if (__ARMCC_VERSION >= 6010050)            /* 使用AC6编译器时 */
__asm(".global __use_no_semihosting\n\t");  /* 声明不使用半主机模式 */
__asm(".global __ARM_use_no_argv \n\t");    /* AC6下需要声明main函数为无参数格式，否则部分例程可能出现半主机模式 */

#else
/* 使用AC5编译器时, 要在这里定义__FILE 和 不使用半主机模式 */
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif

/* 不使用半主机模式，至少需要重定义_ttywrch\_sys_exit\_sys_command_string函数,以同时兼容AC6和AC5模式 */
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

/* 定义_sys_exit()以避免使用半主机模式 */
void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

/* FILE 在 stdio.h里面定义. */
FILE __stdout;

/* 重定义fputc函数, printf函数最终会通过调用fputc输出字符串到串口 */
int fputc(int ch, FILE *f)
{
    while ((USART1->SR & 0X40) == 0);     /* 等待上一个字符发送完成 */

    USART1->DR = (uint8_t)ch;             /* 将要发送的字符 ch 写入到DR寄存器 */
    return ch;
}
#endif
/******************************************************************************************/





