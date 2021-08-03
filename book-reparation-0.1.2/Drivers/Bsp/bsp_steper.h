#ifndef __BSP_STEPER_H__
#define __BSP_STEPER_H__

#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "delay.h"
///*************X�������Ŷ���****************/
////Motor ��������
//#define X_MOTOR_DIR_GPIO GPIOE
//#define X_MOTOR_DIR_PIN GPIO_PIN_8
////Motor ��������
//#define X_MOTOR_PUL_GPIO GPIOB
//#define X_MOTOR_PUL_PIN GPIO_PIN_1

///*************Y�������Ŷ���****************/
// //Motor ��������
//#define Y_MOTOR_DIR_GPIO GPIOC
//#define Y_MOTOR_DIR_PIN GPIO_PIN_5
// //Motor ��������
//#define Y_MOTOR_PUL_GPIO GPIOC
//#define Y_MOTOR_PUL_PIN GPIO_PIN_4

#define SUBDIVIDE 4

/* ��������ṹ�� */
typedef struct{
	GPIO_TypeDef* pul_pin_gpio;        //��������
	uint16_t pul_pin_port;        //��������
	GPIO_TypeDef* dir_pin_gpio;
	uint16_t dir_pin_port; 
	double distance;
	uint8_t stopFlag;
}Stepper_TypeDef;


/* ��������ṹ�� */
typedef struct{
	float x_dis;
	float y_dis;
}StepDistance_Def;

/* ������ö�� */
typedef enum{
   x_axis = 0U,
   y_axis
}Axis_TypeDef;

/**
* @brief  ���������ת
* @param  steper            ���ص��
* @param  dir               ѡ������ת(ȡֵ��Χ��0,1)
* @param  speed             �������� ��λMS   ����Խ��Ƶ��Խ�ߣ�ת��Խ�� ϸ��Ϊ1ʱ����10ms
* @param  angle             ��Ҫת���ĽǶ�ֵ
* @param  subdivide         ϸ��ֵ
* @note   ��
* @retval ��
*/
void steper_move(Stepper_TypeDef steper, uint8_t dir, uint32_t speed, float angle);

/**
* @brief  ���������ת0.45mm
* @param  steper            ���ص��
* @param  dir               ѡ������ת(ȡֵ��Χ��0,1)
* @param  speed             �������� ��λMS   ����Խ��Ƶ��Խ�ߣ�ת��Խ�� 
* @note   ��
* @retval ��
*/
void steperMove045mm(int step, uint8_t dir, uint32_t speed);

/**
* @brief  �����������dis����
* @param  i            			���ص�������
* @param  dir               ѡ������ת(ȡֵ��Χ��0,1)
* @param  speed             �������� ��λMS   ����Խ��Ƶ��Խ�ߣ�ת��Խ�� 
* @param  dis 							��������  
* @note   ��
* @retval ��
*/
void steperMove(uint8_t i, uint8_t dir, uint32_t speed, uint32_t dis);

/**
* @brief  �����������pul����λ(һ��Pul����0.45mm)
* @param  i            			���ص�������
* @param  dir               ѡ������ת(ȡֵ��Χ��0,1)
* @param  speed             �������� ��λMS   ����Խ��Ƶ��Խ�ߣ�ת��Խ�� 
* @param  pul 							����pul����λ����  
* @note   ��
* @retval ��
*/
void steperMovePul(uint8_t step, uint8_t dir, uint32_t speed, uint32_t pul);

/**
* @brief  ������άƽ���˶�
* @param  x            		x���ƶ���λ��
* @param  y               y���ƶ��ľ���
* @note   ��
* @retval ��
*/
void steperCoordinateMajor(float major_x, float major_y);

/**
* @brief  ���������άƽ���˶�
* @param  x            		x���ƶ���λ��
* @param  y               y���ƶ��ľ���
* @note   ��
* @retval ��
*/
void steperCoordinateSecond(float Second_x, float Second_y);

void steperCoordinateMajorX(float major_x);
void steperCoordinateMajorY(float major_y);

#endif

