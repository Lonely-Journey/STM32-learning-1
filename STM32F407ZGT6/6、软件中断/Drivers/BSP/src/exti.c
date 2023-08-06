#include "exti.h"



/**
******************************************************************************
* @file      ��.\Drivers\BSP\src\exti.c
*              .\Drivers\BSP\inc\exti.h
* @author    ��XRbin
* @version   ��V1.0
* @date      ��2023-06-16
* @brief     ������жϴ���
******************************************************************************
* @attention
*   �ҵ�GitHub   ��https://github.com/XR-bin
*   �ҵ�gitee    ��https://gitee.com/xrbin
*   �ҵ�leetcode ��https://leetcode.cn/u/xrbin/
******************************************************************************
*/



/**********************************************************
* @funcName ��EXTI5_Swier_Init
* @brief    ������ⲿ�жϳ�ʼ��
* @param    ��void
* @retval   ��void
* @details  ��
*            ����˿�
* @fn       ��
************************************************************/
void EXTI5_Swier_Init(void)
{
    uint32_t pri;

    /* �ⲿ�ж����� */
    /* ����ж��¼��Ĵ��� */
    EXTI->SWIER &= ~(1<<5);

    /* �жϷ��� */
    /* ���ȼ����飨��������д��*/
    /* �������ȼ�����ֵ */
    /* 5--101  2�ŷ��鷽�� 2 λ��ռ���ȼ��� 2 λ��Ӧ���ȼ� */
    pri = NVIC_EncodePriority(5, 1, 1);     /* ���ж���ռ����Ϊ1�������ȼ�Ϊ1 */
    /* ������ֵд������ж�Դ */
    NVIC_SetPriority(EXTI9_5_IRQn, pri);
    /* ʹ��NVIC��Ӧͨ�� */
    NVIC_EnableIRQ(EXTI9_5_IRQn); 

    /* �ж����μĴ��� */
    EXTI->IMR |= (1<<5);
}



/**********************************************************
* @funcName ��EXTI9_5_IRQHandler
* @brief    ���ⲿ�жϷ�����
* @param    ��void
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void EXTI9_5_IRQHandler(void)
{
    if(EXTI->PR & (1<<5))
    {
        GPIOF->ODR ^= (1<<9);            /* LED0��ת */
        EXTI->PR |= (1<<5);              /* д1����жϱ�־ */
    }
}

