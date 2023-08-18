#ifndef _BEEP_H
#define _BEEP_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"



    /********************   �궨��   ********************/
    #define BEEP_ON  GPIOB->ODR |= (1<<8)        /* �������� */
    #define BEEP_OFF GPIOB->ODR &= ~(1<<8)       /* �ط����� */



    /****************    �����ⲿ����   *****************/
    void BEEP_Init(void);       /* BEEP��ʼ�� */

#endif










