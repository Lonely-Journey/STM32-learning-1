#ifndef _TOUCH_H
#define _TOUCH_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"
    #include "delay.h"



    /********************   �궨��   ********************/
    /* Ƭѡ�� */
    #define T_CS_H    GPIOC->ODR |= (1<<13)      /* Ƭѡʧ�� */
    #define T_CS_L    GPIOC->ODR &= ~(1<<13)     /* Ƭѡʹ�� */
    /* ʱ���� */
    #define T_SCK_H   GPIOB->ODR |= (1<<0)
    #define T_SCK_L   GPIOB->ODR &= ~(1<<0)
    /* ����� */
    #define T_MOSI_H  GPIOF->ODR |= (1<<11)
    #define T_MOSI_L  GPIOF->ODR &= ~(1<<11)
    /* ������ */
    #define T_MISO    (GPIOB->IDR & (1<<2))
    /* �ʽӴ��� */
    #define T_PEN     (GPIOB->IDR >> 1 & 0x1)

    /* ָ�� */
    #define TOUCH_X   0xD0    //��ȡx��������
    #define TOUCH_Y   0x90    //��ȡy��������



    /****************    �����ⲿ����   *****************/
    void Touch_IO_Init(void);                /* ���败�������ų�ʼ�� */
    uint16_t Touch_Data(uint8_t command);    /* ����败�����������ݲ����յ��败�������������� */

#endif



