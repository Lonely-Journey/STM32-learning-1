#ifndef _WWDG_H
#define _WWDG_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"



    /****************    �����ⲿ����   *****************/
    void WWDG_Init(uint8_t tr, uint8_t wr, uint8_t fprer); /* ��ʼ�����ڿ��Ź� */
    void WWDG_Set_Counter(uint8_t cnt);                    /* ������WWDG��������ֵ */

#endif




