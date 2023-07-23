/*
 * image_process.c
 *
 *  Created on: 2023��7��1��
 *      Author: ZYX
 */
#include "headfile.h"
///***********************************  ��������  ***********************************/
//sint16 y=65;
///*  Ԫ�ر�־λ  */
//uint8 Process_Flag = 0;
///*  ������־λ  */
//uint8 Round_Flag  = 0;
///*  ��·��־λ  */
//uint8_t OpenRoad_Flag = 0;        //��·��־λ 0�����Ƕ�· 1����·
///*  T�Ͳ�ڱ�־λ  */
//uint8 T_Flag = 0;
//uint8 Servo_P = 12;
//uint8 motor_flag=1;
//uint8 Depart_Flag=0;
////��������
//uint8 ImageSide[MT9V03X_H][2];      //���ұ���
//uint8 UpdowmSide[2][MT9V03X_W];     //���±���
//uint8 Roadwide[MT9V03X_H];          //�������
//int16 Offset_Error = 0;         //ƫ��
//
////����
//uint8 round_size=8;     //����������
//
//uint8 rightline[MT9V03X_H];//�ұ��ߣ�����ֵ��y���ֵ꣬��x����
//uint8 leftline[MT9V03X_H]; //����ߣ�����ֵ��y���ֵ꣬��x����
//uint8 upline[MT9V03X_W];   //�ϱ��ߣ�����ֵ��x���ֵ꣬��y����
//uint8 downline[MT9V03X_W]; //�±��ߣ�����ֵ��x���ֵ꣬��y����
//
//uint8 right_flag[MT9V03X_H];//�ҵ��ұ��߱�־λ���ҵ�Ϊ1��û�ҵ�Ϊ0��û�ҵ��Ļ�rightline[]ֵ��187��ͼ���ұ�Ե��
//uint8 left_flag[MT9V03X_H]; //�ҵ�����߱�־λ���ҵ�Ϊ1��û�ҵ�Ϊ0��û�ҵ��Ļ�leftline[]ֵ��0(ͼ�����Ե��
//uint8 up_flag[MT9V03X_W];   //�ҵ��ϱ��߱�־λ���ҵ�Ϊ1��û�ҵ�Ϊ0��û�ҵ��Ļ�upline[]ֵ��119��ͼ���±�Ե��
//uint8 down_flag[MT9V03X_W]; //�ҵ��±��߱�־λ���ҵ�Ϊ1��û�ҵ�Ϊ0��û�ҵ��Ļ�downline[]ֵ��0(ͼ���ϱ�Ե��
//
//uint8 road_width[MT9V03X_H];//·��
//
//uint8 centerline[MT9V03X_H];//����
//
///***********************************  ����  ***********************************/
///*  mt9v03x_image[y][x]��ͼ������
// * 0�����ɫ��255�����ɫ��Y���ϵ������꣬X���ϵĺ����꣬
// * �����򵥵�forѭ��������ͼ�Ͷ��ˣ���������if�Ǹ��߽���жϣ�����һ��if�ǶԱ߽�����ơ�
// * row:���� --> MT9V03X_H
// * col:���� --> MT9V03X_W
// * */
//void ImageGetSide(const uint8 *image_in,uint16 row,uint16 col)
//{
//    uint8 y=0;     //y����
//    uint8 x=0;     //x����
//    static uint8 old = MT9V03X_W/2; //��һ�ε�����λ�ã�x���꣩
//    for (y = row-10; y >= 10; y--) //����
//    {
//        for (x = old; x < col - 2; x++) //���Һ���
//        {
//            if ( *(image_in + y*col + x) == 255 &&
//                    *(image_in + y*col + x+1) == 0 &&
//                    *(image_in + y*col + x+2) == 0)
//            {
//                ImageSide[y][1] = x;    //�ұ���
//                right_flag[y] =1;
//                break;
//            }
//        }
//        if (x == col - 2)       //����
//        {
//            right_flag[y] =0;
//            ImageSide[y][1] = MT9V03X_W-1;//�Ҳ��ԵλĬ��Ϊ187�����������λ
//        }
///*���ϱߵ�ͬ��*/
//        for (x = old; x > 2; x--) //�������
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
//        road_width[y] = ImageSide[y][1] - ImageSide[y][0];//����������ȣ������һ��һά������
//        centerline[y] = (ImageSide[y][1] + ImageSide[y][0]) / 2;//�������ߵ�λ�ã������һά�����У�centerline[line] ���ڵ�Y=line�����ߵ�X���ꡣ
//        old = centerline[y];//����һ�ε�����λ�ü��������old���´�����Ϊ�����Ѱ�ҡ�
//    }
//}
///*�����±���*/
//uint8 UpdownSideGet(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageOut[2][MT9V03X_W])
//{
//    uint8 i = 0, j = 0;
//    uint8 last = MT9V03X_H/2;
//
//    imageOut[0][MT9V03X_W-1] = 1;
//    imageOut[1][MT9V03X_W-1] = MT9V03X_H-1;
//     //��ͼ���м���    ���е���     ���е���      ɨ��
//
//    //�����м䵥����һ�е����±���
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
//    //�����е����±���
//    //���е���
//    for(i = MT9V03X_W/2-1; i > 0; i--)//����ÿһ��
//    {
//        imageOut[0][i] = 0;
//        imageOut[1][i] = MT9V03X_H-1;
//
//        for(j = imageOut[0][i+1] + 5; j > 0; j--)//һ���е�ɨ��ÿ��  �����е�����+10��ʼ����ɨ��
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
//    //���е���
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
///*  mt9v03x_image[y][x]��ͼ������
// * 0�����ɫ��255�����ɫ��Y���ϵ������꣬X���ϵĺ����꣬
// * �����򵥵�forѭ��������ͼ�Ͷ��ˣ���������if�Ǹ��߽���жϣ�����һ��if�ǶԱ߽�����ơ�
// * row:���� --> MT9V03X_H
// * col:���� --> MT9V03X_W
// * */
//void UpdownSideGet2(const uint8 *image_in,uint16 row,uint16 col)
//{
//    uint8 y=0;     //y����
//    uint8 x=0;     //x����
//    static uint8 old =MT9V03X_H/2; //��һ�ε�����λ�ã�x���꣩
//    for (x = col-10; x >= 10; x--) //�����������
//    {
//        for (y = old ; y > 1; y--) //����
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
//            upline[x] = 1;//�ϲ��ԵλĬ��Ϊ1�����������λ
//        }
//        /*���ϱߵ�ͬ��*/
//        for (y = old; y < 119; y++) //����
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
//  * @brief    �ж��Ƿ���
//  *
//  * @param    imageInput �� ��ֵͼ����Ϣ
//  * @param    imageOut   �� ��������
//  * @param    lineIndex  �� ��
//  *
//  * @return   0��û�ж���   1:��߶���  2���ұ߶���  3�� ���Ҷ�����   4������
//  *
//  * @date     2020/6/24 ������
//  */
//uint8 RoadIsNoSide(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageOut[MT9V03X_H][2], uint8 lineIndex)
//{
//    uint8 state = 0;
//    uint8 i = 0;
//    static uint8 last = 78;
//
//    imageOut[lineIndex][0] = 0;
//    imageOut[lineIndex][1] = 187;
//    /* �þ���С���ȽϽ����� �ж��Ƿ��� */
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
//        /* ��߽綪�� */
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
//        /* ���ұ߽綪�� */
//        if(state == 1)
//        {
//            state = 3;
//        }
//
//        /* �ұ߽綪�� */
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
//  * @brief    ��ȡ��������
//  *
//  * @param    imageInput �� ��ֵͼ����Ϣ
//  * @param    imageOut   �� ��������
//  * @param    status     �� 1���󻷵�(����)  2���һ���(����)
//  *
//  * @return   void
//  *
//  * @note     ˼·������һ�߱����ϸ񵥵�������һ�߱��ߣ���ȡ��һ����
//
//  * @date     2020/6/23 ���ڶ�
//  */
//void RoundaboutGetSide(uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 imageSide[MT9V03X_H][2], uint8 status)
//{
//    uint8 i = 0, j = 0;
//
//    switch(status)
//    {
//        /* �󻷵� */
//      case 1:
//        {
//            /* ����ȷ����߽� */
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
//        /* �һ��� */
//      case 2:
//        {
//            /* ����ȷ���ұ߽� */
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
//  * @brief    �ж����ұ����Ƿ���ڻ���
//  *
//  * @param    imageInput �� ��ֵͼ����Ϣ
//  * @param    imageOut   �� ��������
//  * @param    num       �� ������
//  * @param    index     �� ���ҵ�
//  * ����� index Բ���Ķ���λ��
//  * @param    status     �� 1�������  2���ұ���
//  *
//  * @return
//  *
//  * @date     2020/6/23 ���ڶ�
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
//            if(imageSide[i][0] != 2 && imageSide[i+1][0] != 2)  //û�ж���
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
//                /* �л��� */
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
//                /* �л��� */
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
//   * @brief    ���ߴ���
//   *
//   * @param    imageSide  : ����
//   * @param    status     : 1������߲���   2���ұ��߲���
//   * @param    startX     : ��ʼ�� ����
//   * @param    startY     : ��ʼ�� ����
//   * @param    endX       : ������ ����
//   * @param    endY       : ������ ����
//   *
//   * @return
//   *
//   * @note     endY һ��Ҫ���� startY
//   *
//   */
// void ImageAddingLine(uint8 imageSide[MT9V03X_H][2], uint8 status, uint8 startX, uint8 startY, uint8 endX, uint8 endY)
// {
//     int i = 0;
//
//     // ֱ�� x = ky + b
//     float k = 0.0f, b = 0.0f;
//     switch(status)
//     {
//       case 1://����
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
//       case 2://�Ҳ���
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
//   * @brief    �ж��ϱ����Ƿ񵥵�
//   * @param    X1 :��ʼX��
//   * @param    X2 :��ֹX��              X1 < X2
//   * @param    imageIn �� ��������
//   *
//   * @return   0��������or���� 1������������ 2�������ݼ�
//   *
//   * @date     2021/11/30 ���ڶ�
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
//  * @brief    ��⻷��
//  *
//  * @param    Upimage�����±���
//  * @param    imageInput����Ե����
//  * @param    image�����ұ���
//  * @param    *flag����־λ
//  *
//  * @return   �󻷵�����2���һ�������1
//  *
//  * @date     2020/6/24 ������
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
//        // �ӳ�ͷ��ǰ ������Ƿ񵥵�
//        for(i = ROAD_START_ROW-2; i > ROAD_END_ROW; i--)
//        {
//            if(image[i][0] == 0)        //����
//                continue;
//            if(image[i][0] >= image[i+1][0])    // i��Y����ֵ  0 ��ͼ������X����
//            {
//                if(image[i][0]<MT9V03X_W/2 - 5)
//                    num++;
//                else
//                    num = 0;
//
//                if(num == 40)
//                {
//                    num = 0;
//                    leftState = 1;   // �󵥵���־
//                    break;
//                }
//            }
//            else
//                num = 0;
//            if(i <= ROAD_END_ROW+1)  //   ��0
//                num = 0;
//        }
//        // �ұ����Ƿ񵥵�
//        for(i = ROAD_START_ROW-2; i > ROAD_END_ROW; i--)
//        {
//            if(image[i][1] == MT9V03X_W - 1)  //����
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
//        /* ��ߵ���������Ҳ��Ƿ��ǻ��� */
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
//        /* �ұߵ����� �������Ƿ��ǻ��� */
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
//  * @brief    ��������
//  *
//  * @param    imageInput����Ե����
//  * @param    UpdowmSide�����±���
//  * @param    imageSide�����ұ���
//  * @param    *state��״̬
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
//        //����Ϊ����Բ��
//
////        case 1:
////            // ��黡��
////            err1 = RoundaboutGetArc(imageSide, 2, 3, &pointY);
////            // �л��� ���в��� ���ӻ������ҵ� �� ͼ�����½�
////            if(err1)
////            {
////                pointX = imageSide[pointY][1];
////                ImageAddingLine(imageSide, 2, pointX, pointY, MT9V03X_W-1, ROAD_START_ROW);
////                finderr = 1;
////            }
////            else
////            {
////                if(finderr){
////                    *state = 3;//׼�����뻷��
////                    finderr = 0;
////                }
////            }
////            break;
//
//        //ż��Ϊ����Բ��
//        case 2:
//            errL=0;
//            // ��黡��
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
//                    *state = 4;//׼�����뻷��
//                    finderr = 0;
//                }
//            }
//            break;
//
//        /* �����һ��� �������ڴ����� */
////        case 3:
////            for(i=1;i<MT9V03X_H-1;i++)
////               {
////                    ImageSide[i][0]= ImageSide[i][0]+50;
////               }
////            if(RoadUpSide_Mono(30, MT9V03X_W-1,UpdowmSide) == 1)//���ߵ�����������һ��
////                  *state = 5;
////              break;
//
//        /* �����󻷵� �������ڴ����� */
//        case 4:
//            for(i=1;i<MT9V03X_H-1;i++)
//            {
////                ImageSide[i][1]= ImageSide[i][1]-50;
//            }
//            if(RoadUpSide_Mono(30, MT9V03X_W-30,UpdowmSide) == 1)//���ߵ�����������һ��
//                *state = 6;
//              break;
//
////        case 5 :
////            //
////            err5 = RoundaboutGetArc(imageSide, 1, 10, &pointY);
////            //�������
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
//            //�������
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
//  * @brief    �ж����·
//  *
//  * @param  imageInput��ͼ��
//  * @param  *Flag����־λ
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
//  * @brief    �жϳ���·
//  *
//  * @param  imageInput��ͼ��
//  * @param  *Flag����־λ
//  *
//  * @return
//  *
//  * @note       ���ǳ���·��תΪ����ͷ�ģ����ǵȳ����ȶ������������Ƚ�ֱ��ʱ���л�����ͷ
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
//  * @brief    ��·������
//  *
//  * @param     Upimage[2][LCDW]���±�������   imageSideinput[LCDH][2]���ұ�������   RoadwideInput[LCDH]������� Flag ��־λ
//  *
//  * @return     ��
//  *
//  * @note
//  *
//  * @see
//  *
//  * @date     2022/11/30 ������
//  */
//void OpeningProcess(uint8_t Upimage[2][MT9V03X_W],uint8_t imageSideinput[MT9V03X_H][2],uint8_t  imageInput[MT9V03X_H][MT9V03X_W],uint8_t *Flag)
//{
//   switch(*Flag)
//   {
//       case 1:
//           gpio_set_level(P33_10, GPIO_HIGH);
//           InputOpening(imageInput,&*Flag);
//           break;     //���·
//       case 2:
//           gpio_set_level(P33_10, GPIO_LOW);
//           OutOpening(imageInput,&*Flag);
//           break;        //����·
//       default:break;
//   }
//}
//
//void CameraCar (void)
//{
////    InductorNormal();
//    /******************************************************************Բ��ʶ����*********************************************************/
//        if(Round_Flag == 0&&OpenRoad_Flag==0&&Process_Flag==0 )
//         {
//             // ��⻷��
//             RoadIsRoundabout(ImageSide, &Round_Flag);   //һ�ߵ���һ�߶���
//         }
//        if(Round_Flag)//ʶ��Բ����Բ������
//         {
//           // buzzer(100);//ʶ�𵽻�������������һ��
//            Process_Flag=2;
////            y=58;//�����
//            Target_Speed1 = 65;
//            Target_Speed2 = 65;
//            turn_PID.kp =0.5;
//            turn_PID.kd =0.25;
//            RoundaboutProcess(Bin_Image, ImageSide, UpdowmSide, &Round_Flag);
//         }
//       // gpio_set_level(P33_10, GPIO_LOW);
/////**********************************************************************��·ʶ����***********************************************************/
//        if(Round_Flag == 0&&OpenRoad_Flag==0 )
//        {
//            InputOpening(Bin_Image,&OpenRoad_Flag);//���·ʶ��
//        }
//        if(OpenRoad_Flag)//����·��־λΪ1���Զ����е��ѭ��
//        {
//            OutOpening(Bin_Image,&OpenRoad_Flag);//����·ʶ��(�����·�Ժ���)
//        }
/////***********************************************************************ֱ�����******************************************************************/
//        if(Round_Flag == 0&&OpenRoad_Flag==0 )//ֱ�����
//        {
//            Target_Speed1=60;
//            Target_Speed2=60;
//            turn_PID.kp =0.48;//3
//            turn_PID.kd =0.35 ;
//        }
//}
