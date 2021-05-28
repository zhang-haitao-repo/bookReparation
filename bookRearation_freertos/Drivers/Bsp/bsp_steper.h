#ifndef __BSP_STEPER_H__
#define __BSP_STEPER_H__

#include "main.h"

/*************X�������Ŷ���****************/
 //Motor ��������
#define X_MOTOR_DIR_GPIO GET_PIN(E, 8)
 //Motor ��������
#define X_MOTOR_PUL GET_PIN(B, 1)

/*************Y�������Ŷ���****************/
 //Motor ��������
#define Y_MOTOR_DIR GET_PIN(C, 5)
 //Motor ��������
#define Y_MOTOR_PUL GET_PIN(C, 4)

#define SUBDIVIDE 2

/* ��������ṹ�� */
typedef struct{
  GPIO_TypeDef* pul_pin_gpio;        //��������
  uint16_t pul_pin_port;        //��������
	GPIO_TypeDef* dir_pin_gpio;
	uint16_t dir_pin_port;  
}Stepper_TypeDef;

/* ������ö�� */
typedef enum{
   x_axis = 0U,
   y_axis
}Axis_TypeDef;



#endif

