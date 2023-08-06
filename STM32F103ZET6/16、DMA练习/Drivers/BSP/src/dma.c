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
* @brief    ����DMA1��ͨ��4���г�ʼ������(����USART1�ķ���ͨ��)
* @param    ��uint8_t* data (DMA�洢����ַ)
* @retval   ��void
* @details  ��
* @fn       ��
*            DMA1���洢�������ݰ��˵�����1����
************************************************************/
void DMA1_Usart1_Init(uint8_t* data)
{
    RCC->AHBENR |= 1<<0;               /* ����DMA1ʱ�� */

    delay_ms(5);                       /* �ȴ�DMAʱ���ȶ� */

    DMA1_Channel4->CPAR = (uint32_t)&USART1->DR;  /* DMA �����ַ */
    DMA1_Channel4->CMAR = (uint32_t)data;         /* DMA �洢����ַ */
    DMA1_Channel4->CNDTR = 0;                     /* DMA ���䳤������, ������dma_enable�������� */


    /* DMAͨ��x���üĴ��� */
    DMA1_Channel4->CCR = 0;            /* ��λCCR�Ĵ��� */
    DMA1_Channel4->CCR &= ~(1<<14);    /* �Ǵ洢�����洢��ģʽ */
    DMA1_Channel4->CCR &= ~(3<<12);    /* ͨ�����ȼ�   �� */
    DMA1_Channel4->CCR &= ~(3<<10);    /* �洢�����ݿ��  8λ */
    DMA1_Channel4->CCR &= ~(3<<8);     /* �������ݿ��    8λ */
    DMA1_Channel4->CCR &= ~(1<<6);     /* ��ִ�������ַ����ģʽ */
    DMA1_Channel4->CCR &= ~(1<<5);     /* ��ѭ��ģʽ(��ʹ����ͨģʽ) */
    DMA1_Channel4->CCR |= (1<<7);      /* ִ�д洢����ַ�������� */
    DMA1_Channel4->CCR |= (1<<4);      /* ���ݴ��䷽�� �Ĵ��������� */

    /* ʹ�ܴ���DMA���� */
    USART1->CR3 |= 1<<7;
}



/**********************************************************
* @funcName ��DMA1_Enable
* @brief    ������DMA1���ݴ���
* @param    ��uint16_t cndtr (DMA����������)
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void DMA1_Enable(uint16_t cndtr)
{
    DMA1_Channel4->CCR &= ~(1 << 0);         /* �ر�DMA���� */

    while (DMA1_Channel4->CCR & (1 << 0));   /* ȷ��DMA���Ա����� */

    DMA1_Channel4->CNDTR = cndtr;            /* DMA���������� */
    DMA1_Channel4->CCR |= 1 << 0;            /* ����DMA���� */
}










