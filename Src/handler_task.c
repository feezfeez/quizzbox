/**
  * @file    handler_task.c
  * @version 1.0
  */

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "main.h"
#include "fsm_task.h"
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
    eSystemEvent EventToSend;

    for(;;)
    {
        // Block until interrupt on external input occurs
        xQueueReceive(exti_queue, &exti_pin, portMAX_DELAY);

        EventToSend = 0;

        switch(exti_pin)
        {
            case BLUE_BUZZ_BP_Pin:
                EXTI->IMR &= ~BLUE_BUZZ_BP_Pin & ~RED_BUZZ_BP_Pin & ~YELLOW_BUZZ_BP_Pin & ~GREEN_BUZZ_BP_Pin;
                EventToSend = Blue_Buzzer_Pressed_Event;
                break;

            case RED_BUZZ_BP_Pin:
                EXTI->IMR &= ~BLUE_BUZZ_BP_Pin & ~RED_BUZZ_BP_Pin & ~YELLOW_BUZZ_BP_Pin & ~GREEN_BUZZ_BP_Pin;
                EventToSend = Red_Buzzer_Pressed_Event;
                break;

            case YELLOW_BUZZ_BP_Pin:
                EXTI->IMR &= ~BLUE_BUZZ_BP_Pin & ~RED_BUZZ_BP_Pin & ~YELLOW_BUZZ_BP_Pin & ~GREEN_BUZZ_BP_Pin;
                EventToSend = Yellow_Buzzer_Pressed_Event;
                break;

            case GREEN_BUZZ_BP_Pin:
                EXTI->IMR &= ~BLUE_BUZZ_BP_Pin & ~RED_BUZZ_BP_Pin & ~YELLOW_BUZZ_BP_Pin & ~GREEN_BUZZ_BP_Pin;
                EventToSend = Green_Buzzer_Pressed_Event;
                break;

            case OK_BUTTON_Pin:
                EventToSend = Correct_Answer_Event;
                break;

            case KO_BUTTON_Pin:
                EventToSend = Wrong_Answer_Event;
            break;

            default:
                break;
        }

        xQueueSend(fsm_queue, &EventToSend, 0);
    }
}
