/*
 * element.c
 *
 *  Created on: 2023��7��15��
 *      Author: ZYX
 */
#include "headfile.h"

uint8 car_run_flag=1;   //С�����б�־λ
uint8 element_flag=0;   //Ԫ�ر�־λ
uint8 out_ku_flag=0;   //�����־λ
uint8 barrier_pre_flag=0;   //���Ԥ��־λ
uint8 barrier_flag=0;   //��ϱ�־λ
uint8 state=0;      //�����״̬λ
uint8 state_alone=0;      //�����״̬λ
uint8 barrier_state=0;  //��ϱ�־λ

/*�������⴦��--���ҳ���,�������*/
void Out_Ku_R(void){
    //����
    if( (road_Left>=30) && (road_Right>=30) && (state==0)){
        car_run_flag=1;
        element_flag=1;
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=70;
        Target_Speed2=0;
        state=1;
    }
    if((state==1) && (road_Left-road_temp_L > 50) && (road_Right-road_temp_R > 10) ){
        Target_Speed1=SPEED_L;
        Target_Speed2=SPEED_R;
        element_flag=0;
        state=2;
    }
}

/*������⴦��--���ҳ���,�������*/
void In_Ku_R(void){
    //���
    if(Hall_detection() == 1 && road_sum>=100 && state==2)
    {
        element_flag=1;
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        state=3;
    }
    if(state==3 && road_Left - road_temp_L >=15 && road_Right - road_temp_R>=15){
        Target_Speed1=0;
        Target_Speed2=0;
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        state=4;
    }
    if(state==4){
        Target_Speed1=-70;
        Target_Speed2=0;
        state=5;
    }
    if(state==5 && road_temp_L - road_Left>=21){
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=-70;
        Target_Speed2=-60;
        state=6;
    }
    if(state==6 && road_temp_L - road_Left>=30 && road_temp_R - road_Right>=30){
        Target_Speed1=0;
        Target_Speed2=0;
        element_flag=0;
        car_run_flag=0;
        motor_run(0,0);
    }
}
/*����   ������⴦��--���ҳ���,�������*/
void In_Ku_R_alone(void){
    //���
    if(Hall_detection() == 1 && state_alone==0)
    {
        element_flag=1;
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        state_alone=1;
    }
    if(state_alone==1 && road_Left - road_temp_L >=15 && road_Right - road_temp_R>=15){
        Target_Speed1=0;
        Target_Speed2=0;
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        state_alone=2;
    }
    if(state_alone==2){
        Target_Speed1=-70;
        Target_Speed2=0;
        state_alone=3;
    }
    if(state_alone==3 && road_temp_L - road_Left>=21){
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=-70;
        Target_Speed2=-60;
        state_alone=4;
    }
    if(state_alone==4 && road_temp_L - road_Left>=30 && road_temp_R - road_Right>=30){
        Target_Speed1=0;
        Target_Speed2=0;
        element_flag=0;
        car_run_flag=0; //����С����
        motor_run(0,0);
    }
}

/*������⴦��--�������,�������*/
void In_Ku_L(void)
{
    //���
    if(Hall_detection() == 1 && road_sum>=100 && state==2)
    {
        element_flag=1;
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        state=3;
    }
    if(state==3 && road_Left - road_temp_L >=25 && road_Right - road_temp_R>=25){
        Target_Speed1=0;
        Target_Speed2=0;
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        state=4;
    }
    if(state==4){
        Target_Speed1=0;
        Target_Speed2=-70;
        state=5;
    }
    if(state==5 && road_temp_R - road_Right>=15)
    {
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=-70;
        Target_Speed2=-80;      //75 70
        state=6;
    }
    if(state==6 && road_temp_L - road_Left>=30 && road_temp_R - road_Right>=30){
        Target_Speed1=0;
        Target_Speed2=0;
        element_flag=0;
        car_run_flag=0;
        motor_run(0,0);
    }
}

/*������⴦��--�������,�������*/
void In_Ku_L_alone(void)
{
    //���
    if(Hall_detection() == 1 && state_alone==0)
    {
        element_flag=1;
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        state_alone=1;
    }
    if(state_alone==1 && road_Left - road_temp_L >=25 && road_Right - road_temp_R>=25){
        Target_Speed1=0;
        Target_Speed2=0;
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        state_alone=2;
    }
    if(state_alone==2){
        Target_Speed1=0;
        Target_Speed2=-70;
        state_alone=3;
    }
    if(state_alone==3 & road_temp_R - road_Right>=15)
    {
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=-70;
        Target_Speed2=-80;      //75 70
        state_alone=4;
    }
    if(state_alone==4 && road_temp_L - road_Left>=30 && road_temp_R - road_Right>=30){
        Target_Speed1=0;
        Target_Speed2=0;
        element_flag=0;
        car_run_flag=0;
        motor_run(0,0);
    }
}

/*�������⴦��--�������,�������*/
void Out_Ku_L(void){
    //����
    if( (road_Left>=30) && (road_Right>=30) && (state==0)){
        car_run_flag=1;
        element_flag=1;
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=0;
        Target_Speed2=70;
        state=1;
    }
    if((state==1) && (road_Left-road_temp_L > 10) && (road_Right-road_temp_R > 50) ){
        Target_Speed1=SPEED_L;
        Target_Speed2=SPEED_R;
        element_flag=0;
        state=2;
    }
}

/*���·�ϴ���--��չ��ϰ�*/
void Barrier_L(void)
{
    if(barrier_state==0  && (tof_distance<=500) ){
        if(barrier_pre_flag==0){
            road_temp_L=road_Left;
            road_temp_R=road_Right;
            barrier_pre_flag=1;
        }

        if(road_Left - road_temp_L > 20 &&  road_Right - road_temp_R >20 && (tof_distance<=300) ){
            barrier_state=1;
            barrier_pre_flag=0;
        }
        else if( road_Left - road_temp_L > 50 && road_Right - road_temp_R >50 && (tof_distance>300) ){
            road_temp_L=0;
            road_temp_R=0;
            barrier_pre_flag=0;
        }
    }
    if( barrier_state==1 && (tof_distance<=300) ){
        element_flag=1; //�رշ���
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=-60;
        Target_Speed2=-60;
        barrier_state=2;
    }
    if(barrier_state==2 && road_temp_L-road_Left>=10 && road_temp_R-road_Right>=10){
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=0;
        Target_Speed2=70;
        barrier_state=3;
    }
    if(barrier_state==3 && road_Right-road_temp_R>22){
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=50;
        Target_Speed2=50;
        barrier_state=4;
    }
    if(barrier_state==4 && road_Right-road_temp_R>55 && road_Left-road_temp_L>55){
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=70;
        Target_Speed2=0;
        barrier_state=5;
    }
   if(barrier_state==5 && road_Left-road_temp_L>50){//45С�ˣ��ղ���ȥ  50�����ԣ���������ζ����ˣ�������ʱ��Ƚϼ��ޣ�����·�Ϲ���
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=40;
        Target_Speed2=40;
        barrier_state=6;

        element_flag=0;
        camera_flag=1;//��������ͷѭ��
    }
    if(barrier_state==6 && road_Left-road_temp_L>=120 && road_Right-road_temp_R>=120){
        Target_Speed1=SPEED_L;
        Target_Speed2=SPEED_R;
        barrier_state=0;

        camera_flag=0;
    }

}
/*���·�ϴ���--�ҹչ��ϰ�*/
void Barrier_R(void){
    if(barrier_state==0  && (tof_distance<=500) ){
        if(barrier_pre_flag==0){
            road_temp_L=road_Left;
            road_temp_R=road_Right;
            barrier_pre_flag=1;
        }
        if(road_Left - road_temp_L > 20 &&  road_Right - road_temp_R >20 && (tof_distance<=300) ){
            barrier_state=1;
            barrier_pre_flag=0;
        }
        else if( road_Left - road_temp_L > 50 && road_Right - road_temp_R >50 && (tof_distance>300) ){
            road_temp_L=0;
            road_temp_R=0;
            barrier_pre_flag=0;
        }
    }
    if( barrier_state==1 && (tof_distance<=300) ){
        element_flag=1; //�رշ���
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=-60;
        Target_Speed2=-60;
        barrier_state=2;
    }
    if(barrier_state==2 && road_temp_L-road_Left>=10 && road_temp_R-road_Right>=10){
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=70;
        Target_Speed2=0;
        barrier_state=3;
    }
    if(barrier_state==3 && road_Left - road_temp_L > 22){
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=50;
        Target_Speed2=50;
        barrier_state=4;
    }
    if(barrier_state==4 && road_Right-road_temp_R>55 && road_Left-road_temp_L>55){
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=0;
        Target_Speed2=70;
        barrier_state=5;
    }
   if(barrier_state==5 && road_Right-road_temp_R>40){   //45����е��װ�Ϻ����;�����Ǵ�Ǵ���������ͷѭ����ǵģ�
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=40;
        Target_Speed2=40;
        barrier_state=6;

        element_flag=0;
        camera_flag=1;//��������ͷѭ��
    }
    if(barrier_state==6 && road_Left-road_temp_L>=120 && road_Right-road_temp_R>=120){
        Target_Speed1=SPEED_L;
        Target_Speed2=SPEED_R;

        barrier_state=0;
        camera_flag=0;
    }
}

