/**
  ******************************************************************************
  * �ļ�����: bsp_debug_usart.c 
  * ��    ��: ӲʯǶ��ʽ�����Ŷ�
  * ��    ��: V1.0
  * ��д����: 2015-10-04
  * ��    ��: ���ص��Դ��ڵײ���������Ĭ��ʹ��USART1
  ******************************************************************************
  * ˵����
  * ����������Ӳʯstm32������YS-F1Proʹ�á�
  * 
  * �Ա���
  * ��̳��http://www.ing10bbs.com
  * ��Ȩ��ӲʯǶ��ʽ�����Ŷ����У��������á�
  ******************************************************************************
  */

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "usart/bsp_usartx_fifo.h"

/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
/* ˽�б��� ------------------------------------------------------------------*/
UART_HandleTypeDef husart_debug;
uint8_t ch;

/* ����ÿ�����ڽṹ����� */
#if USART1_FIFO_EN == 1
	static USART_FIFO_Typedef g_tUsart1;
	static uint8_t g_TxBuf1[USART1_TX_BUF_SIZE];		/* ���ͻ����� */
	static uint8_t g_RxBuf1[USART1_RX_BUF_SIZE];		/* ���ջ����� */
#endif

#if USART2_FIFO_EN == 1
	static USART_FIFO_Typedef g_tUsart2;
	static uint8_t g_TxBuf2[USART2_TX_BUF_SIZE];		/* ���ͻ����� */
	static uint8_t g_RxBuf2[USART2_RX_BUF_SIZE];		/* ���ջ����� */
#endif

#if UART5_FIFO_EN == 1
	static USART_FIFO_Typedef g_tUsart5;
	static uint8_t g_TxBuf3[UART5_TX_BUF_SIZE];		/* ���ͻ����� */
	static uint8_t g_RxBuf3[UART5_RX_BUF_SIZE];		/* ���ջ����� */
#endif

/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
/* ������ --------------------------------------------------------------------*/
static void UsartVarInit(void)
{
#if USART1_FIFO_EN == 1
	g_tUsart1.usart = USART1;						        /* STM32 �����豸 */
	g_tUsart1.pTxBuf = g_TxBuf1;					        /* ���ͻ�����ָ�� */
	g_tUsart1.pRxBuf = g_RxBuf1;					        /* ���ջ�����ָ�� */
	g_tUsart1.usTxBufSize = USART1_TX_BUF_SIZE;	/* ���ͻ�������С */
	g_tUsart1.usRxBufSize = USART1_RX_BUF_SIZE;	/* ���ջ�������С */
	g_tUsart1.usTxWrite = 0;			          			/* ����FIFOд���� */
	g_tUsart1.usTxRead = 0;						          /* ����FIFO������ */
	g_tUsart1.usRxWrite = 0;						          /* ����FIFOд���� */
	g_tUsart1.usRxRead = 0;						          /* ����FIFO������ */
	g_tUsart1.usRxCount = 0;						          /* ���յ��������ݸ��� */
	g_tUsart1.usTxCount = 0;						          /* �����͵����ݸ��� */
	g_tUsart1.SendBefor = 0;						          /* ��������ǰ�Ļص����� */
	g_tUsart1.SendOver = 0;						          /* ������Ϻ�Ļص����� */
	g_tUsart1.ReciveNew = 0;						          /* ���յ������ݺ�Ļص����� */
#endif

#if USART2_FIFO_EN == 1
	g_tUsart2.usart = USART2;						        /* STM32 �����豸 */
	g_tUsart2.pTxBuf = g_TxBuf2;					        /* ���ͻ�����ָ�� */
	g_tUsart2.pRxBuf = g_RxBuf2;					        /* ���ջ�����ָ�� */
	g_tUsart2.usTxBufSize = USART2_TX_BUF_SIZE;	/* ���ͻ�������С */
	g_tUsart2.usRxBufSize = USART2_RX_BUF_SIZE;	/* ���ջ�������С */
	g_tUsart2.usTxWrite = 0;			          			/* ����FIFOд���� */
	g_tUsart2.usTxRead = 0;						          /* ����FIFO������ */
	g_tUsart2.usRxWrite = 0;						          /* ����FIFOд���� */
	g_tUsart2.usRxRead = 0;						          /* ����FIFO������ */
	g_tUsart2.usRxCount = 0;						          /* ���յ��������ݸ��� */
	g_tUsart2.usTxCount = 0;						          /* �����͵����ݸ��� */
	g_tUsart2.SendBefor = 0;						          /* ��������ǰ�Ļص����� */
	g_tUsart2.SendOver = 0;						          /* ������Ϻ�Ļص����� */
	g_tUsart2.ReciveNew = 0;						          /* ���յ������ݺ�Ļص����� */
#endif

#if UART5_FIFO_EN == 1
	g_tUsart5.usart = UART5;						        /* STM32 �����豸 */
	g_tUsart5.pTxBuf = g_TxBuf3;					        /* ���ͻ�����ָ�� */
	g_tUsart5.pRxBuf = g_RxBuf3;					        /* ���ջ�����ָ�� */
	g_tUsart5.usTxBufSize = UART5_TX_BUF_SIZE;	/* ���ͻ�������С */
	g_tUsart5.usRxBufSize = UART5_RX_BUF_SIZE;	/* ���ջ�������С */
	g_tUsart5.usTxWrite = 0;			          			/* ����FIFOд���� */
	g_tUsart5.usTxRead = 0;						          /* ����FIFO������ */
	g_tUsart5.usRxWrite = 0;						          /* ����FIFOд���� */
	g_tUsart5.usRxRead = 0;						          /* ����FIFO������ */
	g_tUsart5.usRxCount = 0;						          /* ���յ��������ݸ��� */
	g_tUsart5.usTxCount = 0;						          /* �����͵����ݸ��� */
	g_tUsart5.SendBefor = 0;						          /* ��������ǰ�Ļص����� */
	g_tUsart5.SendOver = 0;						          /* ������Ϻ�Ļص����� */
	g_tUsart5.ReciveNew = 0;						          /* ���յ������ݺ�Ļص����� */
#endif
}

/**
  * ��������: ����Ӳ����ʼ������
  * �������: huart�����ھ������ָ��
  * �� �� ֵ: ��
  * ˵    ��: �ú�����HAL���ڲ�����
  */
static void InitHardUsart(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  
#if USART1_FIFO_EN == 1		/* ����1 TX = PA9   RX = PA10 */
    /* ��������ʱ��ʹ�� */
    __HAL_RCC_USART1_CLK_ENABLE();
    /* ʹ�ܴ��ڹ�������GPIOʱ�� */
    __HAL_RCC_GPIOB_CLK_ENABLE();  
    /* �������蹦��GPIO���� */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = GPIO_PIN_7;  
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);   
  
    husart_debug.Instance = USART1;
    husart_debug.Init.BaudRate = USART1_BAUD;
    husart_debug.Init.WordLength = UART_WORDLENGTH_8B;
    husart_debug.Init.StopBits = UART_STOPBITS_1;
    husart_debug.Init.Parity = UART_PARITY_NONE;
    husart_debug.Init.Mode = UART_MODE_TX_RX;
    husart_debug.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    husart_debug.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&husart_debug);
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif
  
#if USART2_FIFO_EN == 1		/* ����2 TX = PA2�� RX = PA3  */
    /* ��������ʱ��ʹ�� */
    __HAL_RCC_USART2_CLK_ENABLE();
    /* ʹ�ܴ��ڹ�������GPIOʱ�� */
    __HAL_RCC_GPIOD_CLK_ENABLE();  
    /* �������蹦��GPIO���� */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = GPIO_PIN_6;  
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);   
    
    husart_debug.Instance = USART2;
    husart_debug.Init.BaudRate = USART2_BAUD;
    husart_debug.Init.WordLength = UART_WORDLENGTH_8B;
    husart_debug.Init.StopBits = UART_STOPBITS_1;
    husart_debug.Init.Parity = UART_PARITY_NONE;
    husart_debug.Init.Mode = UART_MODE_TX_RX;
    husart_debug.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    husart_debug.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&husart_debug);
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
#endif

#if UART5_FIFO_EN == 1			/* ����5 TX = PB10   RX = PB11 */
    /* ��������ʱ��ʹ�� */
    __HAL_RCC_UART5_CLK_ENABLE();
    /* ʹ�ܴ��ڹ�������GPIOʱ�� */
    __HAL_RCC_GPIOC_CLK_ENABLE();  
    __HAL_RCC_GPIOD_CLK_ENABLE();  
    /* �������蹦��GPIO���� */
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = GPIO_PIN_2;  
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);   
    
    husart_debug.Instance = UART5;
    husart_debug.Init.BaudRate = UART5_BAUD;
    husart_debug.Init.WordLength = UART_WORDLENGTH_8B;
    husart_debug.Init.StopBits = UART_STOPBITS_1;
    husart_debug.Init.Parity = UART_PARITY_NONE;
    husart_debug.Init.Mode = UART_MODE_TX_RX;
    husart_debug.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    husart_debug.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&husart_debug);
    HAL_NVIC_SetPriority(UART5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(UART5_IRQn);
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
#endif
}

/**
  * ��������: ���ڲ�������.
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void Usart_FIFO_Init(void)
{  
    /* ��ʼ��������صı��� */
  InitHardUsart();
  UsartVarInit();
}

/**
  * ��������: ��COM�˿ں�ת��ΪUARTָ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
USART_FIFO_Typedef *ComToUsart(COM_PORT_E _ucPort)
{
	if (_ucPort == COM1)
	{
#if USART1_FIFO_EN == 1
			return &g_tUsart1;
#else
			return 0;
#endif
	}
	else if (_ucPort == COM2)
	{
#if USART2_FIFO_EN == 1
			return &g_tUsart2;
#else
			return 0;
#endif
	}
	else if (_ucPort == COM5)
	{
#if UART5_FIFO_EN == 1
			return &g_tUsart5;
#else
			return 0;
#endif
	}
	else
	{
		/* �����κδ��� */
		return 0;
	}
}

/**
  * ��������: �Ӵ��ڽ��ջ�������ȡ1�ֽ����� ��������������ã�
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
static uint8_t UsartGetChar(USART_FIFO_Typedef *_pUsart, uint8_t *_pByte)
{
	uint16_t usCount;

	/* usRxWrite �������жϺ����б���д���������ȡ�ñ���ʱ����������ٽ������� */
	DISABLE_INT();
	usCount = _pUsart->usRxCount;
	ENABLE_INT();

	if (usCount == 0)	/* �Ѿ�û������ */
	{
		return 0;
	}
	else
	{
		*_pByte = _pUsart->pRxBuf[_pUsart->usRxRead];		/* �Ӵ��ڽ���FIFOȡ1������ */
    
		/* ��дFIFO������ */
		DISABLE_INT();
		if (++_pUsart->usRxRead >= _pUsart->usRxBufSize)
		{
			_pUsart->usRxRead = 0;
		}
		_pUsart->usRxCount--;
		ENABLE_INT();
    
    return 1;
	}
}   

/**
  * ��������: ��д���ݵ�UART���ͻ�����,�����������жϡ��жϴ�����������Ϻ��Զ��رշ����ж�
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
static void UsartSend(USART_FIFO_Typedef *_pUsart, uint8_t *_ucaBuf, uint16_t _usLen)
{
	uint16_t i;

	for (i = 0; i < _usLen; i++)
	{
		/* ������ͻ������Ѿ����ˣ���ȴ��������� */
		/* �� _pUsart->usTxBufSize == 1 ʱ, ����ĺ���������(������) */
		while (1)
		{
			__IO uint16_t usCount;

			DISABLE_INT();
			usCount = _pUsart->usTxCount;
			ENABLE_INT();

			if (usCount < _pUsart->usTxBufSize)
			{
				break;
			}
		}
		/* �����������뷢�ͻ����� */
		_pUsart->pTxBuf[_pUsart->usTxWrite] = _ucaBuf[i];

		DISABLE_INT();
		if (++_pUsart->usTxWrite >= _pUsart->usTxBufSize)
		{
			_pUsart->usTxWrite = 0;
		}
		_pUsart->usTxCount++;
		ENABLE_INT();
	}
	__HAL_UART_ENABLE_IT(&husart_debug, USART_IT_TXE);
}

/**
  * ��������: �򴮿ڷ���һ�����ݡ����ݷŵ����ͻ��������������أ����жϷ�������ں�̨��ɷ���
  * �������: _ucPort: �˿ں�(COM1 - COM3)
  *           _ucaBuf: �����͵����ݻ�����
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void comSendBuf(COM_PORT_E _ucPort, uint8_t *_ucaBuf, uint16_t _usLen)
{
	USART_FIFO_Typedef *pUsart;

	pUsart = ComToUsart(_ucPort);
	if (pUsart == 0)
	{
		return;
	}
	if (pUsart->SendBefor != 0)
	{
		pUsart->SendBefor();
	}
	UsartSend(pUsart, _ucaBuf, _usLen);
}

/**
  * ��������: �򴮿ڷ���1���ֽڡ����ݷŵ����ͻ��������������أ����жϷ�������ں�̨��ɷ���
  * �������: _ucPort: �˿ں�(COM1 - COM3)
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void comSendChar(COM_PORT_E _ucPort, uint8_t _ucByte)
{
	comSendBuf(_ucPort, &_ucByte, 1);
}

/**
  * ��������: �Ӵ��ڻ�������ȡ1�ֽڣ��������������������ݾ���������
  * �������: _ucPort: �˿ں�(COM1 - COM3)
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
uint8_t comGetChar(COM_PORT_E _ucPort, uint8_t *_pByte)
{
	USART_FIFO_Typedef *pUsart;

	pUsart = ComToUsart(_ucPort);
  __HAL_UART_ENABLE_IT(&husart_debug, USART_IT_RXNE);
	if (pUsart == 0)
	{
		return 0;
	}
	return UsartGetChar(pUsart, _pByte);
}

/**
  * ��������: ���жϷ��������ã�ͨ�ô����жϴ�����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
static void UsartIRQ(USART_FIFO_Typedef *_pUsart)
{
	/* ��������ж�  */
	if (__HAL_USART_GET_IT_SOURCE(&husart_debug, USART_IT_RXNE))
	{
		/* �Ӵ��ڽ������ݼĴ�����ȡ���ݴ�ŵ�����FIFO */
    //HAL_UART_Receive(&husart_debug,&ch,1,0);
		ch=(uint16_t)((_pUsart->usart)->DR & (uint16_t)0x01FF);
		_pUsart->pRxBuf[_pUsart->usRxWrite] = ch;
		if (++_pUsart->usRxWrite >= _pUsart->usRxBufSize)
		{
			_pUsart->usRxWrite = 0;
		}
		if (_pUsart->usRxCount < _pUsart->usRxBufSize)
		{
			_pUsart->usRxCount++;
		}
		/* �ص�����,֪ͨӦ�ó����յ�������,һ���Ƿ���1����Ϣ��������һ����� */
    if (_pUsart->ReciveNew)
    {
      _pUsart->ReciveNew(ch);
    }
	}

	/* �����ͻ��������ж� */
	if (__HAL_UART_GET_IT_SOURCE(&husart_debug, UART_IT_TXE))
	{
		if (_pUsart->usTxCount == 0)
		{
			/* ���ͻ�������������ȡ��ʱ�� ��ֹ���ͻ��������ж� ��ע�⣺��ʱ���1�����ݻ�δ����������ϣ�*/
			__HAL_UART_DISABLE_IT(&husart_debug, UART_IT_TXE);

			/* ʹ�����ݷ�������ж� */
			__HAL_UART_ENABLE_IT(&husart_debug, UART_IT_TC);
		}
		else
		{
			/* �ӷ���FIFOȡ1���ֽ�д�봮�ڷ������ݼĴ��� */
			HAL_UART_Transmit(&husart_debug, &(_pUsart->pTxBuf[_pUsart->usTxRead]),1,0xFFFF);
			if (++_pUsart->usTxRead >= _pUsart->usTxBufSize)
			{
				_pUsart->usTxRead = 0;
			}
			_pUsart->usTxCount--;
		}

	}
	/* ����bitλȫ��������ϵ��ж� */
	else if (__HAL_UART_GET_IT_SOURCE(&husart_debug, UART_IT_TC) != RESET)
	{
		if (_pUsart->usTxCount == 0)
		{
			/* �������FIFO������ȫ��������ϣ���ֹ���ݷ�������ж� */
			__HAL_UART_DISABLE_IT(&husart_debug, UART_IT_TC);

			/* �ص�����, һ����������RS485ͨ�ţ���RS485оƬ����Ϊ����ģʽ��������ռ���� */
			if (_pUsart->SendOver)
			{
				_pUsart->SendOver();
			}
		}
		else
		{
			/* ��������£��������˷�֧ */
			/* �������FIFO�����ݻ�δ��ϣ���ӷ���FIFOȡ1������д�뷢�����ݼĴ��� */
			HAL_UART_Transmit(&husart_debug, &(_pUsart->pTxBuf[_pUsart->usTxRead]),1,0xFFFF);
			if (++_pUsart->usTxRead >= _pUsart->usTxBufSize)
			{
				_pUsart->usTxRead = 0;
			}
			_pUsart->usTxCount--;
		}
	}
}

/**
  * ��������: USART�жϷ������
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
#if USART1_FIFO_EN == 1
void USART1_IRQHandler(void)
{
	UsartIRQ(&g_tUsart1);
}
#endif

#if USART2_FIFO_EN == 1
void USART2_IRQHandler(void)
{
	UsartIRQ(&g_tUsart2);
}
#endif

#if UART5_FIFO_EN == 1
void UART5_IRQHandler(void)
{
	UsartIRQ(&g_tUsart5);
}
#endif

/**
  * ��������: �ض���putc��������������ʹ��printf�����Ӵ���1��ӡ���
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
int fputc(int ch, FILE *f)
{
#if 1	/* ����Ҫprintf���ַ�ͨ�������ж�FIFO���ͳ�ȥ��printf�������������� */
	comSendChar(COM5, ch);
	return ch;
  
#else	/* ����������ʽ����ÿ���ַ�,�ȴ����ݷ������ */
	/* дһ���ֽڵ�USART1 */
	HAL_UART_Transmit(UART5, (uint8_t)ch,1,0xFFFF);

	/* �ȴ����ͽ��� */
	while (__HAL_UART_GET_FLAG(UART5, USART_FLAG_TC) == RESET)
	{}
	return ch;
#endif
}

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
