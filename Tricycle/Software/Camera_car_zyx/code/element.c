/*
 * element.c
 *
 *  Created on: 2023年7月15日
 *      Author: ZYX
 */
#include "headfile.h"

uint8 car_run_flag=1;   //小车运行标志位
uint8 element_flag=0;   //元素标志位
uint8 out_ku_flag=0;   //出库标志位
uint8 barrier_pre_flag=0;   //横断预标志位
uint8 barrier_flag=0;   //横断标志位
uint8 state=0;      //出入库状态位
uint8 state_alone=0;      //出入库状态位
uint8 barrier_state=0;  //横断标志位

/*开环出库处理--向右出库,向右入库*/
void Out_Ku_R(void){
    //出库
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

/*开环入库处理--向右出库,向右入库*/
void In_Ku_R(void){
    //入库
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
/*单独   开环入库处理--向右出库,向右入库*/
void In_Ku_R_alone(void){
    //入库
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
        car_run_flag=0; //不让小车跑
        motor_run(0,0);
    }
}

/*开环入库处理--向左出库,向左入库*/
void In_Ku_L(void)
{
    //入库
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

/*开环入库处理--向左出库,向左入库*/
void In_Ku_L_alone(void)
{
    //入库
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

/*开环出库处理--向左出库,向左入库*/
void Out_Ku_L(void){
    //出库
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

/*横断路障处理--左拐过障碍*/
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
        element_flag=1; //关闭方向环
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
   if(barrier_state==5 && road_Left-road_temp_L>50){//45小了，拐不过去  50还可以，试了四五次都进了，不过有时候比较极限，贴着路障过的
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=40;
        Target_Speed2=40;
        barrier_state=6;

        element_flag=0;
        camera_flag=1;//开启摄像头循迹
    }
    if(barrier_state==6 && road_Left-road_temp_L>=120 && road_Right-road_temp_R>=120){
        Target_Speed1=SPEED_L;
        Target_Speed2=SPEED_R;
        barrier_state=0;

        camera_flag=0;
    }

}
/*横断路障处理--右拐过障碍*/
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
        element_flag=1; //关闭方向环
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
   if(barrier_state==5 && road_Right-road_temp_R>40){   //45打角有点大装上横断了;好像不是打角大了是摄像头循迹打角的；
        road_temp_L=road_Left;
        road_temp_R=road_Right;
        Target_Speed1=40;
        Target_Speed2=40;
        barrier_state=6;

        element_flag=0;
        camera_flag=1;//开启摄像头循迹
    }
    if(barrier_state==6 && road_Left-road_temp_L>=120 && road_Right-road_temp_R>=120){
        Target_Speed1=SPEED_L;
        Target_Speed2=SPEED_R;

        barrier_state=0;
        camera_flag=0;
    }
}

