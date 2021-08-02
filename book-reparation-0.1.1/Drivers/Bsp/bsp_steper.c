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
void steperMove045mm(int step, uint8_t dir, uint32_t speed)
{
	Stepper_TypeDef* steper = &stepers[step];
  /* ȷ������˶�����*/
	// GPIO_PinState step_dir = dir==0?GPIO_PIN_RESET:GPIO_PIN_SET;
	HAL_GPIO_WritePin(steper->dir_pin_gpio, steper->dir_pin_port, (GPIO_PinState)dir);
	// osDelay(1);
	/*ģ�ⷽ��*/
	if(step == 1 || step == 0){
		for(int i = 0; i < 5; i++)
		{
			HAL_GPIO_WritePin(steper->pul_pin_gpio, steper->pul_pin_port, GPIO_PIN_SET);
			delay_us(speed);
			HAL_GPIO_WritePin(steper->pul_pin_gpio, steper->pul_pin_port, GPIO_PIN_RESET);
			delay_us(speed);
		}
	}else if(step == 2){
		for(int i = 0; i < 6; i++)
		{
			HAL_GPIO_WritePin(steper->pul_pin_gpio, steper->pul_pin_port, GPIO_PIN_SET);
			delay_us(speed);
			HAL_GPIO_WritePin(steper->pul_pin_gpio, steper->pul_pin_port, GPIO_PIN_RESET);
			delay_us(speed);
		}
	}else{
		for(int i = 0; i < 72; i++)
		{
			HAL_GPIO_WritePin(steper->pul_pin_gpio, steper->pul_pin_port, GPIO_PIN_SET);
			delay_us(50);
			HAL_GPIO_WritePin(steper->pul_pin_gpio, steper->pul_pin_port, GPIO_PIN_RESET);
			delay_us(50);
		}
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
	
	int n = dis/0.45;
	for(int i = 0; i < n; ++i){
		steperMove045mm(step, dir, speed);
	}
  if(step == 0){
    stepers[step].distance = dir == 1 ? stepers[step].distance + dis : stepers[step].distance - dis;
  }else{
    stepers[step].distance = dir == 0 ? stepers[step].distance + dis : stepers[step].distance - dis;
  }
}

/**
* @brief  �����������pul����λ(һ��Pul����0.45mm)
* @param  i            			���ص�������
* @param  dir               ѡ������ת(ȡֵ��Χ��0,1)
* @param  speed             �������� ��λMS   ����Խ��Ƶ��Խ�ߣ�ת��Խ�� 
* @param  pul 							����pul����λ����  
* @note   ��
* @retval ��
*/
void steperMovePul(uint8_t step, uint8_t dir, uint32_t speed, uint32_t pul)
{
	for(int i = 0; i < pul; ++i){
		steperMove045mm(step, dir, speed);
	}
  if(step == 0){
    stepers[step].distance = dir == 1 ? stepers[step].distance + pul*0.45 : stepers[step].distance - pul*0.45;
  }else{
    stepers[step].distance = dir == 0 ? stepers[step].distance + pul*0.45 : stepers[step].distance - pul*0.45;
  }
}

/**
* @brief  ���������άƽ���˶�
* @param  x            		x���ƶ���λ��
* @param  y               y���ƶ��ľ���
* @note   ��
* @retval ��
*/
void steperCoordinateMajor(float major_x, float major_y)
{
	double x = major_x - stepers[0].distance;
	double y = major_y - stepers[1].distance;
	
	int dir_y = y > 0 ? 0:1;
	float dis_y = y > 0 ? y:-y;
	steperMove(1, dir_y, 1000, dis_y);
	
	int dir_x = x > 0 ? 1:0;
	float dis_x = x > 0 ? x:-x;
	steperMove(0, dir_x, 1000, dis_x);
}

/**
* @brief  ���������άƽ���˶�
* @param  x            		x���ƶ���λ��
* @param  y               y���ƶ��ľ���
* @note   ��
* @retval ��
*/
void steperCoordinateSecond(float Second_x, float Second_y)
{
	double x = (double)504.9 - Second_x - stepers[2].distance;
	double y = Second_y - (double)70.0 - stepers[3].distance;
	
	int dir_y = y > 0 ? 0:1;
	float dis_y = y > 0 ? y:-y;
	steperMove(3, dir_y, 1000, dis_y);
	
	int dir_x = x > 0 ? 1:0;
	float dis_x = x > 0 ? x:-x;
	steperMove(2, dir_x, 1000, dis_x);
}

void steperCoordinateMajorX(float major_x)
{
	double x = major_x - stepers[0].distance;
	
	int dir_x = x > 0 ? 1:0;
	float dis_x = x > 0 ? x:-x;
	steperMove(0, dir_x, 1000, dis_x);
}

void steperCoordinateMajorY(float major_y)
{
	double y = major_y - stepers[1].distance; 
	
  int dir_y = y > 0 ? 1:0;
	float dis_y = y > 0 ? y:-y;
	steperMove(1, dir_y, 1000, dis_y);
}

