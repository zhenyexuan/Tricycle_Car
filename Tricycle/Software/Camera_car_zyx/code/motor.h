/*
 * motor.h
 *
 *  Created on: 2023��7��2��
 *      Author: ZYX
 */

#ifndef CODE_MOTOR_H_
#define CODE_MOTOR_H_
#include "headfile.h"

#define SPEED_L     80      //70
#define SPEED_R     80      //70

#define DIR_R               (P02_4)
#define PWM_R               (ATOM0_CH5_P02_5)

#define DIR_L               (P02_6)
#define PWM_L               (ATOM0_CH7_P02_7)

#define ENCODER_DIR_R                     (TIM4_ENCOEDER)            // �������������Ӧʹ�õı������ӿ�
#define ENCODER_DIR_PULSE_R               (TIM4_ENCOEDER_CH1_P02_8)  // PULSE ��Ӧ������
#define ENCODER_DIR_DIR_R                 (TIM4_ENCOEDER_CH2_P00_9)

#define ENCODER_DIR_L                     (TIM2_ENCOEDER)            // �������������Ӧʹ�õı������ӿ�
#define ENCODER_DIR_PULSE_L               (TIM2_ENCOEDER_CH1_P33_7)  // PULSE ��Ӧ������
#define ENCODER_DIR_DIR_L                 (TIM2_ENCOEDER_CH2_P33_6)

extern sint16 MotorDutyL;      // �������ռ�ձ���ֵ
extern sint16 MotorDutyR;      // �������ռ�ձ���ֵ
extern volatile sint16 Target_Speed1;       //�ٶ�ȫ�ֱ���
extern volatile sint16 Target_Speed2;       //�ٶ�ȫ�ֱ���
extern uint8 speed_flag;
extern uint8 direction_flag;

extern volatile sint16 encoder_Left;        //��������ٶ�
extern volatile sint16 encoder_Right;       //�ұ������ٶ�
extern volatile float road_Left;          //�����������
extern volatile float road_Right;         //�ұ���������
extern volatile float road_sum;

extern float road_temp_L;
extern float road_temp_R;


void Para_Init(void);
void Motor_Init(void);
void EncoderInit (void);
void Get_Speed(void);
void Motor_PID(void);
void motor_run(sint16 MotorDuty1,sint16 MotorDuty2);
sint16 Direction(void);    //���򻷣�ƫ��ǶȻ�����ʱ�������ٶȻ� λ��ʽ

#endif /* CODE_MOTOR_H_ */
