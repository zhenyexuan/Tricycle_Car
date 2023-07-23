#include "headfile.h"
#pragma section all "cpu1_dsram"
// **************************** 代码区域 ***************************/
void core1_main(void)
{
    disable_Watchdog();                     // 关闭看门狗
    interrupt_global_enable(0);             // 打开全局中断
    cpu_wait_event_ready();                 // 等待所有核心初始化完毕
    while (TRUE)
    {
/****************************************  摄像头图像处理--压缩图像  ****************************************/
        if(mt9v03x_finish_flag)
        {
            halve_image(Image_addr,halvedImage_addr,MT9V03X_H,MT9V03X_W);   //压缩图像
            ImageBinary(halvedImage_addr,halvedbinaryImage_addr,MT9V03X_HALVED_H,MT9V03X_HALVED_W);   //图像二值化
            sao_xian(halvedbinaryImage_addr,MT9V03X_HALVED_H,MT9V03X_HALVED_W);

#if 0       //由于双核互斥；摄像头图像显示和参数显示最好只开一个！
            tft180_show_gray_image(0,0,halvedbinaryImage_addr, MT9V03X_HALVED_W, MT9V03X_HALVED_H,MT9V03X_HALVED_W,MT9V03X_HALVED_H,0); //显示图像

            Draw_line(MT9V03X_HALVED_H);    //画出三线
            TFT180_Draw_Cross(centerline[aim_point_H],aim_point_H,RGB565_BLACK);//画出预锚点
            TFT180_Draw_Cross(MT9V03X_HALVED_W/2,aim_point_H,RGB565_PURPLE);//画出屏幕中点
#endif

            mt9v03x_finish_flag = 0;    //在图像使用完毕后  务必清除标志位，否则不会开始采集下一幅图像
        }
/****************************************  电感采集和TOF采集  ****************************************/

        InductorNormal();
        tof_distance=TOF_Get_Distance();    //TOF检测到的距离

/****************************************  出入库总函数  ****************************************/
        //拨码开关控制出库方向
        if(gpio_get_level(SWITCH_1)==0){
       //右拐出库，右拐入库
        Out_Ku_R();
        In_Ku_R();
//        In_Ku_R_alone();
        }
        if(gpio_get_level(SWITCH_1)==1){
        //向左出库
        Out_Ku_L();
        In_Ku_L();
//        In_Ku_L_alone();
        }
/****************************************  横断路障总函数  ****************************************/
#if 0   //左拐过障碍
        Barrier_L();
#endif
#if 0   //右拐过障碍
        Barrier_R();
#endif

//            if(mt9v03x_finish_flag)                                                     //总钻风读取到图像
//            {
//                Get_Current_Img(current_image, mt9v03x_image);                   //获取原始图像
//                Get_Bin_Image(3);                                                //大津法二值化
//                ImageGetSide(*Bin_Image,MT9V03X_H,MT9V03X_W);                    //提取左右边线
//                UpdownSideGet(*Bin_Image,UpdowmSide);                            //提取上下边线

///******************************************************************圆环识别处理*********************************************************/
//            if(Round_Flag == 0 && OpenRoad_Flag==0 && Process_Flag==0 )
//             {
//                 // 检测环岛
//                 RoadIsRoundabout(ImageSide, &Round_Flag);   //一边单调一边丢线
//             }
//            if(Round_Flag)//识别到圆环，圆环处理
//             {
//               // buzzer(100);//识别到环岛，蜂鸣器响一声
//                Process_Flag=2;
//                Target_Speed1 = 65;
//                Target_Speed2 = 65;
//                turn_PID.kp =0.5;
//                turn_PID.kd =0.25;
//                RoundaboutProcess(Bin_Image, ImageSide, UpdowmSide, &Round_Flag);
//             }

//                CameraCar();        //摄像头元素识别控制总函数
//
//                mt9v03x_finish_flag = 0;
//            }
        // 此处编写需要循环执行的代码
    }
}
#pragma section all restore
