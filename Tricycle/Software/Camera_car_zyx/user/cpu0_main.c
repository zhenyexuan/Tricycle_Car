#include "headfile.h"
#pragma section all "cpu0_dsram"
// **************************** 代码区域 ****************************
int core0_main(void)
{
    All_Init(); //全部的初始化函数
    while (TRUE)
    {
#if 1       //由于双核互斥；摄像头图像显示和参数显示最好只开一个！
        TFT_show();
        system_delay_ms(20);
#endif
    }
}
#pragma section all restore
// **************************** 代码区域 ****************************

