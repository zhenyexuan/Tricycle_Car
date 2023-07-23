/*
 * motor.c
 *
 *  Created on: 2023年7月2日
 *      Author: ZYX
 */
#include "headfile.h"

sint16 MotorDutyL;
sint16 MotorDutyR;
uint8 speed_flag;
uint8 direction_flag;
volatile sint16 Target_Speed1 = SPEED_L;     // 左轮目标速度
volatile sint16 Target_Speed2 = SPEED_R;     // 右轮目标速度
volatile sint16 encoder_Left = 0;       //左编码器速度
volatile sint16 encoder_Right = 0;       //右编码器速度
volatile float road_Left = 0;          //左编码器积分路程cm单位
volatile float road_Right = 0;         //右编码器积分路程cm单位
volatile float road_sum=0;              //总路程cm单位
float road_temp_L=0;
float road_temp_R=0;

extern uint8 aim_point_H;

void Para_Init(void){
    PidInit(&LSpeed_PID);
    PidInit(&RSpeed_PID);
    PidInit(&turn_PID_camera);
    PidInit(&turn_PID_inductor);
    Pid_Value();
}
void Motor_Init(void){
    gpio_init(P02_4, GPO, GPIO_HIGH, GPO_PUSH_PULL);// GPIO 初始化为输出 默认上拉输出高
    gpio_init(P02_6, GPO, GPIO_HIGH, GPO_PUSH_PULL);// GPIO 初始化为输出 默认上拉输出高
    //电机
    pwm_init ( ATOM0_CH5_P02_5, 17000, 0);
    pwm_init ( ATOM0_CH7_P02_7, 17000, 0);
}
void EncoderInit (void){
    encoder_dir_init(ENCODER_DIR_L, ENCODER_DIR_PULSE_L, ENCODER_DIR_DIR_L);          //编码器初始化
    encoder_dir_init(ENCODER_DIR_R, ENCODER_DIR_PULSE_R, ENCODER_DIR_DIR_R);          //编码器初始化
}
void Get_Speed(void){
    encoder_Left = encoder_get_count(ENCODER_DIR_L);      // 获取编码器计数
    encoder_Right = -encoder_get_count(ENCODER_DIR_R);    // 获取编码器计数
    encoder_clear_count(ENCODER_DIR_L);                   // 清空编码器计数
    encoder_clear_count(ENCODER_DIR_R);                   // 清空编码器计数

    road_Left += encoder_Left * 200 * (3.14159265) * 0.032 /2250;
    road_Right += (encoder_Right * 200 * (3.14159265) * 0.032) / 2250;
    road_sum = (road_Left + road_Right) / 2;
}
sint16 Direction(void)    //方向环，偏差角度环，有时间做角速度环 位置式
{
    //如果有元素就关闭循迹
    if(element_flag==1){
        return 0;
    }
    //摄像头
    if(camera_flag==1){
        camera_error = (MT9V03X_HALVED_W)/2+6-centerline[aim_point_H];
        return PidLocCtrl(&turn_PID_camera,camera_error);
    }
    //电磁
//    return PidLocCtrl(&turn_PID_inductor,inductor_error);
    return 55*inductor_error;
}
void Motor_PID(void)
{
    /*电机PID*/
    MotorDutyL =(int)PidIncCtrl(&LSpeed_PID, (float)(Target_Speed1-Direction()-encoder_Left));//方向环与速度环串级，方向内环，速度外环
    MotorDutyR =(int)PidIncCtrl(&RSpeed_PID, (float)(Target_Speed2+Direction()-encoder_Right));//+Direction()
    /*电机限幅*/
    if(MotorDutyL > 4000)MotorDutyL = 4000;
    else if(MotorDutyL <-4000)MotorDutyL = -4000;
    if(MotorDutyR > 4000)MotorDutyR = 4000;
    else if(MotorDutyR <-4000)MotorDutyR = -4000;
}
/*电机驱动程序，MotorDuty1：左电机占空比；MotorDuty2：右电机占空比*/
void motor_run(sint16 MotorDuty1,sint16 MotorDuty2)
{
    /********************************************以下为电机驱动程序，根据驱动需要的信号更改*********************************************/
    if(MotorDuty1 >= 0)                                                           // 正转
    {
        gpio_set_level(DIR_L, GPIO_HIGH);                                   // DIR输出高电平
        pwm_set_duty(PWM_L, abs(MotorDuty1));                   // 计算占空比
    }
    else{
        gpio_set_level(DIR_L, GPIO_LOW);                                    // DIR输出低电平
        pwm_set_duty(PWM_L, abs(MotorDuty1));                // 计算占空比
    }

    if(MotorDuty2 >= 0)
    {
        gpio_set_level(DIR_R, GPIO_LOW);                                   // DIR输出高电平
        pwm_set_duty(PWM_R, abs(MotorDuty2));
    }
    else{
        gpio_set_level(DIR_R, GPIO_HIGH);                                    // DIR输出低电平
        pwm_set_duty(PWM_R, abs(MotorDuty2));
    }
}


