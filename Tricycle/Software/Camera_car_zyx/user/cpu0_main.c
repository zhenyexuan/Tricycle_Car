#include "headfile.h"
#pragma section all "cpu0_dsram"
// **************************** �������� ****************************
int core0_main(void)
{
    All_Init(); //ȫ���ĳ�ʼ������
    while (TRUE)
    {
#if 1       //����˫�˻��⣻����ͷͼ����ʾ�Ͳ�����ʾ���ֻ��һ����
        TFT_show();
        system_delay_ms(20);
#endif
    }
}
#pragma section all restore
// **************************** �������� ****************************

