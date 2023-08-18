#ifndef __TOUCH_H
#define __TOUCH_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"
    #include "delay.h"



    /********************   �궨��   ********************/
    /* Ƭѡ�� */
    #define T_CS_H    GPIOF->ODR |= (1<<11)      /* Ƭѡʧ�� */
    #define T_CS_L    GPIOF->ODR &= ~(1<<11)     /* Ƭѡʹ�� */
    /* ʱ���� */
    #define T_SCK_H   GPIOB->ODR |= (1<<1)
    #define T_SCK_L   GPIOB->ODR &= ~(1<<1)
    /* ����� */
    #define T_MOSI_H  GPIOF->ODR |= (1<<9)
    #define T_MOSI_L  GPIOF->ODR &= ~(1<<9)
    /* ������ */
    #define T_MISO    (GPIOB->IDR & (1<<2))
    /* �ʽӴ��� */
    #define T_PEN     (GPIOF->IDR >> 10 & 0x1)

    /* ָ�� */
    #define TOUCH_X   0xD0    //��ȡx��������
    #define TOUCH_Y   0x90    //��ȡy��������



    /****************    �����ⲿ����   *****************/
    void Touch_IO_Init(void);                /* ���败�������ų�ʼ�� */
    uint16_t Touch_Data(uint8_t command);    /* ����败�����������ݲ����յ��败�������������� */

#endif







