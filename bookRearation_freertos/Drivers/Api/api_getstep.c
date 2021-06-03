#include "api_getStep.h"
#include "cmsis_os.h"

/**
* @brief  获取上位机下发的X坐标
* @param  steper            收到的数据字符串
* @note   无
* @retval ret								计算得到的X坐标
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
* @brief  获取上位机下发的Y坐标
* @param  steper            收到的数据字符串
* @note   无
* @retval ret								计算得到的Y坐标
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
