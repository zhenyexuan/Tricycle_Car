/*
 * function.c
 *
 *  Created on: 2023��7��1��
 *      Author: ZYX
 */
#include "headfile.h"

volatile uint16 tof_distance;//TOF�����ľ���

uint8 KEY_Level;
uint8 KEY_Flag;

/*ȫ���ĳ�ʼ��*/
void All_Init(void){
    clock_init();                   // ��ȡʱ��Ƶ��<��ر���>
    debug_init();                   // ��ʼ��Ĭ�ϵ��Դ���
    // �˴���д�����ʼ������
    system_delay_ms(100);           //�ϵ��ӳ�

    buzzer_init();                  //��������ʼ��

    GPIO_KEY_Init();                //������ʼ��

    tft180_set_dir(1);              //������ʾ����
    tft180_init();                  //TFT��ʼ��

    Hall_Init();                    //������ʼ��

    TOF_Init();                     //TOF��ʼ��

    mt9v03x_init();                 //����ͷ��ʼ��

    InductorInit();                 //��вɼ���ʼ��

    Para_Init();                    //pid������ʼ������ͨ�������������Ѳ��pid***pid��������

    Motor_Init();                   //�����ʼ��

    EncoderInit();                  //��������ʼ��

    buzzer(100);                    //��ʼ����ɣ���������һ��

    pit_ms_init(CCU60_CH0, 5);      //���ö�ʱ���жϣ���ʼ��Ϊ5msִ��һ��
    pit_ms_init(CCU60_CH1, 20);      //���ö�ʱ���жϣ���ʼ��Ϊ20msִ��һ��

    // �˴���д�����ʼ������
    cpu_wait_event_ready();         // �ȴ����к��ĳ�ʼ�����
}

/*��������ʼ��*/
void Hall_Init(void)
{
    gpio_init(HALL_PIN, GPI, GPIO_HIGH, GPI_PULL_UP);
    gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(LED2, GPO, GPIO_HIGH, GPO_PUSH_PULL);
}
/*�������--��⵽����1��û��⵽����0*/
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
/*TOF��ʼ��*/
void TOF_Init(void){
    uint8 temp=dl1a_init();
    if(temp){
        zf_assert(0);
    }
}
/*TOF��þ��룬mmΪ��λ*/
uint16 TOF_Get_Distance(void){
    dl1a_get_distance();
    if(dl1a_finsh_flag == 1){
        dl1a_finsh_flag = 0;
    }
    return dl1a_distance_mm;
}
/*��������ʼ��*/
void buzzer_init(void)
{
    gpio_init(P33_10, GPO, GPIO_LOW, GPO_PUSH_PULL);
}
/*�����������ms*/
void buzzer(float time)
{
    gpio_set_level(P33_10, GPIO_HIGH);
    system_delay_ms(time);
    gpio_set_level(P33_10, GPIO_LOW);
}
/*�����벦�뿪�س�ʼ������*/
void GPIO_KEY_Init(void)
{
    // ��ʼ��,����ڣ��ߵ�ƽ
    gpio_init(KEY1, GPI, GPIO_HIGH, GPI_PULL_UP);      // ��ʼ�� KEY1 ���� Ĭ�ϸߵ�ƽ ��������
    gpio_init(KEY2, GPI, GPIO_HIGH, GPI_PULL_UP);      // ��ʼ�� KEY2 ���� Ĭ�ϸߵ�ƽ ��������
    gpio_init(KEY3, GPI, GPIO_HIGH, GPI_PULL_UP);      // ��ʼ�� KEY3 ���� Ĭ�ϸߵ�ƽ ��������
    gpio_init(KEY4, GPI, GPIO_HIGH, GPI_PULL_UP);      // ��ʼ�� KEY4 ���� Ĭ�ϸߵ�ƽ ��������
  //���뿪��
    gpio_init(SWITCH_1, GPI, GPIO_HIGH, GPI_PULL_UP);    // ��ʼ��ΪGPIO�������� Ĭ�������ߵ�ƽ
    gpio_init(SWITCH_2, GPI, GPIO_HIGH, GPI_PULL_UP);    // ��ʼ��ΪGPIO�������� Ĭ�������ߵ�ƽ
}
/*
 * �������:ɨ�谴��GPIOĿǰ��״̬
 * ����˵��:��
 * ���ز�������
 * ʹ��ʾ����
 * ��ע��Ϣ
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
 * �������:
 * ����˵��:��
 * ���ز��������µ��ĸ�������1��2��3��4�ֱ�����һ�����ĸ�����
 * ʹ��ʾ����Pit_Key()==1,�����˵�һ��������
 * ��ע��Ϣ
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
