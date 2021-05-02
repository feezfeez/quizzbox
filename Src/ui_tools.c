/**
  * @file    ui_tools.c
  * @version 1.0
  */

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "main.h"
#include "fsm_task.h"
#include "config.h"
#include "ui_tools.h"


void set_reset_all_buzzleds(GPIO_PinState set_reset)
{
    HAL_GPIO_WritePin(BLUE_BUZZ_LED_GPIO_Port, BLUE_BUZZ_LED_Pin, set_reset);
    HAL_GPIO_WritePin(RED_BUZZ_LED_GPIO_Port, RED_BUZZ_LED_Pin, set_reset);
    HAL_GPIO_WritePin(YELLOW_BUZZ_LED_GPIO_Port, YELLOW_BUZZ_LED_Pin, set_reset);
    HAL_GPIO_WritePin(GREEN_BUZZ_LED_GPIO_Port, GREEN_BUZZ_LED_Pin, set_reset);
}

void toggle_all_buzzleds(void)
{
    HAL_GPIO_TogglePin(BLUE_BUZZ_LED_GPIO_Port, BLUE_BUZZ_LED_Pin);
    HAL_GPIO_TogglePin(RED_BUZZ_LED_GPIO_Port, RED_BUZZ_LED_Pin);
    HAL_GPIO_TogglePin(YELLOW_BUZZ_LED_GPIO_Port, YELLOW_BUZZ_LED_Pin);
    HAL_GPIO_TogglePin(GREEN_BUZZ_LED_GPIO_Port, GREEN_BUZZ_LED_Pin);
}

void mask_buzzleds(uint32_t players_mask)
{
    if ((players_mask & BLUE_BUZZ_BP_Pin) == BLUE_BUZZ_BP_Pin)
        HAL_GPIO_WritePin(BLUE_BUZZ_LED_GPIO_Port, BLUE_BUZZ_LED_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(BLUE_BUZZ_LED_GPIO_Port, BLUE_BUZZ_LED_Pin, GPIO_PIN_RESET);

    if ((players_mask & RED_BUZZ_BP_Pin) == RED_BUZZ_BP_Pin)
        HAL_GPIO_WritePin(RED_BUZZ_LED_GPIO_Port, RED_BUZZ_LED_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(RED_BUZZ_LED_GPIO_Port, RED_BUZZ_LED_Pin, GPIO_PIN_RESET);

    if ((players_mask & YELLOW_BUZZ_BP_Pin) == YELLOW_BUZZ_BP_Pin)
        HAL_GPIO_WritePin(YELLOW_BUZZ_LED_GPIO_Port, YELLOW_BUZZ_LED_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(YELLOW_BUZZ_LED_GPIO_Port, YELLOW_BUZZ_LED_Pin, GPIO_PIN_RESET);

    if ((players_mask & GREEN_BUZZ_BP_Pin) == GREEN_BUZZ_BP_Pin)
        HAL_GPIO_WritePin(GREEN_BUZZ_LED_GPIO_Port, GREEN_BUZZ_LED_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(GREEN_BUZZ_LED_GPIO_Port, GREEN_BUZZ_LED_Pin, GPIO_PIN_RESET);

}

void blink_all_buzzleds(uint8_t blink_cnt, portTickType period)
{
    uint8_t i = 0;
    uint8_t state_timing = TOGGLE_TIMING;

    for (i=0 ; i<state_timing ; i++)
        vTaskDelay(period);

    while (blink_cnt != 0)
    {
        portENTER_CRITICAL();
        toggle_all_buzzleds();
        portEXIT_CRITICAL();

        for (i=0 ; i<state_timing ; i++)
            vTaskDelay(period);

        blink_cnt--;
    }
}

void blink_single_buzzled(buzz_led_t buzzer_led, uint8_t blink_cnt, portTickType period)
{
    uint8_t i = 0;
    uint8_t state_timing = TOGGLE_TIMING;

    for (i=0 ; i<state_timing ; i++)
        vTaskDelay(period);

    while (blink_cnt != 0)
    {
        portENTER_CRITICAL();
        HAL_GPIO_TogglePin(buzzer_led.buzz_led_port, buzzer_led.buzz_led_pin);
        portEXIT_CRITICAL();

        for (i=0 ; i<state_timing ; i++)
            vTaskDelay(period);

        blink_cnt--;
    }
}