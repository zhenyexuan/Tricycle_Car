/*
 * image_process.c
 *
 *  Created on: 2023年7月1日
 *      Author: ZYX
 */
#include "headfile.h"
///***********************************  变量声明  ***********************************/
//sint16 y=65;
///*  元素标志位  */
//uint8 Process_Flag = 0;
///*  环岛标志位  */
//uint8 Round_Flag  = 0;
///*  断路标志位  */
//uint8_t OpenRoad_Flag = 0;        //断路标志位 0：不是断路 1：断路
///*  T型岔口标志位  */
//uint8 T_Flag = 0;
//uint8 Servo_P = 12;
//uint8 motor_flag=1;
//uint8 Depart_Flag=0;
////边线数组
//uint8 ImageSide[MT9V03X_H][2];      //左右边线
//uint8 UpdowmSide[2][MT9V03X_W];     //上下边线
//uint8 Roadwide[MT9V03X_H];          //赛道宽度
//int16 Offset_Error = 0;         //偏差
//
////环岛
//uint8 round_size=8;     //环岛检测幅度
//
//uint8 rightline[MT9V03X_H];//右边线，索引值是y坐标，值是x坐标
//uint8 leftline[MT9V03X_H]; //左边线，索引值是y坐标，值是x坐标
//uint8 upline[MT9V03X_W];   //上边线，索引值是x坐标，值是y坐标
//uint8 downline[MT9V03X_W]; //下边线，索引值是x坐标，值是y坐标
//
//uint8 right_flag[MT9V03X_H];//找到右边线标志位，找到为1，没找到为0，没找到的话rightline[]值是187（图像右边缘）
//uint8 left_flag[MT9V03X_H]; //找到左边线标志位，找到为1，没找到为0，没找到的话leftline[]值是0(图像左边缘）
//uint8 up_flag[MT9V03X_W];   //找到上边线标志位，找到为1，没找到为0，没找到的话upline[]值是119（图像下边缘）
//uint8 down_flag[MT9V03X_W]; //找到下边线标志位，找到为1，没找到为0，没找到的话downline[]值是0(图像上边缘）
//
//uint8 road_width[MT9V03X_H];//路宽
//
//uint8 centerline[MT9V03X_H];//中线
//
///***********************************  函数  ***********************************/
///*  mt9v03x_image[y][x]是图像数组
// * 0代表黑色，255代表白色，Y轴上的纵坐标，X轴上的横坐标，
// * 两个简单的for循环，画个图就懂了，接下来的if是个边界的判断，在下一个if是对边界的限制。
// * row:行数 --> MT9V03X_H
// * col:列数 --> MT9V03X_W
// * */
//void ImageGetSide(const uint8 *image_in,uint16 row,uint16 col)
//{
//    uint8 y=0;     //y坐标
//    uint8 x=0;     //x坐标
//    static uint8 old = MT9V03X_W/2; //上一次的中线位置（x坐标）
//    for (y = row-10; y >= 10; y--) //纵向
//    {
//        for (x = old; x < col - 2; x++) //向右横向
//        {
//            if ( *(image_in + y*col + x) == 255 &&
//                    *(image_in + y*col + x+1) == 0 &&
//                    *(image_in + y*col + x+2) == 0)
//            {
//                ImageSide[y][1] = x;    //右边线
//                right_flag[y] =1;
//                break;
//            }
//        }
//        if (x == col - 2)       //丢线
//        {
//            right_flag[y] =0;
//            ImageSide[y][1] = MT9V03X_W-1;//右侧边缘位默认为187，即数组最大位
//        }
///*与上边的同理*/
//        for (x = old; x > 2; x--) //向左横向
//        {
//            if ( *(image_in + y*col + x) == 255 &&
//                    *(image_in + y*col + x-1) == 0 &&
//                    *(image_in + y*col + x-2) == 0)
//            {
//                ImageSide[y][0] = x;
//                left_flag[y] = 1;
//                break;
//            }
//        }
//        if (x == 2)
//        {
//            ImageSide[y][0] = 0;
//            leftline[y] = x;
//        }
//
//        road_width[y] = ImageSide[y][1] - ImageSide[y][0];//计算赛道宽度，存放在一个一维数组中
//        centerline[y] = (ImageSide[y][1] + ImageSide[y][0]) / 2;//计算中线的位置，存放在一维数组中，centerline[line] ：在第Y=line上中线的X坐标。
//        old = centerline[y];//将上一次的中线位置记入进变量old，下次以其为点进行寻找。
//    }
//}
///*找上下边线*/
//uint8 UpdownSideGet(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageOut[2][MT9V03X_W])
//{
//    uint8 i = 0, j = 0;
//    uint8 last = MT9V03X_H/2;
//
//    imageOut[0][MT9V03X_W-1] = 1;
//    imageOut[1][MT9V03X_W-1] = MT9V03X_H-1;
//     //从图像中间行    从中到下     从中到上      扫描
//
//    //处理中间单独那一列的上下边线
//    for(i = last; i > 0; i--)
//    {
//        if( (!imageInput[i][MT9V03X_W/2]) || (i==1) )
//        {
//            imageOut[0][MT9V03X_W/2] = i;
//            break;
//        }
//    }
//
//    for(i = last; i < MT9V03X_H; i++)
//    {
//        if((!imageInput[i][MT9V03X_W/2]) || (i==MT9V03X_H-1) )
//        {
//            imageOut[1][MT9V03X_W/2] = i;
//            break;
//        }
//    }
//    //其他列的上下边线
//    //从中到左
//    for(i = MT9V03X_W/2-1; i > 0; i--)//遍历每一列
//    {
//        imageOut[0][i] = 0;
//        imageOut[1][i] = MT9V03X_H-1;
//
//        for(j = imageOut[0][i+1] + 5; j > 0; j--)//一列中的扫描每行  从上列的行数+10开始向上扫描
//        {
//            if((!imageInput[j][i]) || (j==1))
//            {
//                imageOut[0][i] = j;
//                break;
//            }
//        }
//        for(j = imageOut[1][i+1] - 5; j < MT9V03X_H; j++)
//        {
//            if((!imageInput[j][i]) || (j==MT9V03X_H-1))
//            {
//                imageOut[1][i] = j;
//                break;
//            }
//        }
//    }
//
//    //从中到右
//    for(i = MT9V03X_W/2+1; i < MT9V03X_W-1; i++)
//        {
//            imageOut[0][i] = 0;
//            imageOut[1][i] = MT9V03X_H-1;
//
//            for(j = imageOut[0][i-1] + 5; j > 0; j--)
//            {
//                if((!imageInput[j][i]) || (j==1))
//                {
//                    imageOut[0][i] = j;
//                    break;
//                }
//            }
//            for(j = imageOut[1][i-1] - 5; j < MT9V03X_H; j++)
//            {
//                if((!imageInput[j][i]) ||(j==MT9V03X_H-1))
//                {
//                    imageOut[1][i] = j;
//                    break;
//                }
//            }
//        }
//    return 0;
//}
//
//
///*  mt9v03x_image[y][x]是图像数组
// * 0代表黑色，255代表白色，Y轴上的纵坐标，X轴上的横坐标，
// * 两个简单的for循环，画个图就懂了，接下来的if是个边界的判断，在下一个if是对边界的限制。
// * row:行数 --> MT9V03X_H
// * col:列数 --> MT9V03X_W
// * */
//void UpdownSideGet2(const uint8 *image_in,uint16 row,uint16 col)
//{
//    uint8 y=0;     //y坐标
//    uint8 x=0;     //x坐标
//    static uint8 old =MT9V03X_H/2; //上一次的中线位置（x坐标）
//    for (x = col-10; x >= 10; x--) //横向从右往左
//    {
//        for (y = old ; y > 1; y--) //向上
//        {
//            if(*(image_in+ (y+2)*col + x) == 255 && *(image_in+ (y+1)*col + x) == 255 && *(image_in+ y*col + x)==0)
//            {
//                upline[x] = y;
//                up_flag[x] =1;
//                break;
//            }
//        }
//        if (y == 2 || x == 1 )
//        {
//            up_flag[x] =0;
//            upline[x] = 1;//上侧边缘位默认为1，即数组最大位
//        }
//        /*与上边的同理*/
//        for (y = old; y < 119; y++) //向下
//        {
//            if(*(image_in+ (y-2)*col + x) == 255 && *(image_in+ (y-1)*col + x) == 255 && *(image_in+ y*col + x)==0)
//            {
//                downline[x] = y;
//                down_flag[x] = 1;
//                break;
//            }
//        }
//        if (x == 120-1 || x == 120-2)
//        {
//            down_flag[x] = 0;
//            downline[x] = 119;
//        }
//    old = (downline[x] + upline[x])/2;
//    }
//}
//
///*!
//  * @brief    判断是否丢线
//  *
//  * @param    imageInput ： 二值图像信息
//  * @param    imageOut   ： 边线数组
//  * @param    lineIndex  ： 行
//  *
//  * @return   0：没有丢线   1:左边丢线  2：右边丢线  3： 左右都丢线   4：错误
//  *
//  * @date     2020/6/24 星期三
//  */
//uint8 RoadIsNoSide(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageOut[MT9V03X_H][2], uint8 lineIndex)
//{
//    uint8 state = 0;
//    uint8 i = 0;
//    static uint8 last = 78;
//
//    imageOut[lineIndex][0] = 0;
//    imageOut[lineIndex][1] = 187;
//    /* 用距离小车比较近的行 判断是否丢线 */
//    for(i = last; i > 1; i--)
//    {
//        if(!imageInput[lineIndex][i])                                  //*4.18
//        {
//            imageOut[lineIndex][0] = i;
//            break;
//        }
//    }
//    if(i == 1)
//    {
//        /* 左边界丢线 */
//        state = 1;
//    }
//
//    for(i = last; i < 187; i++)
//    {
//        if(!imageInput[lineIndex][i])                                 //*4.18
//        {
//            imageOut[lineIndex][1] = i;
//            break;
//        }
//    }
//
//    if(i == 187)
//    {
//        /* 左右边界丢线 */
//        if(state == 1)
//        {
//            state = 3;
//        }
//
//        /* 右边界丢线 */
//        else
//        {
//            state = 2;
//        }
//
//    }
//    if(imageOut[lineIndex][1] <= imageOut[lineIndex][0])
//    {
//        state = 4;
//    }
//    return state;
//
//}
//
///*!
//  * @brief    获取环岛边线
//  *
//  * @param    imageInput ： 二值图像信息
//  * @param    imageOut   ： 边线数组
//  * @param    status     ： 1：左环岛(边线)  2：右环岛(边线)
//  *
//  * @return   void
//  *
//  * @note     思路：环岛一边边线严格单调，根据一边边线，获取另一边线
//
//  * @date     2020/6/23 星期二
//  */
//void RoundaboutGetSide(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageSide[MT9V03X_H][2], uint8 status)
//{
//    uint8 i = 0, j = 0;
//
//    switch(status)
//    {
//        /* 左环岛 */
//      case 1:
//        {
//            /* 重新确定左边界 */
//            for(i = ROAD_START_ROW; i > ROAD_END_ROW; i--)
//            {
//                for(j = MT9V03X_W/2; j > 0; j--)
//                {
//                    if(!imageInput[i][j])
//                    {
//                        imageSide[i][0] = j;
//                        break;
//                    }
//                }
//            }
//            break;
//        }
//        /* 右环岛 */
//      case 2:
//        {
//            /* 重新确定右边界 */
//            for(i = ROAD_START_ROW; i > ROAD_END_ROW; i--)
//            {
//                for(j = MT9V03X_W/2; j < MT9V03X_W; j++)
//                {
//                    if(!imageInput[i][j])
//                    {
//                        imageSide[i][1] = j;
//                        break;
//                    }
//                }
//            }
//            break;
//        }
//    }
//}
//
///*!
//  * @brief    判断左右边线是否存在弧形
//  *
//  * @param    imageInput ： 二值图像信息
//  * @param    imageOut   ： 边线数组
//  * @param    num       ： 检测幅度
//  * @param    index     ： 最右点
//  * 输出的 index 圆弧的顶点位置
//  * @param    status     ： 1：左边线  2：右边线
//  *
//  * @return
//  *
//  * @date     2020/6/23 星期二
//  */
//uint8 RoundaboutGetArc(uint8 imageSide[MT9V03X_H][2], uint8 status, uint8 num,uint8 *index)
//{
//    int i = 0;
//    uint8 inc = 0, dec = 0, n = 0;
//    switch(status)
//    {
//      case 1:
//        for(i = ROAD_START_ROW-1; i > 10; i--)
//        {
//            if(imageSide[i][0] != 2 && imageSide[i+1][0] != 2)  //没有丢线
//            {
//                if(imageSide[i][0] == imageSide[i+1][0]){
//                    n++;
//                    continue;
//                }
//                if(imageSide[i][0] > imageSide[i+1][0])
//                {
//                    inc++;
//                    inc+=n;
//                    n=0;
//                }
//                else
//                {
//                    dec++;
//                    dec+=n;
//                    n=0;
//                }
//                /* 有弧线 */
//                if(inc > num && dec > num)
//                {
//                    *index = i + num;
//                    return 1;
//                }
//            }
//            else
//            {
//                inc = 0;
//                dec = 0;n=0;
//            }
//        }
//
//        break;
//
//      case 2:
//        for(i = ROAD_START_ROW-1; i > ROAD_END_ROW; i--)
//        {
//            if(imageSide[i][1] != 187 && imageSide[i+1][1] != 187)
//            {
//                if(imageSide[i][1] == imageSide[i+1][1])
//                {
//                    n++;
//                    continue;
//                }
//                if(imageSide[i][1] > imageSide[i+1][1])
//                {
//                    inc++;
//                    inc+=n;
//                    n = 0;
//                }
//                else
//                {
//                    dec++;
//                    dec+=n;
//                    n=0;
//                }
//
//                /* 有弧线 */
//                if(inc > num && dec > num)
//                {
//                    *index = i + num;
//                    return 1;
//                }
//            }
//            else
//            {
//                inc = 0;
//                dec = 0;n=0;
//            }
//        }
//        break;
//    }
//    return 0;
//}
//
///*!
//   * @brief    补线处理
//   *
//   * @param    imageSide  : 边线
//   * @param    status     : 1：左边线补线   2：右边线补线
//   * @param    startX     : 起始点 列数
//   * @param    startY     : 起始点 行数
//   * @param    endX       : 结束点 列数
//   * @param    endY       : 结束点 行数
//   *
//   * @return
//   *
//   * @note     endY 一定要大于 startY
//   *
//   */
// void ImageAddingLine(uint8 imageSide[MT9V03X_H][2], uint8 status, uint8 startX, uint8 startY, uint8 endX, uint8 endY)
// {
//     int i = 0;
//
//     // 直线 x = ky + b
//     float k = 0.0f, b = 0.0f;
//     switch(status)
//     {
//       case 1://左补线
//         {
//             k = (float)((float)endX - (float)startX) / (float)((float)endY - (float)startY);
//             b = (float)startX - (float)startY * k;
//
//             for(i = startY; i < endY; i++)
//             {
//                 imageSide[i][0] = (uint8_t)(k * i + b);
//             }
//             break;
//         }
//
//       case 2://右补线
//         {
//             k = (float)((float)endX - (float)startX) / (float)((float)endY - (float)startY);
//             b = (float)startX - (float)startY * k;
//
//             for(i = startY; i < endY; i++)
//             {
//                 imageSide[i][1] = (uint8_t)(k * i + b);
//             }
//             break;
//         }
//
//     }
// }
//
// /*!
//   * @brief    判断上边线是否单调
//   * @param    X1 :起始X点
//   * @param    X2 :终止X点              X1 < X2
//   * @param    imageIn ： 边线数组
//   *
//   * @return   0：不单调or错误， 1：单调递增， 2：单调递减
//   *
//   * @date     2021/11/30 星期二
//   */
// uint8 RoadUpSide_Mono(uint8 X1, uint8 X2, uint8 imageIn[2][MT9V03X_W])
// {
//     uint8 i = 0, num = 0;
//     for(i = X1; i < X2-1; i++)
//     {
//         if(imageIn[0][i] >= imageIn[0][i+1])
//             num++;
//         else
//             num = 0;
//         if (num >= (X2-X1)*4/5)
//             return 1;
//     }
//
//     for(i = X1; i < X2-1; i++)
//     {
//         if(imageIn[0][i] <= imageIn[0][i+1])
//             num++;
//         else
//             num = 0;
//         if (num >= (X2-X1)*4/5)
//             return 2;
//     }
//     return 0;
// }
//
//
///*!
//  * @brief    检测环岛
//  *
//  * @param    Upimage：上下边线
//  * @param    imageInput：边缘数组
//  * @param    image：左右边线
//  * @param    *flag：标志位
//  *
//  * @return   左环岛返回2；右环岛返回1
//  *
//  * @date     2020/6/24 星期三
//  */
//
//    uint8 errL=0, errR=0;
//    uint8 leftState = 0, rightState = 0;
//uint8 RoadIsRoundabout(uint8 image[MT9V03X_H][2], uint8 *flag)
//{
//        uint8 i = 0;
////        uint8 errL=0, errR=0;
////        uint8 leftState = 0, rightState = 0;
//        errL=0, errR=0;
//        leftState = 0, rightState = 0;
//        uint8 count = 0;
//        uint8 num = 0 ,py;
//        // 从车头往前 左边线是否单调
//        for(i = ROAD_START_ROW-2; i > ROAD_END_ROW; i--)
//        {
//            if(image[i][0] == 0)        //丢线
//                continue;
//            if(image[i][0] >= image[i+1][0])    // i是Y坐标值  0 是图像左线X坐标
//            {
//                if(image[i][0]<MT9V03X_W/2 - 5)
//                    num++;
//                else
//                    num = 0;
//
//                if(num == 40)
//                {
//                    num = 0;
//                    leftState = 1;   // 左单调标志
//                    break;
//                }
//            }
//            else
//                num = 0;
//            if(i <= ROAD_END_ROW+1)  //   清0
//                num = 0;
//        }
//        // 右边线是否单调
//        for(i = ROAD_START_ROW-2; i > ROAD_END_ROW; i--)
//        {
//            if(image[i][1] == MT9V03X_W - 1)  //丢线
//                continue;
//            if(image[i][1]<= image[i+1][1])
//            {
//                if(image[i][1]>MT9V03X_W/2 + 5)
//                    num++;
//                else
//                    num = 0;
//
//                if(num == 40)
//                {
//                    num = 0;
//                    rightState = 1;
//                    break;
//                }
//            }
//            else
//                num = 0;
//            if(i <= ROAD_END_ROW+1)
//                num = 0;
//        }
//
//        errL = RoundaboutGetArc(image, 1, round_size, &py);
//        errR = RoundaboutGetArc(image, 2, round_size, &py);
//
//        /* 左边单调，检测右侧是否是环岛 */
//        if(leftState == 1 && rightState == 0 && errL == 0)
//        {
//            count = 0;
//            if(RoundaboutGetArc(image, 2, round_size, &count))
//            {
//                *flag = 1;
//                return 1;
//            }
//            else
//            {
//                return 0;
//            }
//        }
//        /* 右边单调， 检测左侧是否是环岛 */
//         if(rightState == 1 && leftState == 0&& errR == 0)
//         {
//             count = 0;
//             if(RoundaboutGetArc(image, 1, round_size, &count))
//             {
//                 *flag = 2;
//                 return 2;
//             }
//             else
//             {
//                 return 0;
//             }
//         }
//        return 0;
//}
//
///*!
//  * @brief    环岛处理
//  *
//  * @param    imageInput：边缘数组
//  * @param    UpdowmSide：上下边线
//  * @param    imageSide：左右边线
//  * @param    *state：状态
//  *
//  * @return
//  *
//  * @date
//  */
//void RoundaboutProcess(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageSide[MT9V03X_H][2], uint8 UpdowmSide[2][MT9V03X_W], uint8* state)
//{
//
//    uint8 i = 0, err5 = 0 ,err6 = 0;
//    uint8 pointX = 0, pointY = 0, inc = 0, dec = 0;
//    uint8 flag= 0, Down_flag = 0;
//    static uint8 finderr = 0;
//    static uint8 err1 = 0;
//    static uint8 err2 = 0;
//
//    switch(*state)
//    {
//        //奇数为入右圆环
//
////        case 1:
////            // 检查弧线
////            err1 = RoundaboutGetArc(imageSide, 2, 3, &pointY);
////            // 有弧线 进行补线 连接弧线最右点 和 图像左下角
////            if(err1)
////            {
////                pointX = imageSide[pointY][1];
////                ImageAddingLine(imageSide, 2, pointX, pointY, MT9V03X_W-1, ROAD_START_ROW);
////                finderr = 1;
////            }
////            else
////            {
////                if(finderr){
////                    *state = 3;//准备进入环岛
////                    finderr = 0;
////                }
////            }
////            break;
//
//        //偶数为入左圆环
//        case 2:
//            errL=0;
//            // 检查弧线
//            err2 = RoundaboutGetArc(imageSide, 1, 3, &pointY);
//            if(err2)
//            {
//                pointX = imageSide[pointY][0];
//                ImageAddingLine(imageSide, 1, pointX, pointY, 1, ROAD_START_ROW);
//                finderr = 1;
//            }
//            else
//            {
//                if(finderr){
//                    *state = 4;//准备进入环岛
//                    finderr = 0;
//                }
//            }
//            break;
//
//        /* 发现右环岛 环岛出口处补线 */
////        case 3:
////            for(i=1;i<MT9V03X_H-1;i++)
////               {
////                    ImageSide[i][0]= ImageSide[i][0]+50;
////               }
////            if(RoadUpSide_Mono(30, MT9V03X_W-1,UpdowmSide) == 1)//上线单调增进入下一步
////                  *state = 5;
////              break;
//
//        /* 发现左环岛 环岛出口处补线 */
//        case 4:
//            for(i=1;i<MT9V03X_H-1;i++)
//            {
////                ImageSide[i][1]= ImageSide[i][1]-50;
//            }
//            if(RoadUpSide_Mono(30, MT9V03X_W-30,UpdowmSide) == 1)//上线单调增进入下一步
//                *state = 6;
//              break;
//
////        case 5 :
////            //
////            err5 = RoundaboutGetArc(imageSide, 1, 10, &pointY);
////            //检查下线
////            for(i = MT9V03X_W-1; i > 0; i--)
////            {
////                if(UpdowmSide[1][i] == 119)
////                      inc++;
////                else
////                     dec++;
////                if( dec <= 15)
////                {
////                    Down_flag = 1;
////                    break;
////                }
////             }
////            flag = RoadUpSide_Mono(20, MT9V03X_W ,UpdowmSide);
////            if(flag && err5 && Down_flag)
////            {
////                 *state = 7;
////            }
////            break;
//
//        case 6 :
//            err6 = RoundaboutGetArc(imageSide, 2, 10, &pointY);
//            //检查下线
//            for(i = MT9V03X_W-1; i > 0; i--)
//            {
//                if(UpdowmSide[1][i] == 119)
//                     inc++;
//                else
//                     dec++;
//                if( dec <= 15)
//                {
//                    Down_flag = 1;
//                    break;
//                }
//             }
//            flag = RoadUpSide_Mono(20, MT9V03X_W ,UpdowmSide);
//            if(flag && err5 && Down_flag)
//            {
//                 *state = 8;
//            }
//            break;
//
//
////        case 7:
////            ImageAddingLine(imageSide, 1, 80, 10, 0, ROAD_START_ROW);
////            flag = RoadUpSide_Mono(50, MT9V03X_W,UpdowmSide);
////            if(flag==0)
////            {
////                *state = 0;
////                finderr = 0;
////                err1 = 0;
////            }
////            break;
//
//        case 8:
//            ImageAddingLine(imageSide, 1, 100, 10, MT9V03X_W, ROAD_START_ROW);
//            flag = RoadUpSide_Mono(50, MT9V03X_W,UpdowmSide);
//            if(flag==0)
//            {
//                *state = 0;
//                finderr = 0;
//                err1 = 0;
//            }
//            break;
//    }
//}
//
///*!
//  * @brief    判断入断路
//  *
//  * @param  imageInput：图像
//  * @param  *Flag：标志位
//  *
//  * @return
//  *
//  * @date
//  */
//void InputOpening(uint8_t  imageInput[MT9V03X_H][MT9V03X_W],uint8_t *Flag)
//{
//      uint8 count0=0,count1=0,flag=0;
//          for(uint8 j=0;j<=MT9V03X_W-1;j++)
//          {
//              if(imageInput[60][j]==0)
//              {
//                  count0++;
//                  if(count0>=150)
//                  {
//                      flag=1;
//                  }
//              }
//              break;
//          }
//        for(uint8 i=0;i<=MT9V03X_H-1;i++)
//        {
//            if(imageInput[i][94]!=0)
//            {
//                count1++;
//                if(count1<=60&&flag==1)
//                {
//                    *Flag=1;
//                }
//            }
//            break;
//        }
//}
//
///*!
//  * @brief    判断出断路
//  *
//  * @param  imageInput：图像
//  * @param  *Flag：标志位
//  *
//  * @return
//  *
//  * @note       不是出断路就转为摄像头的，而是等车身稳定，而且赛道比较直的时候切回摄像头
//  *
//  * @date
//  */
//void OutOpening(uint8_t  imageInput[MT9V03X_H][MT9V03X_W],uint8_t *Flag)
//{
//    uint8 count0=0,count1=0,flag=0;
//    for(uint8 j=0;j<=MT9V03X_W-1;j++)
//    {
//        if(imageInput[60][j]!=0)
//        {
//            count0++;
//            if(count0>=90)
//            {
//                flag=1;
//            }
//        }
//        break;
//    }
//  for(uint8 i=0;i<=MT9V03X_H-1;i++)
//  {
//      if(imageInput[i][94]==0)
//      {
//          count1++;
//          if(count1<=60&&flag==1)
//          {
//              *Flag=2;
//          }
//      }
//      break;
//  }
//}
//
///*!
//  * @brief    断路处理函数
//  *
//  * @param     Upimage[2][LCDW]上下边线数组   imageSideinput[LCDH][2]左右边线数组   RoadwideInput[LCDH]赛道宽度 Flag 标志位
//  *
//  * @return     无
//  *
//  * @note
//  *
//  * @see
//  *
//  * @date     2022/11/30 星期三
//  */
//void OpeningProcess(uint8_t Upimage[2][MT9V03X_W],uint8_t imageSideinput[MT9V03X_H][2],uint8_t  imageInput[MT9V03X_H][MT9V03X_W],uint8_t *Flag)
//{
//   switch(*Flag)
//   {
//       case 1:
//           gpio_set_level(P33_10, GPIO_HIGH);
//           InputOpening(imageInput,&*Flag);
//           break;     //入断路
//       case 2:
//           gpio_set_level(P33_10, GPIO_LOW);
//           OutOpening(imageInput,&*Flag);
//           break;        //出断路
//       default:break;
//   }
//}
//
//void CameraCar (void)
//{
////    InductorNormal();
//    /******************************************************************圆环识别处理*********************************************************/
//        if(Round_Flag == 0&&OpenRoad_Flag==0&&Process_Flag==0 )
//         {
//             // 检测环岛
//             RoadIsRoundabout(ImageSide, &Round_Flag);   //一边单调一边丢线
//         }
//        if(Round_Flag)//识别到圆环，圆环处理
//         {
//           // buzzer(100);//识别到环岛，蜂鸣器响一声
//            Process_Flag=2;
////            y=58;//打角行
//            Target_Speed1 = 65;
//            Target_Speed2 = 65;
//            turn_PID.kp =0.5;
//            turn_PID.kd =0.25;
//            RoundaboutProcess(Bin_Image, ImageSide, UpdowmSide, &Round_Flag);
//         }
//       // gpio_set_level(P33_10, GPIO_LOW);
/////**********************************************************************断路识别处理***********************************************************/
//        if(Round_Flag == 0&&OpenRoad_Flag==0 )
//        {
//            InputOpening(Bin_Image,&OpenRoad_Flag);//入断路识别
//        }
//        if(OpenRoad_Flag)//当断路标志位为1，自动进行电磁循迹
//        {
//            OutOpening(Bin_Image,&OpenRoad_Flag);//出断路识别(进入断路以后开启)
//        }
/////***********************************************************************直道弯道******************************************************************/
//        if(Round_Flag == 0&&OpenRoad_Flag==0 )//直道弯道
//        {
//            Target_Speed1=60;
//            Target_Speed2=60;
//            turn_PID.kp =0.48;//3
//            turn_PID.kd =0.35 ;
//        }
//}
