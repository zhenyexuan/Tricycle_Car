///*
// * image_process.h
// *
// *  Created on: 2023年7月1日
// *      Author: ZYX
// */
//
//#ifndef CODE_IMAGE_PROCESS_H_
//#define CODE_IMAGE_PROCESS_H_
//#include "headfile.h"
//
//#define MT9V03X_W               (188)                                           // 图像宽度     范围 [1-752]
//#define MT9V03X_H               (120)
//
//#define ROAD_MAIN_ROW      y    //主跑行
//#define ROAD_START_ROW     115 //使用起始行
//#define ROAD_END_ROW       10       //使用结束行
//
//extern int16 y;
//extern int16 g_sSteeringError;
//extern uint8 Round_Flag;
//extern uint8 Process_Flag;
//extern uint8 OpenRoad_Flag ; //断路标志位
//extern uint8 motor_flag;
////边线数组
//extern uint8 ImageSide[MT9V03X_H][2];//上下边线
//extern uint8 UpdowmSide[2][MT9V03X_W];//左右边线
//extern uint8 Roadwide[MT9V03X_H];             //赛道宽度
//
//extern uint8 rightline[MT9V03X_H];//右边线，索引值是y坐标，值是x坐标
//extern uint8 leftline[MT9V03X_H];//左边线，索引值是y坐标，值是x坐标
//extern uint8 upline[MT9V03X_W];   //上边线，索引值是x坐标，值是y坐标
//extern uint8 downline[MT9V03X_W]; //下边线，索引值是x坐标，值是y坐标
//
//extern uint8 right_flag[MT9V03X_H];//找到右边线标志位，找到为1，没找到为0，没找到的话rightline[]值是187（图像右边缘）
//extern uint8 left_flag[MT9V03X_H];//找到左边线标志位，找到为1，没找到为0，没找到的话leftline[]值是0(图像左边缘）
//extern uint8 up_flag[MT9V03X_W];   //找到上边线标志位，找到为1，没找到为0，没找到的话upline[]值是119（图像下边缘）
//extern uint8 down_flag[MT9V03X_W]; //找到下边线标志位，找到为1，没找到为0，没找到的话downline[]值是0(图像上边缘）
//
//extern uint8 road_width[MT9V03X_H];//路宽
//
//extern uint8 centerline[MT9V03X_H];//中线
//
//extern uint8 errL, errR;
//extern uint8 leftState, rightState;
///*找左右边线*/
//void ImageGetSide(const uint8 *image_in,uint16 row,uint16 col);
///*找上下边线*/
//uint8 UpdownSideGet(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageOut[2][MT9V03X_W]);
///*找上下边线2*/
//void UpdownSideGet2(const uint8 *image_in,uint16 row,uint16 col);
//uint8 RoadIsNoSide(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageOut[MT9V03X_H][2], uint8 lineIndex);
//void RoundaboutGetSide(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageSide[MT9V03X_H][2], uint8 status);
//uint8 RoundaboutGetArc(uint8 imageSide[MT9V03X_H][2], uint8 status, uint8 num,uint8* index);
//void ImageAddingLine(uint8 imageSide[MT9V03X_H][2], uint8 status, uint8 startX, uint8 startY, uint8 endX, uint8 endY);
///*检测圆环*/
//uint8 RoadIsRoundabout(uint8 image[MT9V03X_H][2], uint8 *flag);
//void RoundaboutProcess(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageSide[MT9V03X_H][2], uint8 UpdowmSide[2][MT9V03X_W], uint8* state);
//void InputOpening(uint8  imageInput[MT9V03X_H][MT9V03X_W],uint8 *Flag);
//void OutOpening(uint8  imageInput[MT9V03X_H][MT9V03X_W],uint8 *Flag);
//void OpeningProcess(uint8 Upimage[2][MT9V03X_W],uint8 imageSideinput[MT9V03X_H][2],uint8  imageInput[MT9V03X_H][MT9V03X_W],uint8 *Flag);
//void CameraCar (void);
//
//#endif /* CODE_IMAGE_PROCESS_H_ */
