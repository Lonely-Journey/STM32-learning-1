#ifndef _DMA_H
#define _DMA_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"
    #include "delay.h"



    /****************    �����ⲿ����   *****************/
    void DMA2_Usart1_Init(uint8_t ch, uint8_t* data);   /* ��DMA2��ͨ��7���г�ʼ������(����USART1�ķ���ͨ��) */
    void DMA2_Enable(uint16_t ndtr);                    /* ����DMA2���ݴ��� */

#endif



