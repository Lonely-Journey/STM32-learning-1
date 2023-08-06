#include "adc.h"



/**
******************************************************************************
* @file      ��.\Drivers\BSP\src\adc.c
*              .\Drivers\BSP\inc\adc.h
* @author    ��XRbin
* @version   ��V1.0
* @date      ��2023-07-27
* @brief     ��ADC��оƬ�ڲ��¶ȴ���
******************************************************************************
* @attention
*   �ҵ�GitHub   ��https://github.com/XR-bin
*   �ҵ�gitee    ��https://gitee.com/xrbin
*   �ҵ�leetcode ��https://leetcode.cn/u/xrbin/
******************************************************************************
*/



/*****************************************
* F407��ADCʱ��Ƶ�ʹٷ�����: ������36Mhz
* F103��ADCʱ��Ƶ�ʹٷ�����: ������14Mhz
******************************************/



/**********************************************************
* @funcName ��ADC1_In16_Init
* @brief    ��ADC1�ĵ�16��ͨ����ʼ������
* @param    ��void
* @retval   ��void
* @details  ��
* @fn       ��
*            �������ţ����ڲ�оƬ�¶�
************************************************************/
void ADC1_In16_Init(void)
{
    /* ADCx�Ĵ������� */
    /* ADCxʱ��ʹ�� */
    RCC->APB2ENR |= 1<<8;                 /* ADC1 */

    /* ADCx���ƼĴ���1   CR1 */
    /* ����ģʽ */
    /* ��ֹ����ͨ���Ĳ���������ģʽ */
    /* ��ֹɨ��ģʽ */
    ADC1->CR1 = 0;

    /* ADCx���ƼĴ���2   CR2 */
    /* �Ҷ��� */
    /* ����ת��ģʽ */
    ADC1->CR2 = 0;
    ADC1->CR2 |= 1<<10;

    /* ADCx����ʱ��Ĵ� */
    ADC1->SMPR1 &= ~(7<<18);
    ADC1->SMPR1 |= (7<<18);      /* ADCx����ʱ��Ĵ�  ����ʱ��Ϊ239.5������ */

    /* ADCx�������мĴ��� */
    ADC1->SQR1 &= ~(0xf<<20);    /* ͨ����Ŀ  1�� */
    ADC1->SQR3 &= ~(0x1f<<0);
    ADC1->SQR3 |= (16<<0);       /* ��1��ת����ͨ����ͨ��6 */

    /* ADCͨ�ÿ��ƼĴ��� */
    ADC->CCR &= ~(3<<16);
    ADC->CCR |= (1<<16);         /* 4��Ƶ 84/4=21Mhz */
    ADC->CCR |= 1<<23;           /* �¶ȴ�����ʹ�� */

    /* ADCxʹ�� */
    ADC1->CR2 |= (1<<0);
}



/**********************************************************
* @funcName ��ADC1_In16_Data
* @brief    ����ȡADC1ͨ��16��ת������
* @param    ��void
* @retval   ��uint16_t
* @details  ��
* @fn       ��
*            ���оƬ�¶�
************************************************************/
uint16_t ADC1_In16_Data(void)
{
    uint16_t data;

    //��������ͨ��ת������
    ADC1->CR2 |= (1<<30);
    //�ȴ�ת�����
    while(!(ADC1->SR & (1<<1)));
    //��ȡת���������
    data = ADC1->DR;

    return data;
}



/**********************************************************
* @funcName ��Oversampling
* @brief    ��ADC�������㷨����߷ֱ��ʣ���12�ֱ��ʱ�Ϊ16�ֱ���
* @param    ��void
* @retval   ��uint16_t  ---  (ADC��16�ֱ�������)
* @details  ��
* @fn       ��
*            ����ת��������������
************************************************************/
uint16_t Oversampling(void)
{
    int i;
    uint32_t sum=0;

    for(i=0; i<256; i++)
    {
        sum+=ADC1_In16_Data();
    }

    return (sum>>4);
}



/**********************************************************
* @funcName ��ADC1_Chip_Temperature1
* @brief    ����ADCֵת��ΪоƬ�¶�ֵ(�ǹ�����)
* @param    ��void
* @retval   ��double
* @details  ��
* @fn       ��
*            ���ڼ��оƬ�¶�
************************************************************/
double ADC1_Chip_Temperature1(void)
{
    uint8_t i;
    uint32_t data;
    double sum = 0;
    double stm_t[6];

    for(i=0;i<5;i++)
    {
        data = ADC1_In16_Data();
        stm_t[i]=(float)data*(3.3/4096);     /* ��ѹֵ */
        stm_t[i]=(1.43-stm_t[i])/0.0043+25;  /* ת��Ϊ�¶�ֵ */
        sum += stm_t[i];
    }

    stm_t[5] = sum/5;

    return stm_t[5];
}



/**********************************************************
* @funcName ��ADC1_Chip_Temperature2
* @brief    ����ADCֵת��ΪоƬ�¶�ֵ(������)
* @param    ��void
* @retval   ��double
* @details  ��
* @fn       ��
*            ���ڼ��оƬ�¶�
************************************************************/
double ADC1_Chip_Temperature2(void)
{
    uint8_t i;
    uint32_t data;
    double sum = 0;
    double stm_t[6];

    for(i=0;i<5;i++)
    {
        data = Oversampling();
        stm_t[i]=(float)data*(3.3/65536);     /* ��ѹֵ */
        stm_t[i]=(1.43-stm_t[i])/0.0043+25;  /* ת��Ϊ�¶�ֵ */
        sum += stm_t[i];
    }

    stm_t[5] = sum/5;

    return stm_t[5];
}



