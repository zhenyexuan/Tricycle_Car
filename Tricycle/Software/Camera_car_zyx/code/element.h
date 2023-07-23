/*
 * element.h
 *
 *  Created on: 2023年7月15日
 *      Author: ZYX
 */

#ifndef CODE_ELEMENT_H_
#define CODE_ELEMENT_H_
#include "headfile.h"

extern uint8 car_run_flag;
extern uint8 element_flag;   //元素标志位
extern uint8 out_ku_flag;   //出库标志位
extern uint8 barrier_flag;   //横断标志位
extern uint8 barrier_state; //横断状态位

void In_Ku_R(void);
void In_Ku_R_alone(void);
void Out_Ku_R(void);
void In_Ku_L(void);
void In_Ku_L_alone(void);
void Out_Ku_L(void);
void Barrier_L(void);
void Barrier_R(void);

#endif /* CODE_ELEMENT_H_ */
