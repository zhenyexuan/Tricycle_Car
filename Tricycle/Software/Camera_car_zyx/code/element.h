/*
 * element.h
 *
 *  Created on: 2023��7��15��
 *      Author: ZYX
 */

#ifndef CODE_ELEMENT_H_
#define CODE_ELEMENT_H_
#include "headfile.h"

extern uint8 car_run_flag;
extern uint8 element_flag;   //Ԫ�ر�־λ
extern uint8 out_ku_flag;   //�����־λ
extern uint8 barrier_flag;   //��ϱ�־λ
extern uint8 barrier_state; //���״̬λ

void In_Ku_R(void);
void In_Ku_R_alone(void);
void Out_Ku_R(void);
void In_Ku_L(void);
void In_Ku_L_alone(void);
void Out_Ku_L(void);
void Barrier_L(void);
void Barrier_R(void);

#endif /* CODE_ELEMENT_H_ */
