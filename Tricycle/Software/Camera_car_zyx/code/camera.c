///*
// * camera.c
// *
// *  Created on: 2023年7月1日
// *      Author: ZYX
// */
//#include "headfile.h"
////大津法变量
//#define GrayScale 256
//int pixelCount[GrayScale];
//float pixelPro[GrayScale];
//unsigned short threshold_IPS;    //用于显示的阈值
////二值化变量
//uint8  current_image[MT9V03X_H][MT9V03X_W];
///* 二值化后用于OLED显示的数据 */
//uint8 Bin_Image[MT9V03X_H][MT9V03X_W];
//
///*获取当前图像*/
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
// *  函数名称：void Get_Bin_Image (unsigned char mode)
// *  功能说明：图像二值化到Bin_Image[][]
// *  参数说明：mode  ：
// *    3：sobel 算子改进型   动态阈值，同时输出改为提取边沿的图像
//
// *************************************************************************/
//void Get_Bin_Image (unsigned char mode)
//{
//    unsigned short i = 0, j = 0;
//    unsigned short Threshold = 0;
//    if (mode == 3)
//    {
//        Threshold = GetOSTU(current_image);  //大津法阈值  灰度图像
//        threshold_IPS=Threshold;
//    }
//    /* 二值化 */
//    for (i = 0; i < MT9V03X_H; i++)
//    {
//        for (j = 0; j < MT9V03X_W; j++)
//        {
//            if (current_image[i][j] > Threshold) //数值越大，显示的内容越多，较浅的图像也能显示出来
//                Bin_Image[i][j] = 255;
//            else
//                Bin_Image[i][j] = 0;
//        }
//    }
//}
//
///*************************************************************************
// *  函数名称：short GetOSTU (unsigned char tmImage[MT9V03X_H][MT9V03X_W])
// *  功能说明：大津法求阈值大小
// *  参数说明：tmImage ： 图像数据
// *  函数返回：无
// *  修改时间：2011年10月28日
// *  备    注：  GetOSTU(Image_Use);//大津法阈值
//Ostu方法又名最大类间差方法，通过统计整个图像的直方图特性来实现全局阈值T的自动选取，其算法步骤为：
//1) 先计算图像的直方图，即将图像所有的像素点按照0~255共256个bin，统计落在每个bin的像素点数量
//2) 归一化直方图，也即将每个bin中像素点数量除以总的像素点
//3) i表示分类的阈值，也即一个灰度级，从0开始迭代 1
//4) 通过归一化的直方图，统计0~i 灰度级的像素(假设像素值在此范围的像素叫做前景像素) 所占整幅图像
//        的比例w0，        并统计前景像素的平均灰度u0；统计i~255灰度级的像素(假设像素值在此范围的像素叫做背
//        景像素)  * 所占整幅图像的比例w1，并统计背景像素的平均灰度u1；
//5) 计算前景像素和背景像素的方差 g = w0*w1*(u0-u1) (u0-u1)
//6) i++；转到4)，直到i为256时结束迭代
//7) 将最大g相应的i值作为图像的全局阈值
//缺陷:OSTU算法在处理光照不均匀的图像的时候，效果会明显不好，因为利用的是全局像素信息。
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
//    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差;
//    signed short MinValue, MaxValue;
//    signed short Threshold = 0;
//    unsigned char HistoGram[256];              //
//
//    for (j = 0; j < 256; j++)
//        HistoGram[j] = 0; //初始化灰度直方图
//
//    for (j = 0; j < MT9V03X_H; j++)
//    {
//        for (i = 0; i < MT9V03X_W; i++)
//        {
//            HistoGram[tmImage[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
//        }
//    }
//
//    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //获取最小灰度的值
//    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //获取最大灰度的值
//
//    if (MaxValue == MinValue)
//        return MaxValue;         // 图像中只有一个颜色
//    if (MinValue + 1 == MaxValue)
//        return MinValue;        // 图像中只有二个颜色
//
//    for (j = MinValue; j <= MaxValue; j++)
//        Amount += HistoGram[j];        //  像素总数
//
//    Pixelshortegral = 0;
//    for (j = MinValue; j <= MaxValue; j++)
//    {
//        Pixelshortegral += HistoGram[j] * j;        //灰度值总数
//    }
//    SigmaB = -1;
//    for (j = MinValue; j < MaxValue; j++)
//    {
//        PixelBack = PixelBack + HistoGram[j];     //前景像素点数
//        PixelFore = Amount - PixelBack;           //背景像素点数
//        OmegaBack = (float) PixelBack / Amount;   //前景像素百分比
//        OmegaFore = (float) PixelFore / Amount;   //背景像素百分比
//        PixelshortegralBack += HistoGram[j] * j;  //前景灰度值
//        PixelshortegralFore = Pixelshortegral - PixelshortegralBack;  //背景灰度值
//        MicroBack = (float) PixelshortegralBack / PixelBack;   //前景灰度百分比
//        MicroFore = (float) PixelshortegralFore / PixelFore;   //背景灰度百分比
//        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);   //计算类间方差
//        if (Sigma > SigmaB)                    //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
//        {
//            SigmaB = Sigma;
//            Threshold = j+15;
//        }
//    }
//    return Threshold;                        //返回最佳阈值;
//}
