#include "sys.h"
#include "lcd.h"
#include "fsmc.h"

/*************************** FSMC �� �� LCD ******************************/

/****************************************************************************
*��������  ����LCD��Ӧ��GPIO�ڽ��г�ʼ������,���ض���GPIO�ڽ���FSMC����
*������    ��FSMC_LCD_Init
*��������  ��void
*��������ֵ��void
*����      ��
*     �����ߣ�//ͨ����� ����      �ٶ�50M
*           DO0---PD14	DO1---PD15	DO2---PD0	DO3---PD1
*           DO4---PE7	DO5---PE8	DO6---PE9	DO7---PE10
*           DO8---PE11	DO9---PE12	DO10---PE13	DO11---PE14
*           DO12---PE15	DO13---PD8	DO14---PD9	DO15---PD10
*     �����ߣ�//ͨ�����  ����      �ٶ�50M
*           WR---PD5	RD---PD4	CS---PG12 	
*           RS/DC(����/����)---PG0	 
*           BL�����⣩--PB0   
*     ����
*         PB��0
*         PD��0-1  4-5  8-10  14-15  
*         PE��7-15
*         PG��0  12   
*     ��Ҫ���õ���FSMC��Bank1������4
***************************************************************************/
void FSMC_LCD_Init(void)
{
  /*ʹ��GPIOxʱ�Ӻ�FSMCʱ��*/
  //GPIOB��D��E��G
  RCC->APB2ENR |= ((1<<3)|(1<<5)|(1<<6)|(1<<8));
  //FSMC
  RCC->AHBENR |= 1<<8;
  
  /***************GPIOx�Ĵ�������***************/
  //PB
  //����ƣ�����ͨ�����
  //�˿����üĴ���
  GPIOB->CRL &= ~(0xf);
  GPIOB->CRL |= (0x3);
  
  //PD 
  //���ø������
  //�˿����üĴ���
  GPIOD->CRL &= ~(0x00ff00ff);
  GPIOD->CRH &= ~(0xff000fff);
  GPIOD->CRL |= (0x00bb00bb);
  GPIOD->CRH |= (0xbb000bbb);
  
  //PE
  //���ø������
  //�˿����üĴ���
  GPIOE->CRL &= ~(0xf0000000);
  GPIOE->CRH &= ~(0xffffffff);
  GPIOE->CRL |= (0xb0000000);
  GPIOE->CRH |= (0xbbbbbbbb);
  
  //PG
  //���ø������
  //�˿����üĴ���
  GPIOG->CRL &= ~(0xf);
  GPIOG->CRH &= ~(0x000f0000);
  GPIOG->CRL |= (0xb);
  GPIOG->CRH |= (0x000b0000);
  
  /********** �ر��� **********/
  LCD_BL_L; 
  
  /***************FSMC�Ĵ�������***************/
  
/***********************************************************************
*ע�⣺bank1��NE1~4,ÿһ��������һ��BCR+TCR+BWTR�������ܹ�12���Ĵ�����
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
*************************************************************************/
  /*LED�õ���Bank1������4*/
  //��������ʹ��NE4 ��Ҳ�Ͷ�ӦBTCR[6],[7]��
  //�������
  FSMC_Bank1->BTCR[6]=0X00000000;
	FSMC_Bank1->BTCR[7]=0X00000000;
	FSMC_Bank1E->BWTR[6]=0X00000000;
  //SRAM/NOR-Flash Ƭѡ���ƼĴ���
  FSMC_Bank1->BTCR[6] |= 1<<14;   //��дʹ�ò�ͬ��ʱ�� 
  FSMC_Bank1->BTCR[6] |= 1<<12;   //�ڴ洢������ʹ����д�����
  FSMC_Bank1->BTCR[6] &= ~(3<<4);
  FSMC_Bank1->BTCR[6] |= (1<<4);  //�����ⲿ�洢���������Ϊ16
  //SRAM/NOR-Flash Ƭѡʱ��Ĵ��� ����ʱ����ƼĴ�����
  FSMC_Bank1->BTCR[7] &= ~(3<<28); //����ģʽ A
  FSMC_Bank1->BTCR[7] |= 0XF<<8;   //���ݽ׶εĳ���ʱ��16��HCLKʱ������
  FSMC_Bank1->BTCR[7] |= 1<<0;     //��ַ���ý׶εĳ���ʱ��2��HCLK ʱ������
  //SRAM/NOR-Flash д��ʱ��Ĵ���   (дʱ����ƼĴ���)
  FSMC_Bank1E->BWTR[6] |= 0<<28; 	//ģʽA
  FSMC_Bank1E->BWTR[6] |= 2<<8; 	//���ݽ׶εĳ���ʱ��Ϊ6ns*2��HCLK=12ns
  FSMC_Bank1E->BWTR[6] |= 0<<0;		//��ַ���ý׶εĳ���ʱ��Ϊ1��HCLK =6ns
  
  //ʹ��BANK1,����4
  FSMC_Bank1->BTCR[6]|=1<<0;
}








