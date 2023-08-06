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
*            CS     PC13  �������
*            SCK    PB0   �������
*            PEN    PB1   ͨ������
*            MISO   PB2   ͨ������
*            MOSI   PF11  �������
* @fn       ��
************************************************************/
void Touch_IO_Init(void)
{
    /* PB */
    /* GPIOxʱ��ʹ�� */
    RCC->AHB1ENR |= 1<<1;
    /* �˿�ģʽ�Ĵ��� */
    GPIOB->MODER &= ~((3<<(2*0))|(3<<(2*1))|(3<<(2*2)));   /* PB1/PB2 ���� */
    GPIOB->MODER |= 1<<(2*0);                              /* PB0��� */
    /* �˿�������ͼĴ��� */
    GPIOB->OTYPER &= ~(1<<0);                              /* PB0���� */
    /* �˿�����ٶȼĴ��� */
    GPIOB->OSPEEDR &= ~(3<<(2*0));
    GPIOB->OSPEEDR |= (2<<(2*0));
    /* �˿�����/�����Ĵ��� */
    GPIOB->PUPDR &= ~((3<<(2*1))|(3<<(2*2)));              /* PB1/PB2�������� */

    /* PC */
    /* GPIOxʱ��ʹ�� */
    RCC->AHB1ENR |= (1<<2);
    /* �˿�ģʽ�Ĵ��� */
    GPIOC->MODER &= ~(3<<(2*13));
    GPIOC->MODER |= (1<<(2*13));                           /* ��� */
    /* �˿�������ͼĴ��� */
    GPIOC->OTYPER &= ~(1<<13);                             /* ���� */
    /* �˿�����ٶȼĴ��� */
    GPIOC->OSPEEDR &= ~(3<<(2*13));
    GPIOC->OSPEEDR |= (2<<(2*13));

    /* PF */
    /* GPIOxʱ��ʹ�� */
    RCC->AHB1ENR |= (1<<5);
    /* �˿�ģʽ�Ĵ��� */
    GPIOF->MODER &= ~(3<<(2*11));
    GPIOF->MODER |= (1<<(2*11));                           /* ��� */
    /* �˿�������ͼĴ��� */
    GPIOF->OTYPER &= ~(1<<11);                             /* ���� */
    /* �˿�����ٶȼĴ��� */
    GPIOF->OSPEEDR &= ~(3<<(2*11));
    GPIOF->OSPEEDR |= (2<<(2*11));

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



