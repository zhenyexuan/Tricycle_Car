/*
 * Inductor.h
 *
 *  Created on: 2023��7��7��
 *      Author: ZYX
 */

#ifndef CODE_INDUCTOR_H_
#define CODE_INDUCTOR_H_
#include "headfile.h"

/*��ȺͲ����*/
extern float inductor_error;  //���ƫ��--��ȺͲ�
extern float para_A,para_B,para_C;            //��ȺͲ�ϵ��

extern sint16 ADC_Left_Min;
extern sint16 ADC_Left_Max;      //���⡭��
extern sint16 ADC_Right_Min;
extern sint16 ADC_Right_Max;     //���⡭��
extern sint16 ADC_Left_Angle_Min;
extern sint16 ADC_Left_Angle_Max;      //���⡭��
extern sint16 ADC_Right_Angle_Min;
extern sint16 ADC_Right_Angle_Max;     //���⡭��

/*��һ��ǰ�ĵ��ֵ*/
extern sint16 ADC_Left_temp;         //�����е�ǰADC��ֵ
extern sint16 ADC_Left_Angle_temp;   //���б��е�ǰADC��ֵ
extern sint16 ADC_Right_temp;        //�Ҳ���е�ǰADC��ֵ
extern sint16 ADC_Right_Angle_temp;  //�Ҳ�б��е�ǰADC��ֵ

/*��һ����ĵ��ֵ*/
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
