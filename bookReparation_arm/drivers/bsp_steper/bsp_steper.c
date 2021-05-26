/**
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-19     Administrator       the first version
 */
#include <stdlib.h>
#include "bsp_steper.h"

/* 步进电机结构体数组 */
Stepper_TypeDef steper[2] =
{
        {X_MOTOR_PUL, X_MOTOR_DIR},
        {Y_MOTOR_PUL, Y_MOTOR_DIR},
};

/**
* @brief  步进电机引脚初始化
* @param  无
* @note   无
* @retval 无
*/
void step_init()
{
    rt_pin_mode(steper[0].dir_pin, PIN_MODE_OUTPUT);
    rt_pin_mode(steper[0].pul_pin, PIN_MODE_OUTPUT);

    rt_pin_mode(steper[1].dir_pin, PIN_MODE_OUTPUT);
    rt_pin_mode(steper[1].pul_pin, PIN_MODE_OUTPUT);
}

/**
* @brief  步进电机旋转
* @param  steper            被控电机
* @param  dir               选择正反转(取值范围：0,1)
* @param  speed             方波周期 单位MS   周期越短频率越高，转速越快 细分为1时最少10ms
* @param  angle             需要转动的角度值
* @param  subdivide         细分值
* @note   无
* @retval 无
*/
void steper_move(Stepper_TypeDef steper, rt_base_t dir, rt_uint32_t speed, float angle)
{
    int n,i;
    /*根据细分数求得步距角被分成多少个方波*/
    n=(int)(angle/(1.8/SUBDIVIDE));

    /* 确定电机运动方向*/
    rt_pin_write(steper.dir_pin, dir);
    rt_thread_mdelay(10);

    /*模拟方波*/
    for(i = 0; i < n; i++)
    {
        rt_pin_write(steper.pul_pin, 1);
        rt_hw_us_delay(speed);
        rt_pin_write(steper.pul_pin, 0);
        rt_hw_us_delay(speed);
    }
}

void steper_coordinate(float x, float y)
{
    int dir_x = x > 0 ? 1:0;
    float angle_x = x > 0 ? x*360:-x*360;
    steper_move(steper[0], dir_x, 500, angle_x);

    int dir_y = y > 0 ? 1:0;
    float angle_y = y > 0 ? y*360:-y*360;
    steper_move(steper[1], dir_y, 500, angle_y);
}

static void steper_move_auto(int argc, char** argv)
{
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    steper_coordinate(x, y);
}

/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(steper_move_auto, step move:<angle speed dir>);
