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

        if (eNextState == Idle_State)
            continue;

        EventToSend = 0;

        if (exti_pin == blue.buzzer)
        {
            EXTI->IMR &= ~(blue.buzzer) & ~(red.buzzer) &
                         ~(yellow.buzzer) & ~(green.buzzer);
            EventToSend = Blue_Buzzer_Pressed_Event;
        }
        else if (exti_pin == red.buzzer)
        {
            EXTI->IMR &= ~(blue.buzzer) & ~(red.buzzer) &
                         ~(yellow.buzzer) & ~(green.buzzer);
            EventToSend = Red_Buzzer_Pressed_Event;
        }
        else if (exti_pin == yellow.buzzer)
        {
            EXTI->IMR &= ~(blue.buzzer) & ~(red.buzzer) &
                         ~(yellow.buzzer) & ~(green.buzzer);
            EventToSend = Yellow_Buzzer_Pressed_Event;
        }
        else if (exti_pin == green.buzzer)
        {
            EXTI->IMR &= ~(blue.buzzer) & ~(red.buzzer) &
                         ~(yellow.buzzer) & ~(green.buzzer);
            EventToSend = Green_Buzzer_Pressed_Event;
        }
        else if (exti_pin == OK_SINGLE_BP_Pin)
        {
            EventToSend = Correct_Answer_Single_Event;
        }
        else if (exti_pin == KO_BP_Pin)
        {
            EventToSend = Wrong_Answer_Event;
        }

        xQueueSend(fsm_queue, &EventToSend, 0);
    }
}
