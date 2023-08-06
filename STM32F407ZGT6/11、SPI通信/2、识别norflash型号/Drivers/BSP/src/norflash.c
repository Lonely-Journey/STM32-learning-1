#include "norflash.h"
#include "spi.h"



/**
******************************************************************************
* @file      ��.\Drivers\BSP\src\w25q128.c
*              .\Drivers\BSP\inc\w25q128.h
* @author    ��XRbin
* @version   ��V1.0
* @date      ��2023-07-01
* @brief     ��w25q128��д��������
******************************************************************************
* @attention
*   �ҵ�GitHub   ��https://github.com/XR-bin
*   �ҵ�gitee    ��https://gitee.com/xrbin
*   �ҵ�leetcode ��https://leetcode.cn/u/xrbin/
******************************************************************************
*/



/***
*W25Q128�洢оƬ
*������С             ��16Mbyte == 128Mbit
*���п���             ��256��
*ÿ������������       ��16����
*ÿ��������ҳ         ��16ҳ
*ÿҳ�ֽ�             ��256�ֽ�
*��ַ��д���ʮ����������0x9fffff
*        9f:����   f������    f��ҳ    ff���ֽ�
*/



/**********************************************************
* @funcName ��W25Q128_Init
* @brief    ��W25Q128��ʼ��
* @param    ��void
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void NorFlash_Init(void)
{
    /* Ƭѡ���� */
    /* GPIOxʱ�� */
    RCC->AHB1ENR |= (1<<1);
    /* �˿�ģʽ�Ĵ���PB14 */
    GPIOB->MODER &= ~(3<<2*14);
    GPIOB->MODER |= (1<<2*14);         /* ͨ����� */
    /* �˿�������ͼĴ��� */
    GPIOB->OTYPER &= ~(1<<14);         /* ���� */
    //�˿�����ٶȼĴ���
    GPIOB->OSPEEDR &= ~(3<<2*14);
    GPIOB->OSPEEDR |= (2<<2*14);
    //�˿�������ݼĴ���(Ƭѡ����)
    GPIOB->ODR |= (1<<14);

    SPI1_Init();                       /* SPI��ʼ�� */
}



/**********************************************************
* @funcName ��NorFlash_Read_ID
* @brief    ����ȡnorflashоƬ��ID
* @param    ��void
* @retval   ��uint16_t -- ����оƬID
* @details  ��
* @fn       ��
************************************************************/
uint16_t NorFlash_Read_ID(void)
{
    uint16_t id;

    SPI_CS_L;                               /* Ƭѡʹ�� */
    SPI1_RS_Byte(FLASH_ManufactDeviceID);   /* ���Ͷ� ID ���� */
    SPI1_RS_Byte(0);                        /* д��һ���ֽ� */
    SPI1_RS_Byte(0);
    SPI1_RS_Byte(0);
    id =  SPI1_RS_Byte(0xFF) << 8;          /* ��ȡ��8λ�ֽ� */
    id |= SPI1_RS_Byte(0xFF);               /* ��ȡ��8λ�ֽ� */
    SPI_CS_H;                               /* Ƭѡʧ�� */

    /* оƬID�б�ο�norfalsh.h��ĺ궨�� */
    printf("оƬID : %x\r\n", id);

    return id;
}



