#ifndef _KEY_H
#define _KEY_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"



    /********************   �궨��   ********************/
    #define KEY0    ((GPIOE->IDR>>4) & 0x1)         /* �͵�ƽ���� */
    #define KEY1    ((GPIOE->IDR>>3) & 0x1)         /* �͵�ƽ���� */
    #define KEY_UP  ((GPIOA->IDR>>0) & 0x1)         /* �ߵ�ƽ���� */



    /****************    �����ⲿ����   *****************/
    void KEY_Init(void);         /* ������ʼ�� */
    uint8_t KEY_Scan(void);      /* ����ɨ�躯�� */

#endif








