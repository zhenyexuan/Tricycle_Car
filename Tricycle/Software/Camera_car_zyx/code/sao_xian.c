/*
 * sao_xian.c
 *
 *  Created on: 2023��7��16��
 *      Author: ZYX
 */
#include "headfile.h"
#define            tft180_x_max         160
#define            tft180_y_max         128
//����ͷѭ����־λ
uint8 camera_flag=0;
//����ͷ�������
float camera_error;

//ԭͼ
uint8 *Image_addr=mt9v03x_image[0];             //ԭͼ���ַ
uint8 binaryImage[MT9V03X_H][MT9V03X_W];        //��ֵ��ͼ������
uint8 *binaryImage_addr=binaryImage[0];         //��ֵ��ͼ���ַ
uint8 threshold;                                //ͼ����ֵ
uint8 aim_point=MT9V03X_H/2;                    //Ԥê��

//ѹ�����ͼ��
uint8 halvedImage[MT9V03X_HALVED_H][MT9V03X_HALVED_W];          //ѹ����ͼ������
uint8 halvedbinaryImage[MT9V03X_HALVED_H][MT9V03X_HALVED_W];    //ѹ�����ֵ��ͼ������
uint8 *halvedImage_addr = halvedImage[0] ;                       //ѹ����ͼ���ַ
uint8 *halvedbinaryImage_addr = halvedbinaryImage[0];           //ѹ�����ֵ��ͼ���ַ
uint8 aim_point_H=MT9V03X_HALVED_H/2;                           //ѹ�����ֵ��ͼ��Ԥê��
uint8 threshold1;

uint8 rightline[MT9V03X_HALVED_H];//�ұ��ߣ�����ֵ��y���ֵ꣬��x����
uint8 leftline[MT9V03X_HALVED_H];//����ߣ�����ֵ��y���ֵ꣬��x����

uint8 right_flag[60];//�ҵ��ұ��߱�־λ���ҵ�Ϊ1��û�ҵ�Ϊ0��û�ҵ��Ļ�rightline[]ֵ��187��ͼ���ұ�Ե��
uint8 left_flag[60];//�ҵ�����߱�־λ���ҵ�Ϊ1��û�ҵ�Ϊ0��û�ҵ��Ļ�leftline[]ֵ��0(ͼ�����Ե��

uint8 road_width[60];//·��

uint8 centerline[60];//����

/*  mt9v03x_image[y][x]��ͼ������
 * 0�����ɫ��255�����ɫ��Y���ϵ������꣬X���ϵĺ����꣬
 * �����򵥵�forѭ��������ͼ�Ͷ��ˣ���������if�Ǹ��߽���жϣ�����һ��if�ǶԱ߽�����ơ�
 * row:���� --> MT9V03X_H
 * col:���� --> MT9V03X_W
 * */
void sao_xian(const uint8 *image_in,uint8 row,uint8 col)
{
    uint8 y=0;     //y����
    uint8 x=0;     //x����
    static uint8 old; //��һ�ε�����λ�ã�x���꣩
    for (y = row-5; y >= 5; y--) //����
    {
        for (x = old; x < col - 2; x++) //���Һ���
        {
            if ( *(image_in + y*col + x) == 255 &&
                    *(image_in + y*col + x+1) == 0 &&
                    *(image_in + y*col + x+2) == 0)
            {
                rightline[y] = x;
                right_flag[y] =1;
                break;
            }
        }
        if (x == col - 2)
        {
            right_flag[y] =0;
            rightline[y] = MT9V03X_HALVED_W-1;//�Ҳ��ԵλĬ��Ϊ187�����������λ
        }
/*���ϱߵ�ͬ��*/
        for (x = old; x >= 2; x--) //�������
        {
            if ( *(image_in + y*col + x) == 255 &&
                    *(image_in + y*col + x-1) == 0 &&
                    *(image_in + y*col + x-2) == 0)
            {
                leftline[y] = x;
                left_flag[y] = 1;
                break;
            }
        }
        if (x == 1)
        {
            left_flag[y] = 0;
            leftline[y] = x;
        }

        road_width[y] = rightline[y] - leftline[y];//����������ȣ������һ��һά������
        centerline[y] = (rightline[y] + leftline[y]) / 2;//�������ߵ�λ�ã������һά�����У�centerline[line] ���ڵ�Y=line�����ߵ�X���ꡣ
        old = centerline[y];//����һ�ε�����λ�ü��������old���´�����Ϊ�����Ѱ�ҡ�
/*
        //����Ļ�л������ߣ����ұ���
        tft180_draw_point(leftline[y]/2,y/2,RGB565_BLUE);
        tft180_draw_point(rightline[y]/2,y/2,RGB565_BLUE);
        tft180_draw_point(centerline[y]/2,y/2,RGB565_RED);
*/
    }
}

/*  �Ҷ�ͼ���ֵ��
 *  image_in:���ڶ�ֵ�������ͼ��
 *  row:���� --> MT9V03X_H
 *  col:���� --> MT9V03X_W
*/
void ImageBinary(const uint8 *image_in,uint8 *image_out,uint8 row,uint8 col)
{
  uint16 grayCount[256]={0};
  uint32 graySum=0;
  uint16 pixelSum=0;
  float graypro[256];

  uint16 i,j;        //XUAN������ĳ�uint8���ԣ�
  uint16 step=2;//���

  for(i=0;i<row;i+=step){
    for(j=0;j<col;j+=step){
      grayCount[ *(image_in + i*col + j) ]++;
      graySum += *(image_in + i*col + j) ;
      pixelSum++;
    }
  }

  for(i=0;i<256;i++){
    graypro[i]=(float)grayCount[i]/pixelSum;
  }

  float w0,w1,u0Temp,u1Temp,u0,u1,u,deltaTemp,deltaMax;
  deltaMax=0;
  for(i=0;i<256;i++){
    w0=w1=u0Temp=u1Temp=u0=u1=u=deltaTemp=0;
    for(j=0;j<256;j++){
      if(j<=i){
        w0+=graypro[j];
        u0Temp+=j*graypro[j];
      }
      else{
        w1+=graypro[j];
        u1Temp+=j*graypro[j];
      }
    }
    u0=u0Temp/w0;
    u1=u1Temp/w1;
    u=u0Temp+u1Temp;
    deltaTemp=w0*(u0-u)*(u0-u)+w1*(u1-u)*(u1-u);
    if(deltaTemp>deltaMax){
      deltaMax=deltaTemp;
      threshold=i;
    }
  }

  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
        *(image_out + i*col + j) = ( *(image_in + i*col + j) >threshold)?255:0;
    }
  }
}

/* ͼ��ѹ�� ��ͼ��ѹ��3/4 */
void halve_image(const uint8 *p_in,uint8 *p_out,uint8 row,uint8 col)
{
    uint8 i, j;
    for (i = 0; i<row/2; i++) {
        for (j = 0;j<col/2; j++) {
            *(p_out+i*col/2+j)=*(p_in+i*2*col+j*2);  // д��ѹ����ͼ���µ�����
        }
    }
}

/*      ����Ļ�ϻ����ߣ����ұ���     */
void Draw_line(uint8 row)
{
    for(uint16 y=row-10;y>=10;y--){
        tft180_draw_point(leftline[y],y,RGB565_BLUE);
        tft180_draw_point(leftline[y] + 1,y,RGB565_BLUE);

        tft180_draw_point(rightline[y],y,RGB565_BLUE);
       tft180_draw_point(rightline[y] - 1,y,RGB565_BLUE);

        tft180_draw_point(centerline[y],y,RGB565_RED);
        tft180_draw_point(centerline[y] + 1,y,RGB565_RED);
    }
}

/**
 * @brief TFT180_Draw_cross ��Ļ���ơ�
 *
 * @param x
 * @param y
 * @param color
 *
 */
void TFT180_Draw_Cross(uint16_t x, uint16_t y, uint16_t color)
{
    if(x <= 4) x = 4;
    else if(x >= tft180_x_max -5) x = tft180_x_max -5;    //tft180_x_max=160
    if(y <= 4) y = 4;
    else if(y >= tft180_y_max -5) y = tft180_y_max -5;    //tft180_y_max=128

    zf_assert(x-4 >= 0 && x <= tft180_x_max -5); //tft180_x_max=160
    zf_assert(y-4 >= 0 && y <= tft180_y_max -5); //tft180_y_max=128

    TFT180_Draw_Line(x-4, y-4, x+4, y+4, color);
    TFT180_Draw_Line(x-4, y+4, x+4, y-4, color);
}
/**
 * @brief TFT180_Draw_Line ��Ļ����ֱ��
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param color
 *
 */
void TFT180_Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    zf_assert(x1 <= tft180_x_max);  //tft180_x_max=160
    zf_assert(y1 <= tft180_y_max);  //tft180_y_max=128
    zf_assert(x1 <= tft180_x_max);  //tft180_x_max=160
    zf_assert(y2 <= tft180_y_max);  //tft180_y_max=128
    zf_assert(x2 <= tft180_x_max);  //tft180_x_max=160
    zf_assert(y2 <= tft180_y_max);  //tft180_y_max=128

    uint16 t;
    int xerr=0,yerr=0,delta_x,delta_y,distance;
    int incx,incy;
//    int uRow,uCol;
    uint16 uRow,uCol;
    delta_x=x2-x1; //������������
    delta_y=y2-y1;
    uRow=x1;
    uCol=y1;
    if(delta_x>0) incx=1; //���õ�������
    else if(delta_x==0) incx=0;//��ֱ��
    else {
        incx=-1;
        delta_x=-delta_x;
    }
    if(delta_y>0) incy=1;
    else if(delta_y==0) incy=0;//ˮƽ��
    else{
        incy=-1;
        delta_y=-delta_y;
    }
    if(delta_x>delta_y) distance=delta_x; //ѡȡ��������������
    else distance = delta_y;
    for(t=0;t<=distance+1;t++) { //�������
        tft180_draw_point(uRow,uCol, color);//����
        xerr+=delta_x ;
        yerr+=delta_y ;
        if(xerr>distance) {
            xerr-=distance;
            uRow+=incx;
        }
        if(yerr>distance) {
            yerr-=distance;
            uCol+=incy;
        }
    }
}

