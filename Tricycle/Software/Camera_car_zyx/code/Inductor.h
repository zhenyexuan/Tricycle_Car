/*
 * Inductor.h
 *
 *  Created on: 2023年7月7日
 *      Author: ZYX
 */

#ifndef CODE_INDUCTOR_H_
#define CODE_INDUCTOR_H_
#include "headfile.h"

/*差比和差参数*/
extern float inductor_error;  //电磁偏差--差比和差
extern float para_A,para_B,para_C;            //差比和差系数

extern sint16 ADC_Left_Min;
extern sint16 ADC_Left_Max;      //待测……
extern sint16 ADC_Right_Min;
extern sint16 ADC_Right_Max;     //待测……
extern sint16 ADC_Left_Angle_Min;
extern sint16 ADC_Left_Angle_Max;      //待测……
extern sint16 ADC_Right_Angle_Min;
extern sint16 ADC_Right_Angle_Max;     //待测……

/*归一化前的电感值*/
extern sint16 ADC_Left_temp;         //左侧横电感当前ADC数值
extern sint16 ADC_Left_Angle_temp;   //左侧斜电感当前ADC数值
extern sint16 ADC_Right_temp;        //右侧横电感当前ADC数值
extern sint16 ADC_Right_Angle_temp;  //右侧斜电感当前ADC数值

/*归一化后的电感值*/
extern sint16 ADC_Left;
extern sint16 ADC_Left_Angle;
extern sint16 ADC_Right;
extern sint16 ADC_Right_Angle;

void InductorInit (void);
void InductorNormal (void);
void saomiao_L(sint16 *ADC_Max,sint16 *ADC_Min);
void saomiao_R(sint16 *ADC_Max,sint16 *ADC_Min);
void saomiao_L_A(sint16 *ADC_Max,sint16 *ADC_Min);
void saomiao_R_A(sint16 *ADC_Max,sint16 *ADC_Min);


#endif /* CODE_INDUCTOR_H_ */
