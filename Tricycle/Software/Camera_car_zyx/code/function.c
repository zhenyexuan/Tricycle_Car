/*
 * function.c
 *
 *  Created on: 2023年7月1日
 *      Author: ZYX
 */
#include "headfile.h"

volatile uint16 tof_distance;//TOF测量的距离

uint8 KEY_Level;
uint8 KEY_Flag;

/*全部的初始化*/
void All_Init(void){
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口
    // 此处编写外设初始化代码
    system_delay_ms(100);           //上电延迟

    buzzer_init();                  //蜂鸣器初始化

    GPIO_KEY_Init();                //按键初始化

    tft180_set_dir(1);              //设置显示方向
    tft180_init();                  //TFT初始化

    Hall_Init();                    //霍尔初始化

    TOF_Init();                     //TOF初始化

    mt9v03x_init();                 //摄像头初始化

    InductorInit();                 //电感采集初始化

    Para_Init();                    //pid参数初始化，先通过这个函数调整巡线pid***pid参数调整

    Motor_Init();                   //电机初始化

    EncoderInit();                  //编码器初始化

    buzzer(100);                    //初始化完成，蜂鸣器响一声

    pit_ms_init(CCU60_CH0, 5);      //设置定时器中断，初始化为5ms执行一次
    pit_ms_init(CCU60_CH1, 20);      //设置定时器中断，初始化为20ms执行一次

    // 此处编写外设初始化代码
    cpu_wait_event_ready();         // 等待所有核心初始化完毕
}

/*霍尔检测初始化*/
void Hall_Init(void)
{
    gpio_init(HALL_PIN, GPI, GPIO_HIGH, GPI_PULL_UP);
    gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(LED2, GPO, GPIO_HIGH, GPO_PUSH_PULL);
}
/*霍尔检测--检测到返回1，没检测到返回0*/
uint8 Hall_detection(void)
{
    uint8 trigger_state=1;
    if(gpio_get_level(HALL_PIN))
    {
        trigger_state = 0;
        gpio_set_level(LED2, GPIO_HIGH);
    }
    else
    {
        gpio_set_level(LED2, GPIO_LOW);
        if(0 == trigger_state)
        {
            trigger_state = 1;
        }
        return 1;
    }
    return 0;
}
/*TOF初始化*/
void TOF_Init(void){
    uint8 temp=dl1a_init();
    if(temp){
        zf_assert(0);
    }
}
/*TOF获得距离，mm为单位*/
uint16 TOF_Get_Distance(void){
    dl1a_get_distance();
    if(dl1a_finsh_flag == 1){
        dl1a_finsh_flag = 0;
    }
    return dl1a_distance_mm;
}
/*蜂鸣器初始化*/
void buzzer_init(void)
{
    gpio_init(P33_10, GPO, GPIO_LOW, GPO_PUSH_PULL);
}
/*蜂鸣器响多少ms*/
void buzzer(float time)
{
    gpio_set_level(P33_10, GPIO_HIGH);
    system_delay_ms(time);
    gpio_set_level(P33_10, GPIO_LOW);
}
/*按键与拨码开关初始化函数*/
void GPIO_KEY_Init(void)
{
    // 初始化,输入口，高电平
    gpio_init(KEY1, GPI, GPIO_HIGH, GPI_PULL_UP);      // 初始化 KEY1 输入 默认高电平 上拉输入
    gpio_init(KEY2, GPI, GPIO_HIGH, GPI_PULL_UP);      // 初始化 KEY2 输入 默认高电平 上拉输入
    gpio_init(KEY3, GPI, GPIO_HIGH, GPI_PULL_UP);      // 初始化 KEY3 输入 默认高电平 上拉输入
    gpio_init(KEY4, GPI, GPIO_HIGH, GPI_PULL_UP);      // 初始化 KEY4 输入 默认高电平 上拉输入
  //拨码开关
    gpio_init(SWITCH_1, GPI, GPIO_HIGH, GPI_PULL_UP);    // 初始化为GPIO浮空输入 默认上拉高电平
    gpio_init(SWITCH_2, GPI, GPIO_HIGH, GPI_PULL_UP);    // 初始化为GPIO浮空输入 默认上拉高电平
}
/*
 * 函数简介:扫描按键GPIO目前的状态
 * 参数说明:无
 * 返回参数：无
 * 使用示例：
 * 备注信息
 */
void Key_Scan(void)
{
    if(gpio_get_level(KEY1)==0)
        KEY_Flag=1;
    else if(gpio_get_level(KEY2)==0)
        KEY_Flag=2;
    else if(gpio_get_level(KEY3)==0)
        KEY_Flag=3;
    else if(gpio_get_level(KEY4)==0)
        KEY_Flag=4;
    else
        KEY_Flag=0;
}
/*
 * 函数简介:
 * 参数说明:无
 * 返回参数：按下的哪个按键，1、2、3、4分别代编第一二三四个按键
 * 使用示例：Pit_Key()==1,按下了第一个按键。
 * 备注信息
 */
uint8 Pit_Key(void)
{
    uint8 Key_Number;
    static uint8 KEY_Now,KEY_Last;
    KEY_Last=KEY_Now;
    KEY_Now=KEY_Flag;
    if(KEY_Now==0 && KEY_Last==1)
        Key_Number=1;
    if(KEY_Now==0 && KEY_Last==2)
        Key_Number=2;
    if(KEY_Now==0 && KEY_Last==3)
        Key_Number=3;
    if(KEY_Now==0 && KEY_Last==4)
        Key_Number=4;
    return Key_Number;
}
