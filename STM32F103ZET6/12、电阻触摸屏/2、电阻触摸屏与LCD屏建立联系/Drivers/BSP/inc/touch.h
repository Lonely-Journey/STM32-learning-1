#ifndef _TOUCH_H
#define _TOUCH_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"
    #include "delay.h"



    /****************     �ṹ�嶨��     ****************/
    /* ���ڵ��败����x��y�����ȡ */
    typedef struct touch
    {
        uint16_t x;     /* ����x���� */
        uint16_t y;     /* ����y���� */
    }TOUCH_XY;

    /* ������������ */
    typedef struct
    {
        void (*init)(void);      /* ��ʼ�������������� */
        void (*adjust)(void);       /* ������У׼ */
        TOUCH_XY (*scan)(uint8_t);   /* ɨ�败����.0,��Ļɨ��;1,��������; */

        uint8_t comX;    /* ��ȡx��������ָ�� */
        uint8_t comY;    /* ��ȡy��������ָ�� */

        /* 5��У׼������У׼����(����������ҪУ׼) */
        float xfac;                 /* LCD�ʹ�����x����ı���ϵ�� */
        float yfac;                 /* LCD�ʹ�����y����ı���ϵ�� */
        short xc;                   /* LCD�ʹ�����x�����ƫ���� */
        short yc;                   /* LCD�ʹ�����x�����ƫ���� */

        /* �����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
         * b0:0, ����(�ʺ�����ΪX����,����ΪY�����TP)
         *    1, ����(�ʺ�����ΪY����,����ΪX�����TP)
         * b1~6: ����.
         * b7:0, ������
         *    1, ������
         */
        uint8_t touchtype;
    } _m_tp_dev;



    /********************   �궨��   ********************/
    /* Ƭѡ�� */
    #define T_CS_H    GPIOF->ODR |= (1<<11)      /* Ƭѡʧ�� */
    #define T_CS_L    GPIOF->ODR &= ~(1<<11)     /* Ƭѡʹ�� */
    /* ʱ���� */
    #define T_SCK_H   GPIOB->ODR |= (1<<1)
    #define T_SCK_L   GPIOB->ODR &= ~(1<<1)
    /* ����� */
    #define T_MOSI_H  GPIOF->ODR |= (1<<9)
    #define T_MOSI_L  GPIOF->ODR &= ~(1<<9)
    /* ������ */
    #define T_MISO    (GPIOB->IDR & (1<<2))
    /* �ʽӴ��� */
    #define T_PEN     (GPIOF->IDR >> 10 & 0x1)

    /* ָ��(���������) */
    #define TOUCH_X   0xD0    //��ȡx��������
    #define TOUCH_Y   0x90    //��ȡy��������
    
    /* ���败������оƬ ���ݲɼ� �˲��ò��� */
    #define TP_READ_TIMES   5       /* ��ȡ���� */
    #define TP_LOST_VAL     1       /* ����ֵ(Ҫ�����������Сֵ����) */
    
    /* �������ζ�ȡX,Y�������������������ֵ */
    #define TP_ERR_RANGE    50         /* ��Χ */

    /* У׼�������Χ */
    #define CORRECT_RANGE_MAX    1.03    /* ��Χ */
    #define CORRECT_RANGE_MIN    0.97    /* ��Χ */



    /****************    �����ⲿ����   *****************/
    extern _m_tp_dev tp_dev;        /* ������������touch.c���涨�� */



    /****************    �����ⲿ����   *****************/
    void Touch_IO_Init(void);                /* ���败�������ų�ʼ�� */
    uint16_t Touch_Data(uint8_t command);    /* ����败�����������ݲ����յ��败�������������� */
    TOUCH_XY Touch_Smoothing(void);          /* ���败���������˲����� */
    void LCD_Calibration_Cross(uint16_t x, uint16_t y, uint16_t color); /* ����У׼��ʮ����ʾ���� */
    void LCD_Touch_Calibration(void);        /* LCD�봥����������ϵ����ĻУ׼ */
    uint8_t Touch_Read_XY(TOUCH_XY* coord);  /* ��ȡ���败���������������� */
    TOUCH_XY Touch_Scan(uint8_t mode);       /* ��ȡ���败������������(�����������Ļ����) */
    void Touch_Init(void);                   /* ��������ʼ�� */

#endif







