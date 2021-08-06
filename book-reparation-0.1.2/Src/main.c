/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_steper.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

osThreadId defaultTaskHandle;
osThreadId limitTaskHandle;
osThreadId stepmoveTaskHandle;
osSemaphoreId mySem_moveHandle;
/* USER CODE BEGIN PV */
uint16_t qiegtrace[151][2]={
	 {1432,401},{1432,403},{1432,405},{1432,407},{1431,409},{1431,410},{1431,412},{1430,414},{1429,416},{1429,418},
	 {1428,419},{1427,421},{1426,423},{1425,424},{1424,426},{1423,427},{1422,429},{1421,430},{1420,432},{1418,433},
	 {1417,434},{1416,436},{1414,437},{1413,438},{1411,439},{1410,440},{1408,441},{1406,442},{1404,442},{1403,443},
	 {1401,444},{1399,444},{1397,445},{1395,445},{1394,446},{1392,446},{1390,446},{1388,446},{1386,446},{1384,446},
	 {1382,446},{1380,446},{1379,445},{1377,445},{1375,444},{1373,444},{1371,443},{1370,442},{1368,442},{1366,441},
	 {1365,440},{1363,439},{1361,438},{1360,437},{1358,436},{1357,434},{1356,433},{1354,432},{1353,430},{1352,429},
	 {1351,427},{1350,426},{1349,424},{1348,423},{1347,421},{1346,419},{1345,418},{1345,416},{1344,414},{1343,412},
	 {1343,410},{1343,409},{1342,407},{1342,405},{1342,403},{1342,401},{1342,399},{1342,397},{1342,395},{1343,393},
	 {1343,392},{1343,390},{1344,388},{1345,386},{1345,384},{1346,383},{1347,381},{1348,379},{1349,378},{1350,376},
	 {1351,375},{1352,373},{1353,372},{1354,370},{1356,369},{1357,368},{1358,366},{1360,365},{1361,364},{1363,363},
	 {1365,362},{1366,361},{1368,360},{1370,360},{1371,359},{1373,358},{1375,358},{1377,357},{1379,357},{1380,356},
	 {1382,356},{1384,356},{1386,356},{1388,356},{1390,356},{1392,356},{1394,356},{1395,357},{1397,357},{1399,358},
	 {1401,358},{1403,359},{1404,360},{1406,360},{1408,361},{1410,362},{1411,363},{1413,364},{1414,365},{1416,366},
	 {1417,368},{1418,369},{1420,370},{1421,372},{1422,373},{1423,375},{1424,376},{1425,378},{1426,379},{1427,381},
	 {1428,383},{1429,384},{1429,386},{1430,388},{1431,390},{1431,392},{1431,393},{1432,395},{1432,397},{1432,399},
	 {1432,401}} ;

uint16_t xiftrace[101][2]={
	 {359,746},{359,748},{359,750},{358,752},{358,754},{357,756},{357,758},{356,760},{355,762},{354,764},{353,765},
	 {351,767},{350,769},{349,770},{347,771},{345,773},{344,774},{342,775},{340,776},{338,777},{336,777},{334,778},
	 {332,778},{330,779},{328,779},{326,779},{324,779},{322,779},{320,778},{318,778},{316,777},{314,777},{312,776},
	 {310,775},{308,774},{307,773},{305,771},{303,770},{302,769},{301,767},{299,765},{298,764},{297,762},{296,760},
	 {295,758},{295,756},{294,754},{294,752},{293,750},{293,748},{293,746},{293,744},{293,742},{294,740},{294,738},
	 {295,736},{295,734},{296,732},{297,730},{298,728},{299,727},{301,725},{302,723},{303,722},{305,721},{307,719},
	 {308,718},{310,717},{312,716},{314,715},{316,715},{318,714},{320,714},{322,713},{324,713},{326,713},{328,713},
	 {330,713},{332,714},{334,714},{336,715},{338,715},{340,716},{342,717},{344,718},{345,719},{347,721},{349,722},
	 {350,723},{351,725},{353,727},{354,728},{355,730},{356,732},{357,734},{357,736},{358,738},{358,740},{359,742},
	 {359,744},{359,746}};

extern Stepper_TypeDef stepers[4];
extern uint8_t recieveData[20];
extern uint8_t stopflag;
char *str;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
void StartDefaultTask(void const * argument);
void LimitTask(void const * argument);
void StepmoveTask(void const * argument);

/* USER CODE BEGIN PFP */
void returnOrigin(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static void NVIC_Close_Config()
{
  HAL_NVIC_DisableIRQ(EXTI3_IRQn);

  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}
/**
* @brief  return 0 point
* @param  无          
* @note   return 0 point and set the current coordinates.
* @retval 无
*/
void returnOrigin()
{
	while(stepers[0].stopFlag == 0){
		steperMove045mm(0, 0, 1000);
	}
	stepers[0].distance = 0;
	HAL_UART_Transmit_IT(&huart1, (uint8_t *)"step1 is up\n",13);
	
	stepers[1].stopFlag = 0;
	while(stepers[1].stopFlag == 0){
		steperMove045mm(1, 1, 1000);
	}
  stepers[1].distance = 0;
	HAL_UART_Transmit_IT(&huart1, (uint8_t *)"step2 is up\t\n",13);
	
	steperMove(3, 0, 1000, 10);
	steperMove(2, 0, 1000, 10);
	osDelay(50);
	stepers[2].stopFlag = 0;
	stepers[3].stopFlag = 0;
	while(stepers[2].stopFlag == 0){
		steperMove045mm(2, 1, 1000);
	}
  stepers[2].distance = 954.9;
	HAL_UART_Transmit_IT(&huart1, (uint8_t *)"step3 is up\t\n",13);
	
	while(stepers[3].stopFlag == 0){
		steperMove045mm(3, 1, 1000);
	}
  stepers[3].distance = 31.50;
	HAL_UART_Transmit_IT(&huart1, (uint8_t *)"step4 is up\t\n",13);
/*
   电机方向： 正：0号.1	  1号.0   
*/
	NVIC_Close_Config();
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	delay_init(168);
	HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of mySem_move */
  osSemaphoreDef(mySem_move);
  mySem_moveHandle = osSemaphoreCreate(osSemaphore(mySem_move), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of limitTask */
  osThreadDef(limitTask, LimitTask, osPriorityIdle, 0, 128);
  limitTaskHandle = osThreadCreate(osThread(limitTask), NULL);

  /* definition and creation of stepmoveTask */
  osThreadDef(stepmoveTask, StepmoveTask, osPriorityIdle, 0, 128);
  stepmoveTaskHandle = osThreadCreate(osThread(stepmoveTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LED2_Pin|LED3_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOI, BEEP_Pin|MOTOR_PUL_3_Pin|MOTOR_PUL_0_Pin|MOTOR_PUL_1_Pin
                          |MOTOR_PUL_2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(MOTOR_DIR_2_GPIO_Port, MOTOR_DIR_2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, RELAY_3_Pin|RELAY_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RELAY_1_Pin|RELAY_0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, MOTOR_DIR_1_Pin|MOTOR_DIR_0_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(MOTOR_DIR_3_GPIO_Port, MOTOR_DIR_3_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LED2_Pin LED3_Pin */
  GPIO_InitStruct.Pin = LED2_Pin|LED3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : BEEP_Pin MOTOR_PUL_3_Pin MOTOR_PUL_0_Pin MOTOR_PUL_1_Pin
                           MOTOR_PUL_2_Pin */
  GPIO_InitStruct.Pin = BEEP_Pin|MOTOR_PUL_3_Pin|MOTOR_PUL_0_Pin|MOTOR_PUL_1_Pin
                          |MOTOR_PUL_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pin : MOTOR_DIR_2_Pin */
  GPIO_InitStruct.Pin = MOTOR_DIR_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(MOTOR_DIR_2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RELAY_3_Pin RELAY_2_Pin MOTOR_DIR_3_Pin */
  GPIO_InitStruct.Pin = RELAY_3_Pin|RELAY_2_Pin|MOTOR_DIR_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : RELAY_1_Pin RELAY_0_Pin */
  GPIO_InitStruct.Pin = RELAY_1_Pin|RELAY_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LED1_Pin */
  GPIO_InitStruct.Pin = LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MOTOR_DIR_1_Pin MOTOR_DIR_0_Pin */
  GPIO_InitStruct.Pin = MOTOR_DIR_1_Pin|MOTOR_DIR_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : Limit1_Pin Limit2_Pin */
  GPIO_InitStruct.Pin = Limit1_Pin|Limit2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : Limit3_Pin */
  GPIO_InitStruct.Pin = Limit3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Limit3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Limit4_Pin */
  GPIO_InitStruct.Pin = Limit4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Limit4_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI3_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
	HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, GPIO_PIN_RESET); // 吹气 气泵
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);	
	
	osDelay(1000);
	HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);
	osDelay(200);
	HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
	osDelay(200);
	
	returnOrigin();
	
	HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, GPIO_PIN_RESET); // 吹气 气泵
  /* Infinite loop */
  for(;;)
  {
		// HAL_UART_Transmit_IT(&huart2, (uint8_t *)"1,0,40", 7);
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
    osDelay(4000);
		// HAL_UART_Transmit_IT(&huart2, (uint8_t *)"1,1,40", 7);
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
		osDelay(4000);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_LimitTask */
/**
* @brief Function implementing the limitTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LimitTask */
void LimitTask(void const * argument)
{
  /* USER CODE BEGIN LimitTask */
  /* Infinite loop */
  for(;;)
  {
		osDelay(10);
  }
  /* USER CODE END LimitTask */
}

/* USER CODE BEGIN Header_StepmoveTask */
/**
* @brief Function implementing the stepmoveTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StepmoveTask */
void StepmoveTask(void const * argument)
{
  /* USER CODE BEGIN StepmoveTask */
  /* Infinite loop */
  for(;;)
  {
    xSemaphoreTake(mySem_moveHandle, portMAX_DELAY); 
//    HAL_UART_Transmit_IT(&huart1, (uint8_t *)"Recieve OK!\r\n",13);
    str = pvPortMalloc(48);
    if(recieveData[0] == 0x01){
      uint8_t motor = recieveData[1];
      uint8_t dir = recieveData[2];
      uint16_t pul = recieveData[3] << 8 | recieveData[4];
      steperMovePul(motor, dir, 1000, pul);
			
			sprintf(str, "motor[%d]:dis=[%0.3f]\r\n", motor, stepers[motor].distance);
			HAL_UART_Transmit_IT(&huart1, (uint8_t *)str, 48);
			
    }else if(recieveData[0] == 0x02){
			uint8_t model = recieveData[1];
			uint16_t x = recieveData[2] << 8 | recieveData[3];
			uint16_t y = recieveData[4] << 8 | recieveData[5];

			model == 0x00 ?	steperCoordinateMajorPul(x, y, 1000):steperCoordinateSecondPul(x, y, 1000);
			model == 0x00 ?	sprintf(str, "X1=[%0.3f] Y2=[%0.3f]\r\n", stepers[0].distance, stepers[1].distance) 
										: sprintf(str, "X3=[%0.3f] Y4=[%0.3f]\r\n", stepers[2].distance, stepers[3].distance);
      HAL_UART_Transmit_IT(&huart1, (uint8_t *)str, 48);
			
		}else if(recieveData[0] == 0x03){
			int state = recieveData[1];
			HAL_GPIO_WritePin(RELAY_3_GPIO_Port, RELAY_3_Pin, (GPIO_PinState)state); // 激光
		
		}else if(recieveData[0] == 0x04){
			sprintf(str, "[%0.3f,%0.3f,%0.3f,%0.3f]\r\n", stepers[0].distance, stepers[1].distance, stepers[2].distance, stepers[3].distance);
			HAL_UART_Transmit_IT(&huart1, (uint8_t *)str, 48);
			
		}
    
    vPortFree(str);
    osDelay(10);
  }
  /* USER CODE END StepmoveTask */
}

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
