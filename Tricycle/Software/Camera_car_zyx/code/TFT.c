/*
 * TFT.c
 *
 *  Created on: 2023年7月1日
 *      Author: ZYX
 */
#include "headfile.h"
void TFT_show(void){
#if 1       //测量赛道最大值
    tft180_show_string(0, 16*0, "L_min:");
    tft180_show_int(60,16*0,ADC_Left_Min,4);

    tft180_show_string(0, 16*1, "L_max:");
    tft180_show_int(60,16*1,ADC_Left_Max,4);

    tft180_show_string(0, 16*2, "R_min:");
    tft180_show_int(60,16*2,ADC_Right_Min,4);

    tft180_show_string(0, 16*3, "R_max:");
    tft180_show_int(60,16*3,ADC_Right_Max,4);

    tft180_show_string(0, 16*4, "L_A_min:");
    tft180_show_int(60,16*4,ADC_Left_Angle_Min,4);

    tft180_show_string(0, 16*5, "L_A_max:");
    tft180_show_int(60,16*5,ADC_Left_Angle_Max,4);

    tft180_show_string(0, 16*6, "R_A_min:");
    tft180_show_int(60,16*6,ADC_Right_Angle_Min,4);

    tft180_show_string(0, 16*7, "R_A_max:");
    tft180_show_int(60,16*7,ADC_Right_Angle_Max,4);
#endif

#if 0
    tft180_show_string(0, 16*0, "SWITCH1:");
    tft180_show_int(60,16*0,gpio_get_level(SWITCH_1),4);
    tft180_show_string(0, 16*1, "SWITCH2:");
    tft180_show_int(60,16*1,gpio_get_level(SWITCH_2),4);
#endif

#if 0
    /*状态位*/
    tft180_show_string(0, 16*0, "state:");
    tft180_show_int(60,16*0,barrier_state,4);
#endif

#if 0
    /*编码器积分路径*/
    tft180_show_string(0, 16*1, "road_t_L:");
    tft180_show_float(60,16*1,road_temp_L,4,2);
    tft180_show_string(0, 16*2, "road_t_R:");
    tft180_show_float(60,16*2,road_temp_R,4,2);

    tft180_show_string(0, 16*4, "road_L:");
    tft180_show_float(60,16*4,road_Left,4,2);
    tft180_show_string(0, 16*5, "road_R:");
    tft180_show_float(60,16*5,road_Right,4,2);
    tft180_show_string(0, 16*6, "sum:");
    tft180_show_float(60,16*6,road_sum,4,2);
#endif

#if 0
/*归一化后的电感值*/
    tft180_show_string(0, 16*4, "Left_A:");
    tft180_show_int(60,16*4,ADC_Left_Angle,4);
    tft180_show_string(0, 16*5, "Left:");
    tft180_show_int(60,16*5,ADC_Left,4);
    tft180_show_string(0, 16*6, "Right:");
    tft180_show_int(60,16*6,ADC_Right,4);
    tft180_show_string(0, 16*5, "Right_A:");
    tft180_show_int(60,16*5,ADC_Right_Angle,4);
    tft180_show_string(0, 16*6, "error:");
    tft180_show_float(60,16*6,inductor_error,2,3);
    tft180_show_string(0, 16*7, "Hall:");
    tft180_show_int(60,16*7,Hall_detection(),2);
#endif
#if 1
/*TOF*/
    tft180_show_string(80, 16*8, "mm");
    tft180_show_uint(0, 16*8, tof_distance, 4);
#endif
}

/*图像数据显示*/
void TFT_camerashow(void){
    if(mt9v03x_finish_flag)                                                     //总钻风读取到图像
    {
//        tft180_show_gray_image(0,0,Bin_Image[0],MT9V03X_W,MT9V03X_H,MT9V03X_W/2,MT9V03X_H/2,0);
//        TFTSPI_BinRoadSide(ImageSide);                    //左右边线
//        TFTSPI_BinRoad_UpdownSide(UpdowmSide);            //上下边线

        mt9v03x_finish_flag = 0;
    }
}
