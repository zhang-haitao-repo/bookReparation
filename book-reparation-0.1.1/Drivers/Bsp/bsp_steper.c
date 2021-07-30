#include "bsp_steper.h"
#include "cmsis_os.h"

/* ��������ṹ������ */
Stepper_TypeDef stepers[4] =
{
        {MOTOR_PUL_0_GPIO_Port, MOTOR_PUL_0_Pin, MOTOR_DIR_0_GPIO_Port, MOTOR_DIR_0_Pin},
        {MOTOR_PUL_1_GPIO_Port, MOTOR_PUL_1_Pin, MOTOR_DIR_1_GPIO_Port, MOTOR_DIR_1_Pin},
				{MOTOR_PUL_2_GPIO_Port, MOTOR_PUL_2_Pin, MOTOR_DIR_2_GPIO_Port, MOTOR_DIR_2_Pin},
				{MOTOR_PUL_3_GPIO_Port, MOTOR_PUL_3_Pin, MOTOR_DIR_3_GPIO_Port, MOTOR_DIR_3_Pin},
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
	// osDelay(1);
	/*ģ�ⷽ��*/
	for(i = 0; i < n; i++)
	{
		HAL_GPIO_WritePin(steper.pul_pin_gpio, steper.pul_pin_port, GPIO_PIN_SET);
		delay_us(speed);
		HAL_GPIO_WritePin(steper.pul_pin_gpio, steper.pul_pin_port, GPIO_PIN_RESET);
		delay_us(speed);
	}
}

/**
* @brief  ���������ת0.45mm
* @param  steper            ���ص��
* @param  dir               ѡ������ת(ȡֵ��Χ��0,1)
* @param  speed             �������� ��λMS   ����Խ��Ƶ��Խ�ߣ�ת��Խ�� 
* @note   ��
* @retval ��
*/
void steperMove045mm(Stepper_TypeDef steper, uint8_t dir, uint32_t speed)
{
    /* ȷ������˶�����*/
	GPIO_PinState step_dir = dir==0?GPIO_PIN_RESET:GPIO_PIN_SET;
	HAL_GPIO_WritePin(steper.dir_pin_gpio, steper.dir_pin_port, step_dir);
	// osDelay(1);
	/*ģ�ⷽ��*/
	for(int i = 0; i < 5; i++)
	{
		HAL_GPIO_WritePin(steper.pul_pin_gpio, steper.pul_pin_port, GPIO_PIN_SET);
		delay_us(speed);
		HAL_GPIO_WritePin(steper.pul_pin_gpio, steper.pul_pin_port, GPIO_PIN_RESET);
		delay_us(speed);
	}
}

/**
* @brief  �����������dis����
* @param  i            			���ص�������
* @param  dir               ѡ������ת(ȡֵ��Χ��0,1)
* @param  speed             �������� ��λMS   ����Խ��Ƶ��Խ�ߣ�ת��Խ�� 
* @param  dis 							��������  
* @note   ��
* @retval ��
*/
void steperMove(uint8_t step, uint8_t dir, uint32_t speed, uint32_t dis)
{
	Stepper_TypeDef* steper = &stepers[step];
	int n = dis/0.45;
	for(int i = 0; i < n; ++i){
		steperMove045mm(*steper, dir, speed);
	}
  if(step == 0 || step == 2){
    steper->distance = dir == 1 ? steper->distance + dis : steper->distance - dis;
  }else{
    steper->distance = dir == 0 ? steper->distance + dis : steper->distance - dis;
  }
}

/**
* @brief  ������άƽ���˶�
* @param  x            		x����Ҫ�ƶ���λ��
* @param  y               y����Ҫ�ƶ��ľ���
* @note   ��
* @retval ��
*/
void steper_coordinate(float x, float y)
{
    int dir_x = x > 0 ? 1:0;
    float angle_x = x > 0 ? x*360:-x*360;
    steper_move(stepers[0], dir_x, 100, angle_x);

    int dir_y = y > 0 ? 1:0;
    float angle_y = y > 0 ? y*360:-y*360;
    steper_move(stepers[1], dir_y, 100, angle_y);
}

void steper_coordinate_x(float x)
{
    int dir_x = x > 0 ? 1:0;
    float angle_x = x > 0 ? x*360:-x*360;
    steper_move(stepers[0], dir_x, 500, angle_x);
}

void steper_coordinate_y(float y)
{
    int dir_y = y > 0 ? 1:0;
    float angle_y = y > 0 ? y*360:-y*360;
    steper_move(stepers[1], dir_y, 500, angle_y);
}

