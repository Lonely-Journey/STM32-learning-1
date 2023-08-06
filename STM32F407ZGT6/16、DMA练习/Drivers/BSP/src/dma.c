#include "dma.h"



/**
******************************************************************************
* @file      ��.\Drivers\BSP\src\dma.c
*              .\Drivers\BSP\inc\dma.h
* @author    ��XRbin
* @version   ��V1.0
* @date      ��2023-08-05
* @brief     ��DMA��ϰ����
******************************************************************************
* @attention
*   �ҵ�GitHub   ��https://github.com/XR-bin
*   �ҵ�gitee    ��https://gitee.com/xrbin
*   �ҵ�leetcode ��https://leetcode.cn/u/xrbin/
******************************************************************************
*/



/**********************************************************
* @funcName ��DMA1_Usart1_Init
* @brief    ����DMA2��ͨ��7���г�ʼ������(����USART1�ķ���ͨ��)
* @param    ��uint8_t* data (DMA�洢����ַ)
* @retval   ��void
* @details  ��
* @fn       ��
*            DMA2���洢�������ݰ��˵�����1����
************************************************************/
void DMA2_Usart1_Init(uint8_t ch, uint8_t* data)
{
    RCC->AHB1ENR |= 1<<22;             /* ����DMA2ʱ�� */

    delay_ms(5);                       /* �ȴ�DMAʱ���ȶ� */

    DMA2_Stream7->CR = (ch & 7) << 25;           /* ������ͨ��ѡ��, 0 ~ 7 */
    DMA2_Stream7->PAR = (uint32_t)&USART1->DR;   /* DMA �����ַ */
    DMA2_Stream7->M0AR = (uint32_t)data;         /* DMA �洢����ַ */
    DMA2_Stream7->NDTR = 0;                      /* DMA ���䳤������, ������dma_enable�������� */

    /* DMAͨ��x���üĴ��� */
    DMA2_Stream7->CR = 0;           /* ��λCCR�Ĵ��� */
    DMA2_Stream7->CR |= 0 << 8;      /* ��ѭ��ģʽ(��ʹ����ͨģʽ) */
    DMA2_Stream7->CR |= 0 << 9;      /* ���������ģʽ */
    DMA2_Stream7->CR |= 0 << 11;     /* �������ݳ���:8λ */
    DMA2_Stream7->CR |= 0 << 13;     /* �洢�����ݳ���:8λ */
    DMA2_Stream7->CR |= 0 << 21;     /* ����ͻ�����δ��� */
    DMA2_Stream7->CR |= 0 << 23;     /* �洢��ͻ�����δ��� */
    DMA2_Stream7->CR |= 1 << 6;      /* �洢��������ģʽ */
    DMA2_Stream7->CR |= 1 << 10;     /* �洢������ģʽ */
    DMA2_Stream7->CR |= 1 << 16;     /* �е����ȼ� */

    /* ʹ�ܴ���DMA���� */
    USART1->CR3 |= (1<<7);
}



/**********************************************************
* @funcName ��DMA2_Enable
* @brief    ������DMA2���ݴ���
* @param    ��uint16_t cndtr (DMA����������)
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void DMA2_Enable(uint16_t ndtr)
{
    DMA2_Stream7->CR &= ~(1 << 0);   /* �ر�DMA���� */

    while (DMA2_Stream7->CR & 0X1);  /* ȷ��DMA���Ա����� */

    DMA2_Stream7->NDTR = ndtr;       /* Ҫ�������������Ŀ */
    DMA2_Stream7->CR |= 1 << 0;      /* ����DMA���� */
}





