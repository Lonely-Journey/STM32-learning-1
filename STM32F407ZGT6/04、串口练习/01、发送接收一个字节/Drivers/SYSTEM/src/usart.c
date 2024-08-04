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

    /* ���ƼĴ���CR2 */
    USART1->CR2 &= ~(3<<12);

    //�����ʼĴ���
    USART1->BRR = 84*1000000/baud;

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









