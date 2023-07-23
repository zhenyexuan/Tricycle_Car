/*
 * motor.c
 *
 *  Created on: 2023��7��2��
 *      Author: ZYX
 */
#include "headfile.h"

sint16 MotorDutyL;
sint16 MotorDutyR;
uint8 speed_flag;
uint8 direction_flag;
volatile sint16 Target_Speed1 = SPEED_L;     // ����Ŀ���ٶ�
volatile sint16 Target_Speed2 = SPEED_R;     // ����Ŀ���ٶ�
volatile sint16 encoder_Left = 0;       //��������ٶ�
volatile sint16 encoder_Right = 0;       //�ұ������ٶ�
volatile float road_Left = 0;          //�����������·��cm��λ
volatile float road_Right = 0;         //�ұ���������·��cm��λ
volatile float road_sum=0;              //��·��cm��λ
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
    gpio_init(P02_4, GPO, GPIO_HIGH, GPO_PUSH_PULL);// GPIO ��ʼ��Ϊ��� Ĭ�����������
    gpio_init(P02_6, GPO, GPIO_HIGH, GPO_PUSH_PULL);// GPIO ��ʼ��Ϊ��� Ĭ�����������
    //���
    pwm_init ( ATOM0_CH5_P02_5, 17000, 0);
    pwm_init ( ATOM0_CH7_P02_7, 17000, 0);
}
void EncoderInit (void){
    encoder_dir_init(ENCODER_DIR_L, ENCODER_DIR_PULSE_L, ENCODER_DIR_DIR_L);          //��������ʼ��
    encoder_dir_init(ENCODER_DIR_R, ENCODER_DIR_PULSE_R, ENCODER_DIR_DIR_R);          //��������ʼ��
}
void Get_Speed(void){
    encoder_Left = encoder_get_count(ENCODER_DIR_L);      // ��ȡ����������
    encoder_Right = -encoder_get_count(ENCODER_DIR_R);    // ��ȡ����������
    encoder_clear_count(ENCODER_DIR_L);                   // ��ձ���������
    encoder_clear_count(ENCODER_DIR_R);                   // ��ձ���������

    road_Left += encoder_Left * 200 * (3.14159265) * 0.032 /2250;
    road_Right += (encoder_Right * 200 * (3.14159265) * 0.032) / 2250;
    road_sum = (road_Left + road_Right) / 2;
}
sint16 Direction(void)    //���򻷣�ƫ��ǶȻ�����ʱ�������ٶȻ� λ��ʽ
{
    //�����Ԫ�ؾ͹ر�ѭ��
    if(element_flag==1){
        return 0;
    }
    //����ͷ
    if(camera_flag==1){
        camera_error = (MT9V03X_HALVED_W)/2+6-centerline[aim_point_H];
        return PidLocCtrl(&turn_PID_camera,camera_error);
    }
    //���
//    return PidLocCtrl(&turn_PID_inductor,inductor_error);
    return 55*inductor_error;
}
void Motor_PID(void)
{
    /*���PID*/
    MotorDutyL =(int)PidIncCtrl(&LSpeed_PID, (float)(Target_Speed1-Direction()-encoder_Left));//�������ٶȻ������������ڻ����ٶ��⻷
    MotorDutyR =(int)PidIncCtrl(&RSpeed_PID, (float)(Target_Speed2+Direction()-encoder_Right));//+Direction()
    /*����޷�*/
    if(MotorDutyL > 4000)MotorDutyL = 4000;
    else if(MotorDutyL <-4000)MotorDutyL = -4000;
    if(MotorDutyR > 4000)MotorDutyR = 4000;
    else if(MotorDutyR <-4000)MotorDutyR = -4000;
}
/*�����������MotorDuty1������ռ�ձȣ�MotorDuty2���ҵ��ռ�ձ�*/
void motor_run(sint16 MotorDuty1,sint16 MotorDuty2)
{
    /********************************************����Ϊ����������򣬸���������Ҫ���źŸ���*********************************************/
    if(MotorDuty1 >= 0)                                                           // ��ת
    {
        gpio_set_level(DIR_L, GPIO_HIGH);                                   // DIR����ߵ�ƽ
        pwm_set_duty(PWM_L, abs(MotorDuty1));                   // ����ռ�ձ�
    }
    else{
        gpio_set_level(DIR_L, GPIO_LOW);                                    // DIR����͵�ƽ
        pwm_set_duty(PWM_L, abs(MotorDuty1));                // ����ռ�ձ�
    }

    if(MotorDuty2 >= 0)
    {
        gpio_set_level(DIR_R, GPIO_LOW);                                   // DIR����ߵ�ƽ
        pwm_set_duty(PWM_R, abs(MotorDuty2));
    }
    else{
        gpio_set_level(DIR_R, GPIO_HIGH);                                    // DIR����͵�ƽ
        pwm_set_duty(PWM_R, abs(MotorDuty2));
    }
}


