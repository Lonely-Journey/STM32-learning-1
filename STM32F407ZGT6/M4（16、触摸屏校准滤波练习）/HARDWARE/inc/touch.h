#ifndef _TOUCH_H
#define _TOUCH_H

  #include "stm32f4xx.h"  
  
  //������ͨ�Ĵ�����x��y�����ȡ
  typedef struct touch
  {
    u16 x;
    u16 y;
  }TOUCH_XY;
 //���ڽ���LCD�ʹ������Ĺ�ϵ��
 typedef struct adjust
 {
   float a_x;  //lcd �� ������ x����ı���ϵ��
   signed short b_x;    //lcd �� ������ x�����ƫ����
   float c_y;  //lcd �� ������ y����ı���ϵ��
   signed short d_y;    //lcd �� ������ y�����ƫ����
 }ADJUST;
 
  //Ƭѡ��
  #define T_CS_H    GPIOC->ODR |= (1<<13)
  #define T_CS_L    GPIOC->ODR &= ~(1<<13)
  //ʱ����
  #define T_SCK_H   GPIOB->ODR |= (1<<0)
  #define T_SCK_L   GPIOB->ODR &= ~(1<<0)
  //�����
  #define T_MOSI_H  GPIOF->ODR |= (1<<11)
  #define T_MOSI_L  GPIOF->ODR &= ~(1<<11)
  //������
  #define T_MISO    (GPIOB->IDR & (1<<2))
  //�ʽӴ���
  #define T_PEN     (GPIOB->IDR & (1<<1))
  
  //ָ��
  #define TOUCH_X   0xD0    //��ȡx��������
  #define TOUCH_Y   0x90    //��ȡy��������
  
  void Touch_Init(void);
  u16 Touch_Data(u8 command);
  TOUCH_XY Touch_Smoothing(void);
  void LCD_Calibration_Cross(u16 x,u16 y,u16 colour);
  void LCD_Touch_Calibration(void);
  TOUCH_XY LCD_Touch_Transition(void);
	
#endif




