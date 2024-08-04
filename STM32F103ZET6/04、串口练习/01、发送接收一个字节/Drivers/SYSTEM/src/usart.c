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








