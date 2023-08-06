#ifndef _BEEP_H
#define _BEEP_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"



    /********************   �궨��   ********************/
    #define BEEP_ON  GPIOF->ODR |= (1<<8)
    #define BEEP_OFF GPIOF->ODR &= ~(1<<8)



    /****************    �����ⲿ����   *****************/
    void BEEP_Init(void);       /* BEEP��ʼ�� */

#endif

