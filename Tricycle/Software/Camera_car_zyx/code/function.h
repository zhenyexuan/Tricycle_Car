/*
 * function.h
 *
 *  Created on: 2023��7��1��
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

//#define DL1A_SCL_PIN             (P20_13)    // ��� IIC SCL ���� ���� TOF �� SCL ����
//#define DL1A_SDA_PIN             (P20_12)    // ��� IIC SDA ���� ���� TOF �� SDA ����
#define DL1A_SCL_PIN             (P10_6)    // ��� IIC SCL ���� ���� TOF �� SCL ����
#define DL1A_SDA_PIN             (P10_5)    // ��� IIC SDA ���� ���� TOF �� SDA ����

extern volatile uint16 tof_distance; //tof��������

/*ȫ���ĳ�ʼ��*/
void All_Init(void);
/*��������ʼ��*/
void Hall_Init(void);
/*�������*/
uint8 Hall_detection(void);
/*TOF��ʼ��*/
void TOF_Init(void);
/*TOF��þ���,mmΪ��λ*/
uint16 TOF_Get_Distance(void);
/*��������ʼ��*/
void buzzer_init(void);
/*�����������ms*/
void buzzer(float time);
/*�����벦�뿪�س�ʼ������*/
void GPIO_KEY_Init(void);
void Key_Scan(void);
uint8 Pit_Key(void);

#endif /* CODE_FUNCTION_H_ */
