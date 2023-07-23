/*
 * function.h
 *
 *  Created on: 2023年7月1日
 *      Author: ZYX
 */

#ifndef CODE_FUNCTION_H_
#define CODE_FUNCTION_H_
#include "headfile.h"

#define HALL_PIN                (P10_2)
#define LED1                    (P20_9)
#define LED2                    (P20_8)

#define SWITCH_1                 (P33_12)
#define SWITCH_2                 (P33_13)

#define KEY1                    (P22_0)
#define KEY2                    (P22_1)
#define KEY3                    (P22_2)
#define KEY4                    (P22_3)

//#define DL1A_SCL_PIN             (P20_13)    // 软件 IIC SCL 引脚 连接 TOF 的 SCL 引脚
//#define DL1A_SDA_PIN             (P20_12)    // 软件 IIC SDA 引脚 连接 TOF 的 SDA 引脚
#define DL1A_SCL_PIN             (P10_6)    // 软件 IIC SCL 引脚 连接 TOF 的 SCL 引脚
#define DL1A_SDA_PIN             (P10_5)    // 软件 IIC SDA 引脚 连接 TOF 的 SDA 引脚

extern volatile uint16 tof_distance; //tof测量距离

/*全部的初始化*/
void All_Init(void);
/*霍尔检测初始化*/
void Hall_Init(void);
/*霍尔检测*/
uint8 Hall_detection(void);
/*TOF初始化*/
void TOF_Init(void);
/*TOF获得距离,mm为单位*/
uint16 TOF_Get_Distance(void);
/*蜂鸣器初始化*/
void buzzer_init(void);
/*蜂鸣器响多少ms*/
void buzzer(float time);
/*按键与拨码开关初始化函数*/
void GPIO_KEY_Init(void);
void Key_Scan(void);
uint8 Pit_Key(void);

#endif /* CODE_FUNCTION_H_ */
