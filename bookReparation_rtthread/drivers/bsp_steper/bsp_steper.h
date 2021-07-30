/**
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-19     Administrator       the first version
 */
#ifndef __BSP_STEPER_H__
#define __BSP_STEPER_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <drv_common.h>

/*************X轴电机引脚定义****************/
 //Motor 方向引脚
#define X_MOTOR_DIR GET_PIN(E, 8)
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
   rt_base_t pul_pin;        //脉冲引脚
   rt_base_t dir_pin;        //方向引脚
}Stepper_TypeDef;

/* 坐标轴枚举 */
typedef enum{
   x_axis = 0U,
   y_axis
}Axis_TypeDef;


void step_init(void);
void steper_move(Stepper_TypeDef steper, rt_base_t dir, rt_uint32_t speed, float angle);

#endif
