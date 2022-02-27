/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LED0_ON() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, HIGH);
#define LED0_Off() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, LOW);
#define LED0_TOG() HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
#define LED1_ON() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, HIGH);
#define LED1_Off() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, LOW);
#define LED1_TOG() HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
struct BCU_HCU_INFO{
	uint8_t BatVoltage_MSB;
	uint8_t BatVoltage_LSB;
	uint16_t BatVoltage; //动力电池总电压
	uint8_t BatCurrent_MSB;
	uint8_t BatCurrent_LSB;
	uint16_t BatCurrent; //动力电池总电流
	uint8_t BatSoc; //动力电池SOC
	uint8_t BatSoh; //动力电池COH
	uint8_t BatState; /*动力电池状态
						1:Sleep (休眠)
						2:Power Up (自检状态)
						3:Standby (待机状态)
						4:Pre-charge (预充状态)
						5:Run (正常运行状态)
						6:Shutdown (关机状态)
						7:Error (故障状态)*/
	uint8_t BatAlmLv; /*0:无告警
						1:一级告警 (最严重)
						2:二级告警
						3:三级告警
						4:四级告警*/
	uint8_t BatLife; //通信生命信息 循环递增 (0 - 255)
};
struct BMS_HCU_MAXV{
	uint8_t MaxCellVolt_MSB;
	uint8_t MaxCellVolt_LSB;
	uint16_t MaxCellVolt; //最高单体电压
	uint8_t MinCellVolt_MSB;
	uint8_t MinCellVolt_LSB;
	uint16_t MinCellVolt; //最低单体电压
	uint8_t MaxCellVoltNo; //最高单体电压序号
	uint8_t MinCellVoltNo; //最低单体电压序号
};
struct BMS_HCU_MAXT{
	uint8_t MaxTemp; //最高温度
	uint8_t MinTemp; //最低温度
	uint8_t MaxTempNo; //最高温度序号
	uint8_t MinTempNo; //最低温度序号
	uint8_t CoolingCtl; //冷却控制, 0 停止, 1 启动
	uint8_t HeatingCtl; //发热控制, 0 停止, 1 启动
};
struct BMS_HCU_RELAY{
	uint8_t PosRlyStr; /*	总正继电器状态
							0:Open
							1:Close
							2:Error */
	uint8_t NegRlyStr; /*	总负继电器状态
							0:Open
							1:Close
							2:Error */
	uint8_t PreRlyStr; /*	预充继电器状态
							0:Open
							1:Close
							2:Error */
	uint8_t OnChrRlyStr; /*	车载充电（慢充）继电器状态
							0:Open
							1:Close
							2:Error */
	uint8_t OffChrRlyStr; /*非车载充电（快充）继电器状态
							0:Open
							1:Close
							2:Error */
	uint8_t ChrState; /*	充电状态
							0:停止充电
							1:进入充电
							2:恒流充电
							3:涓充充电
							4:充电完成 */
	uint8_t ChrCommunication; /*	充电机是否在线
									0：通信超时
									1：在线 */
	uint8_t ChrOFFCC2; /*	非车载充电机连接确认
							0：未连接
							1：已连接 */
	uint8_t ChrONCC; /*	车载充电机连接确认
						0: 未连接
						1: 220Ω
						2: 680Ω
						3: 未知 */
	uint8_t ChrReqVolt_MSB; //
	uint8_t ChrReqVolt_LSB; //
	uint16_t ChrReqVolt; //	充电请求电压
	uint8_t ChrReqCurr_MSB;
	uint8_t ChrReqCurr_LSB;
	uint16_t ChrReqCurr; // 充电请求电流
};
struct BMS_HCU_POWER{
	uint8_t MaxChrCurtLimit_MSB;
	uint8_t MaxChrCurtLimit_LSB;
	uint16_t MaxChrCurtLimit; //当前最大允许充电电流
	uint8_t MaxDisCurtLimit_MSB;
	uint8_t MaxDisCurtLimit_LSB;
	uint16_t MaxDisCurtLimit; //当前最大允许放电电流
	uint8_t MaxChrPowerLimit_MSB;
	uint8_t MaxChrPowerLimit_LSB;
	uint16_t MaxChrPowerLimit; //当前最大允许充电功率
	uint8_t MaxDisPowerLimit_MSB;
	uint8_t MaxDisPowerLimit_LSB;
	uint16_t MaxDisPowerLimit; //当前最大允许放电功率
};
struct BMS_HCU_ALARM{
	uint8_t ALM_CELL_OV; /*	单体过压
							0:无告警
							1:1级告警（最严重）
							2:2级告警
							3:3级告警
							4:4级告警 */
	uint8_t ALM_CELL_UV; /*	单体欠压
							0:无告警
							1:1级告警（最严重）
							2:2级告警
							3:3级告警
							4:4级告警 */
	uint8_t ALM_CELL_OT; /*	电池高温
							0:无告警
							1:1级告警（最严重）
							2:2级告警
							3:3级告警
							4:4级告警 */
	uint8_t ALM_CELL_UT; /*	电池低温
							0:无告警
							1:1级告警（最严重）
							2:2级告警
							3:3级告警
							4:4级告警 */
	uint8_t ALM_CELL_LBK; /*单体电压断线
							0:无告警
							1:1级告警 */
	uint8_t ALM_CELL_TBK; /*单体温度断线
							0:无告警
							1:1级告警 */
	uint8_t ALM_BATT_DV; /*	单体压差过大
							0:无告警
							1:1级告警（最严重）
							2:2级告警
							3:3级告警
							4:4级告警 */
	uint8_t ALM_BATT_DT; /*	电池温差过大
							0:无告警
							1:1级告警（最严重）
							2:2级告警
							3:3级告警
							4:4级告警 */
	uint8_t ALM_BATT_OV; //	整组过压
	uint8_t ALM_BATT_UV; //	整组欠压
	uint8_t ALM_BATT_OC; //	电池组SOC过高
	uint8_t ALM_BATT_UC; //	电池组SOC过低
	uint8_t ALM_CHRG_OCS; //稳态充电过流
	uint8_t ALM_DSCH_OCS; //稳态放电过流
	uint8_t ALM_CHRG_OCT; //瞬态充电过流
	uint8_t ALM_DSCH_OCT; //瞬态放电过流
	uint8_t ALM_BSU_OFFLINE; //	BSU离线
	uint8_t ALM_BSU_FAULT; /*	BSU均衡故障
								0:无告警
								1:1级告警 */
	uint8_t ALM_LEAK_OC; /*	漏电流超限
							0:无告警
							1:1级告警（最严重）
							2:2级告警
							3:3级告警
							4:4级告警 */
	uint8_t ALM_PRECHRG_FAIL; /*预充失败
								0:无告警
								1:1级告警 */
	uint8_t ALM_AUX_FAIL; /*	继电器故障
								0:无告警
								1:1级告警 */
	uint8_t ALM_BMU_FAIL; /*	BMU故障
								0:无告警
								1:1级告警 */
	uint8_t ALM_VCU_OFFLINE; /*	HCU通信超时
								0:无告警
								1:1级告警（最严重）
								2:2级告警
								3:3级告警
								4:4级告警 */
	uint8_t ALM_HVREL_FAIL; /*	电池高压异常
								0:无告警
								1:1级告警 */
	uint8_t ALM_HALL_BREAK;/*	霍尔断线
								0:无告警
								1:1级告警 */
};


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_CAN1_Init();
  MX_CAN2_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_Delay(500);
	  LED0_TOG();
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
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
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

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

