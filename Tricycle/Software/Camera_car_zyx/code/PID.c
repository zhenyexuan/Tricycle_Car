/*
 * PID.c
 *
 *  Created on: 2023��7��2��
 *      Author: ZYX
 */
#include "headfile.h"

pid_param_t LSpeed_PID;
pid_param_t RSpeed_PID;
pid_param_t turn_PID_camera;
pid_param_t turn_PID_inductor;

/*************************************************************************
 *  �������ƣ�float constrain_float(float amt, float low, float high)
 *  ����˵�����޷�����
 *  @param    amt   �� ����
 *  @param    low   �� ���ֵ
 *  @param    high  �� ���ֵ
 *  �������أ���
 *  �޸�ʱ�䣺2020��4��1��
 *  ��    ע��
 *************************************************************************/
float constrain_float(float amt, float low, float high)
{
    return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

// pid����ֵ�޸�
void Pid_Value(void)
{
    //���ֵ��PID����
    LSpeed_PID.kp = 60;         //60    //50
    LSpeed_PID.ki = 0.015;      //0.015
    LSpeed_PID.kd = 0;         //15
    //���ֵ��PID����
    RSpeed_PID.kp = 60;         //60    //50
    RSpeed_PID.ki = 0.015;      //0.015
    RSpeed_PID.kd = 0;         //15

    turn_PID_camera.kp = 1.5;
    turn_PID_camera.ki = 0;
    turn_PID_camera.kd = 0;

    turn_PID_inductor.kp = 55;    //235       230         205             215
    turn_PID_inductor.ki = 0;    //1.0       1.0         1.0             1.0
    turn_PID_inductor.kd = 0;    //0.5       0.5         0.5             0.5
}

// pid������ʼ������
void PidInit(pid_param_t * pid)
{
    pid->kp        = 0;
    pid->ki        = 0;
    pid->kd        = 0;
    pid->imax      = 0;
    pid->out_p     = 0;
    pid->out_i     = 0;
    pid->out_d     = 0;
    pid->out       = 0;
    pid->integrator= 0;
    pid->last_error= 0;
    pid->last_derivative   = 0;
    pid->last_t    = 0;
}

/*************************************************************************
 *  �������ƣ�float constrain_float(float amt, float low, float high)
 *  ����˵����pidλ��ʽ���������
 *  ����˵����
  * @param    pid     pid����
  * @param    error   pid�������
 *  �������أ�PID������
 *  �޸�ʱ�䣺2020��4��1��
 *  ��    ע��
 *************************************************************************/
float PidLocCtrl(pid_param_t * pid, float error)
{
    /* �ۻ���� */
    pid->integrator += error;

    /* ����޷� */
    if(pid->integrator>=200)pid->integrator=200;
    if(pid->integrator<=-200)pid->integrator=-200;

    pid->out_p = pid->kp * error;
    pid->out_i = pid->ki * pid->integrator;
    constrain_float(pid->out_i, -200, 200);
    pid->out_d = pid->kd * (error - pid->last_error);

    pid->last_error = error;

    pid->out = pid->out_p + pid->out_i + pid->out_d;

    return pid->out;
}

/*************************************************************************
 *  �������ƣ�float constrain_float(float amt, float low, float high)
 *  ����˵����pid����ʽ���������
 *  ����˵����
  * @param    pid     pid����
  * @param    error   pid�������
 *  �������أ�PID������   ע���������Ѿ��������ϴν��
 *  �޸�ʱ�䣺2020��4��1��
 *  ��    ע��
 *************************************************************************/
float PidIncCtrl(pid_param_t * pid, float error)
{
    pid->out_p = pid->kp * (error - pid->last_error);      //ϵͳ����Ӧ�ٶȻ���Kpֵ��������ӿ죬ͬʱҲ�����ھ���ļ�С
    pid->out_i = pid->ki * error;  //�����ļ�С���񵴱�С�Լ�ϵͳ�ȶ��Ե����Ӷ�ȡ���ڻ���ʱ��Ti������
    pid->out_d = pid->kd * ((error - pid->last_error) - pid->last_derivative);   //����΢��ʱ��Td����ϵͳ���ȶ��ԡ�ϵͳ��Ӧ�ٶȵļӿ��Լ�ϵͳ�������ļ�С������������

    pid->last_derivative = error - pid->last_error;
    pid->last_error = error;

    pid->out += pid->out_p + pid->out_i + pid->out_d;
    if(pid->out>=6000)pid->out=6000;
    if(pid->out<=-6000)pid->out=-6000;
    return pid->out;
}


