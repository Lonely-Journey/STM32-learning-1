#include "led.h"



/**
******************************************************************************
* @file      ��.\Drivers\BSP\src\led.c
*              .\Drivers\BSP\inc\led.h
* @author    ��XRbin
* @version   ��V1.0
* @date      ��2023-06-16
* @brief     ��LED���������ô���
******************************************************************************
* @attention
*   �ҵ�GitHub   ��https://github.com/XR-bin
*   �ҵ�gitee    ��https://gitee.com/xrbin
*   �ҵ�leetcode ��https://leetcode.cn/u/xrbin/
******************************************************************************
*/



/**********************************************************
* @funcName ��LED_Init
* @brief    ����LED��Ӧ��GPIO�ڽ��г�ʼ������
* @param    ��void
* @retval   ��void
* @details  ��
*            LED0     PB5
*            LED1     PE5
*            �ߵ�ƽ�𣬵͵�ƽ��-----���ģʽ
* @fn       ��
************************************************************/
void LED_Init(void)
{
    /* �˿�ʱ��ʹ�� */
    RCC->APB2ENR |= (1<<3);   /* GPIOBʱ�� */
    RCC->APB2ENR |= (1<<6);   /* GPIOEʱ�� */

    /* �˿�ģʽ���� */
    /* �˿������������ */
    /* �˿�����ٶ����� */
    GPIOB->CRL &= ~(0xF<<4*5);
    GPIOB->CRL |= (3<<4*5);

    GPIOE->CRL &= ~(0xF<<4*5);
    GPIOE->CRL |= (3<<4*5);

    /* �˿�������ݼĴ�������     LED�Ƶĳ�ʼ״̬ */
    GPIOB->ODR |= (1<<5);
    GPIOE->ODR |= (1<<5);
}













