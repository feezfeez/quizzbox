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
    digit_t digit = {};
    uint8_t digit_sel = 0;
    sevenseg_data_t sevenseg_data = {};

    // Period = 1ms
    portTickType period, last_tick_time;
    period = (portTickType)(1/portTICK_RATE_MS);
    last_tick_time = xTaskGetTickCount();

    for(;;)
    {
        // Split digits
        if (digit_sel == 0)
        {
            digit.blue = blue.score % 10;
            digit.red = red.score % 10;
            digit.yellow = yellow.score % 10;
            digit.green = green.score % 10;
        }
        else if (digit_sel == 1)
        {
            digit.blue = (blue.score / 10) % 10;
            digit.red = (red.score / 10) % 10;
            digit.yellow = (yellow.score / 10) % 10;
            digit.green = (green.score / 10) % 10;
        }
        else if (digit_sel == 2)
        {
            digit.blue = (blue.score / 100) % 10;
            digit.red = (red.score / 100) % 10;
            digit.yellow = (yellow.score / 100) % 10;
            digit.green = (green.score / 100) % 10;
        }

        // Convert digit to seven segments data
        sevenseg_data.blue = num_to_sevenseg(digit.blue, blue.buzzer);
        sevenseg_data.red = num_to_sevenseg(digit.red, red.buzzer);
        sevenseg_data.yellow = num_to_sevenseg(digit.yellow, yellow.buzzer);
        sevenseg_data.green = num_to_sevenseg(digit.green, green.buzzer);

        // Off digits

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
        if (digit_sel == 0)
        {
            B_SS_A_GPIO_Port->BSRR |= sevenseg_data.blue << 16;
            R_SS_A_GPIO_Port->BSRR |= sevenseg_data.red << 16;
            Y_SS_A_GPIO_Port->BSRR |= sevenseg_data.yellow << 16;
            G_SS_A_GPIO_Port->BSRR |= sevenseg_data.green << 16;
        }

        // On digits

        digit_sel++;

        if (digit_sel > DIGIT_MAX_NUMBER-1)
            digit_sel = 0;

        // Wait
        vTaskDelayUntil(&last_tick_time, period);
    }
}
