#ifndef __BSP_USARTX_H__
#define __BSP_USARTX_H__

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* ���Ͷ��� ------------------------------------------------------------------*/
/* �궨�� --------------------------------------------------------------------*/
#define USARTx                                 UART5
#define USARTx_BAUDRATE                        115200
#define USART_RCC_CLK_ENABLE()                 __HAL_RCC_UART5_CLK_ENABLE()
#define USART_RCC_CLK_DISABLE()                __HAL_RCC_UART5_CLK_DISABLE()

#define USARTx_GPIO_ClK_ENABLE()               {__HAL_RCC_GPIOC_CLK_ENABLE();__HAL_RCC_GPIOD_CLK_ENABLE();}
#define USARTx_Tx_GPIO_PIN                     GPIO_PIN_12
#define USARTx_Tx_GPIO                         GPIOC
#define USARTx_Rx_GPIO_PIN                     GPIO_PIN_2
#define USARTx_Rx_GPIO                         GPIOD

#define USARTx_AFx                             GPIO_AF8_UART5


#define USARTx_IRQHANDLER                      UART5_IRQHandler
#define USARTx_IRQn                            UART5_IRQn

/* ��չ���� ------------------------------------------------------------------*/
/* ��չ���� ------------------------------------------------------------------*/
extern UART_HandleTypeDef husartx;

/* �������� ------------------------------------------------------------------*/
void MX_USARTx_Init(void);


#endif  /* __BSP_USARTX_H__ */

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
