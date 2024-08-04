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
    /* GPIOx��ʼ������ */
    /* GPIOxʱ��ʹ�� */
    RCC->APB2ENR |= (1<<2);

    /* �˿����üĴ��� */
    GPIOA->CRH &= ~((0xf<<4*(9-8))|(0xf<<4*(10-8)));
    GPIOA->CRH |= ((11<<4*(9-8))|(4<<4*(10-8)));

    /* ������ӳ��Ĵ��� */
    AFIO->MAPR &= ~(1<<2);

    /* ���踴λ�Ĵ��� */
    RCC->APB2RSTR |= (1<<14);
    RCC->APB2RSTR &= ~(1<<14);

    /* ���ڼĴ�����ʼ������ */
    /* ����ʱ��ʹ�� */
    RCC->APB2ENR |= (1<<14);

    /* ���ƼĴ���CR1 */
    USART1->CR1 &= ~(1<<12);
    USART1->CR1 |= ((1<<2)|(1<<3));

    /* ���ƼĴ���CR2 */
    USART1->CR2 &= ~(3<<12);

    /* �����ʼĴ��� */
    USART1->BRR = 72*1000000 / baud;

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

/* MDK����Ҫ�ض���fputc����, printf�������ջ�ͨ������fputc����ַ��������� */
int fputc(int ch, FILE *f)
{
    while ((USART1->SR & 0X40) == 0);     /* �ȴ���һ���ַ�������� */

    USART1->DR = (uint8_t)ch;             /* ��Ҫ���͵��ַ� ch д�뵽DR�Ĵ��� */
    return ch;
}
#endif
/******************************************************************************************/


