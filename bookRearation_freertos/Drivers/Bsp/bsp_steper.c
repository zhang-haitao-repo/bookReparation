#include "bsp_steper.h"
#include "delay.h"
#include "cmsis_os.h"

/* 步进电机结构体数组 */
Stepper_TypeDef steper[2] =
{
        {GPIOB, GPIO_PIN_1, GPIOE, GPIO_PIN_8},
        {GPIOC, GPIO_PIN_4, GPIOC, GPIO_PIN_5},
};

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
void steper_move(Stepper_TypeDef steper, GPIO_PinState dir, uint32_t speed, float angle)
{
    int n,i;
    /*根据细分数求得步距角被分成多少个方波*/
    n=(int)(angle/(1.8/SUBDIVIDE));

    /* 确定电机运动方向*/
    HAL_GPIO_WritePin(steper.dir_pin_gpio, steper.dir_pin_port, dir);
	osDelay(10);
	
    /*模拟方波*/
    for(i = 0; i < n; i++)
    {
        HAL_GPIO_WritePin(steper.pul_pin_gpio, steper.pul_pin_port, GPIO_PIN_SET);
        delay_us(speed);
        HAL_GPIO_WritePin(steper.pul_pin_gpio, steper.pul_pin_port, GPIO_PIN_RESET);
        delay_us(speed);
    }
}

