#ifndef __BEEP_H
#define __BEEP_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"



    /********************   �궨��   ********************/
    #define BEEP_ON  GPIOF->ODR |= (1<<8)      /* �������� */
    #define BEEP_OFF GPIOF->ODR &= ~(1<<8)     /* �ط����� */



    /****************    �����ⲿ����   *****************/
    void BEEP_Init(void);       /* BEEP��ʼ�� */

#endif

