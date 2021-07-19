#ifndef __BSP_STEPER_H__
#define __BSP_STEPER_H__

#include "main.h"
#include "stdio.h"
#include "stdlib.h"

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

void steper_move(Stepper_TypeDef steper, uint8_t dir, uint32_t speed, float angle);
void steper_coordinate(float x, float y);
void steper_coordinate_x(float x);
void steper_coordinate_y(float y);

#endif

