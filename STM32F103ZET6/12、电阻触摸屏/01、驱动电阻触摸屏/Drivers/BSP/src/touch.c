#include "touch.h"



/**
******************************************************************************
* @file      ��.\Drivers\BSP\src\touch.c
*              .\Drivers\BSP\inc\touch.h
* @author    ��XRbin
* @version   ��V1.0
* @date      ��2023-07-03
* @brief     �����败�����������úͲ�������
******************************************************************************
* @attention
*   �ҵ�GitHub   ��https://github.com/XR-bin
*   �ҵ�gitee    ��https://gitee.com/xrbin
*   �ҵ�leetcode ��https://leetcode.cn/u/xrbin/
******************************************************************************
*/



/**********************************************************
* @funcName ��Touch_IO_Init
* @brief    ���Ե��败����оƬ��Ӧ��GPIO�ڽ��г�ʼ������
* @param    ��void
* @retval   ��void
* @details  ��
*            CS     PF11  �������
*            SCK    PB1   �������
*            PEN    PF10  ͨ������
*            MISO   PB2   ͨ������
*            MOSI   PF9   �������
* @fn       ��
************************************************************/
void Touch_IO_Init(void)
{
    /* PB */
    /* GPIOxʱ��ʹ�� */
    RCC->APB2ENR |= 1<<3;
    /* �˿����üĴ��� */
    GPIOB->CRL &= ~((0xf<<(4*1))|(0xf<<(4*2)));
    GPIOB->CRL |= ((3<<(4*1))|(4<<(4*2)));

    /* PF */
    /* GPIOxʱ��ʹ�� */
    RCC->APB2ENR |= 1<<7;
    /* �˿����üĴ��� */
    GPIOF->CRH &= ~((0xf<<(4*(9-8)))|(0xf<<(4*(10-8)))|(0xf<<(4*(11-8))));
    GPIOF->CRH |= ((3<<(4*(9-8)))|(4<<(4*(10-8)))|(3<<(4*(11-8))));

    /* ��ʼ��״̬���� */
    T_CS_H;
    T_SCK_L;
    T_MOSI_L;
}



/**********************************************************
* @funcName ��Touch_Data
* @brief    ���Ե��败����оƬ��Ӧ��GPIO�ڽ��г�ʼ������
* @param    ��uint8_t command (ָ��)
* @retval   ��uint16_t
* @details  ��
*            Ƭѡ��        T_CS_H       T_CS_L  
*            ʱ����        T_SCK_H      T_SCK_L  
*            ���������    T_MOSI_H     T_MOSI_L
*            ����������    T_MISO
*            �ʽӴ���      T_PEN
* @fn       ��
************************************************************/
uint16_t Touch_Data(uint8_t command)
{
    uint8_t i;
    uint16_t data = 0;

    T_MOSI_L;            /* ���������� */
    T_CS_L;              /* Ƭѡʹ�� */

    for(i=0;i<8;i++)
    {
        T_SCK_L;             /* ʱ�������� */

        /* �ж�ָ��λ��ƽ */
        if(command & 0x80)T_MOSI_H;
        else T_MOSI_L;

        command <<= 1;  /* ָ���������� */

        T_SCK_H;          /* ʱ�������� */
        delay_us(1);      /* ��ʱ�����ڴӻ���ȡ���� */
    }
    T_SCK_L;            /* ʱ�������� */
    T_MOSI_L;           /* ���������� */
    delay_us(6);        /* ��ʱ6us�����ڵȴ�ADC������ת���� */

    /* �ճ�һ�������� */
    T_SCK_L;
    delay_us(1);
    T_SCK_H;
    delay_us(1);

    for(i=0;i<12;i++)
    {
        data <<= 1;              /* ָ���������� */
        T_SCK_L;                 /* ʱ�������� */
        delay_us(1);             /* ��ʱ���������ݽ��� */
        T_SCK_H;                 /* ʱ�������� */
        if(T_MISO) data |= 0x1;  /* ��ȡ����λ��ƽ */
        delay_us(1);             /* ��ʱ���������ݽ��� */
    }

    T_CS_H;    /* Ƭѡ���� */
    T_SCK_L;   /* ʱ�������� */

    return data;
}





