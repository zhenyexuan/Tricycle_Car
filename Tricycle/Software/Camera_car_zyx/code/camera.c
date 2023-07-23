///*
// * camera.c
// *
// *  Created on: 2023��7��1��
// *      Author: ZYX
// */
//#include "headfile.h"
////��򷨱���
//#define GrayScale 256
//int pixelCount[GrayScale];
//float pixelPro[GrayScale];
//unsigned short threshold_IPS;    //������ʾ����ֵ
////��ֵ������
//uint8  current_image[MT9V03X_H][MT9V03X_W];
///* ��ֵ��������OLED��ʾ������ */
//uint8 Bin_Image[MT9V03X_H][MT9V03X_W];
//
///*��ȡ��ǰͼ��*/
//void Get_Current_Img(uint8 current_image[][MT9V03X_W], uint8 camera_image[][MT9V03X_W])
//{
//    for (int y=0; y<MT9V03X_H-1; y++)
//    {
//        for (int x=0; x<MT9V03X_W; x++)
//        {
//            current_image[y][x] = camera_image[y][x];
//        }
//    }
//}
///*************************************************************************
// *  �������ƣ�void Get_Bin_Image (unsigned char mode)
// *  ����˵����ͼ���ֵ����Bin_Image[][]
// *  ����˵����mode  ��
// *    3��sobel ���ӸĽ���   ��̬��ֵ��ͬʱ�����Ϊ��ȡ���ص�ͼ��
//
// *************************************************************************/
//void Get_Bin_Image (unsigned char mode)
//{
//    unsigned short i = 0, j = 0;
//    unsigned short Threshold = 0;
//    if (mode == 3)
//    {
//        Threshold = GetOSTU(current_image);  //�����ֵ  �Ҷ�ͼ��
//        threshold_IPS=Threshold;
//    }
//    /* ��ֵ�� */
//    for (i = 0; i < MT9V03X_H; i++)
//    {
//        for (j = 0; j < MT9V03X_W; j++)
//        {
//            if (current_image[i][j] > Threshold) //��ֵԽ����ʾ������Խ�࣬��ǳ��ͼ��Ҳ����ʾ����
//                Bin_Image[i][j] = 255;
//            else
//                Bin_Image[i][j] = 0;
//        }
//    }
//}
//
///*************************************************************************
// *  �������ƣ�short GetOSTU (unsigned char tmImage[MT9V03X_H][MT9V03X_W])
// *  ����˵�����������ֵ��С
// *  ����˵����tmImage �� ͼ������
// *  �������أ���
// *  �޸�ʱ�䣺2011��10��28��
// *  ��    ע��  GetOSTU(Image_Use);//�����ֵ
//Ostu������������������ͨ��ͳ������ͼ���ֱ��ͼ������ʵ��ȫ����ֵT���Զ�ѡȡ�����㷨����Ϊ��
//1) �ȼ���ͼ���ֱ��ͼ������ͼ�����е����ص㰴��0~255��256��bin��ͳ������ÿ��bin�����ص�����
//2) ��һ��ֱ��ͼ��Ҳ����ÿ��bin�����ص����������ܵ����ص�
//3) i��ʾ�������ֵ��Ҳ��һ���Ҷȼ�����0��ʼ���� 1
//4) ͨ����һ����ֱ��ͼ��ͳ��0~i �Ҷȼ�������(��������ֵ�ڴ˷�Χ�����ؽ���ǰ������) ��ռ����ͼ��
//        �ı���w0��        ��ͳ��ǰ�����ص�ƽ���Ҷ�u0��ͳ��i~255�Ҷȼ�������(��������ֵ�ڴ˷�Χ�����ؽ�����
//        ������)  * ��ռ����ͼ��ı���w1����ͳ�Ʊ������ص�ƽ���Ҷ�u1��
//5) ����ǰ�����غͱ������صķ��� g = w0*w1*(u0-u1) (u0-u1)
//6) i++��ת��4)��ֱ��iΪ256ʱ��������
//7) �����g��Ӧ��iֵ��Ϊͼ���ȫ����ֵ
//ȱ��:OSTU�㷨�ڴ�����ղ����ȵ�ͼ���ʱ��Ч�������Բ��ã���Ϊ���õ���ȫ��������Ϣ��
//*************************************************************************/
//short GetOSTU (unsigned char tmImage[MT9V03X_H][MT9V03X_W])
//{
//    signed short i, j;
//    unsigned long Amount = 0;
//    unsigned long PixelBack = 0;
//    unsigned long PixelshortegralBack = 0;
//    unsigned long Pixelshortegral = 0;
//    signed long PixelshortegralFore = 0;
//    signed long PixelFore = 0;
//    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // ��䷽��;
//    signed short MinValue, MaxValue;
//    signed short Threshold = 0;
//    unsigned char HistoGram[256];              //
//
//    for (j = 0; j < 256; j++)
//        HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ
//
//    for (j = 0; j < MT9V03X_H; j++)
//    {
//        for (i = 0; i < MT9V03X_W; i++)
//        {
//            HistoGram[tmImage[j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
//        }
//    }
//
//    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //��ȡ��С�Ҷȵ�ֵ
//    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //��ȡ���Ҷȵ�ֵ
//
//    if (MaxValue == MinValue)
//        return MaxValue;         // ͼ����ֻ��һ����ɫ
//    if (MinValue + 1 == MaxValue)
//        return MinValue;        // ͼ����ֻ�ж�����ɫ
//
//    for (j = MinValue; j <= MaxValue; j++)
//        Amount += HistoGram[j];        //  ��������
//
//    Pixelshortegral = 0;
//    for (j = MinValue; j <= MaxValue; j++)
//    {
//        Pixelshortegral += HistoGram[j] * j;        //�Ҷ�ֵ����
//    }
//    SigmaB = -1;
//    for (j = MinValue; j < MaxValue; j++)
//    {
//        PixelBack = PixelBack + HistoGram[j];     //ǰ�����ص���
//        PixelFore = Amount - PixelBack;           //�������ص���
//        OmegaBack = (float) PixelBack / Amount;   //ǰ�����ذٷֱ�
//        OmegaFore = (float) PixelFore / Amount;   //�������ذٷֱ�
//        PixelshortegralBack += HistoGram[j] * j;  //ǰ���Ҷ�ֵ
//        PixelshortegralFore = Pixelshortegral - PixelshortegralBack;  //�����Ҷ�ֵ
//        MicroBack = (float) PixelshortegralBack / PixelBack;   //ǰ���ҶȰٷֱ�
//        MicroFore = (float) PixelshortegralFore / PixelFore;   //�����ҶȰٷֱ�
//        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);   //������䷽��
//        if (Sigma > SigmaB)                    //����������䷽��g //�ҳ������䷽���Լ���Ӧ����ֵ
//        {
//            SigmaB = Sigma;
//            Threshold = j+15;
//        }
//    }
//    return Threshold;                        //���������ֵ;
//}
