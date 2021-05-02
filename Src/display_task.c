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
    scores_t scores = {};
    digit_t players_digit = {};
    winner_t winner = {};
    uint8_t digit_sel = 0;

    // Period = 10ms
//    portTickType period;
//    period = (portTickType)(10/portTICK_RATE_MS);

    for(;;)
    {
        // Init
        if ((xQueueReceive(display_queue, &winner, 10) == pdTRUE))
        {
            if (winner.player == BLUE_BUZZ_LED_Pin)
                scores.blue_score += winner.points;
            else if (winner.player == RED_BUZZ_LED_Pin)
                scores.red_score += winner.points;
            else if (winner.player == YELLOW_BUZZ_LED_Pin)
                scores.yellow_score += winner.points;
            else if (winner.player == GREEN_BUZZ_LED_Pin)
                scores.green_score += winner.points;
        }

        // Split digits
        if (digit_sel == 0)
        {
            players_digit.blue_digit = scores.blue_score % 10;
            players_digit.red_digit = scores.red_score % 10;
            players_digit.yellow_digit = scores.yellow_score % 10;
            players_digit.green_digit = scores.green_score % 10;
        }
        else if (digit_sel == 1)
        {
            players_digit.blue_digit = (scores.blue_score / 10) % 10;
            players_digit.red_digit = (scores.red_score / 10) % 10;
            players_digit.yellow_digit = (scores.yellow_score / 10) % 10;
            players_digit.green_digit = (scores.green_score / 10) % 10;
        }
        else if (digit_sel == 2)
        {
            players_digit.blue_digit = (scores.blue_score / 100) % 10;
            players_digit.red_digit = (scores.red_score / 100) % 10;
            players_digit.yellow_digit = (scores.yellow_score / 100) % 10;
            players_digit.green_digit = (scores.green_score / 100) % 10;
        }

        // Display and switch digit

        digit_sel++;

        if (digit_sel > 2)
            digit_sel = 0;
    }
}
