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

    // Period = 10ms
    portTickType period;
    period = (portTickType)(10/portTICK_RATE_MS);

    for(;;)
    {
        // Init

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

        // Display and switch digit

        digit_sel++;

        if (digit_sel > DIGIT_MAX_NUMBER-1)
            digit_sel = 0;

        // Wait for period
        vTaskDelay(period);
    }
}
