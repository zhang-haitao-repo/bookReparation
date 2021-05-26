/**
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-18     RT-Thread    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "main.h"

void GPIO_init()
{
    rt_pin_mode(BEEP, PIN_MODE_OUTPUT);
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED3_PIN, PIN_MODE_OUTPUT);

    rt_pin_write(BEEP, 1);
    rt_thread_mdelay(200);
    rt_pin_write(BEEP, 0);
    rt_thread_mdelay(200);

    rt_pin_write(LED1_PIN, 1);
    rt_pin_write(LED3_PIN, 1);
    rt_pin_write(LED2_PIN, 0);
}

int main(void)
{
    int count = 1;
    GPIO_init();
    step_init();

    while (1)
    {
        rt_thread_mdelay(5000);
//        rt_kprintf("count = [%d] Hello RT-Thread!\r\n", count/2);
        count++;

        rt_pin_write(LED2_PIN, count/2);
    }

    return RT_EOK;
}
