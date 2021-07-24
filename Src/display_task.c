/**
  * @file    display_task.c
  * @version 1.0
  */

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "main.h"
#include "fsm_task.h"
#include "config.h"
#include "display_task.h"
#include "task_config.h"
#include "ui_tools.h"

static void _display_task(void *pvParameters);

void create_display_task(void)
{
    // Create task
    xTaskCreate(_display_task, "Display_Task", configMINIMAL_STACK_SIZE,
            NULL, DISPLAY_TASK_PRIORITY, &display_task_handle);
}

static void _display_task (void *pvParameters)
{
    // Init
    uint8_t digit_sel = 0;

    uint16_t blue_sseg_conv[10] = {B_ZERO, B_ONE, B_TWO, B_THREE, B_FOUR,
                                   B_FIVE, B_SIX, B_SEVEN, B_EIGHT, B_NINE};
    uint16_t red_sseg_conv[10] = {R_ZERO, R_ONE, R_TWO, R_THREE, R_FOUR,
                                  R_FIVE, R_SIX, R_SEVEN, R_EIGHT, R_NINE};
    uint16_t yellow_sseg_conv[10] = {Y_ZERO, Y_ONE, Y_TWO, Y_THREE, Y_FOUR,
                                     Y_FIVE, Y_SIX, Y_SEVEN, Y_EIGHT, Y_NINE};
    uint16_t green_sseg_conv[10] = {G_ZERO, G_ONE, G_TWO, G_THREE, G_FOUR,
                                    G_FIVE, G_SIX, G_SEVEN, G_EIGHT, G_NINE};

    // Period = 1ms
    portTickType period, last_tick_time;
    period = (portTickType)(5/portTICK_RATE_MS);
    last_tick_time = xTaskGetTickCount();

    for(;;)
    {
        // Off digits
        portENTER_CRITICAL();
        HAL_GPIO_WritePin(DIG1_CTL_GPIO_Port, DIG1_CTL_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(DIG2_CTL_GPIO_Port, DIG2_CTL_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(DIG3_CTL_GPIO_Port, DIG3_CTL_Pin, GPIO_PIN_SET);
        portEXIT_CRITICAL();

        // Reset all the segments
        B_SS_A_GPIO_Port->BSRR |= (B_SS_A_Pin | B_SS_B_Pin | B_SS_C_Pin | B_SS_D_Pin |
                                   B_SS_E_Pin | B_SS_F_Pin | B_SS_G_Pin);
        R_SS_A_GPIO_Port->BSRR |= (R_SS_A_Pin | R_SS_B_Pin | R_SS_C_Pin | R_SS_D_Pin |
                                   R_SS_E_Pin | R_SS_F_Pin | R_SS_G_Pin);
        Y_SS_A_GPIO_Port->BSRR |= (Y_SS_A_Pin | Y_SS_B_Pin | Y_SS_C_Pin | Y_SS_D_Pin |
                                   Y_SS_E_Pin | Y_SS_F_Pin | Y_SS_G_Pin);
        G_SS_A_GPIO_Port->BSRR |= (G_SS_A_Pin | G_SS_B_Pin | G_SS_C_Pin | G_SS_D_Pin |
                                   G_SS_E_Pin | G_SS_F_Pin | G_SS_G_Pin);

        // Set the appropriate segments
        if (digit_sel == UNITS)
        {
            B_SS_A_GPIO_Port->BSRR |= blue_sseg_conv[(blue.score % 10)] << 16;
            R_SS_A_GPIO_Port->BSRR |= red_sseg_conv[(red.score % 10)] << 16;
            Y_SS_A_GPIO_Port->BSRR |= yellow_sseg_conv[(yellow.score % 10)] << 16;
            G_SS_A_GPIO_Port->BSRR |= green_sseg_conv[(green.score % 10)] << 16;

            portENTER_CRITICAL();
            HAL_GPIO_WritePin(DIG3_CTL_GPIO_Port, DIG3_CTL_Pin, GPIO_PIN_RESET);
            portEXIT_CRITICAL();
        }
        else if (digit_sel == TENS)
        {
            if (blue.score > 9)
                B_SS_A_GPIO_Port->BSRR |= blue_sseg_conv[((blue.score/10) % 10)] << 16;
            if (red.score > 9)
                R_SS_A_GPIO_Port->BSRR |= red_sseg_conv[((red.score/10) % 10)] << 16;
            if (yellow.score > 9)
                Y_SS_A_GPIO_Port->BSRR |= yellow_sseg_conv[((yellow.score/10) % 10)] << 16;
            if (green.score > 9)
                G_SS_A_GPIO_Port->BSRR |= green_sseg_conv[((green.score/10) % 10)] << 16;

            portENTER_CRITICAL();
            HAL_GPIO_WritePin(DIG2_CTL_GPIO_Port, DIG2_CTL_Pin, GPIO_PIN_RESET);
            portEXIT_CRITICAL();
        }
        else if (digit_sel == HUNDREDS)
        {
            if (blue.score > 99)
                B_SS_A_GPIO_Port->BSRR |= blue_sseg_conv[((blue.score/100) % 10)] << 16;
            if (red.score > 99)
                R_SS_A_GPIO_Port->BSRR |= red_sseg_conv[((red.score/100) % 10)] << 16;
            if (yellow.score > 99)
                Y_SS_A_GPIO_Port->BSRR |= yellow_sseg_conv[((yellow.score/100) % 10)] << 16;
            if (green.score > 99)
                G_SS_A_GPIO_Port->BSRR |= green_sseg_conv[((green.score/100) % 10)] << 16;

            HAL_GPIO_WritePin(DIG1_CTL_GPIO_Port, DIG1_CTL_Pin, GPIO_PIN_RESET);
        }

        digit_sel++;

        if (digit_sel > DIGIT_MAX_NUMBER-1)
            digit_sel = 0;

        // Wait
        vTaskDelayUntil(&last_tick_time, period);
    }
}
