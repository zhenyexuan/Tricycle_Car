/*
 * sao_xian.h
 *
 *  Created on: 2023年7月16日
 *      Author: ZYX
 */

#ifndef CODE_SAO_XIAN_H_
#define CODE_SAO_XIAN_H_
#include "headfile.h"

#define MT9V03X_HALVED_W               MT9V03X_W/2
#define MT9V03X_HALVED_H               MT9V03X_H/2

//摄像头循迹标志位
extern uint8 camera_flag;
//摄像头中线误差
extern float camera_error;

//原图
extern uint8 *Image_addr;             //原图像地址
extern uint8 binaryImage[120][188];        //二值化图像数组
extern uint8 *binaryImage_addr;         //二值化图像地址
extern uint8 threshold;                                //图像阈值
extern uint8 aim_point;                    //预锚点

//压缩后的图像
extern uint8 halvedImage[120/2][188/2];          //压缩后图像数组
extern uint8 halvedbinaryImage[120/2][188/2];    //压缩后二值化图像数组
extern uint8 *halvedImage_addr;                       //压缩后图像地址
extern uint8 *halvedbinaryImage_addr;           //压缩后二值化图像地址
extern uint8 aim_point_H;                           //压缩后二值化图像预锚点
extern uint8 threshold1;

//这里的60是MT9V03X_HALVED_H,不知道为什么用MT9V03X_HALVED_H会报错“ctc E231: expression must be constant”
extern uint8 rightline[60];//右边线，索引值是y坐标，值是x坐标
extern uint8 leftline[60];//左边线，索引值是y坐标，值是x坐标

extern uint8 right_flag[60];//找到右边线标志位，找到为1，没找到为0，没找到的话rightline[]值是187（图像右边缘）
extern uint8 left_flag[60];//找到左边线标志位，找到为1，没找到为0，没找到的话leftline[]值是0(图像左边缘）

extern uint8 road_width[60];//路宽

extern uint8 centerline[60];//中线

/*扫线函数*/
void sao_xian(const uint8 *image_in,uint8 row,uint8 col);
/*灰度图像二值化*/
void ImageBinary(const uint8 *image_in,uint8 *image_out,uint8 row,uint8 col);
/* 图像压缩 将图像压缩3/4 */
void halve_image(const uint8 *p_in,uint8 *p_out,uint8 row,uint8 col);
void Draw_line(uint8 row);
/*屏幕绘制直线*/
void TFT180_Draw_Line(uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint16 color);
/*屏幕绘制X*/
void TFT180_Draw_Cross(uint16 x, uint16 y, uint16 color);


#endif /* CODE_SAO_XIAN_H_ */
