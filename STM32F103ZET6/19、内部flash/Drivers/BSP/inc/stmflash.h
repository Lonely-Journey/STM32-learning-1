#ifndef __STMFLASH_H
#define __STMFLASH_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"



    /********************   �궨��   ********************/
    /* FLASH��ʼ��ַ */
    #define STM32_FLASH_SIZE        0x80000         /* STM32 FLASH �ܴ�С */
    #define STM32_FLASH_BASE        0x08000000      /* STM32 FLASH ��ʼ��ַ */

    /* STM32F103 ������С */
    #if STM32_FLASH_SIZE < 256 * 1024
        #define STM32_SECTOR_SIZE   1024           /* ����С��256K�� F103, ������СΪ1K�ֽ� */
    #else
        #define STM32_SECTOR_SIZE   2048           /* �������ڵ�����256K�� F103, ������СΪ2K�ֽ� */
    #endif

    /* FLASH������ֵ */
    #define STM32_FLASH_KEY1        0X45670123
    #define STM32_FLASH_KEY2        0XCDEF89AB



    /****************    �����ⲿ����   *****************/
    static void STMFLASH_Unlock(void);                     /* �ڲ�flash���� */
    static void STMFLASH_Lock(void);                       /* �ڲ�flash���� */
    static uint8_t STMFLASH_Get_Status(void);              /* ��ȡ�ڲ�flash״̬ */
    static uint8_t STMFLASH_Wait_Done(uint32_t time);      /* ��ʱ�ȴ���ȡ�ڲ�flash״̬ */
    static uint8_t STMFLASH_Erase_Sector(uint32_t saddr);  /* �ڲ�flash����ɾ�� */
    static uint8_t STMFLASH_Write_HalfWord(uint32_t faddr, uint16_t data);  /* ���ڲ�flashд��һ������ */
    

    uint16_t STMFLASH_Read_HalfWord(uint32_t faddr);                               /* ���ڲ�flash��ȡһ��uint16_t���� */
    void STMFLASH_Read(uint32_t rAddr, uint16_t *pBuf, uint16_t length);           /* ���ڲ�flash��ȡ���uint16_t���� */
    void STMFLASH_Write_NoCheck(uint32_t wAddr, uint16_t *pBuf, uint16_t length);  /* ���ڲ�flashд����uint16_t����(�������) */
    void STMFLASH_Write(uint32_t wAddr, uint16_t *pBuf, uint16_t length);          /* ���ڲ�flashд����uint16_t����(�д����) */

#endif





