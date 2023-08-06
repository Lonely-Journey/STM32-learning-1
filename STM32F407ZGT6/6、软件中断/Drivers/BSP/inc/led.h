#ifndef _LED_H
#define _LED_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"



    /********************   �궨��   ********************/
    /* ���ƺ궨�� */
    #define LED1_ON GPIOF->ODR &= ~(1<<9)
    #define LED2_ON GPIOF->ODR &= ~(1<<10)
    /* �صƺ궨�� */
    #define LED1_OFF GPIOF->ODR |= (1<<9)
    #define LED2_OFF GPIOF->ODR |= (1<<10)



    /****************    �����ⲿ����   *****************/
    void LED_Init(void);         /* LED��ʼ�� */

#endif








