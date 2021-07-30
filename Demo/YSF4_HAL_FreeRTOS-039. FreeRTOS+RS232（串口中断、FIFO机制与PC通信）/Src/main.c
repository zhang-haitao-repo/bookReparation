 /**
  ******************************************************************************
  * 文件名程: main.c 
  * 作    者: 硬石嵌入式开发团队
  * 版    本: V1.0
  * 编写日期: 2017-3-30
  * 功    能: FreeRTOS+RS232
  ******************************************************************************
  * 说明：
  * 本例程配套硬石stm32开发板YS-F4Pro使用。
  * 
  * 淘宝：
  * 论坛：http://www.ing10bbs.com
  * 版权归硬石嵌入式开发团队所有，请勿商用。
  ******************************************************************************
  */
/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "led/bsp_led.h"
#include "BasicTIM/bsp_BasicTIM.h" 
#include "usart/bsp_usartx_fifo.h"
#include "key/bsp_key.h"

/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
static TaskHandle_t xHandleTaskUserIF = NULL;
static TaskHandle_t xHandleTaskLED1 = NULL;

KEY key1,key2,key3,key4,key5;

/* 扩展变量 ------------------------------------------------------------------*/
/* 私有函数原形 --------------------------------------------------------------*/
static void vTaskTaskUserIF(void *pvParameters);
static void vTaskLED1(void *pvParameters);
static void AppTaskCreate (void);
static void COMProcessHelp(void);

/* 函数体 --------------------------------------------------------------------*/
/**
  * 函数功能: 系统时钟配置
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
 
  __HAL_RCC_PWR_CLK_ENABLE();                                     //使能PWR时钟

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);  //设置调压器输出电压级别1

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;      // 外部晶振，8MHz
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;                        //打开HSE 
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;                    //打开PLL
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;            //PLL时钟源选择HSE
  RCC_OscInitStruct.PLL.PLLM = 8;                                 //8分频MHz
  RCC_OscInitStruct.PLL.PLLN = 336;                               //336倍频
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;                     //2分频，得到168MHz主时钟
  RCC_OscInitStruct.PLL.PLLQ = 7;                                 //USB/SDIO/随机数产生器等的主PLL分频系数
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;       // 系统时钟：168MHz
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;              // AHB时钟： 168MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;               // APB1时钟：42MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;               // APB2时钟：84MHz
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  HAL_RCC_EnableCSS();                                            // 使能CSS功能，优先使用外部晶振，内部时钟源为备用
  
 	// HAL_RCC_GetHCLKFreq()/1000    1ms中断一次
	// HAL_RCC_GetHCLKFreq()/100000	 10us中断一次
	// HAL_RCC_GetHCLKFreq()/1000000 1us中断一次
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);                // 配置并启动系统滴答定时器
  /* 系统滴答定时器时钟源 */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* 系统滴答定时器中断优先级配置 */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

/**
  * 函数功能: 主函数.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
int main(void)
{
  
  /* 复位所有外设，初始化Flash接口和系统滴答定时器 */
  HAL_Init();
  /* 配置系统时钟 */
  SystemClock_Config();
  
  Usart_FIFO_Init();

  /* 初始化LED */
  LED_GPIO_Init();
  /* 板子按键初始化 */
  KEY_GPIO_Init();
  /* 基本定时器初始化：100us中断一次 */
  BASIC_TIMx_Init();
	/* 创建任务 */
	AppTaskCreate();

  /* 启动调度，开始执行任务 */
  vTaskStartScheduler();
  
  /* 无限循环 */
  while (1)
  {
  }
}

/**
  * 函数功能: 接口消息处理
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
static void vTaskTaskUserIF(void *pvParameters)
{
  uint8_t pcWriteBuffer[500];
    /* 创建按键 */
  KeyCreate(&key1,GetPinStateOfKey1);
  KeyCreate(&key2,GetPinStateOfKey2);
  printf("按下KEY1、KEY2执行不同的任务\n");

    while(1)
    {
      Key_RefreshState(&key1);//刷新按键状态
      Key_RefreshState(&key2);//刷新按键状态
                  
      if(Key_AccessTimes(&key1,KEY_ACCESS_READ)!=0)//按键被按下过
      {
        printf("=================================================\r\n");
        printf("任务名      任务状态 优先级   剩余栈 任务序号\r\n");
        vTaskList((char *)&pcWriteBuffer);
        printf("%s\r\n", pcWriteBuffer);
       
        printf("\r\n任务名       运行计数         使用率\r\n");
        vTaskGetRunTimeStats((char *)&pcWriteBuffer);
        printf("%s\r\n", pcWriteBuffer);        
        Key_AccessTimes(&key1,KEY_ACCESS_WRITE_CLEAR);
      }
      
      if(Key_AccessTimes(&key2,KEY_ACCESS_READ)!=0)//按键被按下过
      { 
        COMProcessHelp();
        Key_AccessTimes(&key2,KEY_ACCESS_WRITE_CLEAR);
      }             
     vTaskDelay(20);
  }
		
}

/**
  * 函数功能: LED1任务
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
static void vTaskLED1(void *pvParameters)
{
  uint8_t ucCMD;
	char buf[64];

	/* 打印串口命令操作提示 */
	COMProcessHelp();
	
  while(1)
  {
    if (comGetChar(COM5, &ucCMD))
    {
      switch (ucCMD)
      {
        case '1':
          sprintf(buf, "接收到串口命令1\r\n");      
          comSendBuf(COM5, (uint8_t *)buf, strlen(buf));     
          break;

        case '2':
          sprintf(buf, "接收到串口命令2\r\n");
          comSendBuf(COM5, (uint8_t *)buf, strlen(buf));
          break;

        case '3':
          sprintf(buf, "接收到串口命令3\r\n");
          comSendBuf(COM5, (uint8_t *)buf, strlen(buf));
          break;

        case '4':
          sprintf(buf, "接收到串口命令4\r\n");
          comSendBuf(COM5, (uint8_t *)buf, strlen(buf));
          break;	
      }    
    } 
  vTaskDelay(20);
  }
}

/**
  * 函数功能: 创建任务应用
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
static void AppTaskCreate (void)
{

    xTaskCreate( vTaskTaskUserIF,   	/* 任务函数  */
                 "vTaskUserIF",     	/* 任务名    */
                 512,               	/* 任务栈大小，单位word，也就是4字节 */
                 NULL,              	/* 任务参数  */
                 1,                 	/* 任务优先级*/
                 &xHandleTaskUserIF );  /* 任务句柄  */
	
    xTaskCreate( vTaskLED1,   	      /* 任务函数  */
                 "vTaskLED1",     	  /* 任务名    */
                 512,               	/* 任务栈大小，单位word，也就是4字节 */
                 NULL,              	/* 任务参数  */
                 2,                 	/* 任务优先级*/
                 &xHandleTaskLED1 );  /* 任务句柄  */
	
	
}

static void COMProcessHelp(void)
{
	printf("==========================================\r\n");
	printf("请选择串口操作命令，电脑键盘打印数字即可:\r\n");
	printf("1. 接收到命令1，打印消息\r\n");
	printf("2. 接收到命令2，打印消息\r\n");
	printf("3. 接收到命令3，打印消息\r\n");
	printf("4. 接收到命令4，打印消息\r\n");
}

/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/

