#include "timer.h"



/**
******************************************************************************
* @file      ��.\Drivers\BSP\src\timer.c
*              .\Drivers\BSP\inc\timer.h
* @author    ��XRbin
* @version   ��V1.0
* @date      ��2023-07-27
* @brief     ��������ʱ���ж���ϰ����
******************************************************************************
* @attention
*   �ҵ�GitHub   ��https://github.com/XR-bin
*   �ҵ�gitee    ��https://gitee.com/xrbin
*   �ҵ�leetcode ��https://leetcode.cn/u/xrbin/
******************************************************************************
*/



/**********************************************************
* @funcName ��TIM6_Init
* @brief    ���Զ�ʱ��6���г�ʼ������
* @param    ��uint16_t arr (����ֵ)
* @param    ��uint16_t psc (Ԥ��Ƶֵ)
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void TIM6_Init(uint16_t arr, uint16_t psc)
{
    uint32_t pri;

    /* TIMxʱ��ʹ�� */
    RCC->APB1ENR |= 1<<4;

    /* ���ƼĴ���CR1 */
    TIM6->CR1 &= ~(0xffff);
    TIM6->CR1 |= 1<<7;                  /* �Զ���װ��Ԥװ��ʹ�� */

    TIM6->PSC = psc;                    /* Ԥ��Ƶ�� */
    TIM6->ARR = arr;                    /* �Զ���װ�ؼĴ��� */

    TIM6->EGR |= 1<<0;                  /* �����¼����ɼĴ���(��Ϊ����һ������) */
    TIM6->SR &= ~(1<0);                 /* ��������¼���־ */

    /* NVIC���� */
    /* ���ȼ�����(����������д) */
    /* �������ȼ�����ֵ */
    /* 5--101  2�ŷ��鷽�� 2 λ��ռ���ȼ��� 2 λ��Ӧ���ȼ� */
    pri = NVIC_EncodePriority(5, 1, 1);     /* ���ж���ռ����Ϊ1�������ȼ�Ϊ1 */
    /* ������ֵд������ж�Դ */
    NVIC_SetPriority(TIM6_DAC_IRQn,pri);
    /* ʹ��NVIC��Ӧͨ�� */
    NVIC_EnableIRQ(TIM6_DAC_IRQn);

    /* �жϼĴ��� */
    TIM6->DIER &= ~(0xffff);
    TIM6->DIER |= 1<<0;

    /* �������� */
    TIM6->CR1 |= (1<<0);
}



/**********************************************************
* @funcName ��TIM6_DAC_IRQn
* @brief    ����ʱ��6���жϷ�����
* @param    ��void
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void TIM6_DAC_IRQHandler(void)
{
    /* �ж��Ƿ�ʱ��6�ж� */
    if(TIM6->SR & (1<<0))
    {
        /* ���жϱ�־λ */
        TIM6->SR &= ~(1<<0);
        /* �����¼� */
        GPIOF->ODR ^= (1<<10);     /* LED1��˸ */
    }
}



