/*
 * IPS.c
 *
 *  Created on: 2023年7月2日
 *      Author: ZYX
 */
#include "headfile.h"
/*屏幕数据显示*/
void ips200_show(void){
//    ips200_show_string(0, 16*8, "Left_angle:");
//    ips200_show_int(120,16*8,LnowADC_2,4);
//    ips200_show_string(0, 16*9, "Left:");
//    ips200_show_int(120,16*9,LnowADC_0,4);
//    ips200_show_string(0, 16*10, "Right:");
//    ips200_show_int(120,16*10,LnowADC_1,4);
//    ips200_show_string(0, 16*11, "Right_angle:");
//    ips200_show_int(120,16*11,LnowADC_3,4);



//    //电机PID
//    ips200_show_string(0, 16*8, "MotorDuty1:");
//    ips200_show_int(120,16*8,MotorDuty1,4);
//    ips200_show_string(0, 16*9, "MotorDuty2:");
//    ips200_show_int(120,16*9,MotorDuty2,4);
//    ips200_show_string(0, 16*10, "Target_Speed1:");
//    ips200_show_int(120,16*10,Target_Speed1,4);
//    ips200_show_string(0, 16*11, "Target_Speed2:");
//    ips200_show_int(120,16*11,Target_Speed2,4);
//    ips200_show_string(0, 16*12, "encoder_Left:");
//    ips200_show_int(120,16*12,encoder_Left,4);
//    ips200_show_string(0, 16*13, "encoder_Right:");
//    ips200_show_int(120,16*13,encoder_Right,4);
//    ips200_show_string(0, 16*14, "threshold_IPS:");
//    ips200_show_int(120,16*14,threshold_IPS,4);


    //圆环
//    ips200_show_string(0, 16*8, "Round_Flag:");
//    ips200_show_int(120,16*8,Round_Flag,3);
//    ips200_show_string(0, 16*9, "Process_Flag:");
//    ips200_show_int(120,16*9,Process_Flag,3);
//    ips200_show_string(0, 16*10, "OpenRoad_Flag:");
//    ips200_show_int(120,16*10,OpenRoad_Flag,3);
//    ips200_show_string(0, 16*11, "rightState:");
//    ips200_show_int(120,16*11,rightState,3);
//    ips200_show_string(0, 16*12, "errL:");
//    ips200_show_int(120,16*12,errL,3);
//    ips200_show_string(0, 16*13, "leftState:");
//    ips200_show_int(120,16*13,leftState,3);
//    ips200_show_string(0, 16*14, "errR:");
//    ips200_show_int(120,16*14,errR,3);
//    ips200_show_int(0,16*15,ImageSide[ROAD_START_ROW-10][0],3);
//    ips200_show_int(0,16*16,ImageSide[ROAD_START_ROW-10][1],3);

//    static int i=0;
//    switch(Pit_Key())
//    {
//        case 1:i++;break;
//        case 2:i+=2;break;
//        case 3:i--;break;
//        case 4:i-=2;break;
//    }
//    ips200_show_string(0, 16*12, "i:");
//    ips200_show_int(120,16*12,i,4);
}

///*图像数据显示*/
//void ips200_camerashow(void){
//    if(mt9v03x_finish_flag)          //总钻风读取到图像
//    {
//        ips200_show_gray_image(0,0,Bin_Image[0],MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
//        ips200_BinRoad_Side(ImageSide);         //左右边线
//        ips200_BinRoad_UpdownSide(UpdowmSide);  //上下边线
//
//        mt9v03x_finish_flag = 0;
//    }
//}
///*画左右边线*/
//void ips200_BinRoad_Side(uint8 ImageSide[MT9V03X_H][2])
//{
//    for(uint16 i = ROAD_END_ROW; i < ROAD_START_ROW; i++)
//    {
//        ips200_draw_point(ImageSide[i][0], i, RGB565_RED);
//        ips200_draw_point(ImageSide[i][0]+1, i, RGB565_RED);
//        ips200_draw_point(ImageSide[i][1], i, RGB565_PURPLE);
//        ips200_draw_point(ImageSide[i][1]+1, i, RGB565_PURPLE);
//       ips200_draw_point((ImageSide[i][0] + ImageSide[i][1])/2,i,RGB565_GREEN);
//    }
//}
///*画上下边线*/
//void ips200_BinRoad_UpdownSide(uint8 image_in[2][MT9V03X_W])
//{
//    for(uint16 i = 0; i < MT9V03X_W; i++)
//    {
//        ips200_draw_point(i, image_in[0][i], RGB565_YELLOW);
//        ips200_draw_point(i, image_in[0][i] + 1, RGB565_YELLOW);
//        ips200_draw_point(i, image_in[1][i], RGB565_BLUE);
//        ips200_draw_point(i, image_in[1][i] + 1, RGB565_BLUE);
//        ips200_draw_point(i, (image_in[0][i] + image_in[1][i])/2 ,RGB565_GREEN);
//    }
//}
///*画上下边线*/
//void ips200_BinRoad_UpdownSide2(uint16 *upline,uint16 *downline)
//{
//    for(uint16 i = 0; i < MT9V03X_W ; i++)
//    {
//        ips200_draw_point(i,upline[i],RGB565_YELLOW);
//        ips200_draw_point(i,upline[i]+1,RGB565_YELLOW);
//        ips200_draw_point(i,downline[i],RGB565_BROWN);
//        ips200_draw_point(i,downline[i]-1,RGB565_BROWN);
//    }
//}
