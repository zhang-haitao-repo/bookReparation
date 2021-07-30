 /**
  ******************************************************************************
  * �ļ�����: main.c 
  * ��    ��: ӲʯǶ��ʽ�����Ŷ�
  * ��    ��: V1.0
  * ��д����: 2017-3-30
  * ��    ��: FreeRTOS+RS232
  ******************************************************************************
  * ˵����
  * ����������Ӳʯstm32������YS-F4Proʹ�á�
  * 
  * �Ա���
  * ��̳��http://www.ing10bbs.com
  * ��Ȩ��ӲʯǶ��ʽ�����Ŷ����У��������á�
  ******************************************************************************
  */
/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "led/bsp_led.h"
#include "BasicTIM/bsp_BasicTIM.h" 
#include "usart/bsp_usartx_fifo.h"
#include "key/bsp_key.h"

/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
/* ˽�б��� ------------------------------------------------------------------*/
static TaskHandle_t xHandleTaskUserIF = NULL;
static TaskHandle_t xHandleTaskLED1 = NULL;

KEY key1,key2,key3,key4,key5;

/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
static void vTaskTaskUserIF(void *pvParameters);
static void vTaskLED1(void *pvParameters);
static void AppTaskCreate (void);
static void COMProcessHelp(void);

/* ������ --------------------------------------------------------------------*/
/**
  * ��������: ϵͳʱ������
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
 
  __HAL_RCC_PWR_CLK_ENABLE();                                     //ʹ��PWRʱ��

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);  //���õ�ѹ�������ѹ����1

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;      // �ⲿ����8MHz
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;                        //��HSE 
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;                    //��PLL
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;            //PLLʱ��Դѡ��HSE
  RCC_OscInitStruct.PLL.PLLM = 8;                                 //8��ƵMHz
  RCC_OscInitStruct.PLL.PLLN = 336;                               //336��Ƶ
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;                     //2��Ƶ���õ�168MHz��ʱ��
  RCC_OscInitStruct.PLL.PLLQ = 7;                                 //USB/SDIO/������������ȵ���PLL��Ƶϵ��
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;       // ϵͳʱ�ӣ�168MHz
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;              // AHBʱ�ӣ� 168MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;               // APB1ʱ�ӣ�42MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;               // APB2ʱ�ӣ�84MHz
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  HAL_RCC_EnableCSS();                                            // ʹ��CSS���ܣ�����ʹ���ⲿ�����ڲ�ʱ��ԴΪ����
  
 	// HAL_RCC_GetHCLKFreq()/1000    1ms�ж�һ��
	// HAL_RCC_GetHCLKFreq()/100000	 10us�ж�һ��
	// HAL_RCC_GetHCLKFreq()/1000000 1us�ж�һ��
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);                // ���ò�����ϵͳ�δ�ʱ��
  /* ϵͳ�δ�ʱ��ʱ��Դ */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* ϵͳ�δ�ʱ���ж����ȼ����� */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

/**
  * ��������: ������.
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
int main(void)
{
  
  /* ��λ�������裬��ʼ��Flash�ӿں�ϵͳ�δ�ʱ�� */
  HAL_Init();
  /* ����ϵͳʱ�� */
  SystemClock_Config();
  
  Usart_FIFO_Init();

  /* ��ʼ��LED */
  LED_GPIO_Init();
  /* ���Ӱ�����ʼ�� */
  KEY_GPIO_Init();
  /* ������ʱ����ʼ����100us�ж�һ�� */
  BASIC_TIMx_Init();
	/* �������� */
	AppTaskCreate();

  /* �������ȣ���ʼִ������ */
  vTaskStartScheduler();
  
  /* ����ѭ�� */
  while (1)
  {
  }
}

/**
  * ��������: �ӿ���Ϣ����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
static void vTaskTaskUserIF(void *pvParameters)
{
  uint8_t pcWriteBuffer[500];
    /* �������� */
  KeyCreate(&key1,GetPinStateOfKey1);
  KeyCreate(&key2,GetPinStateOfKey2);
  printf("����KEY1��KEY2ִ�в�ͬ������\n");

    while(1)
    {
      Key_RefreshState(&key1);//ˢ�°���״̬
      Key_RefreshState(&key2);//ˢ�°���״̬
                  
      if(Key_AccessTimes(&key1,KEY_ACCESS_READ)!=0)//���������¹�
      {
        printf("=================================================\r\n");
        printf("������      ����״̬ ���ȼ�   ʣ��ջ �������\r\n");
        vTaskList((char *)&pcWriteBuffer);
        printf("%s\r\n", pcWriteBuffer);
       
        printf("\r\n������       ���м���         ʹ����\r\n");
        vTaskGetRunTimeStats((char *)&pcWriteBuffer);
        printf("%s\r\n", pcWriteBuffer);        
        Key_AccessTimes(&key1,KEY_ACCESS_WRITE_CLEAR);
      }
      
      if(Key_AccessTimes(&key2,KEY_ACCESS_READ)!=0)//���������¹�
      { 
        COMProcessHelp();
        Key_AccessTimes(&key2,KEY_ACCESS_WRITE_CLEAR);
      }             
     vTaskDelay(20);
  }
		
}

/**
  * ��������: LED1����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
static void vTaskLED1(void *pvParameters)
{
  uint8_t ucCMD;
	char buf[64];

	/* ��ӡ�������������ʾ */
	COMProcessHelp();
	
  while(1)
  {
    if (comGetChar(COM5, &ucCMD))
    {
      switch (ucCMD)
      {
        case '1':
          sprintf(buf, "���յ���������1\r\n");      
          comSendBuf(COM5, (uint8_t *)buf, strlen(buf));     
          break;

        case '2':
          sprintf(buf, "���յ���������2\r\n");
          comSendBuf(COM5, (uint8_t *)buf, strlen(buf));
          break;

        case '3':
          sprintf(buf, "���յ���������3\r\n");
          comSendBuf(COM5, (uint8_t *)buf, strlen(buf));
          break;

        case '4':
          sprintf(buf, "���յ���������4\r\n");
          comSendBuf(COM5, (uint8_t *)buf, strlen(buf));
          break;	
      }    
    } 
  vTaskDelay(20);
  }
}

/**
  * ��������: ��������Ӧ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
static void AppTaskCreate (void)
{

    xTaskCreate( vTaskTaskUserIF,   	/* ������  */
                 "vTaskUserIF",     	/* ������    */
                 512,               	/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,              	/* �������  */
                 1,                 	/* �������ȼ�*/
                 &xHandleTaskUserIF );  /* ������  */
	
    xTaskCreate( vTaskLED1,   	      /* ������  */
                 "vTaskLED1",     	  /* ������    */
                 512,               	/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,              	/* �������  */
                 2,                 	/* �������ȼ�*/
                 &xHandleTaskLED1 );  /* ������  */
	
	
}

static void COMProcessHelp(void)
{
	printf("==========================================\r\n");
	printf("��ѡ�񴮿ڲ���������Լ��̴�ӡ���ּ���:\r\n");
	printf("1. ���յ�����1����ӡ��Ϣ\r\n");
	printf("2. ���յ�����2����ӡ��Ϣ\r\n");
	printf("3. ���յ�����3����ӡ��Ϣ\r\n");
	printf("4. ���յ�����4����ӡ��Ϣ\r\n");
}

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/

