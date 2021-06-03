#include "api_getStep.h"
#include "cmsis_os.h"

/**
* @brief  ��ȡ��λ���·���X����
* @param  steper            �յ��������ַ���
* @note   ��
* @retval ret								����õ���X����
*/
float getX(const uint8_t* str)
{
	float ret = 0;
	uint8_t i = 0, index = 0;
	while(str[i] != 'x'){
		i++;
	}
	i = str[1] == '-' ? 2 : 1;
	while(str[i] != ','){
		uint8_t num = str[i] - 0x30;
		ret = ret*10 + num; 
		osDelay(1);
		++i;
		if(i >= 100)
			break;
	}
	ret = str[1] == '-' ? -ret : ret;
	return ret;
}

/**
* @brief  ��ȡ��λ���·���Y����
* @param  steper            �յ��������ַ���
* @note   ��
* @retval ret								����õ���Y����
*/
float getY(const uint8_t* str)
{
	float ret = 0;
	uint8_t i = 1;
	
	i = str[1] == '-' ? 2 : 1;
	while(str[i] != ','){
		uint8_t num = str[i] - 0x30;
		ret = ret*10 + num; 
		osDelay(1);
		++i;
		if(i >= 100)
			break;
	}
	ret = str[1] == '-' ? -ret : ret;
	return ret;
}
