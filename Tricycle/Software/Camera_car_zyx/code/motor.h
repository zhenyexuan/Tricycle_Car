/*
 * motor.h
 *
 *  Created on: 2023年7月2日
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

#define ENCODER_DIR_R                     (TIM4_ENCOEDER)            // 带方向编码器对应使用的编码器接口
#define ENCODER_DIR_PULSE_R               (TIM4_ENCOEDER_CH1_P02_8)  // PULSE 对应的引脚
#define ENCODER_DIR_DIR_R                 (TIM4_ENCOEDER_CH2_P00_9)

#define ENCODER_DIR_L                     (TIM2_ENCOEDER)            // 带方向编码器对应使用的编码器接口
#define ENCODER_DIR_PULSE_L               (TIM2_ENCOEDER_CH1_P33_7)  // PULSE 对应的引脚
#define ENCODER_DIR_DIR_L                 (TIM2_ENCOEDER_CH2_P33_6)

extern sint16 MotorDutyL;      // 电机驱动占空比数值
extern sint16 MotorDutyR;      // 电机驱动占空比数值
extern volatile sint16 Target_Speed1;       //速度全局变量
extern volatile sint16 Target_Speed2;       //速度全局变量
extern uint8 speed_flag;
extern uint8 direction_flag;

extern volatile sint16 encoder_Left;        //左编码器速度
extern volatile sint16 encoder_Right;       //右编码器速度
extern volatile float road_Left;          //左编码器积分
extern volatile float road_Right;         //右编码器积分
extern volatile float road_sum;

extern float road_temp_L;
extern float road_temp_R;


void Para_Init(void);
void Motor_Init(void);
void EncoderInit (void);
void Get_Speed(void);
void Motor_PID(void);
void motor_run(sint16 MotorDuty1,sint16 MotorDuty2);
sint16 Direction(void);    //方向环，偏差角度环，有时间做角速度环 位置式

#endif /* CODE_MOTOR_H_ */
