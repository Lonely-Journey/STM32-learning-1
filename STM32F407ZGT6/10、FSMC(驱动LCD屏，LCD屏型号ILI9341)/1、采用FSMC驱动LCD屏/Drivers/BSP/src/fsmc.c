#include "fsmc.h"



/**
******************************************************************************
* @file      ��.\Drivers\BSP\src\fsmc.c
*              .\Drivers\BSP\inc\fsmc.h
* @author    ��XRbin
* @version   ��V1.0
* @date      ��2023-07-01
* @brief     ��FSMC���ô���
******************************************************************************
* @attention
*   �ҵ�GitHub   ��https://github.com/XR-bin
*   �ҵ�gitee    ��https://gitee.com/xrbin
*   �ҵ�leetcode ��https://leetcode.cn/u/xrbin/
******************************************************************************
*/



/**********************************************************
* @funcName ��MyGPIO_AF_Set
* @brief    �������������ź���
* @param    ��GPIO_TypeDef* GPIOx (������)
* @param    ��uint32_t BITx       (��Ҫ���õ�����)
* @param    ��uint8_t AFx         (���ŷ���)
* @retval   ��void
* @details  ��
* @fn       ��
*            �ú���������������ͬһ��GPIO������
************************************************************/
void MyGPIO_AF_Set(GPIO_TypeDef* GPIOx, uint32_t BITx, uint8_t AFx)
{
    uint8_t pos;
    uint8_t i;
    for(i=0;i<16;i++)
    {
        pos = i;
        if((1<<pos)&BITx)  /* �жϸ������Ƿ�Ҫ���� */
        {
            /* pos>>3�������ж��Ǹ�λ���Ż��ǵ�λ���� */
            GPIOx->AFR[pos>>3]&=~(0X0F<<((pos&0X07)*4));
            GPIOx->AFR[pos>>3]|=(uint32_t)AFx<<((pos&0X07)*4);
        }
    }
}



/**********************************************************
* @funcName ��FSMC_LCD_Init
* @brief    ����LCD��Ӧ��GPIO�ڽ��г�ʼ������,���ض���GPIO�ڽ���FSMC����
* @param    ��void
* @retval   ��void
* @details  ��
*     �����ߣ�
*           DO0---PD14    DO1---PD15    DO2---PD0    DO3---PD1
*           DO4---PE7     DO5---PE8     DO6---PE9    DO7---PE10
*           DO8---PE11    DO9---PE12    DO10---PE13  DO11---PE14
*           DO12---PE15   DO13---PD8    DO14---PD9   DO15---PD10
*
*     �����ߣ� ͨ�����   ����   �ٶ�50M
*           WR---PD5    RD---PD4    CS---PG12
*           RS/DC(����/����)---PF12
*           BL�����⣩--PB15
*     ����
*         PB��15
*         PD��0-1   4-5   8-10   14-15
*         PE��7-15
*         PF��12
*         PG��12
*
*     ��Ҫ���õ���FSMC��Bank1������4
* @fn       ��
************************************************************/
void FSMC_LCD_Init(void)
{
    /* GPIOxʱ��ʹ�� */
    RCC->AHB1ENR |= ((1<<1)|(0xf<<3));
    /* ʹ��FSMCʱ�� */
    RCC->AHB3ENR|=1<<0;

    /* PB��   PB��15 */
    /* �˿�ģʽ�Ĵ��� */
    GPIOB->MODER &= ~(0xc0000000);
    GPIOB->MODER |= (0x40000000);      /* ��� */
    /* �˿�������ͼĴ��� */
    GPIOB->OTYPER &= ~(1<<15);         /* ���� */
    /* �˿�����ٶȼĴ��� */
    GPIOB->OSPEEDR |= (0xc0000000);

    /* PD��   PD��0-1   4-5   8-10   14-15 */
    /* ���ø������ */
    /* �˿�ģʽ�Ĵ��� */
    GPIOD->MODER &= ~(0xf03f0f0f);
    GPIOD->MODER |= (0xa02a0a0a);      /* ������� */
    /* �˿�������ͼĴ��� */
    GPIOD->OTYPER &= ~(0xc733);        /* ���� */
    /* �˿�����ٶȼĴ��� */
    GPIOD->OSPEEDR |= (0xf03f0f0f);
    /* �˿ڸ��üĴ���    ���� */
    MyGPIO_AF_Set(GPIOD,0xc733,12);

    /* PE��   PE��7-15 */
    /* ���ø������ */
    /* �˿�ģʽ�Ĵ��� */
    GPIOE->MODER &= ~(0xffffc000);
    GPIOE->MODER |= (0xaaaa8000);      /* ������� */
    /* �˿�������ͼĴ��� */
    GPIOE->OTYPER &= ~(0xff80);        /* ���� */
    /* �˿�����ٶȼĴ��� */
    GPIOE->OSPEEDR |= (0xffffc000);
    /* �˿ڸ��üĴ���    ���� */
    MyGPIO_AF_Set(GPIOE,0xff80,12);

    /* PF��   PF��12 */
    /* ���ø������ */
    /* �˿�ģʽ�Ĵ��� */
    GPIOF->MODER &= ~(3<<2*12);
    GPIOF->MODER |= (2<<2*12);         /* ������� */
    /* �˿�������ͼĴ��� */
    GPIOF ->OTYPER &= ~(1<<12);        /* ���� */
    /* �˿�����ٶȼĴ��� */
    GPIOF->OSPEEDR |= (3<<2*12);
    /* �˿ڸ��üĴ��� */
    GPIOF->AFR[1] &= ~(0xf<<(4*(12-8)));
    GPIOF->AFR[1] |= (12<<(4*(12-8)));

    /* PG��   PG��12 */
    /* ���ø������ */
    /* �˿�ģʽ�Ĵ��� */
    GPIOG->MODER &= ~(3<<2*12);
    GPIOG->MODER |= (2<<2*12);         /* ������� */
    /* �˿�������ͼĴ��� */
    GPIOG->OTYPER &= ~(1<<12);         /* ���� */
    /* �˿�����ٶȼĴ��� */
    GPIOG->OSPEEDR |= (3<<2*12);
    /* �˿ڸ��üĴ��� */
    GPIOG->AFR[1] &= ~(0xf<<(4*(12-8)));
    GPIOG->AFR[1] |= (12<<(4*(12-8)));

    /********** �ر��� **********/
    GPIOB->ODR &= ~(1<<15);

    /***************FSMC�Ĵ�������***************/
    /***
    * ע�⣺bank1��NE1~4,ÿһ��������һ��BCR+TCR+BWTR�������ܹ�12���Ĵ�����
    *
    *      FSMC_BCRx �� FSMC_BTRx����ϳ� BTCR[8]�Ĵ����飬���ǵĶ�Ӧ��ϵ���£�
    *      BTCR[0]��Ӧ FSMC_BCR1��BTCR[1]��Ӧ FSMC_BTR1
    *      BTCR[2]��Ӧ FSMC_BCR2��BTCR[3]��Ӧ FSMC_BTR2
    *      BTCR[4]��Ӧ FSMC_BCR3��BTCR[5]��Ӧ FSMC_BTR3
    *      BTCR[6]��Ӧ FSMC_BCR4��BTCR[7]��Ӧ FSMC_BTR4
    *
    *      FSMC_BWTRx ����ϳ� BWTR[7]�����ǵĶ�Ӧ��ϵ���£�
    *      BWTR[0]��Ӧ FSMC_BWTR1��BWTR[2]��Ӧ FSMC_BWTR2��
    *      BWTR[4]��Ӧ FSMC_BWTR3��BWTR[6]��Ӧ FSMC_BWTR4��
    *      BWTR[1]��BWTR[3]�� BWTR[5]������û���õ���
    */
    /* LED�õ���Bank1������4 */
    /* ��������ʹ��NE4 ��Ҳ�Ͷ�ӦBTCR[6],[7] */
    /* ������� */
    FSMC_Bank1->BTCR[6]=0X00000000;
    FSMC_Bank1->BTCR[7]=0X00000000;
    FSMC_Bank1E->BWTR[6]=0X00000000;
    /* SRAM/NOR-Flash Ƭѡ���ƼĴ��� */
    FSMC_Bank1->BTCR[6] |= 1<<14;       /* ��дʹ�ò�ͬ��ʱ�� */
    FSMC_Bank1->BTCR[6] |= 1<<12;       /* �ڴ洢������ʹ����д����� */
    FSMC_Bank1->BTCR[6] |= 1<<4;        /* �����ⲿ�洢���������Ϊ16 */
    FSMC_Bank1->BTCR[6] &= ~(1<<1);     /* ��ַ/�����߲����� */
    /* SRAM/NOR-Flash Ƭѡʱ��Ĵ��� ����ʱ����ƼĴ�����*/
    FSMC_Bank1->BTCR[7] &= ~(3<<28);    /* ����ģʽ A */
    FSMC_Bank1->BTCR[7] |= 0X3C<<8;     /* ���ݽ׶εĳ���ʱ��60��HCLKʱ������ */
    FSMC_Bank1->BTCR[7] &= ~(0xF<<4);   /* ��ַ���ֽ׶εĳ���ʱ��1��HCLK ʱ������ */
    FSMC_Bank1->BTCR[7] |= (0xF<<0);    /* ��ַ���ý׶εĳ���ʱ��15��HCLK ʱ������ */
    /* SRAM/NOR-Flash д��ʱ��Ĵ���   (дʱ����ƼĴ���) */
    FSMC_Bank1E->BWTR[6] &= ~(3<<28);   /* ģʽA */
    FSMC_Bank1E->BWTR[6] |= 0x8<<8;     /* ���ݽ׶εĳ���ʱ��8��HCLKʱ������ */
    FSMC_Bank1E->BWTR[6] &= ~(0xF<<4);  /* ��ַ���ֽ׶εĳ���ʱ��1��HCLK ʱ������ */
    FSMC_Bank1E->BWTR[6] |= (0x9<<0);   /* ��ַ���ý׶εĳ���ʱ��9��HCLK ʱ������ */

    /* ʹ��BANK1,����4 */
    FSMC_Bank1->BTCR[6]|=1<<0;
}




