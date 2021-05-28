#include "bsp_steper.h"
#include "delay.h"
#include "cmsis_os.h"

/* ��������ṹ������ */
Stepper_TypeDef steper[2] =
{
        {GPIOB, GPIO_PIN_1, GPIOE, GPIO_PIN_8},
        {GPIOC, GPIO_PIN_4, GPIOC, GPIO_PIN_5},
};

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
void steper_move(Stepper_TypeDef steper, GPIO_PinState dir, uint32_t speed, float angle)
{
    int n,i;
    /*����ϸ������ò���Ǳ��ֳɶ��ٸ�����*/
    n=(int)(angle/(1.8/SUBDIVIDE));

    /* ȷ������˶�����*/
    HAL_GPIO_WritePin(steper.dir_pin_gpio, steper.dir_pin_port, dir);
	osDelay(10);
	
    /*ģ�ⷽ��*/
    for(i = 0; i < n; i++)
    {
        HAL_GPIO_WritePin(steper.pul_pin_gpio, steper.pul_pin_port, GPIO_PIN_SET);
        delay_us(speed);
        HAL_GPIO_WritePin(steper.pul_pin_gpio, steper.pul_pin_port, GPIO_PIN_RESET);
        delay_us(speed);
    }
}

