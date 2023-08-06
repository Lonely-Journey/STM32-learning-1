#ifndef _LED_H
#define _LED_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"



    /********************   �궨��   ********************/
    #define LED0_ON  GPIOB->ODR &= ~(1<<5)
    #define LED1_ON  GPIOE->ODR &= ~(1<<5)
    #define LED0_OFF GPIOB->ODR |= (1<<5)
    #define LED1_OFF GPIOE->ODR |= (1<<5)



    /****************    �����ⲿ����   *****************/
    void LED_Init(void);     /* LED��ʼ�� */ 

#endif









