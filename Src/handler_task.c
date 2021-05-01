/**
  * @file    handler_task.c
  * @version 1.0
  */

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "main.h"
#include "config.h"
#include "handler_task.h"
#include "task_config.h"

static void _handler_task(void *pvParameters);

void create_handler_task(void)
{
    // Create task
    xTaskCreate(_handler_task, "Handler_Task", configMINIMAL_STACK_SIZE,
            NULL, HANDLER_TASK_PRIORITY, handler_task_handle);
}

static void _handler_task (void *pvParameters)
{
    // Init
    uint16_t exti_pin = 0;

    // XXX Period = 10ms?
    portTickType period;
    period = (portTickType)(10/portTICK_RATE_MS);

    for(;;)
    {
        // Block until interrupt on external input occurs
        xQueueReceive(exti_queue, &exti_pin, portMAX_DELAY);

        if (exti_pin == BLUE_BUZZ_BP_Pin || exti_pin == RED_BUZZ_BP_Pin ||
            exti_pin == YELLOW_BUZZ_BP_Pin || exti_pin == GREEN_BUZZ_BP_Pin)
        {
            EXTI->IMR &= ~BLUE_BUZZ_BP_Pin & ~RED_BUZZ_BP_Pin & ~YELLOW_BUZZ_BP_Pin & ~GREEN_BUZZ_BP_Pin;
            xQueueOverwrite(buzzer_id_queue, &exti_pin);
        }
        else if (exti_pin == OK_BUTTON_Pin)
        {
            correct_ans = 1;
        }
        else if (exti_pin == KO_BUTTON_Pin)
        {
            wrong_ans = 1;
        }
    }
}
