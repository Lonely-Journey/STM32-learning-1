#ifndef _IIC_H
#define _IIC_H

  #include "stm32f4xx.h"
  
  //SCL:
  #define SCL_H      (GPIOB->ODR |= (1<<8))    //ʱ��������
  #define SCL_L      (GPIOB->ODR &= ~(1<<8))   //ʱ��������
  //SDA
  //�����
  #define SDA_OUT_H  (GPIOB->ODR |= (1<<9))    //���ģʽ������������
  #define SDA_OUT_L  (GPIOB->ODR &= ~(1<<9))   //���ģʽ������������
  //���룺
  #define SDA_IN     (GPIOB->ODR |= (1<<9))    //����ģʽ
  #define SDA_INT    (GPIOB->IDR & (1<<9))     //���յ���ֵ

  void IIC_Init(void);
  void IIC_Start(void);
  void IIC_Stop(void);
  void IIC_Send_Ack(u8 ack);
  u8 IIC_Receive_Ack(void);
  void IIC_Send_Byte(u8 data);
  u8 IIC_Receive_Byte(void);
  
#endif





