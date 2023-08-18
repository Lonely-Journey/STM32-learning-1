#ifndef __LED_H
#define __LED_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"



    /********************   �궨��   ********************/
    /* ���� */
    #define LED0_ON GPIOF->ODR &= ~(1<<9)
    #define LED1_ON GPIOF->ODR &= ~(1<<10)
    /* �ص� */
    #define LED0_OFF GPIOF->ODR |= (1<<9)
    #define LED1_OFF GPIOF->ODR |= (1<<10)



    /****************    �����ⲿ����   *****************/
    void LED_Init(void);         /* LED��ʼ�� */

#endif








