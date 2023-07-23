///*
// * image_process.h
// *
// *  Created on: 2023��7��1��
// *      Author: ZYX
// */
//
//#ifndef CODE_IMAGE_PROCESS_H_
//#define CODE_IMAGE_PROCESS_H_
//#include "headfile.h"
//
//#define MT9V03X_W               (188)                                           // ͼ����     ��Χ [1-752]
//#define MT9V03X_H               (120)
//
//#define ROAD_MAIN_ROW      y    //������
//#define ROAD_START_ROW     115 //ʹ����ʼ��
//#define ROAD_END_ROW       10       //ʹ�ý�����
//
//extern int16 y;
//extern int16 g_sSteeringError;
//extern uint8 Round_Flag;
//extern uint8 Process_Flag;
//extern uint8 OpenRoad_Flag ; //��·��־λ
//extern uint8 motor_flag;
////��������
//extern uint8 ImageSide[MT9V03X_H][2];//���±���
//extern uint8 UpdowmSide[2][MT9V03X_W];//���ұ���
//extern uint8 Roadwide[MT9V03X_H];             //�������
//
//extern uint8 rightline[MT9V03X_H];//�ұ��ߣ�����ֵ��y���ֵ꣬��x����
//extern uint8 leftline[MT9V03X_H];//����ߣ�����ֵ��y���ֵ꣬��x����
//extern uint8 upline[MT9V03X_W];   //�ϱ��ߣ�����ֵ��x���ֵ꣬��y����
//extern uint8 downline[MT9V03X_W]; //�±��ߣ�����ֵ��x���ֵ꣬��y����
//
//extern uint8 right_flag[MT9V03X_H];//�ҵ��ұ��߱�־λ���ҵ�Ϊ1��û�ҵ�Ϊ0��û�ҵ��Ļ�rightline[]ֵ��187��ͼ���ұ�Ե��
//extern uint8 left_flag[MT9V03X_H];//�ҵ�����߱�־λ���ҵ�Ϊ1��û�ҵ�Ϊ0��û�ҵ��Ļ�leftline[]ֵ��0(ͼ�����Ե��
//extern uint8 up_flag[MT9V03X_W];   //�ҵ��ϱ��߱�־λ���ҵ�Ϊ1��û�ҵ�Ϊ0��û�ҵ��Ļ�upline[]ֵ��119��ͼ���±�Ե��
//extern uint8 down_flag[MT9V03X_W]; //�ҵ��±��߱�־λ���ҵ�Ϊ1��û�ҵ�Ϊ0��û�ҵ��Ļ�downline[]ֵ��0(ͼ���ϱ�Ե��
//
//extern uint8 road_width[MT9V03X_H];//·��
//
//extern uint8 centerline[MT9V03X_H];//����
//
//extern uint8 errL, errR;
//extern uint8 leftState, rightState;
///*�����ұ���*/
//void ImageGetSide(const uint8 *image_in,uint16 row,uint16 col);
///*�����±���*/
//uint8 UpdownSideGet(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageOut[2][MT9V03X_W]);
///*�����±���2*/
//void UpdownSideGet2(const uint8 *image_in,uint16 row,uint16 col);
//uint8 RoadIsNoSide(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageOut[MT9V03X_H][2], uint8 lineIndex);
//void RoundaboutGetSide(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageSide[MT9V03X_H][2], uint8 status);
//uint8 RoundaboutGetArc(uint8 imageSide[MT9V03X_H][2], uint8 status, uint8 num,uint8* index);
//void ImageAddingLine(uint8 imageSide[MT9V03X_H][2], uint8 status, uint8 startX, uint8 startY, uint8 endX, uint8 endY);
///*���Բ��*/
//uint8 RoadIsRoundabout(uint8 image[MT9V03X_H][2], uint8 *flag);
//void RoundaboutProcess(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageSide[MT9V03X_H][2], uint8 UpdowmSide[2][MT9V03X_W], uint8* state);
//void InputOpening(uint8  imageInput[MT9V03X_H][MT9V03X_W],uint8 *Flag);
//void OutOpening(uint8  imageInput[MT9V03X_H][MT9V03X_W],uint8 *Flag);
//void OpeningProcess(uint8 Upimage[2][MT9V03X_W],uint8 imageSideinput[MT9V03X_H][2],uint8  imageInput[MT9V03X_H][MT9V03X_W],uint8 *Flag);
//void CameraCar (void);
//
//#endif /* CODE_IMAGE_PROCESS_H_ */
