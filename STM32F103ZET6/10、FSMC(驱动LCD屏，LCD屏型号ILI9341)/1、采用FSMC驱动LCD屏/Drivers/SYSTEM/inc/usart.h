#ifndef __USART_H
#define __USART_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h" 
    #include "stdio.h"



    /****************    �����ⲿ����   *****************/
    /*����1*/
    void USART1_Init(uint32_t baud);          /* ����1��ʼ�� */
    void USART1_Send_Byte(uint8_t data);      /* ����1����һ���ֽ� */
    uint8_t USART1_Receive_Byte(void);        /* ����1����һ���ֽ� */
    void USART1_Send_Str(uint8_t *str);       /* ����1����һ���ַ��� */
    void USART1_Receive_Str(uint8_t *str);    /* ����1����һ���ַ��� */
    /*����2*/
    void USART2_Init(uint32_t baud);          /* ����2��ʼ�� */
    void USART2_Send_Byte(uint8_t data);      /* ����2����һ���ֽ� */
    uint8_t USART2_Receive_Byte(void);        /* ����2����һ���ֽ� */

#endif






