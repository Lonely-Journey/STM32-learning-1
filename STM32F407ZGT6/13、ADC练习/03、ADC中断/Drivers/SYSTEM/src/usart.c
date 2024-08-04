#include "usart.h"



/**********************************************************
* @funcName ��USART1_Init
* @brief    ����USART1��Ӧ��GPIO�ڽ��г�ʼ������
* @param    ��uint32_t baud (������)
* @retval   ��void
* @details  ��
*             PA9     TX     ---------���
*             PA10    RX     ---------����
* @fn       ��
************************************************************/
void USART1_Init(uint32_t baud)
{
//    uint32_t pri;

    /* GPIOx���ò��� */
    /* GPIOxʱ��ʹ�� */
    RCC->AHB1ENR |= (1<<0);

    /* �˿�ģʽ�Ĵ��� */
    GPIOA->MODER &= ~((3<<2*9)|(3<<2*10));
    GPIOA->MODER |= ((2<<2*9)|(2<<2*10));

    /* �˿�������ͼĴ��� */
    GPIOA->OTYPER &= ~(1<<9); 

    /* �˿�������ʼĴ��� */
    GPIOA->OSPEEDR &= ~(3<<2*9);
    GPIOA->OSPEEDR |= (2<<2*9);

    /* �˿���������/�����Ĵ��� */
    GPIOA->PUPDR &= ~(3<<2*10);

    /* �˿ڸ��ù��ܼĴ��� */
    GPIOA->AFR[1] &= ~((0xf<<4*(9-8))|(0xf<<4*(10-8)));
    GPIOA->AFR[1] |= (7<<4*(9-8)|(7<<4*(10-8)));

    /* �������ò��� */
    /* ����ʱ��ʹ�� */
    RCC->APB2ENR |= (1<<4);

    /* ���ƼĴ���CR1 */
    USART1->CR1 &= ~((1<<15)|(1<<12));
    USART1->CR1 |= ((1<<3)|(1<<2));

    /* ʹ���ж���ʽ��CR1��*/
//    USART1->CR1 |= (1<<5);      /* ��������ж�ʹ�� */
//    USART1->CR1 |= (1<<4);      /* �����ж�ʹ�� */

    /* ���ƼĴ���CR2 */
    USART1->CR2 &= ~(3<<12);

    //�����ʼĴ���
    USART1->BRR = 84*1000000/baud;

    /* NVIC���� */
    /* ���ȼ�����(����������д) */
    /* �������ȼ�����ֵ */
    /* 5--101  2�ŷ��鷽�� 2 λ��ռ���ȼ��� 2 λ��Ӧ���ȼ� */
//    pri = NVIC_EncodePriority (5, 1, 1);  /* ���ж���ռ����Ϊ1�������ȼ�Ϊ1 */
    /* ������ֵд������ж�Դ */
//    NVIC_SetPriority(USART1_IRQn,pri);
    /* ʹ��NVIC��Ӧͨ�� */
//    NVIC_EnableIRQ(USART1_IRQn);

    /* ����ʹ�� */
    USART1->CR1 |= (1<<13);
}



/**********************************************************
* @funcName ��USART1_Send_Byte
* @brief    ������1����һ���ֽڵ����ݣ�uint8_t��
* @param    ��uint8_t data
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void USART1_Send_Byte(uint8_t data)
{
    while(!(USART1->SR & (1<<6)));
    USART1->DR = data;
}



/**********************************************************
* @funcName ��USART1_Send_Str
* @brief    ������1����һ���ַ���
* @param    ��uint8_t *str
* @retval   ��void
* @details  ��
* @fn       ��
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
* @funcName ��USART1_Receive_Byte
* @brief    ������1����һ���ֽڵ����ݣ�uint8_t��
* @param    ��void
* @retval   ��uint8_t
* @details  ��
* @fn       ��
************************************************************/
uint8_t USART1_Receive_Byte(void)
{
    uint8_t data;

    while(!(USART1->SR & (1<<5)));
    data = USART1->DR;

    return data;
}



/**********************************************************
* @funcName ��USART1_Receive_Str
* @brief    ������1����һ���ַ���
* @param    ��uint8_t *str
* @retval   ��void
* @details  ��
* @fn       ��
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



/**********************************************************
* @funcName ��USART2_Init
* @brief    ����USART2��Ӧ��GPIO�ڽ��г�ʼ������
* @param    ��uint32_t baud (������)
* @retval   ��void
* @details  ��
*            PA2     TX     ---------���
*            PA3     RX     ---------����
* @fn       ��
************************************************************/
void USART2_Init(uint32_t baud)
{
//    uint32_t pri;
    /* GPIOx���ò��� */
    /* GPIOxʱ��ʹ�� */
    RCC->AHB1ENR |= (1<<0);

    /* �˿�ģʽ�Ĵ��� */
    GPIOA->MODER &= ~((3<<2*2)|(3<<2*3));
    GPIOA->MODER |= ((2<<2*2)|(2<<2*3));

    /* �˿�������ͼĴ��� */
    GPIOA->OTYPER &= ~(1<<2); 

    /* �˿�������ʼĴ��� */
    GPIOA->OSPEEDR &= ~(3<<2*2);
    GPIOA->OSPEEDR |= (2<<2*2);

    /* �˿���������/�����Ĵ��� */
    GPIOA->PUPDR &= ~(3<<2*3);

    /* �˿ڸ��ù��ܼĴ��� */
    GPIOA->AFR[0] &= ~((0xf<<4*2)|(0xf<<4*3));
    GPIOA->AFR[0] |= ((7<<4*2)|(7<<4*3));

    /* �������ò��� */
    /* ����ʱ��ʹ�� */
    RCC->APB1ENR |= (1<<17);

    /* ���ƼĴ���CR1 */
    USART2->CR1 &= ~((1<<15)|(1<<12));
    USART2->CR1 |= ((1<<3)|(1<<2));

    /* ʹ���ж���ʽ��CR1�� */
//    USART2->CR1 |= (1<<5);      /* ��������ж�ʹ�� */
//    USART2->CR1 |= (1<<4);      /* �����ж�ʹ�� */

    /* ���ƼĴ���CR2 */
    USART2->CR2 &= ~(3<<12);

    /* �����ʼĴ��� */
    USART2->BRR = 42*1000000/baud;

    /* NVIC���� */
    /* ���ȼ�����(����������д) */
    /* �������ȼ�����ֵ */
    /* 5--101  2�ŷ��鷽�� 2 λ��ռ���ȼ��� 2 λ��Ӧ���ȼ� */
//    pri = NVIC_EncodePriority (5, 1, 1);  /* ���ж���ռ����Ϊ1�������ȼ�Ϊ1 */
    /* ������ֵд������ж�Դ */
//    NVIC_SetPriority(USART2_IRQn,pri);
    /* ʹ��NVIC��Ӧͨ�� */
//    NVIC_EnableIRQ(USART2_IRQn);

    /* ����ʹ�� */
    USART2->CR1 |= (1<<13);
}



/**********************************************************
* @funcName ��USART2_Send_Byte
* @brief    ������2����һ���ֽڵ����ݣ�uint8_t��
* @param    ��uint8_t data
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void USART2_Send_Byte(uint8_t data)
{
    while(!(USART2->SR & (1<<6)));
    USART2->DR = data;
}



/**********************************************************
* @funcName ��USART2_Receive_Byte
* @brief    ������2����һ���ֽڵ����ݣ�uint8_t��
* @param    ��void
* @retval   ��uint8_t
* @details  ��
* @fn       ��
************************************************************/
uint8_t USART2_Receive_Byte(void)
{
    uint8_t data;

    while(!(USART2->SR & (1<<5)));
    data = USART2->DR;

    return data;
}



















/******************************************************************************************/
/* �������´���, ֧��printf����, ������Ҫѡ��use MicroLIB */

#if 1
#if (__ARMCC_VERSION >= 6010050)            /* ʹ��AC6������ʱ */
__asm(".global __use_no_semihosting\n\t");  /* ������ʹ�ð�����ģʽ */
__asm(".global __ARM_use_no_argv \n\t");    /* AC6����Ҫ����main����Ϊ�޲�����ʽ�����򲿷����̿��ܳ��ְ�����ģʽ */

#else
/* ʹ��AC5������ʱ, Ҫ�����ﶨ��__FILE �� ��ʹ�ð�����ģʽ */
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif

/* ��ʹ�ð�����ģʽ��������Ҫ�ض���_ttywrch\_sys_exit\_sys_command_string����,��ͬʱ����AC6��AC5ģʽ */
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

/* ����_sys_exit()�Ա���ʹ�ð�����ģʽ */
void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

/* FILE �� stdio.h���涨��. */
FILE __stdout;

/* �ض���fputc����, printf�������ջ�ͨ������fputc����ַ��������� */
int fputc(int ch, FILE *f)
{
    while ((USART1->SR & 0X40) == 0);     /* �ȴ���һ���ַ�������� */

    USART1->DR = (uint8_t)ch;             /* ��Ҫ���͵��ַ� ch д�뵽DR�Ĵ��� */
    return ch;
}
#endif
/******************************************************************************************/





