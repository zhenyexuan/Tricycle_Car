///*
// * round.c
// *
// *  Created on: 2023年7月3日
// *      Author: ZYX
// */
//#include "round.h"
//
//#define  up     0
//#define  down   1
//#define  left   0
//#define  right  1
//
//uint8 count;        //圆弧顶点位置？
//uint8 round_size=6; //圆环的纵坐标连续值
//uint8 line_size=50; //圆环的纵坐标连续值
//
////边线数组
//uint8 ImageSide[MT9V03X_H][2];//左右边线
//uint8 UpdowmSide[2][MT9V03X_W];//上下边线
//
//uint8 RoadIsRound(uint8 Upimage[2][MT9V03X_H], uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 image[MT9V03X_H][2], uint8 *flag)
//{
//    uint8 i = 0;
//    static uint8 errL=0, errR=0;
//    static uint8 leftState = 0, rightState = 0;
//    count = 0;
//    uint8_t num = 0, py;
//
//    // 从车头往前 左边线是否单调
//    for(i = START_H-2; i > END_H; i--)
//    {
//        if(image[i][0] == 1)
//            continue;
//        if(image[i][0] >= image[i+1][0])    // i是Y坐标值  0 是图像左线X坐标
//        {
//            if(image[i][0]<MT9V03X_W/2 - 5)
//                num++;
//            else
//                num = 0  ;
//
//            if(num == line_size)
//            {
//                num = 0;
//                leftState = 1;   // 左单调标志
//                break;
//            }
//        }
//        else
//        {
//            num = 0;
//        }
//        if(i <= END_H+1)  //   清0
//            num = 0;
//    }
//
//    errL = RoundaboutGetArc(image, 1, round_size, &py); //左边是否有弧形
//    errR = RoundaboutGetArc(image, 2, round_size, &py);
//
//    // 右边线是否单调
//    for(i = START_H-2; i > END_H; i--)
//    {
//        if(image[i][1] == MT9V03X_W-1)
//            continue;
//        if(image[i][1] <= image[i+1][1])
//        {
//            if(image[i][1]>MT9V03X_W/2 + 5)
//                num++;
//            else
//                num = 0  ;
//
//
//            if(num == line_size)
//            {
//                num = 0;
//                rightState = 1; // 右单调标志
//                break;
//            }
//        }
//        else
//        {
//              num = 0;
//        }
//        if(i <= END_H+1)
//            num = 0;
//    }
//
//    // 左边单调， 检测右侧是否是环岛
//    if(leftState == 1 && rightState == 0 && errL == 0)
//    {
//        count = 0;
//        if(RoundaboutGetArc(image, 2, round_size, &count))
//        {
//            *flag = 1;
//            return 1;
//        }
//        else
//        {
//            return 0;
//        }
//    }
//
//    /* 右边单调， 检测左侧是否是环岛 */
//    if(rightState == 1 && leftState == 0&& errR == 0)
//    {
//        count = 0;
//        if(RoundaboutGetArc(image, 1, round_size, &count))
//        {
//            *flag = 2;
//            return 2;
//        }
//    }
//    return 0;
//}
//
///*!
//  * @brief    判断左右边线是否存在弧形
//  * 输出的 index 圆弧的顶点位置
//  * @param    imageInput ： 二值图像信息
//  * @param    imageOut   ： 边线数组
//  * @param    status     ： 1：左边线  2：右边线
//  * @param    num        ： 圆弧的大小 用点数表示  （连续N个增  连续N个减）
//  * @return   1 有弧线    0  没弧线
//
//  */
//uint8 RoundaboutGetArc(uint8 imageSide[MT9V03X_H][2], uint8 status, uint8_t num,uint8 *index)
//{
//    int i = 0;
//    uint8 inc = 0, dec = 0, n = 0;
//    switch(status)
//    {
//      case 1:
//        for(i = START_H-2; i > END_H; i--)
//        {
//            //没有丢线
//            if(imageSide[i][0] != 1 && imageSide[i+1][0] != 1)
//            {
//                if(imageSide[i][0] == imageSide[i+1][0])
//                {
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
//
//        break;
//
//      case 2:
//        for(i = START_H-2; i > END_H; i--)
//        {
//            if(imageSide[i][1] != MT9V03X_W-1 && imageSide[i+1][1] != MT9V03X_W-1)
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
//
//        break;
//    }
//
//    return 0;
//}
//#if 0
///*-----------------------------------------------------------------!
//  * @brief    获取边线
//  *
//  * @param    imageInput ： 二值图像信息
//  * @param    imageOut   ： 边线数组
//  *
//  * @return   是否丢线
//  *
//  * @note     思路：从距离车头较近的行开始从中间向两边搜线
// ---------------------------------------------------------------------- */
//uint8 ImageGetSide(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageOut[MT9V03X_H][2])
//{
//    uint8 i = 0, j = 0,k=0;
//
//        for(i = MT9V03X_H-1; i > 0; i--)
//        {
//            imageOut[i][left] = 1;
//            imageOut[i][right] = MT9V03X_W-1;
//        }
//        // 用距离小车比较近的行 判断是否丢线
//        for(i = MT9V03X_W/2; i > 1; i--)
//        {
//            if(!imageInput[MT9V03X_H-1][i])
//            {
//                imageOut[MT9V03X_H-1][left] = i;
//                break;
//            }
//        }
//        for(i = MT9V03X_W/2+1; i < MT9V03X_W-1; i++)
//        {
//            if(!imageInput[MT9V03X_H-1][i])
//            {
//                imageOut[MT9V03X_H-1][right] = i;
//                break;
//            }
//        }
////-------------------------------------------------------------
//
//    // 遍历每行
//    for(i = MT9V03X_H-2; i > 0; i--)
//    {
//        // 向左搜线
//        for(j = imageOut[i+1][left] + 10; j > 0; j--)
//        {
//            if(!imageInput[i][j])
//            {
//                imageOut[i][left] = j;
//                break;
//            }
//        }
//
//        if(imageOut[i][left]  >  MT9V03X_W/2)
//         {
//              imageOut[i][left]=MT9V03X_W/2;
//
//                for(k=i;k>0;k--)
//                {
//                  imageOut[k][left]=MT9V03X_W/2;
//                }
//
//                break;
//         }
//
//    }
//
//   //遍历每一行
//   for(i = MT9V03X_H-2; i > 0; i--)
//   {
//        //向右搜线
//        for(j = imageOut[i+1][right] - 10; j < MT9V03X_W-1; j++)
//        {
//            if(!imageInput[i][j])
//            {
//                imageOut[i][right] = j;
//                break;
//            }
//        }
//
//        if(imageOut[i][right]  <  MT9V03X_W/2)
//        {
//              imageOut[i][right]=MT9V03X_W/2;
//
//              for(k=i;k>0;k--)
//              {
//                  imageOut[k][right]=MT9V03X_W/2;
//              }
//
//              break;
//        }
//   }
//   return 0;
//}
//
//uint8 UpdownSideGet(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageOut[2][MT9V03X_W])
//{
//    uint8 i = 0, j = 0;
//    uint8 last = MT9V03X_H/2;
//
//    imageOut[0][MT9V03X_W-1] = 0;
//    imageOut[1][MT9V03X_W-1] = MT9V03X_H-1;
//     //从图像中间行    从中到下     从中到上      扫描
//
//    //处理中间单独那一列的上下边线
//    for(i = last; i >= 0; i--)
//    {
//        if(!imageInput[i][MT9V03X_W/2])
//        {
//            imageOut[up][MT9V03X_W/2] = i;
//            break;
//        }
//    }
//
//    for(i = last; i < MT9V03X_H; i++)
//    {
//        if(!imageInput[i][MT9V03X_W/2])
//        {
//            imageOut[down][MT9V03X_W/2] = i;
//            break;
//        }
//    }
//    //其他列的上下边线
//    //从中到左
//    for(i = MT9V03X_W/2-1; i > 0; i--)//遍历每一列
//    {
//        imageOut[up][i] = 0;
//        imageOut[down][i] = MT9V03X_H-1;
//
//        for(j = imageOut[0][i+1] + 5; j > 0; j--)//一列中的扫描每行  从上列的行数+10开始向上扫描
//        {
//            if(!imageInput[j][i])
//            {
//                imageOut[up][i] = j;
//                break;
//            }
//        }
//        for(j = imageOut[1][i+1] - 5; j < MT9V03X_H; j++)
//        {
//            if(!imageInput[j][i])
//            {
//                imageOut[down][i] = j;
//                break;
//            }
//        }
//    }
//
//    //从中到右
//    for(i = MT9V03X_W/2+1; i < MT9V03X_W-1; i++)
//        {
//            imageOut[up][i] = 0;
//            imageOut[down][i] = MT9V03X_H-1;
//
//            for(j = imageOut[0][i-1] + 5; j > 0; j--)
//            {
//                if(!imageInput[j][i])
//                {
//                    imageOut[up][i] = j;
//                    break;
//                }
//            }
//            for(j = imageOut[1][i-1] - 5; j < MT9V03X_H; j++)
//            {
//                if(!imageInput[j][i])
//                {
//                    imageOut[down][i] = j;
//                    break;
//                }
//            }
//        }
//    return 0;
//}
//#endif
