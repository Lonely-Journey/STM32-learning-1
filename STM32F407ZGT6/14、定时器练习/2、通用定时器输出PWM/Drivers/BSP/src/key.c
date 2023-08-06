#include "key.h"



/**
******************************************************************************
* @file      ��.\Drivers\BSP\src\key.c
*              .\Drivers\BSP\inc\key.h
* @author    ��XRbin
* @version   ��V1.0
* @date      ��2023-06-16
* @brief     �������������ô���
******************************************************************************
* @attention
*   �ҵ�GitHub   ��https://github.com/XR-bin
*   �ҵ�gitee    ��https://gitee.com/xrbin
*   �ҵ�leetcode ��https://leetcode.cn/u/xrbin/
******************************************************************************
*/



/**********************************************************
* @funcName ��KEY_Init
* @brief    ����KEY��Ӧ��GPIO�ڽ��г�ʼ������
* @param    ��void
* @retval   ��void
* @details  ��
*            KEY0     PE4
*            KEY1     PE3
*            KEY2     PE2
*            KEY_UP   PA0
*                                 -------------���ģʽ
* @fn       ��
************************************************************/
void KEY_Init(void)
{
    /* �˿�ʱ��ʹ��  GPIOA  GPIOE */
    RCC->AHB1ENR |= ((1<<0)|(1<<4));

    /* �˿�ģʽ���� */
    /* PA0 */
    GPIOA->MODER &= ~(3<<0);
    GPIOA->MODER |= (0<<0);                               /* ͨ������ */
    /* PE2~4 */
    GPIOE->MODER &= ~((3<<(2*2))|(3<<(2*3))|(3<<(2*4)));
    GPIOE->MODER |= ((0<<(2*2))|(0<<(2*3))|(0<<(2*4)));   /* ͨ������ */

    /* �˿������� */
    GPIOA->PUPDR &= ~(0<<0);                              /* �������� */
    GPIOE->PUPDR &= ~((3<<(2*2))|(3<<(2*3))|(3<<(2*4)));  /* �������� */
}



/**********************************************************
* @funcName ��KEY_Scan
* @brief    ������ɨ�躯��
* @param    ��void
* @retval   ��uint8_t   1--KEY0  2--KEY1  3--KEY2  4--KEY_UP
* @details  ��
*            KEY0��KEY1 �͵�ƽ���£��ߵ�ƽ̧��
*            KEY_UP     �ߵ�ƽ���£��͵�ƽ̧��
* @fn       ��
************************************************************/
uint8_t KEY_Scan(void)
{
    uint8_t temp = 0;
    static uint8_t key_flay = 1;

    if(key_flay && ( KEY_UP==1 || KEY0==0 || KEY1==0 || KEY2==0))
    {
        delay_ms(10);
        if( KEY_UP==1 || KEY0==0 || KEY1==0 || KEY2==0)
        {
            key_flay = 0;
            if(KEY0==0)        temp = 1;
            else if(KEY1==0)   temp = 2;
            else if(KEY2==0)   temp = 3;
            else if(KEY_UP==1) temp = 4;
        }
    }

    if(KEY_UP==0 && KEY0==1 && KEY1==1 && KEY2==1)
    {
        key_flay = 1;
    }

    return temp;
}



