///*
// * round.c
// *
// *  Created on: 2023��7��3��
// *      Author: ZYX
// */
//#include "round.h"
//
//#define  up     0
//#define  down   1
//#define  left   0
//#define  right  1
//
//uint8 count;        //Բ������λ�ã�
//uint8 round_size=6; //Բ��������������ֵ
//uint8 line_size=50; //Բ��������������ֵ
//
////��������
//uint8 ImageSide[MT9V03X_H][2];//���ұ���
//uint8 UpdowmSide[2][MT9V03X_W];//���±���
//
//uint8 RoadIsRound(uint8 Upimage[2][MT9V03X_H], uint8 imageInput[MT9V03X_H][MT9V03X_W], uint8 image[MT9V03X_H][2], uint8 *flag)
//{
//    uint8 i = 0;
//    static uint8 errL=0, errR=0;
//    static uint8 leftState = 0, rightState = 0;
//    count = 0;
//    uint8_t num = 0, py;
//
//    // �ӳ�ͷ��ǰ ������Ƿ񵥵�
//    for(i = START_H-2; i > END_H; i--)
//    {
//        if(image[i][0] == 1)
//            continue;
//        if(image[i][0] >= image[i+1][0])    // i��Y����ֵ  0 ��ͼ������X����
//        {
//            if(image[i][0]<MT9V03X_W/2 - 5)
//                num++;
//            else
//                num = 0  ;
//
//            if(num == line_size)
//            {
//                num = 0;
//                leftState = 1;   // �󵥵���־
//                break;
//            }
//        }
//        else
//        {
//            num = 0;
//        }
//        if(i <= END_H+1)  //   ��0
//            num = 0;
//    }
//
//    errL = RoundaboutGetArc(image, 1, round_size, &py); //����Ƿ��л���
//    errR = RoundaboutGetArc(image, 2, round_size, &py);
//
//    // �ұ����Ƿ񵥵�
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
//                rightState = 1; // �ҵ�����־
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
//    // ��ߵ����� ����Ҳ��Ƿ��ǻ���
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
//    /* �ұߵ����� �������Ƿ��ǻ��� */
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
//  * @brief    �ж����ұ����Ƿ���ڻ���
//  * ����� index Բ���Ķ���λ��
//  * @param    imageInput �� ��ֵͼ����Ϣ
//  * @param    imageOut   �� ��������
//  * @param    status     �� 1�������  2���ұ���
//  * @param    num        �� Բ���Ĵ�С �õ�����ʾ  ������N����  ����N������
//  * @return   1 �л���    0  û����
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
//            //û�ж���
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
//    }
//
//    return 0;
//}
//#if 0
///*-----------------------------------------------------------------!
//  * @brief    ��ȡ����
//  *
//  * @param    imageInput �� ��ֵͼ����Ϣ
//  * @param    imageOut   �� ��������
//  *
//  * @return   �Ƿ���
//  *
//  * @note     ˼·���Ӿ��복ͷ�Ͻ����п�ʼ���м�����������
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
//        // �þ���С���ȽϽ����� �ж��Ƿ���
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
//    // ����ÿ��
//    for(i = MT9V03X_H-2; i > 0; i--)
//    {
//        // ��������
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
//   //����ÿһ��
//   for(i = MT9V03X_H-2; i > 0; i--)
//   {
//        //��������
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
//     //��ͼ���м���    ���е���     ���е���      ɨ��
//
//    //�����м䵥����һ�е����±���
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
//    //�����е����±���
//    //���е���
//    for(i = MT9V03X_W/2-1; i > 0; i--)//����ÿһ��
//    {
//        imageOut[up][i] = 0;
//        imageOut[down][i] = MT9V03X_H-1;
//
//        for(j = imageOut[0][i+1] + 5; j > 0; j--)//һ���е�ɨ��ÿ��  �����е�����+10��ʼ����ɨ��
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
//    //���е���
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
