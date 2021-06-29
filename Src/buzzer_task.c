/**
  * @file    buzzer_task.c
  * @version 1.0
  */

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "main.h"
#include "fsm_task.h"
#include "config.h"
#include "buzzer_task.h"
#include "task_config.h"
#include "ui_tools.h"

static void _buzzer_task(void *pvParameters);

static const fsm_input_t event_to_send = {End_Of_Correct_UI_Event, NULL};

void create_buzzer_task(void)
{
    // Create task
    xTaskCreate(_buzzer_task, "Buzzer_Task", configMINIMAL_STACK_SIZE,
            NULL, BUZZER_TASK_PRIORITY, &buzzer_task_handle);
}

static void _buzzer_task (void *pvParameters)
{
    // Init
    uint8_t i = 0;
    uint8_t blink_cnt = CORRECT_TOGGL_CNT;
    led_t buzzled = {};

    // Period = 10ms
    portTickType period;
    period = (portTickType)(10/portTICK_RATE_MS);

    for(;;)
    {
        // Init
        i = 0;

        // Block until a buzzer is pressed
        xQueueReceive(buzzer_queue, &buzzled, portMAX_DELAY);

        // Switch off all buzzers LED
        portENTER_CRITICAL();
        set_reset_all_buzzleds(GPIO_PIN_RESET);
        portEXIT_CRITICAL();

        // Blink until answer is approved (or not)
        while((eNextState == Pending_Answer_State) &&
              (uxQueueMessagesWaiting(buzzer_queue) == 0))
        {
            if (i == 0)
            {
                portENTER_CRITICAL();
                HAL_GPIO_TogglePin(buzzled.port, buzzled.pin);
                portEXIT_CRITICAL();
                i = PEND_ANS_PERIOD;
            }
            vTaskDelay(period);
            i--;
        }

        // Reset variables for next while loop
        i = 0;
        blink_cnt = CORRECT_TOGGL_CNT;

        if (eNextState == Correct_UI_State)
        {
            portENTER_CRITICAL();
            HAL_GPIO_WritePin(buzzled.port, buzzled.pin, GPIO_PIN_RESET);
            portEXIT_CRITICAL();

            for (i=0 ; i<BLINK_TOGGLE_TIMING ; i++)
                vTaskDelay(period);
        }

        while (eNextState == Correct_UI_State && blink_cnt != 0)
        {
            portENTER_CRITICAL();
            HAL_GPIO_TogglePin(buzzled.port, buzzled.pin);
            portEXIT_CRITICAL();

            for (i=0 ; i<BLINK_TOGGLE_TIMING ; i++)
                vTaskDelay(period);

            blink_cnt--;
        }

        if (eNextState == Correct_UI_State && blink_cnt == 0)
        {
            xQueueSend(fsm_queue, &event_to_send, 0);
        }
    }
}
