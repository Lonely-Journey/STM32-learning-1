#ifndef _IWDG_H
#define _IWDG_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"



    /****************    �����ⲿ����   *****************/
    void IWDG_Init(uint8_t prer, uint16_t rlr);      /* �������Ź���ʼ�� */
    void IWDG_Feed(void);                            /* ι�� */

#endif






