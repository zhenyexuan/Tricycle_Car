#include "headfile.h"
#pragma section all "cpu1_dsram"
// **************************** �������� ***************************/
void core1_main(void)
{
    disable_Watchdog();                     // �رտ��Ź�
    interrupt_global_enable(0);             // ��ȫ���ж�
    cpu_wait_event_ready();                 // �ȴ����к��ĳ�ʼ�����
    while (TRUE)
    {
/****************************************  ����ͷͼ����--ѹ��ͼ��  ****************************************/
        if(mt9v03x_finish_flag)
        {
            halve_image(Image_addr,halvedImage_addr,MT9V03X_H,MT9V03X_W);   //ѹ��ͼ��
            ImageBinary(halvedImage_addr,halvedbinaryImage_addr,MT9V03X_HALVED_H,MT9V03X_HALVED_W);   //ͼ���ֵ��
            sao_xian(halvedbinaryImage_addr,MT9V03X_HALVED_H,MT9V03X_HALVED_W);

#if 0       //����˫�˻��⣻����ͷͼ����ʾ�Ͳ�����ʾ���ֻ��һ����
            tft180_show_gray_image(0,0,halvedbinaryImage_addr, MT9V03X_HALVED_W, MT9V03X_HALVED_H,MT9V03X_HALVED_W,MT9V03X_HALVED_H,0); //��ʾͼ��

            Draw_line(MT9V03X_HALVED_H);    //��������
            TFT180_Draw_Cross(centerline[aim_point_H],aim_point_H,RGB565_BLACK);//����Ԥê��
            TFT180_Draw_Cross(MT9V03X_HALVED_W/2,aim_point_H,RGB565_PURPLE);//������Ļ�е�
#endif

            mt9v03x_finish_flag = 0;    //��ͼ��ʹ����Ϻ�  ��������־λ�����򲻻Ὺʼ�ɼ���һ��ͼ��
        }
/****************************************  ��вɼ���TOF�ɼ�  ****************************************/

        InductorNormal();
        tof_distance=TOF_Get_Distance();    //TOF��⵽�ľ���

/****************************************  ������ܺ���  ****************************************/
        //���뿪�ؿ��Ƴ��ⷽ��
        if(gpio_get_level(SWITCH_1)==0){
       //�ҹճ��⣬�ҹ����
        Out_Ku_R();
        In_Ku_R();
//        In_Ku_R_alone();
        }
        if(gpio_get_level(SWITCH_1)==1){
        //�������
        Out_Ku_L();
        In_Ku_L();
//        In_Ku_L_alone();
        }
/****************************************  ���·���ܺ���  ****************************************/
#if 0   //��չ��ϰ�
        Barrier_L();
#endif
#if 0   //�ҹչ��ϰ�
        Barrier_R();
#endif

//            if(mt9v03x_finish_flag)                                                     //������ȡ��ͼ��
//            {
//                Get_Current_Img(current_image, mt9v03x_image);                   //��ȡԭʼͼ��
//                Get_Bin_Image(3);                                                //��򷨶�ֵ��
//                ImageGetSide(*Bin_Image,MT9V03X_H,MT9V03X_W);                    //��ȡ���ұ���
//                UpdownSideGet(*Bin_Image,UpdowmSide);                            //��ȡ���±���

///******************************************************************Բ��ʶ����*********************************************************/
//            if(Round_Flag == 0 && OpenRoad_Flag==0 && Process_Flag==0 )
//             {
//                 // ��⻷��
//                 RoadIsRoundabout(ImageSide, &Round_Flag);   //һ�ߵ���һ�߶���
//             }
//            if(Round_Flag)//ʶ��Բ����Բ������
//             {
//               // buzzer(100);//ʶ�𵽻�������������һ��
//                Process_Flag=2;
//                Target_Speed1 = 65;
//                Target_Speed2 = 65;
//                turn_PID.kp =0.5;
//                turn_PID.kd =0.25;
//                RoundaboutProcess(Bin_Image, ImageSide, UpdowmSide, &Round_Flag);
//             }

//                CameraCar();        //����ͷԪ��ʶ������ܺ���
//
//                mt9v03x_finish_flag = 0;
//            }
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}
#pragma section all restore
