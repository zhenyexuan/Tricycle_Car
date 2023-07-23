/*
 * Inductor.c
 *
 *  Created on: 2023年7月7日
 *      Author: ZYX
 */
#include "headfile.h"
#define COUNT 10    //冒泡滤波的采集值个数

/*差比和差参数*/
float inductor_error=0;  //电磁偏差--差比和差
float para_A=100,para_B=0,para_C=0;            //差比和差系数
#if 0   //这是工训的参数
//用于归一化的最大值和最小值
sint16 ADC_Left_Min=40;         //10    去比赛了赛道上重新测!!!
sint16 ADC_Left_Max=1500;       //1500  去比赛了赛道上重新测
sint16 ADC_Right_Min=40;        //10    去比赛了赛道上重新测
sint16 ADC_Right_Max=1500;      //1500  去比赛了赛道上重新测
sint16 ADC_Left_Angle_Min=40;     //待测      去比赛了赛道上重新测
sint16 ADC_Left_Angle_Max=1500;     //      去比赛了赛道上重新测
sint16 ADC_Right_Angle_Min=40;          //    去比赛了赛道上重新测
sint16 ADC_Right_Angle_Max=1500;          //  去比赛了赛道上重新测
#endif

#if 1   //用于测赛道电感最大值--关闭归一化！！！
//用于归一化的最大值和最小值
sint16 ADC_Left_Min=50;         //10    去比赛了赛道上重新测!!!
sint16 ADC_Left_Max=1600;       //1500  去比赛了赛道上重新测
sint16 ADC_Right_Min=50;        //10    去比赛了赛道上重新测
sint16 ADC_Right_Max=1600;      //1500  去比赛了赛道上重新测
sint16 ADC_Left_Angle_Min=50;     //待测      去比赛了赛道上重新测
sint16 ADC_Left_Angle_Max=1600;     //      去比赛了赛道上重新测
sint16 ADC_Right_Angle_Min=50;          //    去比赛了赛道上重新测
sint16 ADC_Right_Angle_Max=1600;          //  去比赛了赛道上重新测
#endif

#if 0   //用于测赛道电感最大值--关闭归一化！！！
//用于归一化的最大值和最小值
sint16 ADC_Left_Min=4096;         //10    去比赛了赛道上重新测!!!
sint16 ADC_Left_Max=0;       //1500  去比赛了赛道上重新测
sint16 ADC_Right_Min=4096;        //10    去比赛了赛道上重新测
sint16 ADC_Right_Max=0;      //1500  去比赛了赛道上重新测
sint16 ADC_Left_Angle_Min=4096;     //待测      去比赛了赛道上重新测
sint16 ADC_Left_Angle_Max=0;     //      去比赛了赛道上重新测
sint16 ADC_Right_Angle_Min=4096;          //    去比赛了赛道上重新测
sint16 ADC_Right_Angle_Max=0;          //  去比赛了赛道上重新测
#endif

/*归一化前的电感值*/
uint16 ADC_Left_buffer[COUNT];
uint16 ADC_Left_Angle_buffer[COUNT];
uint16 ADC_Right_buffer[COUNT];
uint16 ADC_Right_Angle_buffer[COUNT];

sint16 ADC_Left_temp=0;         //左侧横电感当前ADC数值
sint16 ADC_Left_Angle_temp=0;   //左侧斜电感当前ADC数值
sint16 ADC_Right_temp=0;        //右侧横电感当前ADC数值
sint16 ADC_Right_Angle_temp=0;  //右侧斜电感当前ADC数值

/*归一化后的电感值*/
sint16 ADC_Left=0;
sint16 ADC_Left_Angle=0;
sint16 ADC_Right=0;
sint16 ADC_Right_Angle=0;

void InductorInit (void)
{
    adc_init(ADC0_CH0_A0, ADC_12BIT);                       // 初始化 A0 为 ADC1 的 channel0 输入功能 分辨率为8位 1/2^8s
    adc_init(ADC0_CH1_A1, ADC_12BIT);                       // 初始化 A0 为 ADC1 的 channel0 输入功能 分辨率为8位 1/2^8s
    adc_init(ADC0_CH2_A2, ADC_12BIT);                       // 初始化 A0 为 ADC1 的 channel0 输入功能 分辨率为8位 1/2^8s
    adc_init(ADC0_CH3_A3, ADC_12BIT);                       // 初始化 A0 为 ADC1 的 channel0 输入功能 分辨率为8位 1/2^8s

    adc_init(ADC0_CH4_A4, ADC_12BIT);                       // 初始化 A0 为 ADC1 的 channel0 输入功能 分辨率为8位 1/2^8s
    adc_init(ADC0_CH5_A5, ADC_12BIT);                       // 初始化 A0 为 ADC1 的 channel0 输入功能 分辨率为8位 1/2^8s
    adc_init(ADC0_CH6_A6, ADC_12BIT);                       // 初始化 A0 为 ADC1 的 channel0 输入功能 分辨率为8位 1/2^8s
    adc_init(ADC0_CH7_A7, ADC_12BIT);                       // 初始化 A0 为 ADC1 的 channel0 输入功能 分辨率为8位 1/2^8s
}
void InductorNormal (void)
{
    uint16 temp;
    for(uint16 i = 0; i < COUNT; ++i){
        ADC_Left_buffer[i]          =   adc_convert(ADC0_CH2_A2);
        ADC_Left_Angle_buffer[i]    =   adc_convert(ADC0_CH0_A0);
        ADC_Right_buffer[i]         =   adc_convert(ADC0_CH3_A3);
        ADC_Right_Angle_buffer[i]   =   adc_convert(ADC0_CH1_A1);
    }
    for(uint16 j = 0 ; j < COUNT-1; ++j)
    {
        for(uint16 k = 0; k < COUNT-j-1; ++k)
        {
            //从小到大排序，冒泡法排序
            if(ADC_Left_buffer[k] > ADC_Left_buffer[k+1])
            {
                temp = ADC_Left_buffer[k];
                ADC_Left_buffer[k] = ADC_Left_buffer[k+1];
                ADC_Left_buffer[k+1] = temp;
            }
            if(ADC_Left_Angle_buffer[k] > ADC_Left_Angle_buffer[k+1])
            {
                temp = ADC_Left_Angle_buffer[k];
                ADC_Left_Angle_buffer[k] = ADC_Left_Angle_buffer[k+1];
                ADC_Left_Angle_buffer[k+1] = temp;
            }
            if(ADC_Right_buffer[k] > ADC_Right_buffer[k+1])
            {
                temp = ADC_Right_buffer[k];
                ADC_Right_buffer[k] = ADC_Right_buffer[k+1];
                ADC_Right_buffer[k+1] = temp;
            }
            if(ADC_Right_Angle_buffer[k] > ADC_Right_Angle_buffer[k+1])
            {
                temp = ADC_Right_Angle_buffer[k];
                ADC_Right_Angle_buffer[k] = ADC_Right_Angle_buffer[k+1];
                ADC_Right_Angle_buffer[k+1] = temp;
            }
        }
    }
    ADC_Left_temp       =(ADC_Left_buffer[(COUNT/2)-1]+ADC_Left_buffer[COUNT/2])/2;
    ADC_Left_Angle_temp =(ADC_Left_Angle_buffer[(COUNT/2)-1]+ADC_Left_Angle_buffer[COUNT/2])/2;
    ADC_Right_temp      =(ADC_Right_buffer[(COUNT/2)-1]+ADC_Right_buffer[COUNT/2])/2;
    ADC_Right_Angle_temp=(ADC_Right_Angle_buffer[(COUNT/2)-1]+ADC_Right_Angle_buffer[COUNT/2])/2;

//    /*用于确定赛道电感最大值*/
//    saomiao_L(&ADC_Left_Max,&ADC_Left_Min);     //用于确定赛道电磁最大值最小值
//    saomiao_R(&ADC_Right_Max,&ADC_Right_Min);   //用于确定赛道电磁最大值最小值
//    saomiao_L_A(&ADC_Left_Angle_Max,&ADC_Left_Angle_Min);
//    saomiao_R_A(&ADC_Right_Angle_Max,&ADC_Right_Angle_Min);

#if 1   //测赛道电感最大值的时候一定要关掉！！！
    //限幅
    if(ADC_Left_temp > ADC_Left_Max)
        ADC_Left_temp = ADC_Left_Max;
    if(ADC_Left_temp < ADC_Left_Min)
        ADC_Left_temp = ADC_Left_Min;
    //左横电感归一化
    ADC_Left=100*(ADC_Left_temp - ADC_Left_Min)/(ADC_Left_Max - ADC_Left_Min);

    //限幅
    if(ADC_Right_temp > ADC_Right_Max)
        ADC_Right_temp = ADC_Right_Max;
    if(ADC_Right_temp < ADC_Right_Min)
        ADC_Right_temp = ADC_Right_Min;
    //右横电感归一化
    ADC_Right=100*(ADC_Right_temp - ADC_Right_Min)/(ADC_Right_Max - ADC_Right_Min);

    //限幅
    if(ADC_Left_Angle_temp > ADC_Left_Angle_Max)
        ADC_Left_Angle_temp = ADC_Left_Angle_Max;
    if(ADC_Left_Angle_temp < ADC_Left_Angle_Min)
        ADC_Left_Angle_temp = ADC_Left_Angle_Min;
    //左斜电感归一化
    ADC_Left_Angle=100*(ADC_Left_Angle_temp - ADC_Left_Angle_Min)/(ADC_Left_Angle_Max - ADC_Left_Angle_Min);

    //限幅
    if(ADC_Right_Angle_temp > ADC_Right_Angle_Max)
        ADC_Right_Angle_temp = ADC_Right_Angle_Max;
    if(ADC_Right_Angle_temp < ADC_Right_Angle_Min)
        ADC_Right_Angle_temp = ADC_Right_Angle_Min;
    //右斜电感归一化
    ADC_Right_Angle=100*(ADC_Right_Angle_temp - ADC_Right_Angle_Min)/(ADC_Right_Angle_Max - ADC_Right_Angle_Min);

    //差比和差计算偏差
    inductor_error=( para_A*(ADC_Left-ADC_Right) + para_B*(ADC_Left_Angle-ADC_Right_Angle) ) / ( para_A * (ADC_Left+ADC_Right) + para_C * abs(ADC_Left_Angle-ADC_Right_Angle) );
#endif
}

// 扫描赛道 //
void saomiao_L(sint16 *ADC_Max,sint16 *ADC_Min){
       if(ADC_Left_temp > *ADC_Max)
           *ADC_Max=ADC_Left_temp;
       if(ADC_Left_temp < *ADC_Min)
           *ADC_Min=ADC_Left_temp;
}
// 扫描赛道 //
void saomiao_R(sint16 *ADC_Max,sint16 *ADC_Min){
       if(ADC_Right_temp > *ADC_Max)
           *ADC_Max = ADC_Right_temp;
       if(ADC_Right_temp < *ADC_Min)
           *ADC_Min = ADC_Right_temp;
}
// 扫描赛道 //
void saomiao_L_A(sint16 *ADC_Max,sint16 *ADC_Min){
       if(ADC_Left_Angle_temp > *ADC_Max)
           *ADC_Max=ADC_Left_Angle_temp;
       if(ADC_Left_Angle_temp < *ADC_Min)
           *ADC_Min=ADC_Left_Angle_temp;
}
// 扫描赛道 //
void saomiao_R_A(sint16 *ADC_Max,sint16 *ADC_Min){
       if(ADC_Right_Angle_temp > *ADC_Max)
           *ADC_Max=ADC_Right_Angle_temp;
       if(ADC_Right_Angle_temp < *ADC_Min)
           *ADC_Min=ADC_Right_Angle_temp;
}

