/*
 * sao_xian.h
 *
 *  Created on: 2023��7��16��
 *      Author: ZYX
 */

#ifndef CODE_SAO_XIAN_H_
#define CODE_SAO_XIAN_H_
#include "headfile.h"

#define MT9V03X_HALVED_W               MT9V03X_W/2
#define MT9V03X_HALVED_H               MT9V03X_H/2

//����ͷѭ����־λ
extern uint8 camera_flag;
//����ͷ�������
extern float camera_error;

//ԭͼ
extern uint8 *Image_addr;             //ԭͼ���ַ
extern uint8 binaryImage[120][188];        //��ֵ��ͼ������
extern uint8 *binaryImage_addr;         //��ֵ��ͼ���ַ
extern uint8 threshold;                                //ͼ����ֵ
extern uint8 aim_point;                    //Ԥê��

//ѹ�����ͼ��
extern uint8 halvedImage[120/2][188/2];          //ѹ����ͼ������
extern uint8 halvedbinaryImage[120/2][188/2];    //ѹ�����ֵ��ͼ������
extern uint8 *halvedImage_addr;                       //ѹ����ͼ���ַ
extern uint8 *halvedbinaryImage_addr;           //ѹ�����ֵ��ͼ���ַ
extern uint8 aim_point_H;                           //ѹ�����ֵ��ͼ��Ԥê��
extern uint8 threshold1;

//�����60��MT9V03X_HALVED_H,��֪��Ϊʲô��MT9V03X_HALVED_H�ᱨ��ctc E231: expression must be constant��
extern uint8 rightline[60];//�ұ��ߣ�����ֵ��y���ֵ꣬��x����
extern uint8 leftline[60];//����ߣ�����ֵ��y���ֵ꣬��x����

extern uint8 right_flag[60];//�ҵ��ұ��߱�־λ���ҵ�Ϊ1��û�ҵ�Ϊ0��û�ҵ��Ļ�rightline[]ֵ��187��ͼ���ұ�Ե��
extern uint8 left_flag[60];//�ҵ�����߱�־λ���ҵ�Ϊ1��û�ҵ�Ϊ0��û�ҵ��Ļ�leftline[]ֵ��0(ͼ�����Ե��

extern uint8 road_width[60];//·��

extern uint8 centerline[60];//����

/*ɨ�ߺ���*/
void sao_xian(const uint8 *image_in,uint8 row,uint8 col);
/*�Ҷ�ͼ���ֵ��*/
void ImageBinary(const uint8 *image_in,uint8 *image_out,uint8 row,uint8 col);
/* ͼ��ѹ�� ��ͼ��ѹ��3/4 */
void halve_image(const uint8 *p_in,uint8 *p_out,uint8 row,uint8 col);
void Draw_line(uint8 row);
/*��Ļ����ֱ��*/
void TFT180_Draw_Line(uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint16 color);
/*��Ļ����X*/
void TFT180_Draw_Cross(uint16 x, uint16 y, uint16 color);


#endif /* CODE_SAO_XIAN_H_ */
