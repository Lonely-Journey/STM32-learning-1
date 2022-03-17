#include "stm32f4xx.h"   
#include "lcd.h"
#include "fsmc.h"

/*************************** FSMC �� �� LCD ******************************/

/*****************************************************
*��������  �������������ź���
*������    ��MyGPIO_AF_Set
*��������  ��void
*��������ֵ��void
*����      ���ú���������������ͬһ��GPIO������
********************************************************/
void MyGPIO_AF_Set(GPIO_TypeDef* GPIOx,u32 BITx,u8 AFx)
{  
	u8 pos;
	u8 i;
	for(i=0;i<16;i++)
	{
		pos = i;
		if((1<<pos)&BITx)  //�жϸ������Ƿ�Ҫ����
		{
      //pos>>3�������ж��Ǹ�λ���Ż��ǵ�λ����
			GPIOx->AFR[pos>>3]&=~(0X0F<<((pos&0X07)*4));
			GPIOx->AFR[pos>>3]|=(u32)AFx<<((pos&0X07)*4);
		}
	}
}

/****************************************************************************
*��������  ����LCD��Ӧ��GPIO�ڽ��г�ʼ������,���ض���GPIO�ڽ���FSMC����
*������    ��FSMC_LCD_Init
*��������  ��void
*��������ֵ��void
*����      ��
*     �����ߣ�//���� ����   �ٶ�100M
*           DO0---PD14	DO1---PD15	DO2---PD0	DO3---PD1
*           DO4---PE7	DO5---PE8	DO6---PE9	DO7---PE10
*           DO8---PE11	DO9---PE12	DO10---PE13	DO11---PE14
*           DO12---PE15	DO13---PD8	DO14---PD9	DO15---PD10
*     �����ߣ�//����  ����      �ٶ�100M
*           WR---PD5	RD---PD4	CS---PG12 	
*           RS/DC(����/����)---PF12	 
*           BL�����⣩--PB15   
*     ����
*          PB��15
*          PD��0-1  4-5  8-10  14-15  
*          PE��7-15
*          PF��12
*          PG��12           
*     ��Ҫ���õ���FSMC��Bank1������4
***************************************************************************/
void FSMC_LCD_Init(void)
{
  /********* ����GPIO *********/
  //GPIOxʱ��ʹ��
  RCC->AHB1ENR |= ((1<<1)|(0xf<<3));
  
  //PB��
  //����ƣ�����ͨ�����
  //�˿�ģʽ�Ĵ���
  GPIOB->MODER &= ~(0xc0000000);
  GPIOB->MODER |= (0x40000000);
  //�˿�������ͼĴ���
  GPIOB->OTYPER &= ~(1<<15);
  //�˿�����ٶȼĴ���
  GPIOB->OSPEEDR |= (0x0c000000);
  
  //PD��
  //���ø������
  //�˿�ģʽ�Ĵ���
  GPIOD->MODER &= ~(0xf03f0f0f);
  GPIOD->MODER |= (0xa02a0a0a);
  //�˿�������ͼĴ���
  GPIOD->OTYPER &= ~(0xc733);
  //�˿�����ٶȼĴ���
  GPIOD->OSPEEDR |= (0xf03f0f0f);
  //�˿ڸ��üĴ���    ����
  MyGPIO_AF_Set(GPIOD,0xc733,12);
  
  //PE��
  //���ø������
  //�˿�ģʽ�Ĵ���
  GPIOE->MODER &= ~(0xffffc000);
  GPIOE->MODER |= (0xaaaa8000);
  //�˿�������ͼĴ���
  GPIOE->OTYPER &= ~(0xff80);
  //�˿�����ٶȼĴ���
  GPIOE->OSPEEDR |= (0xffffc000);
  //�˿ڸ��üĴ���    ����
  MyGPIO_AF_Set(GPIOE,0xff80,12);
  
  //PF��
  //���ø������
  //�˿�ģʽ�Ĵ���
  GPIOF->MODER &= ~(3<<2*12);
  GPIOF->MODER |= (2<<2*12);
  //�˿�������ͼĴ���
  GPIOF ->OTYPER &= ~(1<<12);
  //�˿�����ٶȼĴ���
  GPIOF->OSPEEDR |= (3<<2*12);
  //�˿ڸ��üĴ���
  GPIOF->AFR[1] &= ~(0xf<<(4*(12-8)));
  GPIOF->AFR[1] |= (12<<(4*(12-8)));

  
  //PG��
  //�˿�ģʽ�Ĵ���
  GPIOG->MODER &= ~(3<<2*12);
  GPIOG->MODER |= (2<<2*12);
  //�˿�������ͼĴ���
  GPIOG->OTYPER &= ~(1<<12);
  //�˿�����ٶȼĴ���
  GPIOG->OSPEEDR |= (3<<2*12);
  //�˿ڸ��üĴ���
  GPIOG->AFR[1] &= ~(0xf<<(4*(12-8)));
  GPIOG->AFR[1] |= (12<<(4*(12-8)));

  /********** �ر��� **********/
  LCD_BL_L; 
  
  /********* ����FSMC *********/
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

  //ʹ��FSMCʱ�� 
  RCC->AHB3ENR|=1<<0;    

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
  FSMC_Bank1->BTCR[7] |= 2<<0;     //��ַ���ý׶εĳ���ʱ��  2��HCLK ʱ������
  //SRAM/NOR-Flash д��ʱ��Ĵ���   (дʱ����ƼĴ���)
  FSMC_Bank1E->BWTR[6] |= 0<<28; 	//ģʽA
  FSMC_Bank1E->BWTR[6] |= 2<<8; 	//���ݽ׶εĳ���ʱ��Ϊ6ns*2��HCLK=12ns
  FSMC_Bank1E->BWTR[6] |= 0<<0;		//��ַ���ý׶εĳ���ʱ��Ϊ1��HCLK =6ns	
  
  //ʹ��BANK1,����4
  FSMC_Bank1->BTCR[6]|=1<<0;
}




/***************************FSMC �� �� �ⲿSRAN******************************/
/************************************************************************
*��������  �����ض���GPIO�ڽ���FSMC���ã�������FSMC�����������ⲿSRAN
*������    ��FSMC_SRAM_Init
*��������  ��void
*��������ֵ��void
*��������  ��
*     ��Ҫ���õ����ţ� 
*                   PD��0/1/4/5/8/9/10/11/12/13/14/15 
*                   PE��0/1/7/8/9/10/11/12/13/14/15
*                   PF��0/1/2/3/4/5/12/13/14/15
*                   PG��0/1/2/3/4/5/10
*              ��Ҫ���õ���FSMC��Bank1������3
*************************************************************************/
void FSMC_SRAM_Init(void)
{
  /********* ����GPIO *********/
  //GPIOxʱ��ʹ��
  RCC->AHB1ENR |= (0xf<<3);
  
  //�ر�ע�⣡��������
  //PG10,AF12(CS�ŵ���ǰ��,��ֹ��λ��CS�Ƿ����,�ƻ�ԭ������)
  GPIOG->AFR[1] &= ~(0xf<<(4*(10-8)));
  GPIOG->AFR[1] |= (12<<(4*(10-8)));
  
  //PD��
  //���ø������
  //�˿�ģʽ�Ĵ���
  GPIOD->MODER &= ~(0xffff0f0f);
  GPIOD->MODER |= (0xaaaa0a0a);
  //�˿�������ͼĴ���
  GPIOD->OTYPER &= ~(0xff33);
  //�˿�����ٶȼĴ���
  GPIOD->OSPEEDR |= (0xffff0f0f);
  //�˿ڸ��üĴ���    ����
  MyGPIO_AF_Set(GPIOD,0xff33,12);
  
  //PE��
  //���ø������
  //�˿�ģʽ�Ĵ���
  GPIOE->MODER &= ~(0xffffc00f);
  GPIOE->MODER |= (0xaaaa800a);
  //�˿�������ͼĴ���
  GPIOE->OTYPER &= ~(0xff83);
  //�˿�����ٶȼĴ���
  GPIOE->OSPEEDR |= (0xffffc00f);
  //�˿ڸ��üĴ���    ����
  MyGPIO_AF_Set(GPIOE,0xff83,12);
  
  //PF��
  //���ø������
  //�˿�ģʽ�Ĵ���
  GPIOF->MODER &= ~(0xff000fff);
  GPIOF->MODER |= (0xaa000aaa);
  //�˿�������ͼĴ���
  GPIOF ->OTYPER &= ~(0xf03f);
  //�˿�����ٶȼĴ���
  GPIOF->OSPEEDR |= (0xff000fff);
  //�˿ڸ��üĴ���
  MyGPIO_AF_Set(GPIOF,0xf03f,12);

  
  //PG��
  //�˿�ģʽ�Ĵ���
  GPIOG->MODER &= ~(0x00300fff);
  GPIOG->MODER |= (0x00200aaa);
  //�˿�������ͼĴ���
  GPIOG->OTYPER &= ~(0x043f);
  //�˿�����ٶȼĴ���
  GPIOG->OSPEEDR |= (0x00300fff);
  //�˿ڸ��üĴ���
  MyGPIO_AF_Set(GPIOG,0x003f,12);
  
    /********* ����FSMC *********/
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

  //ʹ��FSMCʱ�� 
  RCC->AHB3ENR|=1<<0;    

  /*LED�õ���Bank1������3*/
  //��������ʹ��NE3 ��Ҳ�Ͷ�ӦBTCR[4],[5]��				    
	FSMC_Bank1->BTCR[4]=0X00000000;
	FSMC_Bank1->BTCR[5]=0X00000000;
	FSMC_Bank1E->BWTR[4]=0x0FFFFFFF;
  //SRAM/NOR-Flash Ƭѡ���ƼĴ���
  FSMC_Bank1->BTCR[4] &= ~(1<<14);   //��дʹ��ͳһ��ʱ�� 
  FSMC_Bank1->BTCR[4] |= 1<<12;      //�ڴ洢������ʹ����д�����
  FSMC_Bank1->BTCR[4] &= ~(3<<4);
  FSMC_Bank1->BTCR[4] |= (1<<4);    //�����ⲿ�洢���������Ϊ16
  //SRAM/NOR-Flash Ƭѡʱ��Ĵ��� ����ʱ����ƼĴ�����
  FSMC_Bank1->BTCR[5] &= ~(3<<28);   //����ģʽ A
  FSMC_Bank1->BTCR[5] |= 5<<8;       //���ݽ׶εĳ���ʱ��  2��HCLKʱ������
  FSMC_Bank1->BTCR[5] |= 2<<0;       //��ַ���ý׶εĳ���ʱ��  2��HCLKʱ������
  //SRAM/NOR-Flash д��ʱ��Ĵ���   (дʱ����ƼĴ���)
  FSMC_Bank1E->BWTR[4] &= ~(3<<28);    //ģʽA
  FSMC_Bank1E->BWTR[4] &= ~(0xf<<20);  //CLK �źŵ�ʱ�ӷ�Ƶ�ȱ��������� 
  FSMC_Bank1E->BWTR[4] |= (0x3<<16);   //������ת�׶εĳ���ʱ��3��HCLKʱ������
  FSMC_Bank1E->BWTR[4] |= (0x3<<8); 	 //���ݽ׶εĳ���ʱ��Ϊ6ns*3��HCLK=18ns
  FSMC_Bank1E->BWTR[4] &= ~(0xf<<4);   //��ַ���ֽ׶εĳ���ʱ�䱣��������
  FSMC_Bank1E->BWTR[4] |= (0x2<<0);		 //��ַ���ý׶εĳ���ʱ��Ϊ2��HCLK =12ns	
  
  //ʹ��BANK1,����3
  FSMC_Bank1->BTCR[4]|=1<<0;

}






