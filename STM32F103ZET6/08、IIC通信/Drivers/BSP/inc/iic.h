#ifndef __IIC_H
#define __IIC_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"
    #include "delay.h"



    /********************   �궨��   ********************/
    /* SCL */
    #define SCL_H      (GPIOB->ODR |= (1<<6))    /* ʱ�������� */
    #define SCL_L      (GPIOB->ODR &= ~(1<<6))   /* ʱ�������� */

    /* SDA */
    /* ����� */
    #define SDA_OUT_H  (GPIOB->ODR |= (1<<7))    /* ���ģʽ������������ */
    #define SDA_OUT_L  (GPIOB->ODR &= ~(1<<7))   /* ���ģʽ������������ */
    /* ���룺 */
    #define SDA_IN     (GPIOB->ODR |= (1<<7))    /* ����ģʽ */
    #define SDA_INT    (GPIOB->IDR & (1<<7))     /* ���յ���ֵ */



    /****************    �����ⲿ����   *****************/
    void IIC_Init(void);                /* IIC��ʼ�� */
    void IIC_Start(void);               /* IIC��ʼ�ź� */
    void IIC_Stop(void);                /* IICֹͣ�ź� */
    void IIC_Send_Ack(uint8_t ack);     /* IICӦ���ź� */
    uint8_t IIC_Receive_Ack(void);      /* ����IICӦ���ź� */
    void IIC_Send_Byte(uint8_t data);   /* ����һ���ֽ����� */
    uint8_t IIC_Receive_Byte(void);     /* ����һ���ֽ����� */

#endif











