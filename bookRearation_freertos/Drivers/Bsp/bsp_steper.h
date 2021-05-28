#ifndef __BSP_STEPER_H__
#define __BSP_STEPER_H__

#include "main.h"

/*************X轴电机引脚定义****************/
 //Motor 方向引脚
#define X_MOTOR_DIR_GPIO GET_PIN(E, 8)
 //Motor 脉冲引脚
#define X_MOTOR_PUL GET_PIN(B, 1)

/*************Y轴电机引脚定义****************/
 //Motor 方向引脚
#define Y_MOTOR_DIR GET_PIN(C, 5)
 //Motor 脉冲引脚
#define Y_MOTOR_PUL GET_PIN(C, 4)

#define SUBDIVIDE 2

/* 步进电机结构体 */
typedef struct{
  GPIO_TypeDef* pul_pin_gpio;        //脉冲引脚
  uint16_t pul_pin_port;        //方向引脚
	GPIO_TypeDef* dir_pin_gpio;
	uint16_t dir_pin_port;  
}Stepper_TypeDef;

/* 坐标轴枚举 */
typedef enum{
   x_axis = 0U,
   y_axis
}Axis_TypeDef;



#endif

