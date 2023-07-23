/*
 * sao_xian.c
 *
 *  Created on: 2023年7月16日
 *      Author: ZYX
 */
#include "headfile.h"
#define            tft180_x_max         160
#define            tft180_y_max         128
//摄像头循迹标志位
uint8 camera_flag=0;
//摄像头中线误差
float camera_error;

//原图
uint8 *Image_addr=mt9v03x_image[0];             //原图像地址
uint8 binaryImage[MT9V03X_H][MT9V03X_W];        //二值化图像数组
uint8 *binaryImage_addr=binaryImage[0];         //二值化图像地址
uint8 threshold;                                //图像阈值
uint8 aim_point=MT9V03X_H/2;                    //预锚点

//压缩后的图像
uint8 halvedImage[MT9V03X_HALVED_H][MT9V03X_HALVED_W];          //压缩后图像数组
uint8 halvedbinaryImage[MT9V03X_HALVED_H][MT9V03X_HALVED_W];    //压缩后二值化图像数组
uint8 *halvedImage_addr = halvedImage[0] ;                       //压缩后图像地址
uint8 *halvedbinaryImage_addr = halvedbinaryImage[0];           //压缩后二值化图像地址
uint8 aim_point_H=MT9V03X_HALVED_H/2;                           //压缩后二值化图像预锚点
uint8 threshold1;

uint8 rightline[MT9V03X_HALVED_H];//右边线，索引值是y坐标，值是x坐标
uint8 leftline[MT9V03X_HALVED_H];//左边线，索引值是y坐标，值是x坐标

uint8 right_flag[60];//找到右边线标志位，找到为1，没找到为0，没找到的话rightline[]值是187（图像右边缘）
uint8 left_flag[60];//找到左边线标志位，找到为1，没找到为0，没找到的话leftline[]值是0(图像左边缘）

uint8 road_width[60];//路宽

uint8 centerline[60];//中线

/*  mt9v03x_image[y][x]是图像数组
 * 0代表黑色，255代表白色，Y轴上的纵坐标，X轴上的横坐标，
 * 两个简单的for循环，画个图就懂了，接下来的if是个边界的判断，在下一个if是对边界的限制。
 * row:行数 --> MT9V03X_H
 * col:列数 --> MT9V03X_W
 * */
void sao_xian(const uint8 *image_in,uint8 row,uint8 col)
{
    uint8 y=0;     //y坐标
    uint8 x=0;     //x坐标
    static uint8 old; //上一次的中线位置（x坐标）
    for (y = row-5; y >= 5; y--) //纵向
    {
        for (x = old; x < col - 2; x++) //向右横向
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
            rightline[y] = MT9V03X_HALVED_W-1;//右侧边缘位默认为187，即数组最大位
        }
/*与上边的同理*/
        for (x = old; x >= 2; x--) //向左横向
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

        road_width[y] = rightline[y] - leftline[y];//计算赛道宽度，存放在一个一维数组中
        centerline[y] = (rightline[y] + leftline[y]) / 2;//计算中线的位置，存放在一维数组中，centerline[line] ：在第Y=line上中线的X坐标。
        old = centerline[y];//将上一次的中线位置记入进变量old，下次以其为点进行寻找。
/*
        //在屏幕中画出中线，左右边线
        tft180_draw_point(leftline[y]/2,y/2,RGB565_BLUE);
        tft180_draw_point(rightline[y]/2,y/2,RGB565_BLUE);
        tft180_draw_point(centerline[y]/2,y/2,RGB565_RED);
*/
    }
}

/*  灰度图像二值化
 *  image_in:用于二值化处理的图像
 *  row:行数 --> MT9V03X_H
 *  col:列数 --> MT9V03X_W
*/
void ImageBinary(const uint8 *image_in,uint8 *image_out,uint8 row,uint8 col)
{
  uint16 grayCount[256]={0};
  uint32 graySum=0;
  uint16 pixelSum=0;
  float graypro[256];

  uint16 i,j;        //XUAN：这里改成uint8试试？
  uint16 step=2;//间隔

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

/* 图像压缩 将图像压缩3/4 */
void halve_image(const uint8 *p_in,uint8 *p_out,uint8 row,uint8 col)
{
    uint8 i, j;
    for (i = 0; i<row/2; i++) {
        for (j = 0;j<col/2; j++) {
            *(p_out+i*col/2+j)=*(p_in+i*2*col+j*2);  // 写入压缩的图像到新的数组
        }
    }
}

/*      在屏幕上画中线，左右边线     */
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
 * @brief TFT180_Draw_cross 屏幕绘制×
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
 * @brief TFT180_Draw_Line 屏幕绘制直线
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
    delta_x=x2-x1; //计算坐标增量
    delta_y=y2-y1;
    uRow=x1;
    uCol=y1;
    if(delta_x>0) incx=1; //设置单步方向
    else if(delta_x==0) incx=0;//垂直线
    else {
        incx=-1;
        delta_x=-delta_x;
    }
    if(delta_y>0) incy=1;
    else if(delta_y==0) incy=0;//水平线
    else{
        incy=-1;
        delta_y=-delta_y;
    }
    if(delta_x>delta_y) distance=delta_x; //选取基本增量坐标轴
    else distance = delta_y;
    for(t=0;t<=distance+1;t++) { //画线输出
        tft180_draw_point(uRow,uCol, color);//画点
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

