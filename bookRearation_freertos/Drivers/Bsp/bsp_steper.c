#include "bsp_steper.h"
#include "delay.h"
#include "cmsis_os.h"

/* ��������ṹ������ */
Stepper_TypeDef steper[2] =
{
        {X_MOTOR_PUL_GPIO, X_MOTOR_PUL_PIN, X_MOTOR_DIR_GPIO, X_MOTOR_DIR_PIN},
        {Y_MOTOR_PUL_GPIO, Y_MOTOR_PUL_PIN, Y_MOTOR_DIR_GPIO, Y_MOTOR_DIR_PIN},
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
void steper_move(Stepper_TypeDef steper, uint8_t dir, uint32_t speed, float angle)
{
	int n,i;
	/*����ϸ������ò���Ǳ��ֳɶ��ٸ�����*/
	n=(int)(angle/(1.8/SUBDIVIDE));

    /* ȷ������˶�����*/
	GPIO_PinState step_dir = dir==0?GPIO_PIN_RESET:GPIO_PIN_SET;
	HAL_GPIO_WritePin(steper.dir_pin_gpio, steper.dir_pin_port, step_dir);
	osDelay(1);
	/*ģ�ⷽ��*/
	for(i = 0; i < n; i++)
	{
		HAL_GPIO_WritePin(steper.pul_pin_gpio, steper.pul_pin_port, GPIO_PIN_SET);
		//delay_us(100);
		osDelay(1);
		HAL_GPIO_WritePin(steper.pul_pin_gpio, steper.pul_pin_port, GPIO_PIN_RESET);
		//delay_us(100);
		osDelay(1);
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

