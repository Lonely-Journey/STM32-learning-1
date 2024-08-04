#ifndef __KEY_H
#define __KEY_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"
    #include "delay.h"



    /********************   �궨��   ********************/
    #define KEY0    ((GPIOE->IDR>>4) & 0x1)         /* �͵�ƽ���� */
    #define KEY1    ((GPIOE->IDR>>3) & 0x1)         /* �͵�ƽ���� */
    #define KEY2    ((GPIOE->IDR>>2) & 0x1)         /* �͵�ƽ���� */
    #define KEY_UP  ((GPIOA->IDR>>0) & 0x1)         /* �ߵ�ƽ���� */



    /****************    �����ⲿ����   *****************/
    void KEY_Init(void);         /* ������ʼ�� */
    uint8_t KEY_Scan(void);      /* ����ɨ�躯�� */

#endif




