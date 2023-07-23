/*
 * PID.c
 *
 *  Created on: 2023年7月2日
 *      Author: ZYX
 */
#include "headfile.h"

pid_param_t LSpeed_PID;
pid_param_t RSpeed_PID;
pid_param_t turn_PID_camera;
pid_param_t turn_PID_inductor;

/*************************************************************************
 *  函数名称：float constrain_float(float amt, float low, float high)
 *  功能说明：限幅函数
 *  @param    amt   ： 参数
 *  @param    low   ： 最低值
 *  @param    high  ： 最高值
 *  函数返回：无
 *  修改时间：2020年4月1日
 *  备    注：
 *************************************************************************/
float constrain_float(float amt, float low, float high)
{
    return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

// pid参数值修改
void Pid_Value(void)
{
    //左轮电机PID参数
    LSpeed_PID.kp = 60;         //60    //50
    LSpeed_PID.ki = 0.015;      //0.015
    LSpeed_PID.kd = 0;         //15
    //右轮电机PID参数
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

// pid参数初始化函数
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
 *  函数名称：float constrain_float(float amt, float low, float high)
 *  功能说明：pid位置式控制器输出
 *  参数说明：
  * @param    pid     pid参数
  * @param    error   pid输入误差
 *  函数返回：PID输出结果
 *  修改时间：2020年4月1日
 *  备    注：
 *************************************************************************/
float PidLocCtrl(pid_param_t * pid, float error)
{
    /* 累积误差 */
    pid->integrator += error;

    /* 误差限幅 */
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
 *  函数名称：float constrain_float(float amt, float low, float high)
 *  功能说明：pid增量式控制器输出
 *  参数说明：
  * @param    pid     pid参数
  * @param    error   pid输入误差
 *  函数返回：PID输出结果   注意输出结果已经包涵了上次结果
 *  修改时间：2020年4月1日
 *  备    注：
 *************************************************************************/
float PidIncCtrl(pid_param_t * pid, float error)
{
    pid->out_p = pid->kp * (error - pid->last_error);      //系统的响应速度会随Kp值的增大而加快，同时也有助于静差的减小
    pid->out_i = pid->ki * error;  //超调的减小、振荡变小以及系统稳定性的增加都取决于积分时间Ti的增大
    pid->out_d = pid->kd * ((error - pid->last_error) - pid->last_derivative);   //增大微分时间Td对于系统的稳定性、系统响应速度的加快以及系统超调量的减小都会有所帮助

    pid->last_derivative = error - pid->last_error;
    pid->last_error = error;

    pid->out += pid->out_p + pid->out_i + pid->out_d;
    if(pid->out>=6000)pid->out=6000;
    if(pid->out<=-6000)pid->out=-6000;
    return pid->out;
}


