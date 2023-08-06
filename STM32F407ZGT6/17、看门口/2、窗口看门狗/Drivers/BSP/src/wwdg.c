#include "wwdg.h"



/**
******************************************************************************
* @file      ��.\Drivers\BSP\src\wwdg.c
*              .\Drivers\BSP\inc\wwdg.h
* @author    ��XRbin
* @version   ��V1.0
* @date      ��2023-08-05
* @brief     �����ڿ��Ź���ϰ����
******************************************************************************
* @attention
*   �ҵ�GitHub   ��https://github.com/XR-bin
*   �ҵ�gitee    ��https://gitee.com/xrbin
*   �ҵ�leetcode ��https://leetcode.cn/u/xrbin/
******************************************************************************
*/



/* ����WWDG������������ֵ,Ĭ��Ϊ���. */
uint8_t g_wwdg_cnt = 0x7f;


/**********************************************************
* @funcName ��WWDG_Init
* @brief    ����ʼ�����ڿ��Ź�
* @param    ��uint8_t tr (������ֵ)
* @param    ��uint8_t wr (����ֵ)
* @param    ��uint8_t fprer (��Ƶϵ����WDGTB��,��Χ:0~7,��ʾ2^WDGTB��Ƶ)
* @retval   ��void
* @details  ��
* @fn       ��
*           Fwwdg=PCLK1/(4096*2^fprer). һ��PCLK1=36Mhz
*           ���ʱ��=(4096*2^fprer)*(tr-0X3F)/PCLK3
*           ����fprer=4,tr=7f,PCLK1=36Mhz
*           �����ʱ��=4096*16*64/36Mhz=116.50ms
************************************************************/
void WWDG_Init(uint8_t tr, uint8_t wr, uint8_t fprer)
{
    uint32_t pri;

    RCC->APB1ENR |= 1 << 11;        /* ʹ��wwdgʱ�� */
    g_wwdg_cnt = tr & g_wwdg_cnt;   /* ��ʼ��WWDG_CNT. */
    WWDG->CFR |= fprer << 7;        /* PCLK1/4096�ٳ�2^fprer */
    WWDG->CFR &= 0XFF80;
    WWDG->CFR |= wr;                /* �趨����ֵ */
    WWDG->CR |= g_wwdg_cnt;         /* �趨������ֵ */
    WWDG->CR |= 1 << 7;             /* �������Ź� */

    /* NVIC���� */
    /* ���ȼ�����(����������д) */
    /* �������ȼ�����ֵ */
    /* 5--101  2�ŷ��鷽�� 2 λ��ռ���ȼ��� 2 λ��Ӧ���ȼ� */
    pri = NVIC_EncodePriority(5, 1, 1);     /* ���ж���ռ����Ϊ1�������ȼ�Ϊ1 */
    /* ������ֵд������ж�Դ */
    NVIC_SetPriority(WWDG_IRQn,pri);
    /* ʹ��NVIC��Ӧͨ�� */
    NVIC_EnableIRQ(WWDG_IRQn); 

    WWDG->SR = 0X00;                /* �����ǰ�����жϱ�־λ */
    WWDG->CFR |= 1 << 9;            /* ʹ����ǰ�����ж� */
}



/**********************************************************
* @funcName ��WWDG_Set_Counter
* @brief    ��������WWDG��������ֵ
* @param    ��uint8_t cnt (����ֵ)
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void WWDG_Set_Counter(uint8_t cnt)
{
    WWDG->CR = (cnt & 0x7F);   /* ������7λ������ */
}



/**********************************************************
* @funcName ��WWDG_IRQHandler
* @brief    �����ڿ��Ź��жϷ������
* @param    ��void
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void WWDG_IRQHandler(void)
{  
    if (WWDG->SR & 0X01)                /* ���ж��Ƿ�����WWDG��ǰ�����ж� */
    {
        WWDG->SR = 0X00;                /* �����ǰ�����жϱ�־λ */
        WWDG_Set_Counter(g_wwdg_cnt);   /* ���贰�ڿ��Ź���ֵ! */
        GPIOF->ODR ^= (1<<10);          /* LED1�̵���˸ */
    }
}



