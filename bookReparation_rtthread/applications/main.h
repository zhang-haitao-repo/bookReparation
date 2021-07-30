/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-19     Administrator       the first version
 */
#ifndef __MAIN_H__
#define __MIAN_H__

#include <rtdbg.h>
#include "bsp_steper.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG

#define BEEP GET_PIN(D, 11)
#define LED1_PIN GET_PIN(D, 8)
#define LED2_PIN GET_PIN(D, 9)
#define LED3_PIN GET_PIN(D, 10)

void GPIO_init(void);

#endif
