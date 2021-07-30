#ifndef __BSP_USARTX_FIFO_H__
#define __BSP_USARTX_FIFO_H__

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "string.h"

/* ���Ͷ��� ------------------------------------------------------------------*/
/* ����˿ں� */
typedef enum
{
	COM1 = 0,	/* USART1 */
	COM2 = 1,	/* USART2 */
	COM5 = 2,	/* UART5 */
}COM_PORT_E;

/* �����豸�ṹ�� */
typedef struct
{
	USART_TypeDef *usart;              /* STM32�ڲ������豸ָ�� */
	uint8_t *pTxBuf;                   /* ���ͻ����� */
	uint8_t *pRxBuf;                   /* ���ջ����� */
	uint16_t usTxBufSize;              /* ���ͻ�������С */
	uint16_t usRxBufSize;              /* ���ջ�������С */
	__IO uint16_t usTxWrite;           /* ���ͻ�����дָ�� */
	__IO uint16_t usTxRead;            /* ���ͻ�������ָ�� */
	__IO uint16_t usTxCount;           /* �ȴ����͵����ݸ��� */

	__IO uint16_t usRxWrite;           /* ���ջ�����дָ�� */
	__IO uint16_t usRxRead;            /* ���ջ�������ָ�� */
	__IO uint16_t usRxCount;           /* ��δ��ȡ�������ݸ��� */

	void (*SendBefor)(void);           /* ��ʼ����֮ǰ�Ļص�����ָ�루��Ҫ����RS485�л�������ģʽ�� */
	void (*SendOver)(void);            /* ������ϵĻص�����ָ�루��Ҫ����RS485������ģʽ�л�Ϊ����ģʽ�� */
	void (*ReciveNew)(uint8_t _byte);  /* �����յ����ݵĻص�����ָ�� */
}USART_FIFO_Typedef;

/* �궨�� --------------------------------------------------------------------*/
#define	USART1_FIFO_EN                     	         0
#define	USART2_FIFO_EN                     	         0
#define	UART5_FIFO_EN                     	         1

#define DISABLE_INT()                                { __set_PRIMASK(1); }	/* ���ж� */
#define ENABLE_INT()                                 { __set_PRIMASK(0); }	/* ���ж� */

#if USART1_FIFO_EN == 1
	#define USART1_BAUD			                    115200
	#define USART1_TX_BUF_SIZE	                1*1024
	#define USART1_RX_BUF_SIZE	                1*1024
#endif

#if USART2_FIFO_EN == 1
	#define USART2_BAUD			                    115200
	#define USART2_TX_BUF_SIZE	                1*1024
	#define USART2_RX_BUF_SIZE	                1*1024
#endif

#if UART5_FIFO_EN == 1
	#define UART5_BAUD			                    115200
	#define UART5_TX_BUF_SIZE	                1*1024
	#define UART5_RX_BUF_SIZE	                1*1024
#endif

/* ��չ���� ------------------------------------------------------------------*/
extern UART_HandleTypeDef husart_debug;

/* �������� ------------------------------------------------------------------*/
void comSendBuf(COM_PORT_E _ucPort, uint8_t *_ucaBuf, uint16_t _usLen);
void comSendChar(COM_PORT_E _ucPort, uint8_t _ucByte);
uint8_t comGetChar(COM_PORT_E _ucPort, uint8_t *_pByte);

void comClearTxFifo(COM_PORT_E _ucPort);
void comClearRxFifo(COM_PORT_E _ucPort);
void Usart_FIFO_Init(void);


#endif  // __BSP_USARTX_FIFO_H__

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
