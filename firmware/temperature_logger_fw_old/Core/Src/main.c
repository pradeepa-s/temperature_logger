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
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

// TODO

// - Check RTC time drift
// - Check power consumption
// - Check power switching
// - Check min battery voltage
// - Blink LED when erasing
// - Blink LED when reading


/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <stdio.h>
#include "event_manager.h"
#include "button.h"
#include "storage_controller.h"
#include "pc_comms.h"
#include "dev_time.h"
#include "tmp112_sensor.h"
#include "dev_led.h"
#include "dev_operation_tracker.h"
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

/* USER CODE BEGIN PV */
uint8_t is_in_config = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void log_temperature();
void chip_read();
void chip_erase();
void update_time();
void get_state();
void change_alarm();
void indicate_alarm();
void tmp112_i2c_tx_func(uint8_t address, uint8_t* data, size_t size);
void tmp112_i2c_rx_func(uint8_t address, uint8_t* read_data, size_t size);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	process_button_event();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim2)
	{
		dev_led_low_done();
	}
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim21 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		button_press_and_hold();
	}
	else if(htim == &htim2 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		dev_led_high_done();
	}
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
    rtc_alarm_elapsed();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	data_received_from_pc();
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
  MX_TIM2_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  MX_RTC_Init();
  MX_I2C1_Init();
  MX_TIM21_Init();
  /* USER CODE BEGIN 2 */

  tmp112_sensor_init(0x48, tmp112_i2c_tx_func, tmp112_i2c_rx_func);
  button_init(submit_event);
  dev_time_init(submit_event);
  pc_comms_init(submit_event);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint8_t was_in_config = is_in_config;

#ifdef STARTUP_TEST
  for (int i = 0; i < 12; i++)
  {
	  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
	  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);
	  HAL_Delay(250);
  }

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
  while(1)
  {
	  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
	  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);
	  HAL_Delay(1000);
  }
#endif

#ifdef PRINT_TIME
  while(1)
  {
	  Timestamp ts;
	  get_timestamp(&ts);
	  HAL_UART_Transmit(&huart1, ts.buffer, sizeof(ts.buffer), 0xFFFFFFFF);
	  HAL_Delay(1000);
  }
#endif

#ifdef STORAGE_READ_WRITE
  {
	  flash_storage_erase_full();

	  storage_entry se;
	  se.dt.year = 2022;
	  se.dt.month = 11;
	  se.dt.date = 18;
	  se.dt.hour = 21;

	  // Create 1000 dummy data items
	  for (int i = 0; i < 100; i++)
	  {
		  se.tr = i % 50;
		  se.dt.minute = i / 60;
		  se.dt.seconds = i % 60;
		  flash_storage_write(&se, 1);
	  }

	  int turn = 0;
	  while (1)
	  {
		  int count = flash_storage_read(&se, 1);

		  if (count)
		  {
			  const datetime* dt = &(se.dt);

			  char reading[34] = {0};
			  snprintf(reading, sizeof(reading), "\r\n[%04d].%04d:%02d:%02d:%02d:%02d:%02d:%04d",
					turn, dt->year, dt->month, dt->date, dt->hour, dt->minute, dt->seconds,
					se.tr);
			  HAL_UART_Transmit(&huart1, (uint8_t*)reading, sizeof(reading), 0xFFFFFFFF);
			  turn++;
			  HAL_Delay(200);
		  }
		  else
		  {
			  while(1);
		  }
	  }
  }
#endif


  // TODO: Find next write address
  storage_controller_init();

  HAL_DBGMCU_EnableDBGStopMode();

  while (1)
  {
      event_id ev = get_next_event();

	  if (!is_in_config && DEVICE_EVENT_NONE == ev && !dev_operation_is_pending())
	  {
		  HAL_SuspendTick();
		  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
		  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

		  SystemClock_Config();
		  ev = get_next_event();
	  }

      switch(ev)
      {
          case DEVICE_EVENT_RTC_ALARM_ELAPSED:
              log_temperature();
              break;

          case DEVICE_EVENT_CHIP_READ:
              if (is_in_config)
              {
            	  chip_read();
              }
              break;

          case DEVICE_EVENT_LONG_BUTTON_PRESS:
              is_in_config = ~is_in_config;
              break;

          case DEVICE_EVENT_CHIP_ERASE:
              if (is_in_config)
              {
            	  // TODO:
            	  // stop logging
                  chip_erase();
                  // start logging
              }
              else
              {
            	  // TODO: Send error
              }
              break;

          case DEVICE_EVENT_UPDATE_TIME:
              if (is_in_config)
              {
            	  update_time();
              }
              break;

          case DEVICE_EVENT_GET_STATE:
              if (is_in_config)
              {
            	  get_state();
              }
              break;

          case DEVICE_EVENT_SINGLE_BUTTON_PRESS:
              if (is_in_config)
              {
                  change_alarm();
              }
              else
              {
                  indicate_alarm();
              }
              break;

          default:
              break;
      }

	  if (is_in_config != was_in_config)
	  {
		  char done[] = "<<M";
		  HAL_UART_Transmit(&huart1, (uint8_t*)done, sizeof(done), 0xFFFFFFFF);
          indicate_alarm();
		  was_in_config = is_in_config;

		  if (is_in_config)
		  {
			  HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
		  }
		  else
		  {
			  HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
		  }
	  }

      complete_event(ev);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_RTC;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void log_temperature()
{
    //char done[] = "<<L";
    //HAL_UART_Transmit(&huart1, (uint8_t*)done, sizeof(done), 0xFFFFFFFF);
	storage_entry se;
    set_next_alarm();
    double true_temp = tmp112_sensor_get_temperature();
    se.tr = true_temp * 10000;
    get_datetime(&(se.dt));
    flash_storage_write(&se, 1);
}

void chip_read()
{
    flash_storage_read_start();

    int read_index = 0;
    while (1)
    {
		storage_entry se;

		int count = flash_storage_read(&se, 1);

		if (count)
		{
		  const datetime* dt = &(se.dt);

		  char reading[34] = {0};
		  snprintf(reading, sizeof(reading), "\r\n[%04d].%04d:%02d:%02d:%02d:%02d:%02d:%04d",
				  read_index, dt->year, dt->month, dt->date, dt->hour, dt->minute, dt->second,
				se.tr);
		  HAL_UART_Transmit(&huart1, (uint8_t*)reading, sizeof(reading), 0xFFFFFFFF);
		  ++read_index;
		  HAL_Delay(50);
		}
		else
		{
		  return;
		}
	}
}

void chip_erase()
{
	flash_storage_erase_full();
    char done[] = "<<E";
    HAL_UART_Transmit(&huart1, (uint8_t*)done, sizeof(done), 0xFFFFFFFF);
}

void update_time()
{
    dev_time_set(pc_comms_yy, pc_comms_mm, pc_comms_dd, pc_comms_hh, pc_comms_min, pc_comms_ss);
    char done[] = "<<T";
    HAL_UART_Transmit(&huart1, (uint8_t*)done, sizeof(done), 0xFFFFFFFF);
}

void get_state()
{
	datetime dt;
    double true_temp = tmp112_sensor_get_temperature();
    temperature tr = true_temp * 10000;
    get_datetime(&dt);
    char status[27] = {0};
	snprintf(status, sizeof(status), "%04d:%02d:%02d:%02d:%02d:%02d:%04d\r\n",
		  dt.year, dt.month, dt.date, dt.hour, dt.minute, dt.second, tr);
    HAL_UART_Transmit(&huart1, (uint8_t*)status, sizeof(status), 0xFFFFFFFF);
}

void change_alarm()
{
    dev_time_alarm_change();
    indicate_alarm();
}

void indicate_alarm()
{
    uint8_t alarm = dev_time_get_alarm();
    dev_led_indicate_alarm(alarm);
    dev_operation_complete(DEV_OPERATION_BUTTON);
}

void tmp112_i2c_tx_func(uint8_t address, uint8_t* data, size_t size)
{
	HAL_I2C_Master_Transmit(&hi2c1, (address << 1), data, size, 0xffffffff);
}

void tmp112_i2c_rx_func(uint8_t address, uint8_t* read_data, size_t size)
{
	HAL_I2C_Master_Receive(&hi2c1, (address << 1), read_data, size, 0xffffffff);
}
/* USER CODE END 4 */

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
