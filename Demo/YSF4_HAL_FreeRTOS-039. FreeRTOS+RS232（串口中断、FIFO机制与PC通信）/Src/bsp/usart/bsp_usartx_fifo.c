/**
  ******************************************************************************
  * 文件名程: bsp_debug_usart.c 
  * 作    者: 硬石嵌入式开发团队
  * 版    本: V1.0
  * 编写日期: 2015-10-04
  * 功    能: 板载调试串口底层驱动程序：默认使用USART1
  ******************************************************************************
  * 说明：
  * 本例程配套硬石stm32开发板YS-F1Pro使用。
  * 
  * 淘宝：
  * 论坛：http://www.ing10bbs.com
  * 版权归硬石嵌入式开发团队所有，请勿商用。
  ******************************************************************************
  */

/* 包含头文件 ----------------------------------------------------------------*/
#include "usart/bsp_usartx_fifo.h"

/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
UART_HandleTypeDef husart_debug;
uint8_t ch;

/* 定义每个串口结构体变量 */
#if USART1_FIFO_EN == 1
	static USART_FIFO_Typedef g_tUsart1;
	static uint8_t g_TxBuf1[USART1_TX_BUF_SIZE];		/* 发送缓冲区 */
	static uint8_t g_RxBuf1[USART1_RX_BUF_SIZE];		/* 接收缓冲区 */
#endif

#if USART2_FIFO_EN == 1
	static USART_FIFO_Typedef g_tUsart2;
	static uint8_t g_TxBuf2[USART2_TX_BUF_SIZE];		/* 发送缓冲区 */
	static uint8_t g_RxBuf2[USART2_RX_BUF_SIZE];		/* 接收缓冲区 */
#endif

#if UART5_FIFO_EN == 1
	static USART_FIFO_Typedef g_tUsart5;
	static uint8_t g_TxBuf3[UART5_TX_BUF_SIZE];		/* 发送缓冲区 */
	static uint8_t g_RxBuf3[UART5_RX_BUF_SIZE];		/* 接收缓冲区 */
#endif

/* 扩展变量 ------------------------------------------------------------------*/
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/
static void UsartVarInit(void)
{
#if USART1_FIFO_EN == 1
	g_tUsart1.usart = USART1;						        /* STM32 串口设备 */
	g_tUsart1.pTxBuf = g_TxBuf1;					        /* 发送缓冲区指针 */
	g_tUsart1.pRxBuf = g_RxBuf1;					        /* 接收缓冲区指针 */
	g_tUsart1.usTxBufSize = USART1_TX_BUF_SIZE;	/* 发送缓冲区大小 */
	g_tUsart1.usRxBufSize = USART1_RX_BUF_SIZE;	/* 接收缓冲区大小 */
	g_tUsart1.usTxWrite = 0;			          			/* 发送FIFO写索引 */
	g_tUsart1.usTxRead = 0;						          /* 发送FIFO读索引 */
	g_tUsart1.usRxWrite = 0;						          /* 接收FIFO写索引 */
	g_tUsart1.usRxRead = 0;						          /* 接收FIFO读索引 */
	g_tUsart1.usRxCount = 0;						          /* 接收到的新数据个数 */
	g_tUsart1.usTxCount = 0;						          /* 待发送的数据个数 */
	g_tUsart1.SendBefor = 0;						          /* 发送数据前的回调函数 */
	g_tUsart1.SendOver = 0;						          /* 发送完毕后的回调函数 */
	g_tUsart1.ReciveNew = 0;						          /* 接收到新数据后的回调函数 */
#endif

#if USART2_FIFO_EN == 1
	g_tUsart2.usart = USART2;						        /* STM32 串口设备 */
	g_tUsart2.pTxBuf = g_TxBuf2;					        /* 发送缓冲区指针 */
	g_tUsart2.pRxBuf = g_RxBuf2;					        /* 接收缓冲区指针 */
	g_tUsart2.usTxBufSize = USART2_TX_BUF_SIZE;	/* 发送缓冲区大小 */
	g_tUsart2.usRxBufSize = USART2_RX_BUF_SIZE;	/* 接收缓冲区大小 */
	g_tUsart2.usTxWrite = 0;			          			/* 发送FIFO写索引 */
	g_tUsart2.usTxRead = 0;						          /* 发送FIFO读索引 */
	g_tUsart2.usRxWrite = 0;						          /* 接收FIFO写索引 */
	g_tUsart2.usRxRead = 0;						          /* 接收FIFO读索引 */
	g_tUsart2.usRxCount = 0;						          /* 接收到的新数据个数 */
	g_tUsart2.usTxCount = 0;						          /* 待发送的数据个数 */
	g_tUsart2.SendBefor = 0;						          /* 发送数据前的回调函数 */
	g_tUsart2.SendOver = 0;						          /* 发送完毕后的回调函数 */
	g_tUsart2.ReciveNew = 0;						          /* 接收到新数据后的回调函数 */
#endif

#if UART5_FIFO_EN == 1
	g_tUsart5.usart = UART5;						        /* STM32 串口设备 */
	g_tUsart5.pTxBuf = g_TxBuf3;					        /* 发送缓冲区指针 */
	g_tUsart5.pRxBuf = g_RxBuf3;					        /* 接收缓冲区指针 */
	g_tUsart5.usTxBufSize = UART5_TX_BUF_SIZE;	/* 发送缓冲区大小 */
	g_tUsart5.usRxBufSize = UART5_RX_BUF_SIZE;	/* 接收缓冲区大小 */
	g_tUsart5.usTxWrite = 0;			          			/* 发送FIFO写索引 */
	g_tUsart5.usTxRead = 0;						          /* 发送FIFO读索引 */
	g_tUsart5.usRxWrite = 0;						          /* 接收FIFO写索引 */
	g_tUsart5.usRxRead = 0;						          /* 接收FIFO读索引 */
	g_tUsart5.usRxCount = 0;						          /* 接收到的新数据个数 */
	g_tUsart5.usTxCount = 0;						          /* 待发送的数据个数 */
	g_tUsart5.SendBefor = 0;						          /* 发送数据前的回调函数 */
	g_tUsart5.SendOver = 0;						          /* 发送完毕后的回调函数 */
	g_tUsart5.ReciveNew = 0;						          /* 接收到新数据后的回调函数 */
#endif
}

/**
  * 函数功能: 串口硬件初始化配置
  * 输入参数: huart：串口句柄类型指针
  * 返 回 值: 无
  * 说    明: 该函数被HAL库内部调用
  */
static void InitHardUsart(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  
#if USART1_FIFO_EN == 1		/* 串口1 TX = PA9   RX = PA10 */
    /* 串口外设时钟使能 */
    __HAL_RCC_USART1_CLK_ENABLE();
    /* 使能串口功能引脚GPIO时钟 */
    __HAL_RCC_GPIOB_CLK_ENABLE();  
    /* 串口外设功能GPIO配置 */
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
  
#if USART2_FIFO_EN == 1		/* 串口2 TX = PA2， RX = PA3  */
    /* 串口外设时钟使能 */
    __HAL_RCC_USART2_CLK_ENABLE();
    /* 使能串口功能引脚GPIO时钟 */
    __HAL_RCC_GPIOD_CLK_ENABLE();  
    /* 串口外设功能GPIO配置 */
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

#if UART5_FIFO_EN == 1			/* 串口5 TX = PB10   RX = PB11 */
    /* 串口外设时钟使能 */
    __HAL_RCC_UART5_CLK_ENABLE();
    /* 使能串口功能引脚GPIO时钟 */
    __HAL_RCC_GPIOC_CLK_ENABLE();  
    __HAL_RCC_GPIOD_CLK_ENABLE();  
    /* 串口外设功能GPIO配置 */
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
  * 函数功能: 串口参数配置.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void Usart_FIFO_Init(void)
{  
    /* 初始化串口相关的变量 */
  InitHardUsart();
  UsartVarInit();
}

/**
  * 函数功能: 将COM端口号转换为UART指针
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
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
		/* 不做任何处理 */
		return 0;
	}
}

/**
  * 函数功能: 从串口接收缓冲区读取1字节数据 （用于主程序调用）
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
static uint8_t UsartGetChar(USART_FIFO_Typedef *_pUsart, uint8_t *_pByte)
{
	uint16_t usCount;

	/* usRxWrite 变量在中断函数中被改写，主程序读取该变量时，必须进行临界区保护 */
	DISABLE_INT();
	usCount = _pUsart->usRxCount;
	ENABLE_INT();

	if (usCount == 0)	/* 已经没有数据 */
	{
		return 0;
	}
	else
	{
		*_pByte = _pUsart->pRxBuf[_pUsart->usRxRead];		/* 从串口接收FIFO取1个数据 */
    
		/* 改写FIFO读索引 */
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
  * 函数功能: 填写数据到UART发送缓冲区,并启动发送中断。中断处理函数发送完毕后，自动关闭发送中断
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
static void UsartSend(USART_FIFO_Typedef *_pUsart, uint8_t *_ucaBuf, uint16_t _usLen)
{
	uint16_t i;

	for (i = 0; i < _usLen; i++)
	{
		/* 如果发送缓冲区已经满了，则等待缓冲区空 */
		/* 当 _pUsart->usTxBufSize == 1 时, 下面的函数会死掉(待完善) */
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
		/* 将新数据填入发送缓冲区 */
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
  * 函数功能: 向串口发送一组数据。数据放到发送缓冲区后立即返回，由中断服务程序在后台完成发送
  * 输入参数: _ucPort: 端口号(COM1 - COM3)
  *           _ucaBuf: 待发送的数据缓冲区
  * 返 回 值: 无
  * 说    明: 无
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
  * 函数功能: 向串口发送1个字节。数据放到发送缓冲区后立即返回，由中断服务程序在后台完成发送
  * 输入参数: _ucPort: 端口号(COM1 - COM3)
  * 返 回 值: 无
  * 说    明: 无
  */
void comSendChar(COM_PORT_E _ucPort, uint8_t _ucByte)
{
	comSendBuf(_ucPort, &_ucByte, 1);
}

/**
  * 函数功能: 从串口缓冲区读取1字节，非阻塞。无论有无数据均立即返回
  * 输入参数: _ucPort: 端口号(COM1 - COM3)
  * 返 回 值: 无
  * 说    明: 无
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
  * 函数功能: 供中断服务程序调用，通用串口中断处理函数
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
static void UsartIRQ(USART_FIFO_Typedef *_pUsart)
{
	/* 处理接收中断  */
	if (__HAL_USART_GET_IT_SOURCE(&husart_debug, USART_IT_RXNE))
	{
		/* 从串口接收数据寄存器读取数据存放到接收FIFO */
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
		/* 回调函数,通知应用程序收到新数据,一般是发送1个消息或者设置一个标记 */
    if (_pUsart->ReciveNew)
    {
      _pUsart->ReciveNew(ch);
    }
	}

	/* 处理发送缓冲区空中断 */
	if (__HAL_UART_GET_IT_SOURCE(&husart_debug, UART_IT_TXE))
	{
		if (_pUsart->usTxCount == 0)
		{
			/* 发送缓冲区的数据已取完时， 禁止发送缓冲区空中断 （注意：此时最后1个数据还未真正发送完毕）*/
			__HAL_UART_DISABLE_IT(&husart_debug, UART_IT_TXE);

			/* 使能数据发送完毕中断 */
			__HAL_UART_ENABLE_IT(&husart_debug, UART_IT_TC);
		}
		else
		{
			/* 从发送FIFO取1个字节写入串口发送数据寄存器 */
			HAL_UART_Transmit(&husart_debug, &(_pUsart->pTxBuf[_pUsart->usTxRead]),1,0xFFFF);
			if (++_pUsart->usTxRead >= _pUsart->usTxBufSize)
			{
				_pUsart->usTxRead = 0;
			}
			_pUsart->usTxCount--;
		}

	}
	/* 数据bit位全部发送完毕的中断 */
	else if (__HAL_UART_GET_IT_SOURCE(&husart_debug, UART_IT_TC) != RESET)
	{
		if (_pUsart->usTxCount == 0)
		{
			/* 如果发送FIFO的数据全部发送完毕，禁止数据发送完毕中断 */
			__HAL_UART_DISABLE_IT(&husart_debug, UART_IT_TC);

			/* 回调函数, 一般用来处理RS485通信，将RS485芯片设置为接收模式，避免抢占总线 */
			if (_pUsart->SendOver)
			{
				_pUsart->SendOver();
			}
		}
		else
		{
			/* 正常情况下，不会进入此分支 */
			/* 如果发送FIFO的数据还未完毕，则从发送FIFO取1个数据写入发送数据寄存器 */
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
  * 函数功能: USART中断服务程序
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
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
  * 函数功能: 重定义putc函数，这样可以使用printf函数从串口1打印输出
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
int fputc(int ch, FILE *f)
{
#if 1	/* 将需要printf的字符通过串口中断FIFO发送出去，printf函数会立即返回 */
	comSendChar(COM5, ch);
	return ch;
  
#else	/* 采用阻塞方式发送每个字符,等待数据发送完毕 */
	/* 写一个字节到USART1 */
	HAL_UART_Transmit(UART5, (uint8_t)ch,1,0xFFFF);

	/* 等待发送结束 */
	while (__HAL_UART_GET_FLAG(UART5, USART_FLAG_TC) == RESET)
	{}
	return ch;
#endif
}

/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/
